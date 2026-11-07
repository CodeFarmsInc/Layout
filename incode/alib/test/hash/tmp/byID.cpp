#include <stdlib.h>
// --------------------------------------------------------
unsigned int byID_Array::maxCapacity=0;

// --------------------------------------------------------------
// Remove the entry from the array, and shrink the remaining part
// of the array. This changes 'num' and indexes of all entries
// above this index.
// See array.h for method remove() which is much faster but changes
// the order of the array.
// --------------------------------------------------------------
void byID_Array::extract(Company *hp, const int k){
    int j,num;

    num=hp->ZZds.ZZbyID.num;
    if(k>num)return; // nothing to do
    if(k==num){hp->ZZds.ZZbyID.num=num-1; return;}
    for(j=k+1; j<=num; j++)hp->ZZds.ZZbyID.array[j-1]=hp->ZZds.ZZbyID.array[j];
    hp->ZZds.ZZbyID.num=num-1;
}

// --------------------------------------------------------------
// Insert the entry into the array[k], and expand the remaining part
// of the array. This changes 'num' and indexes of all entries
// above this index. 
// --------------------------------------------------------------
void byID_Array::insert(Company *hp,const int k,void* *t){
    int j,kk,oldNum,newNum,sz;

    if(k<0)kk=0; else kk=k;
    oldNum=hp->ZZds.ZZbyID.num;
    sz=hp->ZZds.ZZbyID.sz;
    if(kk>oldNum) newNum=kk; else newNum=oldNum+1;
    if(newNum>=sz){
        (void)sizeChange(hp,newNum+1,0);
    }
    for(j=oldNum; j>=kk; j--) hp->ZZds.ZZbyID.array[j+1]=hp->ZZds.ZZbyID.array[j];
    hp->ZZds.ZZbyID.array[kk]=(*t);
    hp->ZZds.ZZbyID.num=newNum;
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
int byID_Array::sizeChange(Company *hp,const unsigned int newCap,const int exact){
    void** a; void** arr;
    int nCap,j,s,sn,cap,num,incr;

    nCap=newCap;
    arr=hp->ZZds.ZZbyID.array;
    cap=hp->ZZds.ZZbyID.sz;
    num=hp->ZZds.ZZbyID.num;
    incr=hp->ZZds.ZZbyID.incr;

    if(incr==0 && !exact){
    printf("error for byID: attempt to change a fixed array into flexible one\n");
    return 1;
    }
    if(!arr){
        printf("error for byID: cannot modify capacity, array not formed\n");
        return 1;
    }

    if(nCap==cap)return 0; // nothing to do
    if(maxCapacity>0 && nCap>maxCapacity){
        printf("error for byID: requested capacity=%d, maxCapacity=%d\n",
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
        printf("error for byID: failed to allocate array capacity=%d\n",s);
        return 1;
    }

    if(s<=num)sn=s-1; else sn=num;
    for(j=0; j<=sn; j++)a[j]=arr[j];
    delete[] arr;
    hp->ZZds.ZZbyID.array=a;
    hp->ZZds.ZZbyID.sz=s;
    if(num>=s)hp->ZZds.ZZbyID.num=s-1;

    return 0;
}

// --------------------------------------------------------------
// Create array of pointers with the initial size s
// Returns: Returs the array, NULL when the allocation fails
// --------------------------------------------------------------
void** byID_Array::form(Company *hp,unsigned int const sz,int const incr){
    if(hp->ZZds.ZZbyID.array)free(hp);

    hp->ZZds.ZZbyID.array=new void*[sz];
    if(!hp->ZZds.ZZbyID.array){
        printf("byID error, cannot allocate array size=%d\n",sz);
        return NULL;
    }
    hp->ZZds.ZZbyID.sz=sz;
    hp->ZZds.ZZbyID.num= -1;
    hp->ZZds.ZZbyID.incr=incr;
    return hp->ZZds.ZZbyID.array;
}

// --------------------------------------------------------------
// Sort the array by applying qsort with function cmp that compares
// two objects. Only the section of the array which is used will be
// sorted.
// --------------------------------------------------------------
void byID_Array::sort(cmpType cmp,Company *hp){
    if(hp->ZZds.ZZbyID.num<=0)return; // no need to sort 0 or 1 item
    qsort(hp->ZZds.ZZbyID.array,hp->ZZds.ZZbyID.num+1,sizeof(void*),cmp);
}
void byID_Array::sortSubset(cmpType cmp,Company *hp,int i1,int i2){
    if(i2>hp->ZZds.ZZbyID.num){
        printf("warning: upper range of sortSubset() automatically adjusted ");
        printf("from=%d to %d\n",i2,hp->ZZds.ZZbyID.num);
        i2=hp->ZZds.ZZbyID.num;
    }
    qsort(&(hp->ZZds.ZZbyID.array[i1]),i2-i1+1,sizeof(void*),cmp);
}

// --------------------------------------------------------------
// Return pointer to the element[i] of the array.
// WARNING: The pointer thus obtained must be used either immediately,
//          or when we are absolutely sure that the array will not 
//          automatically re-allocate, for example when working with
//          a fixed array (incr=0).
// --------------------------------------------------------------
void** byID_Array::ind(Company *hp,int i){
    if(!(hp->ZZds.ZZbyID.array)){
        printf("error for byID: index operation attempted before formed\n");
        return NULL;
    }
    if(i>=hp->ZZds.ZZbyID.sz){
        if(sizeChange(hp,i+1,0))return NULL; // error message inside there
    }
    if(hp->ZZds.ZZbyID.num<i)hp->ZZds.ZZbyID.num=i;
    return &(hp->ZZds.ZZbyID.array[i]);
}

// --------------------------------------------------------------
// Fast way of getting ind[0]
// --------------------------------------------------------------
void** byID_Array::head(Company *hp){
    return (void**)(hp->ZZds.ZZbyID.array);
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
void byID_Array::inHeap(cmpType cmpF,Company *hp,void* *e,bck callback){
    int i; void** newE;

    i=hp->ZZds.ZZbyID.num + 1;
    newE=indHeap(hp,i,callback);
    if(!newE)return;
    (*newE)=(*e);
    if(callback) (*callback)(&(hp->ZZds.ZZbyID.array[i]),i);
    if(i>1)upHeap(cmpF,hp,i,callback);
}

// --------------------------------------------------------------
// Assuming a new element in location n, re-sort the heap proceeding
// from n to all its ascendents.
// --------------------------------------------------------------
void byID_Array::upHeap(cmpType cmpF,Company *hp,int n,bck callback){
    int i1,i2; void** a1; void** a2; void* aa;

    if(n==0)return;
    // traverse the ascendants
    for(i1=n, i2=(n-1)/2, a1=ind(hp,n); i1>0; i1=i2, i2=(i2-1)/2, a1=a2){
        a2=ind(hp,i2);
        if(cmpF(a2,a1)<=0)break;
        // exchange the contents of a1 and a2
        aa=(*a1); (*a1)=(*a2); (*a2)=aa;
        if(callback){
            (*callback)(&(hp->ZZds.ZZbyID.array[i1]),i1);
            (*callback)(&(hp->ZZds.ZZbyID.array[i2]),i2);
        }
    }
}

// --------------------------------------------------------------
// Return the top of the heap in e, and remove it from the heap.
// Return 1 when successful, return 0 when the heap is empty
// --------------------------------------------------------------
int byID_Array::outHeap(cmpType cmpF,Company *hp,void** e,bck callback){
    int num;

    num=hp->ZZds.ZZbyID.num;
    if(num<0) return 0;
    (*e)=hp->ZZds.ZZbyID.array[0];
    if(callback) (*callback)(&(hp->ZZds.ZZbyID.array[0]),-1);
    if(num>0){
       hp->ZZds.ZZbyID.array[0]=hp->ZZds.ZZbyID.array[num];
       if(callback) (*callback)(&(hp->ZZds.ZZbyID.array[0]),0);
       downHeap(cmpF,hp,0,callback);
    }
    (hp->ZZds.ZZbyID.num)--;
    return 1;
}


// --------------------------------------------------------------
// Assuming a new element in location n, re-sort the heap proceeding
// from n to all its descendents.
// --------------------------------------------------------------
void byID_Array::downHeap(cmpType cmpF,Company *hp,int n,bck callback){
    int k,i1,i2,num; void** ak; void** a1; void** a2; void* aa;

    num=hp->ZZds.ZZbyID.num;
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
            (*callback)(&(hp->ZZds.ZZbyID.array[i1]),i1);
            (*callback)(&(hp->ZZds.ZZbyID.array[k]),k);
        }
    }
}

// --------------------------------------------------------------
// Update heap when the value associated with entry n has changed
// --------------------------------------------------------------
void byID_Array::updHeap(cmpType cmpF,Company *hp,int n,bck callback){
    int num,n1,n2;

    num=hp->ZZds.ZZbyID.num;
    if(n<0 || n>num){
        printf("error updating heap=byID, n=%d num=%d\n",n,num);
        return;
    }
    downHeap(cmpF,hp,n,callback);
    upHeap(cmpF,hp,n,callback);
}

// --------------------------------------------------------------
// Delete item index n from the heap.
// --------------------------------------------------------------
void byID_Array::delHeap(cmpType cmpF,Company *hp,int n,bck callback){
    int num; void** arr;

    num=hp->ZZds.ZZbyID.num;
    arr=hp->ZZds.ZZbyID.array;
    if(n<0 || n>num){
        printf("error deleting from heap=byID, n=%d num=%d\n",n,num);
        return;
    }
    (hp->ZZds.ZZbyID.num)--;
    if(callback) (*callback)(&(hp->ZZds.ZZbyID.array[num]),-1);
    if(n==num) return;
    arr[n]=arr[num];
    if(callback) (*callback)(&(hp->ZZds.ZZbyID.array[n]),n);
    updHeap(cmpF,hp,n,callback);
}

// --------------------------------------------------------------
// Same function as ind() but providing a callback function.
// This function is needed when relocating heaps automatically.
// --------------------------------------------------------------
void** byID_Array::indHeap(Company *hp,int i,bck callback){
    int k,num,sz;
    void* *elem;

    num=hp->ZZds.ZZbyID.num;
    sz=hp->ZZds.ZZbyID.sz;
    elem=ind(hp,i);
    if(!elem)return NULL;
    // report changes of position when re-allocating
    if(i>=sz){
        for(k=0; k<num; k++){
            if(callback) (*callback)(&(hp->ZZds.ZZbyID.array[k]),k);
        }
    }
    return elem;
}
// --------------------------------------------------------------


int byID_Array::formed(Company *hp){ if(hp->ZZds.ZZbyID.array)return 1; return 0;}

void byID_Array::free(Company *hp){ 
    if(hp->ZZds.ZZbyID.array){
        delete[] hp->ZZds.ZZbyID.array;
        hp->ZZds.ZZbyID.array=NULL;
    }
    hp->ZZds.ZZbyID.num= -1;
    hp->ZZds.ZZbyID.sz=0;
}

unsigned int byID_Array::capacity(Company *hp) {return hp->ZZds.ZZbyID.sz;} 

unsigned int byID_Array::size(Company *hp) {return (unsigned int)(hp->ZZds.ZZbyID.num + 1);} 

int byID_Array::increment(Company *hp) {return hp->ZZds.ZZbyID.incr;} 

void* byID_Array::get(Company *hp,const unsigned int k){  // a=array[k]
    int kk=k;
    if(kk>=hp->ZZds.ZZbyID.sz)sizeChange(hp,kk+1,0);
    if(kk>hp->ZZds.ZZbyID.num)hp->ZZds.ZZbyID.num=kk;
    return hp->ZZds.ZZbyID.array[kk];
}

void byID_Array::set(Company *hp,const unsigned int k,void* a){ // array[k]=a
    int kk=k;
    if(kk>=hp->ZZds.ZZbyID.sz)sizeChange(hp,kk+1,0);
    if(kk>hp->ZZds.ZZbyID.num)hp->ZZds.ZZbyID.num=kk;
    hp->ZZds.ZZbyID.array[kk]=a;
}
void byID_Array::remove(Company *hp,const unsigned int k){ // fast but order changed
    int kk=k;
    int num=hp->ZZds.ZZbyID.num;
    if(kk<num){hp->ZZds.ZZbyID.array[k]=hp->ZZds.ZZbyID.array[num]; (hp->ZZds.ZZbyID.num)--;}
}
int byID_Array::reduce(Company *hp){             // reduce the array to its used size
    return sizeChange(hp,hp->ZZds.ZZbyID.num+1,1);
}
int byID_Array::reduce(Company *hp,const unsigned int newCap){ // reduce size to newSz
    if(newCap>=hp->ZZds.ZZbyID.sz)return hp->ZZds.ZZbyID.sz;
    return sizeChange(hp,newCap,1);
} 
int byID_Array::grow(Company *hp,const unsigned int newCap){
    return sizeChange(hp,newCap,0);
} 
void byID_Array::push(Company *hp,void** e){
    unsigned int num,sz;

    num=hp->ZZds.ZZbyID.num+1; sz=hp->ZZds.ZZbyID.sz;
    if(num>=sz)sizeChange(hp,num+1,0);
    hp->ZZds.ZZbyID.array[num]=(*e); (hp->ZZds.ZZbyID.num)++;
}
void** byID_Array::pop(Company *hp){void** e=NULL; int num=hp->ZZds.ZZbyID.num;
    if(num>=0){e= &(hp->ZZds.ZZbyID.array[num]); (hp->ZZds.ZZbyID.num)--;}
    return e;
}
void byID_Array::reset(Company *hp,int newSz,int incr){
    hp->ZZds.ZZbyID.num=newSz-1; hp->ZZds.ZZbyID.incr=incr;
}

// -----------------------------------------------------------------------
// Add a new object into the ordered collection. This is relatively
// fast using binary search to find the position, but a section of
// the array must move to open one slot.
// -----------------------------------------------------------------------
void byID_Array::addOrd(cmpType cmpF,Company *hp,void* *op){
    int k,found;

    if(hp->ZZds.ZZbyID.num<0)k=0;
    else k=binSearch(cmpF,hp,op,&found);
    insert(hp,k,op); // insert even if the same key is already there
}

// -----------------------------------------------------------------------
// Find the given object in the sorted array (using binary search0
// and remove it from the array without changing the order of the remaining
// elements.
// -----------------------------------------------------------------------
void byID_Array::delOrd(cmpType cmpF,Company *hp,void* *obj){
    int k,found;

    k=binSearch(cmpF,hp,obj,&found);
    if(found) delOrd(cmpF,hp,k);
    else printf("warning: calling byID::delOrd() but object not there\n");
}


// -----------------------------------------------------------------------
// Binary search, returns the index of the object with the same key as op
// or the first object with the higher key than that.
// In case of any error, e.g. when the array has not been formed yet, 
// the function generates an error message and returns -1.
// -----------------------------------------------------------------------
int byID_Array::binSearch(cmpType cmpF,Company *hp,void* *op,int *found){
    int i1,i2,k,cmp,num; void** rr; void** arr;

    arr=hp->ZZds.ZZbyID.array;
    num=hp->ZZds.ZZbyID.num;
    if(!arr || num<0){
        printf("byID error in binSearch(): array not formed or empty\n");
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
int byID_Array::getBit(Company *hp,int i){
    int iChar,iBit,sz,k,newBytes; void** ap; unsigned char *p,b;

    sz=sizeof(void*) * hp->ZZds.ZZbyID.sz; // sz is size in bytes
    if(i>=sz*8){ // sz*8 is the size in bits
        ap=ind(hp,i/(8*sizeof(void*)));
        if(!ap){
            printf("byID error: cannot realocate for %d bits\n",i);
            return -1;
        }

        // initialize the new part of the array to 0
        newBytes=sizeof(void*)*hp->ZZds.ZZbyID.sz;
        p=(unsigned char*)(hp->ZZds.ZZbyID.array);
        for(k=sz; k<newBytes; k++) p[k]=0;
    }
    else if(hp->ZZds.ZZbyID.num<0){ // first call, initialize all bits to 0
        p=(unsigned char*)(hp->ZZds.ZZbyID.array);
        for(k=0; k<sz; k++) p[k]=0;
    }

    k=i/(8*sizeof(void*)); // object index in which bit i is
    if(hp->ZZds.ZZbyID.num < k)hp->ZZds.ZZbyID.num=k;

    p=(unsigned char*)(hp->ZZds.ZZbyID.array);
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
int byID_Array::setBit(Company *hp,int i,int val){
    int iChar,iBit,sz,k,newBytes; void** ap; unsigned char *p,b;

    sz=sizeof(void*) * hp->ZZds.ZZbyID.sz; // sz is size in bytes
    if(i>=sz*8){ // sz*8 is the size in bits
        ap=ind(hp,i/(8*sizeof(void*)));
        if(!ap){
            printf("byID error: cannot realocate for %d bits\n",i);
            return -1;
        }

        // initialize the new part of the array to 0
        newBytes=sizeof(void*)*hp->ZZds.ZZbyID.sz;
        p=(unsigned char*)(hp->ZZds.ZZbyID.array);
        for(k=sz; k<newBytes; k++) p[k]=0;
    }
    else if(hp->ZZds.ZZbyID.num<0){ // first call, initialize all bits to 0
        p=(unsigned char*)(hp->ZZds.ZZbyID.array);
        for(k=0; k<sz; k++) p[k]=0;
    }

    k=i/(8*sizeof(void*)); // object index in which bit i is
    if(hp->ZZds.ZZbyID.num < k)hp->ZZds.ZZbyID.num=k;

    p=(unsigned char*)(hp->ZZds.ZZbyID.array);
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
int byID_Array::getOrd(cmpType cmpF,Company *hp,void* *op,int *found){
    int k=binSearch(cmpF,hp,op,found);
    return k;
}



