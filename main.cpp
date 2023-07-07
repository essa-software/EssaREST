#include "src/server/BasicServer.hpp"
#include <iostream>

int main(){

    BasicServer server;
    server.set_port(2137);
    server.run();

    return 0;
}