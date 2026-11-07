    #include "gen.h"
    class Company {
    public:
        ZZ_Company ZZds;
    };

    class Warehouse {
    public:
        ZZ_Warehouse ZZds;
    };

    class PartType {
        int ID;
        int count;
    public:
        ZZ_PartType ZZds;
        int getID(){return ID;}
    };

    class Supplier {
    public:
        ZZ_Supplier ZZds;
    };

    class Assembly : public PartType {
    public:
        ZZ_Assembly ZZds;
    };
    class Product : public Assembly {
    public:
        ZZ_Product ZZds;
    };

    Association Bag<Assembly,PartType> assemble;
    Association LinkedList1<Company,Supplier> suppliers;
    Association Aggregate2<Supplier,PartType> supply;
    Association Hash<Company,PartType> partHash;
    Association LinkedList1<Company,Warehouse> warehouses;
    Association LinkedList1<Company,Product> products;
    Association Aggregate2<Warehouse,PartType> stored;
    Association Name<Product> prodName;
    // Association Uni1toX<Product,PartType> needed; // eliminated 

    int partHash::cmp(PartType *pt1,PartType *pt2){
        return pt1->getID() - pt2->getID();
    }

    int partHash::hash(PartType *pt,int hashSz){
        return hashInt(pt->getID(),hashSz);
    }

    int main(){
        // objects themselves
        int res=sizeof(Company) + 3*sizeof(Warehouse) + 60*sizeof(Product)
                                                + 7500*sizeof(PartType);
        // Uni1toX keeps an array of pointer links (each link 4B).
        // This array may re-allocate itself with 3x bigger size when
        // the current size is not sufficient. This means that Uni1toX
        // needs on average 8B per link.

        res=res + 7500*8 + 60*800*8;
        printf("total=%d bytes\n",res);
        return 0;
    };
    #include "gen.cpp"
