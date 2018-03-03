call clean
..\..\codegen ds.def ..\..\lib gen
cl ilarray.cpp
ilarray  > ilarray.res
..\diff ilarray.res ilarray.out
