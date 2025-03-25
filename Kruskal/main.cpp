// GROUP:   1
// ID:      20226117
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Yousef Sherif Mohamad

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
	int n;
	int* parent;
	int* num_nodes;

	void Initialize(int _n){
	    n = _n;
        parent = new int [n];
        num_nodes = new int [n];
        for(int i = 0; i < n; i++){
            parent[i] = -1;
            num_nodes[i] = 1;
        }
	}
	void Destroy(){
        delete [] parent;
        delete [] num_nodes;
	}
	int Find(int i){
        while(parent[i] != -1){
            i = parent[i];
        }
        return i;
	}
	bool Union(int i, int j){
        int parentI = Find(i);
        int parentJ = Find(j);
        if(parentI != parentJ || parentI == -1  || parentJ == -1){
            if(num_nodes[parentI] >= num_nodes[parentJ]){
                parent[parentJ] = parentI;
                num_nodes[parentI] += num_nodes[parentJ];
            }else{
                parent[parentI] = parentJ;
                num_nodes[parentJ] += num_nodes[parentI];
            }
            return true;
        }
        return false;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
    int mid = n / 2;
    Type * left = new Type [mid];
    Type * right = new Type [n - mid];
    for(int i = 0; i < mid; i++){
        left[i] = a[i];
    }
    for(int i = 0; i < n - mid; i++){
        right[i] = a[i + mid];
    }
    int i = 0, j = 0;
    while(i < mid && j < (n - mid)){
        if(IsBefore(left[i], right[j])){
            a[i+j] = left[i];
            i++;
        }else{
            a[i+j] = right[j];
            j++;
        }
    }
    while(i < mid){
        a[i+j] = left[i];
        i++;
    }
    while(j < (n - mid)){
        a[i+j] = right[j];
        j++;
    }
    delete [] right;
    delete [] left;
    return;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
    if(n > 1){
        int c = n/2;
        MergeSort(a, c, IsBefore);
        MergeSort(a+c, n - c, IsBefore);
        Merge(a, n, IsBefore);
    }else{
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int u, v;
	int w;
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
	return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    while(true){
        int m, n;
        cin>>m>>n;
        if(m == 0 && n == 0)break;
        DisjointSets sets;
        sets.Initialize(m);
        int max_sum = 0, min_sum = 0;
        Edge *arr = new Edge [n];
        for(int i = 0; i < n; i++){
            int a, b, w;
            cin>>a>>b>>w;
            arr[i].u = a;
            arr[i].v = b;
            arr[i].w = w;
            max_sum += w;

        }
        MergeSort(arr, n, IsBeforeEdge);
        for(int i = 0; i < n; i++){
            if(sets.Union(arr[i].u, arr[i].v)){
                min_sum+=arr[i].w;
            }
        }
        cout<<max_sum - min_sum<<endl;
        delete [] arr;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
