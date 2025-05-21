#ifndef MEDIANA_H
#define MEDIANA_H

#include "MyPriorityQueue.h"

class Mediana {
private:
    MyPriorityQueue<int> maxHeap; 
    MyPriorityQueue<int> minHeap;  

    void balanceHeaps();

public:
    void insere(int x);  // O(log n)
    int getMediana();    // O(1)
};

#endif