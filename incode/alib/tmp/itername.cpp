#include <string.h>
class Iterator;

void iterName_Name::add(Iterator *p, char *c){
    char* s=p->ZZds.ZZiterName.name;
    if(s){
        printf("iterName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZiterName.name=c;
}

void iterName_Name::addNew(Iterator *p, char *c){
    char *s;
    if(!c){
        printf("iterName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("iterName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZiterName.name=s;
}

char* iterName_Name::get(Iterator *p){ return p->ZZds.ZZiterName.name;}

int iterName_Name::compare(Iterator *p1, Iterator *p2){
    return strcmp(p1->ZZds.ZZiterName.name, p2->ZZds.ZZiterName.name);
}

char* iterName_Name::remove(Iterator *p1){char* s=p1->ZZds.ZZiterName.name; p1->ZZds.ZZiterName.name=NULL; return s;}

