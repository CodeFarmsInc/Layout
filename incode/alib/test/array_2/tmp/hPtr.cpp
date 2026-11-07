// --------------------------------------------------------
class PtrEmpl;
class Employee;

Employee* const hPtr_SingleLink::target(PtrEmpl *p){
    return p->ZZds.ZZhPtr.linkTo;
}

void hPtr_SingleLink::add(PtrEmpl *p,Employee *c){
    if(p->ZZds.ZZhPtr.linkTo){
        printf("hPtr.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZhPtr.linkTo = c;
}

void hPtr_SingleLink::remove(PtrEmpl *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZhPtr.linkTo = NULL;
}
