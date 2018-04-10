#include <iostream>
#include <fstream>
using namespace std;

class Postscript {
private:
    ofstream ps;

    float rs, gs, bs;
    float rf, gf, bf;
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

    void line(float a, float b, float c, float d){
        ps << a << " " << b << " moveto " << c << " " << d << " lineto stroke\n";
    }

    void drawRect(float a, float b, float c, float d){
        ps << a << " " << b << " moveto " << a+c << " " << b << " lineto " << a+c << " " << b+d << " lineto " << a << " " << b+d << " lineto closepath\n" << rs << " " << gs << " " << bs << " setrgbcolor\n" << "stroke\n";
    }

    void fillRect(float a, float b, float c, float d){
        ps << a << " " << b << " moveto " << a+c << " " << b << " lineto " << a+c << " " << b+d << " lineto " << a << " " << b+d << " lineto closepath\n" << rf << " " << gf << " " << bf << " setrgbcolor\n" << "fill\n";
    }

    void setFillColor(float r, float g, float b){
        rf = r/255.0;
        gf = g/255.0;
        bf = b/255.0;
    }

    void setStrokeColor(float r, float g, float b){
        rs = r/255.0;
        gs = g/255.0;
        bs = b/255.0;
    }

    void drawTriangle(float a, float b, float c, float d, float e, float f){
        ps << a << " " << b << " moveto " << c << " " << d << " lineto " << e << " " << f << " lineto closepath\n" << rs << " " << gs << " " << bs << " setrgbcolor\n" << "stroke\n";
    }

    void fillTriangle(float a, float b, float c, float d, float e, float f){
        ps << a << " " << b << " moveto " << c << " " << d << " lineto " << e << " " << f << " lineto closepath\n" << rf << " " << gf << " " << bf << " setrgbcolor\n" << "fill\n";
    }

    void grid(float a, float b, float c, float d, float e, float f){
        ps << "/vline {" << a << " " << d << " moveto " << a << " " << f << " lineto stroke} def\n" << "gasave\n" << "vline\n";
        ps << (c-a)/b << " {" << b << " 0 translate vline} repeat\n" << "grestore\n";
        ps << "/hline {" << a << " " << d << " moveto " << c << " " << d << " lineto stroke} def\n" << "gasave\n" << "vline\n";
        ps << (f-d)/e << " {" << 0 << " e translate hline} repeat\n" << "grestore\n";
    }
    void drawCircle(float x, float y, float r){
        ps<<x<<" "<<y<<" "<<r<<" "<<"0 360 arc \n"<<rs<<" "<<gs<<" "<<bs<<" "<<"setrgbcolor \n"<<"stroke \n";
    }
    void fillCircle(float x, float y, float r){
        ps<<x<<" "<<y<<" "<<r<<" "<<"0 360 arc \n"<<rf<<" "<<gf<<" "<<bf<<" "<<"setrgbcolor \n"<<"fill \n";
    }
    void text(float x, float y, const char* str){
        ps<<"/Times-Roman findfont 12 scalefont setfont newpath"<<x<<" "<<y<<" "<<"moveto"<<"("<<str<<")"<<rs<<" "<<gs<<" "<<bs<<" "<<"setrgbcolor \n"<<"show \n";
    }
};

int main() {
    Postscript p("test.ps");

    p.line(0,0, 300,400);  // 0 0 moveto 300 400 lineto stroke
    int r = 50, g = 255, b = 50;
    p.drawRect(0, 0, 150, 150);   // x y moveto x+w y lineto x+w y+h lineto ... closepath stroke
    p.fillRect(20, 20, 50, 50);   // x y moveto x+w y lineto x+w y+h lineto ... closepath fill
    p.setFillColor(r, g, b); // 1.0 0.5 0 setrgbcolor
    p.setStrokeColor(255, 50, 50);
    p.drawTriangle(50, 50, 100, 100, 50, 30);
    p.fillTriangle(100, 100, 150, 150, 50, 10);
    p.drawCircle(150,100,50); // x y 0 360 r arc stroke
    p.text(80, 80, "Welcome, to my beloved city"); // look it up  setfont  (ABC) show

    p.grid(300, 50, 500, 400, 50, 700);
}
