add_library(sockets socket.cpp socket.h utils.h)

install(TARGETS sockets DESTINATION lib)
install(FILES socket.h DESTINATION include)