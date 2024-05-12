cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Server_lab5")

add_executable (Server_lab5 
"Source/main.cpp" 
"Include/Server.h" 
"Source/Server.cpp" 
"include/Logger.h" 
"source/ClientHandler.cpp" 
"include/ClientHandler.h" 
"source/sendWebList.cpp" 
"include/sendWebList.h"
 "source/Logger.cpp"  "source/FunctionsServer/gaussian.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Server_lab5 PROPERTY CXX_STANDARD 20)
endif()
