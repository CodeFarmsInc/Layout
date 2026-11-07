call clean
..\..\codegen ds.def ..\..\lib gen
cl /EHsc ring2.cpp
ring2 > ring2.res
..\diff ring2.res ring2.out
