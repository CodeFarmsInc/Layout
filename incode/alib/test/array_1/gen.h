#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Person;
class Couple;
class Header;

#include "tmp/people.h"
#include "tmp/name.h"
#include "tmp/per1.h"
#include "tmp/per2.h"
#include "tmp/arr.h"
#include "tmp/cArr.h"

// -----------------------------------------------
#ifdef ZZmain
people_Ring1 people;
name_Name name;
per1_SingleLink per1;
per2_SingleLink per2;
arr_Array arr;
cArr_Array cArr;

#else // ZZmain
extern people_Ring1 people;
extern name_Name name;
extern per1_SingleLink per1;
extern per2_SingleLink per2;
extern arr_Array arr;
extern cArr_Array cArr;
#endif // ZZmain
// -----------------------------------------------


class ZZ_Person {
public:
    people_Ring1Element ZZpeople;
    name_NameParent ZZname;
};

class ZZ_Couple {
public:
    per1_SingleLinkParent ZZper1;
    per2_SingleLinkParent ZZper2;
};

class ZZ_Header {
public:
    arr_ArrayHolder ZZarr;
    cArr_ArrayHolder ZZcArr;
};

typedef people_Ring1Iterator people_Iterator;
typedef people_Ring1Iterator people_iterator;

#endif // ZZ_CODEGEN_INCLUDE
