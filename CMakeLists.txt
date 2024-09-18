#*****************************************************
# specify minimum version of CMake to use
# (find_package requires 3.23)
#*****************************************************
cmake_minimum_required(VERSION 3.23)

#*****************************************************
project(StarcraftRemastered)
#*****************************************************

#*****************************************************
# add source files
#*****************************************************

SET(APP_SRC_FILES_LIST
    StarcraftRemastered/Source.cpp
	StarcraftRemastered/Engine.h
	StarcraftRemastered/Engine.cpp
	StarcraftRemastered/BattleCruiser.h
	StarcraftRemastered/BattleCruiser.cpp
	StarcraftRemastered/Common.h
	StarcraftRemastered/Race.h
	StarcraftRemastered/Race.cpp
	StarcraftRemastered/Terran.cpp
	StarcraftRemastered/Terran.h
	StarcraftRemastered/Texture.cpp
	StarcraftRemastered/Texture.h
	StarcraftRemastered/Unit.cpp
	StarcraftRemastered/Unit.h
	StarcraftRemastered/vec2.cpp
	StarcraftRemastered/vec2.h
)

#*****************************************************
# Find SFML library (set proper path and run find_package)
#*****************************************************

SET(SFML_DIR "./Dependencies/SFML-2.5.1/lib/cmake/SFML" )
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

#*****************************************************
# generate app exe
#*****************************************************

ADD_EXECUTABLE(StarcraftRemastered ${APP_SRC_FILES_LIST} )

#*****************************************************
# enable multi processor compilation 
#  - for visual "/MP" flag must be set
#*****************************************************

if(MSVC)
    target_compile_options(StarcraftRemastered PRIVATE "/MP")
endif()

#*****************************************************
# tracy
#*****************************************************

#target_compile_definitions(StarcraftRemastered PUBLIC TRACY_ENABLE)

#target_include_directories(StarcraftRemastered PUBLIC "Dependencies/Tracy")

#*****************************************************
# Set language version to C++20
#*****************************************************

set_property(TARGET StarcraftRemastered PROPERTY CXX_STANDARD 20)

#*****************************************************
# Specify which SFML libraries to link with exe
#*****************************************************

target_link_libraries(StarcraftRemastered sfml-graphics sfml-audio)