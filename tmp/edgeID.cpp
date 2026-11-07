#include <string.h>
class Edge;

void edgeID_Name::add(Edge *p, char *c){
    char* s=p->ZZds.ZZedgeID.name;
    if(s){
        printf("edgeID:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZedgeID.name=c;
}

void edgeID_Name::addNew(Edge *p, char *c){
    char *s;
    if(!c){
        printf("edgeID:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("edgeID:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZedgeID.name=s;
}

char* edgeID_Name::get(Edge *p){ return p->ZZds.ZZedgeID.name;}

int edgeID_Name::compare(Edge *p1, Edge *p2){
    return strcmp(p1->ZZds.ZZedgeID.name, p2->ZZds.ZZedgeID.name);
}

char* edgeID_Name::remove(Edge *p1){char* s=p1->ZZds.ZZedgeID.name; p1->ZZds.ZZedgeID.name=NULL; return s;}

