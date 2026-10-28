#ifndef PARTICULA_H
#define PARTICULA_H

#include "vector2d.h"
#include "bigs.h"
#include "bigs_image.h"

class Particula
{
private:
    double px, py;
    double vx, vy;
    double ax, ay;
    double radio_;
    double densidad_;
    Vector2D direccion_;
    BiGS::Color color_;
    int tipo_;
    bool difunta_;
    double tiempoDisparo_;
    static BiGS::Image naveImg;
    static BiGS::Image asteroideImg;
    static BiGS::Image disparoImg;

public:
    Particula();
    Particula(double p[2], double v[2]);
    Particula(const Vector2D &p, const Vector2D &v, const Vector2D &a);

    static bool cargarImagenes();
    static void liberarImagenes();

    void posicion(double p[2]) const;
    Vector2D posicion() const;
    void posicion(double p[2]);
    void posicion(double x, double y);

    void velocidad(double v[2]) const;
    void velocidad(double v[2]);
    void velocidad(double m, double a);
    Vector2D velocidad() const;
    void velocidad(const Vector2D &v);

    void aceleracion(double a[2]);
    void aceleracion(double m, double a);
    Vector2D aceleracion() const;

    void vmod(double m);
    void vang(double a);

    void avanzaMRU(double dt);
    void avanzaMUA(double dt);

    void radio(double r);
    double radio() const;
    void densidad(double d);
    double densidad() const;
    double masa() const;

    Vector2D direccion() const;
    void direccion(double ang);
    void girar(double ang);

    void tipo(int t);
    int tipo() const;
    void color(BiGS::Color c);

    void dibujar(bool dibujarVectores = false);

    void marcarDifunta(bool d = true);
    bool esDifunta() const;

    void tiempoDisparo(double t);
    double tiempoDisparo() const;

    std::string to_string() const;

    friend void corrigeChoque(Particula &a1, Particula &a2);
};

#endif