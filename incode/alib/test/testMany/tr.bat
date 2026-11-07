call clean
dir testmany.cpp > srcList
..\..\codegen -uml ds.def ..\..\lib gen srcList umlFile
cl testmany.cpp
testmany > testmany.res
..\diff testmany.res testmany.out
