call clean
..\..\codegen -dol ds.def ..\..\lib gen
cl array_5.cpp
array_5 > array_5.res
..\diff array_5.res array_5.out
