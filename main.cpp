#include <iostream>
#include <unordered_map>
#include <queue>
#include <limits>

// Define the graph structure
using Graph = std::unordered_map<char, std::unordered_map<char, int>>;

// Function to find the shortest distance between two cities
int findShortestDistance(const Graph& graph, char startCity, char endCity) {
    std::unordered_map<char, int> distances;
    for (const auto& pair : graph) {
        distances[pair.first] = std::numeric_limits<int>::max();
    }

    distances[startCity] = 0;
    std::priority_queue<std::pair<int, char>, std::vector<std::pair<int, char>>, std::greater<std::pair<int, char>>> pq;
    pq.push({ 0, startCity });

    while (!pq.empty()) {
        char currentCity = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        if (currentCity == endCity) {
            return currentDistance;
        }

        if (currentDistance > distances[currentCity]) {
            continue;
        }

        for (const auto& neighbor : graph.at(currentCity)) {
            char neighborCity = neighbor.first;
            int distance = neighbor.second;

            if (currentDistance + distance < distances[neighborCity]) {
                distances[neighborCity] = currentDistance + distance;
                pq.push({ distances[neighborCity], neighborCity });
            }
        }
    }

    return -1; // If no path is found
}

int main() {
    // Create the graph representing the road network
    Graph roadNetwork = {
        {'A', { {'B', 10}, {'C', 15}, {'D', 20} }},
        {'B', { {'A', 10}, {'C', 25}, {'E', 30} }},
        {'C', { {'A', 15}, {'B', 25}, {'D', 35} }},
        {'D', { {'A', 20}, {'C', 35}, {'E', 40} }},
        {'E', { {'B', 30}, {'D', 40} }}
    };

    // Find the shortest distance between two cities
    char startCity = 'B';
    char endCity = 'D';
    int shortestDistance = findShortestDistance(roadNetwork, startCity, endCity);

    if (shortestDistance == -1) {
        std::cout << "No path found between cities " << startCity << " and " << endCity << std::endl;
    } else {
        std::cout << "Shortest distance between cities " << startCity << " and " << endCity << " is: " << shortestDistance << std::endl;
    }

    return 0;
}
