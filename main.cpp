#include "src/rest/Defines.hpp"
#include "src/rest/HttpClientRequest.hpp"
#include "src/server/BasicServer.hpp"
#include "src/server/HttpServer.hpp"
#include "src/utils/HtmlBuilder.hpp"
#include <EssaUtil/Json.hpp>
#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

int main(){
    HttpServer server;
    server.set_port(2137);
    server.add_get_method("/", [](const HttpGETClientRequest&) -> HttpServerResponse{
        return HttpServerResponse::text(OK, "Working!");
    });
    server.add_get_method("/xd", [](const HttpGETClientRequest&) -> HttpServerResponse{
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

        return HttpServerResponse::json(OK, json);
    });

    server.add_get_method("/bajojajo", [](const HttpGETClientRequest& req) -> HttpServerResponse{
        std::stringstream ss;
        for(const auto& g : req.Get()){
            ss << g.first << " -> " << g.second << "\n";
        }
        return HttpServerResponse::text(OK, ss.str());
    });

    server.run();

    return 0;
}