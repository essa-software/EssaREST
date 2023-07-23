#include "src/server/BasicServer.hpp"
#include "src/server/HttpServer.hpp"
#include "src/utils/HtmlBuilder.hpp"
#include "src/utils/Json.hpp"
#include <iostream>
#include <string_view>
#include <vector>

int main(){

    // auto html = HtmlBuilder("Bajo jajo",Element("div", 
    //      Attributes(Value("id", "abc"), Value("class", "headers")), 
    //     "Bajo Jajo"));

    // std::cout << html.size() << "\n";

    JSON::Node json({
        {"abc", 1},
        {"def", true},
        {"ghi", JSON::Array({
            1, 
            "cos", 
            JSON::Node({
                {"aaa", false}
                })
        })},
        {"jkl", JSON::Node({
            {"mno", 2.5}
        })}
    });

    std::cout << json.stringify() << "\n";
    auto a = JSON::Marshall(json.stringify());

    std::cout << a.stringify() << "\n";

    HttpServer server;
    server.set_port(2137);
    server.run();

    return 0;
}