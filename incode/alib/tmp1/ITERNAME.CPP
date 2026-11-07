#include <string.h>
class Iterator;

void iterName_Name::add(Iterator *p, char *c){
    char* s=p->ZZds.ZZiterName.name;
    if(s){
        printf("iterName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZiterName.name=c;
}

char* iterName_Name::get(Iterator *p){ return p->ZZds.ZZiterName.name;}

int iterName_Name::compare(Iterator *p1, Iterator *p2){
    return strcmp(p1->ZZds.ZZiterName.name, p2->ZZds.ZZiterName.name);
}
