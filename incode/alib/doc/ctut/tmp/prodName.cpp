#include <string.h>
class Product;

void prodName_Name::add(Product *p, char *c){
    char* s=p->ZZds.ZZprodName.name;
    if(s){
        printf("prodName:add() error: object=%d has already a name\n",p); return;
    }
    p->ZZds.ZZprodName.name=c;
}

char* prodName_Name::get(Product *p){ return p->ZZds.ZZprodName.name;}

int prodName_Name::compare(Product *p1, Product *p2){
    return strcmp(p1->ZZds.ZZprodName.name, p2->ZZds.ZZprodName.name);
}

char* prodName_Name::remove(Product *p1){char* s=p1->ZZds.ZZprodName.name; p1->ZZds.ZZprodName.name=NULL; return s;}

