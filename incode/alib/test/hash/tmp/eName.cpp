#include <string.h>
class Employee;

void eName_Name::add(Employee *p, char *c){
    char* s=p->ZZds.ZZeName.name;
    if(s){
        printf("eName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZeName.name=c;
}

void eName_Name::addNew(Employee *p, char *c){
    char *s;
    if(!c){
        printf("eName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("eName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZeName.name=s;
}

char* eName_Name::get(Employee *p){ return p->ZZds.ZZeName.name;}

int eName_Name::compare(Employee *p1, Employee *p2){
    return strcmp(p1->ZZds.ZZeName.name, p2->ZZds.ZZeName.name);
}

char* eName_Name::remove(Employee *p1){char* s=p1->ZZds.ZZeName.name; p1->ZZds.ZZeName.name=NULL; return s;}

