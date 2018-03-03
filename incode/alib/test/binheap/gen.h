#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Employee;
class Header;
class PtrEmpl;

#include "tmp/eRing.h"
#include "tmp/eName.h"
#include "tmp/rStart.h"
#include "tmp/pHeap.h"
#include "tmp/pHeap1.h"
#include "tmp/eHeap.h"
#include "tmp/eHeap1.h"
#include "tmp/hHeap.h"
#include "tmp/hHeap1.h"
#include "tmp/hPtr.h"

// -----------------------------------------------
typedef class eRing_Ring1 eRing;
typedef class eName_Name eName;
typedef class rStart_SingleLink rStart;
typedef class pHeap_BinaryHeap pHeap;
typedef class eHeap_BinaryHeap eHeap;
typedef class hHeap_BinaryHeap hHeap;
typedef class hPtr_SingleLink hPtr;
// -----------------------------------------------


class ZZ_Employee {
public:
    eRing_Ring1Element ZZeRing;
    eName_NameParent ZZeName;
};

class ZZ_Header {
public:
    rStart_SingleLinkParent ZZrStart;
    pHeap_HeapHolder ZZpHeap;
    eHeap_HeapHolder ZZeHeap;
    hHeap_HeapHolder ZZhHeap;
};

class ZZ_PtrEmpl {
public:
    hPtr_SingleLinkParent ZZhPtr;
};

typedef eRing_Ring1Iterator eRing_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
