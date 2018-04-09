#include <iostream>
#include <fstream>
using namespace std;

class Postscript {
private:
    ofstream ps;
    int rs, gs, bs;
    int rf, gf, bf;
    char fillColor[64];

public:
    Postscript(const char *str) {
        ps.open(str);
        rs = 0;
        gs = 0;
        bs = 0;
        rf = 0;
        gf = 0;
        bf = 0;
    }

    ~Postscript() {
        ps.close();
    }

    void line(int a, int b, int c, int d){
        ps << a << " " << b << " moveto " << c << " " << d << " lineto stroke\n";
    }

    void drawRect(int a, int b, int c, int d){
        ps << a << " " << b << " moveto " << a+c << " " << b << " lineto " << a+c << " " << b+d << " lineto " << a << " " << b+d << " lineto closepath\n" << rs << " " << gs << " " << bs << " setrgbcolor\n" << "stroke\n";
    }

    void fillRect(int a, int b, int c, int d){
        ps << a << " " << b << " moveto " << a+c << " " << b << " lineto " << a+c << " " << b+d << " lineto " << a << " " << b+d << " lineto closepath\n" << rf << " " << gf << " " << bf << " setrgbcolor\n" << "fill\n";
    }

    void setFillColor(int r, int g, int b){
        rf = r;
        gf = g;
        bf = b;
    }

    void setStrokeColor(int r, int g, int b){
        rs = r;
        gs = g;
        bs = b;
    }

    void drawTriangle(int a, int b, int c, int d, int e, int f){
        ps << a << " " << b << " moveto " << c << " " << d << " lineto " << e << " " << f << " lineto closepath\n" << rs << " " << gs << " " << bs << " setrgbcolor\n" << "stroke\n";
    }

    void fillTriangle(int a, int b, int c, int d, int e, int f){
        ps << a << " " << b << " moveto " << c << " " << d << " lineto " << e << " " << f << " lineto closepath\n" << rf << " " << gf << " " << bf << " setrgbcolor\n" << "fill\n";
    }
};

int main() {
    Postscript p("/Users/nines/CLionProjects/postscript/text.cpp");

    p.line(0,0, 300,400);  // 0 0 moveto 300 400 lineto stroke
    int r = 50, g = 255, b = 50;
    p.drawRect(0, 0, 150, 150);   // x y moveto x+w y lineto x+w y+h lineto ... closepath stroke
    p.fillRect(20, 20, 50, 50);   // x y moveto x+w y lineto x+w y+h lineto ... closepath fill
    p.setFillColor(r, g, b); // 1.0 0.5 0 setrgbcolor
    p.setStrokeColor(255, 50, 50);
    p.drawTriangle(50, 50, 100, 100, 50, 30);
    p.fillTriangle(100, 100, 150, 150, 50, 10);
    //p.drawCircle(150,100,50); // x y 0 360 r arc stroke
    //p.text(80, 80, "Welcome, to my beloved city"); // look it up  setfont  (ABC) show

    //p.grid(300, 50, 500, 400, 50, 700);
}