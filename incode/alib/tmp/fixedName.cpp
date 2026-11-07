#include <string.h>
class FixedType;

void fixedName_Name::add(FixedType *p, char *c){
    char* s=p->ZZds.ZZfixedName.name;
    if(s){
        printf("fixedName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZfixedName.name=c;
}

void fixedName_Name::addNew(FixedType *p, char *c){
    char *s;
    if(!c){
        printf("fixedName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("fixedName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZfixedName.name=s;
}

char* fixedName_Name::get(FixedType *p){ return p->ZZds.ZZfixedName.name;}

int fixedName_Name::compare(FixedType *p1, FixedType *p2){
    return strcmp(p1->ZZds.ZZfixedName.name, p2->ZZds.ZZfixedName.name);
}

char* fixedName_Name::remove(FixedType *p1){char* s=p1->ZZds.ZZfixedName.name; p1->ZZds.ZZfixedName.name=NULL; return s;}

