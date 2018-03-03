#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Header;
class Entry;

#include "tmp/myArray.h"

// -----------------------------------------------
#ifdef ZZmain
myArray_Array myArray;

#else // ZZmain
extern myArray_Array myArray;
#endif // ZZmain
// -----------------------------------------------


class ZZ_Header {
public:
    myArray_ArrayHolder ZZmyArray;
};
#define ZZ_Entry static int


#endif // ZZ_CODEGEN_INCLUDE
