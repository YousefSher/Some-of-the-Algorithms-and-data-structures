// GROUP:   X
// ID:      XXXXXXXX
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name:    XXX MY FULL NAME

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <cfloat>
#include <iomanip>
using namespace std;

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

struct Point
{
	double x,y;
};

bool IsBeforeX(Point& a, Point& b){
    return a.x < b.x;
}
bool IsBeforeY(Point& a, Point& b){
    return a.y < b.y;
}
double dist(Point& a, Point& b){
    double x12 = (b.x - a.x)*(b.x - a.x);
    double y12 = (b.y - a.y)*(b.y - a.y);
    double sum = x12 + y12;
    double distance = sqrt(sum);
    return distance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
double ClosestPair(Point* p, int n){
    if(n <= 3){
            double d = DBL_MAX;
            for(int i = 0; i < n; i++){
                for(int j = i + 1; j < n; j++){
                    d = min(d, dist(p[i],p[j]));
                }
            }
        return d;
    }
    double d1 = ClosestPair(p, n/2);
    double d2 = ClosestPair(p + n/2, n - n/2);
    double d = min(d1, d2);
    double mid = p[n/2].x;
    Point* windowPoints = new Point [n];
    int windowSize = 0;
    for(int i = 0; i < n; i++){
        if(fabs(mid - p[i].x) < d){
            windowPoints[windowSize] = p[i];
            windowSize++;
        }
    }
    MergeSort(windowPoints, windowSize, IsBeforeY);
    for(int i = 0; i < windowSize; i++){
        for(int j = i + 1; j < windowSize && fabs(windowPoints[i].y - windowPoints[j].y) < d; j++){
            d = min(d, dist(windowPoints[i],windowPoints[j]));
        }
    }
    delete [] windowPoints;
    return d;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int t;
    cin>>t;
    while(t){
        Point* p = new Point [t];
        for(int i = 0; i < t; i ++){
            double x, y;
            cin>>x>>y;
            p[i] = {x, y};
        }
        MergeSort(p,t,IsBeforeX);
        double d = ClosestPair(p, t);
        if(d > 10000){
            cout<<"INFINITY"<<endl;
        }else{
            cout<<fixed<<setprecision(4)<<d<<endl;
        }
        delete [] p;
        cin>>t;
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
