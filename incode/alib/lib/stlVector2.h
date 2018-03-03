
// ----------------------------------------------------------
// -------- bi-directional one-to-many based on the STL vector<T> ---------------
// ----------------------------------------------------------
// WARNING: This is only a "how-to-do-it" skeleton with a few methods such as 
//          push_back() and iterator


#ifndef ZZ_$$_VECTOR2_INCLUDED
#define ZZ_$$_VECTOR2_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_Vector2Parent : public $$_Vector1Parent {
friend class $$_Vector2;
};

class $$_Vector2Child : public $$_Vector1Child {
friend class $$_Vector2;
    $1 *parent;
public:
    $$_Vector2Child():$$_Vector1Child(){parent=NULL;}
};
// ----------------------------------------------------------

class $$_Vector2 : public $$_Vector1 {
public:
    static $1 *getParent($2 *c);

    static void push_back($1 *p, $2 *c);
    // .. all other methods of STL vector
};
    
#endif // ZZ_$$_VECTOR2_INCLUDED
