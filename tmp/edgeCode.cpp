#include <string.h>
class Edge;

void edgeCode_Name::add(Edge *p, char *c){
    char* s=p->ZZds.ZZedgeCode.name;
    if(s){
        printf("edgeCode:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZedgeCode.name=c;
}

void edgeCode_Name::addNew(Edge *p, char *c){
    char *s;
    if(!c){
        printf("edgeCode:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("edgeCode:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZedgeCode.name=s;
}

char* edgeCode_Name::get(Edge *p){ return p->ZZds.ZZedgeCode.name;}

int edgeCode_Name::compare(Edge *p1, Edge *p2){
    return strcmp(p1->ZZds.ZZedgeCode.name, p2->ZZds.ZZedgeCode.name);
}

char* edgeCode_Name::remove(Edge *p1){char* s=p1->ZZds.ZZedgeCode.name; p1->ZZds.ZZedgeCode.name=NULL; return s;}

