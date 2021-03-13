#pragma once 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string> 
#include <vector>
#include <ctime>

class Socket
{
    struct sockaddr_in addr;
    enum class CONTENT_TYPE
    {
        TEXT_HTML, 
    }; 
    struct REQ
    {
        std::string path;
        std::string method; 
        std::string host;
    };
    struct RES
    {
        CONTENT_TYPE content_type;
        size_t status_code;
        std::vector<std::pair<std::string, std::string>> headers;
        std::string content; 
    };
    char buffer[1024];
    std::vector<std::pair<std::string, void (*)(REQ&, RES&)>> APP;
    public:      
        using Res = struct RES;
        using Content_Type = CONTENT_TYPE; 
        using Req = struct REQ; 
        using App = std::vector<std::pair<std::string, void (*)(REQ&, RES&)>>;  
        void init(int port = 3000); 
        void app(const App*);
        friend const std::string format(const Socket::Res&, const Socket::Req&);   

};