#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Root;
class PartPtr;
class Part;

#include "tmp/myBag.h"
#include "tmp/ptr.h"

// -----------------------------------------------
typedef class myBag_Array myBag;
typedef class ptr_SingleLink ptr;
// -----------------------------------------------


class ZZ_Root {
public:
    myBag_ArrayHolder ZZmyBag;
};

class ZZ_PartPtr {
public:
    ptr_SingleLinkParent ZZptr;
};
#define ZZ_Part static int


#endif // ZZ_CODEGEN_INCLUDE
