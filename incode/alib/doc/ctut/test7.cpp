#include <stdio.h>
#include "gen.h"

    class Component {
        char *cName; // not used in LinkedList2, only for the testing
    public:
        ZZ_Component ZZds;
        Component(char *name){cName=name;}
        void prt(){printf("   %s\n",cName);}
    };

    class Product {
        char *pName; // not used in LinkedList2, only for the testing
    public:
        ZZ_Product ZZds;
        Product(char *name){pName=name;}
        void prt(){printf("%s\n",pName);}
    };

    Association LinkedList2<Product,Component> assembly;
            
    int main(){
        Product *p; Component *c,*cMot; 
        assembly_Iterator it;

        p=new Product("bicycle");
        // load several colour to the list
        c=new Component("wheel"); assembly::addTail(p,c);
        c=new Component("pedal"); assembly::addTail(p,c);
        c=new Component("handlebar"); assembly::addTail(p,c);
        c=new Component("motor"); assembly::addTail(p,c);
        cMot=c; // remember the 'motor' component
        c=new Component("chain"); assembly::addTail(p,c);
        c=new Component("frame"); assembly::addTail(p,c);

        // remove the 'motor' from the component list
        assembly::remove(p,cMot);

        // print the resulting list
        printf("Product: "); p->prt();
        for(c=it.fromHead(p); c; c=it.next()){
            c->prt();
        }
        return 0;
    }
#include "gen.cpp"
    

