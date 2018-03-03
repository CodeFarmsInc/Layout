#include <string.h>
class Node;

void nodeName_Name::add(Node *p, char *c){
    char* s=p->ZZds.ZZnodeName.name;
    if(s){
        printf("nodeName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZnodeName.name=c;
}

void nodeName_Name::addNew(Node *p, char *c){
    char *s;
    if(!c){
        printf("nodeName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("nodeName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZnodeName.name=s;
}

char* nodeName_Name::get(Node *p){ return p->ZZds.ZZnodeName.name;}

int nodeName_Name::compare(Node *p1, Node *p2){
    return strcmp(p1->ZZds.ZZnodeName.name, p2->ZZds.ZZnodeName.name);
}

char* nodeName_Name::remove(Node *p1){char* s=p1->ZZds.ZZnodeName.name; p1->ZZds.ZZnodeName.name=NULL; return s;}

