call clean
..\..\codegen -dol ds.def ..\..\lib gen
cl array_3.cpp
array_3 > array_3.res
..\diff array_3.res array_3.out
