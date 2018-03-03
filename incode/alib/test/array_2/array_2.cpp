#include "array_2.h"

#define BSIZE 80

main(int argc,char **argv) {
    int pSort(const void *p1,const void *p2);
    int oSort(const void *p1,const void *p2);
    int hSort(const void *p1,const void *p2);
    void cpEmpl(Employee *p1,Employee *p2),freeArr(Header *h);
    void bck(void *,int),hBck(void *,int);
    FILE *file1,*file2;
    Header *h;
    Employee *ep,*sp,**pa,*oa,*p1,**p2,*p3,*p4,*ee;
    PtrEmpl *pe,*pp;
    char buff[BSIZE],name[BSIZE],*cp,*cc;
    int i,k,n;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    h=new Header;    /* main holder of the arrays */
    ee=new Employee; /* temporary working object */
    pp=new PtrEmpl;  /* temporary working object */
    sp=(Employee *)NULL;
    n=0;
    while(fgets(buff,BSIZE,file1)){
        ep=new Employee;
        sscanf(buff,"%s %d %d\n",name,&(ep->emplNum),&(ep->salary));
        cp=new char[strlen(name)+1]; strcpy(cp,name);
        eName.add(ep,cp);
        sp=eRing.add(sp,ep);
        n++;
    }
    rStart.add(h,sp);
    fclose(file1);

    /* test of normal usage of the array, compare all 4 methods */
    fprintf(file2," testing 4 ways to index the array\n");
    pa=pArr.form(h,4,2);
    oa=oArr.form(h,3,-2);

    i=0;
    eRing_iterator eIter(sp);
    for(ep= ++eIter; ep; ep= ++eIter){
        p2=pArr.ind(h,i);
        (*p2)=ep;
        p1=oArr.ind(h,n-i);
        cpEmpl(ep,p1);
        i++;
    }

    /* update array entries before section of direct access */
    pa=pArr.ind(h,0);
    oa=oArr.ind(h,0);
    fprintf(file2,"\n direct access\n");
    for(i=0;i<n;i++){
        p1=pa[i];
        cp=eName.fwd(p1);
        fprintf(file2,"i=%d name=%s emplNum=%d salary=%d",
                                               i,cp,p1->emplNum,p1->salary);
        p3= &(oa[n-i]);
        cc=eName.fwd(p3);
        if(strcmp(cp,cc))fprintf(file2," (1 not 3)");
        fprintf(file2,"\n");
    }
    fprintf(file2,"\n protected access\n");
    for(i=0;i<n;i++){
        p2=pArr.ind(h,i);
        cp=eName.fwd(*p2);
        fprintf(file2,"i=%d name=%s emplNum=%d salary=%d",
                                            i,cp,(*p2)->emplNum,(*p2)->salary);
        p4=oArr.ind(h,n-i);
        cc=eName.fwd(p4);
        if(strcmp(cp,cc))fprintf(file2," (2 not 4)");
        fprintf(file2,"\n");
    }

    fprintf(file2,"\n the same thing, only different indexing\n");
    freeArr(h);
    pa=pArr.form(h,4,2);
    oa=oArr.form(h,3,-2);

    i=0;
    eIter.start(sp);
    for(ep= ++eIter; ep; ep= ++ eIter){
        p2=pArr.ind(h,n-i);
        (*p2)=ep;
        p1=oArr.ind(h,i);
        cpEmpl(ep,p1);
        i++;
    }

    /* update array entries before section of direct access */
    pa=pArr.ind(h,0);
    oa=oArr.ind(h,0);
    fprintf(file2,"\n direct access\n");
    for(i=0;i<n;i++){
        p1=pa[n-i];
        cp=eName.fwd(p1);
        fprintf(file2,"i=%d name=%s emplNum=%d salary=%d",
                                               i,cp,p1->emplNum,p1->salary);
        p3= &(oa[i]);
        cc=eName.fwd(p3);
        if(strcmp(cp,cc))fprintf(file2," (1 not 3)");
        fprintf(file2,"\n");
    }
    fprintf(file2,"\n protected access\n");
    for(i=0;i<n;i++){
        p2=pArr.ind(h,n-i);
        cp=eName.fwd(*p2);
        fprintf(file2,"i=%d name=%s emplNum=%d salary=%d",
                                            i,cp,(*p2)->emplNum,(*p2)->salary);
        p4=oArr.ind(h,i);
        cc=eName.fwd(p4);
        if(strcmp(cp,cc))fprintf(file2," (2 not 4)");
        fprintf(file2,"\n");
    }

    fprintf(file2,"\n using the array as a stack\n");
    freeArr(h);
    pa=pArr.form(h,4,-3);
    oa=oArr.form(h,3,10);

    eIter.start(sp);
    for(ep= ++eIter; ep; ep= ++ eIter){
        p2= &ep;
        pArr.push(h,p2);
        cpEmpl(ep,ee);
        oArr.push(h,ee);
        cp=eName.fwd(ep);
        fprintf(file2,"push: %s emplNum=%d salary=%d\n",
                                                 cp,ep->emplNum,ep->salary);
    }
    for(p1=sp;p1;){ /* start with any non-null pointer from loading eRing */
        p2=pArr.pop(h);
        if(!p2)break;
        cc=eName.fwd(*p2);
        p1=oArr.pop(h);
        if(!p1)break;
        cp=eName.fwd(p1);
        fprintf(file2,"pop: %s emplNum=%d salary=%d",
                                                 cp,p1->emplNum,p1->salary);
        if(!strcmp(cc,cp))fprintf(file2,"\n");
        else fprintf(file2," different names: %s %s\n",cc,cp);
    }

    fprintf(file2,"\n using the array as a heap, load twice\n");
    freeArr(h);
    pa=pArr.form(h,4,-3);
    oa=oArr.form(h,3,3);

    /* load the heap */
    eIter.start(sp);
    for(ep= ++eIter; ep; ep= ++ eIter){
        p2= &ep;
        pArr.inHeap(pSort,h,p2,bck);
        cpEmpl(ep,ee);
        oArr.inHeap(oSort,h,ee,bck);
        cp=eName.fwd(ep);
        fprintf(file2,"in heap: %s emplNum=%d salary=%d\n",
                                                 cp,ep->emplNum,ep->salary);
    }
    /* three hand modifications */
    pArr.delHeap(pSort,h,4,bck);
    oArr.delHeap(oSort,h,4,bck);
    p2=pArr.ind(h,4);
    p1=oArr.ind(h,4);
    p1->salary=(*p2)->salary=4200;
    pArr.updHeap(pSort,h,4,bck);
    oArr.updHeap(oSort,h,4,bck);
    p2=pArr.ind(h,5);
    p1=oArr.ind(h,5);
    p1->salary=(*p2)->salary=1400;
    pArr.updHeap(pSort,h,5,bck);
    oArr.updHeap(oSort,h,5,bck);

    /* unload the heap */
    /* p1 and ee are the storage for the intermediate results */
    for(;;){ /* end of the loop detected by the id.size() function */
        n=pArr.size(h);
        if(n<=0)break;
        pArr.outHeap(pSort,h,&p1,bck);
        cc=eName.fwd(p1);
        n=oArr.size(h);
        if(n<=0)break;
        oArr.outHeap(oSort,h,ee,bck); /* ee points to an allocated object */
        cp=eName.fwd(ee);
        fprintf(file2,"out heap: %s emplNum=%d salary=%d",
                                                 cp,p1->emplNum,ee->salary);
        if(!strcmp(cc,cp))fprintf(file2,"\n");
        else fprintf(file2," different names: %s %s\n",cc,cp);
    }

    fprintf(file2,"\n heap with a call-back function\n");
    freeArr(h);
    pe=hArr.form(h,4,-3);

    /* load the heap */
    eIter.start(sp);
    ITERATE(eIter,ep){
        pe=new PtrEmpl;
        hPtr.add(pe,ep);
        hArr.inHeap(hSort,h,pe,hBck);
        cp=eName.fwd(ep);
        fprintf(file2,"in heap: %s emplNum=%d salary=%d\n",
                                                 cp,ep->emplNum,ep->salary);
    }
    /* delete odd entries, modify salaries +-1000 */
    i=1;
    n=1000;
    eIter.start(sp);
    ITERATE(eIter,ep){
        k=ep->heapIndex;
        cp=eName.fwd(ep);
        if(i>0){
            hArr.delHeap(hSort,h,k,hBck);
            fprintf(file2,"deleted: %s emplNum=%d salary=%d\n",
                                          cp,ep->emplNum,ep->salary);
        }
        else {
            ep->salary+=n;
            n= -n;
            hArr.updHeap(hSort,h,k,hBck);
            fprintf(file2,"update: %s emplNum=%d salary=%d\n",
                                          cp,ep->emplNum,ep->salary);
        }
        i= -i;
    };
    /* unload the heap */
    /* pp is a pre-allocated storage for intermediate results */
    for(;;){ /* end of the loop detected by pArr.size() */
        n=hArr.size(h);
        if(n<=0)break;
        hArr.outHeap(hSort,h,pp,bck);
        ep=hPtr.target(pp);
        cp=eName.fwd(ep);
        fprintf(file2,"out heap: %s emplNum=%d salary=%d\n",
                                                 cp,ep->emplNum,ep->salary);
    }
    return(0);
}
/* --------------------------------------------------------------------- */
int oSort(const void *c1,const void *c2)
{
    Employee *p1,*p2;

    p1=(Employee *)c1;
    p2=(Employee *)c2;
    if(p1->salary<p2->salary)return(-1);
    if(p1->salary>p2->salary)return(1);
    return(0);
}
/* --------------------------------------------------------------------- */
int pSort(const void *c1,const void *c2)
{
    Employee **p1,**p2;

    p1=(Employee **)c1;
    p2=(Employee **)c2;
    if((*p1)->salary<(*p2)->salary)return(-1);
    if((*p1)->salary>(*p2)->salary)return(1);
    return(0);
}
/* --------------------------------------------------------------------- */
int hSort(const void *c1,const void *c2)
{
    Employee *p1,*p2;

    p1=hPtr.target((PtrEmpl*)c1);
    p2=hPtr.target((PtrEmpl*)c2);
    if(p1->salary<p2->salary)return(-1);
    if(p1->salary>p2->salary)return(1);
    return(0);
}
/* --------------------------------------------------------------------- */
/* disconnect links on array oa, and free both arrays */
void freeArr(Header *h)
{
    int i,n;
    Employee *oa;

    n=oArr.capacity(h);
    oa=oArr.ind(h,0);
    for(i=0;i<n;i++){
        eName.del(&(oa[i]));
    }
    pArr.free(h);
    oArr.free(h);
    return;
}
/* --------------------------------------------------------------------- */
/* Copy one Employee record onto another, but avoid the organization pointers.
 * Note that: (*p2)=(*p1); would be wrong, it would mess up the pointers */
void cpEmpl(Employee *p1,Employee *p2)
{
    char *cp;

    eName.del(p2);
    cp=eName.fwd(p1);
    eName.add(p2,cp); /* using the same name as string */
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

    e=hPtr.target((PtrEmpl*)p);
    e->heapIndex=i;
}

#include "gen.cpp"
