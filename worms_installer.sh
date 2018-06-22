mkdir build && cd build
cmake ..
make
sudo mv client/client /usr/bin
sudo mv editor/editor /usr/bin
sudo mv server/server /usr/bin
if [ ! -d /usr/var/worms ]; then 
	sudo mkdir -p /usr/var/worms
fi
sudo mv ../resources /usr/var/worms
if [ ! -d /usr/etc/worms ]; then
	sudo mkdir -p /usr/etc/worms 
fi
sudo mv ../server/config.yml /usr/etc/worms
