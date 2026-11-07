call clean
..\..\codegen ds.def ..\..\lib gen
cl testABC.cpp testB.cpp
testABC > abc.res
..\diff abc.res abc.out
