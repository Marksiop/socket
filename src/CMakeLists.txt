add_library(sockets socket.cpp socket.h)

install(TARGETS sockets DESTINATION lib)
install(FILES socket.h DESTINATION include)