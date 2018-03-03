del array_7.res
del gen.*
del tmp\*.cpp
del tmp\*.h
del *.obj
del *.exe
..\..\codegen ds.def ..\..\lib gen
cl array_7.cpp 
array_7 > array_7.res
..\diff array_7.res array_7.out
