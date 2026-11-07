/* Primitive diff - prints error message if files not the same.
 * either prints     "==diff: identical files"
 * or prints an empty line and ">>diff: ..." describing the error
 * Syntax: diff file1 file2
 * or      diff -n file1 file2
 *    if you do not want to check the first n lines.
 * Author: J.Soukup, Sept.27, 2004 */

#include <stdio.h>
#define BSIZE 256

int main(int argc,char **argv){
    int i,k,i1,i2,n;
    char buf1[BSIZE],buf2[BSIZE],*f1,*f2,*s;
    FILE *file1,*file2;

    if(argc<2){printf("diff: wrong syntax\n"); return(1);}
    
    s=argv[1];
    if(*s=='-'){ // option of skipping some lines
        if(argc!=4){printf("\n>>diff: wrong syntax\n"); return(1);}
        i1=2; i2=3;
        sscanf(argv[1]+1,"%d",&n);
    }
    else { // normal, full scale diff
        if(argc!=3){printf("\n>>diff: wrong syntax\n"); return(1);}
        i1=1; i2=2;
        n=0;
    }

    file1=fopen(argv[i1],"r");
    file2=fopen(argv[i2],"r");
    if(!file1){printf("\n>>diff: cannot open file=%s\n",argv[i1]); return(1);}
    if(!file2){printf("\n>>diff: cannot open file=%s\n",argv[i2]); return(1);}
    
    for(i=0; ;i++){
        f1=fgets(buf1,BSIZE,file1);
        f2=fgets(buf2,BSIZE,file2);
        if(!f1 && !f2){ /* normal exit */
            printf("==diff: identical files\n");
            return(0);
        }
        if(!f1){
            printf("\n>>diff: %s has %d lines, %s is longer\n",
                                                        argv[i1],i,argv[i2]);
            return(1);
        }
        if(!f2){
            printf("\n>>diff: %s has %d lines, %s is longer\n",
                                                        argv[i2],i,argv[i1]);
            return(1);
        }

        if(i<n)continue;
        for(k=0; buf1[k]!='\n'; k++){
            if(buf1[k]!=buf2[k]){
                printf("\n>>diff: %s %s: first different line=%d char=%d\n",
                                                        argv[i1],argv[i2],i+1,k);
                return(1);
            }
        }
        if(buf2[k]!='\n'){
            printf("\n>>diff: %s %s: first different line=%d char=%d\n",
                                                        argv[i1],argv[i2],i+1,k);
            return(1);
        }
    }
    printf("\n>>diff: strange exit - never should happen\n");
    return(2);
}
        
