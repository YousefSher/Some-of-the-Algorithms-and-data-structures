// GROUP:   X
// ID:      XXXXXXXX
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    XXX MY FULL NAME

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
	int v;
	int w;
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
int Knapsack1(int n, int w){
    if(n == 0 || w == 0)return 0;
    if(T1[n][w] != -1)return T1[n][w];
    int w1 = a[n - 1].w;
    int v1 = 0;
    if(w - w1 >= 0)v1 = a[n-1].v + Knapsack1(n-1, w - w1);
    int v2 = Knapsack1(n-1, w);
    int v = max(v1 ,v2);
    T1[n][w] = v;
    return v;
}
int ComputeKnapsack1(int N, int W){
    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= W; j++){
            T1[i][j] = -1;
        }
    }
    int v = Knapsack1(N, W);
    return v;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int ComputeKnapsack2(int N, int W){
    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= W; j++){
            T2[i][j] = 0;
        }
    }
    for(int i = 1; i<=N; i++){
        int n = i;
        for(int w = 0; w<=W; w++){
            int v1 = 0;
            if(w - a[n-1].w >= 0)v1 = a[n-1].v + T2[n-1][w - a[n-1].w];;
            int v2 = T2[n-1][w];
            int v = max(v1, v2);
            T2[n][w] = v;
        }
    }
    return T2[N][W];

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W){
    for(int i = 0; i <= N; i++){
        for(int j = 0; j <= W; j++){
            T3[i][j] = 0;
        }
    }
    for(int i = 1; i<=N; i++){
        int n = i%2;
        int prevN = (i - 1)%2;
        for(int w = 0; w<=W; w++){
            int v1 = 0;
            if(w - a[i-1].w >= 0)v1 = a[i-1].v + T3[prevN][w - a[i-1].w];
            int v2 = T3[prevN][w];
            int v = max(v1, v2);
            T3[n][w] = v;
        }
    }
    return T3[N%2][W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W){
    for(int w = 0; w <= W; w++){
        T4[w] = 0;
    }
    for(int i = 0; i<N; i++){
        for(int w = W; w >= 0; w--){
            int v1 = 0;
            if(w - a[i].w>=0) v1 = a[i].v + T4[w - a[i].w];
            int v2 = T4[w];
            int v = max(v1, v2);
            T4[w] = v;
        }
    }
    return T4[W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W)
{
	return ComputeKnapsack1(N,W);
	//return ComputeKnapsack2(N,W);
	//return ComputeKnapsack3(N,W);
	//return ComputeKnapsack4(N,W);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Compute() {
    int t;
    cin>>t;
    while(t--) {
        int N;
        cin>>N;
        for (int i = 0; i < N; i++){
            cin>>a[i].v>>a[i].w;
        }
        int g;
        cin>>g;
        int tot = 0;
        for(int i = 0; i < g; ++i) {
            int W;
            cin>>W;
            tot += ComputeKnapsack(N, W);
        }
        cout<<tot<<endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    freopen("input_assign09_10130.txt", "r", stdin);
    Compute();
    fclose(stdin);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
