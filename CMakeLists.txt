cmake_minimum_required(VERSION 3.3)

project(Basket)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(CMAKE_BUILD_TYPE Debug)

#set(OSMIUM_INCLUDE_DIRS /usr/include/osmium)

set(OpenGL_GL_PREFERENCE "GLVND")

file (GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/src/*)

add_executable(Basket ${SRC})

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(Bullet REQUIRED)
find_package(OpenAL REQUIRED)
find_package(Freetype REQUIRED)
find_package(SQLite3 REQUIRED)

#add_subdirectory(source/osmium/)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/entities)

include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${GASSIMP_INCLUDE_DIRS})
include_directories(${BULLET_INCLUDE_DIRS})
include_directories(${OPENAL_INCLUDE_DIRS})
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(/usr/include/osmium)

target_link_libraries(Basket
	GL
	GLEW::GLEW
	glfw
	assimp

	BulletDynamics
	BulletCollision
	LinearMath

	openal

	sndfile

	freetype

	sqlite3

	# For osmium :
	pthread
	z
	bz2
	expat
)

