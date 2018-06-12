


==========


Código y notas del proyecto final de Taller de Programación I - FIUBA


| Padrón | Nombre y Apellido         |
|--------|---------------------------|
| 97893 | ALVAREZ WINDEY ARIEL JUSTO |
| 98546 | DIZ GONZALO                |
| 95897 | GABRIEL ROBLES             |

Tablero de tareas en TRELLO:
https://trello.com/b/opoeIXXF/worms-tp-final

# Tutorial de instalacion:

1) Descargar las siguientes librerias
```bash
 $ sudo apt-get install libsdl2-dev
 $ sudo apt-get install libsdl2-image-dev
 $ sudo apt-get install libsdl2-ttf-dev
 $ sudo apt-get install libsdl2-mixer-dev
 $ sudo apt-get install qt5-default
 $ sudo apt-get install cmake 
```
2) Ejecutar el editor para crear un mapa. Dentro de tp-final-taller/editor:
```bash
 $ mkdir build
 $ cd build
 $ cmake ..
 $ make
 $ ./editor
```
2.1) Seleccionar un background (imagen .png), elegir la configuración del fondo (centrado, mosaico o extendido) ponerle nombre al escenario, seleccionar cantidad de equipos, vida inicial de Worms, nivel del agua y municiones. Cuando todo esté seteado presionar 'Go Create'".
   
   2.2) Colocar vigas y gusanos. Todos los gusanos deben ser colocados. Se puede utilizar los comandos rápidos ctrl+z y ctrl+y como 'undo' y 'redo' de las acciones. Los objetos a colocar se pueden seleccionar con el mouse o cambiarlos con la letra Q. Las vigas pueden rotarse con la letr R o bien con la rueda del mouse.
   
   2.3) Una vez todos los Worms estén colocados en el mapa, apretar alt-f4 o bien cerrar la ventana clickeando en la cruz. Se nos preguntará si queremos guardar el mapa.
   
   2.4) El mapa se guardará en la carpeta tp-final-taller/editor/maps como un archivo .tar.gz

3) Ejecutar un servidor. En el directorio tp-final-taller/server ejecutar los siguientes comandos:

```c++
 $ mkdir build
 $ cd build
 $ cmake ..
 $ make
 $ ./server ../server.cfg <port>
```
 Nota sobre modificación de parámetros: En esta preentrega el archivo server.cfg no tiene niguna utilidad. Las configuraciones de parámetros del servidor se pueden realizar modificando los archivos fuente configuration.cpp ubicado en tp-final-taller/server/src.
 
   3.1) El servidor se ejecutará y puede aceptar conexiones.

4) Ejecutar un cliente. En el directorio tp-final-taller/client ejecutar los siguientes comandos:
```bash
 $ mkdir build
 $ cd build
 $ cmake ..
 $ make
 $ ./client
```
   4.1) Escribir puerto e IP (localhost/<port>) y un username deseado. Si el username ya existe el servidor te va a renombrar.
 
   4.2) Estas en el Lobby del servidor. Acá podes crear una partida "Create Match", unirte a una partida en espera "Join Match" o salir del con "Exit".
  
   4.3) Crear una partida. En el lobby clickear "Create Match". Nombrar a la partida y elegir un mapa clickeando "Choose Map". Los mapas que creaste con el editor van a estar por default en la carpeta tp-final-taller/editor/maps. Debe tener la extensión .tar.gz tal como el editor lo generó. Clickear "Create Match".

   4.4) Estas en tu sala de espera. Clickeando Refresh podrás ver los jugadores que se unieron a tu partida. Cuando la cantidad de jugadores en espera sea la suficiente (la requerida por el mapa), podrás clickear en "Start Match". Si clickeas en "Exit", cancelarás la partida en espera y todos los jugadores de esa sala volverán al Lobby.
   
5) Comienza la partida. Manual de juego.
```bash
  $ Movimiento de gusano: 
        - A: movimiento a izquierda.
        - D: movimiento a derecha.
        - W: movimiento de mira hacia arriba.
        - S: movimiento de miera hacia abajo.
        - ENTER: salto hacia adelante.
        - BACK: salto hacia atras.
   $ Inventario de armas:
        - Q: abre el inventario, apretar nuevamente para navegar por el.
        - E: cierra el inventario.
        - RIGHT CLICK: abre el inventario.
        - LEFT CLICK: selecciona el arma.
   $ Disparos:
        - SPACE: disparar arma seleccionada, si se mantiene apretada aumenta la potencia de tiro
        - AIR STRIKE Y TELEPORT: se activan con el click izquierdo del mouse.
   $ Camara:
        - ARROW KEYS: mueven la camara.
```
