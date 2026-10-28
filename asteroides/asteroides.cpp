#include "bigs_defs.h"
#include "bigs_image.h"
#include "bigs.h"
#include "particula.h"
#include "listaparticulas.h"
#include <cmath>
#include <ctime>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

// Variables globales para los parámetros del juego
int AstN = 3;                                                                  // Número de asteroides
int AstRMin = 10, AstRMax = 40, AstRDes = 10;                                  // Radio mínimo, máximo y umbral de destrucción de asteroides
int AstVMin = 10, AstVMax = 100;                                               // Velocidad mínima y máxima de asteroides
int DispMax = 5, DispTVida = 10;                                               // Máximo de disparos y tiempo de vida de disparos (10 segundos)
int NaveR = 20, NaveAInc = 50, NaveAMax = 300, NaveVMax = 300, DispVMin = 150; // Parámetros de la nave

bool BordersBounce = true;         // Modo de colisión con bordes (rebote o vuelta)
const char *Jugador = "-";        // Nombre del jugador por defecto
const char *RankingFile = nullptr; // Nombre del archivo de ranking

// Genera un número aleatorio entre min y max
double aleatorio(double min, double max)
{
    return min + (std::rand() / (double)RAND_MAX) * (max - min);
} 

// Verifica si una posición es válida (lo suficientemente lejos de la nave)
bool esPosicionValida(double x, double y, double naveX, double naveY, double minDist)
{
    double dx = x - naveX;
    double dy = y - naveY;
    return std::sqrt(dx * dx + dy * dy) > minDist;
}

// Crea un asteroide con propiedades aleatorias, asegurando que no esté cerca de la nave
Particula crearAsteroide(double naveX, double naveY, int AN, int AL)
{
    Particula a;
    double x, y;
    // Genera posiciones hasta encontrar una válida
    do
    {
        x = aleatorio(0, AN);
        y = aleatorio(0, AL);
    } while (!esPosicionValida(x, y, naveX, naveY, 150));
    a.posicion(x, y);
    a.radio(aleatorio(AstRMin, AstRMax));
    a.densidad(aleatorio(1, 5));
    a.velocidad(aleatorio(AstVMin, AstVMax), aleatorio(0, 360));
    a.aceleracion(0, 0);
    a.tipo(2); // Tipo 2 para asteroides
    a.color(BiGS::CCyan);
    return a;
}

// Función principal del juego
int main(int argc, char **argv)
{
    // Inicializa la semilla aleatoria
    std::srand((unsigned)std::time(nullptr));
    // Procesa los argumentos de la línea de comandos
    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-jugador") && i + 1 < argc)
            Jugador = argv[++i]; // Establece el nombre del jugador
        else if (!strcmp(argv[i], "-ranking") && i + 1 < argc)
            RankingFile = argv[++i]; // Establece el archivo de ranking
        else if (!strcmp(argv[i], "-borders"))
            BordersBounce = !BordersBounce; // Cambia el modo de bordes
        else if (!strcmp(argv[i], "-astn") && i + 1 < argc)
            AstN = std::atoi(argv[i + 1]); // Número de asteroides
        else if (!strcmp(argv[i], "-dispmax") && i + 1 < argc)
            DispMax = std::atoi(argv[++i]); // Máximo de disparos
        else if (!strcmp(argv[i], "-disptvida") && i + 1 < argc)
            DispTVida = std::atoi(argv[++i]); // Tiempo de vida de disparos
    }

    // Define dimensiones de la ventana
    const int AN = 800, AL = 600;
    // Abre la ventana del juego
    BiGS::windowOpen(AN, AL, "MP-Asteroides", true, DRAWMODE_DELAYED);

    // Carga las imágenes de las partículas
    if (!Particula::cargarImagenes())
        return 1;

    // Carga la imagen de fondo
    BiGS::Image fondo;
    if (!fondo.load("./data/fondo.bmp"))
    {
        Particula::liberarImagenes();
        return 1;
    }

    // Carga los archivos de audio
    BiGS::Audio musica = BiGS::audioLoad("./data/musicafondo.wav");
    BiGS::Audio disparo = BiGS::audioLoad("./data/disparo.wav");
    BiGS::Audio explosion = BiGS::audioLoad("./data/explosionasteroide.wav");

    // Verifica si los audios se cargaron correctamente
    bool audioLoaded = (musica != -1 && disparo != -1 && explosion != -1);
    if (audioLoaded && musica != -1)
        BiGS::audioPlay(musica, 0, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP); // Reproduce música en bucle

    // Carga la fuente para el texto
    BiGS::Font fuente = BiGS::txtLoadFont("./data/fuente.ttf", 20);
    if (fuente == -1)
        fuente = 0;

    // Lista para almacenar todas las partículas (nave, asteroides, disparos)
    ListaParticulas lista;

    // Crea la nave en el centro de la pantalla
    Particula nave;
    nave.posicion(AN / 2.0, AL / 2.0);
    nave.velocidad(0, 0);
    nave.aceleracion(0, 0);
    nave.radio(NaveR);
    nave.densidad(1);
    nave.direccion(-90);
    nave.tipo(1); // Tipo 1 para la nave
    nave.color(BiGS::CGreen);
    lista.inserta(nave);

    // Inicializa contadores
    int puntos = 0;
    int disparosActivos = 0;

    // Almacena tiempos de vida acumulados para disparos (índice en lista -> tiempo)
    std::vector<std::pair<int, double>> shotLifetimes;

    // Crea los asteroides iniciales
    for (int i = 0; i < AstN; i++)
        lista.inserta(crearAsteroide(AN / 2.0, AL / 2.0, AN, AL));

    // Dibuja la pantalla inicial
    BiGS::clear(BiGS::CBlack);
    if (!fondo.empty())
        fondo.draw(0, 0, 1.0, 1.0);
    for (int i = 0; i < lista.size(); i++)
        lista.get(i).dibujar(false);
    if (fuente != -1)
        BiGS::txtDraw("Pulsa una tecla para comenzar", AN / 2 - 100, AL / 2, BiGS::CWhite, fuente, ALLEGRO_ALIGN_CENTRE);
    BiGS::refresh();
    BiGS::eventWaitKeyboard();

    // Bucle principal del juego
    bool jugando = true;
    while (jugando && !BiGS::closeRequested())
    {
        // Calcula el tiempo transcurrido
        double dt = BiGS::timeFromLastCall() / 1000000.0;
        if (dt < 0.0001 || dt > 0.1)
            dt = 0.016;

        // Control de la nave
        if (lista.size() > 0)
        {
            Particula nave = lista.get(0);
            if (BiGS::isKeyPressed(ALLEGRO_KEY_LEFT))
                nave.girar(-5); // Gira a la izquierda
            if (BiGS::isKeyPressed(ALLEGRO_KEY_RIGHT))
                nave.girar(5); // Gira a la derecha
            if (BiGS::isKeyPressed(ALLEGRO_KEY_UP))
            { // Acelera hacia adelante
                double ang = nave.direccion().getAnguloGrados();
                double acc = nave.aceleracion().getModulo() + NaveAInc;
                if (acc > NaveAMax)
                    acc = NaveAMax;
                nave.aceleracion(acc, ang);
            }
            else if (BiGS::isKeyPressed(ALLEGRO_KEY_DOWN))
            { // Frena
                double ang = nave.velocidad().getAnguloGrados() + 180;
                nave.aceleracion(NaveAMax, ang);
            }
            else
            {
                nave.aceleracion(0, nave.direccion().getAnguloGrados()); // Sin aceleración
            }

            // Limita la velocidad máxima de la nave
            if (nave.velocidad().getModulo() > NaveVMax)
            {
                double ang = nave.velocidad().getAnguloGrados();
                nave.velocidad(NaveVMax, ang);
            }

            lista.set(nave, 0);
        }
        else
        {
            jugando = false;
            break;
        }

        // Manejo de eventos
        BiGS::Event ev;
        while (BiGS::eventPresent())
        {
            if (BiGS::eventNext(ev))
            {
                if (ev.type == BiGS::KEY_DOWN)
                {
                    if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE && disparosActivos < DispMax && lista.size() > 0)
                    {
                        // Dispara un proyectil
                        if (audioLoaded && disparo != -1)
                            BiGS::audioPlay(disparo, 0, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE);
                        Particula d = lista.get(0);
                        double ang = d.direccion().getAnguloGrados();
                        double x = d.posicion().getX() + (d.radio() + 10) * cos(ang * M_PI / 180.0);
                        double y = d.posicion().getY() + (d.radio() + 10) * sin(ang * M_PI / 180.0);
                        d.posicion(x, y);
                        double v = std::max((double)DispVMin, d.velocidad().getModulo() * 1.2);
                        d.velocidad(v, ang);
                        d.radio(5);
                        d.aceleracion(0, 0);
                        d.tipo(3); // Tipo 3 para disparos
                        d.tiempoDisparo(BiGS::timeGet());
                        int shotIndex = lista.size();
                        lista.inserta(d);
                        disparosActivos++;
                        shotLifetimes.push_back({shotIndex, 0.0}); // Inicializa tiempo de vida
                    }
                    else if (ev.keyboard.keycode == ALLEGRO_KEY_B)
                    {
                        BordersBounce = !BordersBounce; // Cambia el modo de bordes
                    }
                }
            }
        }

        // Actualiza tiempos de vida acumulados
        for (auto &shot : shotLifetimes)
        {
            shot.second += dt;
        }

        // Expirar disparos
        std::vector<int> aBorrar;
        for (int i = 1; i < lista.size(); i++)
        {
            Particula p = lista.get(i);
            if (p.tipo() == 3 && !p.esDifunta())
            {
                for (auto &shot : shotLifetimes)
                {
                    if (shot.first == i && shot.second > DispTVida)
                    {
                        p.marcarDifunta(true);
                        lista.set(p, i);
                        disparosActivos--;
                        aBorrar.push_back(i);
                        break;
                    }
                }
            }
        }

        // Detectar colisiones
        ListaParticulas nuevasParticulas;
        for (int i = 0; i < lista.size(); i++)
        {
            Particula pi = lista.get(i);
            if (pi.esDifunta())
                continue;
            for (int j = i + 1; j < lista.size(); j++)
            {
                Particula pj = lista.get(j);
                if (pj.esDifunta())
                    continue;
                double dx = pi.posicion().getX() - pj.posicion().getX();
                double dy = pi.posicion().getY() - pj.posicion().getY();
                double dist = std::sqrt(dx * dx + dy * dy);
                if (dist < pi.radio() + pj.radio())
                {
                    if (pi.tipo() == 1 || pj.tipo() == 1)
                    {
                        jugando = false; // Colisión con nave termina el juego
                        break;
                    }
                    else if (pi.tipo() == 2 && pj.tipo() == 2)
                    {
                        corrigeChoque(pi, pj); // Corrige choque entre asteroides
                        lista.set(pi, i);
                        lista.set(pj, j);
                    }
                    else if ((pi.tipo() == 2 && pj.tipo() == 3) || (pi.tipo() == 3 && pj.tipo() == 2))
                    {
                        // Colisión entre asteroide y disparo
                        if (audioLoaded && explosion != -1)
                            BiGS::audioPlay(explosion, 0, 2.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE);
                        int idxA = pi.tipo() == 2 ? i : j;
                        int idxD = pi.tipo() == 3 ? i : j;
                        Particula ast = lista.get(idxA);
                        puntos += (int)ast.radio();

                        if (!lista.get(idxD).esDifunta())
                        {
                            aBorrar.push_back(idxA);
                            aBorrar.push_back(idxD);
                            disparosActivos--;
                        }

                        // Divide el asteroide si es lo suficientemente grande
                        double nuevoRadio = ast.radio() / 2.0;
                        if (nuevoRadio > AstRDes)
                        {
                            for (int offset : {90, -90})
                            {
                                Particula nuevoAst = ast;
                                nuevoAst.radio(nuevoRadio);
                                double ang = ast.velocidad().getAnguloGrados() + offset;
                                nuevoAst.velocidad(ast.velocidad().getModulo(), ang);
                                nuevoAst.posicion(ast.posicion().getX(), ast.posicion().getY());
                                nuevoAst.densidad(ast.densidad());
                                nuevoAst.tipo(2);
                                nuevoAst.color(BiGS::CCyan);
                                nuevasParticulas.inserta(nuevoAst);
                            }
                        }
                    }
                    else if (pi.tipo() == 3 && pj.tipo() == 3)
                    {
                        // Colisión entre disparos: desaparecen
                        if (!pi.esDifunta() && !pj.esDifunta())
                        {
                            pi.marcarDifunta(true);
                            pj.marcarDifunta(true);
                            lista.set(pi, i);
                            lista.set(pj, j);
                            disparosActivos -= 2; // Reduce el contador de disparos activos
                            aBorrar.push_back(i);
                            aBorrar.push_back(j);
                        }
                    }
                }
            }
            if (!jugando)
                break;
        }

        // Elimina partículas marcadas, protegiendo la nave
        std::sort(aBorrar.begin(), aBorrar.end(), std::greater<int>());
        for (int idx : aBorrar)
        {
            if (idx != 0 && idx < lista.size())
            {
                lista.borra(idx);
                // Actualiza índices en shotLifetimes
                for (auto &shot : shotLifetimes)
                {
                    if (shot.first > idx)
                        shot.first--;
                }
            }
        }

        // Limpia shotLifetimes para disparos eliminados
        shotLifetimes.erase(
            std::remove_if(shotLifetimes.begin(), shotLifetimes.end(),
                [&](const auto &shot) {
                    if (shot.first >= lista.size()) return true;
                    return lista.get(shot.first).esDifunta();
                }),
            shotLifetimes.end());

        // Inserta nuevas partículas
        for (int i = 0; i < nuevasParticulas.size(); i++)
        {
            lista.inserta(nuevasParticulas.get(i));
        }

        // Actualiza posiciones
        for (int i = lista.size() - 1; i >= 0; i--)
        {
            Particula p = lista.get(i);
            if (p.esDifunta())
                continue;
            double x = p.posicion().getX(), y = p.posicion().getY(), r = p.radio();

            if (BordersBounce)
            {
                // Rebote en los bordes para todas las partículas
                if (x - r < 0 || x + r > AN)
                    p.vang(180 - p.velocidad().getAnguloGrados());
                if (y - r < 0 || y + r > AL)
                    p.vang(-p.velocidad().getAnguloGrados());

                x = std::min(std::max(x, r), (double)AN - r);
                y = std::min(std::max(y, r), (double)AL - r);
            }
            else
            {
                // Vuelta al otro lado de la pantalla para todas las partículas
                if (x + r < 0)
                    x = AN + r;
                if (x - r > AN)
                    x = -r;
                if (y + r < 0)
                    y = AL + r;
                if (y - r > AL)
                    y = -r;
            }

            p.posicion(x, y);
            p.avanzaMUA(dt); // Avanza según movimiento uniformemente acelerado
            lista.set(p, i);
        }

        // Dibuja la escena
        BiGS::clear(BiGS::CBlack);
        if (!fondo.empty())
            fondo.draw(0, 0, 1.0, 1.0);
        if (lista.size() > 0 && fuente != -1)
        {
            // Muestra información en pantalla
            BiGS::txtDraw((std::string("Jugador: ") + Jugador).c_str(), 10, 10, BiGS::CWhite, fuente);
            BiGS::txtDraw(("Puntos: " + std::to_string(puntos)).c_str(), 10, 30, BiGS::CWhite, fuente);
            BiGS::txtDraw(("Disparos: " + std::to_string(DispMax - disparosActivos)).c_str(), 10, 50, BiGS::CWhite, fuente);
            BiGS::txtDraw(("Modo bordes: " + std::string(BordersBounce ? "REBOTE" : "VUELTA")).c_str(), 10, 70, BiGS::CWhite, fuente);
            BiGS::txtDraw(("Velocidad nave: " + std::to_string((int)lista.get(0).velocidad().getModulo())).c_str(), 10, 90, BiGS::CWhite, fuente);
            BiGS::txtDraw(("Aceleracion nave: " + std::to_string((int)lista.get(0).aceleracion().getModulo())).c_str(), 10, 110, BiGS::CWhite, fuente);
        }
        for (int i = 0; i < lista.size(); i++)
        {
            if (!lista.get(i).esDifunta())
                lista.get(i).dibujar(false); // Dibuja partículas no eliminadas
        }
        BiGS::refresh();

        // Verifica si quedan asteroides
        bool quedanAst = false;
        for (int i = 0; i < lista.size(); i++)
        {
            if (lista.get(i).tipo() == 2 && !lista.get(i).esDifunta())
            {
                quedanAst = true;
                break;
            }
        }
        if (!quedanAst)
        {
            jugando = false; // Gana si no hay asteroides
        }

        // Corrige el contador de disparos activos
        int conteoReal = 0;
        for (int i = 0; i < lista.size(); i++)
        {
            if (lista.get(i).tipo() == 3 && !lista.get(i).esDifunta())
                conteoReal++;
        }
        disparosActivos = conteoReal;
    }

    // Muestra la pantalla final
    BiGS::clear(BiGS::CBlack);
    if (!fondo.empty())
        fondo.draw(0, 0, 1.0, 1.0);
    // Verifica si hay asteroides para determinar el mensaje final
    bool quedanAst = false;
    for (int i = 0; i < lista.size(); i++)
    {
        if (lista.get(i).tipo() == 2 && !lista.get(i).esDifunta())
        {
            quedanAst = true;
            break;
        }
    }
    std::string sfin = (!quedanAst ? "¡GANASTE! Puntos: " : "¡PERDISTE! Puntos: ") + std::to_string(puntos);
    if (fuente != -1)
        BiGS::txtDraw(sfin.c_str(), AN / 2 - 100, AL / 2, BiGS::CWhite, fuente, ALLEGRO_ALIGN_CENTRE);
    BiGS::refresh();
    BiGS::eventWaitKeyboard();

    // Guarda el puntaje en el archivo de ranking
    if (RankingFile)
    {
        std::ofstream f(RankingFile, std::ios::app);
        if (f)
            f << puntos << " " << Jugador << "\n";
    }

    // Libera recursos
    BiGS::audioStop();
    Particula::liberarImagenes();

    return 0;
} 