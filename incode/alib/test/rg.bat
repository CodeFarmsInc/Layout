del *.exe
del *.res
cl diff.cpp
REM ---------------------------------
del abc.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen testABC.h ..\lib gen
cl testABC.cpp testB.cpp
testABC > abc.res
diff abc.res abc.out
REM ---------------------------------
del ring1.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen ring1.cpp ..\lib gen
cl ring1.cpp
ring1 > ring1.res
diff ring1.res ring1.out
REM ---------------------------------
del ring2.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen ring2.cpp ..\lib gen
cl ring2.cpp
ring2 > ring2.res
diff ring2.res ring2.out
REM ---------------------------------
del array_1.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen -dol array_1.cpp ..\lib gen
cl array_1.cpp 
array_1 array_1.inp array_1.res
diff array_1.res array_1.out
REM ---------------------------------
del array_2.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen -dol array_2.cpp ..\lib gen
cl array_2.cpp
array_2 array_2.inp array_2.res
diff array_2.res array_2.out
REM ---------------------------------
del stack.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen stack.cpp ..\lib gen
cl stack.cpp
stack stack.inp stack.res
diff stack.res stack.out
REM ---------------------------------
del binheap.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen binheap.cpp ..\lib gen
cl binheap.cpp
binheap binheap.inp binheap.res
diff binheap.res binheap.out
REM ---------------------------------
del array_3.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen -dol array_3.cpp ..\lib gen
cl array_3.cpp
array_3 > array_3.res
diff array_3.res array_3.out
REM ---------------------------------
del array_4.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen array_4.cpp ..\lib gen
cl array_4.cpp
array_4 > array_4.res
diff array_4.res array_4.out
REM ---------------------------------
del array_5.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen -dol array_5.cpp ..\lib gen
cl array_5.cpp
array_5 > array_5.res
diff array_5.res array_5.out
REM ---------------------------------
del hash.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen hash.cpp ..\lib gen
cl hash.cpp
hash > hash.res
diff hash.res hash.out
REM ---------------------------------
del vector.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen vector.cpp ..\lib gen
cl -GX vector.cpp
vector > vector.res
diff vector.res vector.out
REM ---------------------------------
del inh.des
dir testComp.h > srcList
..\codegen -uml testComp.h ..\lib gen srcList umlFile
copy layout.inp testComp.res
diff testComp.res testComp.out
REM ---------------------------------
del array_6.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen array_6.cpp ..\lib gen
cl array_6.cpp 
array_6 > array_6.res
diff array_6.res array_6.out
REM ---------------------------------
del array_7.res
del gen.*
del tmp\*.cpp
del tmp\*.h
..\codegen array_7.cpp ..\lib gen
cl array_7.cpp 
array_7 > array_7.res
diff array_7.res array_7.out
REM ---------------------------------
del testmany.res
del gen.*
del tmp\*.cpp
del tmp\*.h
dir testmany.cpp > srcList
..\codegen -uml testmany.cpp ..\lib gen srcList umlFile
cl testmany.cpp
testmany > testmany.res
diff testmany.res testmany.out
REM ---------------------------------
