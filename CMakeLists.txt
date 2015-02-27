cmake_minimum_required(VERSION 2.8)
project(telepathy-steam)

include(FindPkgConfig)
include(GNUInstallDirs)

# fine all required libraries first

# telepathy-glib
pkg_check_modules(TP_GLIB REQUIRED telepathy-glib)
