if(NOT EXISTS "/home/dangminh214/Visual Computing/OpenGL_Praktikum_Framework/OpenGL_Praktikum/cmake-build-debug/libs/glm-master/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: /home/dangminh214/Visual Computing/OpenGL_Praktikum_Framework/OpenGL_Praktikum/cmake-build-debug/libs/glm-master/install_manifest.txt")
endif(NOT EXISTS "/home/dangminh214/Visual Computing/OpenGL_Praktikum_Framework/OpenGL_Praktikum/cmake-build-debug/libs/glm-master/install_manifest.txt")

if (NOT DEFINED CMAKE_INSTALL_PREFIX)
  set (CMAKE_INSTALL_PREFIX "/usr/local")
endif ()
 message(${CMAKE_INSTALL_PREFIX})

file(READ "/home/dangminh214/Visual Computing/OpenGL_Praktikum_Framework/OpenGL_Praktikum/cmake-build-debug/libs/glm-master/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  message(STATUS "Uninstalling $ENV{DESTDIR}${file}")
  if(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    exec_program(
      "/home/dangminh214/CLion/CLion-2023.1.1/clion-2023.1.1/bin/cmake/linux/x64/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    if(NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing $ENV{DESTDIR}${file}")
    endif(NOT "${rm_retval}" STREQUAL 0)
  else(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    message(STATUS "File $ENV{DESTDIR}${file} does not exist.")
  endif(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
endforeach(file)
