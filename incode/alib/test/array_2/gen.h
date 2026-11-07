#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Employee;
class Header;
class PtrEmpl;

#include "tmp/eRing.h"
#include "tmp/eName.h"
#include "tmp/rStart.h"
#include "tmp/pArr.h"
#include "tmp/oArr.h"
#include "tmp/hArr.h"
#include "tmp/hPtr.h"

// -----------------------------------------------
#ifdef ZZmain
eRing_Ring1 eRing;
eName_Name eName;
rStart_SingleLink rStart;
pArr_Array pArr;
oArr_Array oArr;
hArr_Array hArr;
hPtr_SingleLink hPtr;

#else // ZZmain
extern eRing_Ring1 eRing;
extern eName_Name eName;
extern rStart_SingleLink rStart;
extern pArr_Array pArr;
extern oArr_Array oArr;
extern hArr_Array hArr;
extern hPtr_SingleLink hPtr;
#endif // ZZmain
// -----------------------------------------------


class ZZ_Employee {
public:
    eRing_Ring1Element ZZeRing;
    eName_NameParent ZZeName;
};

class ZZ_Header {
public:
    rStart_SingleLinkParent ZZrStart;
    pArr_ArrayHolder ZZpArr;
    oArr_ArrayHolder ZZoArr;
    hArr_ArrayHolder ZZhArr;
};

class ZZ_PtrEmpl {
public:
    hPtr_SingleLinkParent ZZhPtr;
};

typedef eRing_Ring1Iterator eRing_Iterator;
typedef eRing_Ring1Iterator eRing_iterator;

#endif // ZZ_CODEGEN_INCLUDE
