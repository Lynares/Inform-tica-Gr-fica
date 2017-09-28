#ifndef JERARQUICO_H
#define JERARQUICO_H

#include "objeto.h"
#include "objetoR.h"

class Jerarquico{
    private:
        Objeto cubo;
        ObjetoR cilindro;
        Objeto perfilU1;
        Objeto perfilU2;
        Objeto beethoven;

        bool activo;
        int modo;

        float desplazamiento;
        int giro;
        int elevacion;
        float velDesplazamiento;
        int velGiro;
        int velElevacion;

        void rail();
        void railes();
        void base();
        void cuerpo();
        void brazo();
        void cable();
        void mercancia();
        void eje();
        void cableMercancia();
        void brazoCableMercancia();
        void cuerpoBrazoCableMercancia();
        void baseCuerpoBrazoCableMercancia();
        void grua();

    public:
        Jerarquico();
        ~Jerarquico(){}

        void avanzar();
        void retroceder();
        void girarI();
        void girarD();
        void elevar();
        void bajar();
        void cambiarModo(int m);
        void incrementarVelAvance();
        void decrementarVelAvance();
        void incrementarVelGiro();
        void decrementarVelGiro();
        void incrementarVelElevacion();
        void decrementarVelElevacion();
        void cambiarModo();

        void activar(){ if(activo) activo = false; else activo = true; }
        void draw();
};

#endif
