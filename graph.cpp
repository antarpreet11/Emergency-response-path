#include "graph.h"
#include "minheap.h"

const char* illegal_exception::what() const noexcept {
    return "illegal argument";
}

Node::Node(int vertex, double weight, double d, double s, double A) {
    this->vertex = vertex;
    this->weight = weight;
    this->d = d;
    this->s = s;
    this->A = A;
    this->next = nullptr;
}\

void Graph::addEdgeToList(int from, int to, double weight, double d, double s, double A) {
    Node* edge = findEdge(from, to);

    if (edge != nullptr) {
        edge->d = d;
        edge->s = s;
        edge->A = A;
        edge->weight = weight;
        return;
    }

    if (!vertexExists[from - 1]) {
        adjacencyList[from - 1] = new Node(to, weight, d, s, A);
        vertexExists[from - 1] = true;
        numVertices++;
    } else {
        Node* newEdge = new Node(to, weight, d, s, A);
        newEdge->next = adjacencyList[from - 1];
        adjacencyList[from - 1] = newEdge;
    }
}

void Graph::deleteGraph() {
    for (int i = 0; i < maxVertices; ++i) {
        Node* current = adjacencyList[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        adjacencyList[i] = nullptr;
    }
    delete[] adjacencyList;
    delete[] vertexExists;
}

double Graph::calcWeight(double d, double s, double A) {
    if (A == 0) {
        return DBL_MAX;
    }

    return d / (s * A);
}

Node* Graph::findEdge(int from, int to) {

    if(!vertexExists[from - 1] || !vertexExists[to - 1]) {
        return nullptr;
    }

    Node* current = adjacencyList[from - 1];

    while (current) {
        if (current->vertex == to) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

Graph::Graph(int maxV) {
    maxVertices = maxV;
    adjacencyList = new Node*[maxV];
    vertexExists = new bool[maxV]; 
    numVertices = 0;

    for (int i = 0; i < maxV; ++i) {
        adjacencyList[i] = nullptr;
        vertexExists[i] = false;
    }
}

Graph::~Graph() {
    deleteGraph();
}

std::string Graph::load(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "failure";
    }

    int a, b;
    double d, s;

    while (file >> a >> b >> d >> s) {
        addEdge(a, b, d, s);
    }

    file.close();

    return "success";
}

std::string Graph::addEdge(int from, int to, double d, double s) {
    try {
        if(from < 1 || from > maxVertices || to < 1 || to > maxVertices || d <= 0 || s <= 0) {
            throw illegal_exception();
        }

        double weight = calcWeight(d, s, 1);

        addEdgeToList(from, to, weight, d, s, 1);
        addEdgeToList(to, from, weight, d, s, 1);

        return "success";
    } catch (const illegal_exception& e) {
        return std::string(e.what());
    }
}

std::string Graph::print(int vertex) {
    try {
        if (vertex < 1 || vertex > maxVertices) {
            throw illegal_exception();
        }

        if (!vertexExists[vertex - 1]) {
            return "failure";
        }

        std::string output = "";
        Node* current = adjacencyList[vertex - 1];
        while (current) {
            output += std::to_string(current->vertex) + " ";
            current = current->next;
        }

        return output;
    } catch (const illegal_exception& e) {
        return std::string(e.what());
    }
}

std::string Graph::deleteVertex(int vertex) {
    try {
        if (vertex < 1 || vertex > maxVertices) {
            throw illegal_exception();
        }

        if (!vertexExists[vertex - 1]) {
            return "failure";
        }

        Node* current = adjacencyList[vertex - 1];
        while (current != nullptr) {
            int adj = current->vertex;

            Node* temp = adjacencyList[adj - 1];
            Node* prev = nullptr;

            /*
                CITATION:

                Chat GPT was used to fix some issues with the while loop below
            */
            while (temp != nullptr) {
                if (temp->vertex == vertex) {
                    if (prev == nullptr) {
                        adjacencyList[adj - 1] = temp->next;
                    } else {
                        prev->next = temp->next;
                    }
                    delete temp;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }

            Node* nextEdge = current->next;
            delete current;
            current = nextEdge;
        }

        adjacencyList[vertex - 1] = nullptr;
        vertexExists[vertex - 1] = false;
        numVertices--;

        return "success";

    } catch (const illegal_exception& e) {
        return std::string(e.what());
    }
}

std::string Graph::traffic(int from, int to, double A) {
    try {
        if (from < 1 || from > maxVertices || to < 1 || to > maxVertices) {
            throw illegal_exception();
        }

        if (vertexExists[from - 1] && vertexExists[to - 1]) {
            Node* edge = findEdge(from, to);
            if (edge) {
                edge->A = A;
                edge->weight = calcWeight(edge->d, edge->s, A);

                Node* reverseEdge = findEdge(to, from);
                reverseEdge->A = A;
                reverseEdge->weight = calcWeight(reverseEdge->d, reverseEdge->s, A);
                return "success";
            } else {
                return "failure"; 
            } 
        }

        return "failure";
    } catch (const illegal_exception& e) {
        return std::string(e.what());
    }
}

std::string Graph::update(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return "failure";
    }

    int a, b;
    double A;
    bool update = false;

    while (file >> a >> b >> A) {
        std::string result = traffic(a, b, A);

        if (result == "success") {
            update = true;
        }
    }

    file.close();
    
    return update ? "success" : "failure";
}

void Graph::dijkstra(int startVertex, int endVertex, std::string& outPath, double& outTotalWeight) {
    try {
        if (startVertex < 1 || startVertex > maxVertices || endVertex < 1 || endVertex > maxVertices) {
            throw illegal_exception();
        }

        if (!vertexExists[startVertex - 1] || !vertexExists[endVertex - 1] || numVertices == 0) {
            outPath = "failure";
            outTotalWeight = DBL_MAX;
            return;
        }

        MinHeap minHeap(numVertices);
        double* dist = new double[numVertices];
        int* prev = new int[numVertices];
        bool* visited = new bool[numVertices];

        for (int i = 0; i < numVertices; ++i) {
            dist[i] = DBL_MAX;
            prev[i] = -1;
            visited[i] = false;
        }

        dist[startVertex - 1] = 0;
        minHeap.push(startVertex, 0);

        while (!minHeap.isEmpty()) {
            int currentVertex = minHeap.pop();

            if (visited[currentVertex - 1]) {
                continue;
            }

            visited[currentVertex - 1] = true;

            Node* vertex = adjacencyList[currentVertex - 1];
            while (vertex) {
                int neighbor = vertex->vertex;
                double newDistance = dist[currentVertex - 1] + vertex->weight;

                if (!visited[neighbor - 1] && newDistance < dist[neighbor - 1]) {
                    dist[neighbor - 1] = newDistance;
                    prev[neighbor - 1] = currentVertex;
                    minHeap.push(neighbor, newDistance);
                } 

                vertex = vertex->next;
            }
        }

        if (dist[endVertex - 1] == DBL_MAX) {
            outPath = "failure";
            outTotalWeight = DBL_MAX;
            delete[] dist;
            delete[] prev;
            delete[] visited;
            return;
        }

        int current = endVertex;
        while (current != -1) {
            outPath = std::to_string(current) + " " + outPath;
            current = prev[current - 1];
        }

        outTotalWeight = dist[endVertex - 1];

        delete[] dist;
        delete[] prev;
        delete[] visited;
    } catch (const illegal_exception& e) {
        outPath = std::string(e.what());
        outTotalWeight = DBL_MAX;
        return;
    }
}
