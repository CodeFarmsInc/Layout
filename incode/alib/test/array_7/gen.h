#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Root;
class Part;

#include "tmp/myBag.h"
#include "tmp/myBag1.h"
#include "tmp/myBag2.h"

// -----------------------------------------------
typedef class myBag_Uni1toX myBag;
// -----------------------------------------------


class ZZ_Root {
public:
    myBag_Uni1toXParent ZZmyBag;
};
#define ZZ_Part static int

typedef myBag_Uni1toXIterator myBag_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
