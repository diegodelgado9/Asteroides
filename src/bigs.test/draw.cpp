#include "bigs.h"

using namespace BiGS;

// Con Allegro es obligatorio usar este prototipo de main()
// Si se usa el prototipo simplificado, main(), mostrará un error en tiempo de ejecución:
//   symbol not found in flat namespace '__al_mangled_main'
int main(int argc, char *argv[]) {
  windowOpen(800,600,"BiGS: dibujando");

  // Dibujamos puntos en tonos azules
  for (int i=0; i<50; ++i) {
    Color c = colorRGB(i*4,i*4,250);
    drawPoint(10+i*2,10+i*2,c);
  }

  // Dibujamos líneas rectas (tonos violeta)
  for (int i=0; i<10; ++i) {
    Color c = colorRGB(100+i*10,0,100+i*10);
    drawLine(10,100+i*10,100,200+i*30,c);
  }

  // Dibujamos rectángulos sin relleno (tonos rojos)
  for (int i=0; i<20; ++i) {
    Color c = colorRGB(255-i*10,0,0);
    drawRectangle(250+i*3,20+i*3,450-i*2,300-i*2,c);
  }

  // Dibujamos rectángulos con relleno (tonos verdes)
  drawRectangle(150,350,350,500,colorRGB(0,255,0),colorRGB(0,255,0));
  drawRectangle(250,310,450,400,colorRGB(0,200,0),colorRGB(0,200,0));
  drawRectangle(300,370,400,550,colorRGB(0,160,0),colorRGB(0,160,0));

  // Dibujamos círculos sin relleno (tonos amarillos)
  for (int i=0; i<20; ++i)
    drawCircle(600,150,50+i*2,colorRGB(255-i*10,255-i*10,0));
  
  // Dibujamos elipses con relleno (tonos azules)
  for (int i=20; i>0; --i)
    drawEllipse(600,350,50+i*4,30+i*2,colorRGB(0,0,255-i*10),colorRGB(0,0,255-i*10));

  // Esperamos a que se pulse una tecla
  eventWaitKeyboard();

  return 0;
}