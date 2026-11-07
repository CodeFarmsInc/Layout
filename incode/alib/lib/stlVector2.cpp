$1* $$_Vector2::getParent($2 *c){return c->$0.parent;}
void $$_Vector2::push_back($1 *p, $2 *c){
    c->$0.parent=p;
    $$_Vector1::push_back(p,c);
}    

