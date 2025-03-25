#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <climits>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11];

int T[11][11];
int D[11][11];
int MatChain(int a, int b){
  if(b == a+1){
    return T[a][b] = 0;
  }
  if(T[a][b] != -1){
    return T[a][b];
  }
  int v = INT_MAX, q, k;
  for(k = a + 1; k < b; k++){
    int r = p[a] * p[k] * p[b] + MatChain(a, k) + MatChain(k, b);
    if(r < v){
      v = r;
      q = k;
    }
  }
  T[a][b] = v;
  D[a][b] = q;
  return v;
}
void MatChainTopDown(int n){
  for(int i = 0; i < 11; i++){
    for(int j = 0; j < 11; j++){
      T[i][j] = -1;
      D[i][j] = -1;
    }
  }
  MatChain(0, n);
}

void MatChainBottomUp(int n){
  for(int i = 0; i < 10; i++)T[i][i+1]=0;
  for(int t = 2; t <= n; t++){
    for(int a = 0; a + t <= n; a++){
      int b = a + t;
      int v = INT_MAX, q;
      for(int k = a + 1; k < b; k++){
        int r = p[a] * p[k] * p[b] + T[a][k] + T[k][b];
        if(r < v){
          v = r;
          q = k;
        }
      }
      T[a][b] = v;
      D[a][b] = q;
    }
  }
}

void MatChainSol(int a, int b){
    if(b <= a + 1){
      cout << "A" << a+1;
    } else {
      int k = D[a][b];
      cout << "(";
      MatChainSol(a, k);
      cout << " x ";
      MatChainSol(k, b);
      cout << ")";
    }
    return;
}

/*
3
1 5
5 20
20 1
3
5 10
10 20
20 35
6
30 35
35 15
15 5
5 10
10 20
20 25
0
*/

void Compute(){
  int n;
  int caseNumber = 1;
  cin>>n;
  while(n){
    int psize = 0;
    for(int i = 0; i < n * 2; i++){
      int x;
      cin>>x;
      if(i % 2 == 0 || i == n * 2 - 1){
        p[psize++] = x;
      }else{
        continue;
      }
    }
    MatChainBottomUp(n);
    cout<<"Case "<< caseNumber<<": ";
    MatChainSol(0, n);
    cout<<endl;
    caseNumber++;
    cin>>n;
  }
  return;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign10_00348.txt", "r", stdin);
	Compute();
	return 0;
}///////////////////////////////////////////////////////////////////////////////////////
