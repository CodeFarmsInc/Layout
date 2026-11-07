call clean
..\..\codegen ds.def ..\..\lib gen
cl hash.cpp
hash > hash.res
..\diff hash.res hash.out
