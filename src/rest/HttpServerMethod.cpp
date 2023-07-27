#include "HttpServerMethod.hpp"
#include "HttpServerResponse.hpp"
#include <string>

std::string HttpServerMethod::exec(HttpGETClientRequest& req) const{
    HttpServerResponse res(Uri());
    res.add_header("Host", req.Header("Host"));
    
    if(m_foo)
        res = m_foo(res);
    
    res.add_header("Content-Length", std::to_string(res.Data_Len()));

    return res.raw_data();
}
