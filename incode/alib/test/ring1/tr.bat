call clean
..\..\codegen ds.def ..\..\lib gen
cl ring1.cpp
ring1 > ring1.res
..\diff ring1.res ring1.out
