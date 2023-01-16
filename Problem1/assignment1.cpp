#include "topFivePctContainer.h"
#include <chrono>
#include <iostream>

// On my laptop, RAND MAX is 2147483647

// #define ARRAY_SIZE 12800000
#define ARRAY_SIZE 12800000
#define ALLOCATION_SIZE 12800000
#define CARDINALITY 128000000
#define PRINT_INTERVAL 524287

int main() {
    nodeAllocator allocator(ALLOCATION_SIZE);
    splitList splits(10, 2, allocator); // 4, 1 comes in at 8 minutes
   
    topFivePctContainer container(splits, allocator, ARRAY_SIZE);
    srand((unsigned)time(0));

    container.insertFirst((double)(rand() % CARDINALITY));
    container.insertSecond((double)(rand() % CARDINALITY));

    for (int i = 2; i < ARRAY_SIZE; ++ i){
        container.insertNumber((double)(rand() % CARDINALITY));
        // std::cout << container.counter_ << ": ";
        // std::cout << container.getMarker() << '\n';
        if ((container.counter_ & PRINT_INTERVAL) == 0) {
            auto now = std::chrono::system_clock::now();
        
            auto nowTime = std::chrono::system_clock::to_time_t(now);
        
            std::cout << "Time At " << container.counter_ << ":" << std::ctime(&nowTime);
        }
    }

    return 0;
}

/* With Array Size + Cardinality 12,800,00
[davidbernardo@localhost build]$ date && time ./Assignment1
Mon Jan 16 01:10:57 PM CST 2023
Time At 524288:Mon Jan 16 13:10:58 2023
Time At 1048576:Mon Jan 16 13:11:00 2023
Time At 1572864:Mon Jan 16 13:11:03 2023
Time At 2097152:Mon Jan 16 13:11:06 2023
Time At 2621440:Mon Jan 16 13:11:08 2023
Time At 3145728:Mon Jan 16 13:11:11 2023
Time At 3670016:Mon Jan 16 13:11:14 2023
Time At 4194304:Mon Jan 16 13:11:16 2023
Time At 4718592:Mon Jan 16 13:11:19 2023
Time At 5242880:Mon Jan 16 13:11:22 2023
Time At 5767168:Mon Jan 16 13:11:25 2023
Time At 6291456:Mon Jan 16 13:11:27 2023
Time At 6815744:Mon Jan 16 13:11:30 2023
Time At 7340032:Mon Jan 16 13:11:32 2023
Time At 7864320:Mon Jan 16 13:11:34 2023
Time At 8388608:Mon Jan 16 13:11:37 2023
Time At 8912896:Mon Jan 16 13:11:39 2023
Time At 9437184:Mon Jan 16 13:11:41 2023
Time At 9961472:Mon Jan 16 13:11:43 2023
Time At 10485760:Mon Jan 16 13:11:45 2023
Time At 11010048:Mon Jan 16 13:11:47 2023
Time At 11534336:Mon Jan 16 13:11:49 2023
Time At 12058624:Mon Jan 16 13:11:51 2023
Time At 12582912:Mon Jan 16 13:11:52 2023

real	0m56.363s
user	0m55.883s
sys	0m0.297s
*/

/* With Array Size + Cardinality 128,000,000
ime At 524288:Mon Jan 16 13:12:42 2023
Time At 1048576:Mon Jan 16 13:12:45 2023
Time At 1572864:Mon Jan 16 13:12:50 2023
Time At 2097152:Mon Jan 16 13:12:59 2023
Time At 2621440:Mon Jan 16 13:13:14 2023
Time At 3145728:Mon Jan 16 13:13:35 2023
Time At 3670016:Mon Jan 16 13:14:01 2023
Time At 4194304:Mon Jan 16 13:14:33 2023
Time At 4718592:Mon Jan 16 13:15:11 2023
Time At 5242880:Mon Jan 16 13:15:56 2023
Time At 5767168:Mon Jan 16 13:16:48 2023
Time At 6291456:Mon Jan 16 13:17:46 2023
*/

/* With Array Size 12,800,000 + Cardinality 128,000,000
[davidbernardo@localhost build]$ date && time ./Assignment1
Mon Jan 16 01:19:24 PM CST 2023
Time At 524288:Mon Jan 16 13:19:26 2023
Time At 1048576:Mon Jan 16 13:19:28 2023
Time At 1572864:Mon Jan 16 13:19:31 2023
Time At 2097152:Mon Jan 16 13:19:33 2023
Time At 2621440:Mon Jan 16 13:19:36 2023
Time At 3145728:Mon Jan 16 13:19:39 2023
Time At 3670016:Mon Jan 16 13:19:42 2023
Time At 4194304:Mon Jan 16 13:19:45 2023
Time At 4718592:Mon Jan 16 13:19:48 2023
Time At 5242880:Mon Jan 16 13:19:50 2023
Time At 5767168:Mon Jan 16 13:19:53 2023
Time At 6291456:Mon Jan 16 13:19:56 2023
Time At 6815744:Mon Jan 16 13:19:58 2023
Time At 7340032:Mon Jan 16 13:20:01 2023
Time At 7864320:Mon Jan 16 13:20:03 2023
Time At 8388608:Mon Jan 16 13:20:05 2023
Time At 8912896:Mon Jan 16 13:20:08 2023
Time At 9437184:Mon Jan 16 13:20:10 2023
Time At 9961472:Mon Jan 16 13:20:12 2023
Time At 10485760:Mon Jan 16 13:20:14 2023
Time At 11010048:Mon Jan 16 13:20:16 2023
Time At 11534336:Mon Jan 16 13:20:18 2023
Time At 12058624:Mon Jan 16 13:20:19 2023
Time At 12582912:Mon Jan 16 13:20:21 2023
*/