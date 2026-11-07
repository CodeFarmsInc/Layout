
PURPOSE
-------
This is the C++ version of the code generator which uses itself to manage
its data structures.
It is very similar to the code generator from lib_4.9, but instead of using
C++ templates, it uses code parametrized by
   $$ ... data structure name (name if its instance)
   $1 ... class name of the first participant
   $2 ... class name of the second participant
             ... etc

Since there are neither templates nor macros (just several macros 
in general.h which are not essential), this code is the starting step
for designing a data structure library in the same style which will work
in Java.

SYNTAX
------
    codegen [-dol] dsFile libPath genFile ... just to compile
    codegen -uml [-dol] dsFile libPath genFile srcList umlID ... also UML 

 where:
    static  uses static functions as interface (recommended),
    dol     uses the old DOL interface (for historical comparison)

    dsFile  is the input file which contains all the DataStructure statements
            used by the program(typically ds.def),
    libPath is the relative or absolute path to the library directory,
            the library must contain the 'registry' file.
    genFile name of the file that will be generated.
    umlID   is a unique ID which will be used for all the UML objects in this
            project
    srcList is an optional list such as produced by "dir *.h" under DOS
            or "ls *.h" under UNIX. When this list is not given, the generator
            does not generate inheritance records.


APPLYING THE CODE GENERATOR TO ITSELF
-------------------------------------
While developing the code generator, files js.h and js.cpp  (or their 
equivalent with a possibly different order of lines) are the files
that the code generator 'codegen' should generate when applied to itself.
These files are useful when developing, modifying, or debugging codegen.

    rr      ... runs the codegen on itself, creates gen.h and gen.cpp
    tt      ... recompiles codegen using these files
-----------
Compiling codegen for the first time or when debugging, do this:
    pp      ... compiles standalone utility 'replace'
    prepare ... makes initial substitution of '$' in the library files
    ttt     ... compiles codegen using hand coded js.h and js.cpp
-----------
After this, you can call any number of times:
    rr
    tt
-----------
Once codegen is compiled, you can also run:
    uu      ... same as rr, but also generates the UML diagram
    

DIRECTORY STRUCTURE
-------------------
Directory 'src' contains the source of the code generator 'codegen'.
Directory 'doc' contains the documentation for this library.

Directory 'lib' contains generic data structures, each data structure
typically requires several files. File lib\registry describes which files
are needed for individual data structures -- one line for each data
structure. For the description of the format - see lib\readme.txt.

Directory 'tmp' contains customized versions of the data structures 
produced by the code generator.

A run of codegen (e.g. rr.bat) re-creates the 'tmp' directory.
For the debugging or the initial compile of the code generator,
the 'tmp' directory can be also created by invoking prepare.bat and 
copying all files from directory 'js' to 'tmp'.

Directory 'test' contains additional testing examples for additional
data structures - those not used in the code generator such as Array or Hash.
The test include both the new and the historical (DOL style) interfaces,
an also an example of how to reuse traditional STL containers
in the new style (Vector).

test\diff.cpp is a simple utility which compares two ascii files and
prints the line number of the first line on which they differ. There is
no output if the files are identical.

CONNECTING TO AN UML TOOL
-------------------------
When calling codegen with option '-uml', it generates two files:
   layout.inp ...  file from which the layout tool can generate the UML diagram
                   - it contains both inheritance records and an expanded
                   copy of the DataStructure statements.

WARNING:
The code generator sometimes generates file umlFile.xmi which, hopefully,
will connect this library to other UML tools such as Poseidon. At the moment,
this files is not usable yet - it is incomplete and  may contain errors.

                     Jiri Soukup              April 8, 2005
