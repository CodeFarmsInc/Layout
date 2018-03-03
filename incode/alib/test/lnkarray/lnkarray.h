
// ------------------------------------------------------
// This is a test LinkArray class, simple and testing
// only general functionality and some methods.
// Practically all methods are inherited from class Array.
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

