// GROUP:   1
// ID:      20226117
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    Yousef Sherif Mohamad

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
long long CountInvMerge(long long* a, int n){
    int mid = n / 2;
    long long* left = new long long[mid];
    long long* right = new long long[n - mid];
    for(int i = 0; i < mid; i++){
        left[i] = a[i];
    }
    for(int i = 0; i < n - mid; i++){
        right[i] = a[i + mid];
    }
    int i = 0, j = 0, k = 0;
    long long invCount = 0;
    while(i < mid && j < (n - mid)) {
        if(left[i] <= right[j]) {
            a[k++] = left[i++];
        }else {
            a[k++] = right[j++];
            invCount += (mid - i);
        }
    }
    while(i < mid){
         a[k++] = left[i++];
    }
    while(j < (n - mid)){
         a[k++] = right[j++];
    }
    delete[] left;
    delete[] right;
    return invCount;
}

long long CountInv(long long* a, int n){
    if(n < 2)
        return 0;
    int mid = n / 2;
    long long invCount = 0;
    invCount += CountInv(a, mid);
    invCount += CountInv(a + mid, n - mid);
    invCount += CountInvMerge(a, n);
    return invCount;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    while (true){
        int n;
        cin>>n;
        if(n == 0)
            break;
        long long* arr = new long long[n];
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
        long long num = CountInv(arr, n);
        cout<<num<<endl;
        delete[] arr;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
