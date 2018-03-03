call clean
dir ring2.cpp > srcList
..\..\codegen -uml ds.def ..\..\lib gen srcList umlFile
cl ring2.cpp
ring2 > ring2.res
..\diff ring2.res ring2.out
