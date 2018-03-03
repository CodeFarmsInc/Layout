#include <string.h>
class Layout;

void diagramTitle_Name::add(Layout *p, char *c){
    char* s=p->ZZds.ZZdiagramTitle.name;
    if(s){
        printf("diagramTitle:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZdiagramTitle.name=c;
}

void diagramTitle_Name::addNew(Layout *p, char *c){
    char *s;
    if(!c){
        printf("diagramTitle:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("diagramTitle:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZdiagramTitle.name=s;
}

char* diagramTitle_Name::get(Layout *p){ return p->ZZds.ZZdiagramTitle.name;}

int diagramTitle_Name::compare(Layout *p1, Layout *p2){
    return strcmp(p1->ZZds.ZZdiagramTitle.name, p2->ZZds.ZZdiagramTitle.name);
}

char* diagramTitle_Name::remove(Layout *p1){char* s=p1->ZZds.ZZdiagramTitle.name; p1->ZZds.ZZdiagramTitle.name=NULL; return s;}

