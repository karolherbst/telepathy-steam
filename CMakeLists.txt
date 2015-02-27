cmake_minimum_required(VERSION 2.8)
project(telepathy-steam)

include(FindPkgConfig)
include(GNUInstallDirs)

# find all required libraries first

# telepathy-glib
pkg_search_module(TP_GLIB REQUIRED telepathy-glib)

include_directories(
  ${TP_GLIB_INCLUDE_DIRS}
)

link_directories(
  ${TP_GLIB_LIBRARY_DIRS}
)

add_executable(telepathy-steam
  main.cpp
)

target_link_libraries(telepathy-steam
  ${TP_GLIB_LIBRARIES}
)

install(
  TARGETS telepathy-steam
  DESTINATION ${CMAKE_INSTALL_FULL_LIBEXECDIR}
)
