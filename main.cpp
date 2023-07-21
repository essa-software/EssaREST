#include "src/server/BasicServer.hpp"
#include "src/server/HttpServer.hpp"
#include <iostream>

int main(){

    HttpServer server;
    server.set_port(2137);
    server.run();

    return 0;
}