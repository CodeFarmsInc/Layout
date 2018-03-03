call clean
..\..\codegen -dol ds.def ..\..\lib gen
cl array_1.cpp 
array_1 array_1.inp array_1.res
..\diff array_1.res array_1.out
