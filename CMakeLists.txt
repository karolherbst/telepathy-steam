cmake_minimum_required(VERSION 2.8)
project(telepathy-steam CXX)

include(CheckCXXCompilerFlag)
include(FindPkgConfig)
include(GNUInstallDirs)

# check required compiler flags
check_cxx_compiler_flag("-std=c++11" HAS_CXX11)
if(NOT HAS_CXX11)
  message(FATAL_ERROR "C++11 support required")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# check additional compiler flags
foreach(flag -Werror=switch -Werror=return-type -fvisibility=hidden)
  string(REGEX REPLACE "^-" "" flag_name ${flag})
  check_cxx_compiler_flag(${flag} HAS_${flag_name})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}")
endforeach()

# add some common sense linker flags
foreach(type EXE MODULE SHARED STATIC)
  set(CMAKE_${type}_LINKER_FLAGS "${CMAKE_${type}_LINKER_FLAGS} -Wl,--as-needed -Wl,-z,defs")
endforeach()

# find all required libraries first
pkg_check_modules(DBUS REQUIRED dbus-1)
pkg_check_modules(GOBJECT REQUIRED gobject-2.0)
pkg_check_modules(TP_GLIB REQUIRED telepathy-glib>=0.11.13)

include_directories(
  ${DBUS_INCLUDE_DIRS}
  ${GOBJECT_INCLUDE_DIRS}
  ${TP_GLIB_INCLUDE_DIRS}
)

link_directories(
  ${GOBJECT_LIBRARY_DIRS}
  ${TP_GLIB_LIBRARY_DIRS}
)

add_executable(telepathy-steam
  connection-manager.cpp
  connection.cpp
  main.cpp
  protocol.cpp
# random files not included in IDEs
  glib-helpers.h
  steam.manager
)

target_link_libraries(telepathy-steam
  ${GOBJECT_LIBRARIES}
  ${TP_GLIB_LIBRARIES}
)

install(
  TARGETS telepathy-steam
  DESTINATION ${CMAKE_INSTALL_FULL_LIBEXECDIR}
)

# dbus file
configure_file(steam.service.in org.freedesktop.Telepathy.ConnectionManager.steam.service)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/org.freedesktop.Telepathy.ConnectionManager.steam.service
  DESTINATION ${CMAKE_INSTALL_FULL_DATAROOTDIR}/dbus-1/services
)

# telepathy file
install(
  FILES steam.manager
  DESTINATION ${CMAKE_INSTALL_FULL_DATAROOTDIR}/telepathy/managers
)
