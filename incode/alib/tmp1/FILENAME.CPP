#include <string.h>
class Organization;

void fileName_Name::add(Organization *p, char *c){
    char* s=p->ZZds.ZZfileName.name;
    if(s){
        printf("fileName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZfileName.name=c;
}

char* fileName_Name::get(Organization *p){ return p->ZZds.ZZfileName.name;}

int fileName_Name::compare(Organization *p1, Organization *p2){
    return strcmp(p1->ZZds.ZZfileName.name, p2->ZZds.ZZfileName.name);
}
