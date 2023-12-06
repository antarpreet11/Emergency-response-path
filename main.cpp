#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.h"
#include "minheap.h"

int main() {
    Graph graph(500000);

    std::string line;
    
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "LOAD") {
            std::string filename;
            iss >> filename;

            std::cout << graph.load(filename) << std::endl;
        } else if (command == "INSERT") {
            int a, b;
            double d, s;
            iss >> a >> b >> d >> s;

            std::cout << graph.addEdge(a, b, d, s) << std::endl;

        } else if (command == "PRINT") {
            int a;
            iss >> a;

            std::cout << graph.print(a) << std::endl;

        } else if (command == "DELETE") {
            int a;
            iss >> a;

            std::cout << graph.deleteVertex(a) << std::endl;

        } else if (command == "PATH") {
            int a, b;
            iss >> a >> b;

            std::string path;
            double totalWeight;

            graph.dijkstra(a, b, path, totalWeight);

            if (path == "failure" || path == "illegal argument") {
                std::cout << path << std::endl;
            } else {
                std::cout << path << std::endl;
            }
        } else if (command == "TRAFFIC") {
            int a, b;
            double A;
            iss >> a >> b >> A;

            std::cout << graph.traffic(a, b, A) << std::endl;

        } else if (command == "UPDATE") {
            
            std::string filename;
            iss >> filename;
            
            std::cout << graph.update(filename) << std::endl;

        } else if (command == "LOWEST") {
            int a, b;
            iss >> a >> b;

            std::string path;
            double totalWeight;

            graph.dijkstra(a, b, path, totalWeight);

            if (path == "failure" || path == "illegal argument") {
                std::cout << path << std::endl;
            } else {
                std::cout << "lowest is " << std::to_string(totalWeight) << std::endl;
            }
        } else if (command == "END") {
            break;  
        } else {
            std::cout << "Invalid command\n";
        }
    }
}
