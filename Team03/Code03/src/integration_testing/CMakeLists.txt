file(GLOB srcs
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*.cpp"
)
file(GLOB headers
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*/*/*/*.h"
)
add_executable(integration_testing ${srcs} ${headers}
        src/TestSpa.cpp)
target_link_libraries(integration_testing spa)
