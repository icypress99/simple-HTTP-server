cmake_minimum_required(VERSION 3.16)

project(webserver LANGUAGES C)
set(LIBMICROHTTPD_INCLUDE_DIR "C:/mylibs/include")
set(LIBMICROHTTPD_LIBRARY_DIR "C:/mylibs/lib")
include_directories(${LIBMICROHTTPD_INCLUDE_DIR})
link_directories(${LIBMICROHTTPD_LIBRARY_DIR})

# include_directories("C:/mylibs/include")
# link_directories("C:/mylibs/lib")

add_executable(webserver main.c)
target_link_libraries(webserver microhttpd)


include(GNUInstallDirs)
install(TARGETS webserver
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
