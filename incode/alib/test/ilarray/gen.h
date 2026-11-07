#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Department;
class Employee;

#include "tmp/eArr.h"
#include "tmp/eArr1.h"
#include "tmp/eArr2.h"
#include "tmp/eName.h"
#include "tmp/eList.h"
#include "tmp/eList1.h"

// -----------------------------------------------
typedef class eArr_IndexedLinkArray eArr;
typedef class eName_Name eName;
typedef class eList_LinkedList1 eList;
// -----------------------------------------------


class ZZ_Department {
public:
    eArr_IndexedLinkArrayHolder ZZeArr;
    eList_LinkedList1Parent ZZeList;
};

class ZZ_Employee {
public:
    eArr_IndexedLinkArrayElement ZZeArr;
    eName_NameParent ZZeName;
    eList_LinkedList1Child ZZeList;
};

typedef eList_LinkedList1Iterator eList_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
