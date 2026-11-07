#include <string.h>
class Student;

void sName_Name::add(Student *p, char *c){
    char* s=p->ZZds.ZZsName.name;
    if(s){
        printf("sName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZsName.name=c;
}

void sName_Name::addNew(Student *p, char *c){
    char *s;
    if(!c){
        printf("sName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("sName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZsName.name=s;
}

char* sName_Name::get(Student *p){ return p->ZZds.ZZsName.name;}

int sName_Name::compare(Student *p1, Student *p2){
    return strcmp(p1->ZZds.ZZsName.name, p2->ZZds.ZZsName.name);
}

char* sName_Name::remove(Student *p1){char* s=p1->ZZds.ZZsName.name; p1->ZZds.ZZsName.name=NULL; return s;}

