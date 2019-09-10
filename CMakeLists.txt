cmake_minimum_required (VERSION 3.0)
project (sr_parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

add_custom_command(
	OUTPUT ${PROJECT_SOURCE_DIR}/lexer.cpp
	COMMAND fa2lexer --src lexer.cpp --tpl expr_lexer.fa2l
)

add_custom_command(
	OUTPUT ${PROJECT_SOURCE_DIR}/Tables.cpp ${PROJECT_SOURCE_DIR}/Expr.h
	COMMAND ecc -g grammar_prueba.txt --src Tables.cpp --hdr Expr.h --alg lr0
)

add_executable(${PROJECT_NAME}
                    src/main.cpp
                    src/ExprLexer.cpp
                    src/Parser.cpp
                    src/Tables.cpp)

target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++ -L/usr/X11/lib -lX11 -lstdc++)