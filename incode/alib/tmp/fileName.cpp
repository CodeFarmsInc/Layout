#include <string.h>
class OrgType;

void fileName_Name::add(OrgType *p, char *c){
    char* s=p->ZZds.ZZfileName.name;
    if(s){
        printf("fileName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZfileName.name=c;
}

void fileName_Name::addNew(OrgType *p, char *c){
    char *s;
    if(!c){
        printf("fileName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("fileName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZfileName.name=s;
}

char* fileName_Name::get(OrgType *p){ return p->ZZds.ZZfileName.name;}

int fileName_Name::compare(OrgType *p1, OrgType *p2){
    return strcmp(p1->ZZds.ZZfileName.name, p2->ZZds.ZZfileName.name);
}

char* fileName_Name::remove(OrgType *p1){char* s=p1->ZZds.ZZfileName.name; p1->ZZds.ZZfileName.name=NULL; return s;}

