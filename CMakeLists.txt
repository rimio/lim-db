# Ver >2.6
cmake_minimum_required (VERSION 2.6)
project (lim-db)

# Flags (C++ standard 11, GDB debugging symbols)
add_definitions (-std=c++11)

# Version
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

# Directories
set (SOURCE_DIR src)
set (BUILD_DIR build)
set (BIN_DIR ${BUILD_DIR}/bin)

# Include directories
include_directories (
	${SOURCE_DIR}
	)

# Config file
configure_file (
	${SOURCE_DIR}/configure.hpp.in
	${SOURCE_DIR}/configure.hpp
	)

# Lexer and parser targets
#find_package (FLEX REQUIRED)
#find_package (BISON REQUIRED)
#flex_target (lexer ${SOURCE_DIR}/parser/lexer.l ${SOURCE_DIR}/parser/lexer.cc)
#bison_target (parser ${SOURCE_DIR}/parser/parser.yy ${SOURCE_DIR}/parser/parser.cc)
#add_flex_bison_dependency (lexer parser)

# Header files
set (HEADER_FILES
	)

# Source files
set (SOURCE_FILES
	${SOURCE_DIR}/executables/lim-db.cpp
	)

# Executable targets
add_executable (${BIN_DIR}/lim-db
	${SOURCE_FILES}
	${HEADER_FILES}
	)