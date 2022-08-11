cmake_minimum_required(VERSION 3.10)

project(Panel VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Panel src/main.cpp src/ssd1306.cpp)
target_link_libraries(Panel i2c cairo)
set_target_properties(Panel PROPERTIES OUTPUT_NAME "panel")
