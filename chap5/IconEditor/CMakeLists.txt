find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
add_executable(IconEditor main.cpp IconEditor.cpp)
target_include_directories(IconEditor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR})
qt5_use_modules(IconEditor Core Widgets)
