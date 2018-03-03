call clean
..\..\codegen ds.def ..\..\lib gen
cl array_4.cpp
array_4 > array_4.res
..\diff array_4.res array_4.out
