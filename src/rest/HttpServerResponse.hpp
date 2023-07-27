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
    HttpServerResponse(std::string _uri) : AbstractServerResponse(_uri){
        add_header("Server", "EssaServer");
        add_header("Connection", "Keep-Alive");
        add_header("Content-Type", "application/x-www-form-urlencoded");


        time_t now;
        time(&now);
        char buf[256]{0};
        strftime(buf, sizeof buf, "%a, %e %b %Y %T %Z", gmtime(&now));

        add_header("Date", buf);
    };
    void add_header(const std::string& key, const std::string& val){m_headers[key] = val;};

    HttpServerResponse& json(HttpResponseCode _code, const JSON::Node& _data);
    HttpServerResponse& text(HttpResponseCode _code, const std::string& _data);

    virtual std::string raw_data() const;
    HttpResponseCode response_code() const {return m_code;}
    int Data_Len() const{return Data().size();}
};