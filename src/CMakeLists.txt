add_library(sockets socket.h socket.cpp )

install(TARGETS sockets DESTINATION lib)
install(FILES socket.h DESTINATION include)