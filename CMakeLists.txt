# Ver >2.6
cmake_minimum_required (VERSION 2.6)
project (lim-db)

# Version
set (VERSION_MAJOR 0)
set (VERSION_MINOR 1)

# Directories
set (SOURCE_DIR src)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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

# Parser files
set (SRC_PARSER_FILES
	${SOURCE_DIR}/parser/parser-context.hpp
	${SOURCE_DIR}/parser/parser-context.cpp

	${SOURCE_DIR}/parser/parser-node.hpp
	${SOURCE_DIR}/parser/parser-node.cpp

	${SOURCE_DIR}/parser/parser-root.hpp
	${SOURCE_DIR}/parser/parser-root.cpp

	${SOURCE_DIR}/parser/parser-alter-table.hpp
	${SOURCE_DIR}/parser/parser-alter-table.cpp

	${SOURCE_DIR}/parser/parser-column.hpp
	${SOURCE_DIR}/parser/parser-column.cpp

	${SOURCE_DIR}/parser/parser-command.hpp
	${SOURCE_DIR}/parser/parser-command.cpp

	${SOURCE_DIR}/parser/parser-create-table.hpp
	${SOURCE_DIR}/parser/parser-create-table.cpp

	${SOURCE_DIR}/parser/parser-delete.hpp
	${SOURCE_DIR}/parser/parser-delete.cpp

	${SOURCE_DIR}/parser/parser-drop-table.hpp
	${SOURCE_DIR}/parser/parser-drop-table.cpp

	${SOURCE_DIR}/parser/parser-identifier.hpp
	${SOURCE_DIR}/parser/parser-identifier.cpp

	${SOURCE_DIR}/parser/parser-index.hpp
	${SOURCE_DIR}/parser/parser-index.cpp

	${SOURCE_DIR}/parser/parser-insert.hpp
	${SOURCE_DIR}/parser/parser-insert.cpp

	${SOURCE_DIR}/parser/parser-select.hpp
	${SOURCE_DIR}/parser/parser-select.cpp

	${SOURCE_DIR}/parser/parser-table.hpp
	${SOURCE_DIR}/parser/parser-table.cpp

	${SOURCE_DIR}/parser/parser-update.hpp
	${SOURCE_DIR}/parser/parser-update.cpp

	${SOURCE_DIR}/parser/parser-value.hpp
	${SOURCE_DIR}/parser/parser-value.cpp

	# flex/bison
	${BISON_parser_OUTPUT_HEADER}
	${BISON_parser_OUTPUT_SOURCE}
	${FLEX_lexer_OUTPUTS}
	${SOURCE_DIR}/parser/lexer.hpp
	)
source_group("src\\parser" FILES ${SRC_PARSER_FILES})

set (SRC_PARSER_EXPRESSION_FILES
	${SOURCE_DIR}/parser/expression/parser-expression.hpp
	${SOURCE_DIR}/parser/expression/parser-expression.cpp
	
	${SOURCE_DIR}/parser/expression/parser-expression-arithmetic.hpp
	${SOURCE_DIR}/parser/expression/parser-expression-arithmetic.cpp

	${SOURCE_DIR}/parser/expression/parser-expression-compare.hpp
	${SOURCE_DIR}/parser/expression/parser-expression-compare.cpp

	${SOURCE_DIR}/parser/expression/parser-expression-logical.hpp
	${SOURCE_DIR}/parser/expression/parser-expression-logical.cpp
	)
source_group("src\\parser\\expression" FILES ${SRC_PARSER_EXPRESSION_FILES})

set (SRC_BASE_FILES
	${SOURCE_DIR}/base/bitmap.hpp
	${SOURCE_DIR}/base/bitmap.cpp

	${SOURCE_DIR}/base/data-type.hpp

	${SOURCE_DIR}/base/error-codes.hpp

	${SOURCE_DIR}/base/error-manager.hpp
	${SOURCE_DIR}/base/error-manager.cpp

	${SOURCE_DIR}/base/generic-constants.hpp

	${SOURCE_DIR}/base/generic-operations.hpp

	${SOURCE_DIR}/base/generic-type-definitions.hpp
	
	${SOURCE_DIR}/base/serializable.hpp
	${SOURCE_DIR}/base/serializable.cpp

	${SOURCE_DIR}/base/template-class.hpp
	${SOURCE_DIR}/base/template-class.cpp
	)
source_group("src\\base" FILES ${SRC_BASE_FILES})

set (SRC_BOOT_FILES
	${SOURCE_DIR}/boot/boot.hpp
	${SOURCE_DIR}/boot/boot.cpp
	)
source_group("src\\boot" FILES ${SRC_BOOT_FILES})

set (SRC_STORAGE_FILES
	${SOURCE_DIR}/storage/data-sector.hpp
	${SOURCE_DIR}/storage/data-sector.cpp

	${SOURCE_DIR}/storage/row-data.hpp
	${SOURCE_DIR}/storage/row-data.cpp

	${SOURCE_DIR}/storage/sector.hpp
	${SOURCE_DIR}/storage/sector.cpp

	${SOURCE_DIR}/storage/sector-manager.hpp
	${SOURCE_DIR}/storage/sector-manager.cpp
	)
source_group("src\\storage" FILES ${SRC_STORAGE_FILES})

set (SRC_SCHEMA_FILES
	${SOURCE_DIR}/schema/attribute.hpp
	${SOURCE_DIR}/schema/attribute.cpp

	${SOURCE_DIR}/schema/schema-manager.hpp
	${SOURCE_DIR}/schema/schema-manager.cpp

	${SOURCE_DIR}/schema/table.hpp
	${SOURCE_DIR}/schema/table.cpp
	)
source_group("src\\schema" FILES ${SRC_SCHEMA_FILES})

set (SRC_METADATA_FILES
	${SOURCE_DIR}/metadata/sector-group.hpp
	${SOURCE_DIR}/metadata/sector-group.cpp

	${SOURCE_DIR}/metadata/database-value.hpp
	${SOURCE_DIR}/metadata/database-value.cpp

	${SOURCE_DIR}/metadata/bool-database-value.hpp
	${SOURCE_DIR}/metadata/bool-database-value.cpp

	${SOURCE_DIR}/metadata/int-database-value.hpp
	${SOURCE_DIR}/metadata/int-database-value.cpp

	${SOURCE_DIR}/metadata/float-database-value.hpp
	${SOURCE_DIR}/metadata/float-database-value.cpp

	${SOURCE_DIR}/metadata/string-database-value.hpp
	${SOURCE_DIR}/metadata/string-database-value.cpp
	)
source_group("src\\metadata" FILES ${SRC_METADATA_FILES})

# Unit-testing Header files
set (UNIT_TEST_HEADER_FILES
	${SOURCE_DIR}/unit-test/bitmap-test.hpp
	${SOURCE_DIR}/unit-test/sector-manager-test.hpp
	${SOURCE_DIR}/unit-test/data-sector-test.hpp
	)

# Unit-testing Source files
set (UNIT_TEST_SOURCE_FILES
	${SOURCE_DIR}/unit-test/bitmap-test.cpp
	${SOURCE_DIR}/unit-test/sector-manager-test.cpp
	${SOURCE_DIR}/unit-test/data-sector-test.cpp
	)

add_library(lim-db
			${SRC_PARSER_FILES}
			${SRC_PARSER_EXPRESSION_FILES}
			${SRC_BASE_FILES}
			${SRC_BOOT_FILES}
			${SRC_STORAGE_FILES}
			${SRC_SCHEMA_FILES}
			${SRC_METADATA_FILES})

# Executable targets
add_executable (lim-db-console
				# executable
				${SOURCE_DIR}/executables/lim-db.cpp
				)
target_link_libraries (lim-db-console lim-db)

add_executable (unit-test
				${UNIT_TEST_SOURCE_FILES}
				${UNIT_TEST_HEADER_FILES}

				# executable
				${SOURCE_DIR}/executables/unit-test/unit-test.cpp
				)
target_link_libraries(unit-test lim-db)

set_property(TARGET lim-db PROPERTY FOLDER "libraries")
set_property(TARGET lim-db-console PROPERTY FOLDER "executables")
set_property(TARGET unit-test PROPERTY FOLDER "executables")

# C++11
set_property(TARGET lim-db PROPERTY CXX_STANDARD 11)