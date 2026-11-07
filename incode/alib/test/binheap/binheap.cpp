
// ------------------------------------------------------
// This is the 'static' version of the DOL test9a, part testing the
// binary heap. Though this functionality was originally (in DOL)
// available under the Array class, we now have a separate class for it
// called BinaryHeap.

// The test problem:
// A set of employee records is loaded into a ring (eRing).
// and from there into three binary heaps -- eHeap (for complete employee
// records), pHeap (for pointers to employee records), and
// hHeap (heap of complete employee records which are tested with 
// callback functions).
// The heaps start with smaller sizes than actually
// needed, so that the re-allocation mechanism is also tested.

// Input format: employeeName id salary

// WARNING:
// The testing program uses function ind() which is NOT recommended
// to be used when working with binary heaps -- it can easily
// introduce nasty errors. However, the BinaryHeap class allows a rather
// advanced use of the heap, where you can modify selected entries inside
// the heap and then re-sort the heap as needed.
// ------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include "gen.h"

class Header {
public:
    ZZ_Header ZZds;
    void cpEmpl(Employee *p1,Employee *p2);
    void freeArr();
};
class Employee {
public:
    ZZ_Employee ZZds;
    int emplNum; // employee number or id
    int salary;
    int heapIndex;
    static int pSort(const void *p1,const void *p2);
    static int eSort(const void *p1,const void *p2);
    static int hSort(const void *p1,const void *p2);
};
class PtrEmpl {
public:
    ZZ_PtrEmpl ZZds;
};

#define BSIZE 80

main(int argc,char **argv) {
    void bck(void *,int),hBck(void *,int);
    FILE *file1,*file2;
    Header *h;
    Employee *ep,*sp,**pa,*oa,*p1,**p2,*ee;
    PtrEmpl *pe,*pp;
    char buff[BSIZE],name[BSIZE],*cp,*cc;
    int i,k,n;
    eRing_Iterator eIter;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    h=new Header;    // main holder of the arrays
    ee=new Employee; // temporary working object
    pp=new PtrEmpl;  // temporary working object
    sp=(Employee *)NULL;
    n=0;
    while(fgets(buff,BSIZE,file1)){
        ep=new Employee;
        sscanf(buff,"%s %d %d\n",name,&(ep->emplNum),&(ep->salary));
        cp=new char[strlen(name)+1]; strcpy(cp,name);
        eName::add(ep,cp);
        sp=eRing::add(sp,ep);
        n++;
    }
    rStart::add(h,sp);
    fclose(file1);

    fprintf(file2,"\n using the array as a heap, load twice\n");
    pa=pHeap::form(h,4,-3);
    oa=eHeap::form(h,3,3);

    /* load the heap */
    eIter.start(sp);
    for(ep= ++eIter; ep; ep= ++ eIter){
        p2= &ep;
        pHeap::inHeap(Employee::pSort,h,p2,bck);
        h->cpEmpl(ep,ee);
        eHeap::inHeap(Employee::eSort,h,ee,bck);
        cp=eName::get(ep);
        fprintf(file2,"in heap: %s emplNum=%d salary=%d\n",
                                                 cp,ep->emplNum,ep->salary);
    }
    /* three hand modifications */
    pHeap::delHeap(Employee::pSort,h,4,bck);
    eHeap::delHeap(Employee::eSort,h,4,bck);
    p2=pHeap::ind(h,4);
    p1=eHeap::ind(h,4);
    p1->salary=(*p2)->salary=4200;
    pHeap::updHeap(Employee::pSort,h,4,bck);
    eHeap::updHeap(Employee::eSort,h,4,bck);
    p2=pHeap::ind(h,5);
    p1=eHeap::ind(h,5);
    p1->salary=(*p2)->salary=1400;
    pHeap::updHeap(Employee::pSort,h,5,bck);
    eHeap::updHeap(Employee::eSort,h,5,bck);

    /* unload the heap */
    /* p1 and ee are the storage for the intermediate results */
    for(;;){ /* end of the loop detected by the id.size() function */
        n=pHeap::size(h);
        if(n<=0)break;
        pHeap::outHeap(Employee::pSort,h,&p1,bck);
        cc=eName::get(p1);
        n=eHeap::size(h);
        if(n<=0)break;
        eHeap::outHeap(Employee::eSort,h,ee,bck); 
                                      // ee points to an allocated object
        cp=eName::get(ee);
        fprintf(file2,"out heap: %s emplNum=%d salary=%d",
                                                 cp,p1->emplNum,ee->salary);
        if(!strcmp(cc,cp))fprintf(file2,"\n");
        else fprintf(file2," different names: %s %s\n",cc,cp);
    }

    fprintf(file2,"\n heap with a call-back function\n");
    h->freeArr();
    pe=hHeap::form(h,4,-3);

    /* load the heap */
    eIter.start(sp);
    ITERATE(eIter,ep){
        pe=new PtrEmpl;
        hPtr::add(pe,ep);
        hHeap::inHeap(Employee::hSort,h,pe,hBck);
        cp=eName::get(ep);
        fprintf(file2,"in heap: %s emplNum=%d salary=%d\n",
                                                 cp,ep->emplNum,ep->salary);
    }
    /* delete odd entries, modify salaries +-1000 */
    i=1;
    n=1000;
    eIter.start(sp);
    ITERATE(eIter,ep){
        k=ep->heapIndex;
        cp=eName::get(ep);
        if(i>0){
            hHeap::delHeap(Employee::hSort,h,k,hBck);
            fprintf(file2,"deleted: %s emplNum=%d salary=%d\n",
                                          cp,ep->emplNum,ep->salary);
        }
        else {
            ep->salary+=n;
            n= -n;
            hHeap::updHeap(Employee::hSort,h,k,hBck);
            fprintf(file2,"update: %s emplNum=%d salary=%d\n",
                                          cp,ep->emplNum,ep->salary);
        }
        i= -i;
    };
    /* unload the heap */
    /* pp is a pre-allocated storage for intermediate results */
    for(;;){ /* end of the loop detected by pHeap.size() */
        n=hHeap::size(h);
        if(n<=0)break;
        hHeap::outHeap(Employee::hSort,h,pp,bck);
        ep=hPtr::target(pp);
        cp=eName::get(ep);
        fprintf(file2,"out heap: %s emplNum=%d salary=%d\n",
                                                 cp,ep->emplNum,ep->salary);
    }
    hHeap::free(h);
    return(0);
}
/* --------------------------------------------------------------------- */
int Employee::eSort(const void *c1,const void *c2)
{
    Employee *p1,*p2;

    p1=(Employee *)c1;
    p2=(Employee *)c2;
    if(p1->salary<p2->salary)return(-1);
    if(p1->salary>p2->salary)return(1);
    return(0);
}
/* --------------------------------------------------------------------- */
int Employee::pSort(const void *c1,const void *c2)
{
    Employee **p1,**p2;

    p1=(Employee **)c1;
    p2=(Employee **)c2;
    if((*p1)->salary<(*p2)->salary)return(-1);
    if((*p1)->salary>(*p2)->salary)return(1);
    return(0);
}
/* --------------------------------------------------------------------- */
int Employee::hSort(const void *c1,const void *c2)
{
    Employee *p1,*p2;

    p1=hPtr::target((PtrEmpl*)c1);
    p2=hPtr::target((PtrEmpl*)c2);
    if(p1->salary<p2->salary)return(-1);
    if(p1->salary>p2->salary)return(1);
    return(0);
}
/* --------------------------------------------------------------------- */
/* disconnect links on array oa, and free both arrays */
void Header::freeArr()
{
    int i,n;
    Employee *oa;

    n=eHeap::size(this);
    oa=eHeap::ind(this,0);
    for(i=0;i<n;i++){
        eName::del(&(oa[i]));
    }
    pHeap::free(this);
    eHeap::free(this);
    return;
}
/* --------------------------------------------------------------------- */
/* Copy one Employee record onto another, but avoid the organization pointers.
 * Note that: (*p2)=(*p1); would be wrong, it would mess up the pointers */
void Header::cpEmpl(Employee *p1,Employee *p2)
{
    char *cp;

    eName::del(p2);
    cp=eName::get(p1);
    eName::add(p2,cp); /* using the same name as string */
    p2->emplNum=p1->emplNum;
    p2->salary=p1->salary;
    return;
}
// --------------------------------------------------------------------- */
// heap callback function when not used
void bck(void *p,int i){p=p; i=i;}

// heap callback function when used
void hBck(void *p,int i){
    Employee *e;

    e=hPtr::target((PtrEmpl*)p);
    e->heapIndex=i;
}

#include "gen.cpp"
