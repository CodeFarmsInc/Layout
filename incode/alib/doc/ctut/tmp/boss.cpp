// --------------------------------------------------------
class Department;
class Manager;

Manager* const boss_SingleLink::target(Department *p){
    return p->ZZds.ZZboss.linkTo;
}

void boss_SingleLink::add(Department *p,Manager *c){
    if(p->ZZds.ZZboss.linkTo){
        printf("boss.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZboss.linkTo = c;
}

void boss_SingleLink::remove(Department *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZboss.linkTo = NULL;
}
