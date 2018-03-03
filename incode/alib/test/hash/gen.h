#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Company;
class Employee;

#include "tmp/byName.h"
#include "tmp/byName1.h"
#include "tmp/byID.h"
#include "tmp/byID1.h"
#include "tmp/eName.h"
#include "tmp/eList.h"
#include "tmp/eList1.h"

// -----------------------------------------------
typedef class byName_Hash byName;
typedef class byID_Hash byID;
typedef class eName_Name eName;
typedef class eList_LinkedList1 eList;
// -----------------------------------------------


class ZZ_Company {
public:
    byName_HashHolder ZZbyName;
    byID_HashHolder ZZbyID;
    eList_LinkedList1Parent ZZeList;
};

class ZZ_Employee {
public:
    byName_HashElement ZZbyName;
    byID_HashElement ZZbyID;
    eName_NameParent ZZeName;
    eList_LinkedList1Child ZZeList;
};

typedef byName_HashIterator byName_Iterator;
typedef byID_HashIterator byID_Iterator;
typedef eList_LinkedList1Iterator eList_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
