#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

class Graph
{
    int V;
    vector<vector<int>> adjList;

public:
    Graph(int V) : V(V), adjList(V) {}

    void addEdge(int i, int j)
    {
        adjList[i].push_back(j);
        adjList[j].push_back(i);
    }

    void DFS(int startVertex) //Time : O(V+E), space: O(V){stack mdhe vertex cha track thevto}
    {
        vector<bool> visited(V, false);
        DFSUtil(startVertex,visited);
    }

    void DFSUtil(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout<<v<<" ";

        for(int i = 0; i < adjList[v].size();++i)
        {
            int n = adjList[v][i];
            if(!visited[n])
            {
                DFSUtil(n, visited);
            }
        }
    } 

    void parallelDFS(int startVertex)//Time : O(V/P +E/P), space : O(V)+threads
    {
        vector<bool> visited(V, false);
        parallelDFSUtil(startVertex,visited);
    }

    void parallelDFSUtil(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout<<v<<" ";

        #pragma omp parallel for
        for(int i = 0; i < adjList[v].size();++i)
        {
            int n = adjList[v][i];
            if(!visited[n])
            {
                parallelDFSUtil(n, visited);
            }
        }
    }

    void BFS(int startVertex)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[startVertex]=true;
        q.push(startVertex);
        while(!q.empty())
        {
            int v = q.front();
            q.pop();
            cout<<v<<" ";

            for(int i = 0; i < adjList[v].size();++i)
            {
                int n = adjList[v][i];
                if(!visited[n])
                {
                    visited[n]=true;
                    q.push(n);
                }
            }
        }
    }

    void parallelBFS(int startVertex)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[startVertex]=true;
        q.push(startVertex);
        while(!q.empty())
        {
            int v = q.front();
            q.pop();
            cout<<v<<" ";

            #pragma omp parallel for
            for(int i = 0; i < adjList[v].size();++i)
            {
                int n = adjList[v][i];
                if(!visited[n])
                {
                    visited[n]=true;
                    q.push(n);
                }
            }
        }
    }
};

int main()
{
    int vertices;
    double startTime,endTime;
    cout<<"\nEnter total number of vertices : ";
    cin>>vertices;
    Graph g(vertices);
    int edges;
    cout<<"\nEnter total number of edges : ";
    cin>>edges;
    for(int i = 0; i < edges; i++)
    {
        int v1, v2;
        cout<<"\nEnter vertex v1 and v2 such that v1 --- > v2 : ";
        cin>>v1>>v2;
        g.addEdge(v1,v2);
    }
    int start;
    cout<<"\nEnter start vertex : ";
    cin>>start;
    startTime=omp_get_wtime();
    cout<<"\nSequential DFS: ";
    g.DFS(start);
    cout<<endl;
    endTime=omp_get_wtime();
    cout<<"\nTime taken by sequentail DFS : "<<endTime-startTime;
    startTime=omp_get_wtime();
    cout<<"\nParallel DFS: ";
    g.parallelDFS(start);
    cout<<endl;
    endTime=omp_get_wtime();
    cout<<"\nTime taken by parallel DFS : "<<endTime-startTime;
    startTime=omp_get_wtime();
    cout<<"\nSequential BFS: ";
    g.BFS(start);
    cout<<endl;
    endTime=omp_get_wtime();
    cout<<"\nTime taken by sequentail BFS : "<<endTime-startTime;
    startTime=omp_get_wtime();
    cout<<"\nParallel BFS: ";
    g.parallelBFS(start);
    cout<<endl;
    endTime=omp_get_wtime();
    cout<<"\nTime taken by parallel BFS : "<<endTime-startTime;
    return 0;
}

/*
        0 -------->1
        |         / \
        |        /   \
        |       /     \
        v       v       v
        2 ----> 3       4
        |      |
        |      |
        v      v
        5      6
    */

/*
OpenMp :
1. Open Multi-Processing, is an application programming interface (API) that supports multi-platform shared-memory parallel programming in C, C++, and Fortran.
2.uses compiler directives to specify which parts of the code should be parallelized. Eg : #pragma omp parallel for
3.offers synchronization constructs such as critical sections (omp critical), locks (omp lock), and barriers (omp barrier) to manage dependencies and prevent race conditions.
4.omp_get_wtime() provides the elapsed wall-clock time in seconds
*/
/*
Parallel programming can take more time than sequential programming due to overhead from managing threads, synchronization, and communication between threads. the better approach depends on the problem size and complexity; parallel programming is usually better for large, complex problems, while sequential programming can be more efficient for small, simple problems.
*/
