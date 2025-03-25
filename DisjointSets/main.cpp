// GROUP:   1
// ID:      20226117
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    Yousef Sherif Mohamad Nokod

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
            parent[parentJ] = parentI;
            num_nodes[parentI] += num_nodes[parentJ];
            return true;
        }
        return false;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getMaxOfArray(int arr[], int n){
    int max_ = -100;
    for(int i = 0; i < n; i++){
        if(max_ < arr[i])
            max_ = arr[i];
    }
    return max_;
}
int main()
{
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin>>n>>m;
        DisjointSets set1;
        set1.Initialize(n);
        int a, b;
        bool flag;
        for(int i = 0; i < m; i++){
            cin>>a>>b;
            flag = set1.Union(a - 1, b - 1);
        }
        int max_ = getMaxOfArray(set1.num_nodes, set1.n);
        cout<<max_<<endl;
        set1.Destroy();
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
