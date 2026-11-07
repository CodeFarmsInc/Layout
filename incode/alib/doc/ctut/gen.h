#ifndef ZZ_CODEGEN_INCLUDE
#define ZZ_CODEGEN_INCLUDE

#include "d:\revol\cd\alib\lib/general.h"

class Assembly;
class PartType;
class Company;
class Supplier;
class Warehouse;
class Product;

#include "tmp/assemble.h"
#include "tmp/assemble1.h"
#include "tmp/suppliers.h"
#include "tmp/suppliers1.h"
#include "tmp/supply.h"
#include "tmp/supply1.h"
#include "tmp/supply2.h"
#include "tmp/partHash.h"
#include "tmp/partHash1.h"
#include "tmp/warehouses.h"
#include "tmp/warehouses1.h"
#include "tmp/products.h"
#include "tmp/products1.h"
#include "tmp/stored.h"
#include "tmp/stored1.h"
#include "tmp/stored2.h"
#include "tmp/prodName.h"

// -----------------------------------------------
typedef class assemble_Bag assemble;
typedef class suppliers_LinkedList1 suppliers;
typedef class supply_Aggregate2 supply;
typedef class partHash_Hash partHash;
typedef class warehouses_LinkedList1 warehouses;
typedef class products_LinkedList1 products;
typedef class stored_Aggregate2 stored;
typedef class prodName_Name prodName;
// -----------------------------------------------


class ZZ_Assembly {
public:
    assemble_BagHolder ZZassemble;
};

class ZZ_PartType {
public:
    supply_Aggregate2Child ZZsupply;
    partHash_HashElement ZZpartHash;
    stored_Aggregate2Child ZZstored;
};

class ZZ_Company {
public:
    suppliers_LinkedList1Parent ZZsuppliers;
    partHash_HashHolder ZZpartHash;
    warehouses_LinkedList1Parent ZZwarehouses;
    products_LinkedList1Parent ZZproducts;
};

class ZZ_Supplier {
public:
    suppliers_LinkedList1Child ZZsuppliers;
    supply_Aggregate2Parent ZZsupply;
};

class ZZ_Warehouse {
public:
    warehouses_LinkedList1Child ZZwarehouses;
    stored_Aggregate2Parent ZZstored;
};

class ZZ_Product {
public:
    products_LinkedList1Child ZZproducts;
    prodName_NameParent ZZprodName;
};

typedef assemble_BagIterator assemble_Iterator;
typedef suppliers_LinkedList1Iterator suppliers_Iterator;
typedef supply_Aggregate2Iterator supply_Iterator;
typedef partHash_HashIterator partHash_Iterator;
typedef warehouses_LinkedList1Iterator warehouses_Iterator;
typedef products_LinkedList1Iterator products_Iterator;
typedef stored_Aggregate2Iterator stored_Iterator;

#endif // ZZ_CODEGEN_INCLUDE
