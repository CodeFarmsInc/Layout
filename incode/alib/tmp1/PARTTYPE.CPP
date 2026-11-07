#include <string.h>
class Participant;

void partType_Name::add(Participant *p, char *c){
    char* s=p->ZZds.ZZpartType.name;
    if(s){
        printf("partType:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZpartType.name=c;
}

char* partType_Name::get(Participant *p){ return p->ZZds.ZZpartType.name;}

int partType_Name::compare(Participant *p1, Participant *p2){
    return strcmp(p1->ZZds.ZZpartType.name, p2->ZZds.ZZpartType.name);
}
