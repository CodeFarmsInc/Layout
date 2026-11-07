#include "gen.h"
#include "ilarray.h"

void Department::prt(char *label){
    Employee *e; int i,sz;

    printf("%s:\n",label);
    sz=eArr::size(this);
    for(i=0; i<sz; i++){
        e=eArr::get(this,i);
        printf("i=%d Employee index=%d name=%s\n",
                       i,eArr::getIndex(e),eName::get(e));
    }
    printf("\n");
}

Employee::Employee(){
}

// compare two Employees for the purpose of sorting
int Employee::cmp(void const *c1,void const *c2){
    Employee *e1,*e2;

    e1=(*((Employee**)c1));
    e2=(*((Employee**)c2));
    return strcmp(eName::get(e1),eName::get(e2));
}

int main() {
    void bck(void *,int),hBck(void *,int);
    Department *d; Employee *e,*e0,*e1,*e2,*e3,*e4,*e5; int i;
    eList_Iterator eit;

    d=new Department;
    eArr::form(d,10,0);

    e0=new Employee; eName::addNew(e0,"J. White"); eList::addTail(d,e0);
    e1=new Employee; eName::addNew(e1,"F. Brown"); eList::addTail(d,e1);
    e2=new Employee; eName::addNew(e2,"C. Green"); eList::addTail(d,e2);
    e3=new Employee; eName::addNew(e3,"A. Black"); eList::addTail(d,e3);
    e4=new Employee; eName::addNew(e4,"R. Reddy"); eList::addTail(d,e4);
    e5=new Employee; eName::addNew(e5,"I. Gray"); eList::addTail(d,e5);

    for(e=eit.fromHead(d), i=0; e; e=eit.next(), i++){
        eArr::set(d,i,e);
    }
    d->prt("first set");

    eArr::remove(d,2);
    eArr::addTail(d,e2);
    //JS eArr::set(d,2,e1); // trying a wrong thing
    eArr::remove(d,1);
    eArr::insert(d,3,e1);
    d->prt("after several operations");

    eArr::sort(Employee::cmp,d);
    d->prt("after sort");
        
    return(0);
}

#include "gen.cpp"
