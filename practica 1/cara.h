#ifndef CARA_H
#define CARA_H

class Cara{
    public:
        int a;
        int b;
        int c;

        Cara(){}
        Cara(int a1, int b1, int c1){ a = a1; b= b1; c = c1;}
        ~Cara(){}
        Cara(const Cara &cara) { a = cara.a; b = cara.b; c = cara.c; }
};

#endif

