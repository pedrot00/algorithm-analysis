#include "Mediana.h"

bool invertCompare(int a, int b) {
    return a > b;  
}

void Mediana::balanceHeaps() {
    if (maxHeap.size() > minHeap.size() + 1) {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
    } else if (minHeap.size() > maxHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
    }
}

void Mediana::insere(int x) {
    if (maxHeap.size() == 0 || x <= maxHeap.top()) {
        maxHeap.push(x);
    } else {
        minHeap.push(-x);
    }
    balanceHeaps();
}

int Mediana::getMediana() {
    if (maxHeap.size() == minHeap.size()) {
        return (maxHeap.top() + (-minHeap.top())) / 2;
    } else {
        return maxHeap.top();
    }
}