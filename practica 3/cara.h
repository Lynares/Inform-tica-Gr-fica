#ifndef CARA_H
#define CARA_H

class Cara{
    public:
        int a;
        int b;
        int c;

        Cara(){}
        ~Cara(){}
        Cara(const Cara &cara) { a = cara.a; b = cara.b; c = cara.c; }
        Cara &operator=(const Cara &cara);
};

#endif

