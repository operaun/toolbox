set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32 -g -O0")

set(LINKLIBS m EGL gbm skia skia_core skia_images skia_chrome skia_ports views GL client controls base ui base_i18n compositor)

link_directories(/system/lib)

include_directories(/system/include)

add_definitions(-DOS_TOS -DOS_FREEBSD -DOS_POSIX $
                -fcolor-diagnostics -fno-rtti)

add_executable(test_program test_program.cc)
target_link_libraries(test_program ${LINKLIBS})
