
// -------- data structure: array based stack ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class $$_Stack
// ----------------------------------------------------------
#ifndef ZZ_$$_STACK_INCLUDED
#define ZZ_$$_STACK_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_StackHolder : public $$_ArrayHolder {
public:
    $$_StackHolder() : $$_ArrayHolder(){}
};

// ----------------------------------------------------------

class $$_Stack {
public:
    static void push($1 *hp,$2* e){
        $$_Array::push(hp,e);
    }
    static $2* pop($1 *hp){
        return $$_Array::pop(hp);
    }
    static $2* form($1 *hp,unsigned int const sz,int const incr){
        return $$_Array::form(hp,sz,incr);
    }
    static void free($1 *hp){
        $$_Array::free(hp);
    }
    static int size($1 *hp,int* wMark,int* incr){
        return $$_Array::size(hp,wMark,incr);
    }
};

#endif // ZZ_$$_STACK_INCLUDED

