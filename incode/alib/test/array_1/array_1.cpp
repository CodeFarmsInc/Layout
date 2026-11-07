// ------------------------------------------------------------------------
// This is test16c from the DOL regression suite, and the results
// should be identical except for the type information which is formatted 
// differently.
// This program tests not only Array, but also Ring1, SingleLink and
// Name organizations.
//                                        Jiri Soukup, Mar.10, 2004
// ------------------------------------------------------------------------
// The input file has two types of records:
// P name age salary              // person description
// C name1 name2 numberOfChidren  // couple description
// ------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include "gen.h"

class PrtObject {
public:
    virtual void prt(FILE *fp){fprintf(fp,"PrtObject\n");}
};

class Header : public PrtObject {
public:
    ZZ_Header ZZds;
    void prt(FILE *fp){fprintf(fp,"Header\n");}
};

class Person : public PrtObject {
public:
    ZZ_Person ZZds;
    int age;
    float salary;
    void prt(FILE *fp){fprintf(fp,"Person=%s age=%d salary=%6.2f\n",
                                                   name.get(this),age,salary);}
};

class Couple : public PrtObject {
public:
    ZZ_Couple ZZds;
    int numChild;
    void prt(FILE *fp){fprintf(fp,"Couple numChild=%d/n",numChild);}
};

#define BSIZE 80

int main(int argc,char **argv) {
    char bf[BSIZE],name1[BSIZE],name2[BSIZE];
    Person *getPerson(Person *p,char *nm);
    void printObj(char *obj,int typeInd,int size,const char *priv);
    void printAll(FILE *fp,Header *h);
    FILE *file1,*file2;
    Header *h;
    char c,*n1,*v[1],*t[1];
    int i,n,age,child,*ci;
    float salary;
    Person *sp,*pp,*p1,*p2;
    Couple *cp;

    if(argc<=1)file1=stdin;  else file1=fopen(argv[1],"r");
    if(argc<=2)file2=stdout; else file2=fopen(argv[2],"w");

    h=new Header;
    sp=(Person *)NULL;
    n=i=0;
    while(fgets(bf,BSIZE,file1)){
        sscanf(bf,"%c",&c);
        if(c=='P'){
            if(n<0){printf("all P records must preceed C records\n");return(0);}
            n++;
            sscanf(bf,"%c %s %d %f",&c,name1,&age,&salary);
            pp=new Person;
            pp->age=age;
            pp->salary=salary;
            n1=new char[strlen(name1)+1]; strcpy(n1,name1);
            name.add(pp,n1);
            sp=people.add(sp,pp);
        }
        else if(c=='C'){
            if(n>0){
                (void)arr.form(h,n/2,3);
                if(!cArr.formed(h))ci=cArr.form(h,n/2,3); // test of formed()
                if(!cArr.formed(h))ci=cArr.form(h,n/2,3); // should not form
                n= -1;
            }
            sscanf(bf,"%c %s %s %d",&c,name1,name2,&child);
            p1=getPerson(sp,name1);
            p2=getPerson(sp,name2);
            if(p1 && p2){
                cp=arr.ind(h,i);
                per1.add(cp,p1);
                per2.add(cp,p2);
                cp->numChild=child;
                ci[i]=child;
                i++;
            }
            else printf("wrong couple definition %s %s\n",name1,name2);
        }
    }
    fclose(file1);

    printAll(file2,h);
    return(0);
}
/* ------------------------------------------------------------------ */
Person *getPerson(Person *sp,char *nm)
{
    Person *pp;
    char *nn;
    people_iterator pIter;

    pIter.start(sp);
    for(pp= ++pIter;pp;pp= ++pIter){ // See NOTE at the end of the code
        nn=name.get(pp);
        if(!strcmp(nm,nn))return(pp);
    }
    return((Person *)NULL);
}
/* ------------------------------------------------------------------ */
void printAll(FILE *file2,Header *h)
{
    int i,sz;
    int *ci;
    char *n1,*n2;
    Couple *ca;
    Person *p1,*p2,*pp;
    people_iterator pIt;

    sz=arr.size(h);
    ca=arr.ind(h,0);
    ci=cArr.ind(h,0);

    for(i=0;i<sz;i++,ca++){
        p1=per1.target(ca);
        n1=name.get(p1);
        p2=per2.target(ca);
        n2=name.get(p2);

        if(i==0 && p1){ // before the first couple, print the list of all people
            pIt.start(p1);
            ITERATE(pIt,pp){
                pp->prt(file2);
            }
            fprintf(file2,"\n");
        }

        // print the next couple
        fprintf(file2,
          "%s(%d,%6.2f) %s(%d,%6.2f) child=%d\n",
               n1,p1->age,p1->salary,n2,p2->age,p2->salary,ca->numChild);
        if(ca->numChild!=ci[i])fprintf(file2,
                    "   disagreement: i=%d ca=%d ci=%d\n",i,ca->numChild,ci[i]);
    }
}
#include "gen.cpp"

// NOTE: The most convenient way of iterating over a set is to use a while()
//       loop. In this situation, you can simply use:
//                while(pp=pIter++){
//       Unfortunately, many compilers issue warnings for this code.
//       Using the syntactically correct for() is unwieldy:
//                for(pp= ++pIter;pp;pp= ++pIter){
//       but can be hidden under a macro which is provided by the library:
//                ITERATE(pIter,pp){
