#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>
#include <unordered_set>
#include <iostream>

using namespace std;

class Graph {
private:
    int V;  // Number of vertices
    vector<vector<int>> adj;  // Adjacency list
    
    void DFSUtil(int v, unordered_set<int>& visited, vector<int>& component) {
        visited.insert(v);
        component.push_back(v);
        
        for (int neighbor : adj[v]) {
            if (visited.find(neighbor) == visited.end()) {
                DFSUtil(neighbor, visited, component);
            }
        }
    }
    
public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }
    
    void addEdge(int u, int v) {
        if (u < V && v < V && u >= 0 && v >= 0) {
            adj[u].push_back(v);
            adj[v].push_back(u);  // Undirected graph
        }
    }
    
    vector<int> BFS(int start) {
        vector<int> result;
        if (start < 0 || start >= V) return result;
        
        unordered_set<int> visited;
        queue<int> q;
        
        q.push(start);
        visited.insert(start);
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            result.push_back(current);
            
            for (int neighbor : adj[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }
        
        return result;
    }
    
    vector<vector<int>> getConnectedComponents() {
        vector<vector<int>> components;
        unordered_set<int> visited;
        
        for (int i = 0; i < V; i++) {
            if (visited.find(i) == visited.end()) {
                vector<int> component;
                DFSUtil(i, visited, component);
                if (!component.empty()) {
                    components.push_back(component);
                }
            }
        }
        
        return components;
    }
    
    int getVertexCount() const { return V; }
    
    int getEdgeCount() const {
        int count = 0;
        for (int i = 0; i < V; i++) {
            count += adj[i].size();
        }
        return count / 2;  // Undirected graph
    }
    
    vector<int> getNeighbors(int v) {
        if (v >= 0 && v < V) {
            return adj[v];
        }
        return vector<int>();
    }
};

#endif
