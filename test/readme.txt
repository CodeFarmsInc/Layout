This directory contains numerous test problems
----------------------------------------------
In order to run a test producing an svg file, use ss.bat.
For example type
   ss inp0
and the result will be in the file display.svg.

In order to run a test producing a Java display, use jj.bat.
For example type
   jj inp0
and the run will will create a window with the diagram. 

All test input files in this directory have names starting with 'inp'.
This is for convenience, the input file can have any name.
Note that some examples are quite tough and complex.

As explained, the Layout program is still in the expiremental stage.
Most examples, especially the Java-display version, give excelent diagrams,
but there are still a few where the diagram is less pleasing.
 The problem with occassional crashing has been completely removed in Ver.2.3.

The current status as of June 18, 2016 is as follows.
Except for display of ManyToMany relations, these are just minor esthetic
problems that happen only for complex, crowded diagrams.

input               svg               Java
==============================================================
inpO                OK                OK
inp1                OK                OK
inp2                (4)               OK
inp4                OK                OK 
inp7                OK                OK
inp8                OK                OK
inp9                (1)(4)            (4)
inp10               (4)               OK
inp11               (1)               OK
inp12               OK                OK
inp13               (3)               (3)
inp14               (3)               (3)
inp15               (1)(4)            OK
inp16               OK                (2)
inp17               (4)               OK
inp18               (4)               (4)
inp19               OK                OK
inp20               (4)               OK
inp21               OK                OK
inp22               OK                OK
inpBook             OK                OK
inpJCU              OK                OK
inpLayOld1          OK                OK
inpLayOld2          (4)               OK
inpLayout           (4)               OK
inpBench            OK                OK
inpBench3           OK                OK
inpMN               (3)               (3)

General problem: When calling the layout.exe with a non-existing file
                 name, it crashes instead of a graceful exit.
=====================================================================
(1) labels overflow boxes
(2) incomplete drawing of multiple ineritance
(3) MtoN relation not drawn correctly
(4) some labels overlap

NOTE: If the Java display does not show the bottom of the picture, the problem 
is the incorrect setting of the screslbn size in file param.txt.
