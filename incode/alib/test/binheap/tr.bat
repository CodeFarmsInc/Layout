call clean
..\..\codegen ds.def ..\..\lib gen
cl binheap.cpp
binheap binheap.inp binheap.res
..\diff binheap.res binheap.out
