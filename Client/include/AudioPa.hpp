/*
** EPITECH PROJECT, 2021
** sound.hpp
** File description:
** soud.hpp
*/

#ifndef SOUND_HPP
#define SOUND_HPP

#include <portaudio.h>
#include <string>
#include <iostream>

/* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
#define SAMPLE_RATE  (48000)
#define FRAMES_PER_BUFFER (480)
#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (2)

/* #define DITHER_FLAG     (paDitherOff) */
#define DITHER_FLAG     (0) /**/

/* Select sample format. */
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"

class AudioParams {
    public:
        AudioParams();
        ~AudioParams();
        int getFrameIndex();
        int getMaxIndex();
        int getNumSamples();
        void setFrameIndex(int);
        SAMPLE *getSample();
    
    private:
        int frameIndex; 
        int maxFrameIndex;
        int numSamples;
        SAMPLE *recordedSamples;
};

class AudioManager {
    public:
        AudioManager();
        ~AudioManager();
        void launchCall();
        void startStream();
        void stopStream();
        void closeStream();
        AudioParams *getParams();
        int callBackMethod(const void *, void *, unsigned long, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags);

    private:
        AudioParams *paTestData;
        bool inCall;
        char channel;
        int sample;
        PaStreamParameters inPam;
        PaStreamParameters ouPam;
        PaStream* stream;
        PaError err = paNoError;
        const void *inputBuffer;
        void *outputBuffer;
        const PaStreamCallbackTimeInfo* timeInfo;
        PaStreamCallbackFlags statusFlags;
        void *userData;
};

// --- CALLBACK ---

static int convCallback (const void *tmp_buff, void *outputBuffer, unsigned long frm, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    AudioManager *data = new AudioManager;

    data = static_cast<AudioManager *>(userData);
    return (data->callBackMethod(tmp_buff, outputBuffer, frm, timeInfo, statusFlags));
}

#endif /* !SOUND_HPP */