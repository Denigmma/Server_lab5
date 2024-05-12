cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Server")

add_executable (Server
"Source/main.cpp" 
"Include/Server.h" 
"Source/Server.cpp" 
"include/Logger.h" 
"source/Logger.cpp" 
"source/ClientHandler.cpp" 
"include/ClientHandler.h" 
"source/sendLists.cpp" 
"include/sendLists.h" 
"source/FunctionsServer/gauss.cpp"
"source/SendGetFile.cpp" 
"source/FunctionsServer/align.cpp" 
"source/FunctionsServer/rotate.cpp" 
"include/FunctionsServerh/align.h" 
"include/FunctionsServerh/rotate.h"
"include/FunctionsServerh/blackwhite.h"
"source/FunctionsServer/blackwhite.cpp" 
"include/FunctionsServerh/stb_image_write.h"
"include/FunctionsServerh/stb_image.h"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Server PROPERTY CXX_STANDARD 20)
endif()
