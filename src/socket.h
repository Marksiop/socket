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
    struct RES
    {
        CONTENT_TYPE content_type;
        size_t status_code;
        std::vector<std::pair<std::string, std::string>> headers;
        std::string content; 
    };
    public:      
        using Res = struct RES;
        using Content_Type = CONTENT_TYPE; 
        void init(int port = 3000);
        friend const std::string format(Socket::Res);   

};