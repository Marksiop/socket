#include <iostream>
#include <socket.h>
#include <config.h>



int main()
{
    Socket si;
    Socket::App app; 
    std::pair<std::string, void(*)(Socket::Req&, Socket::Res&)> a;
    a.first = "/"; 
    a.second = [](Socket::Req& req, Socket::Res& res) 
    {
        req.method = std::string{ "GET" };
        res.content_type = Socket::Content_Type::TEXT_HTML;
        res.status_code = 200; 
        res.content = "hello world!";
    }; 
    std::pair<std::string, void(*)(Socket::Req&, Socket::Res&)> b;
    b.first = "/goggle";
    b.second = [](Socket::Req & req, Socket::Res& res)
    {
        req.method = std::string{ "GET" }; 
        res.content_type = Socket::Content_Type::TEXT_HTML; 
        res.status_code = 200; 
        res.content = "hello google";
    };
    std::pair<std::string, void(*)(Socket::Req&, Socket::Res&)> c;
    c.first = "/foo";
    c.second = [](Socket::Req & req, Socket::Res& res)
    {
        req.method = std::string{ "GET" }; 
        res.content_type = Socket::Content_Type::TEXT_HTML; 
        res.status_code = 200; 
        res.content = "boo";
    };
    app.push_back(a);
    app.push_back(b);
    app.push_back(c);

    si.app(&app);
    si.init();
    return 0; 
}