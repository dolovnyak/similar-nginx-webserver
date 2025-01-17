cmake_minimum_required(VERSION 3.16)
project(web-server)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D STDOUT_LOG_LEVEL=6 -D FILE_LOG_LEVEL=6")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

################################################################################
# web-server-lib target
################################################################################
set(WS_LIB ${PROJECT_NAME}-lib)
add_library(${WS_LIB}
        srcs/config/Config.cpp
        srcs/config/ConfigParser.cpp
        srcs/sessions/HttpSession/HttpSession.cpp
        srcs/sessions/EndpointSession/EndpointSession.cpp
        srcs/http/Request/AutoindexHandler.cpp
        srcs/http/Request/RequestParser.cpp
        srcs/http/Request/RequestHandler.cpp
        srcs/http/Request/CgiHandler.cpp
        srcs/http/errors/ErrorPages.cpp
        srcs/http/Http.cpp
        srcs/utilities/utilities.cpp
        )

target_include_directories(${WS_LIB} PUBLIC
        srcs
        srcs/config
        srcs/utilities
        srcs/cgi
        srcs/webserver
        srcs/sessions
        srcs/sessions/HttpSession
        srcs/sessions/EndpointSession
        srcs/http
        srcs/http/errors
        srcs/http/Request
        )

target_compile_definitions(${WS_LIB} PUBLIC -D_DEBUG)

# Boost asio
set(Boost_INCLUDE_DIR libs/boost_1_81_0)
target_include_directories(${WS_LIB} PUBLIC ${Boost_INCLUDE_DIR})

# Openssl library
set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl)
set(OPENSSL_LIBRARIES /opt/homebrew/opt/openssl/lib)
find_package(OpenSSL REQUIRED)

target_include_directories(${WS_LIB} PUBLIC ${OPENSSL_INCLUDE_DIR})
target_link_libraries(${WS_LIB} LINK_PUBLIC
        ${OPENSSL_SSL_LIBRARY}
        ${OPENSSL_CRYPTO_LIBRARY})

# Logging library
set(CppLog_INCLUDE_DIR ./libs/CppLog/include)
target_include_directories(${WS_LIB} PUBLIC ${CppLog_INCLUDE_DIR})

################################################################################
# web-server target
################################################################################
add_executable(${PROJECT_NAME}
        srcs/main.cpp
        srcs/http/Request/AutoindexHandler.h)
target_link_libraries(${PROJECT_NAME} PUBLIC ${WS_LIB})

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
        )

################################################################################
# tests
################################################################################
set(WS_TESTS ${PROJECT_NAME}-tests)
add_subdirectory(libs/googletest)

add_executable(${WS_TESTS}
        tests/test_utilities.cpp
        tests/test_fsm_handle_request.cpp
        )

target_link_libraries(${WS_TESTS}
        gtest
        gtest_main
        ${WS_LIB})

target_include_directories(${WS_TESTS} PUBLIC
        googletest/googletest/include
        )
