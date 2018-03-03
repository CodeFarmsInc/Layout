#include <string.h>
class Edge;

void edgeType_Name::add(Edge *p, char *c){
    char* s=p->ZZds.ZZedgeType.name;
    if(s){
        printf("edgeType:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZedgeType.name=c;
}

void edgeType_Name::addNew(Edge *p, char *c){
    char *s;
    if(!c){
        printf("edgeType:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("edgeType:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZedgeType.name=s;
}

char* edgeType_Name::get(Edge *p){ return p->ZZds.ZZedgeType.name;}

int edgeType_Name::compare(Edge *p1, Edge *p2){
    return strcmp(p1->ZZds.ZZedgeType.name, p2->ZZds.ZZedgeType.name);
}

char* edgeType_Name::remove(Edge *p1){char* s=p1->ZZds.ZZedgeType.name; p1->ZZds.ZZedgeType.name=NULL; return s;}

