#include <string.h>
class Organization;

void orgType_Name::add(Organization *p, char *c){
    char* s=p->ZZds.ZZorgType.name;
    if(s){
        printf("orgType:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZorgType.name=c;
}

char* orgType_Name::get(Organization *p){ return p->ZZds.ZZorgType.name;}

int orgType_Name::compare(Organization *p1, Organization *p2){
    return strcmp(p1->ZZds.ZZorgType.name, p2->ZZds.ZZorgType.name);
}
