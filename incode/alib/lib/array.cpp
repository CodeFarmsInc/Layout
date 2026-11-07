#include <stdlib.h>
// --------------------------------------------------------
unsigned int $$_Array::maxCapacity=0;

// --------------------------------------------------------------
// Remove the entry from the array, and shrink the remaining part
// of the array. This changes 'num' and indexes of all entries
// above this index.
// See array.h for method remove() which is much faster but changes
// the order of the array.
// --------------------------------------------------------------
void $$_Array::extract($1 *hp, const int k){
    int j,num;

    num=hp->$0.num;
    if(k>num)return; // nothing to do
    if(k==num){hp->$0.num=num-1; return;}
    for(j=k+1; j<=num; j++)hp->$0.array[j-1]=hp->$0.array[j];
    hp->$0.num=num-1;
}

// --------------------------------------------------------------
// Insert the entry into the array[k], and expand the remaining part
// of the array. This changes 'num' and indexes of all entries
// above this index. 
// --------------------------------------------------------------
void $$_Array::insert($1 *hp,const int k,$2 *t){
    int j,kk,oldNum,newNum,sz;

    if(k<0)kk=0; else kk=k;
    oldNum=hp->$0.num;
    sz=hp->$0.sz;
    if(kk>oldNum) newNum=kk; else newNum=oldNum+1;
    if(newNum>=sz){
        (void)sizeChange(hp,newNum+1,0);
    }
    for(j=oldNum; j>=kk; j--) hp->$0.array[j+1]=hp->$0.array[j];
    hp->$0.array[kk]=(*t);
    hp->$0.num=newNum;
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
int $$_Array::sizeChange($1 *hp,const unsigned int newCap,const int exact){
    $2* a; $2* arr;
    int nCap,j,s,sn,cap,num,incr;

    nCap=newCap;
    arr=hp->$0.array;
    cap=hp->$0.sz;
    num=hp->$0.num;
    incr=hp->$0.incr;

    if(incr==0 && !exact){
    printf("error for $$: attempt to change a fixed array into flexible one\n");
    return 1;
    }
    if(!arr){
        printf("error for $$: cannot modify capacity, array not formed\n");
        return 1;
    }

    if(nCap==cap)return 0; // nothing to do
    if(maxCapacity>0 && nCap>maxCapacity){
        printf("error for $$: requested capacity=%d, maxCapacity=%d\n",
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

    a=new $2[s];
    if(!a){
        printf("error for $$: failed to allocate array capacity=%d\n",s);
        return 1;
    }

    if(s<=num)sn=s-1; else sn=num;
    for(j=0; j<=sn; j++)a[j]=arr[j];
    delete[] arr;
    hp->$0.array=a;
    hp->$0.sz=s;
    if(num>=s)hp->$0.num=s-1;

    return 0;
}

// --------------------------------------------------------------
// Create array of pointers with the initial size s
// Returns: Returs the array, NULL when the allocation fails
// --------------------------------------------------------------
$2* $$_Array::form($1 *hp,unsigned int const sz,int const incr){
    if(hp->$0.array)free(hp);

    hp->$0.array=new $2[sz];
    if(!hp->$0.array){
        printf("$$ error, cannot allocate array size=%d\n",sz);
        return NULL;
    }
    hp->$0.sz=sz;
    hp->$0.num= -1;
    hp->$0.incr=incr;
    return hp->$0.array;
}

// --------------------------------------------------------------
// Sort the array by applying qsort with function cmp that compares
// two objects. Only the section of the array which is used will be
// sorted.
// --------------------------------------------------------------
void $$_Array::sort(cmpType cmp,$1 *hp){
    if(hp->$0.num<=0)return; // no need to sort 0 or 1 item
    qsort(hp->$0.array,hp->$0.num+1,sizeof($2),cmp);
}
void $$_Array::sortSubset(cmpType cmp,$1 *hp,int i1,int i2){
    if(i2>hp->$0.num){
        printf("warning: upper range of sortSubset() automatically adjusted ");
        printf("from=%d to %d\n",i2,hp->$0.num);
        i2=hp->$0.num;
    }
    qsort(&(hp->$0.array[i1]),i2-i1+1,sizeof($2),cmp);
}

// --------------------------------------------------------------
// Return pointer to the element[i] of the array.
// WARNING: The pointer thus obtained must be used either immediately,
//          or when we are absolutely sure that the array will not 
//          automatically re-allocate, for example when working with
//          a fixed array (incr=0).
// --------------------------------------------------------------
$2* $$_Array::ind($1 *hp,int i){
    if(!(hp->$0.array)){
        printf("error for $$: index operation attempted before formed\n");
        return NULL;
    }
    if(i>=hp->$0.sz){
        if(sizeChange(hp,i+1,0))return NULL; // error message inside there
    }
    if(hp->$0.num<i)hp->$0.num=i;
    return &(hp->$0.array[i]);
}

// --------------------------------------------------------------
// Fast way of getting ind[0]
// --------------------------------------------------------------
$2* $$_Array::head($1 *hp){
    return ($2*)(hp->$0.array);
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
void $$_Array::inHeap(cmpType cmpF,$1 *hp,$2 *e,bck callback){
    int i; $2* newE;

    i=hp->$0.num + 1;
    newE=indHeap(hp,i,callback);
    if(!newE)return;
    (*newE)=(*e);
    if(callback) (*callback)(&(hp->$0.array[i]),i);
    if(i>1)upHeap(cmpF,hp,i,callback);
}

// --------------------------------------------------------------
// Assuming a new element in location n, re-sort the heap proceeding
// from n to all its ascendents.
// --------------------------------------------------------------
void $$_Array::upHeap(cmpType cmpF,$1 *hp,int n,bck callback){
    int i1,i2; $2* a1; $2* a2; $2 aa;

    if(n==0)return;
    // traverse the ascendants
    for(i1=n, i2=(n-1)/2, a1=ind(hp,n); i1>0; i1=i2, i2=(i2-1)/2, a1=a2){
        a2=ind(hp,i2);
        if(cmpF(a2,a1)<=0)break;
        // exchange the contents of a1 and a2
        aa=(*a1); (*a1)=(*a2); (*a2)=aa;
        if(callback){
            (*callback)(&(hp->$0.array[i1]),i1);
            (*callback)(&(hp->$0.array[i2]),i2);
        }
    }
}

// --------------------------------------------------------------
// Return the top of the heap in e, and remove it from the heap.
// Return 1 when successful, return 0 when the heap is empty
// --------------------------------------------------------------
int $$_Array::outHeap(cmpType cmpF,$1 *hp,$2* e,bck callback){
    int num;

    num=hp->$0.num;
    if(num<0) return 0;
    (*e)=hp->$0.array[0];
    if(callback) (*callback)(&(hp->$0.array[0]),-1);
    if(num>0){
       hp->$0.array[0]=hp->$0.array[num];
       if(callback) (*callback)(&(hp->$0.array[0]),0);
       downHeap(cmpF,hp,0,callback);
    }
    (hp->$0.num)--;
    return 1;
}


// --------------------------------------------------------------
// Assuming a new element in location n, re-sort the heap proceeding
// from n to all its descendents.
// --------------------------------------------------------------
void $$_Array::downHeap(cmpType cmpF,$1 *hp,int n,bck callback){
    int k,i1,i2,num; $2* ak; $2* a1; $2* a2; $2 aa;

    num=hp->$0.num;
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
            (*callback)(&(hp->$0.array[i1]),i1);
            (*callback)(&(hp->$0.array[k]),k);
        }
    }
}

// --------------------------------------------------------------
// Update heap when the value associated with entry n has changed
// --------------------------------------------------------------
void $$_Array::updHeap(cmpType cmpF,$1 *hp,int n,bck callback){
    int num,n1,n2;

    num=hp->$0.num;
    if(n<0 || n>num){
        printf("error updating heap=$$, n=%d num=%d\n",n,num);
        return;
    }
    downHeap(cmpF,hp,n,callback);
    upHeap(cmpF,hp,n,callback);
}

// --------------------------------------------------------------
// Delete item index n from the heap.
// --------------------------------------------------------------
void $$_Array::delHeap(cmpType cmpF,$1 *hp,int n,bck callback){
    int num; $2* arr;

    num=hp->$0.num;
    arr=hp->$0.array;
    if(n<0 || n>num){
        printf("error deleting from heap=$$, n=%d num=%d\n",n,num);
        return;
    }
    (hp->$0.num)--;
    if(callback) (*callback)(&(hp->$0.array[num]),-1);
    if(n==num) return;
    arr[n]=arr[num];
    if(callback) (*callback)(&(hp->$0.array[n]),n);
    updHeap(cmpF,hp,n,callback);
}

// --------------------------------------------------------------
// Same function as ind() but providing a callback function.
// This function is needed when relocating heaps automatically.
// --------------------------------------------------------------
$2* $$_Array::indHeap($1 *hp,int i,bck callback){
    int k,num,sz;
    $2 *elem;

    num=hp->$0.num;
    sz=hp->$0.sz;
    elem=ind(hp,i);
    if(!elem)return NULL;
    // report changes of position when re-allocating
    if(i>=sz){
        for(k=0; k<num; k++){
            if(callback) (*callback)(&(hp->$0.array[k]),k);
        }
    }
    return elem;
}
// --------------------------------------------------------------


int $$_Array::formed($1 *hp){ if(hp->$0.array)return 1; return 0;}

void $$_Array::free($1 *hp){ 
    if(hp->$0.array){
        delete[] hp->$0.array;
        hp->$0.array=NULL;
    }
    hp->$0.num= -1;
    hp->$0.sz=0;
}

unsigned int $$_Array::capacity($1 *hp) {return hp->$0.sz;} 

unsigned int $$_Array::size($1 *hp) {return (unsigned int)(hp->$0.num + 1);} 

int $$_Array::increment($1 *hp) {return hp->$0.incr;} 

$2 $$_Array::get($1 *hp,const unsigned int k){  // a=array[k]
    int kk=k;
    if(kk>=hp->$0.sz)sizeChange(hp,kk+1,0);
    if(kk>hp->$0.num)hp->$0.num=kk;
    return hp->$0.array[kk];
}

void $$_Array::set($1 *hp,const unsigned int k,$2 a){ // array[k]=a
    int kk=k;
    if(kk>=hp->$0.sz)sizeChange(hp,kk+1,0);
    if(kk>hp->$0.num)hp->$0.num=kk;
    hp->$0.array[kk]=a;
}
void $$_Array::remove($1 *hp,const unsigned int k){ // fast but order changed
    int kk=k;
    int num=hp->$0.num;
    if(kk<num){hp->$0.array[k]=hp->$0.array[num]; (hp->$0.num)--;}
}
int $$_Array::reduce($1 *hp){             // reduce the array to its used size
    return sizeChange(hp,hp->$0.num+1,1);
}
int $$_Array::reduce($1 *hp,const unsigned int newCap){ // reduce size to newSz
    if(newCap>=hp->$0.sz)return hp->$0.sz;
    return sizeChange(hp,newCap,1);
} 
int $$_Array::grow($1 *hp,const unsigned int newCap){
    return sizeChange(hp,newCap,0);
} 
void $$_Array::push($1 *hp,$2* e){
    unsigned int num,sz;

    num=hp->$0.num+1; sz=hp->$0.sz;
    if(num>=sz)sizeChange(hp,num+1,0);
    hp->$0.array[num]=(*e); (hp->$0.num)++;
}
$2* $$_Array::pop($1 *hp){$2* e=NULL; int num=hp->$0.num;
    if(num>=0){e= &(hp->$0.array[num]); (hp->$0.num)--;}
    return e;
}
void $$_Array::reset($1 *hp,int newSz,int incr){
    hp->$0.num=newSz-1; hp->$0.incr=incr;
}

// -----------------------------------------------------------------------
// Add a new object into the ordered collection. This is relatively
// fast using binary search to find the position, but a section of
// the array must move to open one slot.
// -----------------------------------------------------------------------
void $$_Array::addOrd(cmpType cmpF,$1 *hp,$2 *op){
    int k,found;

    if(hp->$0.num<0)k=0;
    else k=binSearch(cmpF,hp,op,&found);
    insert(hp,k,op); // insert even if the same key is already there
}

// -----------------------------------------------------------------------
// Find the given object in the sorted array (using binary search0
// and remove it from the array without changing the order of the remaining
// elements.
// -----------------------------------------------------------------------
void $$_Array::delOrd(cmpType cmpF,$1 *hp,$2 *obj){
    int k,found;

    k=binSearch(cmpF,hp,obj,&found);
    if(found) delOrd(cmpF,hp,k);
    else printf("warning: calling $$::delOrd() but object not there\n");
}


// -----------------------------------------------------------------------
// Binary search, returns the index of the object with the same key as op
// or the first object with the higher key than that.
// In case of any error, e.g. when the array has not been formed yet, 
// the function generates an error message and returns -1.
// -----------------------------------------------------------------------
int $$_Array::binSearch(cmpType cmpF,$1 *hp,$2 *op,int *found){
    int i1,i2,k,cmp,num; $2* rr; $2* arr;

    arr=hp->$0.array;
    num=hp->$0.num;
    if(!arr || num<0){
        printf("$$ error in binSearch(): array not formed or empty\n");
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
int $$_Array::getBit($1 *hp,int i){
    int iChar,iBit,sz,k,newBytes; $2* ap; unsigned char *p,b;

    sz=sizeof($2) * hp->$0.sz; // sz is size in bytes
    if(i>=sz*8){ // sz*8 is the size in bits
        ap=ind(hp,i/(8*sizeof($2)));
        if(!ap){
            printf("$$ error: cannot realocate for %d bits\n",i);
            return -1;
        }

        // initialize the new part of the array to 0
        newBytes=sizeof($2)*hp->$0.sz;
        p=(unsigned char*)(hp->$0.array);
        for(k=sz; k<newBytes; k++) p[k]=0;
    }
    else if(hp->$0.num<0){ // first call, initialize all bits to 0
        p=(unsigned char*)(hp->$0.array);
        for(k=0; k<sz; k++) p[k]=0;
    }

    k=i/(8*sizeof($2)); // object index in which bit i is
    if(hp->$0.num < k)hp->$0.num=k;

    p=(unsigned char*)(hp->$0.array);
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
int $$_Array::setBit($1 *hp,int i,int val){
    int iChar,iBit,sz,k,newBytes; $2* ap; unsigned char *p,b;

    sz=sizeof($2) * hp->$0.sz; // sz is size in bytes
    if(i>=sz*8){ // sz*8 is the size in bits
        ap=ind(hp,i/(8*sizeof($2)));
        if(!ap){
            printf("$$ error: cannot realocate for %d bits\n",i);
            return -1;
        }

        // initialize the new part of the array to 0
        newBytes=sizeof($2)*hp->$0.sz;
        p=(unsigned char*)(hp->$0.array);
        for(k=sz; k<newBytes; k++) p[k]=0;
    }
    else if(hp->$0.num<0){ // first call, initialize all bits to 0
        p=(unsigned char*)(hp->$0.array);
        for(k=0; k<sz; k++) p[k]=0;
    }

    k=i/(8*sizeof($2)); // object index in which bit i is
    if(hp->$0.num < k)hp->$0.num=k;

    p=(unsigned char*)(hp->$0.array);
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
int $$_Array::getOrd(cmpType cmpF,$1 *hp,$2 *op,int *found){
    int k=binSearch(cmpF,hp,op,found);
    return k;
}



