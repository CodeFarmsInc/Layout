#include <string.h>
class Organization;

void orgName_Name::add(Organization *p, char *c){
    char* s=p->ZZds.ZZorgName.name;
    if(s){
        printf("orgName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZorgName.name=c;
}

void orgName_Name::addNew(Organization *p, char *c){
    char *s;
    if(!c){
        printf("orgName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("orgName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZorgName.name=s;
}

char* orgName_Name::get(Organization *p){ return p->ZZds.ZZorgName.name;}

int orgName_Name::compare(Organization *p1, Organization *p2){
    return strcmp(p1->ZZds.ZZorgName.name, p2->ZZds.ZZorgName.name);
}

char* orgName_Name::remove(Organization *p1){char* s=p1->ZZds.ZZorgName.name; p1->ZZds.ZZorgName.name=NULL; return s;}

