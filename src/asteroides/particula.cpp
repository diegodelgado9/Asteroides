#include "particula.h"
#include <cmath>
#include <string>

// Definición e inicialización de miembros estáticos para las imágenes
BiGS::Image Particula::naveImg;
BiGS::Image Particula::asteroideImg;
BiGS::Image Particula::disparoImg;

// Constructor por defecto: inicializa todos los atributos a valores predeterminados
Particula::Particula()
    : px(0), py(0), vx(0), vy(0), ax(0), ay(0), radio_(0), densidad_(0),
      direccion_(Vector2D(1, 0)), color_(BiGS::CWhite), tipo_(0), difunta_(false), tiempoDisparo_(0) {}

// Constructor con posición y velocidad como arreglos
Particula::Particula(double p[2], double v[2])
    : px(p[0]), py(p[1]), vx(v[0]), vy(v[1]), ax(0), ay(0), radio_(0), densidad_(0),
      direccion_(Vector2D(1, 0)), color_(BiGS::CWhite), tipo_(0), difunta_(false), tiempoDisparo_(0) {}

// Constructor con posición, velocidad y aceleración como vectores
Particula::Particula(const Vector2D &p, const Vector2D &v, const Vector2D &a)
    : px(p.getX()), py(p.getY()), vx(v.getX()), vy(v.getY()), ax(a.getX()), ay(a.getY()),
      radio_(0), densidad_(0), direccion_(Vector2D(1, 0)), color_(BiGS::CWhite), tipo_(0), difunta_(false), tiempoDisparo_(0) {}

// Carga las imágenes de la nave y los asteroides
bool Particula::cargarImagenes()
{
    bool exito = true;
    if (naveImg.empty())
    {
        exito &= naveImg.load("./data/nave.bmp"); // Carga la imagen de la nave
    }
    if (asteroideImg.empty())
    {
        exito &= asteroideImg.load("./data/asteroides.bmp"); // Carga la imagen de los asteroides
    }
    return exito; // Devuelve true si todas las imágenes se cargaron correctamente
} 

// Libera las imágenes de la memoria
void Particula::liberarImagenes()
{
    if (!naveImg.empty())
    {
        naveImg = BiGS::Image(); // Libera la imagen de la nave
    }
    if (!asteroideImg.empty())
    {
        asteroideImg = BiGS::Image(); // Libera la imagen de los asteroides
    }
    if (!disparoImg.empty())
    {
        disparoImg = BiGS::Image(); // Libera la imagen de los disparos
    }
}

// Obtiene la posición como un arreglo
void Particula::posicion(double p[2]) const
{
    p[0] = px;
    p[1] = py;
}

// Obtiene la posición como un vector
Vector2D Particula::posicion() const
{
    return Vector2D(px, py);
}

// Establece la posición desde un arreglo
void Particula::posicion(double p[2])
{
    px = p[0];
    py = p[1];
}

// Establece la posición desde coordenadas x e y
void Particula::posicion(double x, double y)
{
    px = x;
    py = y;
}

// Obtiene la velocidad como un arreglo
void Particula::velocidad(double v[2]) const
{
    v[0] = vx;
    v[1] = vy;
}

// Establece la velocidad desde un arreglo
void Particula::velocidad(double v[2])
{
    vx = v[0];
    vy = v[1];
}

// Establece la velocidad desde módulo y ángulo (en grados)
void Particula::velocidad(double m, double a)
{
    double rad = a * M_PI / 180.0; // Convierte grados a radianes
    vx = m * cos(rad);
    vy = m * sin(rad);
}

// Modifica el módulo de la velocidad manteniendo el ángulo
void Particula::vmod(double m)
{
    double ang = atan2(vy, vx); // Calcula el ángulo actual
    vx = m * cos(ang);
    vy = m * sin(ang);
}

// Modifica el ángulo de la velocidad manteniendo el módulo
void Particula::vang(double a)
{
    double m = sqrt(vx * vx + vy * vy); // Calcula el módulo actual
    double rad = a * M_PI / 180.0;      // Convierte grados a radianes
    vx = m * cos(rad);
    vy = m * sin(rad);
}

// Establece la aceleración desde módulo y ángulo (en grados)
void Particula::aceleracion(double m, double a)
{
    double rad = a * M_PI / 180.0; // Convierte grados a radianes
    ax = m * cos(rad);
    ay = m * sin(rad);
}

// Obtiene la aceleración como un vector
Vector2D Particula::aceleracion() const
{
    return Vector2D(ax, ay);
}

// Avanza la partícula usando movimiento rectilíneo uniforme (MRU)
void Particula::avanzaMRU(double dt)
{
    px += vx * dt; // Actualiza posición en x
    py += vy * dt; // Actualiza posición en y
}

// Avanza la partícula usando movimiento uniformemente acelerado (MUA)
void Particula::avanzaMUA(double dt)
{
    px += vx * dt + 0.5 * ax * dt * dt; // Actualiza posición en x
    py += vy * dt + 0.5 * ay * dt * dt; // Actualiza posición en y
    vx += ax * dt;                      // Actualiza velocidad en x
    vy += ay * dt;                      // Actualiza velocidad en y
}

// Establece el radio de la partícula
void Particula::radio(double r)
{
    radio_ = r;
}

// Obtiene el radio de la partícula
double Particula::radio() const
{
    return radio_;
}

// Establece la densidad de la partícula
void Particula::densidad(double d)
{
    densidad_ = d;
}

// Obtiene la densidad de la partícula
double Particula::densidad() const
{
    return densidad_;
}

// Obtiene la velocidad como un vector
Vector2D Particula::velocidad() const
{
    return Vector2D(vx, vy);
}

// Establece la velocidad desde un vector
void Particula::velocidad(const Vector2D &v)
{
    vx = v.getX();
    vy = v.getY();
}

// Calcula la masa de la partícula (densidad * área)
double Particula::masa() const
{
    return densidad_ * M_PI * radio_ * radio_;
}

// Obtiene la dirección de la partícula
Vector2D Particula::direccion() const
{
    return direccion_;
}

// Establece la dirección desde un ángulo (en grados)
void Particula::direccion(double a)
{
    direccion_ = Vector2D(radio_, a, Vector2D::Uds::Grados);
}

// Gira la partícula un ángulo dado (en grados)
void Particula::girar(double ang)
{
    double nuevoAngulo = direccion_.getAnguloGrados() + ang;
    direccion_.setAnguloGrados(nuevoAngulo); // Actualiza la dirección
}

// Establece el tipo de partícula (1: nave, 2: asteroide, 3: disparo)
void Particula::tipo(int t)
{
    tipo_ = t;
}

// Establece el color de la partícula
void Particula::color(BiGS::Color c)
{
    color_ = c;
}

// Dibuja la partícula en la pantalla
void Particula::dibujar(bool dibujarVectores)
{
    if (tipo_ == 1 && !naveImg.empty())
    {
        // Dibuja la nave con su imagen, escalada y rotada según la dirección
        float escala = (2 * radio_) / naveImg.width();                       // Escala para que el diámetro sea 2*radio
        float angulo = (direccion_.getAnguloGrados() + 90.0) * M_PI / 180.0; // Compensa orientación
        naveImg.draw(px - radio_, py - radio_, escala, escala, angulo);
    }
    else if (tipo_ == 2 && !asteroideImg.empty())
    {
        // Dibuja el asteroide con su imagen, escalada
        float escala = (2 * radio_) / asteroideImg.width();               // Escala para que el diámetro sea 2*radio
        asteroideImg.draw(px - radio_, py - radio_, escala, escala, 0.0); // Sin rotación
    }
    else if (tipo_ == 3)
    {
        // Dibuja el disparo como un círculo verde
        BiGS::drawCircle(px, py, radio_, BiGS::CGreen, BiGS::CGreen);
    }
    else
    {
        // Dibuja la partícula como un círculo con el color especificado
        BiGS::drawCircle(px, py, radio_, color_, color_);
    }

    if (dibujarVectores)
    {
        // Dibuja el vector de velocidad (amarillo)
        Vector2D vel = velocidad();
        float vmod = vel.getModulo();
        if (vmod > 0)
        {
            float ang = vel.getAnguloGrados();
            float scale = radio_ / 20.0; // Escala la flecha
            float minLength = 10.0;      // Longitud mínima para visibilidad
            float scaledLength = std::max(vmod * scale, minLength);
            float x2 = px + scaledLength * cos(ang * M_PI / 180.0);
            float y2 = py + scaledLength * sin(ang * M_PI / 180.0);
            BiGS::drawArrow(px, py, x2, y2, 8.0, 8.0, BiGS::CYellow); // Flecha amarilla
        }

        // Dibuja el vector de aceleración (rojo)
        Vector2D acc = aceleracion();
        float amod = acc.getModulo();
        if (amod > 0)
        {
            float ang = acc.getAnguloGrados();
            float scale = radio_ / 20.0; // Escala la flecha
            float minLength = 10.0;      // Longitud mínima para visibilidad
            float scaledLength = std::max(amod * scale, minLength);
            float x2 = px + scaledLength * cos(ang * M_PI / 180.0);
            float y2 = py + scaledLength * sin(ang * M_PI / 180.0);
            BiGS::drawArrow(px, py, x2, y2, 8.0, 8.0, BiGS::CRed); // Flecha roja
        }

        // Dibuja el vector de dirección para la nave (verde oscuro)
        if (tipo_ == 1)
        {
            Vector2D dir = direccion();
            float ang = dir.getAnguloGrados();
            float length = radio_ * 1.5; // Longitud de la flecha de dirección
            float x2 = px + length * cos(ang * M_PI / 180.0);
            float y2 = py + length * sin(ang * M_PI / 180.0);
            BiGS::drawArrow(px, py, x2, y2, 8.0, 8.0, BiGS::colorRGB(0, 100, 0)); // Flecha verde oscuro
        }
    }
}

// Marca la partícula como difunta (eliminada)
void Particula::marcarDifunta(bool d)
{
    difunta_ = d;
}

// Verifica si la partícula está marcada como difunta
bool Particula::esDifunta() const
{
    return difunta_;
}

// Establece el tiempo de disparo (para disparos)
void Particula::tiempoDisparo(double t)
{
    tiempoDisparo_ = t;
}

// Obtiene el tiempo de disparo
double Particula::tiempoDisparo() const
{
    return tiempoDisparo_;
}

// Obtiene el tipo de partícula
int Particula::tipo() const
{
    return tipo_;
}

// Convierte los datos de la partícula a una cadena
std::string Particula::to_string() const
{
    return "P=(" + std::to_string(px) + "," + std::to_string(py) + "), V=(" +
           std::to_string(vx) + "," + std::to_string(vy) + "), r=" + std::to_string(radio_) +
           ", m=" + std::to_string(masa());
}

// Corrige las velocidades de dos partículas tras una colisión elástica
void corrigeChoque(Particula &a1, Particula &a2)
{
    Vector2D v1 = a1.velocidad(); // Velocidad de la primera partícula
    Vector2D v2 = a2.velocidad(); // Velocidad de la segunda partícula
    // Verifica si las partículas se están acercando
    if ((v1.getX() - v2.getX()) * (a2.posicion().getX() - a1.posicion().getX()) +
            (v1.getY() - v2.getY()) * (a2.posicion().getY() - a1.posicion().getY()) >=
        0)
    {
        double sum = a1.masa() + a2.masa();              // Suma de las masas
        Vector2D difp12 = a1.posicion() - a2.posicion(); // Vector de posición relativa (1 a 2)
        Vector2D difp21 = a2.posicion() - a1.posicion(); // Vector de posición relativa (2 a 1)
        double dot1 = difp12 * (v1 - v2);                // Producto escalar para la primera partícula
        double dot2 = (v2 - v1) * difp21;                // Producto escalar para la segunda partícula
        double normal = difp12.getModulo();
        normal *= normal; // Norma al cuadrado
        double norma2 = difp21.getModulo();
        norma2 *= norma2; // Norma al cuadrado
        // Calcula las nuevas velocidades usando la fórmula de colisión elástica
        Vector2D nueva_v1 = v1 - (2 * a2.masa() / sum) * dot1 * (1.0 / normal) * difp12;
        Vector2D nueva_v2 = v2 - (2 * a1.masa() / sum) * dot2 * (1.0 / norma2) * difp21;
        a1.velocidad(nueva_v1); // Actualiza la velocidad de la primera partícula
        a2.velocidad(nueva_v2); // Actualiza la velocidad de la segunda partícula
    }
}