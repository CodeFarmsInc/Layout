del inh.des
dir testComp.h > srcList
..\codegen -uml testComp.h ..\lib res srcList umlFile
diff inh.def testComp.out
