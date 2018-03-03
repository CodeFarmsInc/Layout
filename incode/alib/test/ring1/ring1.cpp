#include <iostream.h>
#include "gen.h"

class A;

class A {
    int aa;
public:
    ZZ_A ZZds; 
    A(){aa=0;}
    A(int i){aa=i;}
    void prt(void){cout << aa << " ";}
    static int cmpA(const void *v1,const void *v2){
        A* a1=(A*)v1;
        A* a2=(A*)v2;
        if(a1->aa<a2->aa)return -1; 
        else if(a1->aa>a2->aa)return 1; 
        else return 0;
    }
};

void printRings(A *tail1,A *tail2){
    A *ap;
    // iterators are automatically provided
    ring1_Iterator itRing1;
    ring2_Iterator itRing2;

    cout << "ring1:\n";
    for(ap=itRing1.fromHead(tail1); ap; ap=itRing1.next()){ ap->prt(); }
    cout << "\n";

    cout << "ring2:\n";
    for(ap=itRing2.fromHead(tail2); ap; ap=itRing2.next()){ ap->prt(); }
    cout << "\n";
    cout.flush();
}

int main(void){
    int i;
    A *ap,*tail1,*tail2,*tailx; A* arr[10];
    
    // create test data one A, three B with two C each.
    tail1=tail2=NULL;
    for(i=1;i<10;i++){
        arr[i]=new A(i);
        tail1=ring1::addTail(tail1,arr[i]);
        tail2=ring2::addHead(tail2,arr[i]);
    }
    ap=new A(10);

    tail1=ring1::append(tail1,arr[3],ap);
    tail2=ring2::append(tail2,arr[3],ap);
    ap=new A(11);
    tail1=ring1::append(tail1,arr[6],ap);
    tail2=ring2::append(tail2,arr[6],ap);
    ap=new A(12);
    tail1=ring1::append(tail1,arr[9],ap);
    tail2=ring2::append(tail2,arr[9],ap);
        
    printRings(tail1,tail2);

    tail1=ring1::sort(A::cmpA,tail1);
    tail2=ring2::sort(A::cmpA,tail2);

    printRings(tail1,tail2);

    tail1=ring1::remove(tail1,arr[1]);
    tail2=ring2::remove(tail2,arr[5]);
    ring1::merge(arr[3],arr[7]);
    tail1=arr[7];
    tailx=arr[3];
    tail1=ring1::remove(tail1,arr[7]);
    tail2=ring2::remove(tail2,arr[7]);

    printRings(tail1,tail2);

    ring1::merge(tail1,tailx);

    printRings(tail1,tail2);
    return(0);
}

#include "gen.cpp"
