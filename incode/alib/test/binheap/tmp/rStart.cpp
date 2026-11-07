// --------------------------------------------------------
class Header;
class Employee;

Employee* const rStart_SingleLink::target(Header *p){
    return p->ZZds.ZZrStart.linkTo;
}

void rStart_SingleLink::add(Header *p,Employee *c){
    if(p->ZZds.ZZrStart.linkTo){
        printf("rStart.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZrStart.linkTo = c;
}

void rStart_SingleLink::remove(Header *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZrStart.linkTo = NULL;
}
