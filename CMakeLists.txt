project( sceneTest )
cmake_minimum_required( VERSION 3.0 )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11"  )

find_package( ASSIMP REQUIRED )
find_package( OpenCV REQUIRED )

add_subdirectory( Scene )
add_subdirectory( Accelerate )
add_subdirectory( Ray )
add_subdirectory( Camera )
add_subdirectory( PathTracing )

add_executable( sceneTest "sceneTest.cpp" )
target_link_libraries( sceneTest sceneLib ${ASSIMP_LIBRARIES} )

add_executable( accTest "AccTest.cpp" )
target_link_libraries( accTest sceneLib accelerateLib rayLib cameraLib tracingLib ${ASSIMP_LIBRARIES} ${OpenCV_LIBRARIES} )

add_executable( demo "demo.cpp" )
target_link_libraries( demo sceneLib accelerateLib rayLib cameraLib tracingLib ${ASSIMP_LIBRARIES} ${OpenCV_LIBRARIES} )
