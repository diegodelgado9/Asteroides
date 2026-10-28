#include "vector2d.h"
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

// Constructor por defecto
Vector2D::Vector2D() : x(0), y(0) {}

// Constructor con coordenadas cartesianas
Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

// Constructor con módulo y ángulo
Vector2D::Vector2D(double modulo, double angulo, Vector2D::Uds tipo_angulo)
{
    if (tipo_angulo == Vector2D::Uds::Grados)
    {
        angulo = angulo * M_PI / 180.0; // Convertir grados a radianes
    }
    x = modulo * cos(angulo);
    y = modulo * sin(angulo);
}

// Métodos de acceso
double Vector2D::getX() const { return x; }
double Vector2D::getY() const { return y; }
double Vector2D::getModulo() const { return sqrt(x * x + y * y); }
double Vector2D::getAnguloRadianes() const { return atan2(y, x); }
double Vector2D::getAnguloGrados() const { return getAnguloRadianes() * 180.0 / M_PI; }

// Métodos de modificación
void Vector2D::setX(double x) { this->x = x; }
void Vector2D::setY(double y) { this->y = y; }
void Vector2D::setModulo(double modulo)
{
    double angulo = getAnguloRadianes();
    x = modulo * cos(angulo);
    y = modulo * sin(angulo);
}
void Vector2D::setAnguloRadianes(double angulo)
{
    double modulo = getModulo();
    x = modulo * cos(angulo);
    y = modulo * sin(angulo);
}
void Vector2D::setAnguloGrados(double angulo)
{
    setAnguloRadianes(angulo * M_PI / 180.0);
}

// Método estático para crear un vector desde módulo y ángulo
Vector2D Vector2D::desdeModuloYAngulo(double modulo, double angulo, Vector2D::Uds unidades)
{
    if (unidades == Vector2D::Uds::Grados)
    {
        angulo = angulo * M_PI / 180.0; // Convertir grados a radianes
    }
    return Vector2D(modulo * cos(angulo), modulo * sin(angulo));
}

// Operaciones con vectores
Vector2D Vector2D::sumar(const Vector2D &v) const
{
    return Vector2D(x + v.x, y + v.y);
}
Vector2D Vector2D::restar(const Vector2D &v) const
{
    return Vector2D(x - v.x, y - v.y);
}
Vector2D Vector2D::multiplicar(double escalar) const
{
    return Vector2D(x * escalar, y * escalar);
}

// Representación en cadena
std::string Vector2D::to_string(int fmt) const
{
    std::string str;
    if (fmt & FMTCARTESIANAS)
    {
        str += "(" + std::to_string(x) + "," + std::to_string(y) + ")";
    }
    if (fmt & FMTPOLARESG)
    {
        str += " [" + std::to_string(getModulo()) + " @ " + std::to_string(getAnguloGrados()) + "°]";
    }
    if (fmt & FMTPOLARESR)
    {
        str += " [" + std::to_string(getModulo()) + " @ " + std::to_string(getAnguloRadianes()) + " rad]";
    }
    return str;
}

// Funciones globales
Vector2D sumar(const Vector2D &v1, const Vector2D &v2)
{
    return v1.sumar(v2);
}
Vector2D restar(const Vector2D &v1, const Vector2D &v2)
{
    return v1.restar(v2);
}
Vector2D multiplicar(const Vector2D &v, double escalar)
{
    return v.multiplicar(escalar);
}
Vector2D multiplicar(double escalar, const Vector2D &v)
{
    return v.multiplicar(escalar);
}
double multiplicar(const Vector2D &v1, const Vector2D &v2)
{
    return v1.getX() * v2.getX() + v1.getY() * v2.getY();
}

Vector2D operator+(const Vector2D &a, const Vector2D &b)
{
    return Vector2D(a.getX() + b.getX(), a.getY() + b.getY());
}

Vector2D operator-(const Vector2D &a, const Vector2D &b)
{
    return Vector2D(a.getX() - b.getX(), a.getY() - b.getY());
}

double operator*(const Vector2D &a, const Vector2D &b)
{
    return a.getX() * b.getX() + a.getY() * b.getY();
}

Vector2D operator*(const Vector2D &v, double escalar)
{
    return Vector2D(v.getX() * escalar, v.getY() * escalar);
}

Vector2D operator*(double escalar, const Vector2D &v)
{
    return Vector2D(v.getX() * escalar, v.getY() * escalar);
}

Vector2D operator/(const Vector2D &v, double escalar)
{
    return Vector2D(v.getX() / escalar, v.getY() / escalar);
}

ostream &operator<<(ostream &os, const Vector2D &v)
{
    os << "(" << v.getX() << "," << v.getY() << ")";
    return os;
}

istream &operator>>(istream &is, Vector2D &v)
{
    char par1, coma, par2;
    double x, y;
    is >> par1 >> x >> coma >> y >> par2;
    if (par1 == '(' && coma == ',' && par2 == ')')
    {
        v.setX(x);
        v.setY(y);
    }
    else
    {
        is.setstate(std::ios::failbit);
    }
    return is;
}

double Vector2D::mod() const
{
    return std::sqrt(getX() * getX() + getY() * getY());
}
