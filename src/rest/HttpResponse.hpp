#pragma once

#include "AbstractServerResponse.hpp"
#include <map>
#include <string>
class HttpResponse : public AbstractServerResponse{
    std::map<std::string, std::string> m__headers;
public:
    HttpResponse(std::string _uri) : AbstractServerResponse(_uri){}

    void add_header(const std::string& key, const std::string& value);
    HttpResponse& Json();
};