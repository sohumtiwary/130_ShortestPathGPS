#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

const int INF = numeric_limits<int>::max();

class GPSNetwork {
private:
    int numberOfNodes;
    vector<string> cityNames;
    vector<vector<int>> adjacencyMatrix;

    int getCityIndex(const string &city) const {
        for (int i = 0; i < numberOfNodes; i++) {
            if (cityNames[i] == city) return i;
        }
        return -1;
    }

public:
    GPSNetwork() {
        numberOfNodes = 6;
        cityNames = {"Aldoria", "Bramhelm", "Celestia", "Drakmoor", "Eldoria", "Frostfall"};
        adjacencyMatrix.assign(numberOfNodes, vector<int>(numberOfNodes, INF));
        for (int i = 0; i < numberOfNodes; i++)
            adjacencyMatrix[i][i] = 0;

        addRoad("Aldoria", "Bramhelm", 10);
        addRoad("Aldoria", "Drakmoor", 8);
        addRoad("Bramhelm", "Celestia", 15);
        addRoad("Bramhelm", "Drakmoor", 12);
        addRoad("Celestia", "Frostfall", 20);
        addRoad("Celestia", "Eldoria", 5);
        addRoad("Drakmoor", "Eldoria", 7);
        addRoad("Eldoria", "Frostfall", 9);
    }

    GPSNetwork(const string &filename) {
        cout << "Importing map data from: " << filename << "\n";
        parseFile(filename);
    }

    void parseFile(const string &filename) {
        ifstream in(filename);
        if (!in) {
            cerr << "Error opening file: " << filename << "\n";
            exit(1);
        }
        int M;
        in >> numberOfNodes >> M;
        cityNames.resize(numberOfNodes);
        for (int i = 0; i < numberOfNodes; i++) {
            in >> cityNames[i];
        }
        adjacencyMatrix.assign(numberOfNodes, vector<int>(numberOfNodes, INF));
        for (int i = 0; i < numberOfNodes; i++)
            adjacencyMatrix[i][i] = 0;
        string c1, c2;
        int dist;
        for (int e = 0; e < M; e++) {
            in >> c1 >> c2 >> dist;
            addRoad(c1, c2, dist);
        }
    }

    void addRoad(const string &cityA, const string &cityB, int distance) {
        int i = getCityIndex(cityA);
        int j = getCityIndex(cityB);
        if (i >= 0 && j >= 0) {
            adjacencyMatrix[i][j] = distance;
            adjacencyMatrix[j][i] = distance;
        }
    }

    void makeOneWay(const string &fromCity, const string &toCity) {
        int i = getCityIndex(fromCity);
        int j = getCityIndex(toCity);
        if (i >= 0 && j >= 0) {
            adjacencyMatrix[j][i] = INF;
        }
    }

    void displayMap() const {
        cout << "\n=== City Road Map ===\n";
        for (int i = 0; i < numberOfNodes; i++) {
            for (int j = 0; j < numberOfNodes; j++) {
                if (adjacencyMatrix[i][j] != INF && i != j) {
                    cout << cityNames[i] << " <-> " << cityNames[j]
                         << ": " << adjacencyMatrix[i][j] << " mi\n";
                }
            }
        }
    }

    void computeRoutingTable(const string &sourceCity) const {
        int src = getCityIndex(sourceCity);
        if (src < 0) {
            cerr << "Error: source city not found: " << sourceCity << "\n";
            return;
        }
        vector<int> dist(numberOfNodes, INF), prev(numberOfNodes, -1);
        vector<bool> visited(numberOfNodes, false);
        dist[src] = 0;
        for (int cnt = 0; cnt < numberOfNodes; cnt++) {
            int u = -1, best = INF;
            for (int i = 0; i < numberOfNodes; i++) {
                if (!visited[i] && dist[i] < best) {
                    best = dist[i]; u = i;
                }
            }
            if (u < 0) break;
            visited[u] = true;
            for (int v = 0; v < numberOfNodes; v++) {
                if (!visited[v] && adjacencyMatrix[u][v] != INF &&
                    dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjacencyMatrix[u][v];
                    prev[v] = u;
                }
            }
        }
        cout << "\n=== Dijkstra Routing Table from " << sourceCity << " ===\n";
        cout << "Destination    Next Hop    Distance(mi)\n";
        cout << "-------------------------------------\n";
        for (int i = 0; i < numberOfNodes; i++) {
            if (i == src) continue;
            cout << setw(15) << cityNames[i];
            if (dist[i] == INF) {
                cout << setw(12) << "-" << setw(14) << "INF" << "\n";
            } else {
                int hop = i;
                while (prev[hop] != src) hop = prev[hop];
                cout << setw(12) << cityNames[hop] << setw(12) << dist[i] << "\n";
            }
        }
    }

    void computeShortestPath(const string &startCity, const string &endCity) const {
        int src = getCityIndex(startCity);
        int dst = getCityIndex(endCity);
        if (src < 0 || dst < 0) {
            cerr << "Error: invalid city name(s).\n";
            return;
        }
        vector<int> dist(numberOfNodes, INF), prev(numberOfNodes, -1);
        vector<bool> visited(numberOfNodes, false);
        dist[src] = 0;
        for (int cnt = 0; cnt < numberOfNodes; cnt++) {
            int u = -1, best = INF;
            for (int i = 0; i < numberOfNodes; i++) {
                if (!visited[i] && dist[i] < best) {
                    best = dist[i]; u = i;
                }
            }
            if (u < 0) break;
            visited[u] = true;
            for (int v = 0; v < numberOfNodes; v++) {
                if (!visited[v] && adjacencyMatrix[u][v] != INF &&
                    dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjacencyMatrix[u][v];
                    prev[v] = u;
                }
            }
        }
        if (dist[dst] == INF) {
            cout << "No route found from " << startCity << " to " << endCity << ".\n";
            return;
        }
        vector<int> path;
        for (int at = dst; at != -1; at = prev[at]) path.push_back(at);
        reverse(path.begin(), path.end());
        cout << "\nShortest path from " << startCity << " to " << endCity << ":\n";
        for (size_t i = 0; i < path.size(); i++) {
            cout << cityNames[path[i]];
            if (i + 1 < path.size()) cout << " -> ";
        }
        cout << " (" << dist[dst] << " mi)\n";
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <sourceCity> <destCity>\n";
        return 1;
    }
    string sourceCity = argv[1];
    string destCity = argv[2];

    GPSNetwork map("gps2.txt");
    map.displayMap();
    map.computeRoutingTable(sourceCity);
    map.computeShortestPath(sourceCity, destCity);

    return 0;
}
