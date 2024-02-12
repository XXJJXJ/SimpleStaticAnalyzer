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
add_library(integration_testing ${srcs} ${headers})
target_link_libraries(integration_testing spa)
