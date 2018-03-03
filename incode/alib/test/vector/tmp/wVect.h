
// ----------------------------------------------------------
// -------- aLib interpretation of the STL vector<T> ---------------
// ----------------------------------------------------------
// WARNING: This is only a "how-to-do-it" skeleton with a few methods such as 
//          push_back() and iterator


#ifndef ZZ_wVect_VECTOR1_INCLUDED
#define ZZ_wVect_VECTOR1_INCLUDED

#include <vector>
using namespace std;
class Holder;
class Widget;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class wVect_Vector1Parent {
public:
    vector<Widget> vect;
    wVect_Vector1Parent(){ }
};

class wVect_Vector1Child {
};
// ----------------------------------------------------------

class wVect_Vector1 {
public:
    // typedef Widget* iterator;
    typedef vector<Widget>::iterator iterator;
    static iterator begin(Holder *p);
    static iterator end(Holder *p);

    static void push_back(Holder *p, Widget *c);
    // .. all other methods of STL vector

};

#endif // ZZ_wVect_VECTOR1_INCLUDED
