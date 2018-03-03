void $$_Vector1::push_back($1 *p, $2 *c){
    using namespace std;
    p->$0.vect.push_back(*c);
}    
$$_Vector1::iterator $$_Vector1::begin($1 *p){return p->$0.vect.begin();}
$$_Vector1::iterator $$_Vector1::end($1 *p)  {return p->$0.vect.end();}
