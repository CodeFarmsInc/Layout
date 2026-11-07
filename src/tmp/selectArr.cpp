#include <stdlib.h>
// --------------------------------------------------------
unsigned int selectArr_Array::maxCapacity=0;

// --------------------------------------------------------------
// Remove the entry from the array, and shrink the remaining part
// of the array. This changes 'num' and indexes of all entries
// above this index.
// See array.h for method remove() which is much faster but changes
// the order of the array.
// --------------------------------------------------------------
void selectArr_Array::extract(Layout *hp, const int k){
    int j,num;

    num=hp->ZZds.ZZselectArr.num;
    if(k>num)return; // nothing to do
    if(k==num){hp->ZZds.ZZselectArr.num=num-1; return;}
    for(j=k+1; j<=num; j++)hp->ZZds.ZZselectArr.array[j-1]=hp->ZZds.ZZselectArr.array[j];
    hp->ZZds.ZZselectArr.num=num-1;
}

// --------------------------------------------------------------
// Insert the entry into the array[k], and expand the remaining part
// of the array. This changes 'num' and indexes of all entries
// above this index. 
// --------------------------------------------------------------
void selectArr_Array::insert(Layout *hp,const int k,void* *t){
    int j,kk,oldNum,newNum,sz;

    if(k<0)kk=0; else kk=k;
    oldNum=hp->ZZds.ZZselectArr.num;
    sz=hp->ZZds.ZZselectArr.sz;
    if(kk>oldNum) newNum=kk; else newNum=oldNum+1;
    if(newNum>=sz){
        (void)sizeChange(hp,newNum+1,0);
    }
    for(j=oldNum; j>=kk; j--) hp->ZZds.ZZselectArr.array[j+1]=hp->ZZds.ZZselectArr.array[j];
    hp->ZZds.ZZselectArr.array[kk]=(*t);
    hp->ZZds.ZZselectArr.num=newNum;
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
int selectArr_Array::sizeChange(Layout *hp,const unsigned int newCap,const int exact){
    void** a; void** arr;
    int nCap,j,s,sn,cap,num,incr;

    nCap=newCap;
    arr=hp->ZZds.ZZselectArr.array;
    cap=hp->ZZds.ZZselectArr.sz;
    num=hp->ZZds.ZZselectArr.num;
    incr=hp->ZZds.ZZselectArr.incr;

    if(incr==0 && !exact){
    printf("error for selectArr: attempt to change a fixed array into flexible one\n");
    return 1;
    }
    if(!arr){
        printf("error for selectArr: cannot modify capacity, array not formed\n");
        return 1;
    }

    if(nCap==cap)return 0; // nothing to do
    if(maxCapacity>0 && nCap>maxCapacity){
        printf("error for selectArr: requested capacity=%d, maxCapacity=%d\n",
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

    a=new void*[s];
    if(!a){
        printf("error for selectArr: failed to allocate array capacity=%d\n",s);
        return 1;
    }

    if(s<=num)sn=s-1; else sn=num;
    for(j=0; j<=sn; j++)a[j]=arr[j];
    delete[] arr;
    hp->ZZds.ZZselectArr.array=a;
    hp->ZZds.ZZselectArr.sz=s;
    if(num>=s)hp->ZZds.ZZselectArr.num=s-1;

    return 0;
}

// --------------------------------------------------------------
// Create array of pointers with the initial size s
// Returns: Returs the array, NULL when the allocation fails
// --------------------------------------------------------------
void** selectArr_Array::form(Layout *hp,unsigned int const sz,int const incr){
    if(hp->ZZds.ZZselectArr.array)free(hp);

    hp->ZZds.ZZselectArr.array=new void*[sz];
    if(!hp->ZZds.ZZselectArr.array){
        printf("selectArr error, cannot allocate array size=%d\n",sz);
        return NULL;
    }
    hp->ZZds.ZZselectArr.sz=sz;
    hp->ZZds.ZZselectArr.num= -1;
    hp->ZZds.ZZselectArr.incr=incr;
    return hp->ZZds.ZZselectArr.array;
}

// --------------------------------------------------------------
// Sort the array by applying qsort with function cmp that compares
// two objects. Only the section of the array which is used will be
// sorted.
// --------------------------------------------------------------
void selectArr_Array::sort(cmpType cmp,Layout *hp){
    if(hp->ZZds.ZZselectArr.num<=0)return; // no need to sort 0 or 1 item
    qsort(hp->ZZds.ZZselectArr.array,hp->ZZds.ZZselectArr.num+1,sizeof(void*),cmp);
}
void selectArr_Array::sortSubset(cmpType cmp,Layout *hp,int i1,int i2){
    if(i2>hp->ZZds.ZZselectArr.num){
        printf("warning: upper range of sortSubset() automatically adjusted ");
        printf("from=%d to %d\n",i2,hp->ZZds.ZZselectArr.num);
        i2=hp->ZZds.ZZselectArr.num;
    }
    qsort(&(hp->ZZds.ZZselectArr.array[i1]),i2-i1+1,sizeof(void*),cmp);
}

// --------------------------------------------------------------
// Return pointer to the element[i] of the array.
// WARNING: The pointer thus obtained must be used either immediately,
//          or when we are absolutely sure that the array will not 
//          automatically re-allocate, for example when working with
//          a fixed array (incr=0).
// --------------------------------------------------------------
void** selectArr_Array::ind(Layout *hp,int i){
    if(!(hp->ZZds.ZZselectArr.array)){
        printf("error for selectArr: index operation attempted before formed\n");
        return NULL;
    }
    if(i>=hp->ZZds.ZZselectArr.sz){
        if(sizeChange(hp,i+1,0))return NULL; // error message inside there
    }
    if(hp->ZZds.ZZselectArr.num<i)hp->ZZds.ZZselectArr.num=i;
    return &(hp->ZZds.ZZselectArr.array[i]);
}

// --------------------------------------------------------------
// Fast way of getting ind[0]
// --------------------------------------------------------------
void** selectArr_Array::head(Layout *hp){
    return (void**)(hp->ZZds.ZZselectArr.array);
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
void selectArr_Array::inHeap(cmpType cmpF,Layout *hp,void* *e,bck callback){
    int i; void** newE;

    i=hp->ZZds.ZZselectArr.num + 1;
    newE=indHeap(hp,i,callback);
    if(!newE)return;
    (*newE)=(*e);
    if(callback) (*callback)(&(hp->ZZds.ZZselectArr.array[i]),i);
    if(i>1)upHeap(cmpF,hp,i,callback);
}

// --------------------------------------------------------------
// Assuming a new element in location n, re-sort the heap proceeding
// from n to all its ascendents.
// --------------------------------------------------------------
void selectArr_Array::upHeap(cmpType cmpF,Layout *hp,int n,bck callback){
    int i1,i2; void** a1; void** a2; void* aa;

    if(n==0)return;
    // traverse the ascendants
    for(i1=n, i2=(n-1)/2, a1=ind(hp,n); i1>0; i1=i2, i2=(i2-1)/2, a1=a2){
        a2=ind(hp,i2);
        if(cmpF(a2,a1)<=0)break;
        // exchange the contents of a1 and a2
        aa=(*a1); (*a1)=(*a2); (*a2)=aa;
        if(callback){
            (*callback)(&(hp->ZZds.ZZselectArr.array[i1]),i1);
            (*callback)(&(hp->ZZds.ZZselectArr.array[i2]),i2);
        }
    }
}

// --------------------------------------------------------------
// Return the top of the heap in e, and remove it from the heap.
// Return 1 when successful, return 0 when the heap is empty
// --------------------------------------------------------------
int selectArr_Array::outHeap(cmpType cmpF,Layout *hp,void** e,bck callback){
    int num;

    num=hp->ZZds.ZZselectArr.num;
    if(num<0) return 0;
    (*e)=hp->ZZds.ZZselectArr.array[0];
    if(callback) (*callback)(&(hp->ZZds.ZZselectArr.array[0]),-1);
    if(num>0){
       hp->ZZds.ZZselectArr.array[0]=hp->ZZds.ZZselectArr.array[num];
       if(callback) (*callback)(&(hp->ZZds.ZZselectArr.array[0]),0);
       downHeap(cmpF,hp,0,callback);
    }
    (hp->ZZds.ZZselectArr.num)--;
    return 1;
}


// --------------------------------------------------------------
// Assuming a new element in location n, re-sort the heap proceeding
// from n to all its descendents.
// --------------------------------------------------------------
void selectArr_Array::downHeap(cmpType cmpF,Layout *hp,int n,bck callback){
    int k,i1,i2,num; void** ak; void** a1; void** a2; void* aa;

    num=hp->ZZds.ZZselectArr.num;
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
            (*callback)(&(hp->ZZds.ZZselectArr.array[i1]),i1);
            (*callback)(&(hp->ZZds.ZZselectArr.array[k]),k);
        }
    }
}

// --------------------------------------------------------------
// Update heap when the value associated with entry n has changed
// --------------------------------------------------------------
void selectArr_Array::updHeap(cmpType cmpF,Layout *hp,int n,bck callback){
    int num,n1,n2;

    num=hp->ZZds.ZZselectArr.num;
    if(n<0 || n>num){
        printf("error updating heap=selectArr, n=%d num=%d\n",n,num);
        return;
    }
    downHeap(cmpF,hp,n,callback);
    upHeap(cmpF,hp,n,callback);
}

// --------------------------------------------------------------
// Delete item index n from the heap.
// --------------------------------------------------------------
void selectArr_Array::delHeap(cmpType cmpF,Layout *hp,int n,bck callback){
    int num; void** arr;

    num=hp->ZZds.ZZselectArr.num;
    arr=hp->ZZds.ZZselectArr.array;
    if(n<0 || n>num){
        printf("error deleting from heap=selectArr, n=%d num=%d\n",n,num);
        return;
    }
    (hp->ZZds.ZZselectArr.num)--;
    if(callback) (*callback)(&(hp->ZZds.ZZselectArr.array[num]),-1);
    if(n==num) return;
    arr[n]=arr[num];
    if(callback) (*callback)(&(hp->ZZds.ZZselectArr.array[n]),n);
    updHeap(cmpF,hp,n,callback);
}

// --------------------------------------------------------------
// Same function as ind() but providing a callback function.
// This function is needed when relocating heaps automatically.
// --------------------------------------------------------------
void** selectArr_Array::indHeap(Layout *hp,int i,bck callback){
    int k,num,sz;
    void* *elem;

    num=hp->ZZds.ZZselectArr.num;
    sz=hp->ZZds.ZZselectArr.sz;
    elem=ind(hp,i);
    if(!elem)return NULL;
    // report changes of position when re-allocating
    if(i>=sz){
        for(k=0; k<num; k++){
            if(callback) (*callback)(&(hp->ZZds.ZZselectArr.array[k]),k);
        }
    }
    return elem;
}
// --------------------------------------------------------------


int selectArr_Array::formed(Layout *hp){ if(hp->ZZds.ZZselectArr.array)return 1; return 0;}

void selectArr_Array::free(Layout *hp){ 
    if(hp->ZZds.ZZselectArr.array){
        delete[] hp->ZZds.ZZselectArr.array;
        hp->ZZds.ZZselectArr.array=NULL;
    }
    hp->ZZds.ZZselectArr.num= -1;
    hp->ZZds.ZZselectArr.sz=0;
}

unsigned int selectArr_Array::capacity(Layout *hp) {return hp->ZZds.ZZselectArr.sz;} 

unsigned int selectArr_Array::size(Layout *hp) {return (unsigned int)(hp->ZZds.ZZselectArr.num + 1);} 

int selectArr_Array::increment(Layout *hp) {return hp->ZZds.ZZselectArr.incr;} 

void* selectArr_Array::get(Layout *hp,const unsigned int k){  // a=array[k]
    int kk=k;
    if(kk>=hp->ZZds.ZZselectArr.sz)sizeChange(hp,kk+1,0);
    if(kk>hp->ZZds.ZZselectArr.num)hp->ZZds.ZZselectArr.num=kk;
    return hp->ZZds.ZZselectArr.array[kk];
}

void selectArr_Array::set(Layout *hp,const unsigned int k,void* a){ // array[k]=a
    int kk=k;
    if(kk>=hp->ZZds.ZZselectArr.sz)sizeChange(hp,kk+1,0);
    if(kk>hp->ZZds.ZZselectArr.num)hp->ZZds.ZZselectArr.num=kk;
    hp->ZZds.ZZselectArr.array[kk]=a;
}
void selectArr_Array::remove(Layout *hp,const unsigned int k){ // fast but order changed
    int kk=k;
    int num=hp->ZZds.ZZselectArr.num;
    if(kk<num){hp->ZZds.ZZselectArr.array[k]=hp->ZZds.ZZselectArr.array[num]; (hp->ZZds.ZZselectArr.num)--;}
}
int selectArr_Array::reduce(Layout *hp){             // reduce the array to its used size
    return sizeChange(hp,hp->ZZds.ZZselectArr.num+1,1);
}
int selectArr_Array::reduce(Layout *hp,const unsigned int newCap){ // reduce size to newSz
    if(newCap>=hp->ZZds.ZZselectArr.sz)return hp->ZZds.ZZselectArr.sz;
    return sizeChange(hp,newCap,1);
} 
int selectArr_Array::grow(Layout *hp,const unsigned int newCap){
    return sizeChange(hp,newCap,0);
} 
void selectArr_Array::push(Layout *hp,void** e){
    unsigned int num,sz;

    num=hp->ZZds.ZZselectArr.num+1; sz=hp->ZZds.ZZselectArr.sz;
    if(num>=sz)sizeChange(hp,num+1,0);
    hp->ZZds.ZZselectArr.array[num]=(*e); (hp->ZZds.ZZselectArr.num)++;
}
void** selectArr_Array::pop(Layout *hp){void** e=NULL; int num=hp->ZZds.ZZselectArr.num;
    if(num>=0){e= &(hp->ZZds.ZZselectArr.array[num]); (hp->ZZds.ZZselectArr.num)--;}
    return e;
}
void selectArr_Array::reset(Layout *hp,int newSz,int incr){
    hp->ZZds.ZZselectArr.num=newSz-1; hp->ZZds.ZZselectArr.incr=incr;
}

// -----------------------------------------------------------------------
// Add a new object into the ordered collection. This is relatively
// fast using binary search to find the position, but a section of
// the array must move to open one slot.
// -----------------------------------------------------------------------
void selectArr_Array::addOrd(cmpType cmpF,Layout *hp,void* *op){
    int k,found;

    if(hp->ZZds.ZZselectArr.num<0)k=0;
    else k=binSearch(cmpF,hp,op,&found);
    insert(hp,k,op); // insert even if the same key is already there
}

// -----------------------------------------------------------------------
// Find the given object in the sorted array (using binary search0
// and remove it from the array without changing the order of the remaining
// elements.
// -----------------------------------------------------------------------
void selectArr_Array::delOrd(cmpType cmpF,Layout *hp,void* *obj){
    int k,found;

    k=binSearch(cmpF,hp,obj,&found);
    if(found) delOrd(cmpF,hp,k);
    else printf("warning: calling selectArr::delOrd() but object not there\n");
}


// -----------------------------------------------------------------------
// Binary search, returns the index of the object with the same key as op
// or the first object with the higher key than that.
// In case of any error, e.g. when the array has not been formed yet, 
// the function generates an error message and returns -1.
// -----------------------------------------------------------------------
int selectArr_Array::binSearch(cmpType cmpF,Layout *hp,void* *op,int *found){
    int i1,i2,k,cmp,num; void** rr; void** arr;

    arr=hp->ZZds.ZZselectArr.array;
    num=hp->ZZds.ZZselectArr.num;
    if(!arr || num<0){
        printf("selectArr error in binSearch(): array not formed or empty\n");
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
int selectArr_Array::getBit(Layout *hp,int i){
    int iChar,iBit,sz,k,newBytes; void** ap; unsigned char *p,b;

    sz=sizeof(void*) * hp->ZZds.ZZselectArr.sz; // sz is size in bytes
    if(i>=sz*8){ // sz*8 is the size in bits
        ap=ind(hp,i/(8*sizeof(void*)));
        if(!ap){
            printf("selectArr error: cannot realocate for %d bits\n",i);
            return -1;
        }

        // initialize the new part of the array to 0
        newBytes=sizeof(void*)*hp->ZZds.ZZselectArr.sz;
        p=(unsigned char*)(hp->ZZds.ZZselectArr.array);
        for(k=sz; k<newBytes; k++) p[k]=0;
    }
    else if(hp->ZZds.ZZselectArr.num<0){ // first call, initialize all bits to 0
        p=(unsigned char*)(hp->ZZds.ZZselectArr.array);
        for(k=0; k<sz; k++) p[k]=0;
    }

    k=i/(8*sizeof(void*)); // object index in which bit i is
    if(hp->ZZds.ZZselectArr.num < k)hp->ZZds.ZZselectArr.num=k;

    p=(unsigned char*)(hp->ZZds.ZZselectArr.array);
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
int selectArr_Array::setBit(Layout *hp,int i,int val){
    int iChar,iBit,sz,k,newBytes; void** ap; unsigned char *p,b;

    sz=sizeof(void*) * hp->ZZds.ZZselectArr.sz; // sz is size in bytes
    if(i>=sz*8){ // sz*8 is the size in bits
        ap=ind(hp,i/(8*sizeof(void*)));
        if(!ap){
            printf("selectArr error: cannot realocate for %d bits\n",i);
            return -1;
        }

        // initialize the new part of the array to 0
        newBytes=sizeof(void*)*hp->ZZds.ZZselectArr.sz;
        p=(unsigned char*)(hp->ZZds.ZZselectArr.array);
        for(k=sz; k<newBytes; k++) p[k]=0;
    }
    else if(hp->ZZds.ZZselectArr.num<0){ // first call, initialize all bits to 0
        p=(unsigned char*)(hp->ZZds.ZZselectArr.array);
        for(k=0; k<sz; k++) p[k]=0;
    }

    k=i/(8*sizeof(void*)); // object index in which bit i is
    if(hp->ZZds.ZZselectArr.num < k)hp->ZZds.ZZselectArr.num=k;

    p=(unsigned char*)(hp->ZZds.ZZselectArr.array);
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
int selectArr_Array::getOrd(cmpType cmpF,Layout *hp,void* *op,int *found){
    int k=binSearch(cmpF,hp,op,found);
    return k;
}



