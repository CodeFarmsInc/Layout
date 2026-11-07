#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\..\lib/general.h"

class Mark;
class Student;
class Takes;
class Course;
class Took;
class Year;

#include "tmp/marks.h"
#include "tmp/marks1.h"
#include "tmp/marks2.h"
#include "tmp/marks3.h"
#include "tmp/takes.h"
#include "tmp/takes1.h"
#include "tmp/takes2.h"
#include "tmp/takes3.h"
#include "tmp/takes4.h"
#include "tmp/byYear.h"
#include "tmp/byYear1.h"
#include "tmp/byYear2.h"
#include "tmp/byYear3.h"
#include "tmp/byYear4.h"
#include "tmp/byYear5.h"
#include "tmp/sName.h"
#include "tmp/cName.h"

// -----------------------------------------------
typedef class marks_1XtoX marks;
typedef class takes_2XtoX takes;
typedef class byYear_3XtoX byYear;
typedef class sName_Name sName;
typedef class cName_Name cName;
// -----------------------------------------------


class ZZ_Mark {
public:
    marks_1XtoXRelation ZZmarks;
};

class ZZ_Student {
public:
    marks_1XtoXEntity1 ZZmarks;
    takes_2XtoXEntity1 ZZtakes;
    byYear_3XtoXEntity1 ZZbyYear;
    sName_NameParent ZZsName;
};

class ZZ_Takes {
public:
    takes_2XtoXRelation ZZtakes;
};

class ZZ_Course {
public:
    takes_2XtoXEntity2 ZZtakes;
    byYear_3XtoXEntity2 ZZbyYear;
    cName_NameParent ZZcName;
};

class ZZ_Took {
public:
    byYear_3XtoXRelation ZZbyYear;
};

class ZZ_Year {
public:
    byYear_3XtoXEntity3 ZZbyYear;
};

typedef marks_1XtoXIterator marks_Iterator;
typedef takes_2XtoXIterator takes_Iterator;
typedef byYear_3XtoXIterator byYear_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
