file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(autotester ${srcs}
        ../spa/src/qps/entity/strategy/ProjectionStrategy.h
        ../spa/src/qps/entity/query/Query.cpp
        ../spa/src/common/EntityType.h)
target_link_libraries(autotester spa ${AUTOTESTER_LIBRARIES})

if (NOT WIN32)
    target_link_libraries(autotester pthread)
endif()
