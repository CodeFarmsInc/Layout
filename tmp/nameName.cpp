#include <string.h>
class Name;

void nameName_Name::add(Name *p, char *c){
    char* s=p->ZZds.ZZnameName.name;
    if(s){
        printf("nameName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZnameName.name=c;
}

void nameName_Name::addNew(Name *p, char *c){
    char *s;
    if(!c){
        printf("nameName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("nameName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZnameName.name=s;
}

char* nameName_Name::get(Name *p){ return p->ZZds.ZZnameName.name;}

int nameName_Name::compare(Name *p1, Name *p2){
    return strcmp(p1->ZZds.ZZnameName.name, p2->ZZds.ZZnameName.name);
}

char* nameName_Name::remove(Name *p1){char* s=p1->ZZds.ZZnameName.name; p1->ZZds.ZZnameName.name=NULL; return s;}

