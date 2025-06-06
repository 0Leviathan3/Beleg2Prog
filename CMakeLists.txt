cmake_minimum_required(VERSION 3.10)

# Set the project name
project(beleg_2_semester)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(beleg_2_semester main.cpp person.cpp CD.cpp book.cpp BlueRay.cpp medium.cpp mainwindow.cpp)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
target_link_libraries(beleg_2_semester Qt6::Widgets)



# Include directories (if needed)
# include_directories(${PROJECT_SOURCE_DIR}/include)

# Link libraries (if needed)
# target_link_libraries(${PROJECT_NAME} library_name)