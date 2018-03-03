call clean
..\..\codegen ds.def ..\..\lib gen
cl stack.cpp
stack stack.inp stack.res
..\diff stack.res stack.out
