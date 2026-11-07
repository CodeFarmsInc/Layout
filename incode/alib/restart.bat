copy js.h gen.h
copy js.cpp gen.cpp
del tmp\*.cpp
del tmp\*.h
copy tmpStart\*.* tmp
cl codegen.cpp substitu.cpp
