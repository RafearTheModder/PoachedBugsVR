cmake_minimum_required(VERSION 3.20)
set(NAME "PoachedBugsVR")

# Find Git executable
find_package(Git QUIET)

# Check if Git is found
if(GIT_FOUND)
    # Get the latest tag
    execute_process(
        COMMAND git describe --tags
        OUTPUT_VARIABLE RAW_VERSION
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )

    # Get the commit hash for the build
    execute_process(
        COMMAND git rev-parse HEAD
        OUTPUT_VARIABLE COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
endif()

if(NOT ${RAW_VERSION} STREQUAL "")
    # Parse version from tag (e.g., v1.2.3)
    string(REGEX MATCH "release/v([0-9]+)\\.([0-9]+)\\.([0-9]+)(\\-)?([0-9]+)?(.+)?" _VERSION_MATCH "${RAW_VERSION}")
    set(PROJECT_VERSION_MAJOR "${CMAKE_MATCH_1}")
    set(PROJECT_VERSION_MINOR "${CMAKE_MATCH_2}")
    set(PROJECT_VERSION_PATCH "${CMAKE_MATCH_3}")
	if(NOT ${CMAKE_MATCH_5} STREQUAL "")
		set(PROJECT_COMMITS_SINCE_TAG ${CMAKE_MATCH_5})
	else()
		set(PROJECT_COMMITS_SINCE_TAG 0)
	endif()
else()
    # Set default version if Git is not found
    set(RAW_VERSION "v0.0.0-experimentalScratchBuild")
    set(PROJECT_VERSION_MAJOR "0")
    set(PROJECT_VERSION_MINOR "0")
    set(PROJECT_VERSION_PATCH "0")
	set(PROJECT_COMMITS_SINCE_TAG 0)
endif()
message(
	STATUS
		"Project version pulled from git tags: ${RAW_VERSION}\n"
		"PROJECT_VERSION_MAJOR: ${PROJECT_VERSION_MAJOR}\n"
		"PROJECT_VERSION_MINOR: ${PROJECT_VERSION_MINOR}\n"
		"PROJECT_VERSION_PATCH: ${PROJECT_VERSION_PATCH}\n"
		"PROJECT_COMMITS_SINCE_TAG: ${PROJECT_COMMITS_SINCE_TAG}\n"
		"COMMIT_HASH: ${COMMIT_HASH}\n"
)
set(VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

# ---- Options ----

option(COPY_BUILD "Copy the build output to the Skyrim directory." OFF)
option(BUILD_SKYRIMVR "Build for Skyrim VR" OFF)

# ---- Cache build vars ----

macro(set_from_environment VARIABLE)
	if (NOT DEFINED ${VARIABLE} AND DEFINED ENV{${VARIABLE}})
		set(${VARIABLE} $ENV{${VARIABLE}})
	endif ()
endmacro()

set_from_environment(VCPKG_ROOT)

macro(find_commonlib_path)
	if (CommonLibName AND NOT ${CommonLibName} STREQUAL "")
		# Check extern
		find_path(CommonLibPath
		include/REL/Relocation.h
		PATHS extern/${CommonLibName})
		if (${CommonLibPath} STREQUAL "CommonLibPath-NOTFOUND")
			#Check path
			set_from_environment(${CommonLibName}Path)
			set(CommonLibPath ${${CommonLibName}Path})
		endif()
	endif()
endmacro()

if(BUILD_SKYRIMVR)
	add_compile_definitions(SKYRIMVR)
	set(CommonLibName "CommonLibVR")
	set_from_environment(SkyrimVRPath)
	set(SkyrimPath ${SkyrimVRPath})
	set(SkyrimVersion "Skyrim VR")
else()
	set(CommonLibName "CommonLibSSE")
	set_from_environment(Skyrim64Path)
	set(SkyrimPath ${Skyrim64Path})
	set(SkyrimVersion "Skyrim SSE")
endif()
find_commonlib_path()
message(
	STATUS
	"Building for ${SkyrimVersion} at ${SkyrimPath} with ${CommonLibName} at ${CommonLibPath}."
)


if (DEFINED VCPKG_ROOT)
	set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
	set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")
else ()
	message(
		WARNING
		"Variable VCPKG_ROOT is not set. Continuing without vcpkg."
	)
endif ()

set(Boost_USE_STATIC_RUNTIME OFF CACHE BOOL "")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "")

# ---- Project ----

project(
	${NAME}
	VERSION ${VERSION}
	LANGUAGES CXX
)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/Version.h.in
	${CMAKE_CURRENT_BINARY_DIR}/include/Version.h
	@ONLY
)

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.rc.in
	${CMAKE_CURRENT_BINARY_DIR}/version.rc
	@ONLY
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(
		FATAL_ERROR
			"In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
	)
endif()

# ---- Globals ----

if (MSVC)
	add_compile_definitions(
		_UNICODE
	)

	if (NOT ${CMAKE_GENERATOR} STREQUAL "Ninja")
		add_compile_options(
			/MP	# Build with Multiple Processes
		)
	endif ()
endif ()

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF)

set(Boost_USE_STATIC_LIBS ON)


# ---- Dependencies ----
if (DEFINED CommonLibPath AND NOT ${CommonLibPath} STREQUAL "" AND IS_DIRECTORY ${CommonLibPath})
	add_subdirectory(${CommonLibPath} ${CommonLibName})
else ()
	message(
		FATAL_ERROR
		"Variable ${CommonLibName}Path is not set or in extern/."
	)
endif()

find_path(CLIB_UTIL_INCLUDE_DIRS "ClibUtil/detail/SimpleIni.h")

# ---- Add source files ----

file(
  GLOB_RECURSE
  SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
  ${CMAKE_CURRENT_BINARY_DIR}/version.rc
)

source_group(
	TREE
		${CMAKE_CURRENT_SOURCE_DIR}
	FILES
		${SOURCES}
)

source_group(
	TREE
		${CMAKE_CURRENT_BINARY_DIR}
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/include/Version.h
)

# ---- Create DLL ----

add_library(
	${PROJECT_NAME}
	SHARED
	${SOURCES}
	${CMAKE_CURRENT_BINARY_DIR}/include/Version.h
	${CMAKE_CURRENT_BINARY_DIR}/version.rc
	.clang-format
	.editorconfig
)

target_compile_features(
	${PROJECT_NAME}
	PRIVATE
		cxx_std_23
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CLIB_UTIL_INCLUDE_DIRS}
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		${CommonLibName}::${CommonLibName}
)

target_precompile_headers(
	${PROJECT_NAME}
	PRIVATE
		src/PCH.h
)

if (MSVC)
	target_compile_options(
		${PROJECT_NAME}
		PRIVATE
			/sdl             # Enable Additional Security Checks
			/utf-8           # Set Source and Executable character sets to UTF-8
			/Zi              # Debug Information Format

			/permissive-     # Standards conformance
			/Zc:preprocessor # Enable preprocessor conformance mode

			/wd4200          # nonstandard extension used : zero-sized array in struct/union

			"$<$<CONFIG:DEBUG>:>"
			"$<$<CONFIG:RELEASE>:/Zc:inline;/JMC-;/Ob3>"
	)

	target_link_options(
		${PROJECT_NAME}
		PRIVATE
			"$<$<CONFIG:DEBUG>:/INCREMENTAL;/OPT:NOREF;/OPT:NOICF>"
			"$<$<CONFIG:RELEASE>:/INCREMENTAL:NO;/OPT:REF;/OPT:ICF;/DEBUG:FULL>"
	)
endif ()

# ---- Post build ----

if (COPY_BUILD)
	if (DEFINED SkyrimPath)
		add_custom_command(
			TARGET ${PROJECT_NAME}
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${SkyrimPath}/Data/SKSE/Plugins/
			COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_PDB_FILE:${PROJECT_NAME}> ${SkyrimPath}/Data/SKSE/Plugins/
		)
	else ()
		message(
			WARNING
			"Variable ${SkyrimPath} is not defined. Skipping post-build copy command."
		)
	endif ()
endif ()
