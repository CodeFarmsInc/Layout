#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Holder;
class Widget;

#include "tmp/wVect.h"

// -----------------------------------------------
typedef class wVect_Vector1 wVect;
// -----------------------------------------------


class ZZ_Holder {
public:
    wVect_Vector1Parent ZZwVect;
};

class ZZ_Widget {
public:
    wVect_Vector1Child ZZwVect;
};


#endif // ZZ_CODEGEN_INCLUDE
