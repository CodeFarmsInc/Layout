#include <stdio.h>

// Only some classes in this library have ++ or -- operators,
// This style of traversal is left in the library for historical
// reasons, mostly because codegen uses it internally.

#define ITERATE(IT,X) for(X= ++IT; X; X= ++IT)
#define RETRACE(IT,X) for(X= --IT; X; X= --IT)

// We recommended you to use the 'from' and 'next' methods
// when traversing the data. It is more direct, and the interface is
// the same in voth C++ and in Java:

//    id_Iterator it;
//    for(c=it.fromHead(p); !c; c=it.next()){...}

// On the other hand, if you like the ITERATE and RETRACE macros
// and/or the use of operators ++ and --, it is easy to code
// these operators using the existing functions such as fromHead() and next().
// For an example of how to do that, look at the code of the iterator
// in aggreg2.h and aggreg2.cpp in this directory.
