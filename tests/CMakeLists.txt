
add_library(MCT INTERFACE)
target_include_directories(MCT INTERFACE MCT/MCT.h)

add_subdirectory(ll)
add_subdirectory(vector)