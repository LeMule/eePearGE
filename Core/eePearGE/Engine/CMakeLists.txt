project(Engine)
message(STATUS "Configuring eePearGE/${PROJECT_NAME}...")

include_directories(include
					../../../ThirdParty/SDL2-2.0.12/include
					../../../ThirdParty/tinyxml2)

#---------------------------------------
# Link libraries
#---------------------------------------
link_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../../../ThirdParty/SDL2-2.0.12/lib/x64
)

#---------------------------------------
# Source/headers
#---------------------------------------
file(GLOB SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB PRIVATE_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/*.h)
list(SORT SOURCE_FILES)

#---------------------------------------
# Create the Executable
#---------------------------------------
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${PUBLIC_HEADERS} ${PRIVATE_HEADERS})
target_link_libraries(${PROJECT_NAME} 
						PUBLIC SDL2 
						PUBLIC SDL2main
						PUBLIC OpenGL32)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
