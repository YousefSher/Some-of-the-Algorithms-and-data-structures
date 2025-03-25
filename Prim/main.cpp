// GROUP:   X
// ID:      XXXXXXXX
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name:    XXX MY FULL NAME

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;

	void Initialize(){
        n = 0;
        sz = 5;
        arr = new Value [sz];
    }
	void Destroy(){
        delete [] arr;
	}
	void AddLast(Value v){
        arr[n] = v;
        n++;
        if(n == sz){
           Value* tempArr = arr;
           sz = sz * 2;
           arr = new Value [sz];
           for(int i = 0; i < n; i++){
                arr[i] = tempArr[i];
           }
           delete [] tempArr;
        }
	}
	void RemoveLast(){
        n--;
	}
	Value& operator[](int i){
        return arr[i];
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int		v;
	double	w;
};

struct Node
{
    int x,y;
	Array<Edge> adj;

	void Initialize(){
        adj.Initialize();
        return;
	}
	void Destroy(){
        adj.Destroy();
        return;
	}
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n){
        n = _n;
        nodes = new Node [_n];
        for(int i = 0; i < n; i++){
            nodes[i].Initialize();
        }
        return;
	}
	void Destroy(){
	    for(int i = 0; i < n; i++){
            nodes[i].Destroy();
        }
        delete [] nodes;
        return;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Sqrt(double v, int n=100){
    if(v == 0)return 0;
    double a = 0, b = v;
    double m;
    for(int i = 0; i < n; i ++){
        m = (a + b)/2.0;
        if(m*m > v){
            b = m;
        }else{
            a = m;
        }
    }
    return m;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    int n, scenario = 1;
    while (cin >> n, n != 0) {
        Graph graph;
        graph.Initialize(n);
        for (int i = 0; i < n; i++) {
            cin >> graph.nodes[i].x >> graph.nodes[i].y;
        }
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double w = Sqrt((graph.nodes[i].x - graph.nodes[j].x) * (graph.nodes[i].x - graph.nodes[j].x) + (graph.nodes[i].y - graph.nodes[j].y) * (graph.nodes[i].y - graph.nodes[j].y));
                graph.nodes[i].adj.AddLast({j, w});
                graph.nodes[j].adj.AddLast({i, w});
            }
        }
        double* d = new double[n];
        bool* visited = new bool[n]();
        for (int i = 0; i < n; i++) d[i] = 1e9;

        d[0] = 0;
        double result = 0;

        for (int i = 0; i < n; i++) {
            int ver = -1;
            for (int j = 0; j < n; j++) {
                if (!visited[j] && (ver == -1 || d[j] < d[ver]))
                    ver = j;
            }

            visited[ver] = true;
            if (ver == 1) {
                result = d[ver];
                break;
            }
            if (ver == -1) {
                break;
            }
            for (int j = 0; j < graph.nodes[ver].adj.n; j++) {
                int v = graph.nodes[ver].adj[j].v;
                double w = graph.nodes[ver].adj[j].w;
                if (!visited[v]) {
                    double maxd = d[ver];
                    if (d[ver] < w) maxd = w;
                    if (maxd < d[v]) {
                        d[v] = maxd;
                    }
                }
            }
        }
        cout << "Scenario #" << scenario++ << endl;
        cout << "Frog Distance = " << fixed << setprecision(3) << result << endl;
        cout << endl;
        delete[] d;
        delete[] visited;
        graph.Destroy();
    }
}
