This directory contains extensive tests of the 'aLib' library
=============================================================
You can run all these tests simply by typing 
    regrwin
which invokes the regression sequence (regrwin.bat) for MS Windows.

This sequence includes testABC which is the sample problem from the
book The Next Software Revolution (Chap.4.10).
Other programs usually work with several data structures, but are designed
to test extensively the data structure indicated by the name. For example,
programs array_1.cpp, array_2.cpp, ..., array_5.cpp test various features
of class 'Array' (dynamically adjustable array).

The aLib library can be used in two modes: regular mode when methods
of all data structures are 'static', or the mode compatible with the
old Data Object Library (using option -dol when calling codegen). 

Note that #define ZZmain is needed only when running in the 'dol' mode.

At the moment there is no documentation for aLib, but methods of
individual classes have intuitive functionality, which is identical
with the DOL library - if you are familiar with it.

A full, proper documentation for aLib will be add soon.

-----------------------------
Book examples:
-----------------------------
(A) For example from Chap.4.10, see test/book.cpp
       cc.bat compiles the program
       rr.bat runs it
    It is the same program as in cd\alib\ttest\book.cpp
    Warning:
         The example in the book differs a bit because of different class names
         which, in the book are chosen to match the previous chapters.
         Also, in the book we only have Aggregate which inherits from Collection
         but Collection is fully coded, not derived from Ring as it is in 
         this library.

(B) Widget example from Chap.4.12 coded with pure STL (aLib not involved)
is in widget.cpp:
       cl -GX widget.cpp
       widget

(C) File test\vector.cpp has the code for the same problem from Chap.4.12,
    where aLib is used as wrapper for the STL vector class.
        tt   ... will compile and run the program.

(D) The same program can be used to test bi-directional association based
    on the STL vector class (also discussed in Chap.4.12).
        replace                DataStructure Vector1<Holder,Widget> wVect;
        by                     DataStructure Vector2<Holder,Widget> wVect;
    and then type
        tt
-----------------------------
Remaining tests are each in a separate subdirectory.
In order to run the individual tests, go to the particular directory
and type 'tr'. This works both under Windows or Linux (files tr.bat and tr).
-----------------------------
    

