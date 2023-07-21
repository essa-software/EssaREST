#pragma once
#include "AbstractClientRequest.hpp"
#include "EssaUtil/UString.hpp"
#include <map>

class HttpClientRequest : public AbstractClientRequest{
    std::map<std::string, std::string> m_headers;
    std::string m_uri;
    std::string m_body;
public:
    HttpClientRequest() = default;
    virtual HttpResponseCode parse(const char* req);
    std::string operator[](std::string key) const;
    std::string Uri() const {return m_uri;}
    std::string Body() const {return m_body;}
};

class HttpGETClientRequest : public HttpClientRequest{
public:
    HttpGETClientRequest() = default;
    virtual HttpResponseCode parse(const char* req);

};
