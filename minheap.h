#include <iostream>
#include <cfloat>
#include <cmath>
#include <string>

class MinHeap {
    private:
        int* vertices;
        double* distances;
        int* indexMap;
        int capacity; 
        int size;

        void heapifyUp(int index);
        void heapifyDown(int index);
        void swapNodes(int i, int j);

    public:
        MinHeap(int maxCapacity);
        ~MinHeap();

        bool isEmpty();
        void push(int vertex, double distance);
        int pop();
        void decreaseKey(int vertex, double distance);
};