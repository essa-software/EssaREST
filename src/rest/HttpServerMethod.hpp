#pragma once

#include "AbstractServerMethod.hpp"
#include "HttpClientRequest.hpp"
#include "HttpServerResponse.hpp"
#include <functional>
#include <string>

class HttpServerMethod : public AbstractServerMethod {
    const std::string m_method;

public:
    HttpServerMethod(const std::string& _uri, const std::string& _method)
        : AbstractServerMethod(_uri)
        , m_method(_method){ }

    std::string Method() const { return m_method; }
};

class HttpGETServerMethod : public HttpServerMethod {
    std::function<HttpServerResponse(const HttpGETClientRequest&)> m_foo;
public:
    HttpGETServerMethod(const std::string& _uri, std::function<HttpServerResponse(const HttpGETClientRequest&)> foo)
        : HttpServerMethod(_uri, "GET"),  m_foo(std::move(foo)) { }
    
    std::string exec(const HttpGETClientRequest& req) const;
};
