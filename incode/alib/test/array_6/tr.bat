call clean
..\..\codegen ds.def ..\..\lib gen
cl array_6.cpp 
array_6 > array_6.res
..\diff array_6.res array_6.out
