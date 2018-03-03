call clean
..\..\codegen ds.def ..\..\lib gen
cl -GX vector.cpp
vector > vector.res
..\diff vector.res vector.out
