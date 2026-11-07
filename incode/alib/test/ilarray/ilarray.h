
// ------------------------------------------------------
// This is a test IndexedLinkArray class, simple and testing
// only the functions where the 'index' is involved. All other
// functions are inherited from LinkedArray and possibly Array,
// and have been tested for those classes.
// ------------------------------------------------------

#include <stdio.h>
#include <string.h>

class Department {
public:
    ZZ_Department ZZds;
    void prt(char *label);
};
class Employee {
public:
    ZZ_Employee ZZds;
    static int cmp(void const *c1,void const *c2);
    Employee();
};

