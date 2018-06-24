if [ $(dpkg-query -W -f='${Status}' cmake 2>/dev/null | grep -c "ok installed") -eq 0 ];
then
 read -p "cmake es necesario para seguir con la instalacion desea instalarlo? (y/n): " -n 1 -r
 echo
 if [[ $REPLY =~ ^[Y|y]$ ]]
 then
    sudo apt-get install cmake
 else exit 1
 fi
fi

if [ $(dpkg-query -W -f='${Status}' libsdl2-dev 2>/dev/null | grep -c "ok installed") -eq 0 ];
then
 read -p "sdl2 es necesario para seguir con la instalacion desea instalarlo? (y/n): " -n 1 -r
 echo
 if [[ $REPLY =~ ^[Y|y]$ ]]
 then
	sudo apt-get install libsdl2-dev
 else exit 1
 fi
fi

if [ $(dpkg-query -W -f='${Status}' libsdl2-image-dev 2>/dev/null | grep -c "ok installed") -eq 0 ];
then
 read -p "sdl2-image-dev es necesario para seguir con la instalacion desea instalarlo? (y/n): " -n 1 -r
 echo
 if [[ $REPLY =~ ^[Y|y]$ ]]
 then
	sudo apt-get install libsdl2-image-dev
 else exit 1
 fi
fi

if [ $(dpkg-query -W -f='${Status}' libsdl2-ttf-dev 2>/dev/null | grep -c "ok installed") -eq 0 ];
then
 read -p "sdl2-ttf-dev es necesario para seguir con la instalacion desea instalarlo? (y/n): " -n 1 -r
 echo
 if [[ $REPLY =~ ^[Y|y]$ ]]
 then
	sudo apt-get install libsdl2-ttf-dev
 else exit 1
 fi
fi

if [ $(dpkg-query -W -f='${Status}' libsdl2-mixer-dev 2>/dev/null | grep -c "ok installed") -eq 0 ];
then
 read -p "libsdl2-mixer-dev es necesario para seguir con la instalacion desea instalarlo? (y/n): " -n 1 -r
 echo
 if [[ $REPLY =~ ^[Y|y]$ ]]
 then
	sudo apt-get install libsdl2-mixer-dev
 else exit 1
 fi
fi

if [ $(dpkg-query -W -f='${Status}' qt5-default 2>/dev/null | grep -c "ok installed") -eq 0 ];
then
 read -p "qt5-default es necesario para seguir con la instalacion desea instalarlo? (y/n): " -n 1 -r
 echo
 if [[ $REPLY =~ ^[Y|y]$ ]]
 then
	sudo apt-get install qt5-default
 else exit 1
 fi
fi

if [ ! -d ./build ]; then
	mkdir build
fi

cd build
cmake ..
make

if [ -f /usr/bin/worms-client ]; then
    echo "Detectado binario 'worms-client' de una instalación anterior. Se borrara dicho binario y se volvera a instalar."
	sudo rm /usr/bin/worms-client 
fi

if [ -f /usr/bin/worms-server ]; then
    echo "Detectado binario 'worms-server' de una instalación anterior. Se borrara dicho binario y se volvera a instalar."
	sudo rm /usr/bin/worms-server
fi

if [ -f /usr/bin/worms-editor ]; then
    echo "Detectado binario 'worms-editor' de una instalación anterior. Se borrara dicho binario y se volvera a instalar."
	sudo rm /usr/bin/worms-editor
fi


sudo cp client/worms-client /usr/bin
sudo cp editor/worms-editor /usr/bin
sudo cp server/worms-server /usr/bin

if [ -d /usr/var/worms ]; then
	echo "Detectada anterior instalación de worms en /usr/var/worms. Se borrara dicho directorio y se volvera a instalar."
	sudo rm -fr /usr/var/worms
fi

if [ ! -d /usr/var/worms ]; then
	sudo mkdir -p /usr/var/worms
fi

sudo cp -ar ../resources /usr/var/worms

if [ ! -d /usr/etc/worms ]; then
	sudo mkdir -p /usr/etc/worms 
	sudo mkdir /usr/etc/worms/maps
	sudo chmod -R 777 /usr/etc/worms/maps
fi

sudo cp ../server/server_config.yml /usr/etc/worms

echo "Juego instalado!"
