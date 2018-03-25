project( sceneTest )
cmake_minimum_required( VERSION 3.0 )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11"  )

find_package( ASSIMP REQUIRED )

add_subdirectory( Scene )
add_subdirectory( Accelerate )

add_executable( sceneTest "sceneTest.cpp" )
target_link_libraries( sceneTest sceneLib ${ASSIMP_LIBRARIES} )

add_executable( accTest "AccTest.cpp" )
target_link_libraries( accTest sceneLib accelerateLib ${ASSIMP_LIBRARIES} )
