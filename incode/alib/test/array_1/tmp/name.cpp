#include <string.h>
class Person;

void name_Name::add(Person *p, char *c){
    char* s=p->ZZds.ZZname.name;
    if(s){
        printf("name:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZname.name=c;
}

void name_Name::addNew(Person *p, char *c){
    char *s;
    if(!c){
        printf("name:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("name:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZname.name=s;
}

char* name_Name::get(Person *p){ return p->ZZds.ZZname.name;}

int name_Name::compare(Person *p1, Person *p2){
    return strcmp(p1->ZZds.ZZname.name, p2->ZZds.ZZname.name);
}

char* name_Name::remove(Person *p1){char* s=p1->ZZds.ZZname.name; p1->ZZds.ZZname.name=NULL; return s;}

