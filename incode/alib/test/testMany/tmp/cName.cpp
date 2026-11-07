#include <string.h>
class Course;

void cName_Name::add(Course *p, char *c){
    char* s=p->ZZds.ZZcName.name;
    if(s){
        printf("cName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZcName.name=c;
}

void cName_Name::addNew(Course *p, char *c){
    char *s;
    if(!c){
        printf("cName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("cName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZcName.name=s;
}

char* cName_Name::get(Course *p){ return p->ZZds.ZZcName.name;}

int cName_Name::compare(Course *p1, Course *p2){
    return strcmp(p1->ZZds.ZZcName.name, p2->ZZds.ZZcName.name);
}

char* cName_Name::remove(Course *p1){char* s=p1->ZZds.ZZcName.name; p1->ZZds.ZZcName.name=NULL; return s;}

