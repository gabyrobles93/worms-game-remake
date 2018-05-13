#!bin/bash

g++ server_mock_main.cpp ../src/socket.cpp ../src/socket_error.cpp ../src/protocol.cpp ../src/protocol_error.cpp -L ../libs/libyaml-cpp.a -o server_mock
