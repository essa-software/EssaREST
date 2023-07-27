#include "src/rest/Defines.hpp"
#include "src/server/BasicServer.hpp"
#include "src/server/HttpServer.hpp"
#include "src/utils/HtmlBuilder.hpp"
#include <EssaUtil/Json.hpp>
#include <iostream>
#include <string_view>
#include <vector>

int main(){
    HttpServer server;
    server.set_port(2137);
    server.add_get_method("/", [](HttpServerResponse& res) -> HttpServerResponse{
        return res.text(OK, "Working!");
    });
    server.add_get_method("/xd", [](HttpServerResponse& res) -> HttpServerResponse{
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

        return res.json(OK, json);
    });

    server.run();

    return 0;
}