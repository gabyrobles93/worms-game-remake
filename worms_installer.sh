if [ $(dpkg-query -W -f='${Status}' cmake 2>/dev/null | grep -c "ok installed") -eq 0 ];
then
 echo testeando, no tiene cmake instalado
 command || exit 1
 
fi

echo si tenes cmake 
mkdir build && cd build
cmake ..
make
sudo mv client/worms-client /usr/bin
sudo mv editor/worms-editor /usr/bin
sudo mv server/worms-server /usr/bin
if [ ! -d /usr/var/worms ]; then 
	sudo mkdir -p /usr/var/worms
fi
sudo cp -ar ../resources /usr/var/worms
if [ ! -d /usr/etc/worms ]; then
	sudo mkdir -p /usr/etc/worms 
fi
sudo cp -ar ../server/config.yml /usr/etc/worms
