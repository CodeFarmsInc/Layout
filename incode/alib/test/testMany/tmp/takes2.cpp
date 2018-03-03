class Student;
class Takes;
                          
void takes_Aggregate2::addHead(Student *p, Takes *c){
    if(c->ZZds.ZZtakes.parent){
        printf("takes.addHead() error: Child=%d already in takes_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZtakes.parent=p;
    takes_LinkedList2::addHead(p,c);
}
                          
void takes_Aggregate2::addTail(Student *p, Takes *c){
    if(c->ZZds.ZZtakes.parent){
        printf("takes.addTail() error: Child=%d already in takes_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZtakes.parent=p;
    takes_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void takes_Aggregate2::append(Takes *c1, Takes *c2){
    Student* p=c1->ZZds.ZZtakes.parent;
    if(!p){
        printf("takes.append() error: c1=%d not in takes_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZtakes.parent){
        printf("takes.addTail() error: c2=%d already in takes_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZtakes.parent=p;
    takes_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void takes_Aggregate2::insert(Takes *c1, Takes *c2){
    Student* p=c2->ZZds.ZZtakes.parent;
    if(!p){
        printf("takes.append() error: c2=%d not in takes_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZtakes.parent){
        printf("takes.addTail() error: c1=%d already in takes_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZtakes.parent=p;
    takes_LinkedList2::insert(c1,c2);
}
                          
void takes_Aggregate2::remove(Takes *c){
    Student* p=c->ZZds.ZZtakes.parent;
    if(p){takes_LinkedList2::remove(p,c); c->ZZds.ZZtakes.parent=NULL;}
    else printf("WARNING: takes.remove() with c=%d already disconnected\n",c);
}

Student* const takes_Aggregate2::parent(Takes *c){
                                                 return c->ZZds.ZZtakes.parent; }

