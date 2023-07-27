#include "HttpServerResponse.hpp"
#include <algorithm>
#include <sstream>
#include <string>

std::string HttpServerResponse::raw_data() const{
    std::stringstream ss;
    ss << "HTTP/1.1 " << m_code << " " << get_response_line(m_code) << "\n";

    for(const auto& h : m_headers){
        ss << h.first << ": " << h.second << "\n";
    }

    ss << "\n" << Data();
    
    return ss.str();
}

HttpServerResponse HttpServerResponse::json(HttpResponseCode _code, const JSON::Node& _data){
    HttpServerResponse res;
    res.set_response_code(_code);
    std::string stringified = _data.stringify();
    res.set_data(stringified);
    res.add_header("Content-Type", "application/json");

    return res;
}

HttpServerResponse HttpServerResponse::text(HttpResponseCode _code, const std::string& _data){
    HttpServerResponse res;
    res.set_response_code(_code);
    res.set_data(_data);
    res.add_header("Content-Type", "text/plain");

    return res;
}