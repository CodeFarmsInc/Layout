#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "lib/general.h"

class Generator;
class Organization;
class Participant;
class OrgType;
class PartType;
class Iterator;
class FixedType;
class ClassLink;
class ApplClass;

#include "tmp/orgs.h"
#include "tmp/orgs1.h"
#include "tmp/parts.h"
#include "tmp/parts1.h"
#include "tmp/parts2.h"
#include "tmp/orgName.h"
#include "tmp/partName.h"
#include "tmp/types.h"
#include "tmp/types1.h"
#include "tmp/partTypes.h"
#include "tmp/partTypes1.h"
#include "tmp/partTypes2.h"
#include "tmp/inherits.h"
#include "tmp/iters.h"
#include "tmp/iters1.h"
#include "tmp/orgTypeName.h"
#include "tmp/fileName.h"
#include "tmp/partTypeName.h"
#include "tmp/iterName.h"
#include "tmp/inhName.h"
#include "tmp/fixedName.h"
#include "tmp/inhMatch.h"
#include "tmp/inhFixed.h"
#include "tmp/fixedTypes.h"
#include "tmp/fixedTypes1.h"
#include "tmp/myType.h"
#include "tmp/myPartType.h"
#include "tmp/toBase.h"
#include "tmp/classes.h"
#include "tmp/classes1.h"
#include "tmp/dependsOn.h"
#include "tmp/dependsOn1.h"
#include "tmp/usedBy.h"
#include "tmp/usedBy1.h"
#include "tmp/usedBy2.h"
#include "tmp/cName.h"

// -----------------------------------------------
typedef class orgs_LinkedList2 orgs;
typedef class parts_Aggregate2 parts;
typedef class orgName_Name orgName;
typedef class partName_Name partName;
typedef class types_LinkedList2 types;
typedef class partTypes_Aggregate2 partTypes;
typedef class inherits_SingleLink inherits;
typedef class iters_LinkedList1 iters;
typedef class orgTypeName_Name orgTypeName;
typedef class fileName_Name fileName;
typedef class partTypeName_Name partTypeName;
typedef class iterName_Name iterName;
typedef class inhName_Name inhName;
typedef class fixedName_Name fixedName;
typedef class inhMatch_SingleLink inhMatch;
typedef class inhFixed_SingleLink inhFixed;
typedef class fixedTypes_LinkedList1 fixedTypes;
typedef class myType_SingleLink myType;
typedef class myPartType_SingleLink myPartType;
typedef class toBase_SingleLink toBase;
typedef class classes_Hash classes;
typedef class dependsOn_LinkedList1 dependsOn;
typedef class usedBy_Aggregate2 usedBy;
typedef class cName_Name cName;
// -----------------------------------------------


class ZZ_Generator {
public:
    orgs_LinkedList2Parent ZZorgs;
    types_LinkedList2Parent ZZtypes;
    classes_HashHolder ZZclasses;
};

class ZZ_Organization {
public:
    orgs_LinkedList2Child ZZorgs;
    parts_Aggregate2Parent ZZparts;
    orgName_NameParent ZZorgName;
    myType_SingleLinkParent ZZmyType;
};

class ZZ_Participant {
public:
    parts_Aggregate2Child ZZparts;
    partName_NameParent ZZpartName;
    myPartType_SingleLinkParent ZZmyPartType;
    usedBy_Aggregate2Child ZZusedBy;
};

class ZZ_OrgType {
public:
    types_LinkedList2Child ZZtypes;
    partTypes_Aggregate2Parent ZZpartTypes;
    inherits_SingleLinkParent ZZinherits;
    iters_LinkedList1Parent ZZiters;
    orgTypeName_NameParent ZZorgTypeName;
    fileName_NameParent ZZfileName;
    fixedTypes_LinkedList1Parent ZZfixedTypes;
};

class ZZ_PartType {
public:
    partTypes_Aggregate2Child ZZpartTypes;
    partTypeName_NameParent ZZpartTypeName;
    inhName_NameParent ZZinhName;
    inhMatch_SingleLinkParent ZZinhMatch;
};

class ZZ_Iterator {
public:
    iters_LinkedList1Child ZZiters;
    iterName_NameParent ZZiterName;
};

class ZZ_FixedType {
public:
    fixedName_NameParent ZZfixedName;
    inhFixed_SingleLinkParent ZZinhFixed;
    fixedTypes_LinkedList1Child ZZfixedTypes;
};

class ZZ_ClassLink {
public:
    toBase_SingleLinkParent ZZtoBase;
    dependsOn_LinkedList1Child ZZdependsOn;
};

class ZZ_ApplClass {
public:
    classes_HashElement ZZclasses;
    dependsOn_LinkedList1Parent ZZdependsOn;
    usedBy_Aggregate2Parent ZZusedBy;
    cName_NameParent ZZcName;
};

typedef orgs_LinkedList2Iterator orgs_Iterator;
typedef parts_Aggregate2Iterator parts_Iterator;
typedef types_LinkedList2Iterator types_Iterator;
typedef partTypes_Aggregate2Iterator partTypes_Iterator;
typedef iters_LinkedList1Iterator iters_Iterator;
typedef fixedTypes_LinkedList1Iterator fixedTypes_Iterator;
typedef classes_HashIterator classes_Iterator;
typedef dependsOn_LinkedList1Iterator dependsOn_Iterator;
typedef usedBy_Aggregate2Iterator usedBy_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
