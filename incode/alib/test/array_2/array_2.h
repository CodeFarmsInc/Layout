
// ------------------------------------------------------
// This is test9a from the DOL regression suite, and the results
// should be identical. 
// This is an extensive test of the Array class, together with Ring1,
// SingleLink and Name organizations.

// The Array class is tested as a basic array, array of pointers, binary
// heap, and stack.

// The test problem:
// A set of employee records is loaded into a ring (eRing).
// and from there into array, stack, and heap (hArr). 
// Two sets of tests are made: one for the array of full employee records(oArr),
// the other for the array of pointers (pArr).
// All arrays start with a smaller size than actually
// needed, so that the re-allocation mechanism is tested.

// Input format: employeeName id salary
// ------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include "gen.h"

class Header {
public:
    ZZ_Header ZZds;
};
class Employee {
public:
    ZZ_Employee ZZds;
    int emplNum; // employee number or id
    int salary;
    int heapIndex;
};
class PtrEmpl {
public:
    ZZ_PtrEmpl ZZds;
};

