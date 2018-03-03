#include <stdio.h>
    class LinkedList2;
    class Component;
    class Product;

    class LinkedList2Parent {
    public:
        LinkedList2Parent(){tail=NULL;}
        Component *tail; // moved to here from Product
    };

    class LinkedList2Child {
    public:
        LinkedList2Child(){next=prev=NULL;}
        Component *next; // moved to here from Component
        Component *prev; // moved to here from Component
    };
        

    class Component {
    friend class LinkedList2;
    friend class LinkedList2Iterator;
        char *cName; // not used in LinkedList2, only for the testing
    public:
        LinkedList2Child ZZds;
        Component(char *name){cName=name;}
        void prt(){printf("   %s\n",cName);}
    };

    class Product {
    friend class LinkedList2;
    friend class LinkedList2Iterator;
        char *pName; // not used in LinkedList2, only for the testing
    public:
        LinkedList2Parent ZZds;
        Product(char *name){pName=name;}
        void prt(){printf("%s\n",pName);}
    };

    // class which controls the association but keeps no data
    class LinkedList2 {
    public:
        static void addTail(Product *p,Component *c);
        static void addHead(Product *p,Component *c);
        static void remove(Product *p,Component *c);
        // ... more methods
    };

    // iterator which helps to traverse all children
    class LinkedList2Iterator {
        int forward;
        Component *nxt;
        Product *par;
    public:
        LinkedList2Iterator(){forward=1; nxt=NULL; par=NULL;}
        Component *fromHead(Product *p);
        Component *fromTail(Product *p);
        Component *next(); // traverses forward or backward
    };

    // -------------------------------------------------------------
    // Product *p; Component *c;
    // forward traversing: for(c=it.fromHead(); c; c=it.next()){...}
    // reverse traversing: for(c=it.fromTail(); c; c=it.next()){...}
    // -------------------------------------------------------------

    void LinkedList2::addTail(Product *p,Component *c){
        Component *c1,*c2;

        if(c->ZZds.next){
            printf("LinkedList2::addTail() error: child already in a list\n");
            return;
        }
        c1=p->ZZds.tail;
        if(c1){ 
            c2=c1->ZZds.next;
            c1->ZZds.next=c; c->ZZds.next=c2;
            c2->ZZds.prev=c; c->ZZds.prev=c1;
        }
        else {c->ZZds.next=c->ZZds.prev=c;}
        p->ZZds.tail=c;
    }
    void LinkedList2::addHead(Product *p,Component *c){
        Component *c1,*c2;

        addTail(p,c);
        if(p->ZZds.tail)p->ZZds.tail=p->ZZds.tail->ZZds.prev;
    }

    void LinkedList2::remove(Product *p,Component *c){
        if(c->ZZds.next==c){
            p->ZZds.tail=c->ZZds.prev=c->ZZds.next=NULL;
            return;
        }
        if(p->ZZds.tail==c)p->ZZds.tail=c->ZZds.prev;
        c->ZZds.next->ZZds.prev=c->ZZds.prev;
        c->ZZds.prev->ZZds.next=c->ZZds.next;
        c->ZZds.prev=c->ZZds.next=NULL;
    }

    Component* LinkedList2Iterator::fromHead(Product *p){
        Component *ret;

        forward=1;
        par=p;
        if(p->ZZds.tail==NULL)return NULL;
        ret=p->ZZds.tail->ZZds.next;
        nxt=ret->ZZds.next;
        if(nxt==ret)nxt=NULL;
        return ret;
    }

    Component* LinkedList2Iterator::fromTail(Product *p){
        Component *ret;

        forward=0;
        par=p;
        ret=p->ZZds.tail;
        if(ret==NULL)return NULL;
        nxt=ret->ZZds.prev;
        if(nxt==ret)nxt=NULL;
        return ret;
    }

    Component* LinkedList2Iterator::next(){
        Component *ret;

        ret=nxt;
        if(!ret)return NULL;
        if(forward){
            if(ret==par->ZZds.tail)nxt=NULL;
            else nxt=ret->ZZds.next;
        }
        else {
            nxt=ret->ZZds.prev;
            if(nxt==par->ZZds.tail)nxt=NULL;
        }
        return ret;
    }
            
    int main(){
        Product *p; Component *c,*cMot; 
        LinkedList2Iterator it;

        p=new Product("bicycle");
        // load several colour to the list
        c=new Component("wheel"); LinkedList2::addTail(p,c);
        c=new Component("pedal"); LinkedList2::addTail(p,c);
        c=new Component("handlebar"); LinkedList2::addTail(p,c);
        c=new Component("motor"); LinkedList2::addTail(p,c);
        cMot=c; // remember the 'motor' component
        c=new Component("chain"); LinkedList2::addTail(p,c);
        c=new Component("frame"); LinkedList2::addTail(p,c);

        // remove the 'motor' from the component list
        LinkedList2::remove(p,cMot);

        // print the resulting list
        printf("Product: "); p->prt();
        for(c=it.fromHead(p); c; c=it.next()){
            c->prt();
        }
        return 0;
    }

    

