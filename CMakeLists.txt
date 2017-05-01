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

#GLM options
option(GLM_DYNAMIC_LIBRARY_ENABLE "" OFF)
option(GLM_TEST_ENABLE_FAST_MATH "" ON)
option(GLM_TEST_ENABLE_LANG_EXTENSIONS "" ON)
option(GLM_TEST_ENABLE_SIMD_AVX2 "" ON)
option(GLM_TEST_ENABLE_SIMD_SSE3 "" ON)
download_project(PROJ glm
        GIT_REPOSITORY      https://github.com/g-truc/glm.git
        GIT_TAG              5dcc564
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )
add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
include_directories("${glm_SOURCE_DIR}")

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

download_project(PROJ json
GIT_REPOSITORY      https://github.com/nlohmann/json.git
GIT_TAG             9ff0cc0
${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
include_directories("${json_SOURCE_DIR}/src")

#---------------- ASSIMP
#TODO: go back and enable this, submit bug report
set(ASSIMP_NO_EXPORT ON CACHE BOOL "" FORCE)

set(ASSIMP_BUILD_MDC_IMPORTER OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_3DS_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_AC_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASE_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSBIN_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSXML_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_B3D_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_BVH_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_COLLADA_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_DXF_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_CSM_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_HMP_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_IRRMESH_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_IRR_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_LWO_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_LWS_IMPORTER OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_MD2_IMPORTER OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_MD3_IMPORTER OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_MD5_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_MDC_IMPORTER OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_MDL_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_NFF_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_NDO_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OFF_IMPORTER OFF CACHE BOOL "" FORCE)
#set(ASSIMP_BUILD_OBJ_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OGRE_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_OPENGEX_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_PLY_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_MS3D_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_COB_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_BLEND_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_IFC_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_XGL_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_Q3D_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_Q3BSP_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_RAW_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SIB_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SMD_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_STL_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TERRAGEN_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_3D_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_X_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_GLTF_IMPORTER OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_3MF_IMPORTER OFF CACHE BOOL "" FORCE)


download_project(PROJ assimp
        GIT_REPOSITORY      https://github.com/assimp/assimp
        GIT_TAG             a8673d4
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )
add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
include_directories("${assimp_SOURCE_DIR}/include")

#---------------- ASSIMP

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)
file(GLOB_RECURSE CMP_SOURCE_FILES src/components/*.cpp src/components/*.h)
include_directories("src")
include (GenerateExportHeader)
add_library(sharp_blue STATIC ${SOURCE_FILES})
 GENERATE_EXPORT_HEADER( sharp_blue
                           BASE_NAME sharp_blue
                           EXPORT_MACRO_NAME sharp_blue_EXPORT
                           EXPORT_FILE_NAME sharp_blue_Export.h
                           STATIC_DEFINE sharp_blue_BUILT_AS_STATIC
  )
 source_group("Standard components" FILES ${CMP_SOURCE_FILES})

file(GLOB_RECURSE GAME_SOURCE_FILES game/*.cpp game/*.h)
add_executable(sp_game ${GAME_SOURCE_FILES})
file(GLOB_RECURSE CMP_SOURCE_FILES game/components/*.cpp game/components/*.h)
source_group("Game components" FILES ${CMP_SOURCE_FILES})


set_property(TARGET sp_game PROPERTY CXX_STANDARD 14)
set_property(TARGET sharp_blue PROPERTY CXX_STANDARD 14)

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

	file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/sp_game.vcxproj.user" 
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
  target_link_libraries(sharp_blue SDL2 libglew_shared assimp)
  target_link_libraries(sp_game sharp_blue)
else()
  target_link_libraries(sharp_blue SDL2 libglew_shared assimp)
  target_link_libraries(sp_game sharp_blue)
endif()
add_dependencies(sharp_blue SDL2 libglew_shared assimp)
add_dependencies(sp_game sharp_blue)
