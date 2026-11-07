#include <string.h>
class Participant;

void partAppl_Name::add(Participant *p, char *c){
    char* s=p->ZZds.ZZpartAppl.name;
    if(s){
        printf("partAppl:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZpartAppl.name=c;
}

char* partAppl_Name::get(Participant *p){ return p->ZZds.ZZpartAppl.name;}

int partAppl_Name::compare(Participant *p1, Participant *p2){
    return strcmp(p1->ZZds.ZZpartAppl.name, p2->ZZds.ZZpartAppl.name);
}
