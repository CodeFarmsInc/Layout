#include <string.h>
class PartType;

void inhName_Name::add(PartType *p, char *c){
    char* s=p->ZZds.ZZinhName.name;
    if(s){
        printf("inhName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZinhName.name=c;
}

void inhName_Name::addNew(PartType *p, char *c){
    char *s;
    if(!c){
        printf("inhName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("inhName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZinhName.name=s;
}

char* inhName_Name::get(PartType *p){ return p->ZZds.ZZinhName.name;}

int inhName_Name::compare(PartType *p1, PartType *p2){
    return strcmp(p1->ZZds.ZZinhName.name, p2->ZZds.ZZinhName.name);
}

char* inhName_Name::remove(PartType *p1){char* s=p1->ZZds.ZZinhName.name; p1->ZZds.ZZinhName.name=NULL; return s;}

