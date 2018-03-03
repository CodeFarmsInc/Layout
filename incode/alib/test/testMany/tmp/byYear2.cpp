class Student;
class Took;
                          
void byYear_Aggregate2::addHead(Student *p, Took *c){
    if(c->ZZds.ZZbyYear.parent){
        printf("byYear.addHead() error: Child=%d already in byYear_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZbyYear.parent=p;
    byYear_LinkedList2::addHead(p,c);
}
                          
void byYear_Aggregate2::addTail(Student *p, Took *c){
    if(c->ZZds.ZZbyYear.parent){
        printf("byYear.addTail() error: Child=%d already in byYear_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZbyYear.parent=p;
    byYear_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void byYear_Aggregate2::append(Took *c1, Took *c2){
    Student* p=c1->ZZds.ZZbyYear.parent;
    if(!p){
        printf("byYear.append() error: c1=%d not in byYear_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZbyYear.parent){
        printf("byYear.addTail() error: c2=%d already in byYear_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZbyYear.parent=p;
    byYear_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void byYear_Aggregate2::insert(Took *c1, Took *c2){
    Student* p=c2->ZZds.ZZbyYear.parent;
    if(!p){
        printf("byYear.append() error: c2=%d not in byYear_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZbyYear.parent){
        printf("byYear.addTail() error: c1=%d already in byYear_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZbyYear.parent=p;
    byYear_LinkedList2::insert(c1,c2);
}
                          
void byYear_Aggregate2::remove(Took *c){
    Student* p=c->ZZds.ZZbyYear.parent;
    if(p){byYear_LinkedList2::remove(p,c); c->ZZds.ZZbyYear.parent=NULL;}
    else printf("WARNING: byYear.remove() with c=%d already disconnected\n",c);
}

Student* const byYear_Aggregate2::parent(Took *c){
                                                 return c->ZZds.ZZbyYear.parent; }

