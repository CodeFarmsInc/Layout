/****************************************************************/
/*							      	*/
/*               Copyright (C) 2004                             */
/*	Code Farms Inc.,  All Rights Reserved.			*/
/*							  	*/
/*   7214 Jock Trail, Richmond, Ontario, K0A 2Z0, Canada        */
/*        (613)-838-3216, jiri@codefarms.com                    */
/****************************************************************/
// Author: Jiri Soukup, Mar.5, 2013 

// ----------------------------------------------------------------------------
// Code Generator for the data structure management in Objective-C
//                                       xxxxxxxxxxxxxxxxxxxxxxxxxx
//
// This code generator uses itself for the management of its own internal data.
// Syntax:
//    codegen [-dol] dsFile libPath genFile ... just to compile
//    codegen -uml [-dol] dsFile libPath genFile srcList umlID ... also UML 
// where:
//    static  uses static functions as interface (recommended),
//    dol     uses the old DOL interface (for historical comparison)
//
//    dsFile  is the input file which contains all the DataStructure statements
//            used by the program(typically ds.def),
//    libPath is the relative or absolute path to the library directory,
//            the library must contain the 'registry' file.
//    genFile name of the file that will be generated.
//    umlID   is a unique ID which will be used for all the UML objects in this
//            project
//    srcList is an optional list such as produced by "dir *.h" under DOS
//            or "ls *.h" under UNIX. When this list is not given, the generator
//            does not generate inheritance records.
//
// All the parameters must be given (there are no defaults).
// The output file which allows to generate the UML class diagram with commonly
// used UML tools has always the same name:  umlFile.xmi
//
// WARNING: The call to 'codegen' is slightly different from Java.
// WARNING: When extracting inheritance, the existing program treats macros such
//          as #define as regular C++ code.
// IMPORTANT: When using the automatic extraction in C++, the inheritance statements
//          must have a blank on both sides of the double-colon: 
//          Correct:   class A : public B {
//          Incorrect: class A:public B {
// -----------------------------------------------------------------------------
// UPDATES:
//
// Ver.1.1 (May 4, 2004): 
//    Added the association code to the lib\registry file
// Ver.1.2 (Sept.5, 2004):
//    Automatic extraction of inheritance.
// Ver.2 (July 14, 2005):
//    Associations with more than 2 participating classes
// ----------------------------------------------------------------------------

// Next line is important for the strategy of dealing with ptrList,
// and also whether the inheritance from PersistObject is really needed.
//
// #define SEAN

#include "codegen.h"

void substitute(char*,char*,char**,int,int);

// ---------------------------------------------
// methods needed for the Hash association between Generator and ApplClass
// ---------------------------------------------
int classes::hash(ApplClass *a,int hashSz){
    char *s;
    s=cName::get(a);
    return classes::hashString(s,hashSz);
}
int classes::cmp(ApplClass *a1,ApplClass *a2){
    char *s1,*s2;
    s1=cName::get(a1);
    s2=cName::get(a2);
    return strcmp(s1,s2);
}
// ---------------------------------------------

// ----------------------------------------------------------------------
// The arguments given to the Genereator are:
//    dsFile libPath genFile srcList umlID
// last two arguments are given only when the UML generation is planned
// i.e. when umlRun=1.
// ----------------------------------------------------------------------
Generator::Generator(int umlR,int dolR,int objcR,char **argv){
    static char* version = "3.0 ObjectiveC capable";

    umlRun=umlR;
    dolRun=dolR;
    objcRun=objcR;

    startID=objectID=1000;
    classes::form(this,200); // form hash table with 200 buckets
    derived=NULL;

    dsFileName=argv[0];
    libPath=argv[1];
    outFileName=argv[2];
    if(umlRun){
        srcList=argv[3];
        umlID=argv[4];
        umlFile="umlFile.xmi";
        layFile="layout.inp";
    }

    bufSz=512; 
    buff=new char[bufSz];
    name=new char[bufSz];
    if(!buff || !name){
        printf("allocation error in Generator()\n");
        return;
    }

    printf("--- jslib codegen Ver.%s\n",version);
    readDSfile();
    readRegistry(libPath);
}

// -----------------------------------------------------------------
// Here is an advanced use of the constructor. When creating
// a new Participant with index i, beside the usual initialization,
// add it also to 'parts', set its name to 'partName', and add
// this Participant to the list 'usedBy' of all Participants
// with the same name (same ApplClass).
// NOTE: 'partName' is obtained from the ApplClass.
// -----------------------------------------------------------------
Participant::Participant(int i,ApplClass *apClass,Organization *org,Generator *gen){
    char *s,*name;

    id=gen->getObjectID();
    used=false;   
    index=i; 
    parts::addTail(org,this);
    usedBy::addTail(apClass,this);

    name=cName::get(apClass);
    s=new char[strlen(name)+1]; 
    if(!s)printf("error when allocating name=%s\n",name);
    strcpy(s,name); 
    partName::add(this,s); // reuse the name of the ApplClass
}

// --------------------------------------------------------------
// If ApplClass with name 's' already exists, find it and return it.
// if it does not exist, create it with its name and id, and add it
// to 'classes'
// --------------------------------------------------------------
ApplClass* Generator::getOrCreateApplClass(char *s){
    ApplClass *ac,*acTemp; char *p;

    p=newString(s);
    acTemp=new ApplClass(p);
    ac=classes::get(this,acTemp);
    if(ac==NULL){
        ac=acTemp;
        ac->setID(this);
        classes::add(this,ac);
    }
    else {
        cName::del(acTemp);
        delete p;
        delete acTemp;
    }
    return ac;
}

// -----------------------------------------------------------------
// read the input file, and extract lines starting with "DataStructure"
// Returns: 0=everything OK, >0 means errors
// -----------------------------------------------------------------
int Generator::readDSfile(){
    char* ds="DataStructure"; int dsSz=strlen(ds);
    char* as="Association"; int asSz=strlen(as);
    FILE *inpFile; char *p,*s; ApplClass *ac;
    int numTok,i,k,numPar,nh;

    Organization *org;
    OrgType *oType;
    Participant *part;
    orgs_Iterator oIter;
    parts_Iterator pIter;

    inpFile=fopen(dsFileName,"r");
    if(!inpFile){
        printf("problem to open input file=%s\n",dsFileName);
        return 1;
    }

    while(fgets(buff,bufSz,inpFile)){ // read the input line-by-line
        for(p=buff; *p==' '; p++)continue; // skip leading blanks
        // consider only the lines starting with the keyword 'DataStructure'
        if(strncmp(ds,p,dsSz) && strncmp(as,p,asSz))continue;
        
        numTok=oneLine(inpFile,&numPar,&nh);
        if(nh>0){
            printf("error: DataStructure %s with two <...>\n",tokens[0]);
            return 2;
        }
        
        if(numTok<0)return 3; // error or overflow inside oneLine()
        if(numTok<=1)continue;

        for(i=1, k=0, org=NULL; i<numTok; i++){
            s=newString(tokens[i]);

            if(i==1){
                org=new Organization;
                orgs::addTail(this,org);
                oType=getOrgType(s,0);
                myType::add(org,oType);
            }
            else if(i==numTok-1){
                orgName::add(org,s);
            }
            else {
                k++;
                ac=getOrCreateApplClass(s);
                part=new Participant(k,ac,org,this);
            }
        }
    }
    fclose(inpFile);
    return 0;
}

// --------------------------------------------------------------------
int Generator::isBasicType(Participant *part){
    char c,*s;

    s=partName::get(part);
    c=s[strlen(s)-1]; // last character of s
    if(!strcmp(s,"int") || !strcmp(s,"char") ||
       !strcmp(s,"float") || !strcmp(s,"double") || c=='*'){
        return 1;
    }
    return 0;
}

// --------------------------------------------------------------------
// name s must be externally pre-allocated
// --------------------------------------------------------------------
ApplClass::ApplClass(char *s){
    id=0;
    ci=1;
    cName::add(this,s);
    count=0;
}

// --------------------------------------------------------------------
// read the registry file, and search for the uses of each organization
// --------------------------------------------------------------------
void Generator::readRegistry(char *libPath){
    int numTok;
    FILE *inpFile; char *p,*s,*code; 
    int i,k,numPar,n,nh,ref,m;
    Organization *org;
    OrgType *oType,*otp;
    PartType *pType, *pInh;
    Iterator *iter;
    FixedType *ft;
    orgs_Iterator oIter,oIter1;
    parts_Iterator pIter;
    types_Iterator tIter;

    strcpy(name,libPath);
    strcat(name,"/registry");
    inpFile=fopen(name,"r");
    if(!inpFile){
        printf("problem to open input file=%s\n",name);
        return;
    }

    while(fgets(buff,bufSz,inpFile)){ // read the input line-by-line
        numTok=oneLine(inpFile,&numPar,&nh);
        if(numTok<0)return;
        if(numTok<=2)continue;

        if(numTok<numPar+3){
            printf("registry incorrect entry: ");
            for(i=0; i<numTok; i++)printf("%s ",tokens[i]);
            printf("\n");
            return;
        }

        // skip the first token which contains the UML code
        for(i=1, k=0, org=NULL; i<numTok; i++){

            s=newString(tokens[i]);

            if(i==1){
                oType=getOrgType(s,1);
                oType->setCode(tokens[0]); 
            }
            else if(i<=numPar+1){
                if(s[0]=='-'){ s=s+1; ref=1;} else ref=0;
            pType=new PartType(k+1,ref); k++;
            if(!pType){
                printf("allocation problem in basic data\n"); return;
            }
            partTypes::addTail(oType,pType);
            partTypeName::add(pType,s);

            // set the multiplicity stored in tokens[0]
            m=2*i - 3;
            pType->setMult(tokens[0][m]);
            }
            else if(i==numPar+2){
                fileName::add(oType,s);
                k=0;
            }
            else if(s[0]==':'){ // inheritance record, participants will follow
                k=nh;
                otp=getOrgType(s+1,0);
                if(!otp){
                    printf("error in registry: %s not preceeding %s\n",
                            s+1,tokens[1]);
                    return;
                }
                inherits::add(oType,otp);
            }
            else if(k>0){ // inheritance participants
                if(s[0]=='$'){ // reference to establish link
                    n=atoi(s+1); // get the index reference

                    // We have a link from the n-th participant of the 
                    // derived class to the k-th participant of the base class

                    pType=findPartType(oType,n);
                    pInh=findPartType(otp,nh-k+1);
                    if(!pType || !pInh)return;
                    inhMatch::add(pType,pInh);
                }
                else {
                    ft=new FixedType;
                    if(!ft){
                        printf("problem to allocate FixedType\n");
                        return;
                    }
                    fixedTypes::addTail(oType,ft);
                    fixedName::add(ft,newString(s));
                    pInh=findPartType(otp,nh-k+1);
                    inhFixed::add(ft,pInh);
                }

                k--;
            }
            else { // iterator
                iter=new Iterator;
                if(!iter){
                    printf("allocation problem in basic data\n"); return;
                }
                iters::addTail(oType,iter);
                iterName::add(iter,s);
            }
        }
    }
    fclose(inpFile);
    if(matchParticipants())return;

    // check that all OrgTypes are fully recorded
    tIter.start(this);
    ITERATE(tIter,oType){
        if(oType->isFull())continue;
        printf("input error, %s used but not recorded in registry\n",
                                                    orgTypeName::get(oType));
    }
}

// ----------------------------------------------------------------
// For the given OrgType, find the participant with index n.
// If not found, print an error message and return NULL.
// ----------------------------------------------------------------
PartType* Generator::findPartType(OrgType* otp,int n){
    partTypes_Iterator ptIter;
    PartType *pt;

    ptIter.start(otp);
    ITERATE(ptIter,pt){
        if(n==pt->getIndex())break;
    }
    if(!pt){
        printf("registry error, $%d of %s\n",n,orgTypeName::get(otp));
    }
    return pt;
}

// ----------------------------------------------------------------
// Search for the OrgType of the given name. 
// If there isn't one already, create it and return pointer to it.
// Use full=1 when setting a full type record, full=0 otherwise.
// Return=NULL means error, most likely allocation error.
// ----------------------------------------------------------------
OrgType* Generator::getOrgType(char *s,int full){
    types_Iterator it; OrgType *oType;

    it.start(this);
    ITERATE(it,oType){
        if(!strcmp(s,orgTypeName::get(oType)))break;
    }
    if(oType){
        if(full)oType->setFull(); // do NOT just set it to 'full'
        return oType;
    }

    oType=new OrgType(full);
    if(oType){
        orgTypeName::add(oType,s);
        types::addTail(this,oType);
    }
    return oType;
}

// ----------------------------------------------------------------
// Match participants of all organizations with their types,
// there must be the same number of participants, and they are matched
// in their order, and their indexes must agree.
// Return=0 means everything OK.
// ----------------------------------------------------------------
int Generator::matchParticipants(){
    types_Iterator tIter;
    orgs_Iterator oIter;
    Organization *org; OrgType *tp; Participant *part; PartType *pType;

    oIter.start(this);
    ITERATE(oIter,org){
        tp=myType::fwd(org); 
        if(!tp){printf("error in matching participants\n"); return 1;}

        // walking in parallel through both participants

        for(part=parts::head(org), pType=partTypes::head(tp); part && pType;
                 part=parts::next(part), pType=partTypes::next(pType)){

          if(part->getIndex()!=pType->getIndex()){
                printf("input error, parameters not matching for %s and %s\n",
                                orgName::get(org),orgTypeName::get(tp));
                return 1;
          }
          myPartType::add(part,pType);
        }
        if(part || pType){
          printf("input error, number of parameters for %s and %s\n",
                                orgName::get(org),orgTypeName::get(tp));
          return 1;
        }
    }
    return 0;
}

// ----------------------------------------------------------------
// IMPORTANT: buff[bufSz] and tokens[] are memebers of class Generator.
//
// Inside 'buff', detect tokens separated by separators, and make
// tokens 0-ending. Return number of tokens, the array with pointers
// to individual tokens, and the numbers of parameters in possibly two
// sets of <....>, npar1 and npar2.
//
// In case of comment or empty (or a full comment) line, return -1.
// Comments (//) are allowed as usual in C++ or Java.
// Each definition may split over several lines using the backslash (\)
// character. The total length of one defintion is limited by bufSz.
//
// Returns: number of tokens, 0 or 1 means the line is not interesting,
//          -1 means error
// ----------------------------------------------------------------
int Generator::oneLine(FILE *inpFile,int *npar1,int *npar2){
    static char* separator=" <>,";
    int i,k,n,tokInd,tokenInProgress,inside;


    for(i=0; i<bufSz; i++){
        if(buff[i]!=' ' || buff[i]=='\t')break;
    }
    if(buff[i]=='\n')return 0;                  // skip empty line
    if(buff[i]=='/' && buff[i+1]=='/')return 0; // skip comment line

    // Search for either ':' or '\n'. When ';' not found, read
    // more data into buff[] until ':' is found.
    // skip comments or empty line

    for(n=0; n<bufSz; ){
        for(i=n; i<bufSz; i++){
            if(buff[i]==';' || buff[i]=='\n')break;
        }
        if(i>=bufSz){
            buff[bufSz-1]='\n';
            printf("statement over %d bytes or end missing\n%s\n",bufSz,buff);
            return -1;
        }
        if(buff[i]==';')break; // complete statement in buff[]
        // read another line into buff[] starting from i
        n=i;
        if(!fgets(buff+n,bufSz-n,inpFile)){
            buff[n]='\n';
            printf("error reading continuation of\n%s\n",buff);
            return -1;
        }
    }

    *npar1= *npar2= 0;
    for(i=tokInd=inside=tokenInProgress=0; buff[i]!='\n' && buff[i]!='\0'; i++){ 
        if(buff[i]==';'){buff[i]='\0'; return tokInd;}

        for(k=0; separator[k]!='\0'; k++){
            if(separator[k]==buff[i])break;
        }

        if(separator[k]=='<')inside=tokInd;
        else if(separator[k]=='>'){
            if(*npar1==0)*npar1=tokInd-inside;
            else         *npar2=tokInd-inside;
        }
        if(separator[k]!='\0'){buff[i]='\0'; tokenInProgress=0; continue;}

        if(!tokenInProgress){
            tokens[tokInd]= &(buff[i]);
            tokInd++;
            tokenInProgress=1;
        }
    }
    printf("record not ending with ';'\n%s\n",buff);
    return 0;
}

// ------------------------------------------------------------------
// This function generates file (umlFile.xmi) which allows a UML tool such as
// Poseidon to display the UML class diagram. It also generates file
// layout.inp which can be used as input for the layout program which 
// displays the UML class diagram.
// This task has two parts:
// Part 1: Constructor Generator() already collected all the information
//         about associations (data structures) and this information just
//         must be written to outFileName in the proper format (XMI).
// Part 2: Information about inheritance among the classes 
//         must be recovered from the source, but it is an
//         easy task if file srcList provides a list of all *.h files.
//         Such file can be produced with 'dir' (in DOS) or 'ls' (in UNIX).
// For details of the algorithms see the functions which implement the two
// parts.
// Returns: 0=everything OK, 1=errors.
// ------------------------------------------------------------------
int Generator::genUmlFile(){
    FILE *fp,*fi;

    fp=fopen(umlFile,"w");
    fi=fopen(layFile,"w");
    if(!fp || !fi){
        printf("error: cannot open UML interface files=%s or %s\n",
                                                   umlFile,layFile);
        return 2;
    }
    if(extractAssociations(fi)) return 1; // must be called first, defines root
    if(extractInheritance(fi)) return 1;
    fclose(fi);

    prtXMIheader(fp);   
    prtXMIclasses(fp);
#ifdef JS   
    prtXMIassociations(fp);
    prtXMIinheritance(fp);
#endif // JS
    prtXMItail(fp);
    fclose(fp);
    return 0;
}

// ------------------------------------------------------------------
void Generator::prtXMIassociations(FILE *fp){
printf("XXX prtXMIassociations() has not been designed yet!!\n");
}

// ------------------------------------------------------------------
void Generator::prtXMIinheritance(FILE *fp){
printf("XXX prtXMIassociations() has not been designed yet!!\n");
}

// ------------------------------------------------------------------
// Generate the header of the XMI file
// QUESTION: Is the format of the time-stamp mandatory like this?
//           'Fri Aug 27 06:15:53 PDT 2004'
// The existing code uses seconds since Jan.1, 1970, 00:00 GMT
// ------------------------------------------------------------------
void Generator::prtXMIheader(FILE *fp){
    fprintf(fp,"<?xml version = '1.0' encoding = 'UTF-8' ?>\n");
    fprintf(fp,"<XMI xmi.version = '1.2' xmlns:UML = 'org.omg.xmi.namespace.UML'\n");
    fprintf(fp,"         timestamp = '%ld'\n",time(NULL));
    fprintf(fp,"  <XMI.header>\n");
    fprintf(fp,"    <XMI.documentation>\n");
    fprintf(fp,"      <XMI.exporter>CentralControl</XMI.exporter>\n");
    fprintf(fp,"      <XMI.exporterVersion>1.0</XMI.exporterVersion>\n");
    fprintf(fp,"    </XMI.documentation>\n");
    fprintf(fp,"  </XMI.header>\n");
    fprintf(fp,"  <XMI.content>\n");
    fprintf(fp,"    <UML:Model xmi.id = '%s:%d'\n",umlID,startID);
    fprintf(fp,"      name = '%s' isSpecification = 'false'\n",umlID);
    fprintf(fp,"      isRoot = 'false' isLeaf = 'false' isAbstract = 'false'>\n");
    fprintf(fp,"      <UML:Namespace.jLib_UML>\n");
}

// -------------------------------------------------------------
// Traverse 'classes'and print the XMI record for all ApplClasses
// -------------------------------------------------------------
void Generator::prtXMIclasses(FILE *fp){
    ApplClass *ac;
    classes_Iterator cIter;

    for(ac=cIter.first(this,-1); ac; ac=cIter.next()){           
      fprintf(fp,"        <UML:Class xmi.id = '%s:%d'",umlID,ac->getID());
      fprintf(fp," name = '%s'\n",cName::get(ac));
      fprintf(fp,"              visibility = 'public' isSpecification = 'false'\n");
      fprintf(fp,"              isRoot = 'false' isLeaf = 'false' isAbstract = 'false'\n");
      fprintf(fp,"              isActive = 'false'/>\n");
    }
}

// -------------------------------------------------------------
void Generator::prtXMItail(FILE *fp){
    fprintf(fp,"      </UML:Namespace.jLib_UML>\n");
    fprintf(fp,"    </UML:Model>\n");
    fprintf(fp,"  </XMI.content>\n</XMI>\n"); 
}

// ------------------------------------------------------------------
// Outside loop: Read file srcList, and for each line look for ".h" or ".H"
//            and from that recover the file name.
// Inside loop - reading that file line by line, while:
//     - eliminating /* ... */ sections that run over several lines
//     - eliminating anything after // ....
//     - eliminating anything between "..." over several lines.
//     - search for single ':', not preceeded by ' or \
//     - use the section between ':' and '{' plus the last word before ':'
//       do define the inheritance
//     - for each line, keep the last unused word (in case ':' will start
//       the next line.
// The output is file layout.inp
// Returns: 0=everything OK, >0 means errors.
// ------------------------------------------------------------------
int Generator::extractInheritance(FILE *rFile){
    FILE *oFile,*iFile; //outside & inside loop, results
    int n,ret,mode; char *fn;

    derived=NULL;
    if(srcList==NULL){
        printf("not extracting inheritance, file srcList not given\n");
        return 0;
    }
    oFile=fopen(srcList,"r");
    if(!oFile){
        printf("error: cannot open given srcList=%s\n",srcList);
        return 1;
    }

    ret=0;
    while(fgets(name,bufSz,oFile)){ // read srcList line-by-line
        fn=getFileName(name);
        if(!fn)continue; // padding line, no file reference
        iFile=fopen(fn,"r");
        if(!iFile){
            printf("error: cannot open file=%s\n",fn);
            ret=1;
            continue;
        }

        // read the source file line by line
        mode=0; // mode in which the last search() stopped, initial to 0
        buff[0]='\0'; // no last word
        for(;;){
            if(mode==0)n=reduce(buff); //reduce buff to the last blank-separated
                          // token, return the number of characters without \0
            else n=0;

            if(!fgets(&(buff[n]),bufSz,iFile))break;
            eliminateComment(buff); // process //... and blank/tab padding
            mode=search(buff,mode,rFile,fn); // produces inheritance records
            if(mode<0)return 1;
        }
    }
    return ret;
}

// ------------------------------------------------------------------
// Print records similar to the DataStructure statements to which
// the corresponding record from the lib\registry has been added (e.g. u1-*)
// Returns: 0=everything OK, >0 means errors.
// ------------------------------------------------------------------
int Generator::extractAssociations(FILE *fp){
    Organization *org; PartType *pType; Participant *part; OrgType *oType;
    ApplClass *ap;
    int i; char c;
    orgs_Iterator oIter; 
    parts_Iterator pIter; 

    // print one line for each Organization
    oIter.start(this);
    ITERATE(oIter,org){
        // print the special code from lib\registry, e.g. b1=*
        oType=myType::fwd(org);

        // treat Name as a special case, just like Inheritance
        if(!strcmp("Name",orgTypeName::get(oType))){
            part=parts::head(org);
            fprintf(fp,"Name %s %s ;\n",
                           partName::get(part),orgName::get(org));
            continue;
        }

        fprintf(fp,"%s",oType->getCode());
         
        // print the organization type
        fprintf(fp," %s",orgTypeName::get(oType));

        // print the types of the participants
        pIter.start(org);
        ITERATE(pIter,part){
            fprintf(fp," %s",partName::get(part));
        }
  
        // print the organization name
        fprintf(fp," %s ;\n",orgName::get(org));
    }
    return 0;
}

// ------------------------------------------------------------------
// Reduce buffer b to the last blank-separated token, return the size
// including one additional blank at the end.
// ------------------------------------------------------------------
int Generator::reduce(char *b){
    int i,k,n;
    n=strlen(b);
    if(n<=0)return 0;
    for(i=n-1; i>=0; i--){
        if(b[i]==' ')break;
    }
   
    for(i=i+1, k=0; i<n; i++,k++) b[k]=b[i];
    b[k]=' '; k++; // add one blank at the end
    return k;
}

// ------------------------------------------------------------------
// Process buffer b:
// - eliminate all \n or \r (they are not essential in this context)
// - cut off end for //.... type comment,
// - eliminate leading blanks/tabs
// - replace multiple blank/tab groups by a single blank (eliminate tabs)
// ------------------------------------------------------------------
void Generator::eliminateComment(char *b){
    int i,k,leading,padding; char c;

    leading=1;
    padding=0;
    for(i=0, k=0; b[i]; i++){ // i=read index, k=write index
        c=b[i];
        if(c=='\t'  || c==',')c=' '; // treat comma and tab as blanks
        if(c=='\n' || c=='\r')continue; // always skip them
        if(leading){
            if(c==' ')continue; // eliminate leading char
        }
        leading=0;
        if(c=='/' && b[i+1]=='/'){
            b[k]='\0';
            break;
        }

        // eliminate multiple padding
        if(c==' '){
            if(padding)continue;
            padding=1;
        }
        else padding=0;
        b[k]=c; k++;
    }
    b[k]='\0'; // make a new ending
}
        
        
// ------------------------------------------------------------------
// Search through buffer depending on the mode, then return the mode
// so the next search can use it. Return -1 means error.
//
// mode=0 searching for the pattern:
//               class something :
//        and discarding when two :: are used.
//  bit1  '"' was detected, discard everything until the end of this text string
//  bit2  /* detected, discard everything until */
//  bit4  inheritance record in process until '{' is found
// When entering with mode=0, it is externally arranged that if ':'
// is found, the last token which was before it (possibly several lines back)
// is also in b.
// Discard lines starting with '#'
// Algorithm:
//   This is essentially a state machine walking through the characters of b.
//   b is \0 ending.
// Note the bit preference: 1,2,4.
// ------------------------------------------------------------------
int Generator::search(char *b,int mode,FILE *rFile,char *fileName){
    int i,k,endOfB,endOfInh; char c,prev,nxt; char *last;
    ApplClass *ac; ClassLink *cLink;

    endOfB=0;
    for(i=0, k=0; b[i] && !endOfB; i++){
        c=b[i];
        if(mode&1){ // search for the second '"'
            for(; b[i]; i++){
                c=b[i];
                if(c=='"'){
                    if(i>0 && b[i-1]!='\\')break;
                }
            }
            if(c)mode=mode & 6;
            continue;
        }

        else if(mode&2){ // search for "*/"
            for(; c=b[i]; i++){
                if(c=='*' && b[i+1]=='/')break;
            }
            if(c)mode=mode & 5;
            i++;
            continue;
        }

        else if(mode&4){ // search for '{' and record inheritance along the way
            if(c=='/' && b[i+1]=='*'){
                mode=mode | 2;
                i++;
                last=NULL;
                continue;
            }
            if(c=='{'){
                fprintf(rFile," ;\n");
                derived=NULL;
                mode=mode & ~4;
                continue;
            }
            if(c==' ')continue;
            // detected a new token
            last= &(b[i]);

            for(; b[i]; i++){
                if(b[i]==' ' || b[i]=='{')break;
            }
            if(!b[i])endOfB=1;  // end of buffer b
            if(b[i]=='{')endOfInh=1; else endOfInh=0;
            b[i]='\0';
            if(strcmp(last,"public") && strcmp(last,"private") &&
                                        strcmp(last,"protected")){
                fprintf(rFile," %s",last); 

                ac=getOrCreateApplClass(last);
                cLink=new ClassLink(0); // 0=in C++ always inheritance
                dependsOn::addTail(derived,cLink);
                toBase::add(cLink,ac);
            }
            if(endOfInh){
                mode=mode & ~4;
                fprintf(rFile," ;\n");
            }
            if(endOfB)break;
            continue;
        }

        else {           // search for " : ", '"', or "/*"
            for(; b[i]; i++){
                c=b[i];
                if(c==':'){
                    if(i==0)prev=' '; else prev=b[i-1];
                    nxt=b[i+1]; if(nxt=='\0')nxt=' ';
                    if(prev==':' || nxt==':')continue;
                    // inheritance detected, print the previous token
                    last=getLast(b,i); // may turn b[i] into '\0'
                    // For pattern: class last :    it returns last,
                    // if 'class' is mising or
                    // if last='private'||'protected'||'public' returns NULL
                    if(!last)continue;
                    if(!strcmp(last,"public") || !strcmp(last,"private")
                                 || !strcmp(last,"protected"))continue;
                    fprintf(rFile,"Inherits %s",last);
                    derived=getOrCreateApplClass(last);
                    b[i]=':'; // res-set b[i] back to what it was
                    mode=4;
                    break;
                }
                else if(c=='/' && b[i+1]=='*'){
                    i++;
                    mode=2;
                    break;
                }
                else if(c=='"'){
                    if(i>0){
                        if(b[i-1]=='\\')continue;
                    }
                    i++;
                    mode=1;
                    break;
                }
            }
            if(b[i]=='\0')break;
        }
    }
    return mode;
}

// ------------------------------------------------------------------
// Search b backward from the ':' (index n) for the last blank-separated token.
// Return pointer to its beginning, and set the end to \0 to make it
// a proper string.
// However, all this is valid only if we deal with the inhertance definition 
// which we want to detect:
//   class B : public A {
// but not(!) when declaring access
//   public:
// or in constructors of derived classes
//   B() : A() {   // where class B inherits A
// In such cases this function returns NULL.     
// The outside code already eliminates the case of casting
//   A::add(...
// WARNING: This function may set b[i] or b[i-1] to '\0'
// ------------------------------------------------------------------
char* Generator::getLast(char *b,int n){
    int i,ii,k; 

    if(n<=0)return NULL;
    if(b[n-1]==' ')ii=n-2; else ii=n-1;
    b[ii+1]='\0';
    k= -1; // k will be the start of the token to return, -1 for not found
    for(i=ii; i>=0; i--){
        if(b[i]==' '){k=i+1; b[i]='\0'; break;}
    }
    if(i<0)return NULL; // no previous token

    // if the token declares access, return NULL (not an inheritance definition)
    if(!strcmp("public",&(b[k])) || 
       !strcmp("protected",&(b[k])) || 
       !strcmp("private",&(b[k]))){
        return NULL;
    }

    // get the next previous token and make sure it is 'class'
    for(i=k-2; i>=0; i--){
        if(b[i]==' ')break;
    }
    if(strcmp("class",&(b[i+1])))return NULL;

    return &(b[k]);
}
    
        
// ------------------------------------------------------------------
// Search the given buffer b for ".h" or ".H" or ".cpp" or ".CPP",
// set \0 after it,
// and return pointer to the beginning of the name, e.g. "myFile.h".
// Return NULL if none of the special file types is found.
// ------------------------------------------------------------------
char* Generator::getFileName(char *b){
    int i;

    for(i=0; b[i]; i++){
        if(b[i]!='.')continue;
        if(b[i+1]=='h' || b[i+1]=='H'){
            b[i+2]='\0';
            break;
        }
        if(!strncmp(&(b[i+1]),"cpp",3) ||
           !strncmp(&(b[i+1]),"CPP",3)){
            b[i+4]='\0';
            break;
        }
    }
    if(!b[i])return NULL;
    for(i=i-1; i>=0; i--){
        if(b[i]==' ' || b[i]=='\t')break;
    }
    return &(b[i+1]);
}

// ------------------------------------------------------------------
// The main generator functions. Creates files outFileName.h and outFileName.cpp
// (or outFileName.m) using *.c and *.cpp (or *.m) generic files from 
// directory libPath.
// Returns: 0=everything OK, >0 errors
// ------------------------------------------------------------------
int Generator::generate(){
    FILE *hFile,*cFile;
    char fName[80];

    strcpy(fName,outFileName); strcat(fName,".h");
    hFile=fopen(fName,"w");
    if(!hFile){printf("codegen: problem to open file %s\n",fName); return 1;}

    fprintf(hFile,"#ifndef ZZ_CODEGEN_INCLUDE\n");
    fprintf(hFile,"#define ZZ_CODEGEN_INCLUDE\n\n");

    fprintf(hFile,"#include \"%s/general.h\"\n",libPath);
    genClasses(hFile);
    genIncludes(hFile,0,"tmp");
    if(genDefinitions(hFile))return 1;
    genInsertions(hFile);
    genTypedefs(hFile);

    fprintf(hFile,"\n#endif // ZZ_CODEGEN_INCLUDE\n");
    fclose(hFile);
    // ------------------------------

    strcpy(fName,outFileName);
    if(objcRun) strcat(fName,".m");
    else        strcat(fName,".cpp");

    cFile=fopen(fName,"w");
    if(!cFile){printf("codegen: problem to open file %s\n",fName); return 1;}

    genIncludes(cFile,1,"tmp");
    fclose(cFile);
    // ------------------------------
    
    genFiles(libPath,"tmp");
    return 0;
}

// --------------------------------------------------------------------------
// COnverts integer into a string, and loads it into the preallocated s.
// Similar but not identical to itoa() -- has a different last parameter.
// If the size of the resulting string is larger than sz (allocated length of s)
// the function returns NULL, otherwise it returns s.
// The function also returns NULL when i<0;
// The reason for coding this function is that some C++ compilers do not have
// itoa().
// NOTE: In this program, the performance of this function is not critical.
// --------------------------------------------------------------------------
char* Generator::i2s(int i,char *s,int sz){
    int k,n,j,m;
    char d[]={'0','1','2','3','4','5','6','7','8','9'}; 

    if(i<0)return NULL; // function handles only i>=0
    for(k=0; k<sz-1; k++){
        n=i/10;
        j=i-n*10;
        // shift the existing string by 1
        for(m=k; m>0; m--){s[m]=s[m-1];} // no shift for k=0
        s[0]=d[j];
        if(n<=0)break;
        i=n;
    }
    if(k>=sz-1)return NULL;
    s[k+1]='\0';
    return s;
}

// --------------------------------------------------------------------------
// Generate *.h and *.cpp files for used organizations. Replace
// $$, $0, $1, $2, ... by the organization name and participating class names.
// Algorithm: For each organization, start with a call to setInhNames() which
//            fills inhName for all PartTypes involved in all inheritance levels.
//            After this, setting parameters for each inheritance level is
//            straightforward. All this is needed because the inheritance
//            may change the order or number of parameters - for example, see
//            LinkedList2 and Ring2.
// --------------------------------------------------------------------------
void Generator::genFiles(char *sourcePath,char *targetPath){
    int i,k,j,level;
    char name1[256], name2[256];
    char* depth=new char[8]; // decimal expressing inheritance depth,NULL ending

    char* exth=".h"; char* extp=".cpp"; 
    if(objcRun)extp=".m";

    Organization *org;
    OrgType *ot;
    PartType *pt;
    orgs_Iterator oIter;
    partTypes_Iterator ptIter;

    typedef char* ptr_type;
    char **params=new ptr_type[8];// most data structures have 2 or 3 parameters
    int numParams;                // only many-to-many has 4 parameters
    int maxParams=8;

    oIter.start(this);
    ITERATE(oIter,org){
        if(setInhNames(org))break; // error situation when break

        // count inheritance levels
        for(level=0, ot=myType::next(org); ot; level++, ot=inherits::next(ot)){
            continue;
        }

        for(k=0; k<level; k++){
            for(j=level-1, ot=myType::next(org); ot;
                                                 j--, ot=inherits::next(ot)){
                if(j==k)break;
            }
            if(!ot){
                printf("internal error in genFiles(), level calculation\n");
                return;
            }
     
            if(!i2s(k,depth,8)){
                printf("internal error in genFiles(), depth[8] not enough\n");
                return;
            }
            // fill params[] with the names stored in inhName on ot
            params[0]=orgName::get(org);
            i=1;
            ptIter.start(ot);
            ITERATE(ptIter,pt){
                if(i>=maxParams){
                   printf("internal error in genFiles(), maxParams exceeded\n");
                   return;
                }
                params[i]=inhName::get(pt);
                i++;
            }
            numParams=i;

            strcpy(name1,sourcePath); strcat(name1,"/");
            strcat(name1,fileName::get(ot));
            strcat(name1,exth);
            strcpy(name2,targetPath); strcat(name2,"/");
            strcat(name2,orgName::get(org)); 
            if(k>0)strcat(name2,depth);
            strcat(name2,exth);
            substitute(name1,name2,params,numParams,objcRun);

            strcpy(name1,sourcePath); strcat(name1,"/");
            strcat(name1,fileName::get(ot));
            strcat(name1,extp);
            strcpy(name2,targetPath); strcat(name2,"/");
            strcat(name2,orgName::get(org)); 
            if(k>0)strcat(name2,depth);
            strcat(name2,extp);
            substitute(name1,name2,params,numParams,objcRun);

            if(ot==myType::next(org))break; 
        }
    }
}

// --------------------------------------------------------------------------
// Set inhName for all the subclasses of 'org'.
// The logic of the data organization is described in the comment section
// right after the DataStructure block.
//
// There are two mechanisms which are used here.
// (1) For parameters represented as $x in the registry file, SingleLink
// inhMatch leads directly from the PartType of the derived OrgType to
// the PartType of the base OrgType.
// (2) For fixed parameters (no $ used in the registry file), the derived
// OrgType keeps a list (collection) of FixedType instance, each with
// a fixed name and with a singleLink to the PartType of the base OrgType.
// 
// Note that inhName is set as a pointer to already allocated string,
// which is kept for a temporary reference.
//
// The purpose of this function is to fill temporary inhName so that
// the generator can create the new code in a simple sweep.
// Returns: 0=normal, >0 errors
// --------------------------------------------------------------------------
int Generator::setInhNames(Organization *org){
    Participant *part;
    OrgType *ot,*otNext;
    PartType *pt,*ptInh;
    FixedType *ft;
    parts_Iterator pIter;
    partTypes_Iterator pTypes;
    fixedTypes_Iterator ftIter;

    // proceed through all levels of inheritance and set inhName=NULL
    for(ot=myType::next(org); ot; ot=inherits::next(ot)){
        pTypes.start(ot);
        ITERATE(pTypes,pt){
            if(inhName::get(pt))inhName::remove(pt);
        }
    }

    // start by setting the top class
    pIter.start(org);
    ITERATE(pIter,part){
        pt=myPartType::next(part);
        inhName::add(pt, partName::get(part));
    }

    // proceed gradually deeper and deeper into the base classes
    for(ot=myType::next(org), otNext=NULL; ot; ot=otNext){
        otNext=inherits::next(ot);
        if(!otNext)break;

        // set the $-style references
        pTypes.start(ot);
        ITERATE(pTypes,pt){
            ptInh=inhMatch::next(pt);
            if(ptInh)inhName::add(ptInh, inhName::get(pt));

        }

        // set the fixed names
        ftIter.start(ot);
        ITERATE(ftIter,ft){
            ptInh=inhFixed::next(ft);
            inhName::add(ptInh, fixedName::get(ft));
        }
    }
    if(!otNext)return 0;
    return 1;
} 

// --------------------------------------------------------------------------
// Generate typedefs for all the Iterators.
// This means to go through all organizations, and then through their Iterators
// --------------------------------------------------------------------------
void Generator::genTypedefs(FILE *file){
    char *itName;
    Organization *org;
    OrgType *ot;
    Iterator *iter;
    orgs_Iterator oIter;
    iters_Iterator iIter;

    fprintf(file,"\n");
    oIter.start(this);
    ITERATE(oIter,org){
        ot=myType::next(org);
        iIter.start(ot);
        ITERATE(iIter,iter){
            itName=iterName::get(iter);
            fprintf(file,"typedef %s_%s%s",
                    orgName::get(org),orgTypeName::get(ot),itName);
            fprintf(file," %s_%s;\n",orgName::get(org),itName);

            
            if(dolRun && !strcmp(itName,"Iterator")){
                // print the same again with 'iterator' instead "Iterator"
                fprintf(file,"typedef %s_%s%s",
                    orgName::get(org),orgTypeName::get(ot),itName);
                fprintf(file," %s_iterator;\n",orgName::get(org));
            }
    
        }
    }
}


// --------------------------------------------------------------------------
// Generate definitions of organizations.
// Returns: 0=normal
// --------------------------------------------------------------------------
int Generator::genDefinitions(FILE *file){
    int i; 
    Organization *org;
    OrgType *ot;
    Participant *part;
    orgs_Iterator oIter;

    fprintf(file,"// -----------------------------------------------\n");
    if(dolRun==1)fprintf(file,"#ifdef ZZmain\n");
    for(i=0; i<=dolRun; i++){ // for 'dol' style, run this twice
        if(i==1)fprintf(file,"\n#else // ZZmain\n");
        oIter.start(this);
        ITERATE(oIter,org){
            ot=myType::next(org);
            if(objcRun==1)    fprintf(file,"typedef ");
	    else if(dolRun==0)fprintf(file,"typedef class ");
            if(i==1)fprintf(file,"extern ");
            fprintf(file,"%s_%s",orgName::get(org),orgTypeName::get(ot));
            fprintf(file," %s;\n",orgName::get(org));
        }
    }
    if(dolRun==1)fprintf(file,"#endif // ZZmain\n");
    fprintf(file,"// -----------------------------------------------\n");
    fprintf(file,"\n");
    return 0;
}

// --------------------------------------------------------------------------
// This is a simple-minded O(n*n) algorithm, but there is no point trying
// to be efficient with typically at most a few dozens organizations.
// --------------------------------------------------------------------------
void Generator::genInsertions(FILE *file){
    Organization *org;
    Participant *part;
    orgs_Iterator oIter;
    parts_Iterator pIter;

    oIter.start(this);
    ITERATE(oIter,org){
        pIter.start(org);
        ITERATE(pIter,part){
            if(isBasicType(part))continue; // no inserts needed for basic types
            if(part->isUsed())continue;

            // next line may change isUsed)() on many participants
            searchParticipants(file,part); 
        }
    }
}

// --------------------------------------------------------------------------
// Go through all participants, and pick up those that have the same 'partAppl'
// and mark them as used. Then, for each of them,
// create a member statement for ZZds, plus several 'friend' statements
// derived from the organization of that participant.
// --------------------------------------------------------------------------
void Generator::searchParticipants(FILE *file,Participant *curPart){
    int first,record;
    Organization *org,*myOrg,*baseOrg;
    Participant *part,*myPart,*pp;
    PartType *pt;
    Iterator *iter;
    orgs_Iterator oIter;
    parts_Iterator pIter;
    parts_Iterator ppIter;

    // ...................................................
    // First loop generates the ZZS structures
    // ...................................................
    
    record=0; // if stays 0, use #define for ZZ_...
    oIter.start(this);
    ITERATE(oIter,org){
        pIter.start(org);
        ITERATE(pIter,part){
            if(strcmp(partName::get(curPart),partName::get(part)))continue;
            if(part->isUsed())continue; // can happen because of the next loop
            if(isBasicType(part))continue; // no insertion for basic types

            // loop includes the case when parent&child are the same class 
            first=1;
            ppIter.start(org);
            ITERATE(ppIter,pp){
                pt=myPartType::next(pp);
                if(strcmp(partName::get(pp),partName::get(part)))continue;

                pp->setUsed(1); //1 = used for ZZS
                if(!pt->isRefOnly()){
                    if(!record){
                        if(objcRun)fprintf(file,"\nstruct ZZS_%s {\n",
                                                    partName::get(curPart));
			else       fprintf(file,"\nclass ZZ_%s {\npublic:\n",
                                                    partName::get(curPart));
                        record=1;
                    }
                    myOrg=parts::parent(part);
                    if(first){
			fprintf(file,"    %s_",orgName::get(myOrg));
		    }
                    fprintf(file,"%s",partTypeName::get(pt));
                    first=0;
                }
            }
            if(!first){
		if(objcRun)fprintf(file,";\n",orgName::get(myOrg));
		else       fprintf(file," ZZ%s;\n",orgName::get(myOrg));
	    }
        }
		                         	
    }

    if(record){
        fprintf(file,"};\n");
        if(objcRun)fprintf(file,"typedef struct ZZS_%s ZZ_%s;\n",
                           partName::get(curPart),partName::get(curPart));
    }
    else fprintf(file,"#define ZZ_%s static int\n",partName::get(curPart));

    if(!objcRun)return;

    // ...................................................
    // Second loop generates the ptrLists: same logic, only different prints
    // ...................................................
    
    record=0; // if stays 0, create empty ptrList
    oIter.start(this);
    ITERATE(oIter,org){
        pIter.start(org);
        ITERATE(pIter,part){
            if(strcmp(partName::get(curPart),partName::get(part)))continue;
            if(part->isUsed()>1)continue; // can happen because of the next loop
            if(isBasicType(part))continue; // no insertion for basic types

            // loop includes the case when parent&child are the same class 
            first=1;
            ppIter.start(org);
            ITERATE(ppIter,pp){
                pt=myPartType::next(pp);
                if(strcmp(partName::get(pp),partName::get(part)))continue;

                pp->setUsed(2); // 2 = used for ptrLists
                if(!pt->isRefOnly()){
                    if(!record){
                        fprintf(file,"\n#define ptrList_%s \\\n",
                                                    partName::get(curPart));
			ptrListFirstLines(file);
                        record=1;
                    }
                    myOrg=parts::parent(part);
                    if(first){
			fprintf(file,"    %s_",orgName::get(myOrg));
		    }
                    fprintf(file,"%s_ptrList",partTypeName::get(pt));
                    first=0;
                }
            }
            if(!first){
		fprintf(file,";\\\n",orgName::get(myOrg));
	    }
        }
		                         	
    }

    if(record){
        fprintf(file,"    return self;\\\n}\n");
    }
    else {
        fprintf(file,"\n#define ptrList_%sd\\\n",partName::get(curPart));
       	ptrListFirstLines(file);
        fprintf(file,"}\n");
    }
}

// --------------------------------------------------------------------------
void Generator::ptrListFirstLines(FILE *file){
    fprintf(file,"- (id) ptrList { \\\n");
#ifdef SEAN
    fprintf(file,"    Class supC = [self superclass];\\\n");
    fprintf(file,"    if(supC != nil && class_respondsToSelector");
    fprintf(file,"(supC, @selector(ptrList))) {\\\n");
    fprintf(file,"        struct objc_super sup = { self, supC };\\\n");
    fprintf(file,"        objc_msgSendSuper(&sup, @selector(ptrList));\\\n");
    fprintf(file,"    }\\\n");
#else
    fprintf(file,"    [super ptrList];\\\n");
#endif
}

// --------------------------------------------------------------------------
// generate the include section of the file:
// for type=0: *.h file
// for type=1: *.cpp file
// --------------------------------------------------------------------------
void Generator::genIncludes(FILE *file,int type,char *libPath){
    int i,level;
    char *ext;

    Organization *org;
    OrgType *ot;
    orgs_Iterator oIter;

    if(objcRun){
        if(type==0)ext="h"; else ext="m";
    }
    else {
        if(type==0)ext="h"; else ext="cpp";
    }
    oIter.start(this);
    ITERATE(oIter,org){
        // count inheritance level
        for(level=0, ot=myType::next(org); inherits::next(ot);
                                            level++, ot=inherits::next(ot)){
            continue;
        }
        if(level==0)fprintf(file,"#include \"%s/%s.%s\"\n",
                                              libPath,orgName::get(org),ext);
        else {
            for(i=0; i<=level; i++){
                if(i==0)fprintf(file,"#include \"%s/%s.%s\"\n",
                                              libPath,orgName::get(org),ext);

                else fprintf(file,"#include \"%s/%s%d.%s\"\n",
                                              libPath,orgName::get(org),i,ext);
            }
        }
    }
    fprintf(file,"\n");
}

// --------------------------------------------------------------------------
// Debugging print of the internal data structures
// --------------------------------------------------------------------------
void Generator::debPrt(){
    int i;

    Organization *org;
    OrgType *ot,*oInh;
    Participant *part;
    PartType *pt;
    FixedType *ft;
    orgs_Iterator oIter;
    parts_Iterator pIter;
    partTypes_Iterator ptIter;
    fixedTypes_Iterator ftIter;

    printf("\nDEBUG PRINT:\n");
    oIter.start(this);
    ITERATE(oIter,org){
        ot=myType::next(org);
        printf("orgName=%s type=%s file=%s\n",


                  orgName::get(org),orgTypeName::get(ot),fileName::get(ot));
        oInh=inherits::next(ot);
        if(oInh){
            setInhNames(org);
            for( ; oInh; oInh=inherits::next(oInh)){
                printf("    --- inherits from=%s(",orgTypeName::get(oInh));
                i=0;
                ptIter.start(oInh);
                ITERATE(ptIter,pt){
                    if(i>0)printf(",");
                    printf("%s",inhName::get(pt));


                    i++;
                }
                printf(")\n");

                printf("    --- fixed names from=%s(",orgTypeName::get(oInh));
                i=0;
                ftIter.start(oInh);
                ITERATE(ftIter,ft){
                    if(i>0)printf(",");
                    printf("%s->",fixedName::get(ft));
                    pt=inhFixed::next(ft);
                    printf("%s",inhName::get(pt));
                    i++;
                }
                printf(")\n");
            }
        }
        pIter.start(org);
        ITERATE(pIter,part){
            pt=myPartType::next(part);
            printf("    %d: partName=%s   %d: partTypeName=%s\n",
                  part->getIndex(), partName::get(part),
                  pt->getIndex(), partTypeName::get(pt));
        }
    }
    printf("\n");
}

// --------------------------------------------------------------------------
// Generate a list of all the classes that participate in any data structures.
// No need to be super efficient here, this is an O(n*n) search:
// --------------------------------------------------------------------------
void Generator::genClasses(FILE *file){
    int printed; // 0=before search, 1=confirmed not printed, 2=already printed
    Organization *org,*org2;
    Participant *part,*part2;
    orgs_Iterator oIter,oIter2;
    parts_Iterator pIter,pIter2;

    fprintf(file,"\n");
    oIter.start(this);
    ITERATE(oIter,org){
        pIter.start(org);
        ITERATE(pIter,part){

            // avoid printing basic types
            if(isBasicType(part))continue;
    
            // check that this class has not been listed yet
            printed=0;
            oIter2.start(this);
            ITERATE(oIter2,org2){
                pIter2.start(org2);
                ITERATE(pIter2,part2){
                    if(part2==part){printed=1; break;}
                    if(!strcmp(partName::get(part),partName::get(part2))){
                        printed=2; break;
                    }
                }
                if(printed>0)break;
            }
            if(printed==1){
		if(objcRun) fprintf(file,"@class %s;\n",partName::get(part));
		else        fprintf(file,"class %s;\n",partName::get(part));
	    }
        }
    }
    fprintf(file,"\n");
}


int main(int argc,char **argv){
    int umlRun,err,dolRun,numOpt,objcRun,i;

    err=umlRun=dolRun=numOpt=objcRun=0;
    if(argc<4)err=1;
    else {
        for(i=0; i<argc; i++){
            if(!strcmp(argv[i],"-dol")){
                dolRun=1; numOpt++;
            }
	    else if(!strcmp(argv[i],"-uml")){
                umlRun=1; numOpt++;
            }
	    else if(!strcmp(argv[i],"-objc")){
                objcRun=1; numOpt++;
            }
        }
    }

    if(umlRun){
        if(argc-numOpt != 6)err=1;
    }
    else {
        if(argc-numOpt != 4)err=1;
    }

    if(err){
        printf("ERROR in calling codegen(), two styles of use allowed:\n");
        printf("codegen [-dol] [-objc] dsFile libPath genFile\n");
        printf("codegen -uml [-dol] [-objc] dsFile libPath genFile srcList umlID\n");
        return 1;
    }

    Generator generator(umlRun,dolRun,objcRun,&(argv[numOpt+1]));

    if(umlRun){
        if(generator.genUmlFile())return 1;
    }
    
    if(generator.generate())return 1;
    return 0;
}
