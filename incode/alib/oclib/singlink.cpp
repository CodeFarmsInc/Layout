// --------------------------------------------------------
class $1;
class $2;

$2* const $$_SingleLink::target($1 *p){
    return p->$0.linkTo;
}

void $$_SingleLink::add($1 *p,$2 *c){
    if(p->$0.linkTo){
        printf("$$.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->$0.linkTo = c;
}

void $$_SingleLink::remove($1 *p){
    // no need for warning or error message if there is no link
    p->$0.linkTo = NULL;
}
