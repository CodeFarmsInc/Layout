#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Employee;
class Header;

#include "tmp/eRing.h"
#include "tmp/eName.h"
#include "tmp/rStart.h"
#include "tmp/pStack.h"
#include "tmp/eStack.h"

// -----------------------------------------------
typedef class eRing_Ring1 eRing;
typedef class eName_Name eName;
typedef class rStart_SingleLink rStart;
typedef class pStack_Array pStack;
typedef class eStack_Array eStack;
// -----------------------------------------------


class ZZ_Employee {
public:
    eRing_Ring1Element ZZeRing;
    eName_NameParent ZZeName;
};

class ZZ_Header {
public:
    rStart_SingleLinkParent ZZrStart;
    pStack_ArrayHolder ZZpStack;
    eStack_ArrayHolder ZZeStack;
};

typedef eRing_Ring1Iterator eRing_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
