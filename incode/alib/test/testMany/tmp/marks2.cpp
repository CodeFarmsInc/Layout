class Student;
class Mark;
                          
void marks_Aggregate2::addHead(Student *p, Mark *c){
    if(c->ZZds.ZZmarks.parent){
        printf("marks.addHead() error: Child=%d already in marks_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZmarks.parent=p;
    marks_LinkedList2::addHead(p,c);
}
                          
void marks_Aggregate2::addTail(Student *p, Mark *c){
    if(c->ZZds.ZZmarks.parent){
        printf("marks.addTail() error: Child=%d already in marks_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZmarks.parent=p;
    marks_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void marks_Aggregate2::append(Mark *c1, Mark *c2){
    Student* p=c1->ZZds.ZZmarks.parent;
    if(!p){
        printf("marks.append() error: c1=%d not in marks_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZmarks.parent){
        printf("marks.addTail() error: c2=%d already in marks_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZmarks.parent=p;
    marks_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void marks_Aggregate2::insert(Mark *c1, Mark *c2){
    Student* p=c2->ZZds.ZZmarks.parent;
    if(!p){
        printf("marks.append() error: c2=%d not in marks_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZmarks.parent){
        printf("marks.addTail() error: c1=%d already in marks_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZmarks.parent=p;
    marks_LinkedList2::insert(c1,c2);
}
                          
void marks_Aggregate2::remove(Mark *c){
    Student* p=c->ZZds.ZZmarks.parent;
    if(p){marks_LinkedList2::remove(p,c); c->ZZds.ZZmarks.parent=NULL;}
    else printf("WARNING: marks.remove() with c=%d already disconnected\n",c);
}

Student* const marks_Aggregate2::parent(Mark *c){
                                                 return c->ZZds.ZZmarks.parent; }

