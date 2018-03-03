#include <iostream.h>
#include <string.h>
#include "gen.h"

    // declaration of classes
    class Employee {
    public:
        ZZ_Employee ZZds; // add mechanically to every class
        Employee(char *name);
        Employee(){}
        void prt();
    };

    class Manager : public Employee {
    public:
        ZZ_Manager ZZds;
        Manager(char *name) : Employee(name){}
        Manager() : Employee(){}
    };

    class Department {
        int deptNo;
    public:
        ZZ_Department ZZds; 
        Department(int dNo){deptNo=dNo;}
        Department(){deptNo=0;}
        void prt(int layer);
        void prtSpace(int layer);
    };

    class Company {
    public:
        ZZ_Company ZZds;
        Company(){}
    };

    // declare the relations (schema) one association per line

    Association Hash<Company,Employee> eHash;
    Association SingleLink<Company,Department> root;
    Association Aggregate2<Department,Employee> empl;
    Association Aggregate2<Department,Department> dHier; 
    Association SingleLink<Department,Manager> boss;
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

    Employee::Employee(char *name){eName::add(this,name);}

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
        Employee *e; Manager *m; Department *d1,*d2,*d3,*d4,*d5;

        d1=new Department(100);
        m =new Manager("C.Black"); boss::add(d1,m);
        
        d2=new Department(110);    dHier::addTail(d1,d2);
        m =new Manager("A.Green"); boss::add(d2,m);
        e =new Employee("J.Fox");  empl::addTail(d2,e); // <--- note1
        e =new Employee("K.Doe");  empl::addTail(d2,e);

        d3=new Department(120);    dHier::addTail(d1,d3);
        m =new Manager("B.White"); boss::add(d3,m);

        d4=new Department(111);        dHier::addTail(d2,d4);
        m =new Manager("B.Brown");     boss::add(d4,m);
        e =new Employee("S.Winter");   empl::addTail(d4,e);
        e =new Employee("I.Springer"); empl::addTail(d4,e);
        e =new Employee("B.Summers");  empl::addTail(d4,e);


        d5=new Department(112);        dHier::addTail(d2,d5);
        m =new Manager("G.Gray");      boss::add(d5,m); // <--- note2
        e =new Employee("F.Beech");    empl::addTail(d5,e);
        e =new Employee("H.Oats");     empl::addTail(d5,e);

        // print the entire data by accessing its root, d1
        d1->prt(0);
        return 0;
    }
   
#include "gen.cpp"
