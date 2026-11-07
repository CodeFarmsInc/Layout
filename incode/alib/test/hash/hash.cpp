// -------------------------------------------------------------------------
// This is a test of class Hash.
// We have Company with Employees which we want to access quickly
// either by name or by the ID. We keep the employee records in two
// independent hash tables: byName and byID.
// For eazy checking, we also store all employees in a LinkedList eList.
// This allows us to check that all objects in either table are in the list,
// and all objects in the list are in the table.
//
// We form one tiny and one reasonably large table, load them with
// test data, and call the checking function.
// Then we resize the small table to a large one and the large one to a small
// one, and call the checking function again.
// Then remove every second employee on the list from all records,
// and call the checking function.
//
// This test does not generate any output data except for a message that
// all the automatic checking passed correctly.
//
// This test runs with the standard interface (not using the historical DOL
// interface).
// --------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include "gen.h"

class Company {
public:
    ZZ_Company ZZds;
    int checkAll(char *label);
    void debPrtName();
    void debPrtID();
    void debPrtIteratorName();
    void debPrtIteratorID();
    void debPrtList();
};

class Employee {
    int ID;
public:
    int flg;
    ZZ_Employee ZZds;
    Employee(){ID=0;} // for temporary objects, has no name
    Employee(char *name,int id);
    ~Employee();
    int getID(){return ID;}
    void prt();
};

int byName::hash(Employee *e,int hashSz){
    char *s;
    s=eName::get(e);
    return byName::hashString(s,hashSz);
}

int byID::hash(Employee *e,int hashSz){
    return byName::hashInt(e->getID(),hashSz);
}

int byName::cmp(Employee *e1,Employee *e2){
    char *s1,*s2;
    s1=eName::get(e1);
    s2=eName::get(e2);
    return strcmp(s1,s2);
}

int byID::cmp(Employee *e1,Employee *e2){
    int i1,i2;
    i1=e1->getID();
    i2=e2->getID();
    return i1 - i2;
}

// ------------------------------------------------------------
// Use the Employee::flg when comparing records
// Return  0 when everything correct.
// ------------------------------------------------------------
int Company::checkAll(char *label){
    Employee *ep,ee,*p; int ret,k,count_name,count_id,sz;
    eList_Iterator eIter;
    byName_Iterator nIter;
    byID_Iterator iIter;

    printf("\n---calling checkAll(): %s\n",label);
    ret=0;
    for(ep=eIter.fromHead(this); ep; ep=eIter.next()){
        ep->flg=0;
        ee=(*ep); // use a different object to carry the name and ID
        p=byName::get(this,&ee);
        if(p!=ep){
            printf("byName mixup, different names=%s, %s\n",
                                         eName::get(ep),eName::get(&ee));
            ret=1;
        }
        p=byID::get(this,&ee);
        if(p!=ep){
            printf("byID mixup, different ID=%d, %d\n",ep->getID(),ee.getID());
            ret=1;
        }
    }

    for(ep=nIter.first(this,-1); ep; ep=nIter.next()){
        (ep->flg)++;
    }

    for(ep=iIter.first(this,-1); ep; ep=iIter.next()){
        (ep->flg)++;
    }

    sz=byName::size(this,&count_name);
    sz=byID::size(this,&count_id);
    if(count_name != count_id){
        printf("error: count_name=%d count_id=%d\n",count_name,count_id);
    }
       
    for(ep=eIter.fromHead(this), k=0; ep; ep=eIter.next(), k++){
        if(ep->flg != 2){
            printf("error: %s %d is not in both hash tables, flg=%d\n",
                           eName::get(ep),ep->getID(),ep->flg);
            ret=1;
        }
    }

    if(k!=count_name){
        printf("error in counts: list=%d byName=%d byID=%d\n",
                                                  k,count_name,count_id);
        ret=1;
    }
    
    if(ret==0) printf("all results correct\n");
    eName::remove(&ee); // otherwise the automatic destruction of ee would 
                        // also destroy its name, i.e. a valid name from ep
    return ret;
}

// ------------------------------------------------------------
void Employee::prt(){
    printf("EMPLOYEE: addr=%d name=%s ID=%d\n",this,eName::get(this),getID());
}
        
// ------------------------------------------------------------
// Debugging print of hash table 'byName'
// ------------------------------------------------------------
void Company::debPrtName(){
    Employee *ep; int i,sz,count,c;
    byName_Iterator eIter;

    sz=byName::size(this,&count);
    c=0;
    printf("\nDEBUGGING PRINT OF: byName\n");
    for(i=0; i<sz; i++){
        for(ep=eIter.first(this,i); ep; ep=eIter.next()){
            printf("   slot=%d ",i); ep->prt();
            c++;
        }
    }
    printf("  count=%d c=%d\n\n",count,c);
}

// ------------------------------------------------------------
// Debugging print of hash table 'byID'
// ------------------------------------------------------------
void Company::debPrtID(){
    Employee *ep; int i,sz,count,c;
    byID_Iterator eIter;

    sz=byID::size(this,&count);
    c=0;
    printf("\nDEBUGGING PRINT OF: byID\n");
    for(i=0; i<sz; i++){
        for(ep=eIter.first(this,i); ep; ep=eIter.next()){
            printf("   slot=%d ",i); ep->prt();
            c++;
        }
    }
    printf("  count=%d c=%d\n\n",count,c);
}

// ------------------------------------------------------------
// Debugging print of hash table 'byName' using iterator option -1
// ------------------------------------------------------------
void Company::debPrtIteratorName(){
    Employee *ep; int count,c,sz;
    byName_Iterator nIter;

    sz=byName::size(this,&count);
    c=0;
    printf("\nDEBUGGING PRINT OF: byName OPTION: -1\n");
    for(ep=nIter.first(this,-1); ep; ep=nIter.next()){
        ep->prt();
        c++;
    }
    printf("  count=%d c=%d\n\n",count,c);
}

// ------------------------------------------------------------
// Debugging print of hash table 'byID' using iterator option -1
// ------------------------------------------------------------
void Company::debPrtIteratorID(){
    Employee *ep; int count,c,sz;
    byID_Iterator iIter;

    sz=byID::size(this,&count);
    c=0;
    printf("\nDEBUGGING PRINT OF: byID OPTION: -1\n");
    for(ep=iIter.first(this,-1); ep; ep=iIter.next()){
        ep->prt();
        c++;
    }
    printf("  count=%d c=%d\n\n",count,c);
}

// ------------------------------------------------------------
// Debugging print of the Employees, using 'eList'
// ------------------------------------------------------------
void Company::debPrtList(){
    Employee *ep; 
    eList_Iterator eIter;

    printf("\nDEBUGGING PRINT OF: eList\n");
    for(ep=eIter.fromHead(this); ep; ep=eIter.next()){
        printf("flg=%d ",ep->flg); ep->prt();
    }
}

// ------------------------------------------------------------
Employee::Employee(char *name, int id){
    char* s=new char[strlen(name)+1];
    if(s)strcpy(s,name);
    else printf("unable to allocate Employee name\n");
    eName::add(this,s);
    ID=id;
}

// ------------------------------------------------------------
Employee::~Employee(){
    char *s;
    s=eName::remove(this);
    if(s)delete[] s;
}

// ------------------------------------------------------------
int main(){
    Company *cp; int i,k; Employee *ep;
    char seed[20]; strcpy(seed,"A_name_z"); int seedNum=1234;
    int last=strlen(seed)-1;
    eList_Iterator it;

    cp=new Company;
    byName::form(cp,3);
    byID::form(cp,20);

    // generate 20 employees with unique names and ID's
    // and load them into the two hash tables and into the linked list
    for(i=k=0; i<20; i++){
        if(k>=0)k++;
        k= -k;
        (seed[0])++; (seed[last])--;
        ep=new Employee(seed,seedNum+k);
        eList::addHead(cp,ep);
        byName::add(cp,ep);
        byID::add(cp,ep);
    }

    if(cp->checkAll("after creating data"))return 1;

    byName::resize(cp,40);
    byID::resize(cp,4);
    if(cp->checkAll("after re-sizing hash tables"))return 1;

    // remove all records for every second employee on the list
    for(ep=it.fromHead(cp), k=0; ep; ep=it.next(), k=1-k){
        if(k)continue;
        eList::remove(cp,ep);
        byName::remove(cp,ep);
        byID::remove(cp,ep);
        delete ep;
    }
    if(cp->checkAll("after removing every second employee"))return 1;
   
    i=byName::size(cp,&k);
    printf("final check: count=%d - everything OK\n",k);
    return 0;
}

#include "gen.cpp"

