// These classes correspond to Fig.5.2. The inheritance is coded with variations
// of format for the purpose of testing, including keywords 'public' and 'private'.
// Also, for the purpose of testing multiple inheritance, class Document has been added. 

class Graphics {
    int x1,y1,x2,y2;
protected:
    void foo(){}
public:
    ZZ_Graphics ZZds;
};

class Editable {
public:
    ZZ_Editable ZZds;
};

class Picture : Graphics , Editable {
    char *name;
    int x,y,orient;
public:
    ZZ_Picture ZZds;
    void myFoo(){Graphics::foo();}
};

class Line	:	Graphics	{
public:
    ZZ_Line ZZds;  // test of : in a comment
};

class Text :       /* inheritance statement split over several lines */
 Editable, Graphics{
	char *text;
public:
    ZZ_Text ZZds;
};

class Rectangle: private /* comment in the middle */ Graphics {
public:
    ZZ_Rectangle ZZds;
};

/* test of C-style comment over several lines
class Dummy : public Rectangle {
public:
    ZZ_Dummy ZZds;
};
 eliminate Dummy */

class NoInheritanceClass {
    ZZ_NoInheritanceClass ZZds;
);
