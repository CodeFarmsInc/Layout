#include <string.h>
class Employee;

void eName_Name::add(Employee *p, char *c){
    char* s=p->ZZds.ZZeName.name;
    if(s){
        printf("eName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZeName.name=c;
}

char* eName_Name::get(Employee *p){ return p->ZZds.ZZeName.name;}

int eName_Name::compare(Employee *p1, Employee *p2){
    return strcmp(p1->ZZds.ZZeName.name, p2->ZZds.ZZeName.name);
}

char* eName_Name::remove(Employee *p1){char* s=p1->ZZds.ZZeName.name; p1->ZZds.ZZeName.name=NULL; return s;}

