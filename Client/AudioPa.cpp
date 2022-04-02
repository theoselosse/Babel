/*
** EPITECH PROJECT, 2021
** sound.cpp
** File description:
** sound.cpp
*/

#include "../include/AudioPa.hpp"

// --- BEGINNING AUDIO PARAMS CLASS ---

AudioParams::AudioParams() :
    frameIndex(0), maxFrameIndex(NUM_SECONDS * SAMPLE_RATE)
{   
    int numBytes;

    this->numSamples = maxFrameIndex * NUM_CHANNELS;
    numBytes = numSamples * sizeof(SAMPLE);
    this->recordedSamples = (SAMPLE *) malloc(numBytes);
    if (this->recordedSamples == NULL) {
        std::cout << "Malloc failed." << std::endl;
        exit(64);
    }
    for (int i = 0; i < this->numSamples; i++) {
        this->recordedSamples[i] = 0;
    }
}

AudioParams::~AudioParams()
{
    free(recordedSamples);
}

int AudioParams::getFrameIndex()
{
    return (this->frameIndex);
}

int AudioParams::getMaxIndex()
{
    return (this->maxFrameIndex);
}

int AudioParams::getNumSamples()
{
    return (this->numSamples);
}

SAMPLE *AudioParams::getSample()
{
    return (this->recordedSamples);
}

void AudioParams::setFrameIndex(int newFrame)
{
    this->frameIndex = newFrame;
}

// --- AUDIO MANAGER CLASS ---

AudioManager::AudioManager() :
    inCall(false), channel(1), sample(48000), stream(nullptr)
{
    this->paTestData = new AudioParams;

    this->err = Pa_Initialize();
    if (this->err != paNoError)
        exit(64);
    this->paTestData->setFrameIndex(0);
}

AudioManager::~AudioManager()
{
    Pa_Terminate();
}

AudioParams *AudioManager::getParams()
{
    return (this->paTestData);
}

void AudioManager::launchCall()
{
    this->inPam.device = Pa_GetDefaultInputDevice();
    if (this->inPam.device == paNoDevice) {
        std::cout << "No input device :(" << std::endl;
        exit(64);
    }
    this->inPam.channelCount = 2;
	this->inPam.sampleFormat = PA_SAMPLE_TYPE;
	this->inPam.suggestedLatency = Pa_GetDeviceInfo(this->inPam.device)->defaultLowInputLatency;
	this->inPam.hostApiSpecificStreamInfo = NULL;
    this->ouPam.device = Pa_GetDefaultOutputDevice();
    if (this->ouPam.device == paNoDevice) {
        std::cout << "No output device :( )." << std::endl;
        exit(64);
    }
    this->ouPam.channelCount = 2;
    this->ouPam.sampleFormat =  PA_SAMPLE_TYPE;
    this->ouPam.suggestedLatency = Pa_GetDeviceInfo(this->ouPam.device)->defaultLowOutputLatency;
    this->ouPam.hostApiSpecificStreamInfo = NULL;
    this->err = Pa_OpenStream(&stream, &inPam, &ouPam, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, convCallback, this);
    if (this->err != paNoError)
        exit(64);
}

int AudioManager::callBackMethod(const void *tmp_buff, void *outputBuffer, unsigned long frm, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags)
{
    long framesToCalc;
    long i;
    int finished;
    unsigned long framesLeft;

    const SAMPLE *rptr = (const SAMPLE*)tmp_buff;
    SAMPLE *wptr = &this->getParams()->getSample()[this->getParams()->getFrameIndex() * NUM_CHANNELS];
    SAMPLE *speaker = (SAMPLE *)outputBuffer;
    framesLeft = this->getParams()->getMaxIndex() - this->getParams()->getFrameIndex();
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;
    if (framesLeft < frm) {
        framesToCalc = framesLeft;
        finished = paComplete;
    } else {
        framesToCalc = frm;
        finished = paContinue;
    }
    if (tmp_buff == NULL) {
        for (i = 0; i < framesToCalc; i++) {
            *wptr++ = SAMPLE_SILENCE;
            if (NUM_CHANNELS == 2)
                *wptr++ = SAMPLE_SILENCE;
        }
    } else {
        for (i = 0; i < framesToCalc; i++) {
            wptr[i] = *rptr++;
            if (NUM_CHANNELS == 2)
                wptr[i] = *rptr++;
        }
    }
    // UDP SEND wptr
    // UDP RECEIVE <= 480 /// IF NO PACKET => PACKET SILENCE
    // speaker = wpr /// speaker = udp_packet.payload
    for (i = 0; i < framesToCalc; ++i) {
        *speaker++ = wptr[i];
        if (NUM_CHANNELS == 2)
            *speaker++ = wptr[i];
    }
    this->getParams()->setFrameIndex((this->getParams()->getFrameIndex() + framesToCalc));
    if (finished == paComplete) {
        this->getParams()->setFrameIndex(0);
        // FIN DE CONVERSATION -> paComplete
        finished = paContinue;
    }
    return (finished);
}

void AudioManager::startStream()
{
    this->err = Pa_StartStream(this->stream);
    if (this->err != paNoError) {
        std::cerr << err << std::endl;
        exit(64);
    }
    while ((err = Pa_IsStreamActive(this->stream)) == 1) {
        Pa_Sleep(1000);
    }
    if (err < 0)
        exit(64);
}

void AudioManager::stopStream()
{
    PaError paErr = Pa_StopStream(this->stream);

    if (this->err != paNoError)
        exit(64);
    this->inCall = false;
}

void AudioManager::closeStream()
{
    this->err = Pa_CloseStream(this->stream);
    if (this->err != paNoError)
        exit(64);
}