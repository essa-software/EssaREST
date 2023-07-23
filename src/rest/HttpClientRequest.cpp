#include "HttpClientRequest.hpp"
#include "EssaUtil/UString.hpp"
#include <sstream>
#include <string>

HttpResponseCode HttpClientRequest::parse(const char* req){
    std::stringstream ss;
    ss << req;

    std::string method, path, version;
    ss >> method >> path >> version;
    
    m_uri = path;

    if(version != "HTTP/1.1"){
        return HttpResponseCode::HTTPVersionNotSupported;
    }

    std::string line;
    while (std::getline(ss, line)) {
        std::string::size_type pos = line.find(": ");
        if(pos == std::string::npos){
            m_body = ss.str();
        }
        
        std::string header = line.substr(0, pos);
        std::string content = line.substr(pos + 2);

        m_headers[header] = content;
    }

    return HttpResponseCode::OK;
}

HttpResponseCode HttpGETClientRequest::parse(const char* req){
    HttpResponseCode res = HttpClientRequest::parse(req);
    if(res != HttpResponseCode::OK) return res;

    std::stringstream ss;
    ss << req;

    std::string method, path, version;
    ss >> method >> path >> version;

    if(method != "GET"){
        return HttpResponseCode::MethodNotAllowed;
    }

    std::string::size_type pos = path.find('?');

    if(pos != std::string::npos){
        std::string query = path.substr(pos + 1);
        while(true){
            std::string::size_type eq_pos = query.find('=');
            std::string::size_type sep_pos = query.find('&');

            if(eq_pos == std::string::npos) return HttpResponseCode::BadRequest;

            if(sep_pos != std::string::npos){
                m_get.insert({query.substr(0, eq_pos), query.substr(eq_pos+1, sep_pos-eq_pos-1)});
                query = query.substr(sep_pos+1);
            }else{
                m_get.insert({query.substr(0, eq_pos), query.substr(eq_pos+1)});
                break;
            }
        }
    }

    return HttpResponseCode::OK;
}
