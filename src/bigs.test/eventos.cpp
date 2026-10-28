#include "bigs.h"
using namespace BiGS;

int cuentalineas(const char *t) {
  int c=0;
  while (*t) {
    if (*t=='\n') c++;
    t++;
  }
  return c;
}

int main(int argc, char *argv[]) {
  BiGS::windowOpen(500,400,"BiGS: Eventos");
  BiGS::logEvents();
  BiGS::txtDraw("Pulsa una tecla",10,10,BiGS::CGreen);
  int nlin = 0; // Línea por la que vamos escribiendo
  int sizelin = BiGS::txtLineHeight()+1;
  int height = BiGS::windowHeight();
  // Bucle típico: mientras no se pulse cerrar ventana
  while (!BiGS::closeRequested()) {
    BiGS::Event e;
    if (BiGS::eventNext(e)) {
      int nlineas = cuentalineas(BiGS::to_string(e).c_str())+1;
      if (height-nlin*sizelin < 0 ) {
        BiGS::clear();
        nlin = 0;
      }
      BiGS::txtDrawMultiline(BiGS::to_string(e).c_str(),10,nlin*sizelin,480,BiGS::CGreen);
      nlin += nlineas;
    }
  }
}