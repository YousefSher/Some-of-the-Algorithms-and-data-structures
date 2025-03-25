// GROUP:   X
// ID:      XXXXXXXX
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    XXX MY FULL NAME
#include <iostream>
using namespace std;
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

template<class Elem>
struct Heap
{
	Array<Elem> a;
	bool (*IsBefore)(Elem&, Elem&);

	void Initialize(bool (*_IsBefore)(Elem&, Elem&)){
	    IsBefore = _IsBefore;
	    a.Initialize();
	}
	void Destroy(){
        a.Destroy();
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
            MoveUp(Parent(ind));
        }
	}
	void MoveDown(int ind){
	    int childIndex = Child(ind);
        if(childIndex != -1 && IsBefore(a[childIndex], a[ind])){
            swap(a[ind], a[childIndex]);
            MoveDown(childIndex);
        }
	}
	void Add(Elem e){
        a.AddLast(e);
        int i = a.n - 1;
        MoveUp(i);
	}
	Elem GetFirst(){
        return a[0];
	}
	Elem RetrieveFirst(){
	    Elem b = a[0];
        a[0] = a[a.n - 1];
        a.RemoveLast();
        int i = 0;
        if(a.n > 0)
            MoveDown(i);
        return b;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
	return a<b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n = 1;
    while(n){
        cin>>n;
        if(n > 0){
            Heap<int> arr;
            int a, ans = 0, cost = 0;
            arr.Initialize(IsBeforeInt);
            for(int i = 0; i < n; i++){
                cin>>a;
                arr.Add(a);
            }
            ans += arr.RetrieveFirst();
            for(int i = 0; i < n - 1; i++){
                ans += arr.RetrieveFirst();
                cost += ans;
            }
            cout<<cost<<endl;
            arr.Destroy();
        }
    }
	return 0;
}

