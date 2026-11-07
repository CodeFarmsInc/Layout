#ifndef ZZ_CODEGEN_INCLUDED
#define ZZ_CODEGEN_INCLUDED

#define DataStructure /##/
#define ITERATE(IT,X) for(X= ++IT; X; X= ++IT)

#ifdef ZZmain
#define ZZextern
#else
#define ZZextern extern
#endif


class Generator;
class Organization;
class Participant;
class Iterator;
class PartType;
class FixedType;
class ApplClass;
class ClassLink;

#include "tmp/orgs.h"
#include "tmp/orgs1.h"
#include "tmp/types.h"
#include "tmp/types1.h"
#include "tmp/parts.h"
#include "tmp/parts1.h"
#include "tmp/parts2.h"
#include "tmp/partTypes.h"
#include "tmp/partTypes1.h"
#include "tmp/partTypes2.h"
#include "tmp/inherits.h"
#include "tmp/iters.h"
#include "tmp/iters1.h"
#include "tmp/orgName.h"
#include "tmp/partName.h"
#include "tmp/fileName.h"
#include "tmp/orgTypeName.h"
#include "tmp/partTypeName.h"
#include "tmp/iterName.h"
#include "tmp/inhMatch.h"
#include "tmp/inhName.h"
#include "tmp/fixedName.h"
#include "tmp/inhFixed.h"
#include "tmp/fixedTypes.h"
#include "tmp/fixedTypes1.h"
#include "tmp/myType.h"
#include "tmp/myPartType.h"
#include "tmp/classes.h"
#include "tmp/classes1.h"
#include "tmp/dependsOn.h"
#include "tmp/dependsOn1.h"
#include "tmp/usedBy.h"
#include "tmp/usedBy1.h"
#include "tmp/usedBy2.h"
#include "tmp/toBase.h"
#include "tmp/cName.h"

// -----------------------------------------------
typedef class orgs_LinkedList2 orgs;
typedef class parts_Aggregate2 parts;
typedef class orgName_Name orgName;
typedef class partName_Name partName;
typedef class types_LinkedList2 types;
typedef class partTypes_Aggregate2 partTypes;
typedef class inherits_SingleLink inherits;
typedef class inhMatch_SingleLink inhMatch;
typedef class inhFixed_SingleLink inhFixed;
typedef class fixedTypes_LinkedList1 fixedTypes;
typedef class inhName_Name inhName;
typedef class fixedName_Name fixedName;
typedef class iters_LinkedList1 iters;
typedef class orgTypeName_Name orgTypeName;
typedef class fileName_Name fileName;
typedef class partTypeName_Name partTypeName;
typedef class iterName_Name iterName;
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
    ZZ_Generator() {}
};

class ZZ_Organization {
public:
    orgs_LinkedList2Child ZZorgs;
    parts_Aggregate2Parent ZZparts;
    orgName_NameParent ZZorgName;
    myType_SingleLinkParent ZZmyType;
    ZZ_Organization() {}
};

class ZZ_OrgType {
public:
    types_LinkedList2Child ZZtypes;
    partTypes_Aggregate2Parent ZZpartTypes;
    inherits_SingleLinkParent ZZinherits;
    iters_LinkedList1Parent ZZiters;
    orgTypeName_NameParent ZZorgTypeName;
    fileName_NameParent ZZfileName;
    myType_SingleLink ZZmyType;
    fixedTypes_LinkedList1Parent ZZfixedTypes;
    ZZ_OrgType() {}
};

class ZZ_Participant {
public:
    parts_Aggregate2Child ZZparts;
    usedBy_Aggregate2Child ZZusedBy;
    partName_NameParent ZZpartName;
    myPartType_SingleLinkParent ZZmyPartType;
    ZZ_Participant(){}
};

class ZZ_PartType {
public:
    partTypes_Aggregate2Child ZZpartTypes;
    inhMatch_SingleLinkParent ZZinhMatch;
    partTypeName_NameParent ZZpartTypeName;
    inhName_NameParent ZZinhName;
    ZZ_PartType(){}
};

class ZZ_FixedType {
public:
    fixedTypes_LinkedList1Child ZZfixedTypes;
    inhFixed_SingleLinkParent ZZinhFixed;
    fixedName_NameParent ZZfixedName;
    ZZ_FixedType(){}
};

class ZZ_Iterator {
public:
    iters_LinkedList1Child ZZiters;
    iterName_NameParent ZZiterName;
    ZZ_Iterator() {}
};


class ZZ_ApplClass {
public:
    classes_HashElement ZZclasses;
    dependsOn_LinkedList1Parent ZZdependsOn;
    usedBy_Aggregate2Parent ZZusedBy;
    cName_NameParent ZZcName;
    ZZ_ApplClass() {}
};

class ZZ_ClassLink {
public:
    toBase_SingleLinkParent ZZtoBase;
    dependsOn_LinkedList1Child ZZdependsOn;
    ZZ_ClassLink() {}
};

typedef orgs_LinkedList2Iterator orgs_Iterator;
typedef parts_Aggregate2Iterator parts_Iterator;
typedef types_LinkedList2Iterator types_Iterator;
typedef partTypes_LinkedList2Iterator partTypes_Iterator;
typedef iters_LinkedList1Iterator iters_Iterator;
typedef fixedTypes_LinkedList1Iterator fixedTypes_Iterator;
typedef classes_HashIterator classes_Iterator;
typedef dependsOn_LinkedList1Iterator dependsOn_Iterator;
typedef usedBy_Aggregate2Iterator usedBy_Iterator;

#endif // ZZ_CODEGEN_INCLUDED
