#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "..\incode\alib\lib/general.h"

class Pair;
class Node;
class Layout;
class Group;
class Edge;
class Member;
class Track;
class Net;

#include "tmp/inPair1.h"
#include "tmp/inPair2.h"
#include "tmp/pairs.h"
#include "tmp/pairs1.h"
#include "tmp/groups.h"
#include "tmp/groups1.h"
#include "tmp/nodes.h"
#include "tmp/nodes1.h"
#include "tmp/edges.h"
#include "tmp/edges1.h"
#include "tmp/myGroup.h"
#include "tmp/members.h"
#include "tmp/members1.h"
#include "tmp/memberName.h"
#include "tmp/newLayerArr.h"
#include "tmp/newLayerArr1.h"
#include "tmp/ndIndex.h"
#include "tmp/ndIndex1.h"
#include "tmp/ndIndex2.h"
#include "tmp/sameLayer.h"
#include "tmp/nodeName.h"
#include "tmp/trace.h"
#include "tmp/firstTo.h"
#include "tmp/edgeType.h"
#include "tmp/edgeID.h"
#include "tmp/edgeCode.h"
#include "tmp/sources.h"
#include "tmp/sources1.h"
#include "tmp/sources2.h"
#include "tmp/targets.h"
#include "tmp/targets1.h"
#include "tmp/targets2.h"
#include "tmp/trackArr.h"
#include "tmp/trackArr1.h"
#include "tmp/trackArr2.h"
#include "tmp/byTrack.h"
#include "tmp/byTrack1.h"
#include "tmp/byTrack2.h"
#include "tmp/root.h"
#include "tmp/title.h"
#include "tmp/selectArr.h"
#include "tmp/selectArr1.h"
#include "tmp/nets.h"
#include "tmp/nets1.h"
#include "tmp/nets2.h"
#include "tmp/byNet.h"
#include "tmp/byNet1.h"
#include "tmp/byNet2.h"
#include "tmp/netRelation.h"
#include "tmp/netSource.h"

// -----------------------------------------------
typedef class inPair1_SingleLink inPair1;
typedef class inPair2_SingleLink inPair2;
typedef class pairs_LinkedList1 pairs;
typedef class groups_LinkedList1 groups;
typedef class nodes_LinkedList1 nodes;
typedef class edges_LinkedList1 edges;
typedef class myGroup_SingleLink myGroup;
typedef class members_LinkedList1 members;
typedef class memberName_Name memberName;
typedef class newLayerArr_LinkArray newLayerArr;
typedef class ndIndex_IndexedLinkArray ndIndex;
typedef class sameLayer_Ring1 sameLayer;
typedef class nodeName_Name nodeName;
typedef class trace_SingleLink trace;
typedef class firstTo_SingleLink firstTo;
typedef class edgeType_Name edgeType;
typedef class edgeID_Name edgeID;
typedef class edgeCode_Name edgeCode;
typedef class sources_Aggregate2 sources;
typedef class targets_Aggregate2 targets;
typedef class trackArr_IndexedLinkArray trackArr;
typedef class byTrack_Aggregate2 byTrack;
typedef class root_SingleLink root;
typedef class title_Name title;
typedef class selectArr_LinkArray selectArr;
typedef class nets_Aggregate2 nets;
typedef class byNet_Aggregate2 byNet;
typedef class netRelation_SingleLink netRelation;
typedef class netSource_SingleLink netSource;
// -----------------------------------------------


class ZZ_Pair {
public:
    inPair1_SingleLinkParent ZZinPair1;
    inPair2_SingleLinkParent ZZinPair2;
    pairs_LinkedList1Child ZZpairs;
};

class ZZ_Node {
public:
    nodes_LinkedList1Child ZZnodes;
    myGroup_SingleLinkParent ZZmyGroup;
    members_LinkedList1Parent ZZmembers;
    ndIndex_IndexedLinkArrayElement ZZndIndex;
    sameLayer_Ring1Element ZZsameLayer;
    nodeName_NameParent ZZnodeName;
    trace_SingleLinkParent ZZtrace;
    firstTo_SingleLinkParent ZZfirstTo;
    sources_Aggregate2Parent ZZsources;
    targets_Aggregate2Parent ZZtargets;
};

class ZZ_Layout {
public:
    pairs_LinkedList1Parent ZZpairs;
    groups_LinkedList1Parent ZZgroups;
    nodes_LinkedList1Parent ZZnodes;
    edges_LinkedList1Parent ZZedges;
    newLayerArr_LinkArrayHolder ZZnewLayerArr;
    ndIndex_IndexedLinkArrayHolder ZZndIndex;
    trackArr_IndexedLinkArrayHolder ZZtrackArr;
    root_SingleLinkParent ZZroot;
    title_NameParent ZZtitle;
    selectArr_LinkArrayHolder ZZselectArr;
    nets_Aggregate2Parent ZZnets;
};

class ZZ_Group {
public:
    groups_LinkedList1Child ZZgroups;
};

class ZZ_Edge {
public:
    edges_LinkedList1Child ZZedges;
    edgeType_NameParent ZZedgeType;
    edgeID_NameParent ZZedgeID;
    edgeCode_NameParent ZZedgeCode;
    sources_Aggregate2Child ZZsources;
    targets_Aggregate2Child ZZtargets;
    byTrack_Aggregate2Child ZZbyTrack;
    byNet_Aggregate2Child ZZbyNet;
};

class ZZ_Member {
public:
    members_LinkedList1Child ZZmembers;
    memberName_NameParent ZZmemberName;
};

class ZZ_Track {
public:
    trackArr_IndexedLinkArrayElement ZZtrackArr;
    byTrack_Aggregate2Parent ZZbyTrack;
};

class ZZ_Net {
public:
    nets_Aggregate2Child ZZnets;
    byNet_Aggregate2Parent ZZbyNet;
    netRelation_SingleLinkParent ZZnetRelation;
    netSource_SingleLinkParent ZZnetSource;
};

typedef pairs_LinkedList1Iterator pairs_Iterator;
typedef groups_LinkedList1Iterator groups_Iterator;
typedef nodes_LinkedList1Iterator nodes_Iterator;
typedef edges_LinkedList1Iterator edges_Iterator;
typedef members_LinkedList1Iterator members_Iterator;
typedef sameLayer_Ring1Iterator sameLayer_Iterator;
typedef sources_Aggregate2Iterator sources_Iterator;
typedef targets_Aggregate2Iterator targets_Iterator;
typedef byTrack_Aggregate2Iterator byTrack_Iterator;
typedef nets_Aggregate2Iterator nets_Iterator;
typedef byNet_Aggregate2Iterator byNet_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
