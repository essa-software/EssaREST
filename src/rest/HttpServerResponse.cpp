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

HttpServerResponse& HttpServerResponse::json(HttpResponseCode _code, const JSON::Node& _data){
    m_code = _code;
    std::string stringified = _data.stringify();
    set_data(stringified);
    add_header("Content-Type", "application/json");

    return *this;
}

HttpServerResponse& HttpServerResponse::text(HttpResponseCode _code, const std::string& _data){
    m_code = _code;
    set_data(_data);
    add_header("Content-Type", "text/plain");

    return *this;
}