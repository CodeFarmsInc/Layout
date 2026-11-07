#include <string.h>
class OrgType;

void orgTypeName_Name::add(OrgType *p, char *c){
    char* s=p->ZZds.ZZorgTypeName.name;
    if(s){
        printf("orgTypeName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZorgTypeName.name=c;
}

void orgTypeName_Name::addNew(OrgType *p, char *c){
    char *s;
    if(!c){
        printf("orgTypeName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("orgTypeName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZorgTypeName.name=s;
}

char* orgTypeName_Name::get(OrgType *p){ return p->ZZds.ZZorgTypeName.name;}

int orgTypeName_Name::compare(OrgType *p1, OrgType *p2){
    return strcmp(p1->ZZds.ZZorgTypeName.name, p2->ZZds.ZZorgTypeName.name);
}

char* orgTypeName_Name::remove(OrgType *p1){char* s=p1->ZZds.ZZorgTypeName.name; p1->ZZds.ZZorgTypeName.name=NULL; return s;}

