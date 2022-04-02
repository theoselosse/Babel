#include <iostream>
#include <future>
#include <thread>
#include <chrono>
 
// int main()
// {
//     std::future<int> future = std::async(std::launch::async, [](){ 
//         std::this_thread::sleep_for(std::chrono::seconds(10));
//         return 10;
//     });
//     std::cout << "waiting...\n";
//     std::future_status status;
//     do {
//         status = future.wait_for(std::chrono::seconds(10));
//         if (status == std::future_status::timeout) {
//             std::cout << "timeout\n";
//         } else if (status == std::future_status::ready) {
//             std::cout << "ready!\n";
//         }
//     } while (status != std::future_status::ready);
//     std::cout << "STOP!\n";
// }