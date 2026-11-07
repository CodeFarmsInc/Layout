// --------------------------------------------------------
class PartPtr;
class Part;

Part* const ptr_SingleLink::target(PartPtr *p){
    return p->ZZds.ZZptr.linkTo;
}

void ptr_SingleLink::add(PartPtr *p,Part *c){
    if(p->ZZds.ZZptr.linkTo){
        printf("ptr.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZptr.linkTo = c;
}

void ptr_SingleLink::remove(PartPtr *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZptr.linkTo = NULL;
}
