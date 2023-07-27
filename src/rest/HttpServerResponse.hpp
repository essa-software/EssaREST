#pragma once

#include "AbstractServerResponse.hpp"
#include "Defines.hpp"
#include <EssaUtil/Json.hpp>
#include <cstring>
#include <map>
#include <string>

class HttpServerResponse : public AbstractServerResponse{
    std::map<std::string, std::string> m_headers;
    HttpResponseCode m_code;
    void set_response_code(HttpResponseCode _code) {m_code = _code;}
public:
    HttpServerResponse() = default;
    void add_header(const std::string& key, const std::string& val){m_headers[key] = val;};

    static HttpServerResponse json(HttpResponseCode _code, const JSON::Node& _data);
    static HttpServerResponse text(HttpResponseCode _code, const std::string& _data);

    virtual std::string raw_data() const;
    HttpResponseCode response_code() const {return m_code;}
    int Data_Len() const{return Data().size();}
};