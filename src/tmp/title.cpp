#include <string.h>
class Layout;

void title_Name::add(Layout *p, char *c){
    char* s=p->ZZds.ZZtitle.name;
    if(s){
        printf("title:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZtitle.name=c;
}

void title_Name::addNew(Layout *p, char *c){
    char *s;
    if(!c){
        printf("title:addNew() given a NULL name\n"); return;
    }
    s=new char[strlen(c)+1];
    if(!s){
        printf("title:addNew() error: problem to allocate string=%s\n",c); return;
    }
    strcpy(s,c);
    p->ZZds.ZZtitle.name=s;
}

char* title_Name::get(Layout *p){ return p->ZZds.ZZtitle.name;}

int title_Name::compare(Layout *p1, Layout *p2){
    return strcmp(p1->ZZds.ZZtitle.name, p2->ZZds.ZZtitle.name);
}

char* title_Name::remove(Layout *p1){char* s=p1->ZZds.ZZtitle.name; p1->ZZds.ZZtitle.name=NULL; return s;}

