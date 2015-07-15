# Ver >2.6
cmake_minimum_required (VERSION 2.6)
project (lim-db)

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
find_package (FLEX REQUIRED)
find_package (BISON REQUIRED)
flex_target (lexer
	${SOURCE_DIR}/parser/lexer.l
	${SOURCE_DIR}/parser/lexer.cpp
	)
bison_target (parser
	${SOURCE_DIR}/parser/parser.yy
	${SOURCE_DIR}/parser/parser.cpp
	)
add_flex_bison_dependency (lexer parser)

# Header files
set (HEADER_FILES
	# parser
	${SOURCE_DIR}/parser/parser-node.hpp
	${SOURCE_DIR}/parser/command-node.hpp
	${SOURCE_DIR}/parser/statement-node.hpp
	${SOURCE_DIR}/parser/value-node.hpp
	${SOURCE_DIR}/parser/identifier-node.hpp
	${SOURCE_DIR}/parser/operator-node.hpp
	${SOURCE_DIR}/parser/parser-context.hpp

	# base
	${SOURCE_DIR}/base/error-codes.hpp
	${SOURCE_DIR}/base/error-manager.hpp
	${SOURCE_DIR}/base/generic-type-definitions.hpp
	${SOURCE_DIR}/base/generic-constants.hpp
	${SOURCE_DIR}/base/generic-operations.hpp
	${SOURCE_DIR}/base/data-type.hpp
	${SOURCE_DIR}/base/bitmap.hpp
	${SOURCE_DIR}/base/template-class.hpp
	${SOURCE_DIR}/base/serialize.hpp

	#boot
	${SOURCE_DIR}/boot/boot.hpp

	# storage
	${SOURCE_DIR}/storage/sector.hpp
	${SOURCE_DIR}/storage/sector-manager.hpp

	# schema
	${SOURCE_DIR}/schema/attribute.hpp
	${SOURCE_DIR}/schema/table.hpp
	${SOURCE_DIR}/schema/schema-manager.hpp

	# metadata
	${SOURCE_DIR}/metadata/sector-group.hpp

	# flex/bison
	${BISON_parser_OUTPUT_HEADER}
	${SOURCE_DIR}/parser/lexer.hpp
	)

# Source files
set (SOURCE_FILES
	
	# parser
	${SOURCE_DIR}/parser/parser-node.cpp
	${SOURCE_DIR}/parser/command-node.cpp
	${SOURCE_DIR}/parser/statement-node.cpp
	${SOURCE_DIR}/parser/value-node.cpp
	${SOURCE_DIR}/parser/identifier-node.cpp
	${SOURCE_DIR}/parser/operator-node.cpp
	${SOURCE_DIR}/parser/parser-context.cpp

	# base
	${SOURCE_DIR}/base/error-manager.cpp
	${SOURCE_DIR}/base/bitmap.cpp
	${SOURCE_DIR}/base/template-class.cpp
	${SOURCE_DIR}/base/serialize.cpp

	#boot
	${SOURCE_DIR}/boot/boot.cpp

	# storage
	${SOURCE_DIR}/storage/sector.cpp
	${SOURCE_DIR}/storage/sector-manager.cpp
	
	# schema
	${SOURCE_DIR}/schema/attribute.cpp
	${SOURCE_DIR}/schema/table.cpp
	${SOURCE_DIR}/schema/schema-manager.cpp

	# metadata
	${SOURCE_DIR}/metadata/sector-group.cpp

	# flex/bison
	${BISON_parser_OUTPUT_SOURCE}
	${FLEX_lexer_OUTPUTS}
	)

# Unit-testing Header files
set (UNIT_TEST_HEADER_FILES
	${SOURCE_DIR}/unit-test/bitmap-test.hpp
	${SOURCE_DIR}/unit-test/sector-manager-test.hpp
	)

# Unit-testing Source files
set (UNIT_TEST_SOURCE_FILES
	${SOURCE_DIR}/unit-test/bitmap-test.cpp
	${SOURCE_DIR}/unit-test/sector-manager-test.cpp
	)

# Executable targets
add_executable (${BIN_DIR}/lim-db
	${SOURCE_FILES}
	${HEADER_FILES}

	# executable
	${SOURCE_DIR}/executables/lim-db.cpp
	)

add_executable (${BIN_DIR}/unit-test
	${SOURCE_FILES}
	${HEADER_FILES}

	${UNIT_TEST_SOURCE_FILES}
	${UNIT_TEST_HEADER_FILES}

	# executable
	${SOURCE_DIR}/executables/unit-test/unit-test.cpp
	)

# C++11
set_property(TARGET ${BIN_DIR}/lim-db PROPERTY CXX_STANDARD 11)