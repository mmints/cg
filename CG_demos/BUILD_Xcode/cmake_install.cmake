# Install script for directory: /Users/mark/Development/cg/CG_demos/src

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
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/libraries/CG1_Tools/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/libraries/CVK_1_Minimal/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/libraries/SimpleImage/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/01_Start/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/02_DrawLine/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/02_Put_Pixel/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/02_Sierpinski/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/03_PolygonClipping/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/04_SimpleShader/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/04_Solution/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/05_Das_Haus_Vom_Nikolaus/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/05_Solution/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/06_Solution/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/06_Terrain/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/07_MultipleViewports/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/07_Solution/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/08_Phong/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/08_Solution/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/09_FlightSimulator/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/09_Solution/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/10_Balloonflight/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/11_Raytracer/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/executables/11_Solution/cmake_install.cmake")
  include("/Users/mark/Development/cg/CG_demos/BUILD_Xcode/shaders/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/mark/Development/cg/CG_demos/BUILD_Xcode/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
