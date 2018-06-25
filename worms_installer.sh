if [ $(dpkg-query -W -f='${Status}' cmake 2>/dev/null | grep -c "ok installed") -eq 0 ];
then
 echo "cmake necesario para proceder con la instalación."
 command || exit 1
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

if [ ! -d /tmp ]; then
	sudo mkdir -p /tmp
	sudo chmod -R 777 /tmp
fi

sudo cp ../server/server_config.yml /usr/etc/worms
sudo cp -a ../editor/maps/. /usr/etc/worms/maps

echo "Juego instalado!"
