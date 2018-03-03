// This is a utility program for the initial booting of the code generator.
// It reads the file given as the first parameter, and replaces all '$$'
// '$1', '$2', etc by the text strings of given parameters.
//                                                   
// The utility does this automatically for both *.h and *.cpp files.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char **argv) {
    char inFile[80],outFile[80];
    int nameSz=80;

    typedef char* ptr_type;
    int i,numParams;
    void substitute(char *fName1,char *fName2,char **params,int numParams,int objcRun);
    char **params=new ptr_type[8];
    int maxParams=8;  

    if(argc<4 || argc>maxParams+3){
        printf("syntax: replace inpFile outFile orgName param1 param2 ...\n");
        return 1;
    }

    if(strlen(argv[1])>nameSz-5 || strlen(argv[2])>nameSz-5){
        printf("file names used in utility 'replace' are over %d characters\n",
                                                           nameSz-5);
        return 2;
    }

    for(i=3; i<argc; i++){
        params[i-3]=argv[i];
    }
    numParams=argc-3;
    
    strcpy(inFile,argv[1]);  strcat(inFile,".h");
    strcpy(outFile,argv[2]); strcat(outFile,".h");
    substitute(inFile,outFile,params,numParams,0); // 0 for C++
    
    strcpy(inFile,argv[1]);  strcat(inFile,".cpp");
    strcpy(outFile,argv[2]); strcat(outFile,".cpp");
    substitute(inFile,outFile,params,numParams,0); // 0 for C++
    return 0;
}
