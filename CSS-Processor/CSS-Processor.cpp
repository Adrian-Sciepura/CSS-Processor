#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <chrono>
#include "Processor.h"

//SPEED TEST
//void program()
//{
//    List list;
//    for (int i = 0; i < 200; i++)
//    {
//        list.newNode();
//        ListNode* curr = list.last;
//
//        for (int j = 0; j < 1000; j++)
//        {
//            curr->attributes.add({ "abcdefgh", "123456" });
//            curr->selectors.add({ "xxxxx" });
//        }
//    }
//
//    std::cout << "Allocated " << list.numberOfNodes << " sections\n";
//    int counter1 = 0;
//    int counter2 = 0;
//    ListNode* search = list.first;
//    for (int i = 0; i < 200; i++)
//    {
//        counter1 += search->attributes.numberOfElements;
//        counter2 += search->selectors.numberOfElements;
//
//        search = search->next;
//    }
//    std::cout << "Allocated " << counter1 << " attributes\n";
//    std::cout << "Allocated " << counter2 << " selectors\n";
//}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    
    Processor processor;
    processor.start();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time: " << duration.count() << " microseconds\n";
    
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();
}