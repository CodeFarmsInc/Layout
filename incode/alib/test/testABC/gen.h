#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class A;
class B;
class C;

#include "tmp/AtoB.h"
#include "tmp/AtoB1.h"
#include "tmp/AtoB2.h"
#include "tmp/BtoC.h"
#include "tmp/BtoC1.h"

// -----------------------------------------------
typedef class AtoB_Aggregate2 AtoB;
typedef class BtoC_LinkedList1 BtoC;
// -----------------------------------------------


class ZZ_A {
public:
    AtoB_Aggregate2Parent ZZAtoB;
};

class ZZ_B {
public:
    AtoB_Aggregate2Child ZZAtoB;
    BtoC_LinkedList1Parent ZZBtoC;
};

class ZZ_C {
public:
    BtoC_LinkedList1Child ZZBtoC;
};

typedef AtoB_Aggregate2Iterator AtoB_Iterator;
typedef BtoC_LinkedList1Iterator BtoC_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
