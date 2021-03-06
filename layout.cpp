// STATUS:
// The Java display link is fully operational.
// SVG display is operational including many-to-many and interface/inheritance.
// For remaining problems, read the end of doc/laytutor.doc
// Names and other member-like attributes are displayed within the Node box.
// 
//                                       Jiri Soukup, Sep.19/05
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// JS: POSSIBLE IMPROVEMENTS:
// (1) Allow to start from more roots than one.
// (2) Edges which represent inheritance should get a higher weight
//     (multiplicity?) at least (or just) for the FORCE calculation.
// (3) I tried to avoid unnecessary crossings of lines but there are
//     still some. Perhaps I could use a technique similar to Deutch's
//     dogleg router. Note however that I circumvented his main problem
//     of overlapping vertical lines by shifting them slightly apart.
// (4) For tracks with a short horizontal segment (names overflow)
//     we could use an abbreviation and print a legend on the side
// (5) The Java display should include scroll bars, and a printer/save
//     buttons.
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Parameter file:
// In order to generate the UML diagram of proper dimensions (esthetically
// pleasing and neither too big nor too small for the existing screen),
// this program must read the basic font- and screen parameters from 
// a small file, called parameter file. For the definition and format
// of this file, see the comment part of Layout::graphics().
// This file can be created manually, or preferably automatically
// for example when using Java for the display, program genParFile.java
// generates such file, called java.par. This file has to be created
// only once for the given environment (computer and screen).
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "display.h"
#include "gen.h"

class Layout;
class Edge;
class Node;
class Member;


class Pair {
public:
    ZZ_Pair ZZds;
    double dist;
    Pair(){dist=0.0;}
    Pair(Node *nd1,Node *nd2);
    ~Pair(){
        if(inPair1::target(this))inPair1::remove(this);
        if(inPair2::target(this))inPair2::remove(this);
    }
};

Pair::Pair(Node *nd1,Node *nd2){
    inPair1::add(this,nd1);
    inPair2::add(this,nd2);
    dist=0.0;
}

class Group {
public:
    ZZ_Group ZZds;
    int orderInd; // order index within 'groups' =0,1,2,...
    double center;
    Group(int i){orderInd=i; center=0.0;}
    Group(){orderInd= -1; center=0.0;}
};

class Member {
friend class Node;
friend class Layout;
public:
    ZZ_Member ZZds;
    Member(char *type,char *id){
        char *n; int k;
        k=strlen(type)+strlen(id)+3;
        n=new char[k];
        if(!n){
            printf("string allocation problem in Member(), k=%d\n",k);
            return;
        }
        strcpy(n," ");
        strcat(n,type);
        strcat(n,":");
        strcat(n,id);
        memberName::add(this,n);
    }
    Member(){}
    ~Member(){
        char* nm=memberName::get(this);
        if(nm)delete(nm);
    }
};
    
class Node {
friend class Layout;
friend class Edge;
    int placed;   // 3=placed layers, 2=placed new layer,
                  // 1=unplaced new layer, 0=remaining layers (all unplaced)
    int ix,iy;   // layer (iy) and the position within it
    double x,y;  // resulting layout in window 0<x<1 0<y<1
    int xx,yy;   // x,y converted into pixels, including some shuffelling
    int xOrig,xGap; // temporary variables when compacting rows of nodes
    double xmin,xmax; // limits of connections on the previous layer
    double center;    // 
    int dir; // indicator of direction (0=left, 1=right)
    double dist;   // internal variable for the shortest path algorithm
    int mark; // 0=open, 1=starting set, 2=target set, 3=unavailable
    int count,depth,flg;  // temporary variables for the root-finding algorithm
public:
    ZZ_Node ZZds;
    Node(){
        placed=0;
        ix=iy= -1; x=y=center=xmin=xmax=dist=0.0; xx=yy=0;
        sameLayer::add(this,this);
    }

    ~Node(){ 
        Member *nm;
        members_Iterator nit;
        for(nm=nit.fromHead(this); nm; nm=nit.next()){
            members::remove(this,nm);
            delete nm;
        }
    }
        
    Member *addMember(char *type,char *id){
        Member* nm=new Member(type,id);
        if(!nm)return NULL;
        members::add(this,nm);
        return nm;
    }
};


class Edge {
friend class Layout;
    int blocked; // temporary: when selecting the next node for the new layer
    int mult; // multiplicity of the edge (how many edges between source/target)
    int xs,xt; // source & target coordinates used only in the final display
    int y;     // y-coordinate assigned during the display
    int sMult,tMult; //source/target multiplicity 1,2,. 0=no display, -1=many(*)
    int direction; // 0=both ways, 1= source-to-target, 2=inheritance,
                   // 3=implementing interface in Java.
                   // These must fit 'arrow' in Display::line(..,arrow)
public:
    ZZ_Edge ZZds;
    Edge(){sMult=tMult=direction=mult= blocked=0; xs=xt=y= -1.0;}
    Edge(char *typeName,char *idName){
        sMult=tMult=0; xs=xt=y= -1.0;
        if(!typeName || !idName){printf("error in use of Edge(..)\n"); return;}
        edgeType::addNew(this,typeName);
        edgeID::addNew(this,idName);
        if(!edgeType::get(this) || !edgeID::get(this)){
            printf("allocation error in Edge(..)\n"); return;
        }
    }
    ~Edge(){
        char* type=edgeType::get(this);
        char* id=edgeID::get(this);
        char* code=edgeCode::get(this);

        if(type){ edgeType::remove(this); delete[] type; }
        if(id){ edgeID::remove(this); delete[] id; }
        if(code){ edgeCode::remove(this); delete[] code; }
    }
    Node *getOtherNode(Node *nd);
    int getLayer(); // return minLayer, -1 if the same or not defined
    void prt(char *label);
};

class Net {
friend class Layout;
public:
    ZZ_Net ZZds;
    Net(){}
    Net(Node *relation,Node *source);
};


class Track {
friend class Layout;
    int layer;
    int type; // 1=neighbours same layer, 0=other tracks
    int num;
    double y;
public:
    ZZ_Track ZZds;
    Track(){layer=0; type=0; num=0;}
};

class Layout {
    int automScale; // 0=no scale eforced, 1=y scale to fit the screen
    int numNodes; // number of nodes
    int numEdges; // number of edges
    int infDist;  // distance larger than total of all edges

    // data related to solving the system of equations
    double **matr;   // matrix of num rows and (num+1) columns
                     // only numIndex rows used and (numIndex+1) columns
                     // matr[i][k] is column i row k as used in math
    double *res;     // results of linear equations, capacity num, size=numIndex
    double small;    // small number to eliminate roundoff
    double minSpacing; // min.spacing between class symbols(0.0 means not given)
    double space;      // spacing for the currently processed layer
    // ====================================================================
    // DATA COMING FROM THE PARAMETER FILE
    // Line 1: // dimensions of the screen in pixels
    int xScreen,yScreen; 

    // Line 2: // font for the class names (Courier New, bold assumed)
    int cFont; // typical value=12
    int cx, cUp, cDown; // character size in pixels, y from the text line

    // Line 3: // font for the associations (Courier New, regular assumed)
    int aFont; // typical value=10
    int ax, aUp, aDown; // character size in pixels, y from the text line
    // ====================================================================
    // GEOMETRY LIMITS:
    int boxH,boxW,boxH2,boxW2; // box dimensions and their halves
    int minBoxH; // minimal box hight to accomodate the text
    int boxSpacing; // minimal gap between connected boxes of the same layer
    int boxXframe,boxYframe; // distances to nearest lines or boxes
    int trackSpacing; // spacing between horizontal lines of indirect tracks
    // ====================================================================
   
    Edge *addEdge(
        char *umlCode,char *source,char *target,char *typeName,char *idName);
    Node *getNode(char *nodeName);
    void disposeData();
    int setMatrix();
    int solveEquations();
    void updateNodes();
    double getCost(); // total cost of the current layout (x coordinates only)
    int sortNewLayer();
    void sortNodesAndEdges();
    static int sortFunNodes(const void *p1,const void *p2);
    static int sortFunGroups(const void *p1,const void *p2);
    static int sortFunDouble(const void *p1,const void *p2);
    static int sortFunLayX(const void *p1,const void *p2);
    static int sortFunEdges(const void *p1,const void *p2);
    static int sortFunEdgeList(const void *p1,const void *p2);
    static int sortFunXLST(const void *p1,const void *p2);
    static int sortNodesByLayer(const void *p1,const void *p2);
    int areConnected(Node *n1,Node *n2);
    int fitNodes(int lay,int numPrevLayer);
    int spreadNodes();
    int detectConnectedGroups();
    int spreadFromSeed(int i1,int i2);
    int spreadGroups();
    double getCenter(Group *gr);
    void setCenter(Node *nd);
    int findSeed(int i1,int i2, Node **n1,Node **n2);
    double shortestPath();
    void markPaths(double dist,Node **from,Node **to);
    int addOneEnd(Node *fromNd,Node *toNd,double spacing);
    void prtMatrix(FILE *fp); // debugging print of the matrix
    void prtGroup(int i1,int i2); // debugging print of one group
    void prtNodes(char *label); // debugging printout including 'index'
    void testSolution(); // debugging test, checks result of the equation solver
    void sortSubset(int i1,int i2);
    void markConnectedNodes(Node *nd, Group *gr);
    double pushNode(int dir,int ind,double target,int toCenter);
    void resetX();
    void fitInEdge(Edge *ed,int fromTrack,int layer,int style);
    void eliminateMatchingDoglegs();
    Track *createTrack(int layer,int type);
    void addTracks(int style,int layer,int fromTrack);
    int maxDirectTracks();
    void setSegmentEnds();
    void xToPixels();
    int readParFile(char *parFileName);
    int addMember(char *nodeName,char *type,char *id);
    void findRoot();
    int findDepth(Node *givenNd);
    int getGeomLimits(char *parFileName);
    void fixSegmentConflicts();
    void avoidOverlaps();
    char getMultChar(Edge *ed,int endType);
    double getXscale(double xSpan,int numLayers);
    void removeGroups();
    int changeRootOnNets(int layer);
public:
    ZZ_Layout ZZds;
    Layout(int autS,char *inpFileName){
        title::addNew(this,inpFileName);

        automScale=autS;
        numNodes=numEdges=0;
        infDist=100000.0; // in fact to number of edges would be enough
                          // if we are working in the 0,1 window.
        small=0.0001; // small enough when spreading nodes in (0,1)
        matr=NULL; res=NULL;
        minSpacing=0.0; // default as not given, spread classes across the page
        space=0.5;      // spacing for the currently processed layer
    }
    ~Layout();
    int readInput(FILE *file1);
    int preprocess();
    int place(char *parFileName);
    int route(double trackSpacing);
    void prt(FILE *fp,int style);
    void graphics(Display *disp);
    void debug(char *label);
};

// --------------------------
void Layout::debug(char *label){
     Edge *ed;
     edges_Iterator eit;

     for(ed=eit.fromHead(this); ed; ed=eit.next()){
         if(ed->direction< -1 || ed->direction>3){
           printf("%s: ed=%d %s dir=%d\n",label,edgeID::get(ed),ed->direction);
         }
     }
}

// --------------------------------------------------------------
Layout::~Layout(){
    disposeData();
}

// --------------------------------------------------------------
// Read the little three-line parameter file with the information
// about the screen and font sizes.
// --------------------------------------------------------------
int Layout::readParFile(char *parFileName){
    int i;
    char buff[80];
    FILE* fp=fopen(parFileName,"r");
    if(!fp){
        printf("error: cannot open parameter file=%s\n",parFileName);
        return 1;
    }
    for(i=0; i<3 && fgets(buff,80,fp); i++){
        if     (i==0) sscanf(buff,"%d %d",&xScreen,&yScreen);
        else if(i==1) sscanf(buff,"%d %d %d %d",&cFont,&cx,&cUp,&cDown);
        else if(i==2) sscanf(buff,"%d %d %d %d",&aFont,&ax,&aUp,&aDown);
    }
    fclose(fp);
    if(i<3){
        printf("error reading the parameter file=%s line=%d\n",parFileName,i+1);
        return 1;
    }
    
    // adjust yScreen to the area within the Windows bars
    yScreen=yScreen*(17.5/22.5); // distances measured on the screen
    return 0;
}

// --------------------------------------------------------------
// If there is any internal data, dispose it. This includes array 
// nodes[] and the linked list of the Edges.
// --------------------------------------------------------------
void Layout::disposeData(){
    int i; Edge *e; char *p; Node *n; Pair *pa; Group *gr; Net *nt;
    pairs_Iterator pit;
    groups_Iterator git;
    nodes_Iterator nit;
    edges_Iterator eit;
    nets_Iterator ntit;
    byNet_Iterator bnit;

    p=title::get(this);
    if(p){title::remove(this); delete[] p;}

    for(nt=ntit.fromHead(this); nt; nt=ntit.next()){
        for(e=bnit.fromHead(nt); e; e=bnit.next()){
            byNet::remove(e);
        }
        nets::remove(nt);
        delete nt;
    }

    for(n=nit.fromHead(this); n; n=nit.next()){
        p=nodeName::get(n);
        if(p)delete[] p;
        delete n;
    }
    for(e=eit.fromHead(this); e; e=eit.next()){
        delete e;
    }
    if(matr){
        for(i=0; i<numNodes; i++) delete[] matr[i];
        delete[] matr;
        matr=NULL;
    }
    numNodes=0; numEdges=0; 
    root::remove(this);
    if(res)delete[] res; res=NULL;

    for(pa=pit.fromHead(this); pa; pa=pit.next()){
        pairs::remove(this,pa);
        delete pa;
    }
    
    for(gr=git.fromHead(this); gr; gr=git.next()){
        groups::remove(this,gr);
        delete gr;
    }
    
    if(trackArr::capacity(this)>0) trackArr::free(this);
    selectArr::free(this);
}

// --------------------------------------------------------------
// There can be at most 2*n-1 Nodes, assuming the given root is one of them.
// If it is not, the task has no meaning.
// Returns: 0=everything OK, 1=problems
// --------------------------------------------------------------
int Layout::preprocess(){
    int i,flg; Node *np,*n1,*n2; Edge *ed1,*ed2;
    typedef Node* NodePtr;
    typedef Edge* EdgePtr;
    typedef double* doublePtr;
    edges_Iterator eit1;
    edges_Iterator eit2;

    // at this time numNodes and numEdges are set

    // set the multiplicity of edges, also count the edges
    numEdges=0;
    for(ed1=eit1.fromHead(this); ed1; ed1=eit1.next()){
        numEdges++;
        ed1->mult=0;
        for(ed2=eit2.fromHead(this); ed2; ed2=eit2.next()){

            if((sources::parent(ed1)==sources::parent(ed2) &&
                targets::parent(ed1)==targets::parent(ed2)) ||
               (sources::parent(ed1)==targets::parent(ed2) &&
                targets::parent(ed1)==sources::parent(ed2))){

                (ed1->mult)++;
            }
        }
    }
    // at this time, num is set to the number of nodes

    ndIndex::form(this,numNodes,0);
    matr=new  doublePtr[numNodes+1];
    res=new double[numNodes];
    if(!matr || !res){
        printf("error to allocate matr[%d] or res[%d]\n",numNodes+1,numNodes);
        return 1;
    }
    for(i=0; i<numNodes; i++){
        matr[i]=new double[numNodes];
        if(!matr[i]){
            printf("error to allocate column %d of %d doubles\n",i,numNodes);
            return 1;
        }
    }
    
    i=numEdges; if(i<numNodes)i=numNodes;
    newLayerArr::form(this,i,0);
    selectArr::form(this,i,0);
    trackArr::form(this,i,0);
 
    findRoot();
    if(!root::target(this))return 1;

    return 0;
}

// --------------------------------------------------------------
// debugging print of one Edge
// --------------------------------------------------------------
void Edge::prt(char * label){
    Node *src,*trg;

    src=sources::parent(this);
    trg=targets::parent(this);
    printf("EDGE (%s) from=%s to=%s\n",
                        label,nodeName::get(src),nodeName::get(trg));
}

// --------------------------------------------------------------
// Add a Member to the Node
// Returns: 0=everything OK, 1=allocation error
// --------------------------------------------------------------
int Layout::addMember(char *ndName,char *type,char *id){
    Node *n1; Member *nm;

    n1=getNode(ndName);
    if(!n1){
        printf("problem to allocate Name on %s id=%s\n",ndName,id);
        return 1;
    }
    nm=n1->addMember(type,id);
    if(!nm)return 1; // error
    return 0;
}
  
// --------------------------------------------------------------
// Add one edge to the internal data structure.
// Returns the new Edge, NULL when allocation error
// --------------------------------------------------------------
Edge* Layout::addEdge(
     char *umlCode,char *source,char *target,char *typeName,char *idName){
    Node *n1,*n2; Edge *e; char *src; int interf;

    interf=0;
    src=source;
    if(!strcmp(umlCode,"Inherits") && !strncmp(source,"i:",2)){
        interf=1;
        src= &(source[2]);
    }

    n1=getNode(src);
    n2=getNode(target);
    e=new Edge(typeName,idName);
    if(!n1 || !n2 || !e){
        printf("problem to allocate edge: %s to %s\n",source,target);
        return NULL;
    }
    numEdges++;
    edges::addHead(this,e);
    sources::addHead(n1,e);
    targets::addHead(n2,e);

    if(!strcmp(umlCode,"Inherits")){
        if(interf==1)                          e->direction=3;
        else                                   e->direction=2;
    }
    else if(umlCode[0]=='u' || umlCode[0]=='U')e->direction=1;
    else                                       e->direction=0;

    edgeCode::addNew(e,umlCode);
    if(!edgeCode::get(e)){
        printf("allocation error in addEdge(), aborting ...\n");
        return NULL;
    }
    return e;
}
  
// --------------------------------------------------------------
// Find the node with the given name. If such node
// does not exist, create it, set it up with the given name,
// and add it to the list of all nodes.
// Return NULL when encoutering a name allocation error.
// --------------------------------------------------------------
Node* Layout::getNode(char *ndName){
    char *name; Node *nd;
    nodes_Iterator nit;

    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        if(!strcmp(ndName,nodeName::get(nd)))return nd;
    }
    nd=new Node;
    name=new char[strlen(ndName)+1];
    if(!name || !nd){
        printf("problem to allocate node, name=%s\n",ndName);
        return NULL;
    }
    strcpy(name,ndName);
    numNodes++;
    nodeName::add(nd,name);
    nodes::addHead(this,nd);
    return nd;
}

// --------------------------------------------------------------
// Using the established data structure, place all the nodes
// into 0,1 window (so that node coordinates are 0<x1 0<y<1).
//
// NOTE: This placement creates only the rough relative placement,
//       which will be modified and scaled when generating the actual display
//       in function graphics().
//
// Algorithm - force directed, layer by layer:
// Place the root in the first layer, then repeat this:
// Step 1: Find directly connected nodes (the new layer) and record it in
//         newLayerArr[].
//         Also find groups of nodes connected to them and mark them in 'group'
// Step 2: Use forces to find the positions.
// Step 3: Sort the nodes in the new layer which, in general, form
//   groups of nodes with the same coordinates.
// Step 4: Separately for each group, try all pairs of endpoints, place them
//   in between the adjacent nodes or groups, and use forces to find the
//   positions of the nodes within the group while considering the rest
//   of the new layer fixed. Select the solution with the smallest cost
//   (=sum of square distances of all connections).
// Step 5: Spread the nodes:
//   If the previous layer had more nodes, try to fit similar coordinates,
//   otherwise spread to the full width of the page.
//
// Balancing the forces:
// The forces are in balance when, on every node, the sum of the forces
// is zero. This leads to n linear equations, when n is the number of
// unplaced nodes, including nodes in the new layer. 
// Since all the nodes are assumed connected to the root, this is only
// a small, well behaving matrix, which can be solved by elimination.
// The only danger is that some nodes may end up with the same resulting
// coordinate, but the handling of groups as described above takes care
// of that situation.
//
// Supporting functions:
// (A) setMatrix() sets the matrix  and also ndIndex[] and Node::indx
// (B) solveEquations() solves the linear system of equations.
// (C) getCost() calculates the cost of the solution (sum of distance squares)
//     regardless which nodes are placed and which not.
//       
// minSpacing = minimum x-spacing allowed between nodes. When it is 0.0,
//              each line of nodes will be uniformly spaced in (0,1).
//              If this number is positive but very small, some lines
//              of nodes may be unwieldly long and some of the algorithms
//              may not be optimal dues to round-off errors.
//              Value of 0.05 is most recommended. 
// Returns: 0=placement succeded, 1=failed
// --------------------------------------------------------------
    
int Layout::place(char *parFileName){
    int i,n,k,kk,newLay,lay,numPrevLayer,numGroups,numL; 
    Node *nd,*nxtNd,*rt,*ns; Edge *ed;
    nodes_Iterator nit;
    sources_Iterator sit;
    targets_Iterator tit;
    sameLayer_Iterator SLit;
    
    if(getGeomLimits(parFileName))return 1;

    // in the placement, minSpacing is the lower limit on how close
    // nodes can be placed within one layer. Since the placement works 
    // for x from (0,1), we prorate the center-to-center distance with
    // the size of the screen

    minSpacing=double(boxSpacing+boxW)/xScreen;
    rt=root::target(this);

    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        nd->placed=0;
    }

    // count number of nodes including the root to go to the first layer
    for(ns=SLit.fromHead(rt), kk=0; ns; ns=SLit.next()){
        kk++;
    }

    // start with the root and all nodes that should be on the same layer
    for(ns=SLit.fromHead(rt), k=0; ns; ns=SLit.next(), k++){
        ns->placed=2;
        ns->ix=0; ns->x=(1.0/(kk+1))*(k+1);
        newLayerArr::set(this,k,ns);
    }
    // after the loop, kk is the number of roots on the first layer

    // repeat as long as there is new layer
    for(lay=0; newLayerArr::size(this)>0; lay++){ 
        newLayerArr::init(this); // initiate new layer

        // -------------------------------------------------
        // STEP 1: Find the nodes of the new layer
        // -------------------------------------------------
        for(nd=nit.fromHead(this); nd; nd=nit.next()){
            if(nd->placed==1){
                // repeat this for all nodes to be placed on the same layers
                for(ns=SLit.fromHead(nd); ns; ns=SLit.next()){
                    ns->placed=2;
                }
            }
        }

        if(changeRootOnNets(lay)==0)return 1;

        for(nd=nit.fromHead(this); nd; nd=nit.next()){
            if(nd->placed!=2)continue;

            // mark all connected nodes as the new (still unplaced) new layer
            for(ed=sit.fromHead(nd); ed; ed=sit.next()){
                nxtNd=ed->getOtherNode(nd);
                if(!nxtNd)continue;
                if(nxtNd->placed!=0)continue;
                nxtNd->placed=1;
                newLayerArr::addTail(this,nxtNd);
            }
            for(ed=tit.fromHead(nd); ed; ed=tit.next()){
                nxtNd=ed->getOtherNode(nd);
                if(!nxtNd)continue;
                if(nxtNd->placed!=0)continue;
                nxtNd->placed=1;
                newLayerArr::addTail(this,nxtNd);
            }
        }

        // register the old new layer as fully placed
        numPrevLayer=0;
        for(nd=nit.fromHead(this); nd; nd=nit.next()){
            if(nd->placed!=2)continue;
            nd->placed=3;
            nd->iy=lay;
            numPrevLayer++;
        }

        numL=newLayerArr::size(this);

        if(numL<=0){ // no connected nodes as the new layer
            for(nd=nit.fromHead(this); nd; nd=nit.next()){
                if(nd->placed==0)break;
            }
            if(!nd)continue; // will exit because numNewLayer==0
            // start the new layer with the node from a disconnected set
            findRoot(); // start from a new root
            rt=root::target(this);
            if(rt)nd=rt;
            nd->placed=1;
            newLayerArr::set(this,0,nd);
            continue;
        }

        numGroups=detectConnectedGroups(); // also records groups in 'group'
        if(numGroups<=0)return 1; // error

        // set 'center' for all nodes of the new layer
        numL=newLayerArr::size(this);

        for(i=0; i<numL; i++){
            nd=newLayerArr::get(this,i);
            setCenter(nd);
        }
        // -------------------------------------------------
        // STEP 2: Use forces to find the positions
        // -------------------------------------------------
        if(setMatrix())return 1;  // also sets ndIndex[] and indx
        if(solveEquations())return 1;

        updateNodes(); // record the solution in the nodes


        // -------------------------------------------------
        // STEP 3: Sort the nodes in the new layer, use newLayerArr[]
        // -------------------------------------------------
        if(sortNewLayer())return 1; // also sets up newLayerArr[]
        
        // -------------------------------------------------
        // STEP 4: Optimize order inside the groups with equal x coordinates
        // -------------------------------------------------
        if(spreadGroups())return 1;

        // -------------------------------------------------
        // STEP 5: Spread the nodes 
        // -------------------------------------------------
        sortNewLayer(); 
        if(minSpacing==0.0 && numL>=numPrevLayer){
            // spread the nodes across the page
            if(spreadNodes())return 1;
        }
        else {
            // search for similar coordinates in the previous layer
            resetX();
            if(fitNodes(lay+1,numPrevLayer))return 1;
        }
    }

    // derive Node::y from Node::iy, using lay which is the layer number
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        nd->y=1.0 - (nd->iy + 1.0)/(lay+1);
    }

    removeGroups();
    return 0;
}

// ------------------------------------------------------------------
void Layout::removeGroups(){
    Node *nd; Group *gr;
    groups_Iterator git;
    nodes_Iterator nit;

    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        myGroup::remove(nd);
    }
    for(gr=git.fromHead(this); gr; gr=git.next()){
        groups::remove(this,gr);
        delete gr;
    } 
}

// ------------------------------------------------------------------
// Go through all so far unplaced nodes, and find the one which would
// be the best root for the next (disconnected) section of the UML diagram.
// The function always returns a node. If there were neither associations 
// nor inheritance, it randomly selects one of the nodes.
// Algorithm: (a) The candidates are the nodes with the minimum count, where
//                being not first in an association counts as 1.
//                The ideal root has count=0.
//            (b) If there are more nodes with the same minimal count,
//                select the one with the minimum depth of the attached tree
//                (not considering the directions of the edges).
//            (c) If, after this, there are still several nodes with the
//                minimum depth, select the one which was entered first
//                in the input file. We can assume that, subconsciously, 
//                the programmer entered the most important class or 
//                relations first.
// ------------------------------------------------------------------
void Layout::findRoot(){
    int i,mc,md; Node *nd,*lastNd; Edge *ed;
    nodes_Iterator nit;
    targets_Iterator tit;

    root::remove(this);

    // go through all unplaced nodes
    mc= -1; // will be the minimum count
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        if(nd->placed>0)continue;
        // count how many times this node is a target
        i=0;
        for(ed=tit.fromHead(nd); ed; ed=tit.next()){
            i++;
        }
        nd->count=i;
        if(mc<0 || mc>i)mc=i;
    }
        
    // for nodes with count=mc, find the depth of the attached tree
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        nd->flg=0; // flag all nodes as not accessed
    }
    md= -1; // will be the minimum depth
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        if(nd->placed>0 || nd->count!=mc)continue;
        nd->depth=findDepth(nd);
        if(md<0 || md>nd->depth)md=nd->depth;
    }

    // If there are mode nodes with  count=mc and depth=md, 
    // select the first one which was mentioned in the input file.
    // The first node from the input is the last node in list 'nodes'.
    lastNd=NULL;
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        if(nd->placed==0 &&  nd->count==mc && nd->depth==md)lastNd=nd;
    }

    if(!lastNd)printf("algorithm failure in findRoot(), no nodes left\n");
    else {lastNd->ix=0; lastNd->x=0.5;}

    root::add(this,lastNd);
}

// ------------------------------------------------------------------
// By repeated traversals of all nodes, layer by layer, find the depth
// of the tree associated with the given node. In general, this is not
// a very efficient algorithm, but in UML diagrams the number of layers
// is typically very small, and then this does not really matter.
// We travers only nodes with placed==0. The layers of nodes are
// marked with Node::flg=1,2,..
// next, flg=0 for nodes not contacted yet.
//
// There are no error conditions. If the function returns 0, it means
// the given node is an isolated node.
// ------------------------------------------------------------------
int Layout::findDepth(Node *givenNd){
    Node *nd,*nxtNd; Edge *ed; int depth,expanded;
    nodes_Iterator nit;
    sources_Iterator sit;
    targets_Iterator tit;

    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        nd->flg=0;
    }
    givenNd->flg=1;
    for(depth=1; ; depth++){
        
        expanded=0;
        for(nd=nit.fromHead(this); nd; nd=nit.next()){
            if(nd->flg!=depth)continue;

            for(ed=sit.fromHead(nd); ed; ed=sit.next()){
                nxtNd=ed->getOtherNode(nd);
                if(nxtNd->placed>0 || nxtNd->flg>0)continue;
                expanded=1;
                nxtNd->flg=depth+1;
            }
        
            for(ed=tit.fromHead(nd); ed; ed=tit.next()){
                nxtNd=ed->getOtherNode(nd);
                if(nxtNd->placed>0 || nxtNd->flg>0)continue;
                expanded=1;
                nxtNd->flg=depth+1;
            }
        }
        if(!expanded)break;
    }
    depth--;
    return depth;
}

// --------------------------------------------------------------
// When this function is called, the new layer nodes are already sorted by
// group,x, and center. Within each group, x values are in the range of (0,1)
// and now have to be re-scaled so that x increases between 0 and 1.
// Algorithm:
// The easiest is to spread the nodes uniformly through 0,1
// --------------------------------------------------------------
void Layout::resetX(){
    int i,numL; double d,t; Node *nd;

    numL=newLayerArr::size(this);
    d=1.0/(double)(numL+1);
    // find that range of the groups and that they are reasonable
    for(i=0, t=d; i<numL; i++, t=t+d){ 
        nd=newLayerArr::get(this,i);
        nd->x=t;
    }
}

// --------------------------------------------------------------
// Spread nodes with the same 'group' and 'x'.
// Algorithm:
// Walk through newLayerArr[] and detect sets with the same 'group' and 'x'.
// For each of these sets, find a seed = two most connected nodes.
// Gradually add remaining nodes to one or the other side of the seed.
//
// Returns 0 = everything OK
//         1 = error
// --------------------------------------------------------------
int Layout::spreadGroups(){
    int i1,i2,n; Node *nd1,*nd2;

    n=newLayerArr::size(this);
    for(i1=0; i1<n; i1=i2+1){ 
        nd1=newLayerArr::get(this,i1);
        for(i2=i1+1; i2<n; i2++){
            nd2=newLayerArr::get(this,i2);
            if((nd2->x - nd1->x)>small || 
               (myGroup::target(nd1) != myGroup::target(nd2)))break;
        }
        i2--;
        if(i1==i2)continue;
        if(spreadFromSeed(i1,i2))return 1;
    }
    return 0;
}

// --------------------------------------------------------------
// Debugging print of the nodes in the group stored in newLayerArr[]
// between i1 and i2 inclusive.
// --------------------------------------------------------------
void Layout::prtGroup(int i1,int i2){
    int i; Node *nd;

    printf("GROUP:\n");
    for(i=i1; i<=i2; i++){
        nd=newLayerArr::get(this,i);
        printf("    %s mark=%d placed=%d x=%7.5f ix=%d\n",
                           nodeName::get(nd),nd->mark,nd->placed,nd->x,nd->ix);
    }
}

// --------------------------------------------------------------
// Detect nodes (in the new layer or still unassigned) which are coonected
// to individual nodes of the new layer. Mark these nodes with group=1,2,...
//
// ALGORITHM for finding disconnected sets:
// initialize all nodes with group=0;
// Start with k=0;
// Repeat for all nodes nd in the new layer:
// - if(nd->group)continue;
// - k++
// - set group=k;
// - recursively expand from it to points with group==0 and set group=k;
// Result: There are k disconnected sets, each with unique 'group' value.
//
// What we need is to reset the group indexes (which has been selected 
// in an ad-hoc manner) so they reflect the mutual positions of the groups
// - mutual positions of the center of their connections to previous,
// already established layers.
//
// NOTE: After return, arrays groupArr[] and indConvArr[] are not used
//       anywhere else. They could be allocated as local inside this function,
//       but then why to re-allocate them again and again.
// Returns: number of groups, 0 means errors
// --------------------------------------------------------------
int Layout::detectConnectedGroups(){
    Node *nd; int i,k,n,numL; Group *gr;
    groups_Iterator git;
    nodes_Iterator nit;


    numL=newLayerArr::size(this);
    if(numL<=0){
        printf("placement algorithm failure:\n");
        printf("  detectConnectedGroups() called but no nodes left\n");
        return NULL;
    }
    else {
        for(nd=nit.fromHead(this); nd; nd=nit.next()){
            myGroup::remove(nd);
        }
        for(i=0, k=0; i<numL; i++){
            nd=newLayerArr::get(this,i);
            if(myGroup::target(nd)!=NULL)continue;
            gr=new Group(k);
            if(!gr){
                printf("problem to allocate Group no=%d\n",k);
                return 0;
            }
            k++;
            groups::addTail(this,gr);
            markConnectedNodes(nd,gr); // this is the recursive traversal
        }
    }

    // for each group get its center position (average node coordinate)
    for(gr=git.fromHead(this); gr; gr=git.next()){
        gr->center=getCenter(gr);
    }

    // sort the groups by their 'center'
    groups::sort(Layout::sortFunGroups,this);

    // reset 'orderInd" for all groups
    for(gr=git.fromHead(this), k=0; gr; gr=git.next(), k++){
        gr->orderInd=k;
    }
    return k;
}

// --------------------------------------------------------------
// For all nodes of the new layer which have the given group number,
// return the center x-position, i.e. (minX+maxX)/2 of those already
// placed nodes which connect to this group.
// Return 0.0 if no such connected node exists.
// --------------------------------------------------------------
double Layout::getCenter(Group *gr){
    Node *nxtNd,*nd; Edge *ed; double minX,maxX,x; int i,first,n;
    sources_Iterator sit;
    targets_Iterator tit;
    
    minX=maxX=0.0;
    first=1;
    n=newLayerArr::size(this);
    for(i=0; i<n; i++){
        nd=newLayerArr::get(this,i);
        if(myGroup::target(nd) != gr)continue;

        for(ed=sit.fromHead(nd); ed; ed=sit.next()){
            nxtNd=ed->getOtherNode(nd);
            if(nxtNd->placed!=3)continue;
            x=nxtNd->x;
            if(first) minX=maxX=x;
            else {
                if(minX>x)minX=x;
                if(maxX<x)maxX=x;
            }
            first=0;
        }

        for(ed=tit.fromHead(nd); ed; ed=tit.next()){
            nxtNd=ed->getOtherNode(nd);
            if(nxtNd->placed!=3)continue;
            x=nxtNd->x;
            if(first) minX=maxX=x;
            else {
                if(minX>x)minX=x;
                if(maxX<x)maxX=x;
            }
            first=0;
        }
    }

    return (minX+maxX)/2;
}

// --------------------------------------------------------------
// For the given node, set 'center' as the median of the x coordinates
// of all directly connected nodes in the previous (already finished) layers.
// placed nodes which connect to this group.
// If there are no such nodes, set it to 0.0.
// --------------------------------------------------------------
void Layout::setCenter(Node *nd){
    Node *nxtNd; Edge *ed; double minX,maxX,x; int first;
    sources_Iterator sit;
    targets_Iterator tit;
    
    minX=maxX=0.0;
    first=1;

    for(ed=sit.fromHead(nd); ed; ed=sit.next()){
        nxtNd=ed->getOtherNode(nd);
        if(nxtNd->placed!=3)continue;
        x=nxtNd->x;
        if(first) minX=maxX=x;
        else {
            if(minX>x)minX=x;
            if(maxX<x)maxX=x;
        }
        first=0;
    }

    for(ed=tit.fromHead(nd); ed; ed=tit.next()){
        nxtNd=ed->getOtherNode(nd);
        if(nxtNd->placed!=3)continue;
        x=nxtNd->x;
        if(first) minX=maxX=x;
        else {
            if(minX>x)minX=x;
            if(maxX<x)maxX=x;
        }
        first=0;
    }
    nd->center=(minX+maxX)/2;
    nd->xmin=minX;
    nd->xmax=maxX;
}

// --------------------------------------------------------------
// Recursive expansion to nodes with myGroup not set.
// Set their myGroup to gr.
// Do not expand to nodes with placed==3.
// --------------------------------------------------------------
void Layout::markConnectedNodes(Node *nd, Group *gr){
    Node *nxtNd; Edge *ed;
    sources_Iterator sit;
    targets_Iterator tit;

    myGroup::add(nd,gr);
    for(ed=sit.fromHead(nd); ed; ed=sit.next()){
        nxtNd=ed->getOtherNode(nd);
        if(myGroup::target(nxtNd)!=NULL)continue; // already marked
        if(nxtNd->placed==3)continue;
        markConnectedNodes(nxtNd,gr);
    }
    for(ed=tit.fromHead(nd); ed; ed=tit.next()){
        nxtNd=ed->getOtherNode(nd);
        if(myGroup::target(nxtNd)!=NULL)continue; // already marked
        if(nxtNd->placed==3)continue;
        markConnectedNodes(nxtNd,gr);
    }
}

// --------------------------------------------------------------
// Sort the group stored in newLayerArr[] between i1 and i2 inclusive.
// Sorting is by group,x, and  center.
// Also update Node::ix to the new index in newLayerArr[].
// --------------------------------------------------------------
void Layout::sortSubset(int i1,int i2){
    int i; Node *nd;

    newLayerArr::sortSubset(Layout::sortFunNodes,this,i1,i2);
    for(i=i1; i<=i2; i++){
        nd=newLayerArr::get(this,i);
        nd->ix=i;
    }
}

// --------------------------------------------------------------
// Sort list 'nodes' by lay and x,
// then sort list 'edges' by min x.
// Note how this function is simplified when in-code data structures are used.
// --------------------------------------------------------------
void Layout::sortNodesAndEdges(){
    int i; Node *nd; Edge *ed,*prevE;
  
    nodes::sort(sortFunLayX,this);
    edges::sort(sortFunEdgeList,this);
}


// --------------------------------------------------------------
// For the group specified by the index range i1,i2 (both ends included):
// - Find the seed - two nodes with the maximum connectivity between them.
// - Place the two seed nodes side-by-side (order does not matter).
// - Repeat until all nodes are placed:
//   - Mark all unplaced nodes in the new layer by mark=2, set blocked=0
//     for edges.
//   - Repeat until there is no marked node:
//     - Find the shortest paths between the placed nodes of the new layer
//       and the marked nodes while avoiding blocked edges. (*)
//     - Unmark nodes to which there is no path.
//     - Repeat for all marked nodes:
//       - Trace the path starting from the node, mark all edges blocked=1.
//       - Remember 'from' and 'to' nodes of the last path.
//   - Add the 'from' node on the side of the seed (placed nodes) which is
//     closer to 'to'.
//
// Note (*): The short path algorithm may stop after the first expansion wave
//           when at least one marked node was encountered.
// Returns: 0=everything OK, 1=error
// --------------------------------------------------------------
int Layout::spreadFromSeed(int i1,int i2){
    int ret,i,k;  Node *nd,*n1,*n2,*from,*to,*fromNd,*toNd;
    double d1,d2,d,dist,spacing; Edge *ed;
    nodes_Iterator nit;
    edges_Iterator eit;

    if(i1>i2){
        printf("internal error in spreadFromSeed() i1=%d, i2=%d\n",i1,i2);
        return 1;
    }
    if(i2<=i1+1){ // just place the point or two
        n1=newLayerArr::get(this,i1);
        n2=newLayerArr::get(this,i2);
    }
    else { 
        ret=findSeed(i1,i2,&n1,&n2);
        if(ret==2)return 1; // error
        if(ret==1)return 0; // no seed, other methods must solve this
    }

    // position the seed roughly in the middle of the avaialable space
    if(i1<=0)             d1=0.0;
    else if(myGroup::target(newLayerArr::get(this,i1-1)) != 
            myGroup::target(newLayerArr::get(this,i1)))d1=0.0;
    else d1=newLayerArr::get(this,i1-1)->x;

    if(i2>=newLayerArr::size(this)-1) d2=1.0;
    else if(myGroup::target(newLayerArr::get(this,i2+1)) != 
            myGroup::target(newLayerArr::get(this,i2)))d2=1.0;
    else d2=newLayerArr::get(this,i2+1)->x;

    if(d2-d1<=0.0){
        printf("internal error in spreadFromSeed() d1=%7.5f d2=%7.5f\n",d1,d2);
        return 1;
    }
    // select spacing which would work when adding only to one side
    spacing=0.5*(d2-d1)/(i2-i1+2);
    n1->x=(d1+d2)/2 - spacing/2;
    n2->x=(d1+d2)/2 + spacing/2;
    if(i2<=i1+1){
        n1->placed=n2->placed=2;
        return 0; // trivial case, placement done
    }

    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        if(nd->placed>=2)nd->mark=3; // blocked for the path
        else             nd->mark=0; // may be modified by the next loop
        firstTo::remove(nd);
    }
    for(i=i1; i<=i2; i++){
        nd=newLayerArr::get(this,i);
        if(nd==n1 || nd==n2)nd->mark=1; // starting set
        else                nd->mark=2; // target set
    }
        
    for(;;){ // build the new layer adding one node at each pass
        // mark all edges as not blocked
        for(ed=eit.fromHead(this); ed; ed=eit.next()){
            ed->blocked=0;
        }
        for(k=0, fromNd=toNd=NULL; ;k++){ // repeat until shortestPath() fails

            dist=shortestPath();
            if(dist==0)break; 
                 

            markPaths(dist,&from,&to); // from is unplaced yet, to is placed
            if(!to)break;
            if(k==0){    // remember the first (shortest) path end
                firstTo::remove(from);
                firstTo::add(from,to);
            }
            fromNd=from;  toNd=to;  // remember the last from and to

            // after the first pass, reduce the target set
            if(k==0){
                for(nd=nit.fromHead(this); nd; nd=nit.next()){
                    if(firstTo::target(nd)==NULL && nd->mark==2)nd->mark=3;
                }
            }
        }
        if(!toNd)break;

        // add fromNd to the side of the chain which is closer to toNd
        // IMPORTANT: firstTo must be used, not(!) toNd
        if(addOneEnd(fromNd,firstTo::target(fromNd),spacing))return 1;
        toNd->mark=1;
    }

    // if there are still any nodes with mark=2, place them together
    // at an arbitrary position outside of the placed set
    for(i=i1, d=d1; i<=i2; i++){ // find the largest  x for the placed nodes
        nd=newLayerArr::get(this,i);
        if(nd->mark==1){
            if(d<nd->x)d=nd->x;
        }
    }
    for(i=i1, d=d1; i<=i2; i++){ // place the nodes with mark=2 after the end
        nd=newLayerArr::get(this,i);
        if(nd->mark==2){
            nd->x=(d+d2)/2;
        }
    }

    // re-sort the section of newLayerArr[] between i1 and i2
    sortSubset(i1,i2); // we can sort by x only, all nodes have same 'group'
        
    return 0;
}

// --------------------------------------------------------------
// Algorithm B: For all nodes with the given path length, traverse the path and
//   mark its edges as blocked. Return the end-points of the last path.
// Return nodeFrom=nodeTo=NULL when no path is found.
// --------------------------------------------------------------
void Layout::markPaths(double pathLength,Node **nodeFrom,Node **nodeTo){
    Node *from,*nd,*nxtNd; Edge *ed; int i;
    nodes_Iterator nit;

    *nodeFrom= *nodeTo=NULL;
   
    for(from=nit.fromHead(this); from; from=nit.next()){
        if(from->dist!=pathLength)continue;
        if(from->placed!=1 || trace::target(from)==NULL)continue;
        for(nd=from; nd->dist>0; nd=nxtNd){
            ed=trace::target(nd);
            if(ed->blocked)break;
            if(!ed)break;
            ed->blocked=1;
            nxtNd=ed->getOtherNode(nd);
            if(!nxtNd)break;
        }
        if(nd->dist==0){
            *nodeTo=nd;
            *nodeFrom=from;
        }
    }
    // when *nodeTo is left to NULL on the exit, the path is blocked
}

// --------------------------------------------------------------
// Add fromNd to that end of the existing layer where it will be closer to toNd.
// Use the given spacing for the x coordinate
// Possible errors reported:
// (a) Missing input: one of the nodes is not given (is NULL);
// (b) Confusion: fromNd is already placed, or toNd is not placed yet.
// (c) There are no placed nodes.
// Returns: 0=everything OK, 1=error
// --------------------------------------------------------------
int Layout::addOneEnd(Node *fromNd,Node *toNd,double spacing){
    Node *nd,*n1,*n2; int i,k;
    nodes_Iterator nit;

    if(!fromNd || !toNd){
        printf("internal error in addOneEnd(), given node is NULL\n");
        return 1;
    }
    if(fromNd->mark!=2 || toNd->placed!=1){
        printf("internal error in addOneEnd(), confusion what is placed\n");
        return 1;
    }

    // find placed nodes n1 and n2 with min and max value of x
    n1=n2=NULL;
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        if(nd->mark==1){
            if(n1==NULL || n2==NULL)n1=n2=nd;
            else {
                if(n1->x > nd->x)n1=nd;
                if(n2->x < nd->x)n2=nd;
            }
        }
    }
    if(n1==NULL){
        printf("internal error in addOneEnd(), no placed nodes\n");
        return 1;
    }

    // add fromNd on the side which is closer to toNd
    if(toNd->x - n1->x <= n2->x - toNd->x) fromNd->x=n1->x - spacing;
    else                                   fromNd->x=n2->x + spacing;
    fromNd->mark=1;
    return 0;
}

// --------------------------------------------------------------
// Find the seed for gradually building a new group. These will be
// the two nodes with the maximum connectivity between them (short
// and possibly many paths in parallel). The group is specified
// by the index range i1,i2 (both ends inclusive).
//
// Algorithm:
// - Find the seed, the two nodes on he edge with the maximum multiplicity.
//   This is a simple search through all edges, not a path search.
// - If the result is not unique (several edges with the same multiplicity)
//   find, for each pair, the length of the shortest path between them
//   when the the edges directly connecting them are blocked, then select
//   the pair with the shortest short path.
//
// Returns: 0=seed found OK, 1=no seed, disconnected set, 2=error
// --------------------------------------------------------------
int Layout::findSeed(int i1,int i2, Node **n1,Node **n2){ 
    Node *nd1,*nd2,*nd; Edge *ed; Pair *pa,*nxtPa,*bestPa;
    int i,k,numPairs,bestMult;
    pairs_Iterator pit;
    edges_Iterator eit;
    nodes_Iterator nit;

    // delete all Pairs if there are any 
    for(pa=pit.fromHead(this); pa; pa=pit.next()){
        pairs::remove(this,pa);
        delete pa;
    }

    // Find the highest multiplicity edge with both endpoints falling
    // into the index range i1,i2 (inclusive both ends) of newLayerArr[]
    bestMult=0;
    for(ed=eit.fromHead(this); ed; ed=eit.next()){
        nd1=sources::parent(ed);
        nd2=targets::parent(ed);
        if(nd1==nd2)continue; // disregard connections to itself
        // find whether both nd1 and nd2 are in the group
        k=nd1->ix; 
        if(k<i1 || k>i2 || newLayerArr::get(this,k)!=nd1)continue;
        k=nd2->ix; 
        if(k<i1 || k>i2 || newLayerArr::get(this,k)!=nd2)continue;
        if(ed->mult>bestMult) bestMult=ed->mult;
    }

    // if no pairs, all pairs are equal candidates
    numPairs=0;
    if(bestMult==0){
        for(i=i1; i<=i2; i++){
            for(k=i+1; k<=i2; k++){
                pa=new Pair(newLayerArr::get(this,i),newLayerArr::get(this,k));
                pairs::addHead(this,pa);
                numPairs++;
            }
        }
    }

    // Go again through the same calculation, but this time record 
    // all the pairs with multiplicity = bestMult.
    numPairs=0; // count number of Pairs
    for(ed=eit.fromHead(this); ed; ed=eit.next()){
        nd1=sources::parent(ed);
        nd2=targets::parent(ed);
        if(nd1==nd2)continue; // disregard connections to itself
        // find whether both nd1 and nd2 are in the group
        k=nd1->ix; 
        if(k<i1 || k>i2 || newLayerArr::get(this,k)!=nd1)continue;
        k=nd2->ix; 
        if(k<i1 || k>i2 || newLayerArr::get(this,k)!=nd2)continue;
        
        if(ed->mult!=bestMult)continue;
        pa=new Pair(nd1,nd2);
        pairs::addHead(this,pa);
        numPairs++;
    }
    if(numPairs==1){ // no other selection needed
        pa=pairs::head(this);
        *n1=inPair1::target(pa);
        *n2=inPair2::target(pa);
        return 0;
    }
    
    // additional selection based on the multiple paths
    for(pa=pit.fromHead(this); pa; pa=pit.next()){
        nd1=inPair1::target(pa);
        nd2=inPair2::target(pa);
        for(ed=eit.fromHead(this); ed; ed=eit.next()){
            if(nd1==nd2 || 
                      (nd1==sources::parent(ed) && nd2==targets::parent(ed)) ||
                      (nd2==sources::parent(ed) && nd1==targets::parent(ed))){
                ed->blocked=1;
            }
            else ed->blocked=0;
        }
        for(nd=nit.fromHead(this); nd; nd=nit.next()){
            if(nd->placed>1)nd->mark=3; else nd->mark=0;
        }
        nd1->mark=1; // starting set
        nd2->mark=2; // target set

        pa->dist=shortestPath();
    }
        
    // select the Pair with the shortest secondary path
    for(pa=pit.fromHead(this), bestPa=NULL; pa; pa=pit.next()){
        if(pa->dist<=0.0)continue; 
        if(!bestPa){bestPa=pa; continue;}
        if(bestPa->dist>pa->dist)bestPa=pa;
    }
    // all pairs are equivalent, take the first one
    if(!bestPa)bestPa=pairs::head(this);
    *n1=inPair1::target(bestPa);
    *n2=inPair2::target(bestPa);
    return 0;
}

// --------------------------------------------------------------
// Find the shortest path from the nodes marked the starting set (mark=1)
// to the nodes marked as target set mark=2), but not passing throught
// the nodes marked as unavailable (mark=3).
// The distance between two nodes is 1/mult, where mult is the multiplicity
// of the edges between the two nodes. Mult has been set equal for
// all edges connecting the same nodes (regardless of the direction).
// ALGORITHM:
// Due to the nature of this application, keepins a stack of the expanding
// wave is unnecessary, and we simply pass over all nodes in each expansion.
// Returns: 0.0 path does not exist, >0.0 path found, <0.0 error
// --------------------------------------------------------------
double Layout::shortestPath(){
    Node *nd,*nxtNd; Edge *ed; int expanded; double d,incr,inf;
    nodes_Iterator nit;
    sources_Iterator sit;
    targets_Iterator tit;
    
    inf=numNodes+1.0; // equivalent of infinity
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        if(nd->mark==1)nd->dist=0.0; // already placed nodes
        else           nd->dist=inf;
        trace::remove(nd);
    }
    
    for(d=inf, expanded=1; expanded; ){
        expanded=0;
        for(nd=nit.fromHead(this); nd; nd=nit.next()){ // expand all nodes
            for(ed=sit.fromHead(nd); ed; ed=sit.next()){
                if(ed->blocked)continue;
                nxtNd=ed->getOtherNode(nd);
                if(nxtNd->mark==3)continue;
                incr=1.0/ed->mult;
                if(nxtNd->dist<=nd->dist+incr)continue; // distance must improve
                nxtNd->dist=nd->dist+incr;
                trace::remove(nxtNd); trace::add(nxtNd,ed);
                expanded=1;
                if(nxtNd->mark==2){
                    if(d>nxtNd->dist)d=nxtNd->dist;
                }
            }
            for(ed=tit.fromHead(nd); ed; ed=tit.next()){
                if(ed->blocked)continue;
                nxtNd=ed->getOtherNode(nd);
                if(nxtNd->mark==3)continue;
                incr=1.0/ed->mult;
                if(nxtNd->dist<=nd->dist+incr)continue; // distance must improve
                nxtNd->dist=nd->dist+incr;
                trace::remove(nxtNd); trace::add(nxtNd,ed);
                expanded=1;
                if(nxtNd->mark==2){
                    if(d>nxtNd->dist)d=nxtNd->dist;
                }
            }
        }
    }
    if(d==inf)d=0.0; // the target was not reached
    return d;
}

// --------------------------------------------------------------
// Search for similar coordinates in the previous layer, and
// attempt to use them. Use the number of nodes in the previous layer
// as the guidance how much the nodes may move closer to each other.
// 'lay' is the index of the new layer.
// 'numPrevLayer' is the number of nodes in the previous layer.
//
// Algorithm:
//   For each node in the new layer, we have 'x', 'center' where
//   x would be ideally located from the viewpoint of the previous layer,
//   and then 'xmin' and 'xmax' to where x can move without much affecting
//   the readability of the logic.
//   We let nodes push-and-shove to get to better locations, but for each
//   node two attempts are made:
//    (1) to reach the edge of its xmin,xmax interval
//    (2) to make another move to its center (if possible).
// Returns: 0=correct pass, 1=error
// --------------------------------------------------------------
int Layout::fitNodes(int lay,int numPrevLayer){
    int i,improved,numL; double d; Node *nd;

    d=1.0/(double)(numPrevLayer+1);
    if(numPrevLayer<=1)return 0; // no point to fit for a single root
    if(minSpacing>0.0 && minSpacing<=d)space=minSpacing;
    else space=d;

    // repeat until at the position of at least one node improves
    for(improved=1; improved; ){
        improved=0;
        numL=newLayerArr::size(this);
        for(i=0; i<numL; i++){
            nd=newLayerArr::get(this,i);
            d=nd->center - nd->x;
            if(d==0.0)continue;

            if(d<0.0){ // pushing to the left
                if(nd->x>nd->xmax){
                    // try first to reach at least nd->xmax
                    d=pushNode(-1,i,nd->xmax,0);
                    if(d<0.0){
                        nd->x=nd->x+d;
                        improved=1;
                    }
                    else continue;
                }
                if(nd->x>nd->center && nd->x<=nd->xmax){
                    // try to reach nd->center
                    d=pushNode(-1,i,nd->center,1);
                    if(d<0.0){
                        nd->x=nd->x+d;
                        improved=1;
                    }
                    else continue;
                }
            }

            else { // pushing to the left (case of d==0.0 was already handled)
                if(nd->x<nd->xmin){
                    // try first to reach at least nd->xmin
                    d=pushNode(1,i,nd->xmin,0);
                    if(d>0.0){
                        nd->x=nd->x+d;
                        improved=1;
                    }
                    else continue;
                }
                if(nd->x<nd->center && nd->x>=nd->xmin){
                    // try to reach nd->center
                    d=pushNode(1,i,nd->center,1);
                    if(d>0.0){
                        nd->x=nd->x+d;
                        improved=1;
                    }
                    else continue;
                }
            }
        }
    }
    return 0;
}

// --------------------------------------------------------------
// Recursive call to push neighbouring nodes.
// dir= direction (-1 toward left, +1 toward right);
// ind= index of the node requesting the move
// target= ideal coordinate to which the originating node wants to move (center)
// toCenter=1 when this move was originated as a move toward a center,
//         =0 when it originated as a move toward the edge of xmin,xmax.
//
// Note: Without minTarget, the pushing and shoving may result in nonstop
//       oscilations. In order to reach target, other nodes should NOT be
//       moved away from their centers. However, in order to reach minTarget,
//       nodes can move away from their centers as long as they remain
//       within their own xmin,xmax intervals.
// Return: How much the node which requested this action can actually move.
//         (return 0.0 means no move is possible).
// --------------------------------------------------------------
double Layout::pushNode(int dir,int ind,double target,int toCenter){
    Node *origNd,*nd; double x,move; int numL;

     origNd=newLayerArr::get(this,ind);

    // first handle the situations when hitting the boundary of the area
    if(dir<0 && ind<=0){
        x=target-space;
        if(x<0.0)x=0.0; 
        x=x+space - origNd->x;
        if(x>0.0)x=0.0;
        return x;
        
    }

    numL=newLayerArr::size(this);
    if(dir>0 && ind>=numL-1){
        x=target+space;
        if(x>1.0)x=1.0; 
        x=x-space - origNd->x;
        if(x<0.0)x=0.0;
        return x;
    }

    if(dir<0){
        nd=newLayerArr::get(this,ind-1);
        if(nd->x>origNd->x){
            printf("WARNING: bypass error1 in pushNode(), data not sorted\n");
            printf("         nd=%s x=%7.5f, origNd=%s x=%7.5f\n",
                      nodeName::get(nd),nd->x,nodeName::get(origNd),origNd->x);
            return 0.0;
        }
        if(target-space>=nd->x){ // no move is needed to satisfy the request
            return target - origNd->x;
        }

        // get the limit of how far this node can move
        if(toCenter){
            if(nd->x<nd->center)x=nd->x; else x=nd->center;
        }
        else {
            if(nd->x<nd->xmin)x=nd->x; else x=nd->xmin;
        }

        if(target-space>=x)x=target-space;
        if(x>=origNd->x-space)return 0.0;
        move=pushNode(-1,ind-1,x,toCenter);
        nd->x=nd->x + move;
        x=nd->x+space-origNd->x;
        if(x>0.0)x=0.0;
        return x;
    }
    else {
        nd=newLayerArr::get(this,ind+1);
        if(nd->x<origNd->x){
            printf("WARNING: bypass error2 in pushNode(), data not sorted\n");
            printf("         nd=%s x=%7.5f, origNd=%s x=%7.5f\n",
                      nodeName::get(nd),nd->x,nodeName::get(origNd),origNd->x);
            return 0.0;
        }
        if(target+space<=nd->x){ // no move is needed to satisfy the request
            return target - origNd->x;
        }

        // get the limit of how far this node can move
        if(toCenter){
            if(nd->x>nd->center)x=nd->x; else x=nd->center;
        }
        else {
            if(nd->x>nd->xmax)x=nd->x; else x=nd->xmax;
        }

        if(target+space<=x)x=target+space;
        if(x<=origNd->x+space)return 0.0;
        move=pushNode(1,ind+1,x,toCenter);
        nd->x=nd->x + move;
        x=nd->x-space-origNd->x;
        if(x<0.0)x=0.0;
        return x;
    }
}

// --------------------------------------------------------------
// spread the new layer nodes full width of the page (interval 0,1)
// Returns: 0=normal, 1=error
// --------------------------------------------------------------
int Layout::spreadNodes(){
    int i,numL; Node *nd; double d;

    numL=newLayerArr::size(this);
    d=(double)(numL+1);
    for(i=0; i<numL; i++){
        newLayerArr::get(this,i)->x = (i+1.0)/d;
    }
    return 0; // normal return
}

// --------------------------------------------------------------
// Function for sorting Groups, using 'center'.
// --------------------------------------------------------------
int Layout::sortFunGroups(const void *p1,const void *p2){
    double d; Group *g1,*g2;

    g1=(Group*)p1;
    g2=(Group*)p2;
    d=g1->center - g2->center;
    if(d<0.0)return -1;
    if(d>0.0)return 1;
    return 0;
}

// --------------------------------------------------------------
// Function for sorting an array of doubles
// --------------------------------------------------------------
int Layout::sortFunDouble(const void *p1,const void *p2){
    double *d1,*d2,d;

    d1=(double*)p1;
    d2=(double*)p2;
    d=(*d1)-(*d2);
    if(d<0.0)return -1;
    if(d>0.0)return 1;
    return 0;
}

// --------------------------------------------------------------
// Function for sorting Nodes, using three priorities:
//   group, x, center
// --------------------------------------------------------------
int Layout::sortFunNodes(const void *p1,const void *p2){
    double d; Node **n1,**n2; int g;

    n1=(Node**)p1;
    n2=(Node**)p2;

    g=(myGroup::target(*n1))->orderInd - (myGroup::target(*n2))->orderInd;
    if(g<0.0)return -1;
    if(g>0.0)return 1;

    d=(*n1)->x - (*n2)->x;
    if(d<0.0)return -1;
    if(d>0.0)return 1;

    d=(*n1)->center - (*n2)->center;
    if(d<0.0)return -1;
    if(d>0.0)return 1;
    return 0;
}

// --------------------------------------------------------------
// Function for sorting an array of Node pointers by 'lay' and then by 'x'.
// --------------------------------------------------------------
int Layout::sortFunLayX(const void *p1,const void *p2){
    double d; Node *n1,*n2; int g;

    n1=(Node*)p1;
    n2=(Node*)p2;

    g=n1->iy - n2->iy; // iy stores the layer
    if(g<0.0)return -1;
    if(g>0.0)return 1;

    d=n1->x - n2->x;
    if(d<0.0)return -1;
    if(d>0.0)return 1;
    return 0;
}

// --------------------------------------------------------------
// Function for sorting an array of Edge pointers first by their minimal x
// and then by their max x (both sorted in the ascending order).
// --------------------------------------------------------------
int Layout::sortFunEdges(const void *p1,const void *p2){
    double d,x1min,x1max,x2min,x2max,v1,v2; Edge *e1,*e2; 

    e1= *(Edge**)p1;
    e2= *(Edge**)p2;

    v1=sources::parent(e1)->x; v2=targets::parent(e1)->x; 
    if(v1<v2){x1min=v1; x1max=v2;}
    else     {x1min=v2; x1max=v1;}

    v1=sources::parent(e2)->x; v2=targets::parent(e2)->x; 
    if(v1<v2){x2min=v1; x2max=v2;}
    else     {x2min=v2; x2max=v1;}

    d=x1min - x2min;
    if(d<0.0)return -1;
    if(d>0.0)return 1;
    d=x1max -x2max;
    if(d<0.0)return -1;
    if(d>0.0)return 1;
    return 0;
}

// --------------------------------------------------------------
// Function for sorting a linked list of Edges has identical logic
// except thet the void* input parameters have a different meaning:
// and then by their max x (both sorted in the ascending order).
// --------------------------------------------------------------
int Layout::sortFunEdgeList(const void *p1,const void *p2){
    double d,x1min,x1max,x2min,x2max,v1,v2; Edge *e1,*e2; 

    e1= (Edge*)p1;
    e2= (Edge*)p2;

    v1=sources::parent(e1)->x; v2=targets::parent(e1)->x; 
    if(v1<v2){x1min=v1; x1max=v2;}
    else     {x1min=v2; x1max=v1;}

    v1=sources::parent(e2)->x; v2=targets::parent(e2)->x; 
    if(v1<v2){x2min=v1; x2max=v2;}
    else     {x2min=v2; x2max=v1;}

    d=x1min - x2min;
    if(d<0.0)return -1;
    if(d>0.0)return 1;
    d=x1max -x2max;
    if(d<0.0)return -1;
    if(d>0.0)return 1;
    return 0;
}

// --------------------------------------------------------------
// Function for sorting an array of Edge pointers in the ascending
// order by three priorities:
// (1) The lower layer of the source/target node.
// (2) min(xs,xt)
// (4) max(xs,xt)
//
// NOTE: Undefined layers are treated as -1
// --------------------------------------------------------------
int Layout::sortFunXLST(const void *p1,const void *p2){
    int layo,lay1,lay2; double d,x1min,x1max,x2min,x2max,v1,v2;
    Edge *e1,*e2; 

    e1= *(Edge**)p1;
    e2= *(Edge**)p2;

    lay1=e1->getLayer();
    lay2=e2->getLayer();

    if(lay1<lay2)return -1;
    if(lay1>lay2)return 1;

    v1=e1->xs; v2=e1->xt; 
    if(v1<v2){x1min=v1; x1max=v2;}
    else     {x1min=v2; x1max=v1;}

    v1=e2->xs; v2=e2->xt; 
    if(v1<v2){x2min=v1; x2max=v2;}
    else     {x2min=v2; x2max=v1;}

    d=x1min - x2min;
    if(d<0.0)return -1;
    if(d>0.0)return 1;
    d=x1max -x2max;
    if(d<0.0)return -1;
    if(d>0.0)return 1;
    return 0;
}

// --------------------------------------------------------------
// Sort the nodes in the new layer first by 'group' then by 'x'.
// Set up the array of pointers to nodes which are in the new layer,
// In case of a small difference in x, set x as equal.
// Since we work with variables generally in (0,1), the difference of
// 0.0001 seems like a good 'small' number for this purpose.
// Returns: 0=everything OK, 1=errors
// --------------------------------------------------------------
int Layout::sortNewLayer(){
    int i,j,k,numL;  Node *n1,*n2; double d;

    numL=newLayerArr::size(this);
    sortSubset(0,numL-1); 

    for(i=0; i<numL-1; ){
        n1=newLayerArr::get(this,i);
        for(k=i+1; k<numL; k++){
            n2=newLayerArr::get(this,k);
            if(myGroup::target(n1) != myGroup::target(n2))break;
            if(n2->x - n1->x > small)break;
        }
        if(k==i+1){i++; continue;}
        // index range i,k-1 (both inclusive) should have the same x
        n2=newLayerArr::get(this,k-1);
        d=(n1->x + n2->x)/2;
        for(j=i; j<k; j++)newLayerArr::get(this,j)->x=d;
        i=k;
    }
    return 0;
}

// --------------------------------------------------------------
// Get the total cost of the placement = sum of square distances of
// all the connections, regardless whether placed or floating.
// --------------------------------------------------------------
double Layout::getCost(){
    double cost,d; Edge *ed; Node *n1,*n2;
    edges_Iterator eit;

    cost=0.0;
    for(ed=eit.fromHead(this); ed; ed=eit.next()){
         n1=sources::parent(ed);
         n2=targets::parent(ed);
         d=n1->x - n2->x;
         cost=cost + d*d;
    }
    return cost;
}


// --------------------------------------------------------------
// Using the result of the equation solver, res[], update the nodes.
// --------------------------------------------------------------
void Layout::updateNodes(){
    int i,numI; Node *nd;
 
    numI=ndIndex::size(this);
    for(i=0; i<numI; i++){
        nd=ndIndex::get(this,i);
        nd->x=res[i];
    }
}

// --------------------------------------------------------------
// Set the matrix to solve the node positions. 
// Also set numIndex =number of floating nodes and the true size
// of the matrix, ndIndex[] and Node::indx as references between
// the nodes and the equation solver.
// Returns: 0=everything OK, 1=problems
// --------------------------------------------------------------
int Layout::setMatrix(){
    int i,k,i1,i2,count,numI; Node *nd,*n1,*n2; Edge *ed; double x1,x2;
    edges_Iterator eit;
    nodes_Iterator nit;

    // prepare the mutual conversion
    ndIndex::init(this); // reclaim this array

    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        ndIndex::init(nd); // safety in case ndIndex[] was not used properly
        if(nd->placed>1)continue;
        ndIndex::addTail(this,nd);
    }
    numI=ndIndex::size(this);
    if(numI==0){printf("error in setMatrix(), no data to solve\n"); return 1;}

    // initial the part of the matrix which will be used
    for(i=0; i<=numI; i++){
        for(k=0; k<numI; k++){
            matr[i][k]=0.0;
        }
    }

    // go through all the edges and generate the matrix
    count=0;
    for(ed=eit.fromHead(this); ed; ed=eit.next()){
        n1=sources::parent(ed);
        n2=targets::parent(ed); 
        if(n1->placed>=2 && n2->placed>=2)continue;
        if(n1==n2)continue;

        i1=ndIndex::getIndex(n1); x1=n1->x;
        i2=ndIndex::getIndex(n2); x2=n2->x;
        count++;

        if(n2->placed>=2){
            matr[i1][i1]=matr[i1][i1]+1.0;
            matr[numI][i1]=matr[numI][i1]+x2;
        }
        else if(n1->placed>=2){
            matr[i2][i2]=matr[i2][i2]+1.0;
            matr[numI][i2]=matr[numI][i2]+x1;
        }
        else {
            matr[i1][i1]=matr[i1][i1]+1.0;
            matr[i1][i2]=matr[i1][i2]-1.0;
            matr[i2][i2]=matr[i2][i2]+1.0;
            matr[i2][i1]=matr[i2][i1]-1.0;
        }
    }

    // count contains the number of connections, must be at least numIndex-1
    // otherwise the set is disconnected
    if(count<numI-1){
        printf("error in setMatrix(), disconnected set\n");
        return 1;
    }
    return 0;
}

// --------------------------------------------------------------
// Debugging print of the matrix, including the row/column indexes.
// The function also checks the consistency of indexing between Node:indx
// and ndIndex[] and numIndex.
// --------------------------------------------------------------
void Layout::prtMatrix(FILE *fp){
    int i,k,indx,numI; char *txt; Node *nn,*nd;
    nodes_Iterator nit;

    numI=ndIndex::size(this);

    // verify consistency of indexing
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        indx=ndIndex::getIndex(nd);
        if(indx<0)continue;
        nn=ndIndex::get(this,indx);
        if(nn!=nd){
            if(!nn || !(nodeName::get(nn)))txt="NONE";
            else txt=nodeName::get(nn);

            indx=ndIndex::getIndex(nd);
            fprintf(fp,"ERROR1 in prtMatrix(): nd=%s indx=%d ndIndex[]=%s\n",
                        nodeName::get(nd),indx,txt);
        }
    }

    for(i=0;i<numI; i++){
        nd=ndIndex::get(this,i);
        indx=ndIndex::getIndex(nd);
        if(indx!=i){
            if(!nd || !(nodeName::get(nd)))txt="NONE";
            else txt=nodeName::get(nd);

            if(!nd)k= -1; else k=indx;
            fprintf(fp,"ERROR2 in prtMatrix(): ndIndex[%d]=%s; nd->indx=%d\n",
                        i,txt,indx);
        }
    }

    fprintf(fp,"   ");
    for(k=0; k<numI; k++)fprintf(fp,"%6d ",k); 
    fprintf(fp,"\n");
    for(i=0; i<numI; i++){
        fprintf(fp,"%2d ",i);
        for(k=0; k<=numI; k++)fprintf(fp,"%6.3f ",matr[k][i]);
        nd=ndIndex::get(this,i);
        fprintf(fp,"%s\n",nodeName::get(nd));
    }
}

// --------------------------------------------------------------
// Solve the linear system of equations as in matr[n+1][n]
// where n=numIndexis the number of nodes which can move.
// Store the results in Layout::res[]
//
// Algorithm: Elimination, this is typically a well defined task
//   with a small number of variables.
// Returns: 0=solution found, 1=problems
// --------------------------------------------------------------
int Layout::solveEquations(){
    int i,k,j,numI; double d;
    
    numI=ndIndex::size(this);

    for(i=0; i<numI; i++){
        d=matr[i][i];
        if(d==0.0){
            prtMatrix(stdout);
            printf("error with the internal setup, determinant is 0\n");
            prt(stdout,2);
            return 1;
        }
        for(k=i+1; k<=numI; k++) matr[k][i]=matr[k][i]/d;
        matr[i][i]=1.0; // enforce in order to avoid roundoff error

        for(j=i+1; j<numI; j++){
            d=matr[i][j];
            if(d==0.0)continue;
            for(k=i+1; k<=numI; k++) matr[k][j]=matr[k][j] - d*matr[k][i];
            matr[i][j]=0.0; 
        }
    }

    // We have a triangular matrix, retrieve the solution
    for(i=numI-1; i>=0; i--){
        res[i]=matr[numI][i];
        for(k=i+1; k<numI; k++) res[i]=res[i] - res[k]*matr[k][i];
    }
    return 0;
}

// --------------------------------------------------------------
// This is just a debugging test which tests the result of the equation
// solver by substituting the results and printing the residues by row.
// At the time the solution has been found, the original matrix has
// been modified, so in order to really test the solution, we have
// to reset the matrix.
// --------------------------------------------------------------
void Layout::testSolution(){
    int i,k,numI; double r; Node *nd;

    numI=ndIndex::size(this);

    printf("\nresetting the matrix and testing the solution:\n");
    setMatrix();
    for(i=0; i<numI; i++){
        r=(-matr[numI][i]);
        for(k=0; k<numI; k++) r=r+res[k]*matr[k][i];
        nd=ndIndex::get(this,i);
        printf("i=%d res[i]=%7.5f r=%7.5f %s\n",
                              i,res[i],r,nodeName::get(nd));
    }
}

// --------------------------------------------------------------
// Get other node in other to path through this edge.
// If nd not found, return NULL.
// --------------------------------------------------------------
Node* Edge::getOtherNode(Node *nd){
    if     (sources::parent(this)==nd)return targets::parent(this);
    else if(targets::parent(this)==nd)return sources::parent(this);
    else return NULL;
}

// ------------------------------------------------------------------
// Print the position of all nodes and the connections between them.
// This is the first rough printout, nodes represented as small squares
// connected center-to-center, without any labels or directionality.
// Style of print:
// 0=nodes and edges, names only,
// 1=nodes only: name,ix,iy,x,y
// 2=nodes and edges, full info including routing variables and the new layer
// 3=only the new layer
// 4=only tracks
// ------------------------------------------------------------------
void Layout::prt(FILE *fp,int style){
    Node *nd,*n1,*n2; Edge *ed,*nxtEd; char *traceName; Track *tr;
    int i,lay,xx1,xx2,numL; double x1,x2; char c1,c2;
    int numTr=trackArr::size(this);
    double w=0.01;
    edges_Iterator eit;
    nodes_Iterator nit;
    byTrack_Iterator btit;

    if(style<3){
        fprintf(fp,"NODES:\n");
        for(nd=nit.fromHead(this); nd; nd=nit.next()){
            fprintf(fp,"%s ",nodeName::get(nd));
            if(style==1 || style==2)
                       fprintf(fp,"ix=%d iy=%d x=%7.5f y=%7.5f xx=%d ",
                                         nd->ix,nd->iy,nd->x,nd->y,nd->xx);
            if(style==2){
                ed=trace::target(nd);
                if(!ed)traceName="0";
                else {
                    n1=ed->getOtherNode(nd);
                    if(!n1)traceName="0";
                    else traceName=nodeName::get(n1);
                }
                fprintf(fp,"placed=%d dist=%7.5f trace=%s ",
                  nd->placed,nd->dist,traceName);
            }
            fprintf(fp,"\n");
        }
    }
        
    if(style==0 || style==2){
        fprintf(fp,"EDGES:\n");
        for(ed=eit.fromHead(this); ed; ed=eit.next()){
            n1=sources::parent(ed);
            n2=targets::parent(ed);
            if(!n1 || !n2){
                printf("ERROR: incomplete edge\n");
                continue;
            }
            fprintf(fp,"from=%s to=%s ",nodeName::get(n1),nodeName::get(n2));
            x1=sources::parent(ed)->x; x2=targets::parent(ed)->x;
            if(x2<x1)x1=x2;
            if(style==2)fprintf(fp,"mult=%d blocked=%d xmin=%7.5f ",
                                                  ed->mult,ed->blocked,x1);
            fprintf(fp,"\n");
        }
    }

    if(style==0 || style==1)return;
    fprintf(fp,"NEW LAYER:\n");

    numL=newLayerArr::size(this);
    for(i=0; i<numL; i++){
        nd=newLayerArr::get(this,i);
        fprintf(fp," %s group=%d x=%7.5f center=%7.5f xmin=%7.5f xmax=%7.5f",
                     nodeName::get(nd),(myGroup::target(nd))->orderInd,
                     nd->x,nd->center,nd->xmin,nd->xmax);
        fprintf(fp," mark=%d dist=%7.5f\n",nd->mark,nd->dist);
    }
    fprintf(fp,"\n");

    if(style==4 && numTr>0){
        fprintf(fp,"\nTRACKS:\n");
        for(i=0; i<numTr; i++){
            fprintf(fp,"track=%d lay=%d type=%d\n",
                 i,trackArr::get(this,i)->layer,trackArr::get(this,i)->type);
            lay=trackArr::get(this,i)->layer;
            for(ed=btit.fromHead(trackArr::get(this,i)); ed; ed=btit.next()){
                x1=sources::parent(ed)->x;
                x2=targets::parent(ed)->x;
                xx1=ed->xs;
                xx2=ed->xt;
                if(x1<=x2){
                    if(trackArr::get(this,i)->type==1){c1=c2='=';}
                    else {
                        if(sources::parent(ed)->iy==lay)c1='^'; else c1='v';
                        if(targets::parent(ed)->iy==lay)c2='^'; else c2='v';
                    }
                }
                else {
                    x2=sources::parent(ed)->x;
                    x1=targets::parent(ed)->x;
                    xx2=ed->xs;
                    xx1=ed->xt;

                    if(trackArr::get(this,i)->type==1){c1=c2='=';}
                    else {
                        if(sources::parent(ed)->iy==lay)c2='^'; else c2='v';
                        if(targets::parent(ed)->iy==lay)c2='^'; else c2='v';
                    }
                }
                fprintf(fp,"  %d %c%7.5f,%7.5f%c node from=%s to %s,",
                             i,c1,x1,x2,c2,nodeName::get(sources::parent(ed)),
                                           nodeName::get(targets::parent(ed)));
                tr=byTrack::parent(ed);
                fprintf(fp," pixels=%d,%d track=%d\n",
                                       xx1,xx2,trackArr::getIndex(tr));
            }
        }
    }
}


// ------------------------------------------------------------------
// Generate all the connections representing associations
// trackSpacing=spacing between tracks
// Algorithm:
// Re-use newLayerArr[] for storing all nodes, and sort them by layer & x.
// Proceed layer by layer:
//   Route, gradually adding tracks as needed:
//     (a) connections between neighbours in this layer
//     (b) connections within this layer
//     (c) connection from this layer to higher layers
// Returns: 0=everything OK, 1=errors
// ------------------------------------------------------------------
int Layout::route(double trackSpacing){
    int maxLay,lay,numTr; Node *nd;
    nodes_Iterator nit;

    sortNodesAndEdges(); // sort the list starting with nodes, by layer and x
    // find the highest layer number
    maxLay=0;
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        if(nd->iy>maxLay)maxLay=nd->iy;
    }

    numTr=trackArr::size(this);
    if(numTr!=0){
        printf("internal error, starting routing with number_of_tracks!=0\n");
        return 1;
    }

    // proceed layer by layer
    for(lay=0; lay<=maxLay; lay++){
        // first add all edges between neighbours on this layer
        numTr=trackArr::size(this); // update number of tracks
        addTracks(0,lay,numTr); // 0 for neighbours
        numTr=trackArr::size(this); // update number of tracks

        // then add all edges within this layer
        addTracks(1,lay,numTr); // 1 for the same layer

        // add all remaining edges taking advantage of how they are sorted
        addTracks(2,lay,numTr); // 2 for all remaining edges to this layer
    }
    return 0;
}

// ------------------------------------------------------------------
// Go through all nets and treat only those that have some nodes placed
// and some not. Since this is done for each net only once, 
// we can assume that sources of all edges are the same node, the netSource
// recorded for the net.
// If this source is not on the given layer, we have to find the best node 
// to use as the new root, preferably not the relation.
// Leave the original edge between the source and this node intact and,
// for the remaining edges, just replace the source by the new root.
// All other properties of these edges (direction, multiplicity) remain
// the same.
// Returns: 0=error, 1=no change, 2=root changed
// ------------------------------------------------------------------
int Layout::changeRootOnNets(int layer){
    Net *nt; Edge *ed,*keepEd; Node *src,*nd,*rootNd,*relNd; char c,cc;
    int ret;
    nets_Iterator neit;
    byNet_Iterator bnit;

    ret=1;
    for(nt=neit.fromHead(this); nt; nt=neit.next()){
        src=netSource::target(nt);
        if(src->placed>0)continue; // no need to change the root, or net placed
        relNd=netRelation::target(nt);

        // find a placed target, preferable not the relation
        // at the same time, find code[1] which is not ' '.
        rootNd=NULL;
        keepEd=NULL;
        c=' ';
        for(ed=bnit.fromHead(nt); ed; ed=bnit.next()){
            cc=(edgeCode::get(ed))[1];
            if(cc!=' ')c=cc;

            nd=targets::parent(ed);
            if(nd->placed>0){
                if((nd==relNd && !rootNd) || nd!=relNd){
                    rootNd=nd;
                    keepEd=ed;
                }
            }
        }
        if(!rootNd)continue; // net not involved in the next layer
        netSource::remove(nt);
        netSource::add(nt,rootNd);

        (edgeCode::get(keepEd))[1]=c;
        // reset the source to rootNd for Edges except for keepEd
        for(ed=bnit.fromHead(nt); ed; ed=bnit.next()){
            if(ed==keepEd)continue;

            (edgeCode::get(ed))[1]=' ';
            sources::remove(ed);
            sources::addHead(rootNd,ed);
        }
    }
    return ret;
}

// ------------------------------------------------------------------
// Go through all unassigned edges (they are sorted by layer and xmin)
// and try to add them to the existing tracks starting from 'fromTrack' to 
// (numTracks-1). If there is no space, create a new track for them.
// style=0: add only edges between adjacent nodes on the given 'layer'
//      =1: add edges between any two nodes on the given 'layer'
//      =2: add remaining edges connected to the given 'layer'
// Note that this algorithm could be computationally more efficient,
// but since this application always only a few edges per track,
// the simplicity of the code is more important.
// ------------------------------------------------------------------
void Layout::addTracks(int style,int layer,int fromTrack){
    Node *nd1,*nd2,*nn1,*nn2; Edge *ed,*es; 
    double x1,x2,xs1,xs2,lastX; int i,n,repeat;
    edges_Iterator eit;


    // sort all edges by x1,x2
    for(ed=eit.fromHead(this), n=0; ed; ed=eit.next(), n++){
        selectArr::set(this,n,ed);
    }
    selectArr::sort(Layout::sortFunEdges,this);

    for(repeat=1; repeat; ){ // repeat until there is no qualifying edge
        repeat=0;
        for(i=0, lastX=0.0; i<n; i++){
            ed=selectArr::get(this,i);
            if(byTrack::parent(ed))continue; // edge already assigned to a track
            nd1=sources::parent(ed);
            nd2=targets::parent(ed);
            if(nd1->iy!=layer && nd2->iy!=layer)continue; // not this layer

            if(style==0){
                if(byNet::parent(ed))continue; // nets left for style=2 only
                if(nd1==nd2)continue; // show loops inside the channel
                if(nd1->iy!=layer || nd2->iy!=layer)continue; // not this layer
                if(nd2!=nodes::next(this,nd1) && nd1!=nodes::next(this,nd2))
                                               continue; // not neighbours
            }
            else if(style==1){
                if(nd1->iy!=layer || nd2->iy!=layer)continue; // not both on
            }

            x1=nd1->x; x2=nd2->x;
            if(x1>x2){x1=nd2->x; x2=nd1->x;}

            if(x1<lastX){ repeat=1; continue;}
            lastX=x2;
                
            // ed is eligible to be added but, for style==1,we will first search
            // whether there isn't a shorter edge (es) which falls under
            // x1 and x2, where (x1,x2) is the span of ed. 
            // Using such edge on a lower track number improves the appearance
            // of the routing -- there are fewer crossings of lines.
    
            if(style==1){
                if(byNet::parent(ed))continue; // nets left for style=2 only
                for(es=edges::next(this,ed); es; es=edges::next(this,es)){
                    if(byTrack::parent(es))continue; // edge assigned to track
                    nn1=sources::parent(es);
                    nn2=targets::parent(es);
                    if(nn1->iy!=layer || nn2->iy!=layer)continue;

                    xs1=nn1->x; xs2=nn2->x;
                    if(xs1>xs2){xs1=nn2->x; xs2=nn1->x;}

                    if(xs1>=x2)break; // no reason to continue, edges are sorted
                    if((xs1>=x1 && xs2<x2) || (xs1>x1 && xs2<=x2)){
                        ed=es;
                        repeat=1; // we are jumping over ed, must be done later
                        lastX=xs2;
                        break;
                    }
                }
            }
            
            fitInEdge(ed,fromTrack,layer,style);
        }
    }
}

// ------------------------------------------------------------------
// Add another track as the next entry to array 'trackArr'
// ------------------------------------------------------------------
Track* Layout::createTrack(int layer,int type){
    int numTr; Track *tr;

    tr=new Track;
    tr->layer=layer;
    tr->type=type;
    trackArr::addTail(this,tr);
    return tr;
}

// ------------------------------------------------------------------
// Try to fit ed into existing tracks fromTrack to (numTracks-1),
// keep the edges sorted by x.
// If there are not such tracks or if there isn's space on them,
// create a new track and add ed to it.
// Edges of a net are inserted as if they have the width of the entire net,
// but edges of the same net do not interfere with each other.
// ------------------------------------------------------------------
void Layout::fitInEdge(Edge *ed,int fromTrack,int layer,int style){
    Edge *e,*nxtEd,*lastEd; Net *nt;  Track *tr;

    int t,success,type,fail,numTr; double xsrc,xtrg,x1,x2,xx1,xx2;
    byTrack_Iterator btit;
    byNet_Iterator bnit;

    if(style==0)type=1; else type=0;

    numTr=trackArr::size(this);
    if(numTr<=fromTrack){ // pick up the next Track from trackArr[]
        createTrack(layer,type);
    }

    nt=byNet::parent(ed);
    if(nt){
        x1=x2=sources::parent(ed)->x;
        for(e=bnit.fromHead(nt); e; e=bnit.next()){
            xsrc=sources::parent(e)->x;
            xtrg=targets::parent(e)->x;
            if(xsrc<x1)x1=xsrc;
            if(xtrg<x1)x1=xtrg;
            if(xsrc>x2)x2=xsrc;
            if(xtrg>x2)x2=xtrg;
        }
    }
    else {
        x1=sources::parent(ed)->x;
        x2=targets::parent(ed)->x;
        if(x2<x1){
            x2=sources::parent(ed)->x;
            x1=targets::parent(ed)->x;
        }
    }
 
    success=0;
    for(t=fromTrack; ; t++){ // exit provided by the next two lines
        numTr=trackArr::size(this); // may change within the loop
        if(t>=numTr)break;
        
        tr=trackArr::get(this,t); // trackArr has fixed size, tr is safe
        if(byTrack::head(tr)==NULL){ // the track is still empty
            tr->num=1;
            byTrack::addHead(tr,ed);
            success=1;
            break; // finished
        }

        // search within the track
        fail=0;
        for(e=btit.fromHead(tr); e; e=btit.next()){
            lastEd=byTrack::prevRing(e);
            nxtEd=byTrack::next(e);

            if(nt && nt==byNet::parent(e))continue; // same net
            xx1=sources::parent(e)->x;
            xx2=targets::parent(e)->x;
            if(xx2<xx1){
                xx2=sources::parent(e)->x;
                xx1=targets::parent(e)->x;
            }

            // tricky: if next edge is 0 length and sits right on xx2, skip it
            if(nxtEd){
                if(sources::parent(nxtEd)->x==xx2 
                           && targets::parent(nxtEd)->x==xx2)continue;
            }

            if(xx2<=x1)continue; // e is 'before' ed
            if(xx1<x2){ // overlap, ed does not fit this track
                fail=1;
                break;
            }

            // insert ed between lastE and e
            success=1;
            break;
        }
        if(success || !fail){ // when e==NULL ed can still fit at the end
            // add ed after lastE
            (tr->num)++;
            byTrack::append(lastEd,ed);
            success=1;
            break;
        }
    }

    if(!success){
        // create a new track, add ed to it
        createTrack(layer,type);
        numTr=trackArr::size(this); // may change within the loop
        tr=trackArr::get(this,numTr-1);
        byTrack::addHead(tr,ed);
        tr->num=1;
    }
}

// ------------------------------------------------------------------
// Read the parameter file and derive the geometry limits for
// the size of the boxes and for the spacing around them. 
// The meaning of these limits is described in the comment part
// of class Layout, under GEOMETRY LIMITS.
// Returns: 0=everything OK, 1=errors
// ------------------------------------------------------------------
int Layout::getGeomLimits(char *parFileName){
    int i,k,n,nodeLength,nameLength,numNames,edgeLength;
    double scale;
    Node *nd; Edge *ed; Member *nm;
    members_Iterator nmit;
    nodes_Iterator nit;
    edges_Iterator eit;

    if(readParFile(parFileName))return 1;

    // find the max.length of all the members used for edges
    edgeLength=0;
    for(ed=eit.fromHead(this); ed; ed=eit.next()){
        i=strlen(edgeType::get(ed));
        if(i>edgeLength)edgeLength=i;
        i=strlen(edgeID::get(ed));
        if(i>edgeLength)edgeLength=i;
    }
    boxSpacing=ax*(edgeLength+6); // 4 for spaces, 2 for multiplicity
        
    // derive spacing and the dimensions of the class box
    nodeLength=nameLength=numNames=0;
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        i=strlen(nodeName::get(nd));
        if(i>nodeLength)nodeLength=i;
        // go through all the members of this node, and count how many (k)
        for(nm=nmit.fromHead(nd), k=0; nm; nm=nmit.next(), k++){
            i=strlen(memberName::get(nm));
            if(i>nameLength)nameLength=i;
        }
        if(k>numNames)numNames=k;
    }
    
    // Spacing permitting labels above and below each line:
    // aUp in the middle, aDown on sides
    trackSpacing=2*(aUp+aDown); // +3*aDown;
    boxYframe=trackSpacing + aUp + aDown; // just a bit more space
    boxXframe=trackSpacing + cx;

    boxW=(nodeLength+2)*cx;
    i=nameLength*ax;
    if(i>boxW)boxW=i;

    // increase the box size if only a few boxes are used
    scale=xScreen/(float)((2*numNodes+1)*boxW);
    if(scale>3.0)scale=3.0;
    if(scale>1.0)boxW=(int)(scale*boxW);

    boxH=cUp + 2*cDown + numNames*(aUp+aDown); 
    minBoxH=boxH;
    i=trackSpacing*(maxDirectTracks()-1) + 2*cUp;
    if(boxH<i)boxH=i;

    // round off so two halves make exactly the whole
    boxH2=(boxH+1)/2; boxH=2*boxH2;
    boxW2=(boxW+1)/2; boxW=2*boxW2;
    return 0;
}

// ------------------------------------------------------------------
// This function converts the internal layout (mostly in double-precision
// coordinates) into the detailed instruction for the display, using pixels.
// Note that screen coordinates are positive integers:
//   x: from the left to the right
//   y: from the top to the bottom (!)
//
// IMPORTANT AND TRICKY:
// Since we want to treat edges that represent associations and edges
// representing inheritance during the placement process, we need base
// class to be the source and the derived class to be the target.
// Unfortunately, this is opposite to the commonly used direction for
// the inheritance in the UML diagrams. It is easier to absorb this
// conceptual difference in this function (during the display) rather than
// to do it in the algorithmic part which has much more complex logic.
// ------------------------------------------------------------------
void Layout::graphics(Display *disp){
    int i,ii,k,t,n,lay,numLay,x,y,xx,yy,d,firstType0,newY,vDir,numTr,x1,x2,dir; 
    double yScale,boxShrink,s;
    Node *nd,*nds,*ndt; Edge *ed,*e; Member *nm; Track *tr; Net *nt;
    char buff[256];  char *eCode;
    char c[2]; c[1]='\0'; // for converting a character into string

    nodes_Iterator nit;
    edges_Iterator eit;
    members_Iterator nmit;
    byTrack_Iterator btit;
    byNet_Iterator bnit;

    numTr=trackArr::size(this);
    disp->title(title::get(this));
    // If the overall y-dimension of the layout does not fill the screen,
    // we can scale up trackSpacing and boxYframe.

    // First count indirect tracks.
    for(i=k=0; i<numTr; i++){
        tr=trackArr::get(this,i);
        if(tr->type==1)continue;
        k++;
    }

    // then find the number of layers
    // derive spacing and the dimensions of the class box
    numLay=0;
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        if(numLay<nd->iy)numLay=nd->iy;
    }
    numLay++; // until now numLay was the highest layer index.

    // calculate the current vertical size of the entire layout,
    // assuming one layer of boxes at the top, one at the bottom,
    // and the trackSpacing replaced by (boxH + 2*frameSpacing)
    // for all the other layers, leaving boxYframe space at the bottom
    // and top of the screen.

    i=(k-1) - (numLay-2); // number of track-to-track channels
    i=i*trackSpacing + numLay*(boxH + 2*boxYframe);
    yScale=(double)yScreen/(double)(i);
    boxShrink=(double)minBoxH/boxH;
    if(yScale<boxShrink){
        // assume boxes go down to minBoxH, and remaining spaces shrink more
        i=i-numLay*boxH; // space that must shrink
        ii=yScreen-numLay*minBoxH; // space to which it has to map
        yScale=(double)ii/i;
    }

    if(automScale && yScale<1.0){
        boxH=(int)(boxH*yScale);
        if(boxH<minBoxH)boxH=minBoxH;
        boxH2=(boxH+1)/2;
        trackSpacing=(int)(trackSpacing*yScale);
        boxYframe=(int)(boxYframe*yScale);
    }


    xToPixels(); // convert x to xx (in pixels) and shift if boxes too close
    setSegmentEnds();
    eliminateMatchingDoglegs();
    avoidOverlaps();
    fixSegmentConflicts();
    numTr=trackArr::size(this); // previous steps may add tracks

    // produce the first (A=area) record
    disp->area(xScreen,yScreen,cFont,aFont);

    // proceed by layer and its tracks.
    // Tracks with type=0 always form a group in which the y coordinates
    // must be spread.


    for(lay=0, y=boxH2+boxYframe; lay<numLay; lay++, y=newY){

        // display all nodes in this layer
        for(nd=nit.fromHead(this); nd; nd=nit.next()){
            if(nd->iy!=lay)continue;
            x=nd->xx;
            nd->yy=y;
            disp->box(x-boxW2, y-boxH2, x+boxW2, y+boxH2);
            yy=y-boxH2+cUp+cDown;
            disp->text(x-boxW2+cx,yy,nodeName::get(nd),cFont);
            // display also all the Name associations
            for(nm=nmit.fromHead(nd); nm; nm=nmit.next()){
                yy=yy+aDown+aUp;
                disp->text(x-boxW2+cx,yy,memberName::get(nm),aFont);
            }
        }

        // Assign y to all the tracks on this layer and display the
        // the horizontal part of the connections. This includes two cases
        // (type=1 edges and regular 'channel' connections)
        
        // First find how many tracks type=1 are on this layer
        for(i=n=0; i<numTr; i++){
            if(trackArr::get(this,i)->layer==lay &&
                                    trackArr::get(this,i)->type==1)n++;
        }

        // print horizontal tracks of this layer
        if(n>1)d=(boxH-2*cUp)/(n-1); else d=0;
        if(d>trackSpacing)d=trackSpacing;
        s=(double)(n-1)/2;
        yy=y - (int)(s*d);
        firstType0=1;
        for(i=0; i<numTr; i++){
            tr=trackArr::get(this,i); // trackArr is fixed, safe to keep pointer
            if(tr->layer!=lay)continue;
            if(tr->type==1){ // straight between boxes
                for(ed=btit.fromHead(tr); ed; ed=btit.next()){
                    ed->y=yy;
                    x1=ed->xs;
                    x2=ed->xt;

                    if(ed->direction<2){
                        disp->line(x1,yy,x2,yy,ed->direction);
                    }
                    else { // reverse source and target
                        disp->line(x2,yy,x1,yy,ed->direction);
                    }

                    xx=(ed->xs+ed->xt)/2 - (strlen(edgeID::get(ed))*ax)/2;
                    disp->text(xx,yy-aDown,edgeID::get(ed),aFont);
                    xx=(ed->xs+ed->xt)/2 - (strlen(edgeType::get(ed))*ax)/2;
                    disp->text(xx,yy+aUp,edgeType::get(ed),aFont);
                    c[0]=getMultChar(ed,0); // 0=source
                    if(ed->xs>ed->xt)xx=ed->xs-ax-aDown;
                    else             xx=ed->xs+aDown;
                    disp->text(xx,yy-aDown,c,aFont);
                    c[0]=getMultChar(ed,1); // 1=target
                    if(ed->xt>ed->xs)xx=ed->xt-ax-aDown;
                    else             xx=ed->xt+aDown;
                    disp->text(xx,yy-aDown,c,aFont);
                }
                yy=yy+d;
            }
            else {  // normal 'channel' connections
                if(firstType0){yy=y+boxH2+boxYframe; firstType0=0;}
                for(ed=btit.fromHead(tr); ed; ed=btit.next()){
                    ed->y=yy;
                    x1=ed->xs;
                    x2=ed->xt;

                    nt=byNet::parent(ed);
                    if(nt){
                        if(x1>x2){
                            x2=ed->xs;
                            x1=ed->xt;
                        }
                        // get the span of the entire net
                        for(e=bnit.fromHead(nt); e; e=bnit.next()){
                            xx=e->xs; if(xx<x1)x1=xx; if(xx>x2)x2=xx;
                            xx=e->xt; if(xx<x1)x1=xx; if(xx>x2)x2=xx;
                        }
                    }
                    disp->line(x1,yy,x2,yy,0);
                    c[0]=getMultChar(ed,1); // 1=target
                    if(c[0]!=' ' && c[0]!='-'){
                        xx=(ed->xs+ed->xt)/2 - (strlen(edgeID::get(ed))*ax)/2;
                        disp->text(xx,yy-aDown,edgeID::get(ed),aFont);
                        xx=(ed->xs+ed->xt)/2 - (strlen(edgeType::get(ed))*ax)/2;
                        disp->text(xx,yy+aUp,edgeType::get(ed),aFont);
                    }
                }
                yy=yy+trackSpacing;
            }
        }
        if(yy<y+boxH2)newY=y+boxH+boxYframe;
        else          newY=yy-trackSpacing+boxYframe+boxH2;

      
        // display connections from this track to boxes above, also set Edge::y
        for(ed=eit.fromHead(this); ed; ed=eit.next()){
            tr=byTrack::parent(ed);
            eCode=edgeCode::get(ed);

            if(tr->layer!=lay)continue;
            if(tr->type==1)continue;
            nds=sources::parent(ed);
            ndt=targets::parent(ed);
            dir=ed->direction;
            if(nds->iy==lay){
                if(dir>=2)vDir=dir; else vDir=0;
                if(eCode[2]=='R' && eCode[1]=='-')vDir= -1; // dashed line no arrow
                c[0]=getMultChar(ed,0); // 0=source
                if(c[0]!=' '){
                    disp->line(ed->xs,ed->y,ed->xs,y+boxH2,vDir);
                    disp->text(ed->xs+aDown,y+boxH2+aUp,c,aFont);
                }
            }
            if(ndt->iy==lay){
                if(dir==2)vDir=0; else if(dir==3)vDir= -1;  else vDir=dir;
                if(eCode[2]=='R' && eCode[3]=='-')vDir= -1; // dashed line
                c[0]=getMultChar(ed,1); // 1=target
                if(c[0]!=' '){
                    disp->line(ed->xt,ed->y,ed->xt,y+boxH2,vDir);
                    disp->text(ed->xt+aDown,y+boxH2+aUp,c,aFont);
                }
            }
        }

        // display the connections from this track to the boxes below
        for(ed=eit.fromHead(this); ed; ed=eit.next()){
            tr=byTrack::parent(ed);
            eCode=edgeCode::get(ed);
        
            if(tr->layer!=lay)continue;
            if(tr->type==1)continue;
            nds=sources::parent(ed);
            ndt=targets::parent(ed);
            dir=ed->direction;
            if(nds->iy==lay+1){
                if(dir>=2)vDir=dir; else vDir=0;
                if(eCode[2]=='R' && eCode[1]=='-')vDir= -1; // dashed line
                c[0]=getMultChar(ed,0); // 0=source
                if(c[0]!=' '){
                    disp->line(ed->xs,ed->y,ed->xs,newY-boxH2,vDir);
                    disp->text(ed->xs+aDown,newY-boxH2-aDown,c,aFont);
                }
            }
            if(ndt->iy==lay+1){
                if(dir==2)vDir=0; else if(dir==3)vDir= -1;  else vDir=dir;
                if(eCode[2]=='R' && eCode[3]=='-')vDir= -1; // dashed line
                c[0]=getMultChar(ed,1); // 1=target
                if(c[0]!=' '){
                    disp->line(ed->xt,ed->y,ed->xt,newY-boxH2,vDir);
                    disp->text(ed->xt+aDown,newY-boxH2-aDown,c,aFont);
                }
            }
        }
    }
    disp->closeIt();
}

// ------------------------------------------------------------------
// Return the multiplicity character for the given end of the edge:
// endType=0 for source, =1 for target. 
// ------------------------------------------------------------------
char Layout::getMultChar(Edge *ed,int endType){
    char *code;

    if(ed->direction>=2)return '-';
    code=edgeCode::get(ed);
    if(endType==0)return code[1]; else return code[3];
}

// ------------------------------------------------------------------
// Return the minimum layer of the source and the target node.
// Return -1 of the source or target are not defined, or if their
// layer is the same.
// Note: Layer of the node is 'iy'
// ------------------------------------------------------------------
int Edge::getLayer(){ 
    int lays,layt;
    if(!(sources::parent(this)) || !targets::parent(this))return -1; 
    lays=sources::parent(this)->iy;
    layt=targets::parent(this)->iy;
    if(lays<layt)return lays;
    if(layt<lays)return layt;
    return -1;
}

// ------------------------------------------------------------------
// Run through all the edges currently routed, and look for pairs
// that connect different layers and have either xs,xt matching
// or reverse matching. If such a pair found, set xs=xt for both,
// using different values for each edge.
//
// Algorithm:
// Store all eligible edges in selectArr[], then sort them by
// layer, min(xs,xt) and by max(xs,xt).
// Walk through the array and check for matching neighbours on the same layer.
// 
// Note that qsort needs a special sorting function for this purpose.
// There are no error conditions.
// ------------------------------------------------------------------
void Layout::eliminateMatchingDoglegs(){
    int i,n,lay,lay1,lay2,numTr; Edge *ed,*e1,*e2; Track *tr;
    byTrack_Iterator btit;

    selectArr::reset(this,0,0); // reset this temporary array as empty
    // collect all edges which connect different layers in selectArr[]
    n=0; // will be the number of such edges
    numTr=trackArr::size(this);

    for(i=0; i<numTr; i++){
        tr=trackArr::get(this,i); //trackArr is fixed size, safe to keep pointer
        for(ed=btit.fromHead(tr); ed; ed=btit.next()){
            lay=ed->getLayer();
            if(lay<0)continue; // same layer of source/target or undefined
            selectArr::set(this,n,ed);
            n++;
        }
    }

    if(n<=1)return;
    selectArr::sort(Layout::sortFunXLST,this);

    for(i=1; i<n; i++){
        e1=selectArr::get(this,i-1);
        e2=selectArr::get(this,i);

        lay1=e1->getLayer();
        lay2=e2->getLayer();

        if((e1->xs==e2->xs && e1->xt==e2->xt) ||
           (e1->xs==e2->xt && e1->xt==e2->xs)){
            
            e2->xs=e2->xt=e1->xt;
            e1->xt=e1->xs;
            i++; // jump to the next pair
        }
    }
}

// ------------------------------------------------------------------
// As the edges are assigned exact x coordinates, there can be new 
// conflicts which were impossible to see in the earlier, rough design.
// Review edges in all tracks, and if there is any conflict, move
// the smaller edge to the next track. This may evetually require to
// create new tracks.
// ------------------------------------------------------------------
void Layout::fixSegmentConflicts(){
    int i,k,conflict,x1,X1,x2,X2,numTr,isLastTrack;
    Edge *ed1,*ed2,*ed; Track *tr,*nxtTrack;
    byTrack_Iterator btit1;
    byTrack_Iterator btit2;

    for(i=0; i<trackArr::size(this); i++){
        tr=trackArr::get(this,i); 
        if(byTrack::head(tr)==NULL)continue;
        if(tr->type==1)continue;

        for(conflict=1; conflict; ){
            tr=trackArr::get(this,i); // there may be 'insert' into trackArr
            conflict=0;
            // compare each to each edge in this track
            for(ed1=btit1.fromHead(tr); ed1; ed1=btit1.next()){
                x1=ed1->xs; X1=ed1->xt;
                if(x1>X1){x1=ed1->xt; X1=ed1->xs;}
                

                for(ed2=btit2.fromHead(tr); ed2; ed2=btit2.next()){
                    if(ed2==ed1)break;
         
                    x2=ed2->xs; X2=ed2->xt;
                    if(x2>X2){x2=ed2->xt; X2=ed2->xs;}

                    if(x1>=X2 || x2>=X1)continue;
                    conflict=1;
                    break;
                }
                if(conflict)break;
            }

            if(conflict){
                // if the next track is not on the same layer, create a new one
                numTr=trackArr::size(this);
                isLastTrack=0;
                if(i==numTr-1)isLastTrack=1;
                else if(tr->layer!=trackArr::get(this,i+1)->layer)isLastTrack=1;
                if(isLastTrack){
                    // create a new track
                    nxtTrack=new Track;
                    if(!nxtTrack){
                        printf("error to allocate a new Track\n");
                        return;
                    }
                    nxtTrack->layer=tr->layer;
                    nxtTrack->type=tr->type;
                    // insert the new track into position (i+1)
                    trackArr::insert(this,i+1,nxtTrack);
                }
                else nxtTrack=trackArr::get(this,i+1);
                // move the smaller from ed1,ed2 to the next track
                if(X2-x2 > X1-x1)ed=ed1;
                else ed=ed2;

                // disconnect ed from its track
                byTrack::remove(ed);
     
                // connect ed to the new track
                byTrack::addHead(nxtTrack,ed);
            }
        }
    }
}
        
// ------------------------------------------------------------------
// Make all edges just a bit shorter - it will remove most of the
// accidental overlaps between vertical edge including touching
// corners.
// ------------------------------------------------------------------
void Layout::avoidOverlaps(){
    Edge *ed; int d;
    edges_Iterator eit;

    d=ax/2;
    for(ed=eit.fromHead(this); ed; ed=eit.next()){
        if(ed->xs<ed->xt){
            ed->xs=ed->xs+d;
            ed->xt=ed->xt-d;
        }
        else if(ed->xs>ed->xt){
            ed->xs=ed->xs-d;
            ed->xt=ed->xt+d;
        }
        // do nothing when they are equal
    }
}

// ------------------------------------------------------------------
// Get the scale if we know that the total xSpan of all the nodes.
// Read the code, there are some decisions to be made.
// ------------------------------------------------------------------
double Layout::getXscale(double xSpan,int numLayers){
    double scale1,scale2,k;
        
    // If xSpan=0 we display only one box, use about 1/4 of the screen
    if(xSpan<=0.0)xSpan=4*(boxW+2*boxXframe);

    // Assume the boxH and boxXframe around the entire layout, then
    // x1 must convert to (boxW2+boxXframe),
    // x2 must convert to (xScreen-boxW2-boxXframe),
    // or (x2-x1) must convert to (xScreen-boxW-2*boxXframe).

    scale1=(xScreen-boxW-2*boxXframe)/xSpan;

    // However, if the diagram includes just a few boxes per layer,
    // the layout would be stretched horizontally too much (not intuitively
    // pleasant). If we have numLayers layers and the total of num nodes, we can
    // start with scaling in a more compact way

    k=numNodes-numLayers;
    scale2=k*(boxW+boxSpacing)/xSpan;
    if(scale2<0.0){
        printf("warning: in getXscale() scale2<0, recovered\n");
    }
    else if(scale2<scale1)scale1=scale2;
    return scale1;
}

// ------------------------------------------------------------------
// For all nodes, convert x to pixels and store it in xx.
// Shift nodes that are too close. Note that boxes for all nodes have
// the same dimensions, but boxes which are not connected by direct
// edges must be only boxXframe apart. If they are connected, then there
// must be boxSpacing gap between them.
//
// The function uses a new, smart algorithm - read the comments within
// the code.
// ------------------------------------------------------------------
void Layout::xToPixels(){
    int i,i1,i2,ii1,ii2,n,gap,left,right,maxRight,d,dd,d1,d2,xx1,xx2,bypass;
    int numL,numI;
    double x1,x2,scale; Node *nd,*n1,*n2; 
    nodes_Iterator nit;

    // clean up ndIndex[] before using it temporarily for a different purpose
    ndIndex::init(this);
    // safety in case the array was not used properly
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        ndIndex::init(nd);
    }

    // find the min/max values of x for all nodes, find number of layers
    x1=x2=nodes::head(this)->x;
    numL= -1;
    for(nd=nit.fromHead(this), n=0; nd; nd=nit.next(), n++){
        ndIndex::addTail(this,nd);
        if(x1>nd->x)x1=nd->x;
        if(x2<nd->x)x2=nd->x;
        if(nd->iy>numL)numL=nd->iy;
    }
    numL++;
    if(n!=numNodes){
        printf("WARNING: internal error in xToPixels() n=%d num=%d\n",
                                                              n,numNodes);
        if(n>numNodes)n=numNodes;
    }
    
    scale=getXscale(x2-x1,numL);

    // scale x for all nodes and store it in xx
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        nd->xx=boxXframe + boxW2 + (int)((nd->x - x1)*scale);
    }

    // sort nodes by layer and xx
    ndIndex::sort(Layout::sortNodesByLayer,this);

    // Proceed layer by layer and shuffle nodes to keep required distances
    maxRight=0;
    for(i1=1; i1<numNodes; i1=i2+1){
        // find group i1 to i2 which is on the same layer
        n1=ndIndex::get(this,i1);
        for(i2=i1+1; i2<numNodes; i2++){
            n2=ndIndex::get(this,i2);
            if(n1->iy!=n2->iy)break;
        }
        i2--;
        if(i1>=i2)continue;

        // First remember the original xx of the nodes and record
        // the required gap to the next node.
        for(i=i1; i<i2; i++){
            n1=ndIndex::get(this,i);
            n2=ndIndex::get(this,i+1);
            if(areConnected(n1,n2))n1->xGap=boxW+boxSpacing;
            else n1->xGap=boxW+cx; // allow smaller space now
            n1->xOrig=n1->xx;
        }
        n2->xGap=0;
        n2->xOrig=n2->xx;

        ndIndex::get(this,i1)->xx=0;
        for(i=i1+1; i<=i2; i++){
            n1=ndIndex::get(this,i-1);
            n2=ndIndex::get(this,i);
            n2->xx=n1->xx + n1->xGap;
        }

        // Repeatedly place the two outside nodes, trying for a closenest
        // and symetry with regard to the original locations. At the same
        // time, maintain the outside boundary of the available space.
        // In the first step, this boundary (available screen space) may
        // overflow, and it must be on the right side. In the following
        // steps, there is always enough space. The iterations stop when
        // the last group fits over(!) the required pair of nodes, and 
        // all the remaining nodes are placed slammed together.
        
        left=boxW2+cx;
        right=xScreen-boxW2-cx;
        d=ndIndex::get(this,i2)->xx - ndIndex::get(this,i1)->xx;
        if(right-left <= d){ 
            right=left+d;
            bypass=1;
        }
        else bypass=0;

        if(maxRight<right)maxRight=right;
            
        for(ii1=i1, ii2=i2; ii1<=ii2; ii1++, ii2--){
            if(bypass)break; // that will place the entire group
            n1=ndIndex::get(this,ii1);
            n2=ndIndex::get(this,ii2);
            xx1=left; xx2=right; // will be the new positions of n1,n2

            if(n2->xx - n1->xx == right-left){ // case >0 cannot happen
                // finished, place the entire group as compacted as it is
                break; // the placement will be done outside of the loop
            }
            d=n2->xx - n1->xx; // min.distance between them
            if(n1->xOrig >= n2->xOrig){
                dd=(n1->xOrig + n2->xOrig)/2;
                if(dd<left)dd=left;
                if(dd>right)dd=right;
                xx1=xx2=dd;
            }
            else {
                if(n1->xOrig < left) xx1=left;  else xx1=n1->xOrig;
                if(n2->xOrig > right)xx2=right; else xx2=n2->xOrig;
                if(n1==n2){ // last node placed
                    n1->xx=xx1;
                    n2->xx=xx2;
                    break;
                }
            }

            dd=d - (xx2 - xx1); // required minus current distance
            if(dd<=0){ // no adjustment needed
          
                left=xx1 + n1->xGap;
                right=xx2 - ndIndex::get(this,ii2-1)->xGap;
                n1->xx=xx1;
                n2->xx=xx2;
                continue;
            }
            
            // push nodes apart and place the last group
            d1=xx1 - left;
            d2=right - xx2;
            dd=dd/2;
            if(d1<=d2){
                if(d1>=dd) left=xx1-dd;
            }
            else {
                if(d2>=dd) right=xx2+dd;
                left=right-d;
            }
            break; // the placement will be done outside of the loop
        }
        // when this loop exits either the last node was placed (ii1>=ii2)
        // or the remaining nodes should be placed slammed from 'left'

        if(ii1<ii2){
            xx1=ndIndex::get(this,ii1)->xx; // left-slammed value
            for(i=ii1; i<=ii2; i++){
                nd=ndIndex::get(this,i);
                nd->xx=nd->xx + left - xx1;
            }
        }
    }

    if(automScale && maxRight > xScreen-boxW2-cx){

        // Scale everything down including boxes and fonts.
        // This may produce a diagram which will be hard to read,
        // but this is what the request was - scale down to fit the screen

        scale=(double)(xScreen-boxW2-cx)/maxRight;
        for(nd=nit.fromHead(this); nd; nd=nit.next()){
            nd->xx=(int)((nd->xx)*scale);
        }

        boxW2=(int)(boxW2*scale);
        boxW=2*boxW2;
        cx=(int)(cx*scale);
        ax=(int)(ax*scale);
        cFont=(int)(cFont*scale);
        aFont=(int)(aFont*scale);
        boxSpacing=(int)(boxSpacing*scale);
        boxXframe=cx;

        // do not allow fonts so small that they would be unreadable
        if(cFont<10)cFont=10;
        if(aFont<10)aFont=10;
    }
}

// --------------------------------------------------------------
// Function for sorting an array of Nodes first by their layer
// and then by their pixel positions xx.
// --------------------------------------------------------------
int Layout::sortNodesByLayer(const void *p1,const void *p2){
    int d; Node *n1,*n2; 

    n1= *(Node**)p1;
    n2= *(Node**)p2;

    d=n1->iy - n2->iy;
    if(d!=0)return d;
    return n1->xx - n2->xx;
}

// ------------------------------------------------------------------
// Return 1 if there is at least one edge between the two nodes,
// return 0 otherwise.
// ------------------------------------------------------------------
int Layout::areConnected(Node *n1,Node *n2){
    Edge *ed;
    sources_Iterator sit;
    targets_Iterator tit;

    for(ed=sit.fromHead(n1); ed; ed=sit.next()){
        if(n2==ed->getOtherNode(n1))return 1;
    }
    for(ed=tit.fromHead(n1); ed; ed=tit.next()){
        if(n2==ed->getOtherNode(n1))return 1;
    }
    return 0;
}
    
// ------------------------------------------------------------------
// Debugging printout of all nodes including their 'index'
// ------------------------------------------------------------------
void Layout::prtNodes(char *label){
    Node *nd;
    nodes_Iterator nit;

    printf("\nPRINTING ALL NODES: %s\n",label);
    for(nd=nit.fromHead(this); nd; nd=nit.next()){
        printf("  %s index=%d\n",nodeName::get(nd),ndIndex::getIndex(nd));
    }
    printf("\n");
}

// ------------------------------------------------------------------
// Return the maximum number of direct tracks (type=1) for any layer.
// This number determines how high must be the Node box in order to display
// these connections with all their labels.
// The return is always >0  (the default is 1).
// ------------------------------------------------------------------
int Layout::maxDirectTracks(){
    int n,t,k,lastLay,numTr;

    // traverse all layers, keep counting number of type=1 tracks with
    // the same layer
    numTr=trackArr::size(this);
    for(t=0, n=1; t<numTr; ){
        if(trackArr::get(this,t)->type==0){t++; continue;}
        lastLay=trackArr::get(this,t)->layer; 
        for(k=1; t<numTr; t++, k++){
            if(trackArr::get(this,t)->type==0 || trackArr::get(this,t)->layer!=lastLay)break;
            if(n<k)n=k;
            lastLay=trackArr::get(this,t)->layer;
        }
        // possible situations here:
        //    t>=numTr will exit the main loop
        //    type==0 will continue the main loop with the same t and pass it
        //    layer not matching, will start a new type=0 group in the next pass
    }
    return n;
}

// ------------------------------------------------------------------
// For all tracks, set xs and xt (their source and target end) 
// of their edges to their true positions.
// For track type=1 (straight horizontal between class boxes), this is
//            a simple adjustment by boxW/2.
// For track type=0 (other tracks), we have to find how many tracks of this
//            type connect to each Node at this layer, and then 
//            distribute them horizontally depending on in which way
//            they connect. For details see the code.
// Hint: Re-use newLayerArr[] to collect all edges connecting to the same Node
//       and sort them in the way how they should connect to this Node.
// Error conditions: none
// ------------------------------------------------------------------
void Layout::setSegmentEnds(){
    Node *nd,*nxtNd,*nds,*ndt; Edge *ed;
    int i,n,mUp,mDown,lay,trackType,x,d,below;
    nodes_Iterator nit;
    sources_Iterator sit;
    targets_Iterator tit;

    for(nd=nit.fromHead(this); nd; nd=nit.next()){ // proceed through all nodes
        lay=nd->iy; // iy is equivalent to the layer
       
        selectArr::reset(this,0,0); // reset this array as empty
        // collect all edges connecting this node with this or higher layer
        n=0; // will be number of edges in selectArr[]
        mUp=mDown=0; // number of lines up/down from nd including loops (m>=n)

        for(ed=sit.fromHead(nd); ed; ed=sit.next()){
            nxtNd=ed->getOtherNode(nd);
            if(!nxtNd)continue;
            trackType=byTrack::parent(ed)->type;
            if(trackType==1){                          // special simple case
                // nd is the source node
                if(nd->xx<nxtNd->xx)ed->xs=nd->xx + boxW2;
                else                ed->xs=nd->xx - boxW2;
            }
            else {                            // store the edge in selectArr[]
                selectArr::set(this,n,ed);
                n++;
                if(nxtNd->iy>=lay)mDown++; 
                else              mUp++;
            }
        }
        for(ed=tit.fromHead(nd); ed; ed=tit.next()){
            nxtNd=ed->getOtherNode(nd);
            if(!nxtNd)continue;
            if(nd==nxtNd){ mDown++; continue;} // this case is already recorded
            trackType=byTrack::parent(ed)->type;
            if(trackType==1){                          // special simple case
                // nd is the target node
                if(nd->xx<nxtNd->xx)ed->xt=nd->xx + boxW2;
                else                ed->xt=nd->xx - boxW2;
            }
            else {                            // store the edge in selectArr[]
                selectArr::set(this,n,ed);
                n++;
                if(nxtNd->iy>=lay)mDown++; 
                else              mUp++;
            }
        }

        // sort edges in selectArr[] first by min x then max x,
        // which is the same as sorting by the other node's x
        selectArr::sort(Layout::sortFunEdges,this);

        // repeat this twice: for tracks above/below this node
        for(below=0; below<2; below++){
            if(below)d=boxW/(mDown+1); // spacing between contact points
            else     d=boxW/(mUp+1);

            for(i=0, x=nd->xx - boxW2 +d; i<n; i++){
                ed=selectArr::get(this,i);
                nxtNd=ed->getOtherNode(nd);
                if(below){if(nxtNd->iy<lay)continue;}
                else     {if(nxtNd->iy>=lay)continue;}
               
                nds=sources::parent(ed);
                ndt=targets::parent(ed);
                if(nd==nds && nd==ndt){ // edge connecting to the same node
                    ed->xs=x;
                    x=x+d;
                    ed->xt=x;
                }
                else if(nd==nds)ed->xs=x;
                else            ed->xt=x;

                x=x+d;
            }
        }
    }
}

// ------------------------------------------------------------------
// INPUT FORMAT:
// All lines the same, 3 options with the first word:
//    Inherits
//    Name
//    code(4B) associationType class1 class2 associationID ;
// Class names (nodes) are not specifically given, they are simply derived
// from the relation. 
//
// Examples of the code: B1-* u1-1 u1-2
//    where b/u are for bi/uni directional, capital letters mark
//          the default organization, * is for "many"
// Example of the input
//   School
//   u1_* Hash School Teacher teachers ;
//   Name Teacher teachersName ; 
//   Inherits SupplyTeacher Teacher ;
// In C++, multiple inheritance is permitted, for example:
//   Inherits Seaplane Plane Boat ;
// In Java, multiple inheritance may involve implementation of interfaces:
//   Inherits Seaplane Plane i:Boat ;
// ------------------------------------------------------------------
// The purpose of this function is to read the input file and convert
// the associations to two-point connections recorded as Edges, with
// each source having 'source' and 'target'.
//
// Associations connecting 2 classes naturally convert to one Edge each,
// and the code provides the information about the multiplicity of both
// ends and whether the access is uni- or bi-directional. For example:
//    u1-* LinkedList1 Department Employee employees
// converts to a uni-directional Edge (code u) connecting Department (the first
// class listed, therefore the source) with the Employee (target).
// The multiplicity on the Department side is 1 (code[1]), the multiplicity
// on the Employee side is * (code[3]). The value of code[2] is irrelevant in
// this case.
//
// Associations connecting more than 2 classes are converted into several
// Edges using the source as the root. This is important for the placement
// part of the layout. Note, that during the routing stage, this representation
// may change (another Node may be used as the root for this association,
// but this change is performed from the existing Edges without going back
// to the original input record. For example, this function converts
// the following association of 4 classes (see code[2]=4) to 3 Edges:
//   Given input: b14*b*u2 MyAssoc A B C D myID
//   Edge1:       b1-*  source=A target=B
//   Edge2:       b1-*  source=A target=C
//   Edge3:       u1-2  source=A target=D
// Look carefully at how the code is formed for these three edges.
// Later, at the routing stage, this representation may be converted to
// another root, for example to root=C:
//   Edge1:       b1-*  source=C target=B
//   Edge2:       b1-*  source=A target=C    ... remains unchanged
//   Edge3:       u1-2  source=C target=D
// Note that in this representation the edge with the true (original) source
// remains unchanged. The u/b code of the other edges is controlled by
// their targets.
//
// Many-to-many associations (code[0]=='R')are a special case of 3+
// participating classes. On addition to the given number of entities (code[2])
// there is one additional class, Relation, always listed as the first.
// Individual directions and multiplicities are not listed, because in this
// case they are always b and *. For example:
//   R*3* 3XtoX Relation Entity1 Entity2 Entity3 myRelation
// converts to:
//   Edge1:       b*R*  source=Entity1 target=Relation   ... R marks relation
//   Edge2:       b*-*  source=Entity1 target=Entity2   
//   Edge3:       u*-*  source=Entity1 target=Entity3
// Later, at the routing stage, this may convert to a different root,
// for example to root=Entity3, which would result in
//   Edge1:       b*R*  source=Entity1 target=Relation   ... R marks relation
//   Edge2:       b*-*  source=Entity1 target=Entity2   
//   Edge3:       u*-*  source=Entity1 target=Entity3
//
// Note the class Net which represents the collection of two-point edges 
// that form one association keeps the record of which node is the source
// and which is the Relation. This is not only important when converting to
// a different root, but also for the final display of the diagram. For
// example, the connection to the Relation must be displayed as a dashed line.
// ------------------------------------------------------------------
// Return: Number of detected associations.
//         Return of -1 indicates an error.
// ------------------------------------------------------------------

int Layout::readInput(FILE *file1){
    int pSz=10; char *part[10];; // array of possible participants 

    // internal variables:
    int bSz=256;      // sizes of buffers for all the names
    char buff[256],code[256],type[256],id[256];
    char name1[256],name2[256],name3[256],name4[256],name5[256],relation[256]; 
    int i,k,kk,k1,k2; char c,newCode[20];
    Edge *ed; Net *nt; Node *relNd,*srcNd,*nxtNd;

    disposeData(); // if there is any internal data, dispose it

    for(i=0; fgets(buff,bSz,file1); i++){
        // check that the line ends with ';'
        for(k=0; k<bSz && buff[k]!='\n'; k++){
            if(buff[k]==';')break;
        }
        if(k>=bSz || buff[k]!=';'){
            printf("input error, ';' missing on line=%d\n%s",i,buff);
            i=-1;
            break;
        }

        sscanf(buff,"%s",code);

        if(!strcmp("Name",code)){
            // Name is synonymous with the String class, and in the UML
            // diagram should have a similar representation as a class member.
            // However, since it is really implemented as a pointer (in C++)
            // or a reference (in Java) to a variable text string or array,
            // as a software architect, I believe it deserves a special 
            // treatment and should be shown even if other class members are
            // not shown. This is particularly important if your classes
            // are persistent, or if the size and number of objects used
            // by the software is of concern.

            sscanf(buff,"%s %s %s",code,name1,id);

            if(addMember(name1,"Name",id))return -1;
        }
        else if(!strcmp("u1-0",code)){
            // This is the signature of a member like data organization
            // which attaches special data. Name is one of these.

            sscanf(buff,"%s %s %s %s",code,type,name1,id);
            if(id[0]==';'){ // no id, for example Property
                strcpy(id,"");
            }

            if(addMember(name1,type,id))return -1;
        }
        else if(!strcmp("Inherits",code)){
            // Inheritance does not need the special code, it is always
            // unidirectional and usually a 1-to-1 type relation (always in
            // Java, and most of the time in C++). This program, just as
            // many UML tools - for example Poseidon, converts multiple
            // inheritance into a set of single-inheritance links.

            // In order to simplify the algorithm, remove leading blanks
            // and reduce buff[] to single blank separators.
            // Also make sure the ending (;) is blank separated.
            // File layout.inp is generated in such a format already,
            // this is just a safety precaution.

            for(k=kk=0; buff[k]!=';'; k++){
                if(buff[k]!=' ' || (k>0 && buff[k-1]!=' ')){
                    buff[kk]=buff[k];
                    kk++;
                }
            }
            if(buff[kk-1]!=' '){
                if(kk>=bSz-1){i= -1; break;}
                buff[kk]=' '; kk++;
            }
            buff[kk]=';';
      
            // k will be the beginning of the next token
            // kk is the token counter
            for(k=kk=0; buff[k]!=';'; kk++, k=k+strlen(name2)+1){
                // read the next token from buff[]
                sscanf(&(buff[k]),"%s",name2);

                if(kk==0)continue; // skip token "Inherits"
                else if(kk==1){
                    // remember the name of the derived class
                    strcpy(name1,name2);
                }
                else {
                    // record the next inheritance link
                    strcpy(code,"Inherits");
                    strcpy(type,code);
                    // the derived class becomes target
                    part[0]=name2; // the base class becomes source
                    part[1]=name1; // the derived class becomes target
                    strcpy(id,"-");

                    if(!addEdge(code,part[0],part[1],type,id))return -1;
                    i++; 
                }
            }
            if(i<0)break; // error condition
            i--; // compensates for i++ at the main loop
        }
        else {
            // Association of two or more cooperating classes:
            // Besides inheritance, this is the main relation we want
            // to show in UML class diagrams. This program does not
            // handle associations of more than 2 classes, but the
            // extention to n classes is possible. Technically, the main
            // problem is in the display itself.

            sscanf(buff,"%s",code);
            c=code[0];
            if(c!='b' && c!='B' && c!='u' && c!='U' && c!='R'){
                printf("input error, line=%d, code=%s\n",i,code);
                return 3;
            }

            c=code[2];
            if(c=='-')k=2;
            else if(c=='=')k=1;
            else      k=(int)(code[2]) - (int)('0');
            if(code[0]=='R')k++;

            if(k<1 || k>pSz){
                printf("Number of participants incorrect or out of limit:\n");
                printf("%s\n");
                return -1;
            }

            if(k==1){
                sscanf(buff,"%s %s %s %s",
                                      code,type,name1,id);
                part[0]=name1;
                part[1]=name1;
                k=2;
            }
            else if(k==2){
                sscanf(buff,"%s %s %s %s %s",code,type,name1,name2,id);
                part[0]=name1;
                part[1]=name2;
            }
            else if(k==3){
                sscanf(buff,"%s %s %s %s %s %s",
                                      code,type,relation,name1,name2,id);
                part[0]=relation;
                part[1]=name1;
                part[2]=name2;
            }
            else if(k==4){
                sscanf(buff,"%s %s %s %s %s %s %s",
                                      code,type,relation,name1,name2,name3,id);
                part[0]=relation;
                part[1]=name1;
                part[2]=name2;
                part[3]=name3;
            }
            else if(k==5){
                sscanf(buff,"%s %s %s %s %s %s %s %s",
                               code,type,relation,name1,name2,name3,name4,id);
                part[0]=relation;
                part[1]=name1;
                part[2]=name2;
                part[3]=name3;
                part[4]=name4;
            }
            else if(k==6){
                sscanf(buff,"%s %s %s %s %s %s %s %s %s",
                         code,type,relation,name1,name2,name3,name4,name5,id);
                part[0]=relation;
                part[1]=name1;
                part[2]=name2;
                part[3]=name3;
                part[4]=name4;
                part[5]=name5;
            }
            else {
                printf("The existing version of Layout allows associations\n");
                printf("with up to 6 classes. If you need to increase this\n");
                printf(" limit, please modify function readInput()\n");
                return -1;
            }
    

            // do not use type name when a default association is used
            if(code[0]=='U' || code[0]=='B') strcpy(type," ");

            if(k>2){
                if(code[0]=='R'){
                    k1=1; // index of the source
                    relNd=getNode(part[0]);
                    srcNd=getNode(part[1]);
                    for(kk=2; kk<k; kk++){
                        nxtNd=getNode(part[kk]);
                        if(nxtNd==NULL || srcNd==NULL)break;
                        // nxtNd is in a ring with itself, see Node()
                        sameLayer::del(nxtNd,nxtNd); 
                        sameLayer::add(srcNd,nxtNd);
                    }
                }
                else {
                    k1=0; // index of the source
                    relNd=NULL;
                    srcNd=getNode(part[0]);
                }

                nt=new Net(relNd,srcNd);
                if(!nt){printf("error to allocate Net\n"); return -1;}
                nets::addTail(this,nt);
            }
            else {
                k1=0;
                nt=NULL;
            }

            for(k2=0; k2<k; k2++){
                if(k2==k1)continue;

                // reduce the code for the two-point edge
                strncpy(newCode,code,4);
                if(k>2){
                    if(code[0]=='R'){ // special case
                        if(k2==0){
                            newCode[0]='b'; // do not display the arrow
                            newCode[2]='R'; // relation, use dashed line
                            newCode[3]='-'; // no display of multiplicity
                                            // but display of the edge
                        }
                        else {
                            newCode[0]='b'; // always in this case
                            newCode[1]=' '; // display source multipl. just once
                            newCode[2]='-'; // two-point edge
                            newCode[3]='*'; // always in this case
                        }
                    }
                    else if(k2>1){ 
                        newCode[0]=code[2*k2];
                        newCode[1]=' '; // display source multipl. just once
                        newCode[2]='-'; // two-point edge
                        newCode[3]=code[2*k2+1];
                    }
                }

                ed=addEdge(newCode,part[k1],part[k2],type,id);
                if(!ed)return -1;
                if(nt)byNet::addTail(nt,ed);
            }
        }
    }
    if(i<0){
        printf("allocation problem in readInput()\n");
    }
    return i;
}

// ------------------------------------------------------------------
Net::Net(Node *relation,Node *source){
    netRelation::add(this,relation);
    netSource::add(this,source);
}

// ------------------------------------------------------------------
// This program reads the description of the architecture (the logic
// of the UML class diagram) and creates the geometry of this diagram.
// The task has three steps: 
//  (1) Placing the boxes representing classes in
//      an intuitively meaningful way which (hopefully) shows on a screen
//      without much panning. 
//  (2) Connecting the boxes by lines representing inheritance and 
//      associations. Again, hopefully, these lines will be short and
//      will cross as little as possible.
//  (3) Placing labels on these lines representing type and id of 
//      individual associations, their directionality and multiplicity.
// ------------------------------------------------------------------
int main(int argc,char **argv) {
    int i;
    int eSz=200; // limit on the number of edges (and nodes)
    char *codes[200], *types[200], *sourceNames[200], *targetNames[200],
        *ids[200]; 
    FILE *file1,*file2; char *parFileName,*inpFileName; 
    Display *display;

    i=0;
    if(argc>1){
        if(!strcmp(argv[1],"-s")) i=1;
    }
        
    if(argc<=1+i){
        printf("syntax error: layout [-s] paramFile [inpFile outFile]\n");
        return 3;
    }
    parFileName=argv[1+i];

    if(argc<3+i){file1=stdin; inpFileName="unknown source";}  
    else        {file1=fopen(argv[2+i],"r"); inpFileName=argv[2+i];}

    if(argc<4+i)file2=stdout; else file2=fopen(argv[3+i],"w");
    if(file1==NULL || file2==NULL){
        printf("cannot open input or output file\n"); fflush(stdout);
    }

    Layout* layout=new Layout(i,inpFileName); // i=1 for automatic scaling

    printf("UML Layout program Ver.2.1 (c) Code Farms Inc. 2005\n");

    // convert the input file into a set of simplified name arrays
    i=layout->readInput(file1);
    if(i<0)return 2;
    fclose(file1);

    if( layout->preprocess() ){
        printf("layout not finished, error in preprocess()\n");
        return 1;
    }
    if( layout->place(parFileName) ){
        printf("layout not finished, error in place()\n");
        return 1;
    }
    if( layout->route(0.02) ){

        printf("layout not finished, error in route()\n");
        return 1;
    }

    if(!strcmp(argv[1],"-s")) display=new SvgDisplay("display.svg");
    else                      display=new LogDisplay("display.log");

    layout->graphics(display);
    return 0;
}

#include "gen.cpp"
