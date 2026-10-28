#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <string>
#include <cmath> // Para funciones matemáticas como sin, cos, etc.

#define FMTCARTESIANAS 1
#define FMTPOLARESG 2
#define FMTPOLARESR 4

class Vector2D
{
private:
    double x;
    double y;

public:
    enum class Uds
    {
        Grados,
        Radianes
    };

    Vector2D();
    Vector2D(double x, double y);
    Vector2D(double modulo, double angulo, Uds tipo_angulo);

    // Métodos de acceso
    double getX() const;
    double getY() const;
    double getModulo() const;
    double getAnguloRadianes() const;
    double getAnguloGrados() const;

    // Métodos de modificación
    void setX(double x);
    void setY(double y);
    void setModulo(double modulo);
    void setAnguloRadianes(double angulo);
    void setAnguloGrados(double angulo);
    double mod() const;

    // Operaciones vectoriales
    Vector2D sumar(const Vector2D &v) const;
    Vector2D restar(const Vector2D &v) const;
    Vector2D multiplicar(double escalar) const;
    std::string to_string(int fmt = FMTCARTESIANAS | FMTPOLARESG) const;

    static Vector2D desdeModuloYAngulo(double modulo, double angulo, Uds unidades);
};

// Funciones auxiliares
Vector2D sumar(const Vector2D &v1, const Vector2D &v2);
Vector2D restar(const Vector2D &v1, const Vector2D &v2);
Vector2D multiplicar(const Vector2D &v, double escalar);
Vector2D multiplicar(double escalar, const Vector2D &v);
double multiplicar(const Vector2D &v1, const Vector2D &v2);

// Operadores externos (fuera de la clase)
Vector2D operator+(const Vector2D &a, const Vector2D &b);
Vector2D operator-(const Vector2D &a, const Vector2D &b);
double operator*(const Vector2D &a, const Vector2D &b); // producto escalar
Vector2D operator*(const Vector2D &v, double escalar);
Vector2D operator*(double escalar, const Vector2D &v);
Vector2D operator/(const Vector2D &v, double escalar);

// Entrada y salida
std::ostream &operator<<(std::ostream &os, const Vector2D &v);
std::istream &operator>>(std::istream &is, Vector2D &v);

#endif // VECTOR2D_H
