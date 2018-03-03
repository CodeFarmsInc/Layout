call clean
..\..\codegen -dol ds.def ..\..\lib gen
cl lnkarray.cpp
lnkarray lnkarray.inp lnkarray.res
..\diff lnkarray.res lnkarray.out
