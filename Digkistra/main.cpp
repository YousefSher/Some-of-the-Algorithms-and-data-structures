// GROUP:   X
// ID:      XXXXXXXX
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name:    XXX MY FULL NAME

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <cfloat>
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
        if (n == sz) {
            sz *= 2;
            Value* tempArr = new Value[sz];
            for (int i = 0; i < n; i++) {
                tempArr[i] = arr[i];
            }
            delete[] arr;
            arr = tempArr;
        }
        arr[n] = v;
        n++;
	}

	void RemoveLast(){
        n--;
	}
	Value& operator[](int i){
        return arr[i];
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Elem>
struct Heap
{
    int* pos; // pos[v]=i where a[i].v=v, otherwise pos[v]=-1
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);
    void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n){ // n is required to allocate and initialize pos[]
        pos = new int [n];
	    IsBefore = _IsBefore;
	    a.Initialize();
	    for(int i = 0; i < n; i ++){
            pos[i] = -1;
	    }
	}
	void Destroy(){
        a.Destroy();
        delete [] pos;
	}
	int Child(int i){
	    int left = 2*i+1;
	    int right = 2*i+2;
	    if(left >= a.n){
            return -1;
	    }
	    if(right>= a.n){
            return left;
	    }
	    return IsBefore(a[left], a[right])?left:right;
	}
	int Parent(int i){
        return (i - 1)/2;
	}
	void MoveUp(int ind){
        if(ind > 0 && IsBefore(a[ind], a[Parent(ind)])){
            swap(a[ind], a[Parent(ind)]);
            swap(pos[a[ind].v], pos[a[Parent(ind)].v]);
            MoveUp(Parent(ind));
        }
	}
	void MoveDown(int ind){
	    int childIndex = Child(ind);
        if(childIndex != -1 && IsBefore(a[childIndex], a[ind])){
            swap(a[ind], a[childIndex]);
            swap(pos[a[ind].v], pos[a[Child(ind)].v]);
            MoveDown(childIndex);
        }
	}
	void Add(Elem e){
        a.AddLast(e);
        int i = a.n - 1;
        pos[e.v] = a.n - 1;
        MoveUp(i);
	}
	Elem GetFirst(){
        return a[0];
	}
	Elem RetrieveFirst(){
        Elem firstElem = a[0];
        pos[firstElem.v] = -1;
        a[0] = a[a.n - 1];
        pos[a[0].v] = 0;
        a.RemoveLast();
        if (a.n > 0) MoveDown(0);
        return firstElem;
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

bool IsBefore(Edge& a, Edge& b)
{
	return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int casenum;
    cin>>casenum;
    for(int caseNum = 1; caseNum <= casenum; caseNum++) {
        int n, m, s, t;
        cin>>n>>m>>s>>t;
        Heap<Edge> heap;
        heap.Initialize(IsBefore, n);
        Graph graph;
        graph.Initialize(n);
        for(int i = 0; i < m; i++){
            int x, y;
            double w;
            cin >> x >> y >> w;
            graph.nodes[x].adj.AddLast({y, w});
            graph.nodes[y].adj.AddLast({x, w});
        }
        double d[n];
        int p[n];
        bool visited[n];
        for (int i = 0; i < n; i++) {
            d[i] = DBL_MAX;
            p[i] = -1;
            visited[i] = false;
        }
        d[s] = 0;
        p[s] = s;
        heap.Add({s, 0.0});
        while (heap.a.n > 0) {
            Edge chosen = heap.RetrieveFirst();
            int source = chosen.v;
            if (source == t) break;
            if (visited[source]) continue;
            visited[source] = true;
            for (int j = 0; j < graph.nodes[source].adj.n; j++) {
                Edge e = graph.nodes[source].adj[j];
                if (!visited[e.v] && d[source] != DBL_MAX && d[source] + e.w < d[e.v]) {
                    d[e.v] = d[source] + e.w;
                    p[e.v] = source;
                    heap.Add({e.v, d[e.v]});
                }
            }
        }
        graph.Destroy();
        heap.Destroy();
        if(d[t]==DBL_MAX) {
            cout<<"Case #"<<caseNum<<": unreachable"<<endl;
        }else{
            cout<<"Case #"<<caseNum<<": "<<d[t]<<endl;
        }
    }
    return 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
