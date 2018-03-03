#include <string.h>
class PartType;

void partTypeName_Name::add(PartType *p, char *c){
    char* s=p->ZZds.ZZpartTypeName.name;
    if(s){
        printf("partTypeName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZpartTypeName.name=c;
}

void partTypeName_Name::addNew(PartType *p, char *c){
    char *s;
    if(!c){
        printf("partTypeName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("partTypeName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZpartTypeName.name=s;
}

char* partTypeName_Name::get(PartType *p){ return p->ZZds.ZZpartTypeName.name;}

int partTypeName_Name::compare(PartType *p1, PartType *p2){
    return strcmp(p1->ZZds.ZZpartTypeName.name, p2->ZZds.ZZpartTypeName.name);
}

char* partTypeName_Name::remove(PartType *p1){char* s=p1->ZZds.ZZpartTypeName.name; p1->ZZds.ZZpartTypeName.name=NULL; return s;}

