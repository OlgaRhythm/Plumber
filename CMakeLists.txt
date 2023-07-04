cmake_minimum_required (VERSION 3.8)
# set(CMAKE_TOOLCHAIN_FILE E:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "vcpkg toolchain file")
# set(CMAKE_TOOLCHAIN_FILE D:/Program\ Files/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "vcpkg toolchain file")

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Plumber")
add_executable (Plumber "src/main.cpp" "src/window.h" "src/units.h" "src/objects.cpp" "src/creatures.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Plumber PROPERTY CXX_STANDARD 17)
  set_property(TARGET Plumber PROPERTY CXX_STANDARD_REQUIRED ON)
endif()

# find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# target_link_libraries(Plumber PRIVATE sfml-main)

target_link_libraries(Plumber ${CMAKE_SOURCE_DIR}/lib/sfml-graphics.lib)
target_link_libraries(Plumber ${CMAKE_SOURCE_DIR}/lib/sfml-window.lib)
target_link_libraries(Plumber ${CMAKE_SOURCE_DIR}/lib/sfml-system.lib)

include_directories(${CMAKE_SOURCE_DIR}/inc)
