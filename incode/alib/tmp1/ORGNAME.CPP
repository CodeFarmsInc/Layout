#include <string.h>
class Organization;

void orgName_Name::add(Organization *p, char *c){
    char* s=p->ZZds.ZZorgName.name;
    if(s){
        printf("orgName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZorgName.name=c;
}

char* orgName_Name::get(Organization *p){ return p->ZZds.ZZorgName.name;}

int orgName_Name::compare(Organization *p1, Organization *p2){
    return strcmp(p1->ZZds.ZZorgName.name, p2->ZZds.ZZorgName.name);
}
