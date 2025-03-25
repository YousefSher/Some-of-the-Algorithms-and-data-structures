// GROUP:   X
// ID:      XXXXXXXX
// Assign:  11
// Assign:  EditDist
// UVA:     526
// Name:    XXX MY FULL NAME

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <climits>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82];
char b[82];

int D[81][81];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[81][81];
int EditDist1(int n, int m){
    if(T1[n][m] != -1){
        return T1[n][m];
    }
    if(n == 0 && m ==0)return T1[n][m] = 0;
    if(n == 0){
        D[n][m] = 2;
        T1[n][m] = m;
        return T1[n][m];
    }
    if(m == 0){
        D[n][m] = 3;
        T1[n][m] = n;
        return n;
    }
    int v = INT_MAX;
    int v1 = EditDist1(n - 1, m - 1);
    int v2 = EditDist1(n, m - 1);
    int v3 = EditDist1(n - 1, m);
    if(a[n - 1] == b[m - 1]){
        v = v1;
        D[n][m] = 0;
    }else{
        v = v1 + 1;
        D[n][m] = 1;
    }
    if (v2 + 1 < v){
        v = v2 + 1;
        D[n][m] = 2;
    }
    if (v3 + 1 < v){
        v = v3 + 1;
        D[n][m] = 3;
    }
    T1[n][m] = v;
    return v;
}
int ComputeEditDist1(int N, int M){
    for (int i = 0; i <= N; i++){
        for (int j = 0; j <= M; j++){
            T1[i][j] = -1;
            D[i][j] = -1;
        }
    }
    for (int i = 0; i <= N; i++){
        D[i][0] = 3;
        T1[i][0] = i;
    }
    for (int i = 0; i <= M; i++){
        D[0][i] = 2;
        T1[0][i] = i;
    }
    return EditDist1(N, M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[81][81];
int ComputeEditDist2(int N, int M){
    for (int j = 0; j <= M; j++){
        for (int i = 0; i <= N; i++){
            T2[i][j] = -1;
            D[i][j] = -1;
        }
    }
    for (int i = 0; i <= N; i++){
        D[i][0] = 3;
        T2[i][0] = i;
    }
    for (int i = 0; i <= M; i++){
        D[0][i] = 2;
        T2[0][i] = i;
    }
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            int v = INT_MAX;
            int v1 = T2[i - 1][j - 1];
            int v2 = T2[i][j - 1];
            int v3 = T2[i - 1][j];
            if (a[i - 1] == b[j - 1]){
                v = v1;
                D[i][j] = 0;
            }
            else{
                v = v1 + 1;
                D[i][j] = 1;
            }

            if (v2 + 1 < v){
                v = v2 + 1;
                D[i][j] = 2;
            }
            if (v3 + 1< v){
                v = v3 + 1;
                D[i][j] = 3;
            }
            T2[i][j] = v;
        }
    }
    return T2[N][M];

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];
int ComputeEditDist3(int N, int M)
{
    for(int i = 0; i <= M; i++)
        T3[0][i] = i;
    for (int i = 0; i <= N; i++)
        D[i][0] = 3;
    for (int i = 0; i <= M; i++)
        D[0][i] = 2;
    for(int t = 1; t <= N; t++){
        int i = t % 2;
        int prev = (i + 1) % 2;
        T3[i][0] = t;
        for(int j = 1; j <= M; j++){
            int v1 = T3[prev][j - 1];
            int v2 = T3[i][j - 1];
            int v3 = T3[prev][j];
            int v = v1;
            if(a[t - 1] == b[j - 1]){
                D[t][j] = 0;
            }
            else{
                v = v1 + 1;
                D[t][j] = 1;
            }
            if(v2 + 1 < v){
                v = v2 + 1;
                D[t][j] = 2;
            }
            if(v3 + 1 < v){
                v = v3 + 1;
                D[t][j] = 3;
            }
            T3[i][j] = v;
        }
    }
    return T3[N % 2][M];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];
int ComputeEditDist4(int N, int M)
{
    for (int i = 0; i <= N; i++)
        T4[i] = i;
     for (int i = 0; i <= N; i++)
        D[i][0] = 3;
    for (int i = 0; i <= M; i++)
        D[0][i] = 2;
    for (int j = 1; j <= M; j++)
    {
        int z = T4[0];
        T4[0] = j;
        for (int i = 1; i <= N; i++)
        {
            int v = INT_MAX;
            int v1 = z;
            int v2 = T4[i];
            int v3 = T4[i - 1];
            v = v1;
            if(a[i - 1] == b[j - 1]){
                D[i][j] = 0;
            }else{
                v = v1 + 1;
                D[i][j] = 1;
            }
            if(v2 + 1 < v){
                v = v2 + 1;
                D[i][j] = 2;
            }
            if(v3 + 1 < v){
                v = v3 + 1;
                D[i][j] = 3;
            }
            z = T4[i];
            T4[i] = v;
        }
    }
    return T4[N];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper
{
    int n, m;
    int oper;
};

Oper opers[81];
int EditDistSol(int N, int M){
    int c = 0, n = N, m = M;
    while(n > 0 || m > 0){
        if((n > 0 && m > 0) && D[n][m] == 0){
            n--;
            m--;
        }else if((n > 0 && m > 0)&&D[n][m] == 1){
            opers[c] = {n, m, 1};
            n--;
            m--;
            c++;
        }else if(m > 0 &&D[n][m] == 2){
            opers[c] = {n, m, 2};
            m--;
            c++;
        }else if(n > 0 &&D[n][m] == 3){
            opers[c] = {n, m, 3};
            n--;
            c++;
        }
    }
    cout<<c<<endl;
    for(int i = 0; i < c; i++){
        if(opers[i].oper == 1){
            cout<<i + 1<<" Replace "<<opers[i].n<<","<<b[opers[i].m - 1]<<endl;
        }
        else if(opers[i].oper == 2){
            cout<<i + 1 <<" Insert "<<opers[i].n + 1<<","<<b[opers[i].m - 1]<<endl;
        }else if(opers[i].oper == 3){
            cout<<i + 1<<" Delete "<<opers[i].n<<endl;
        }
    }
    return c;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M){
    //return ComputeEditDist1(N, M);
    return ComputeEditDist2(N, M);
    //return ComputeEditDist3(N, M);
    //return ComputeEditDist4(N, M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Compute()
{
    int cas = 0;
    while (true)
    {
        a[0] = 0;
        b[0] = 0;
        if (!fgets(a, 82, stdin))break;
        fgets(b, 82, stdin);
        a[strlen(a) - 1] = 0;
        b[strlen(b) - 1] = 0;
        if (cas)
            cout << endl;
        int N = strlen(a), M = strlen(b);
        ComputeEditDist(N, M);
        EditDistSol(N, M);
        cas++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
abcac
bcd
aaa
aabaaaa
*/
int main()
{
    // freopen("input_assign11_00526.txt", "r", stdin);
    Compute();
    return 0;
}
