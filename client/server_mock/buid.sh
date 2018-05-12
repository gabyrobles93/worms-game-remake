#!bin/bash

g++ server_mock_main.cpp ../socket.cpp ../socket_error.cpp ../protocol.cpp -L ../libs/libyaml-cpp.a -o server_mock