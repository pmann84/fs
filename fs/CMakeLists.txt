set({PROJECT_NAME} fs)

add_executable(${PROJECT_NAME} fs.cpp details.hpp utils.hpp display.hpp)

target_link_libraries(${PROJECT_NAME} PRIVATE sage)