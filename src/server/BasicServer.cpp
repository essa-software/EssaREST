#include "BasicServer.hpp"
#include <unistd.h>
#include <utility>
#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>

void BasicServer::add_method( const std::string url,  AbstractServerMethod const& method){
    m_hooks.insert(std::make_pair(url, std::move(method)));
}
