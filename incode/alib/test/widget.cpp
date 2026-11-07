#include <vector>
#include <iostream.h>
using namespace std;

class Widget {
    int val;
public:
    Widget(){}
    Widget(int i = 0){val=i;}
    void prt(){cout << val <<"\n";}
};

class Holder {
public:
    vector<Widget> wVect;
};

int main(){
    vector<Widget>::iterator it;
    Holder* hp=new Holder;

    for (int j = 0; j < 10; ++j) {	// insert some Widgets
        hp->wVect.push_back(Widget(j));
    }

    for(it=hp->wVect.begin(); it!=hp->wVect.end(); ++it){
        it->prt();
    }
    return 0;
}

