cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
project(Sharp_Blue)
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})
foreach (config ${CMAKE_CONFIGURATION_TYPES})
  string (TOUPPER ${config} config)
  set_target_properties(${_project} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}"
    ARCHIVE_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}"
    LIBRARY_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}"
    #PDB_OUTPUT_DIRECTORY_${config} ${sym_path}
    VS_INTERMEDIATE_DIRECTORY_${config} "temp"
  )
  SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}")
  SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}")
  SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}")
  SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}")
  SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}")
  SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config} "${OUTPUT_DIRECTORY}/${config}")
  SET( VS_INTERMEDIATE_DIRECTORY_${config} "temp/${config}")
  link_directories("${OUTPUT_DIRECTORY}/${config}")
endforeach ()

include(DownloadProject.cmake)

download_project(PROJ SDL
  URL      https://www.libsdl.org/release/SDL2-2.0.5.zip
  ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
add_subdirectory(${SDL_SOURCE_DIR} ${SDL_BINARY_DIR})
include_directories("${SDL_SOURCE_DIR}/include")
#link_directories(${SDL_BINARY_DIR}/lib)


#GLEW options
option(BUILD_UTILS "" OFF)
option(BUILD_SHARED_LIBS "" ON)
option(glew-cmake_BUILD_MULTI_CONTEXT "" OFF)
option(glew-cmake_BUILD_SHARED "" ON)
option(glew-cmake_BUILD_SINGLE_CONTEXT "" ON)
option(glew-cmake_BUILD_STATIC "" OFF)
download_project(PROJ glew
        GIT_REPOSITORY      https://github.com/Perlmint/glew-cmake.git
        GIT_TAG             7be0923
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )
add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR})
include_directories("${glew_SOURCE_DIR}/include")



file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)
include_directories("src")
add_library(sharp_blue ${SOURCE_FILES})

file(GLOB_RECURSE GAME_SOURCE_FILES game/*.cpp game/*.h)
add_executable(sp_game ${GAME_SOURCE_FILES})

#copy General resources to build post build script
add_custom_command(TARGET sharp_blue POST_BUILD  
  COMMAND ${CMAKE_COMMAND} -E copy_directory  "${PROJECT_SOURCE_DIR}/res" $<TARGET_FILE_DIR:sharp_blue>/res)

if(${MSVC})
  #set outDir as debugging directory
  #This doesn't work yet?
  #set_target_properties(sharp_blue PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(TargetDir)")
  
  file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/sharp_blue.vcxproj.user" 
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>
    <Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">
      <LocalDebuggerWorkingDirectory>$(TargetDir)</LocalDebuggerWorkingDirectory>
      <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">
      <LocalDebuggerWorkingDirectory>$(TargetDir)</LocalDebuggerWorkingDirectory>
      <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
    </PropertyGroup>
  </Project>")
		
  target_compile_options(sharp_blue PUBLIC /MP)
  target_link_libraries(sharp_blue SDL2 libglew_shared)
else()
  target_link_libraries(sharp_blue SDL2 libglew_shared)
  target_link_libraries(sp_game sharp_blue)
endif()
add_dependencies(sharp_blue SDL2 libglew_shared)
add_dependencies(sp_game sharp_blue)
