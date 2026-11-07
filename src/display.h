#include <stdio.h>
#include <string.h>
#include <math.h>

// ---------------------------------------------------------
// Base class for symbols used in the UML class diagrams
// frame: 1= using frame, 0= not using the frame
// arrow: 0= no arrow, 1= arrow on x2,y2, 2= inheritance triangle at x2,y2
// Use the constructor of the derived class to enter font size etc.
// ---------------------------------------------------------
class Display {
public:
    virtual void box(int x1,int y1,int x2,int y2) = 0;
    virtual void line(int x1,int y1,int x2,int y2,int arrow) = 0;
    virtual void text(int x,int y,char *txt,int font) = 0;
    virtual void area(int x,int y,int cFont,int aFont) = 0;
    virtual void title(char *titleName) = 0;
    virtual void closeIt() = 0;
};

class NoDisplay : public Display {
public:
    NoDisplay(){printf("--- no graphics selected ---\n");}
    ~NoDisplay(){}
    void box(int x1,int y1,int x2,int y2){}
    void line(int x1,int y1,int x2,int y2,int arrow){}
    void text(int x,int y,char *txt,int font){}
    void area(int x,int y,int cFont,int aFont){};
    void title(char *titleName){}
    void closeIt(){}
};

class LogDisplay : public Display {
    FILE *fp;
public:
    LogDisplay(char *fileName){
        fp=fopen(fileName,"w");
        if(!fp)printf("problem to open LogDisplay file=%s\n",fileName);
    }
    ~LogDisplay(){}
    void box(int x1,int y1,int x2,int y2){
        if(fp)fprintf(fp,"B %d %d %d %d\n", x1,y1,x2,y2);
    }
    void line(int x1,int y1,int x2,int y2,int arrow){
        if(fp)fprintf(fp,"L %d %d %d %d %d\n", x1,y1,x2,y2,arrow);
    }
    void text(int x,int y,char *txt,int font){
        if(fp)fprintf(fp,"T %d %d %s %d\n",x,y,txt,font);
    }
    void area(int xScreen,int yScreen,int cFont,int aFont){
        if(fp)fprintf(fp,"A %d %d %d %d\n",xScreen,yScreen,cFont,aFont);
    }
    void title(char *titleName){
        if(fp)fprintf(fp,"%s\n",titleName);
    }
    void closeIt(){
        if(fp)fclose(fp);
    }
};


class SvgDisplay : public Display {
    FILE *fp;
    int arrowSz,inherSz; // size of special symbols
public:
    SvgDisplay(char *fileName);
    ~SvgDisplay(){}
    void closeIt();
    void text(int x,int y,char *txt,int font);
    void area(int xScreen,int yScreen,int cFont,int aFont);
    void title(char *titleName);
    void line(int x1,int y1,int x2,int y2,int arrow);
    void box(int x1,int y1,int x2,int y2);
};
