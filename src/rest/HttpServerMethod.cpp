#include "HttpServerMethod.hpp"
#include "HttpServerResponse.hpp"
#include <string>

std::string HttpGETServerMethod::exec(const HttpGETClientRequest& req) const{
    HttpServerResponse res;
    
    if(m_foo)
        res = m_foo(req);
    res.add_header("Host", req.Header("Host"));
    res.add_header("Server", "EssaServer");
    res.add_header("Connection", "Keep-Alive");
    // res.add_header("Content-Type", "application/x-www-form-urlencoded");

    time_t now;
    time(&now);
    char buf[256]{0};
    strftime(buf, sizeof buf, "%a, %e %b %Y %T %Z", gmtime(&now));

    res.add_header("Date", buf);
    
    res.add_header("Content-Length", std::to_string(res.Data_Len()));

    return res.raw_data();
}
