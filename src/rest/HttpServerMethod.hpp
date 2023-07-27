#pragma once

#include "AbstractServerMethod.hpp"
#include "HttpClientRequest.hpp"
#include "HttpServerResponse.hpp"
#include <functional>
#include <string>

class HttpServerMethod : public AbstractServerMethod {
    const std::string m_method;
    std::function<HttpServerResponse(HttpServerResponse&)> m_foo;

public:
    HttpServerMethod(const std::string& _uri, const std::string& _method, std::function<HttpServerResponse(HttpServerResponse&)> foo)
        : AbstractServerMethod(_uri)
        , m_method(_method)
        , m_foo(std::move(foo)) { }

    std::string Method() const { return m_method; }
    std::string exec(HttpGETClientRequest& req) const;
};

class HttpGETServerMethod : public HttpServerMethod {
public:
    HttpGETServerMethod(const std::string& _uri, std::function<HttpServerResponse(HttpServerResponse&)> foo)
        : HttpServerMethod(_uri, "GET", std::move(foo)) { }
};
