
// ------------------------------------------------------
// This is the stack part from the DOL test9a coded in the "static style.

// The test problem:
// A set of employee records is loaded into a ring (eRing).
// and from there into the stack.
// Two sets of tests are made: one for the stack of full employee
// records(eStack), the other for the array of pointers (pStack).
// The arrays start with a smaller size than actually
// needed, so that the re-allocation mechanism is tested.

// Input format: employeeName id salary
// ------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include "gen.h"

class Header {
public:
    ZZ_Header ZZds;
    void freeArr();
    void cpEmpl(Employee *p1,Employee *p2);
};
class Employee {
public:
    ZZ_Employee ZZds;
    int emplNum; // employee number or id
    int salary;
    int heapIndex;
};

#define BSIZE 80

main(int argc,char **argv) {
    FILE *file1,*file2;
    Header *h;
    Employee *ep,*sp,**pa,*oa,*p1,**p2,*ee;
    char buff[BSIZE],name[BSIZE],*cp,*cc;
    int n;
    eRing_Iterator eIter;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    h=new Header;    /* main holder of the arrays */
    ee=new Employee; /* temporary working object */
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

    fprintf(file2,"\n using the array as a stack\n");
    pa=pStack::form(h,4,-3);
    oa=eStack::form(h,3,10);

    eIter.start(sp);
    for(ep= ++eIter; ep; ep= ++ eIter){
        p2= &ep;
        pStack::push(h,p2);
        h->cpEmpl(ep,ee);
        eStack::push(h,ee);
        cp=eName::get(ep);
        fprintf(file2,"push: %s emplNum=%d salary=%d\n",
                                                 cp,ep->emplNum,ep->salary);
    }
    for(p1=sp;p1;){ /* start with any non-null pointer from loading eRing */
        p2=pStack::pop(h);
        if(!p2)break;
        cc=eName::get(*p2);
        p1=eStack::pop(h);
        if(!p1)break;
        cp=eName::get(p1);
        fprintf(file2,"pop: %s emplNum=%d salary=%d",
                                                 cp,p1->emplNum,p1->salary);
        if(!strcmp(cc,cp))fprintf(file2,"\n");
        else fprintf(file2," different names: %s %s\n",cc,cp);
    }

    h->freeArr();
    return(0);
}
/* --------------------------------------------------------------------- */
/* disconnect links on array oa, and free both arrays */
void Header::freeArr()
{
    int i,sz;
    Employee *oa;

    sz=eStack::size(this);
    oa=eStack::ind(this,0);
    for(i=0;i<sz;i++){
        eName::del(&(oa[i]));
    }
    pStack::free(this);
    eStack::free(this);
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

#include "gen.cpp"
