#pragma once
#include "AbstractClientRequest.hpp"
#include "EssaUtil/UString.hpp"
#include <map>
#include <string>

class HttpClientRequest : public AbstractClientRequest{
    std::map<std::string, std::string> m_headers;
    std::string m_uri;
    std::string m_body;
public:
    HttpClientRequest() = default;
    virtual HttpResponseCode parse(const char* req);
    std::string Header(const std::string& key)const{return m_headers.find(key)->second;}
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
