del gen.*
..\incode\alib\codegen ds.def ..\incode\alib\lib gen
cl layout.cpp  display.cpp
copy layout.exe ..\bin
del layout.exe
