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
    const std::map<std::string, std::string>& Headers() const{return m_headers;}
    std::string Uri() const {return m_uri;}
    std::string Body() const {return m_body;}
};

class HttpGETClientRequest : public HttpClientRequest{
    std::map<std::string, std::string> m_get;
public:
    HttpGETClientRequest() = default;
    virtual HttpResponseCode parse(const char* req);
    const std::map<std::string, std::string>& Get() const{return m_get;}

};
