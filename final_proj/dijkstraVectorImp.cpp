#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

const int INF = numeric_limits<int>::max();

class Network {
private:
    int numberOfNodes;
    vector<char> nameOfNodes;
    vector<vector<int>> graph;

public:
    Network() {
        numberOfNodes = 6;
        nameOfNodes = {'U', 'V', 'W', 'X', 'Y', 'Z'};
        
        graph = vector<vector<int>>(numberOfNodes, vector<int>(numberOfNodes, INF));
        
        for (int i = 0; i < numberOfNodes; i++) {
            graph[i][i] = 0;
        }
        nodeDistance('U', 'V', 2);
        nodeDistance('U', 'X', 1);
        nodeDistance('V', 'W', 3);
        nodeDistance('V', 'X', 2);
        nodeDistance('W', 'Z', 5);
        nodeDistance('W', 'Y', 1);
        nodeDistance('X', 'Y', 1);
        nodeDistance('Y', 'Z', 2);
    }

    Network(const string &filename) {
        parseFile(filename);
    }

    /**
     * Parse a simple text file: 
     * First line: <N> <M> (#nodes and #edges) 
     * Second line: N node-names (single chars, space-separated) 
     * Next M lines: <node1> <node2> <cost> 
     */
    void parseFile(const string &filename) {
        ifstream in(filename);
        if(!in) {
            cerr << "Error opening file: " << filename << "\n";
            exit(1);
        }
        int M;
        in >> numberOfNodes >> M;
        nameOfNodes.resize(numberOfNodes);
        for(int i=0;i<numberOfNodes;i++) {
            in >> nameOfNodes[i];
        }
        graph.assign(numberOfNodes, vector<int>(numberOfNodes, INF));
        for(int i=0;i<numberOfNodes;i++) graph[i][i]=0;

        char a,b;
        int cost;
        for(int e=0;e<M;e++) {
            in >> a >> b >> cost;
            nodeDistance(a,b,cost);
        }
    }

    int nodeIndexInfo(char name) {
        for (int i = 0; i < numberOfNodes; i++) {
            if (nameOfNodes[i] == name) return i;
        }
        return -1;
    }
    
    
    void nodeDistance(char node1, char node2, int cost) {
        int idx1 = nodeIndexInfo(node1);
        int idx2 = nodeIndexInfo(node2);
        
        if (idx1 != -1 && idx2 != -1) {
            graph[idx1][idx2] = cost;
            graph[idx2][idx1] = cost;
        }
    }

    void makeUnidirectional(char from, char to) {
        int fromIdx = nodeIndexInfo(from);
        int toIdx = nodeIndexInfo(to);
        
        if (fromIdx != -1 && toIdx != -1) {
            graph[toIdx][fromIdx] = INF;
        }
    }
    
    void toplogyOutput() {
        cout << "\n=== Network Topology ===\n";
        for (int i = 0; i < numberOfNodes; i++) {
            for (int j = i + 1; j < numberOfNodes; j++) {
                if (graph[i][j] != INF) {
                    cout << nameOfNodes[i] << " -- " << nameOfNodes[j] << ": " << graph[i][j] << "\n";
                }
            }
        }
    }
    
    void dijkstraMethod(char sourceNode) {
        int sourceIdx = nodeIndexInfo(sourceNode);
        if (sourceIdx == -1) return;
        
        vector<int> dist(numberOfNodes, INF);
        vector<int> prev(numberOfNodes, -1);
        vector<bool> visited(numberOfNodes, false);
        
        dist[sourceIdx] = 0;
        
        for (int count = 0; count < numberOfNodes; count++) {
            
            int minDist = INF;
            int minIdx = -1;
            
            for (int i = 0; i < numberOfNodes; i++) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    minIdx = i;
                }
            }
            
            if (minIdx == -1) break;
            
            visited[minIdx] = true;
            for (int i = 0; i < numberOfNodes; i++) {
                if (!visited[i] && graph[minIdx][i] != INF && 
                    dist[minIdx] + graph[minIdx][i] < dist[i]) {
                    dist[i] = dist[minIdx] + graph[minIdx][i];
                    prev[i] = minIdx;
                }
            }
        }
        
        vector<int> nextHop(numberOfNodes);
        for (int i = 0; i < numberOfNodes; i++) {
            if (i == sourceIdx) continue;
            
            if (prev[i] == sourceIdx) {
                nextHop[i] = i; 
            } else if (prev[i] != -1) {
                int current = i;
                while (prev[current] != sourceIdx) {
                    current = prev[current];
                }
                nextHop[i] = current;
            }
        }
        
        cout << "\n=== This is the Dijkstra's Routing Table for Node " << sourceNode << " ===\n";
        cout << "Destination\tNext Hop\tTotal Cost\n";
        cout << "---------------------------------------\n";
        
        for (int i = 0; i < numberOfNodes; i++) {
            if (i != sourceIdx) {
                cout << nameOfNodes[i] << "\t\t";
                if (dist[i] != INF) {
                    cout << nameOfNodes[nextHop[i]] << "\t\t" << dist[i] << "\n";
                } else {
                    cout << "-\t\tINF\n";
                }
            }
        }
    }
    
    void distanceVectorMethod(char sourceNode) {
        int sourceIdx = nodeIndexInfo(sourceNode);
        if (sourceIdx == -1) return;
        
        vector<vector<int>> distTable(numberOfNodes, vector<int>(numberOfNodes, INF));
        vector<vector<int>> viaTable(numberOfNodes, vector<int>(numberOfNodes, -1));
   
        for (int i = 0; i < numberOfNodes; i++) {
            distTable[i][i] = 0;
            for (int j = 0; j < numberOfNodes; j++) {
                if (graph[i][j] != INF) {
                    distTable[i][j] = graph[i][j];
                    viaTable[i][j] = j;
                }
            }
        }
        
        cout << "\n=== This is the Distance Vector Routing Table for Node " << sourceNode << " ===\n";
        cout << "\t";
        for (int j = 0; j < numberOfNodes; j++) {
            if (j != sourceIdx) {
                cout << nameOfNodes[j] << "\t";
            }
        }
        cout << endl;
    
        cout << "Initial\t";
        for (int j = 0; j < numberOfNodes; j++) {
            if (j != sourceIdx) {
                if (distTable[sourceIdx][j] == INF) {
                    cout << "inf, -\t";
                } else {
                    cout << distTable[sourceIdx][j] << ", " << nameOfNodes[viaTable[sourceIdx][j]] << "\t";
                }
            }
        }
        cout << endl;
    
        bool updated;
        int iteration = 1;
        
        do {
            updated = false;
            
    
            for (int i = 0; i < numberOfNodes; i++) {
                for (int j = 0; j < numberOfNodes; j++) {
                    if (i == j) continue;
                
                    for (int k = 0; k < numberOfNodes; k++) {
                        if (graph[i][k] != INF && distTable[k][j] != INF) {
                            int newDist = graph[i][k] + distTable[k][j];
                            if (newDist < distTable[i][j]) {
                                distTable[i][j] = newDist;
                                viaTable[i][j] = k;
                                updated = true;
                            }
                        }
                    }
                }
            }
        
            if (updated) {
                cout << "Iter " << iteration << "\t";
                for (int j = 0; j < numberOfNodes; j++) {
                    if (j != sourceIdx) {
                        if (distTable[sourceIdx][j] == INF) {
                            cout << "inf, -\t";
                        } else {
                            cout << distTable[sourceIdx][j] << ", " << nameOfNodes[viaTable[sourceIdx][j]] << "\t";
                        }
                    }
                }
                cout << endl;
                iteration++;
            }
        } while (updated);
       
        cout << "\nThis is the Final Routing Table for Node " << sourceNode << ":\n";
        cout << "Destination\tNext Hop\tTotal Cost\n";
        cout << "---------------------------------------\n";
        
        for (int j = 0; j < numberOfNodes; j++) {
            if (j != sourceIdx) {
                cout << nameOfNodes[j] << "\t\t";
                if (distTable[sourceIdx][j] != INF) {
                    cout << nameOfNodes[viaTable[sourceIdx][j]] << "\t\t" << distTable[sourceIdx][j] << endl;
                } else {
                    cout << "-\t\tINF" << endl;
                }
            }
        }
    }
};

int main() {
    // Network network;
    Network network("topo.txt"); 
    
    cout << "Network Routing Table Computation\n";
    cout << "=================================\n";
    
    network.toplogyOutput();
    
    cout << "\n*** BIDIRECTIONAL NETWORK ***\n";
    network.dijkstraMethod('W');
    network.dijkstraMethod('Y');
    network.distanceVectorMethod('W');
    network.distanceVectorMethod('Y');
    
    cout << "\n*** AFTER MAKING V→W UNIDIRECTIONAL ***\n";
    network.makeUnidirectional('V', 'W');
    network.toplogyOutput();
    
    network.dijkstraMethod('W');
    network.dijkstraMethod('Y');
    network.distanceVectorMethod('W');
    network.distanceVectorMethod('Y');
    
    return 0;
}
