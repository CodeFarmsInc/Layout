#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Root;

#include "tmp/bitArr.h"

// -----------------------------------------------
#ifdef ZZmain
bitArr_Array bitArr;

#else // ZZmain
extern bitArr_Array bitArr;
#endif // ZZmain
// -----------------------------------------------


class ZZ_Root {
public:
    bitArr_ArrayHolder ZZbitArr;
};


#endif // ZZ_CODEGEN_INCLUDE
