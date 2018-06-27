# Introducción
Remake del icónico videojuego Worms, un juego de estrategia militar por turnos desarrollado por Team17 y lanzado en 1995.
Desarrollado por tres estudiantes como Trabajo Práctico para la materia (75.42) Taller de Programación de la Facultad de Ingeniería de la Universidad de Buenos Aires. El trabajo fue realizado en un período de 8 (ocho semanas).

Documentación más detallada:

[Manual de usuario](https://github.com/gabyrobles93/tp-final-taller/blob/master/documentation/Manual_de_usuario.pdf)

[Manual de proyecto](https://github.com/gabyrobles93/tp-final-taller/blob/master/documentation/Manual_de_proyecto.pdf)

[Documentacion técnica](https://github.com/gabyrobles93/tp-final-taller/blob/master/documentation/Documentaci%C3%B3n_t%C3%A9cnica.pdf)

# Datos de creadores

| Padrón | Nombre y Apellido         | Mail | Rol |
|--------|---------------------------| ------ | ----- |
| 97893 | ALVAREZ WINDEY ARIEL JUSTO | arieljaw12@gmail.com | Uso de SDL. Dibujos, animaciones y sonidos |
| 98546 | DIZ GONZALO                | dizmartin.gonzalo@gmail.com | Uso de box2d. Modelado de mundo físico. Optimización. |
| 95897 | GABRIEL ROBLES             | gabyrobles93@gmail.com | Uso de QT5. Protocolo e integración cliente-servidor |

# Dependencias
Todas las dependencias son proveídas (si el usuario asi lo desea) por el instalador del juego.

Sistema Operativo: Ubuntu

| Librería | Versión mínima         |
|--------|---------------------------|
| libsdl2-dev | 2.0.8 |
| libsdl2-image-dev | 2.0.3 |
| libsdl2-ttf-dev | 2.0.14  |
| libsdl2-mixer-dev | 2.0.2 |
| qt5-default | 5.9.5 |
| cmake | 3.10.2 |
| box2d | 2.3.1 |
| yaml-cpp (*) | 0.6.2|
| gcc | 7.3.0 |

(*) Obtenida de https://github.com/jbeder/yaml-cpp

# Tutorial de instalacion:

1) Ejecutar:
```bash
 $ sudo ./worms_installer.sh
```
2) Ejecutar el editor para crear un mapa.
```bash
 $ worms-editor
```
2.1) Seleccionar un background (imagen .png), elegir la configuración del fondo (centrado, mosaico o extendido) ponerle nombre al escenario, seleccionar cantidad de equipos, vida inicial de Worms, nivel del agua y municiones. Cuando todo esté seteado presionar 'Go Create'".
   
   2.2) Colocar vigas y gusanos. Todos los gusanos deben ser colocados. Se puede utilizar los comandos rápidos ctrl+z y ctrl+y como 'undo' y 'redo' de las acciones. Los objetos a colocar se pueden seleccionar con el mouse o cambiarlos con la letra Q. Las vigas pueden rotarse con la letr R o bien con la rueda del mouse.
   
   2.3) Una vez todos los Worms estén colocados en el mapa, apretar alt-f4 o bien cerrar la ventana clickeando en la cruz. Se nos preguntará si queremos guardar el mapa.
   
   2.4) El mapa se guardará en la carpeta /usr/etc/worms/maps como un archivo .tar.gz

3) Ejecutar un servidor.

```c++
 $ worms-server <listening_port> |<config_file_path>|
```
 Nota sobre modificación de parámetros: El servidor por default carga el archivo de configuración estándar, ubicado en /usr/etc/worms/server_config.yml . De querer modificar los parámetros del sevidor, se recomienda hacer una copia de este archivo en otro directorio, modificarlo, y al momento de levantar el servidor, referirlo con <config_file_path>.
 
   3.1) El servidor se ejecutará y puede aceptar conexiones.

4) Ejecutar un cliente.
```bash
 $ worms-client
```
   4.1) Escribir puerto e IP (localhost/<port>) y un username deseado. Si el username ya existe el servidor te va a renombrar.
 
   4.2) Estas en el Lobby del servidor. Acá podes crear una partida "Create Match", unirte a una partida en espera "Join Match" o salir del con "Exit".
  
   4.3) Crear una partida. En el lobby clickear "Create Match". Nombrar a la partida y elegir un mapa clickeando "Choose Map". Los mapas que creaste con el editor van a estar por default en la carpeta /usr/etc/worms/maps. Debe tener la extensión .tar.gz tal como el editor lo generó. Clickear "Create Match".

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
