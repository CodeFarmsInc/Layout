#include <string.h>
class Participant;

void partName_Name::add(Participant *p, char *c){
    char* s=p->ZZds.ZZpartName.name;
    if(s){
        printf("partName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZpartName.name=c;
}

void partName_Name::addNew(Participant *p, char *c){
    char *s;
    if(!c){
        printf("partName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("partName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZpartName.name=s;
}

char* partName_Name::get(Participant *p){ return p->ZZds.ZZpartName.name;}

int partName_Name::compare(Participant *p1, Participant *p2){
    return strcmp(p1->ZZds.ZZpartName.name, p2->ZZds.ZZpartName.name);
}

char* partName_Name::remove(Participant *p1){char* s=p1->ZZds.ZZpartName.name; p1->ZZds.ZZpartName.name=NULL; return s;}

