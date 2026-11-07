// ------------------------------------------------------------------------
// This program generates the 'paremeter file' with the dimensions of the screen
// and the two main fonts used for the UML diagrams.
// Both fonts are CourierNew - the font for the class boxes is bold, and the font
// for the attributes of associations is regular.
//                                        Jiri Soukup, Jan.5 2005
// ------------------------------------------------------------------------

import java.io.*;
import java.util.*;
import java.awt.*;
import java.math.*;

class GenParamFile extends Frame{
    int cFont,aFont;

    public boolean handleEvent(Event e) {
        if(e.id == Event.WINDOW_DESTROY) System.exit(0);
        return super.handleEvent(e);
    }

    public void setFonts(int c,int a){cFont=c; aFont=a;}

    public void paint(Graphics gr){
        Font fc=new Font("Courier",Font.BOLD,cFont);
        gr.setFont(fc);
        FontMetrics fmc=gr.getFontMetrics(fc);
        int cx=fmc.stringWidth("v");
        int cUp=fmc.getAscent();
        int cDown=fmc.getDescent();

        gr.drawString("Click on X to release this screen",75,100);

        Font fa=new Font("Courier",Font.PLAIN,aFont);
        gr.setFont(fa);
        FontMetrics fma=gr.getFontMetrics(fa);
        int ax=fma.stringWidth("v");
        int aUp=fma.getAscent();
        int aDown=fma.getDescent();

        System.out.println(cFont + " " +cx + " " + cUp + " " + cDown);
        System.out.println(aFont + " " +ax + " " + aUp + " " + aDown);
    }

    public static void main(String[] args) {
        Graphics gr;
        if(args.length<2){
            System.out.println("syntax: genParamFile classFont assocFont");
            return;
        }

        int xFrame = GraphicsEnvironment.getLocalGraphicsEnvironment()
               .getScreenDevices()[0].getDisplayMode().getWidth();
        int yFrame = GraphicsEnvironment.getLocalGraphicsEnvironment()
               .getScreenDevices()[0].getDisplayMode().getHeight();

        // Line 1: screen dimensions in pixels
        System.out.println(xFrame + " " + yFrame);

        int cfont=Integer.parseInt(args[0]);
        int afont=Integer.parseInt(args[1]);

        GenParamFile gpf=new GenParamFile();
        gpf.setFonts(cfont,afont);
        Frame f=gpf;
        f.resize(xFrame,yFrame);
        f.show();

    }
}