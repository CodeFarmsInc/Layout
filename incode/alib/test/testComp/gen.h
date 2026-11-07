#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Picture;
class Graphics;

#include "tmp/parts.h"
#include "tmp/parts1.h"

// -----------------------------------------------
typedef class parts_LinkedList1 parts;
// -----------------------------------------------


class ZZ_Picture {
public:
    parts_LinkedList1Parent ZZparts;
};

class ZZ_Graphics {
public:
    parts_LinkedList1Child ZZparts;
};

typedef parts_LinkedList1Iterator parts_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
