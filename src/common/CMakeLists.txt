cmake_minimum_required( VERSION 3.0.2 )
project( Sapphire )

file(GLOB UTILS_SOURCE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Config/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Crypt/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Database/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Exd/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Logging/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Network/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Network/PacketDef/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Script/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Util/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/../../deps/imgui/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/../../deps/imgui/examples/imgui_impl_opengl2.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../deps/imgui/examples/imgui_impl_sdl.cpp")

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

add_library( common ${UTILS_PUBLIC_INCLUDE_FILES} ${UTILS_SOURCE_FILES} )

set_target_properties( common PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/../../bin/"
)

target_link_libraries( common PUBLIC xivdat )

target_link_libraries( common PUBLIC mysqlConnector )
if( UNIX )

  target_link_libraries( common PUBLIC mysqlclient )
  target_link_libraries( common PUBLIC pthread )

else()
  target_link_libraries( common
                           PUBLIC
                             mysql )
endif()

target_include_directories( common
                              PUBLIC
                                "${CMAKE_CURRENT_SOURCE_DIR}/"
                                "${CMAKE_CURRENT_SOURCE_DIR}/../../deps/"
                                "${CMAKE_CURRENT_SOURCE_DIR}/../../deps/asio/asio/include/"
                                "${CMAKE_CURRENT_SOURCE_DIR}/../../deps/spdlog/include/"
								"${CMAKE_CURRENT_SOURCE_DIR}/../../deps/imgui/"
								"${CMAKE_CURRENT_SOURCE_DIR}/../../deps/SDL2/include/"
                              PRIVATE
                                "${CMAKE_CURRENT_SOURCE_DIR}/src/libraries/external/")


if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
  set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../../deps/SDL2/lib/x64/SDL2.lib;${CMAKE_CURRENT_SOURCE_DIR}/../../deps/SDL2/lib/x64/SDL2main.lib")
else ()
  set(SDL2_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../../deps/SDL2/lib/x86/SDL2.lib;${CMAKE_CURRENT_SOURCE_DIR}/../../deps/SDL2/lib/x86/SDL2main.lib")
endif ()

find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

message( ${SDL2_LIBRARIES} )

target_link_libraries( common PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} )