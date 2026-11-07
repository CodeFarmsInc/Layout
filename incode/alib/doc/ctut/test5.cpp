#include <stdio.h>
    class LinkedList2;

    class Component {
    friend class LinkedList2;
    friend class LinkedList2Iterator;
        char *cName; // not used in LinkedList2, only for the testing
        Component *next;
        Component *prev;
    public:
        Component(char *name){next=prev=NULL; cName=name;}
        void prt(){printf("   %s\n",cName);}
    };

    class Product {
    friend class LinkedList2;
    friend class LinkedList2Iterator;
        char *pName; // not used in LinkedList2, only for the testing
        Component *tail;
    public:
        Product(char *name){tail=NULL; pName=name;}
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

        if(c->next){
            printf("LinkedList2::addTail() error: child already in a list\n");
            return;
        }
        c1=p->tail;
        if(c1){ 
            c2=c1->next;
            c1->next=c; c->next=c2;
            c2->prev=c; c->prev=c1;
        }
        else {c->next=c->prev=c;}
        p->tail=c;
    }
    void LinkedList2::addHead(Product *p,Component *c){
        Component *c1,*c2;

        addTail(p,c);
        if(p->tail)p->tail=p->tail->prev;
    }

    void LinkedList2::remove(Product *p,Component *c){
        if(c->next==c){p->tail=c->prev=c->next=NULL; return;}
        if(p->tail==c)p->tail=c->prev;
        c->next->prev=c->prev;
        c->prev->next=c->next;
        c->prev=c->next=NULL;
    }

    Component* LinkedList2Iterator::fromHead(Product *p){
        Component *ret;

        forward=1;
        par=p;
        if(p->tail==NULL)return NULL;
        ret=p->tail->next;
        nxt=ret->next;
        if(nxt==ret)nxt=NULL;
        return ret;
    }

    Component* LinkedList2Iterator::fromTail(Product *p){
        Component *ret;

        forward=0;
        par=p;
        ret=p->tail;
        if(ret==NULL)return NULL;
        nxt=ret->prev;
        if(nxt==ret)nxt=NULL;
        return ret;
    }

    Component* LinkedList2Iterator::next(){
        Component *ret;

        ret=nxt;
        if(!ret)return NULL;
        if(forward){
            if(ret==par->tail)nxt=NULL;
            else nxt=ret->next;
        }
        else {
            nxt=ret->prev;
            if(nxt==par->tail)nxt=NULL;
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

    

