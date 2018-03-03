#include <string.h>
class ApplClass;

void cName_Name::add(ApplClass *p, char *c){
    char* s=p->ZZds.ZZcName.name;
    if(s){
        printf("cName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZcName.name=c;
}

void cName_Name::addNew(ApplClass *p, char *c){
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

char* cName_Name::get(ApplClass *p){ return p->ZZds.ZZcName.name;}

int cName_Name::compare(ApplClass *p1, ApplClass *p2){
    return strcmp(p1->ZZds.ZZcName.name, p2->ZZds.ZZcName.name);
}

char* cName_Name::remove(ApplClass *p1){char* s=p1->ZZds.ZZcName.name; p1->ZZds.ZZcName.name=NULL; return s;}

