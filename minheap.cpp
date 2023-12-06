#include "minheap.h"

MinHeap::MinHeap(int maxCapacity) {
    vertices = new int[maxCapacity];
    distances = new double[maxCapacity];
    indexMap = new int[maxCapacity];
    capacity = maxCapacity;
    size = 0;
}

MinHeap::~MinHeap() {
    delete[] vertices;
    delete[] distances;
    delete[] indexMap;
}

bool MinHeap::isEmpty() {
    return size == 0;
}

void MinHeap::swapNodes(int i, int j) {
    std::swap(vertices[i], vertices[j]);
    std::swap(distances[i], distances[j]);
    indexMap[vertices[i]] = i;
    indexMap[vertices[j]] = j;
}

void MinHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (distances[index] < distances[parent]) {
            swapNodes(index, parent);
            index = parent;
        } else {
            break;
        }
    }
}

void MinHeap::heapifyDown(int index) {
    while (true) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < size && distances[leftChild] < distances[smallest]) {
            smallest = leftChild;
        }

        if (rightChild < size && distances[rightChild] < distances[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) {
            swapNodes(index, smallest);
            index = smallest;
        } else {
            break;
        }
    }
}

void MinHeap::push(int vertex, double distance) {
    if (size < capacity) {
        vertices[size] = vertex;
        distances[size] = distance;
        indexMap[vertex] = size;
        heapifyUp(size);
        size++;
    }
}

int MinHeap::pop() {
    if (!isEmpty()) {
        int minVertex = vertices[0];
        swapNodes(0, size - 1);
        size--;
        heapifyDown(0);
        return minVertex;
    }
    return -1;
}

void MinHeap::decreaseKey(int vertex, double distance) {
    int index = indexMap[vertex];
    if (index < size && distances[index] > distance) {
        distances[index] = distance;
        heapifyUp(index);
    }
}