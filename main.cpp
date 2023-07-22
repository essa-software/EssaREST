#include "src/server/BasicServer.hpp"
#include "src/server/HttpServer.hpp"
#include "src/utils/HtmlBuilder.hpp"
#include <iostream>
#include <string_view>

int main(){

    // auto html = HtmlBuilder("Bajo jajo",Element("div", 
    //      Attributes(Value("id", "abc"), Value("class", "headers")), 
    //     "Bajo Jajo"));

    // std::cout << html.size() << "\n";

    HttpServer server;
    server.set_port(2137);
    server.run();

    return 0;
}