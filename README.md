


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

2) En el directorio tp-final-taller/server ejecutar los siguientes comandos:

```c++
 $ mkdir build
 $ cd build
 $ cmake ..
 $ make
 $ ./server 
```
3) En el directorio tp-final-taller/client ejecutar los siguientes comandos:
```bash
 $ mkdir build
 $ cd build
 $ cmake ..
 $ make
 $ ./client
```

4) Manual de juego
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
