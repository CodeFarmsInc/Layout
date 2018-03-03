void wVect_Vector1::push_back(Holder *p, Widget *c){
    using namespace std;
    p->ZZds.ZZwVect.vect.push_back(*c);
}    
wVect_Vector1::iterator wVect_Vector1::begin(Holder *p){return p->ZZds.ZZwVect.vect.begin();}
wVect_Vector1::iterator wVect_Vector1::end(Holder *p)  {return p->ZZds.ZZwVect.vect.end();}
