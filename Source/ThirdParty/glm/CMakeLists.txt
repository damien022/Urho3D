cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

set(GLM_VERSION "0.9.9")
project(glm VERSION ${GLM_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES glm *.h *.hpp *.inl)
add_library(glm STATIC ${SOURCE_FILES} INTERFACE.cpp)

option(GLM_ENABLE_FAST_MATH "Enable fast math optimizations" OFF)
if(GLM_ENABLE_FAST_MATH)
	message(STATUS "GLM: Build with fast math optimizations")

	if((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
		target_compile_options(glm PUBLIC -ffast-math)

	elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
		target_compile_options(glm PUBLIC /fp:fast)
	endif()
else()
	if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
		target_compile_options(glm PUBLIC /fp:precise)
	endif()
endif()

option(GLM_ENABLE_SIMD_SSE2 "Enable SSE2 optimizations" OFF)
option(GLM_ENABLE_SIMD_SSE3 "Enable SSE3 optimizations" OFF)
option(GLM_ENABLE_SIMD_AVX "Enable AVX optimizations" OFF)
option(GLM_ENABLE_SIMD_AVX2 "Enable AVX2 optimizations" OFF)
option(GLM_FORCE_PURE "Force 'pure' instructions" OFF)

if(GLM_FORCE_PURE)
	target_compile_definitions(glm PUBLIC -DGLM_FORCE_PURE)

	if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
		target_compile_options(glm PUBLIC -mfpmath=387)
	endif()
	message(STATUS "GLM: No SIMD instruction set")

elseif(GLM_ENABLE_SIMD_AVX2)
	if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
		target_compile_options(glm PUBLIC -mavx2)
	elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
		target_compile_options(glm PUBLIC /QxAVX2)
	elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
		target_compile_options(glm PUBLIC /arch:AVX2)
	endif()
	message(STATUS "GLM: AVX2 instruction set")

elseif(GLM_ENABLE_SIMD_AVX)
	if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
		target_compile_options(glm PUBLIC -mavx)
	elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
		target_compile_options(glm PUBLIC /QxAVX)
	elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
		target_compile_options(glm PUBLIC /arch:AVX)
	endif()
	message(STATUS "GLM: AVX instruction set")

elseif(GLM_ENABLE_SIMD_SSE3)
	if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
		target_compile_options(glm PUBLIC -msse3)
	elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
		target_compile_options(glm PUBLIC /QxSSE3)
	elseif((CMAKE_CXX_COMPILER_ID MATCHES "MSVC") AND NOT CMAKE_CL_64)
		target_compile_options(glm PUBLIC /arch:SSE2) # VC doesn't support /arch:SSE3
	endif()
	message(STATUS "GLM: SSE3 instruction set")

elseif(GLM_ENABLE_SIMD_SSE2)
	if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
		target_compile_options(glm PUBLIC -msse2)
	elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
		target_compile_options(glm PUBLIC /QxSSE2)
	elseif((CMAKE_CXX_COMPILER_ID MATCHES "MSVC") AND NOT CMAKE_CL_64)
		target_compile_options(glm PUBLIC /arch:SSE2)
	endif()
	message(STATUS "GLM: SSE2 instruction set")
endif()

# Compiler and default options

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	message("GLM: Clang - ${CMAKE_CXX_COMPILER_ID} compiler")

	target_compile_options(glm PUBLIC -Werror -Weverything)
	target_compile_options(glm PUBLIC -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-c++11-long-long -Wno-padded -Wno-gnu-anonymous-struct -Wno-nested-anon-types)
	target_compile_options(glm PUBLIC -Wno-undefined-reinterpret-cast -Wno-sign-conversion -Wno-unused-variable -Wno-missing-prototypes -Wno-unreachable-code -Wno-missing-variable-declarations -Wno-sign-compare -Wno-global-constructors -Wno-unused-macros -Wno-format-nonliteral)

elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	message("GLM: GCC - ${CMAKE_CXX_COMPILER_ID} compiler")

	target_compile_options(glm PUBLIC -O2)
	target_compile_options(glm PUBLIC -Wno-long-long)

elseif(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
	message("GLM: Intel - ${CMAKE_CXX_COMPILER_ID} compiler")

elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	message("GLM: Visual C++ - ${CMAKE_CXX_COMPILER_ID} compiler")

	target_compile_options(glm PUBLIC /FAs /W4 /WX)
	target_compile_options(glm PUBLIC /wd4309 /wd4324 /wd4389 /wd4127 /wd4267 /wd4146 /wd4201 /wd4464 /wd4514 /wd4701 /wd4820 /wd4365)
	target_compile_definitions(glm PUBLIC -D_CRT_SECURE_NO_WARNINGS)
endif()

install(DIRECTORY glm/ DESTINATION ${DEST_THIRDPARTY_HEADERS}/glm FILES_MATCHING PATTERN *.h)
install(DIRECTORY glm/ DESTINATION ${DEST_THIRDPARTY_HEADERS}/glm FILES_MATCHING PATTERN *.hpp)
install(DIRECTORY glm/ DESTINATION ${DEST_THIRDPARTY_HEADERS}/glm FILES_MATCHING PATTERN *.inl)
install_to_build_tree(glm)
