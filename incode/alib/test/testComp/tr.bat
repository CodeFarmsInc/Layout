call clean
dir testComp.h > srcList
..\..\codegen -uml ds.def ..\..\lib gen srcList umlFile
copy layout.inp testComp.res
..\diff testComp.res testComp.out
