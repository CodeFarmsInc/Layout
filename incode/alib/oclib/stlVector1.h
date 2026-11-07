
// ----------------------------------------------------------
// -------- aLib interpretation of the STL vector<T> ---------------
// ----------------------------------------------------------
// WARNING: This is only a "how-to-do-it" skeleton with a few methods such as 
//          push_back() and iterator


#ifndef ZZ_$$_VECTOR1_INCLUDED
#define ZZ_$$_VECTOR1_INCLUDED

#include <vector>
using namespace std;
class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_Vector1Parent {
public:
    vector<$2> vect;
    $$_Vector1Parent(){ }
};

class $$_Vector1Child {
};
// ----------------------------------------------------------

class $$_Vector1 {
public:
    // typedef $2* iterator;
    typedef vector<$2>::iterator iterator;
    static iterator begin($1 *p);
    static iterator end($1 *p);

    static void push_back($1 *p, $2 *c);
    // .. all other methods of STL vector

};

#endif // ZZ_$$_VECTOR1_INCLUDED
