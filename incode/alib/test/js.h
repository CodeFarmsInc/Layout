#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\lib/general.h"

class Person;
class Couple;
class Header;
// class int;

#include "tmp/people.h"
#include "tmp/name.h"
#include "tmp/per1.h"
#include "tmp/per2.h"
#include "tmp/arr.h"
#include "tmp/cArr.h"

// -----------------------------------------------
people_Ring1 people;
name_Name name;
per1_SingleLink per1;
per2_SingleLink per2;
arr_Array arr;
cArr_Array cArr;
// -----------------------------------------------


class ZZ_Person {
public:
    people_Ring1Element ZZpeople;
    name_NameParent ZZname;
    per1_SingleLinkChild ZZper1;
    per2_SingleLinkChild ZZper2;
};

class ZZ_Couple {
public:
    per1_SingleLinkParent ZZper1;
    per2_SingleLinkParent ZZper2;
    arr_ArrayElement ZZarr;
};

class ZZ_Header {
public:
    arr_ArrayHolder ZZarr;
    cArr_ArrayHolder ZZcArr;
};

class ZZ_int {
public:
    cArr_ArrayElement ZZcArr;
};

typedef people_Ring1Iterator people_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
