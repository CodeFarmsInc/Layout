// --------------------------------------------------------
class ClassLink;
class ApplClass;

ApplClass* const toBase_SingleLink::target(ClassLink *p){
    return p->ZZds.ZZtoBase.linkTo;
}

void toBase_SingleLink::add(ClassLink *p,ApplClass *c){
    if(p->ZZds.ZZtoBase.linkTo){
        printf("toBase.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZtoBase.linkTo = c;
}

void toBase_SingleLink::remove(ClassLink *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZtoBase.linkTo = NULL;
}
