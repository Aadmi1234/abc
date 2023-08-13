#include <bits/stdc++.h>
using namespace std;


class Solution {
  public:
    /*  Function to implement Bellman Ford
    *   edges: vector of vectors which represents the graph
    *   S: source vertex to start traversing graph with
    *   V: number of vertices
    */
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
        vector<int> dist(V, 1e8);
        dist[S] = 0;
        
        // For directed edges only
        // Relaxing the edges (V-1) times
        // Since the edges are not in order
        // Therefore it may happen that the changing edges are always the last edges
        // Hence (V-1) times to check for all the edges

        for(int i=0; i<V-1; ++i) {
            for(auto it : edges) {
                int src = it[0];
                int dst = it[1];
                int wt = it[2];
                
                if(dist[src]!=1e8 && dist[src] + wt < dist[dst]) {
                    dist[dst] = dist[src] + wt;
                }
            }    
        }
        
        // To check for negative cycles
        // If a negative cycle exists then the distances will further decrease
        for(auto it : edges) {
            int src = it[0];
            int dst = it[1];
            int wt = it[2];
            
            // If the distance is decreasing any further
            if(dist[src]!=1e8 && dist[src] + wt < dist[dst]) {
                return {-1};
            }
        }
        
        return dist;
    }
};



int main() {
    int t;
    cin >> t;
    while (t--) {
        int N, m;
        cin >> N >> m;
        vector<vector<int>> edges;

        for (int i = 0; i < m; ++i) {
            vector<int> temp;
            for (int j = 0; j < 3; ++j) {
                int x;
                cin >> x;
                temp.push_back(x);
            }
            edges.push_back(temp);
        }

        int src;
        cin >> src;

        Solution obj;
        vector<int> res = obj.bellman_ford(N, edges, src);

        for (auto x : res) {
            cout << x << " ";
        }
        cout << "\n";
    }
    return 0;
}

