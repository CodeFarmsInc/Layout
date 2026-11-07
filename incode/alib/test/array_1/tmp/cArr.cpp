#include <stdlib.h>
// --------------------------------------------------------
unsigned int cArr_Array::maxCapacity=0;

// --------------------------------------------------------------
// Remove the entry from the array, and shrink the remaining part
// of the array. This changes 'num' and indexes of all entries
// above this index.
// See array.h for method remove() which is much faster but changes
// the order of the array.
// --------------------------------------------------------------
void cArr_Array::extract(Header *hp, const int k){
    int j,num;

    num=hp->ZZds.ZZcArr.num;
    if(k>num)return; // nothing to do
    if(k==num){hp->ZZds.ZZcArr.num=num-1; return;}
    for(j=k+1; j<=num; j++)hp->ZZds.ZZcArr.array[j-1]=hp->ZZds.ZZcArr.array[j];
    hp->ZZds.ZZcArr.num=num-1;
}

// --------------------------------------------------------------
// Insert the entry into the array[k], and expand the remaining part
// of the array. This changes 'num' and indexes of all entries
// above this index. 
// --------------------------------------------------------------
void cArr_Array::insert(Header *hp,const int k,int *t){
    int j,kk,oldNum,newNum,sz;

    if(k<0)kk=0; else kk=k;
    oldNum=hp->ZZds.ZZcArr.num;
    sz=hp->ZZds.ZZcArr.sz;
    if(kk>oldNum) newNum=kk; else newNum=oldNum+1;
    if(newNum>=sz){
        (void)sizeChange(hp,newNum+1,0);
    }
    for(j=oldNum; j>=kk; j--) hp->ZZds.ZZcArr.array[j+1]=hp->ZZds.ZZcArr.array[j];
    hp->ZZds.ZZcArr.array[kk]=(*t);
    hp->ZZds.ZZcArr.num=newNum;
}

// --------------------------------------------------------------
// This function changes the array to new capacity, newCap.
// Parameter 'exact' determines the multiples in which the array should grow:
//  exact=0  frow using the increment
//  exact=1  exactly to newSz
// When decreasing the size of the array, it is always decreased to
// exactly newSz.
// When the size is fixed, only a change for newSz to be exact is accepted.
//   This prevents erroneous automatic size change, but still allows to
// enforce the array size when intentional.
// Warning: When reducing the size, entries with index >=newSz are
//          removed from the array.
// Returns 0 if everything OK, returns 1 when problem.
// --------------------------------------------------------------
int cArr_Array::sizeChange(Header *hp,const unsigned int newCap,const int exact){
    int* a; int* arr;
    int nCap,j,s,sn,cap,num,incr;

    nCap=newCap;
    arr=hp->ZZds.ZZcArr.array;
    cap=hp->ZZds.ZZcArr.sz;
    num=hp->ZZds.ZZcArr.num;
    incr=hp->ZZds.ZZcArr.incr;

    if(incr==0 && !exact){
    printf("error for cArr: attempt to change a fixed array into flexible one\n");
    return 1;
    }
    if(!arr){
        printf("error for cArr: cannot modify capacity, array not formed\n");
        return 1;
    }

    if(nCap==cap)return 0; // nothing to do
    if(maxCapacity>0 && nCap>maxCapacity){
        printf("error for cArr: requested capacity=%d, maxCapacity=%d\n",
                                                 nCap,maxCapacity);
        return 1;
    }

    if(nCap<cap || exact==1)s=cap;
    else { // increase the size using increment
        for(s=cap; s<nCap; s=sn){
            if(incr>0) sn=s+incr;
            else       sn=s*(-incr);
          
            if(maxCapacity>0 && sn>maxCapacity){s=maxCapacity; break;}
        }
    }

    a=new int[s];
    if(!a){
        printf("error for cArr: failed to allocate array capacity=%d\n",s);
        return 1;
    }

    if(s<=num)sn=s-1; else sn=num;
    for(j=0; j<=sn; j++)a[j]=arr[j];
    delete[] arr;
    hp->ZZds.ZZcArr.array=a;
    hp->ZZds.ZZcArr.sz=s;
    if(num>=s)hp->ZZds.ZZcArr.num=s-1;

    return 0;
}

// --------------------------------------------------------------
// Create array of pointers with the initial size s
// Returns: Returs the array, NULL when the allocation fails
// --------------------------------------------------------------
int* cArr_Array::form(Header *hp,unsigned int const sz,int const incr){
    if(hp->ZZds.ZZcArr.array)free(hp);

    hp->ZZds.ZZcArr.array=new int[sz];
    if(!hp->ZZds.ZZcArr.array){
        printf("cArr error, cannot allocate array size=%d\n",sz);
        return NULL;
    }
    hp->ZZds.ZZcArr.sz=sz;
    hp->ZZds.ZZcArr.num= -1;
    hp->ZZds.ZZcArr.incr=incr;
    return hp->ZZds.ZZcArr.array;
}

// --------------------------------------------------------------
// Sort the array by applying qsort with function cmp that compares
// two objects. Only the section of the array which is used will be
// sorted.
// --------------------------------------------------------------
void cArr_Array::sort(cmpType cmp,Header *hp){
    if(hp->ZZds.ZZcArr.num<=0)return; // no need to sort 0 or 1 item
    qsort(hp->ZZds.ZZcArr.array,hp->ZZds.ZZcArr.num+1,sizeof(int),cmp);
}
void cArr_Array::sortSubset(cmpType cmp,Header *hp,int i1,int i2){
    if(i2>hp->ZZds.ZZcArr.num){
        printf("warning: upper range of sortSubset() automatically adjusted ");
        printf("from=%d to %d\n",i2,hp->ZZds.ZZcArr.num);
        i2=hp->ZZds.ZZcArr.num;
    }
    qsort(&(hp->ZZds.ZZcArr.array[i1]),i2-i1+1,sizeof(int),cmp);
}

// --------------------------------------------------------------
// Return pointer to the element[i] of the array.
// WARNING: The pointer thus obtained must be used either immediately,
//          or when we are absolutely sure that the array will not 
//          automatically re-allocate, for example when working with
//          a fixed array (incr=0).
// --------------------------------------------------------------
int* cArr_Array::ind(Header *hp,int i){
    if(!(hp->ZZds.ZZcArr.array)){
        printf("error for cArr: index operation attempted before formed\n");
        return NULL;
    }
    if(i>=hp->ZZds.ZZcArr.sz){
        if(sizeChange(hp,i+1,0))return NULL; // error message inside there
    }
    if(hp->ZZds.ZZcArr.num<i)hp->ZZds.ZZcArr.num=i;
    return &(hp->ZZds.ZZcArr.array[i]);
}

// --------------------------------------------------------------
// Fast way of getting ind[0]
// --------------------------------------------------------------
int* cArr_Array::head(Header *hp){
    return (int*)(hp->ZZds.ZZcArr.array);
}


// --------------------------------------------------------------
// The following functions use the array as a partially sorted binary heap, 
//    inHeap() inserts element e into the heap,
//    outHeap() returns in e the top of the heap, and reduces the heap,
//    updHeap() updates the heap if the element in postion i changes its value,
//    delHeap() deletes elemenr in the position i and updates the heap.
//    indHeap() is a private utility, ind() function with the callback
// All these functions use cmpF() to compare two entries from the array.
// Whenever an element of the heap changes its postion, the new position
// is reported by the callback function. This is handy in some advance
// application.
// --------------------------------------------------------------

// --------------------------------------------------------------
// Insert the new element, e, into the heap. The entire object is inserted,
// not just its pointer.
// --------------------------------------------------------------
void cArr_Array::inHeap(cmpType cmpF,Header *hp,int *e,bck callback){
    int i; int* newE;

    i=hp->ZZds.ZZcArr.num + 1;
    newE=indHeap(hp,i,callback);
    if(!newE)return;
    (*newE)=(*e);
    if(callback) (*callback)(&(hp->ZZds.ZZcArr.array[i]),i);
    if(i>1)upHeap(cmpF,hp,i,callback);
}

// --------------------------------------------------------------
// Assuming a new element in location n, re-sort the heap proceeding
// from n to all its ascendents.
// --------------------------------------------------------------
void cArr_Array::upHeap(cmpType cmpF,Header *hp,int n,bck callback){
    int i1,i2; int* a1; int* a2; int aa;

    if(n==0)return;
    // traverse the ascendants
    for(i1=n, i2=(n-1)/2, a1=ind(hp,n); i1>0; i1=i2, i2=(i2-1)/2, a1=a2){
        a2=ind(hp,i2);
        if(cmpF(a2,a1)<=0)break;
        // exchange the contents of a1 and a2
        aa=(*a1); (*a1)=(*a2); (*a2)=aa;
        if(callback){
            (*callback)(&(hp->ZZds.ZZcArr.array[i1]),i1);
            (*callback)(&(hp->ZZds.ZZcArr.array[i2]),i2);
        }
    }
}

// --------------------------------------------------------------
// Return the top of the heap in e, and remove it from the heap.
// Return 1 when successful, return 0 when the heap is empty
// --------------------------------------------------------------
int cArr_Array::outHeap(cmpType cmpF,Header *hp,int* e,bck callback){
    int num;

    num=hp->ZZds.ZZcArr.num;
    if(num<0) return 0;
    (*e)=hp->ZZds.ZZcArr.array[0];
    if(callback) (*callback)(&(hp->ZZds.ZZcArr.array[0]),-1);
    if(num>0){
       hp->ZZds.ZZcArr.array[0]=hp->ZZds.ZZcArr.array[num];
       if(callback) (*callback)(&(hp->ZZds.ZZcArr.array[0]),0);
       downHeap(cmpF,hp,0,callback);
    }
    (hp->ZZds.ZZcArr.num)--;
    return 1;
}


// --------------------------------------------------------------
// Assuming a new element in location n, re-sort the heap proceeding
// from n to all its descendents.
// --------------------------------------------------------------
void cArr_Array::downHeap(cmpType cmpF,Header *hp,int n,bck callback){
    int k,i1,i2,num; int* ak; int* a1; int* a2; int aa;

    num=hp->ZZds.ZZcArr.num;
    if(n>=num)return;
    // traverse the descendents
    for(k=n, ak=ind(hp,n); k<num; k=i1, ak=a1){
        i1=2*k+1;
        i2=2*k+2;
        if(i1>num)break;
        a1=ind(hp,i1);
        if(i2<=num){
            a2=ind(hp,i2);
            if(cmpF(a1,a2)>0){
                a1=a2;
                i1=i2;
            }
        }
        if(cmpF(ak,a1)<=0)break;
        // exchange the contents of ak and a1 (locations k and i1)
        aa=(*ak); (*ak)=(*a1); (*a1)=aa;
        if(callback){
            (*callback)(&(hp->ZZds.ZZcArr.array[i1]),i1);
            (*callback)(&(hp->ZZds.ZZcArr.array[k]),k);
        }
    }
}

// --------------------------------------------------------------
// Update heap when the value associated with entry n has changed
// --------------------------------------------------------------
void cArr_Array::updHeap(cmpType cmpF,Header *hp,int n,bck callback){
    int num,n1,n2;

    num=hp->ZZds.ZZcArr.num;
    if(n<0 || n>num){
        printf("error updating heap=cArr, n=%d num=%d\n",n,num);
        return;
    }
    downHeap(cmpF,hp,n,callback);
    upHeap(cmpF,hp,n,callback);
}

// --------------------------------------------------------------
// Delete item index n from the heap.
// --------------------------------------------------------------
void cArr_Array::delHeap(cmpType cmpF,Header *hp,int n,bck callback){
    int num; int* arr;

    num=hp->ZZds.ZZcArr.num;
    arr=hp->ZZds.ZZcArr.array;
    if(n<0 || n>num){
        printf("error deleting from heap=cArr, n=%d num=%d\n",n,num);
        return;
    }
    (hp->ZZds.ZZcArr.num)--;
    if(callback) (*callback)(&(hp->ZZds.ZZcArr.array[num]),-1);
    if(n==num) return;
    arr[n]=arr[num];
    if(callback) (*callback)(&(hp->ZZds.ZZcArr.array[n]),n);
    updHeap(cmpF,hp,n,callback);
}

// --------------------------------------------------------------
// Same function as ind() but providing a callback function.
// This function is needed when relocating heaps automatically.
// --------------------------------------------------------------
int* cArr_Array::indHeap(Header *hp,int i,bck callback){
    int k,num,sz;
    int *elem;

    num=hp->ZZds.ZZcArr.num;
    sz=hp->ZZds.ZZcArr.sz;
    elem=ind(hp,i);
    if(!elem)return NULL;
    // report changes of position when re-allocating
    if(i>=sz){
        for(k=0; k<num; k++){
            if(callback) (*callback)(&(hp->ZZds.ZZcArr.array[k]),k);
        }
    }
    return elem;
}
// --------------------------------------------------------------


int cArr_Array::formed(Header *hp){ if(hp->ZZds.ZZcArr.array)return 1; return 0;}

void cArr_Array::free(Header *hp){ 
    if(hp->ZZds.ZZcArr.array){
        delete[] hp->ZZds.ZZcArr.array;
        hp->ZZds.ZZcArr.array=NULL;
    }
    hp->ZZds.ZZcArr.num= -1;
    hp->ZZds.ZZcArr.sz=0;
}

unsigned int cArr_Array::capacity(Header *hp) {return hp->ZZds.ZZcArr.sz;} 

unsigned int cArr_Array::size(Header *hp) {return (unsigned int)(hp->ZZds.ZZcArr.num + 1);} 

int cArr_Array::increment(Header *hp) {return hp->ZZds.ZZcArr.incr;} 

int cArr_Array::get(Header *hp,const unsigned int k){  // a=array[k]
    int kk=k;
    if(kk>=hp->ZZds.ZZcArr.sz)sizeChange(hp,kk+1,0);
    if(kk>hp->ZZds.ZZcArr.num)hp->ZZds.ZZcArr.num=kk;
    return hp->ZZds.ZZcArr.array[kk];
}

void cArr_Array::set(Header *hp,const unsigned int k,int a){ // array[k]=a
    int kk=k;
    if(kk>=hp->ZZds.ZZcArr.sz)sizeChange(hp,kk+1,0);
    if(kk>hp->ZZds.ZZcArr.num)hp->ZZds.ZZcArr.num=kk;
    hp->ZZds.ZZcArr.array[kk]=a;
}
void cArr_Array::remove(Header *hp,const unsigned int k){ // fast but order changed
    int kk=k;
    int num=hp->ZZds.ZZcArr.num;
    if(kk<num){hp->ZZds.ZZcArr.array[k]=hp->ZZds.ZZcArr.array[num]; (hp->ZZds.ZZcArr.num)--;}
}
int cArr_Array::reduce(Header *hp){             // reduce the array to its used size
    return sizeChange(hp,hp->ZZds.ZZcArr.num+1,1);
}
int cArr_Array::reduce(Header *hp,const unsigned int newCap){ // reduce size to newSz
    if(newCap>=hp->ZZds.ZZcArr.sz)return hp->ZZds.ZZcArr.sz;
    return sizeChange(hp,newCap,1);
} 
int cArr_Array::grow(Header *hp,const unsigned int newCap){
    return sizeChange(hp,newCap,0);
} 
void cArr_Array::push(Header *hp,int* e){
    unsigned int num,sz;

    num=hp->ZZds.ZZcArr.num+1; sz=hp->ZZds.ZZcArr.sz;
    if(num>=sz)sizeChange(hp,num+1,0);
    hp->ZZds.ZZcArr.array[num]=(*e); (hp->ZZds.ZZcArr.num)++;
}
int* cArr_Array::pop(Header *hp){int* e=NULL; int num=hp->ZZds.ZZcArr.num;
    if(num>=0){e= &(hp->ZZds.ZZcArr.array[num]); (hp->ZZds.ZZcArr.num)--;}
    return e;
}
void cArr_Array::reset(Header *hp,int newSz,int incr){
    hp->ZZds.ZZcArr.num=newSz-1; hp->ZZds.ZZcArr.incr=incr;
}

// -----------------------------------------------------------------------
// Add a new object into the ordered collection. This is relatively
// fast using binary search to find the position, but a section of
// the array must move to open one slot.
// -----------------------------------------------------------------------
void cArr_Array::addOrd(cmpType cmpF,Header *hp,int *op){
    int k,found;

    if(hp->ZZds.ZZcArr.num<0)k=0;
    else k=binSearch(cmpF,hp,op,&found);
    insert(hp,k,op); // insert even if the same key is already there
}

// -----------------------------------------------------------------------
// Find the given object in the sorted array (using binary search0
// and remove it from the array without changing the order of the remaining
// elements.
// -----------------------------------------------------------------------
void cArr_Array::delOrd(cmpType cmpF,Header *hp,int *obj){
    int k,found;

    k=binSearch(cmpF,hp,obj,&found);
    if(found) delOrd(cmpF,hp,k);
    else printf("warning: calling cArr::delOrd() but object not there\n");
}


// -----------------------------------------------------------------------
// Binary search, returns the index of the object with the same key as op
// or the first object with the higher key than that.
// In case of any error, e.g. when the array has not been formed yet, 
// the function generates an error message and returns -1.
// -----------------------------------------------------------------------
int cArr_Array::binSearch(cmpType cmpF,Header *hp,int *op,int *found){
    int i1,i2,k,cmp,num; int* rr; int* arr;

    arr=hp->ZZds.ZZcArr.array;
    num=hp->ZZds.ZZcArr.num;
    if(!arr || num<0){
        printf("cArr error in binSearch(): array not formed or empty\n");
        return  -1;
    }
    i1=0; i2=num; k= -1;
    
    rr= &(arr[i1]); cmp=cmpF(op,rr);
    if(cmp==0){*found=1; return i1;}
    if(cmp<0) {*found=0; return i1;}
    rr= &(arr[i2]); cmp=cmpF(op,rr);
    if     (cmp>0) {*found=0; return num+1;}
    else if(cmp==0){*found=1; return num;} 

    k=(i1+i2)/2;
    while(k>i1){
        rr= &(arr[k]); cmp=cmpF(rr,op);
        if(cmp>0)i2=k;
        else if(cmp<0)i1=k;
        else {*found=1; return k;}
        k=(i1+i2)/2;
    }
    k++;
    rr= &(arr[k]); cmp=cmpF(rr,op);
    if(cmp==0)*found=1; else *found=0;
    return k;
}

// -----------------------------------------------------------------------
// Returns the value of the bin No.i (0 or 1).
// Returns -1 in case of error.
// -----------------------------------------------------------------------
int cArr_Array::getBit(Header *hp,int i){
    int iChar,iBit,sz,k,newBytes; int* ap; unsigned char *p,b;

    sz=sizeof(int) * hp->ZZds.ZZcArr.sz; // sz is size in bytes
    if(i>=sz*8){ // sz*8 is the size in bits
        ap=ind(hp,i/(8*sizeof(int)));
        if(!ap){
            printf("cArr error: cannot realocate for %d bits\n",i);
            return -1;
        }

        // initialize the new part of the array to 0
        newBytes=sizeof(int)*hp->ZZds.ZZcArr.sz;
        p=(unsigned char*)(hp->ZZds.ZZcArr.array);
        for(k=sz; k<newBytes; k++) p[k]=0;
    }
    else if(hp->ZZds.ZZcArr.num<0){ // first call, initialize all bits to 0
        p=(unsigned char*)(hp->ZZds.ZZcArr.array);
        for(k=0; k<sz; k++) p[k]=0;
    }

    k=i/(8*sizeof(int)); // object index in which bit i is
    if(hp->ZZds.ZZcArr.num < k)hp->ZZds.ZZcArr.num=k;

    p=(unsigned char*)(hp->ZZds.ZZcArr.array);
    iChar=i/8;             // character index where the bit is
    iBit=i-iChar*8;        // bit within that character
    p=p+iChar;
    b=1 << iBit;
    if(*p & b){
        return 1;
    }
    return 0;
}

// -----------------------------------------------------------------------
// Set bit No.i to val, where val=0 or 1.
// Return 0=everything OK, -1 when error.
// -----------------------------------------------------------------------
int cArr_Array::setBit(Header *hp,int i,int val){
    int iChar,iBit,sz,k,newBytes; int* ap; unsigned char *p,b;

    sz=sizeof(int) * hp->ZZds.ZZcArr.sz; // sz is size in bytes
    if(i>=sz*8){ // sz*8 is the size in bits
        ap=ind(hp,i/(8*sizeof(int)));
        if(!ap){
            printf("cArr error: cannot realocate for %d bits\n",i);
            return -1;
        }

        // initialize the new part of the array to 0
        newBytes=sizeof(int)*hp->ZZds.ZZcArr.sz;
        p=(unsigned char*)(hp->ZZds.ZZcArr.array);
        for(k=sz; k<newBytes; k++) p[k]=0;
    }
    else if(hp->ZZds.ZZcArr.num<0){ // first call, initialize all bits to 0
        p=(unsigned char*)(hp->ZZds.ZZcArr.array);
        for(k=0; k<sz; k++) p[k]=0;
    }

    k=i/(8*sizeof(int)); // object index in which bit i is
    if(hp->ZZds.ZZcArr.num < k)hp->ZZds.ZZcArr.num=k;

    p=(unsigned char*)(hp->ZZds.ZZcArr.array);
    iChar=i/8;             // character index where the bit is
    iBit=i-iChar*8;        // bit within that character
    p=p+iChar;
    b=1 << iBit;
    if(val)*p=*p | b;
    else   *p=*p & ~b;
    return 0;
}

// -----------------------------------------------------------------------
// For the key given in op, find the index of the object in the array,
// using the binary search. If the object is not found, return 
// the index of the entry before which the new object would have
// to be inserted. The function returns found=1 when found, =0 when not.
// -----------------------------------------------------------------------
int cArr_Array::getOrd(cmpType cmpF,Header *hp,int *op,int *found){
    int k=binSearch(cmpF,hp,op,found);
    return k;
}



