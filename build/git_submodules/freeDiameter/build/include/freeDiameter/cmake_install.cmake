# Install script for directory: /home/gcuba/openair-cn/build/git_submodules/freeDiameter/include/freeDiameter

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "freeDiameter-dev")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/freeDiameter" TYPE FILE FILES
    "/home/gcuba/openair-cn/build/git_submodules/freeDiameter/build/include/freeDiameter/freeDiameter-host.h"
    "/home/gcuba/openair-cn/build/git_submodules/freeDiameter/include/freeDiameter/libfdproto.h"
    "/home/gcuba/openair-cn/build/git_submodules/freeDiameter/include/freeDiameter/libfdcore.h"
    "/home/gcuba/openair-cn/build/git_submodules/freeDiameter/include/freeDiameter/extension.h"
    )
endif()

