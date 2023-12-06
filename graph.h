#include <iostream>
#include <fstream>
#include <cfloat>
#include <limits>
#include <cmath>
#include <string>

class illegal_exception {
    public: 
        const char* what() const noexcept;
};

class Node {
    public:
        int vertex;
        double weight;
        double d;
        double s;
        double A;
        Node* next;

        Node(int vertex, double weight, double d, double s, double A);
};

class Graph {
    private:
        bool* vertexExists;
        Node** adjacencyList;  
        int maxVertices;
        int numVertices;

        void addEdgeToList(int from, int to, double weight, double d, double s, double A);
        void deleteGraph();
        double calcWeight(double d, double s, double A);
        Node* findEdge(int from, int to);

    public:
        Graph(int maxV);
        ~Graph();

        std::string load(std::string filename);
        std::string addEdge(int from, int to, double d, double s);
        std::string print(int vertex);
        std::string deleteVertex(int vertex);
        std::string traffic(int from, int to, double A);
        std::string update(std::string filename);
        void dijkstra(int startVertex, int endVertex, std::string& outPath, double& outTotalWeight);
};
