#include <iostream.h>
#include <string.h>
#include "gen.h"

    // declaration of classes
    class Employee {
    public:
        ZZ_Employee ZZds; // add mechanically to every class
        Employee(Company *co,char *name);
        Employee(){}
        void prt();
        virtual Department *myDept();
    };

    class Manager : public Employee {
    public:
        ZZ_Manager ZZds;
        Manager(Company *co,char *name) : Employee(co,name){}
        Manager() : Employee(){}
        Department *myDept();
    };

    class Department {
        int deptNo;
    public:
        ZZ_Department ZZds; 
        Department(int dNo){deptNo=dNo;}
        Department(){deptNo=0;}
        int getDeptNo(){return deptNo;}
        void prt(int layer);
        void prtSpace(int layer);
    };

    class Company {
        Employee *eTemp; // temporary for passing employee name
    public:
        ZZ_Company ZZds;
        Company();
        ~Company();
        void prtSuperiors(char *emplName);
    };

    // declare the relations (schema) one association per line

    Association Hash<Company,Employee> eHash;
    Association SingleLink<Company,Department> root;
    Association Aggregate2<Department,Employee> empl;
    Association Aggregate2<Department,Department> dHier; 
    Association DoubleLink<Department,Manager> boss;
    Association Name<Employee> eName;


    int eHash::hash(Employee *e,int hashSz){
        char *s;
        s=eName::get(e);
        return eHash::hashString(s,hashSz);
    }

    int eHash::cmp(Employee *e1,Employee *e2){
        char *s1,*s2;
        s1=eName::get(e1);
        s2=eName::get(e2);
        return strcmp(s1,s2);
    }

    // implementation of all the methods to follow

    Department* Employee::myDept(){
        return empl::parent(this);
    }

    Department* Manager::myDept(){
        return boss::bwd(this);
    }

    Company::Company(){
        eHash::form(this,1000); // form hash table with given num.of buckets
        eTemp=new Employee();
    }

    Company::~Company(){
        eHash::free(this); // free (release) the hash table
        delete eTemp;
    }

    void Company::prtSuperiors(char *emplName){
        Employee *ee,*e; Department *d;

        eName::add(eTemp,emplName); // pass name through a temporary object
        ee=eHash::get(this,eTemp);
        eName::remove(eTemp); // re-initialize temporary object
        if(!ee){
            cout << "employee=" << emplName << " not in the company\n";
            return;
        }
        d=ee->myDept();
        if(!d){
            cout<< "employee=" << emplName << " not assigned to a department\n";
            return;
        }
        if(boss::fwd(d) == ee)cout << "\nmanager ";
        else                  cout << "\nemployee ";
        cout << emplName << " superiors: ";
        for(;d; d=dHier::parent(d)){
            e=boss::fwd(d);
            if(e==ee) continue;
            cout << eName::get(e) << "(" << d->getDeptNo() << ") ";
        }
        cout << "\n";
    }
        

    Employee::Employee(Company *co,char *name){
        eName::add(this,name);
        eHash::add(co,this);
    }

    void Employee::prt(){cout << eName::get(this) << "\n";}

    void Department::prtSpace(int layer){
        for(int i=0; i<layer; i++)cout << "   ";
    }

    // recursive print of departments and employees
    void Department::prt(int layer){
        // iterators are automatically provided
        empl_Iterator eIter; 
        dHier_Iterator hIter;
        Department *d;
        Employee *e;

        prtSpace(layer);
        cout << "dept=" << deptNo << " manager=";
        boss::fwd(this)->prt();

        eIter.start(this); // start employee iterator
        ITERATE(eIter,e){  // e walkes through all employees
            prtSpace(layer+1);
            e->prt();
        }
       
        hIter.start(this); // start employee iterator
        ITERATE(hIter,d){  // d walkes through sub-departments
            d->prt(layer+1);
        }
    }

    // main program can already create and manipulate the data
    int main(){
        Employee *e; Manager *m; Company *co;
        Department *d1,*d2,*d3,*d4,*d5;

        co=new Company(); 
        d1=new Department(100); root::add(co,d1);
        m =new Manager(co,"C.Black"); boss::add(d1,m);
        
        d2=new Department(110);    dHier::addTail(d1,d2);
        m =new Manager(co,"A.Green"); boss::add(d2,m);
        e =new Employee(co,"J.Fox");  empl::addTail(d2,e); // <--- note1
        e =new Employee(co,"K.Doe");  empl::addTail(d2,e);

        d3=new Department(120);    dHier::addTail(d1,d3);
        m =new Manager(co,"B.White"); boss::add(d3,m);

        d4=new Department(111);        dHier::addTail(d2,d4);
        m =new Manager(co,"B.Brown");     boss::add(d4,m);
        e =new Employee(co,"S.Winter");   empl::addTail(d4,e);
        e =new Employee(co,"I.Springer"); empl::addTail(d4,e);
        e =new Employee(co,"B.Summers");  empl::addTail(d4,e);


        d5=new Department(112);        dHier::addTail(d2,d5);
        m =new Manager(co,"G.Gray");      boss::add(d5,m); // <--- note2
        e =new Employee(co,"F.Beech");    empl::addTail(d5,e);
        e =new Employee(co,"H.Oats");     empl::addTail(d5,e);

        // print the entire data by accessing its root, d1
        root::fwd(co)->prt(0);

        // print the superiors of H.Oats
        co->prtSuperiors("H.Oats");
        return 0;
    }
   
#include "gen.cpp"
