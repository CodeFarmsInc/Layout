// --------------------------------------------------------
class $1;
class $2;

$2* const $$_DoubleLink::target($1 *p){
    return $$_SingleLink::target(p);
}

$1* const $$_DoubleLink::source($2 *p){
    return p->$0.linkFrom;
}

void $$_DoubleLink::add($1 *p,$2 *c){
    if(p->$0.linkTo){
        printf("$$.add() error: from-object=%d already has a DoubleLink\n",p);
        return;
    }
    if(c->$0.linkFrom){
        printf("$$.add() error: to-object=%d already has a DoubleLink\n",c);
        return;
    }
    p->$0.linkTo = c;
    c->$0.linkFrom = p;
}

void $$_DoubleLink::remove($1 *p){
    // no need for warning or error message if there is no link
    $2* c=p->$0.linkTo;
    p->$0.linkTo = NULL;
    if(c)c->$0.linkFrom = NULL;
}
