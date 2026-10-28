#include <iostream>
#include "bigs.h"

using namespace std;

// Con Allegro es obligatorio usar este prototipo de main()
// Si se usa el prototipo simplificado, main(), mostrará un error en tiempo de ejecución:
//   symbol not found in flat namespace '__al_mangled_main'
int main(int argc, char *argv[]) {
  BiGS::windowOpen(500,400,"BiGS: Teclado 1");
  BiGS::txtDraw("Mira el resultado en la consola",10,10,BiGS::CGreen);

  // Bucle típico: mientras no se pulse cerrar ventana
  while (!BiGS::closeRequested()) {
    BiGS::Event e;
    if (BiGS::eventNext(e)) {
      if (e.type==BiGS::KEY_DOWN) {
        cout << " Evento: KEY_DOWN" << endl;
        cout << " Has pulsado la tecla " << e.keyboard.keycode;
        cout << "  (" << BiGS::eventKeyName(e.keyboard.keycode) << ")" << endl;
        if (e.keyboard.keycode == ALLEGRO_KEY_A)
          cout << "  ... acabo de comprobar que has pulsado la tecla A" << endl;
      } else if (e.type==BiGS::KEY_CHAR) {
        cout << " Evento: KEY_CHAR" << endl;
        cout << " Has pulsado la tecla " << e.keyboard.keycode;
        cout << "  (" << BiGS::eventKeyName(e.keyboard.keycode) << ")" << endl;
        cout << "  unichar = " << e.keyboard.unichar << endl;
        if (e.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT) cout << "SHIFT" << endl;
        if (e.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL) cout << "CTRL" << endl;
        if (e.keyboard.modifiers & ALLEGRO_KEYMOD_ALT) cout << "ALT" << endl;
      } else if (e.type==BiGS::MOUSE_MOVE) {
        cout << "Evento: MOUSE_MOVE" << endl;
        cout << " Has movido el ratón. Coordenadas " << e.mouse.x << "," << e.mouse.y << endl;
      }
      cout << endl;
    }
  }

  return 0;
}