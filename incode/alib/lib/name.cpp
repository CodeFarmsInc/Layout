#include <string.h>
class $1;

void $$_Name::add($1 *p, char *c){
    char* s=p->$0.name;
    if(s){
        printf("$$:add() error: object=%d has already a name\n",p); return;
    }
    p->$0.name=c;
}

void $$_Name::addNew($1 *p, char *c){
    char *s;
    if(!c){
        printf("$$:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("$$:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->$0.name=s;
}

char* $$_Name::get($1 *p){ return p->$0.name;}

int $$_Name::compare($1 *p1, $1 *p2){
    return strcmp(p1->$0.name, p2->$0.name);
}

char* $$_Name::remove($1 *p1){char* s=p1->$0.name; p1->$0.name=NULL; return s;}

