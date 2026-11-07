del gen.*
c:\incode\alib\codegen -uml ds.def c:\incode\alib\lib gen srcList layout
cl layout.cpp display.cpp
copy layout.exe ..\bin
del layout.exe
