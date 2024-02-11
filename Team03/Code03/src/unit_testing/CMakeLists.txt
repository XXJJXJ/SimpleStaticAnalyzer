file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs}
        src/TestQPS.cpp
        ../spa/src/qps/entity/strategy/ProjectionStrategy.h
        ../spa/src/qps/entity/query/Query.cpp
        ../spa/src/common/EntityType.h
        src/qps/TestQueryEvaluationContext.cpp
)

target_link_libraries(unit_testing spa)