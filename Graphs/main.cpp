// GROUP:   1
// ID:      20226117
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Yousef Sherif Mohamad Nokod

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
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

struct Node
{
	Array<int> adj;

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

template <class Type>
struct Queue
{
	int f, n;
	Type* elems;

	void Initialize(int size){
	    f = 0;
	    n = 0;
        elems = new Type [size];
        return;
	}
	void Destroy(){
        delete [] elems;
        return;
	}
	void Add(Type t){
        elems[n] = t;
        n++;
        return;
	}
	Type Pop(){
        if(f < n){
            return elems[f++];
        }
	}
	Type Peek(){
        if(f < n){
            return elems[f];
        }
	}
	int Num(){
        return n-f;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void traversal(const Graph& graph, const int startNode, int &max_num, int &day){
    Queue<int> q;
    q.Initialize(graph.n);
    int level[graph.n];
    bool visited[graph.n];
    int level_counter[graph.n];
    for(int i = 0; i < graph.n; i++){
        level_counter[i] = 0;
        level[i] = -1;
        visited[i] = false;
    }
    q.Add(startNode);
    visited[startNode] = true;
    level[startNode] = 0;
    while(q.Num() > 0){
        int a = q.Pop();
        for(int i = 0;i<graph.nodes[a].adj.n; i++){
            if(!visited[graph.nodes[a].adj[i]]){
                visited[graph.nodes[a].adj[i]] = true;
                q.Add(graph.nodes[a].adj[i]);
                level[graph.nodes[a].adj[i]] = level[a] + 1;
                level_counter[level[graph.nodes[a].adj[i]]]++;
            }
        }
    }
    max_num = 0;
    day = 0;
    for(int i = 0; i < graph.n; i++){
        if(level_counter[i] > max_num){
            max_num = level_counter[i];
            day = i;
        }
    }
    q.Destroy();
    return;
}
int main()
{
    int n, numFr, friend_;
    cin>>n;
    Graph graph;
    graph.Initialize(n);
    for(int i = 0; i < n; i++){
            cin>>numFr;
        for(int j = 0; j < numFr; j++){
                cin>>friend_;
            graph.nodes[i].adj.AddLast(friend_);
        }
    }
    int t;
    cin>>t;
    for(int i = 0; i < t; i++){
            int startNode, max_num, day;
        cin>>startNode;
        traversal(graph, startNode, max_num, day);
        if(max_num == 0){
            cout<<max_num<<endl;
        }else{
            cout<<max_num<<" "<<day<<endl;
        }
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
