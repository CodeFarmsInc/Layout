call clean
..\..\codegen -dol ds.def ..\..\lib gen
cl array_2.cpp
array_2 array_2.inp array_2.res
..\diff array_2.res array_2.out
