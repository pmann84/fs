set({PROJECT_NAME} fs)

add_executable(${PROJECT_NAME} fs.cpp details.hpp utils.hpp display.hpp)
target_link_libraries(${PROJECT_NAME} PRIVATE sage "-lstdc++exp" "-static-libgcc" "-static-libstdc++" "-static")

# On Linux we need to link to libm for log10 and math functions
find_library(MATH_LIBRARY m)
if (MATH_LIBRARY)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${MATH_LIBRARY})
endif()