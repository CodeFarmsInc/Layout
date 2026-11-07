#include <string.h>
class Member;

void memberName_Name::add(Member *p, char *c){
    char* s=p->ZZds.ZZmemberName.name;
    if(s){
        printf("memberName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZmemberName.name=c;
}

void memberName_Name::addNew(Member *p, char *c){
    char *s;
    if(!c){
        printf("memberName:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("memberName:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZmemberName.name=s;
}

char* memberName_Name::get(Member *p){ return p->ZZds.ZZmemberName.name;}

int memberName_Name::compare(Member *p1, Member *p2){
    return strcmp(p1->ZZds.ZZmemberName.name, p2->ZZds.ZZmemberName.name);
}

char* memberName_Name::remove(Member *p1){char* s=p1->ZZds.ZZmemberName.name; p1->ZZds.ZZmemberName.name=NULL; return s;}

