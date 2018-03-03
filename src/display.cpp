#include <stdio.h>
#include <string.h>
#include <math.h>
#include "display.h"

SvgDisplay::SvgDisplay(char *fileName) {
        if(!fileName) return;
        fp=fopen(fileName,"w");
        if(!fp){
              printf("SvgDisplay: problem to open file=%s\n",fileName);
        } 
        else {
          printf("creating SVG display file=%s\n",fileName);
          fprintf(fp,"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 20001102//EN\" ");
          fprintf(fp,
       "\"http://www.w3.org/TR/2000/CR-SVG-20001102/DTD/svg-20001102.dtd\"\n>");
          fprintf(fp,"<svg xmlns=\"http://www.w3.org/2000/svg\">\n");
        }
        arrowSz=inherSz=0;
}

void SvgDisplay::closeIt() { 
        fprintf(fp,"</svg>\n");
        if(fp)fclose(fp);
}

void SvgDisplay::text(int x,int y,char *txt,int font){
        if(!fp)return;
        if(!strcmp(txt,"-"))return;  // used as 'no text'
        if(!strcmp(txt,"Inherits"))return; // no label on the inheritance lines
        fprintf(fp,"  <text x=\"%d\" y=\"%d\" ", x, y);
        fprintf(fp,"style=\"fill:black; stroke:none; font-size:%d;",font);
        fprintf(fp,"\">\n    %s\n  </text>\n", txt);
}

void SvgDisplay::box(int x1,int y1,int x2,int y2){
        char *fillColor="#ffffff";
        char *lineColor="black";
        int lineWidth=2;

        if(!fp)return;
        fprintf(fp,"  <rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" ",
                                            x1, y1, x2-x1, y2-y1);
        fprintf(fp,"fill=\"%s\" stroke=\"%s\" stroke-width=\"%d\"/>\n",
                                            fillColor, lineColor, lineWidth);
}

void SvgDisplay::area(int xScreen,int yScreen,int cFont,int aFont){
        arrowSz=(2*cFont)/3;
        inherSz=2*arrowSz;
}

void SvgDisplay::title(char *titleName){
        if(!fp)return;
        fprintf(fp,"  <title>%s</title>\n", titleName);
        fprintf(fp,"  <desc>Automatically generated UML diagram</desc>\n");
}

    // ------------------------------------------------------
    // Display a line, possibly with a special arrow:
    // arrow=-1... no arrow, dashed line
    // arrow=0 ... no arrow
    // arrow=1 ... arrow at x2,y2
    // arrow=2 ... inheritance sign assuming the base class at x2,y2
    // arrow=3 ... interface, like inheritance but a dashed line
    // ------------------------------------------------------
void SvgDisplay::line(int x1,int y1,int x2,int y2,int arrow){ 
        double x,y,xx1,yy1,xx2,yy2,xe,ye,d;

        if(x1==x2 && y1==y2)return; // protection against division by 0
        x=x1-x2; y=y1-y2;
        d=pow(x*x+y*y,0.5);
        x=x/d; y=y/d;

        if(arrow<=1){  // draw the line itself
            fprintf(fp,"  <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"",
                                          x1,y1,x2,y2);
            fprintf(fp," style=\"stroke:rgb(99,99,99);stroke-width:2\" ");
            if(arrow<0)fprintf(fp,"stroke-dasharray=\"6 3\" ");
            fprintf(fp,"/>");
        }

        if(arrow==1){  // draw the arrow
            xx1=arrowSz*(x*0.866+y*0.5); // using cos and sin of 30-degrees 
            yy1=arrowSz*(y*0.866-x*0.5);
            fprintf(fp,"  <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"",
                                          x2,y2,(int)(x2+xx1),(int)(y2+yy1));
            fprintf(fp," style=\"stroke:rgb(99,99,99);stroke-width:2\" />");

            xx2=arrowSz*(x*0.866-y*0.5); // using cos and sin of 30-degrees 
            yy2=arrowSz*(y*0.866+x*0.5);
            fprintf(fp,"  <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"",
                                          x2,y2,(int)(x2+xx2),(int)(y2+yy2));
            fprintf(fp," style=\"stroke:rgb(99,99,99);stroke-width:2\" />");

        }

        if(arrow==2 || arrow==3){ // draw a shorter line and a triangle
            x=x*inherSz;
            y=y*inherSz;
            xx1=x2+x*0.866; 
            yy1=y2+y*0.866;
            fprintf(fp,"  <line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\"",
                                          x1,y1,(int)xx1,(int)yy1);
            fprintf(fp,"  style=\"stroke:rgb(99,99,99);stroke-width:2\" ");
            if(arrow==3)fprintf(fp,"stroke-dasharray=\"6 3\" ");
            fprintf(fp,"/>");

            // rotate x,y by +30-degrees
            xx1=x2+x*(0.866) + y*(0.5);
            yy1=y2+y*(0.866) - x*(0.5);
            fprintf(fp,"\n  <path d=\"M %d,%d L %d,%d",x2,y2,(int)xx1,(int)yy1);

            // rotate x,y by -30-degrees
            xx2=x2+x*(0.866) + y*(-0.5);
            yy2=y2+y*(0.866) - x*(-0.5);
            fprintf(fp," L %d,%d z\"",(int)xx2,(int)yy2);
            if(arrow==2){
              fprintf(fp," style=\"stroke:rgb(99,99,99);stroke-width:2\"");
              fprintf(fp," fill=\"none\" />\n");
            }
            else {
                fprintf(fp," fill=\"black\"/>\n");
            }

        }
}
