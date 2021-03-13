a web server that will print hello world on the screen 
only for linux users 

Note:
This lib is currently under development you can check the source code and even use it but dn't use it for production purpose 

# use
    git clone https://github.com/notadevps/socket.git
    cd socket
    ./run.sh 

# or install
    sudo ./install.sh
    use SOCKET in command line 
    
# example  
main.cpp file

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
        si.init(3000);
        return 0; 
    }


1. localhost:3000/foo -> will print boo 
2. localhost:3000/google -> will print hello google
3. localhost:3000/ ->  will print hello world

# COMING SOON

1. adding threads
2. adding more content_type and header opt
3. optimization 

