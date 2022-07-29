
add_library(mct INTERFACE)
target_link_directories(mct INTERFACE MCT)

add_subdirectory(ll)
add_subdirectory(vector)