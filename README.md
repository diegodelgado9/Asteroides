# 🚀 Asteroides

Un clásico juego arcade de supervivencia espacial desarrollado en C++ utilizando el motor BiGS y la librería gráfica Allegro 5.

## 🎮 Sobre el juego

En **Asteroides**, controlas una nave espacial con el objetivo de sobrevivir y destruir todos los asteroides de la pantalla. ¡Ten cuidado! Cuando destruyes un asteroide grande, este se dividirá en fragmentos más pequeños. El juego termina si consigues destruir todas las amenazas o si tu nave colisiona con alguna de ellas.

### Controles

* **Flecha Arriba:** Acelerar la nave hacia adelante.
* **Flecha Abajo:** Frenar la nave.
* **Flechas Izquierda / Derecha:** Girar la nave.
* **Barra Espaciadora:** Disparar.
* **Tecla 'B':** Cambiar el comportamiento de los bordes de la pantalla (Modo Rebote o Modo Vuelta al lado opuesto).

## 🛠️ Requisitos previos

Para poder compilar y jugar a Asteroides, necesitas instalar el compilador, CMake y las librerías de desarrollo de **Allegro 5**. Dependiendo de tu sistema operativo o distribución, abre tu terminal y ejecuta los siguientes comandos:

**Ubuntu, Debian, Linux Mint y Pop!_OS:**
```bash
sudo apt update
sudo apt install build-essential cmake liballegro5-dev liballegro-image5-dev liballegro-audio5-dev liballegro-acodec5-dev liballegro-ttf5-dev
```

**Arch Linux, Manjaro y EndeavourOS:**
```bash
sudo pacman -S base-devel cmake allegro
```

**Fedora y RHEL:**
```bash
sudo dnf install gcc-c++ cmake allegro5-devel allegro5-addon-image-devel allegro5-addon-audio-devel allegro5-addon-acodec-devel allegro5-addon-ttf-devel
```

**macOS (Homebrew):**
```bash
brew install cmake allegro
```

**Windows (MSYS2 / MinGW):**
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-allegro
```

## ⚙️ Instrucciones de compilación

Este proyecto utiliza CMake para facilitar la compilación. Para generar el juego sin ensuciar el código fuente, sigue estos pasos estrictamente desde la carpeta raíz del proyecto:

**1. Crea una carpeta de compilación (build)**
Nunca compiles directamente en la carpeta `src`. Crea un directorio aislado:
```bash
mkdir build
cd build
```

**2. Configura el proyecto con CMake**
Ejecuta CMake apuntando a la subcarpeta `asteroides` dentro de `src`:
```bash
cmake ../src/asteroides
```
*(Nota: Este proceso detectará tu compilador, preparará el entorno y copiará automáticamente los recursos de la carpeta `data` a tu entorno de compilación).*

**3. Compila el código**
Una vez configurado, construye el ejecutable:
```bash
make
```

## ▶️ Cómo jugar

Una vez que el proceso de compilación llegue al 100%, el archivo ejecutable se habrá creado dentro de tu carpeta `build`. Para arrancar el juego, simplemente ejecuta:
```bash
./asteroides
```

### Opciones avanzadas (Línea de comandos)

Puedes personalizar tu partida pasando argumentos al ejecutar el juego. Por ejemplo:

* `./asteroides -jugador "TuNombre"` : Establece tu nombre de jugador.
* `./asteroides -astn 5` : Inicia la partida con 5 asteroides en lugar de 3.
* `./asteroides -borders` : Inicia el juego con el rebote en los bordes desactivado.
