# CMakeList.txt: проект CMake для Plumber; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_TOOLCHAIN_FILE D:/Program\ Files/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "vcpkg toolchain file")
# set(CMAKE_TOOLCHAIN_FILE D:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "vcpkg toolchain file")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Plumber")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Plumber "src/main.cpp" "src/window.h" "src/units.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Plumber PROPERTY CXX_STANDARD 20)
endif()

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)

target_link_libraries(Plumber PRIVATE sfml-main)
target_link_libraries(Plumber PRIVATE CURL::libcurl)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

#install (TARGETS Plumber DESTINATION "Plunber/build")