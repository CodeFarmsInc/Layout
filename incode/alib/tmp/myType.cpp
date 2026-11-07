// --------------------------------------------------------
class Organization;
class OrgType;

OrgType* const myType_SingleLink::target(Organization *p){
    return p->ZZds.ZZmyType.linkTo;
}

void myType_SingleLink::add(Organization *p,OrgType *c){
    if(p->ZZds.ZZmyType.linkTo){
        printf("myType.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZmyType.linkTo = c;
}

void myType_SingleLink::remove(Organization *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZmyType.linkTo = NULL;
}
