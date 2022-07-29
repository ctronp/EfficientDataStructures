file(GLOB  vector_test_files CONFIGURE_DEPENDS *.c)

foreach (test_file ${vector_test_files})
    get_filename_component(test_file_name ${test_file} NAME)
    add_executable(vector_test_${test_file_name} ${test_file})
    target_link_libraries(vector_test_${test_file_name} PUBLIC headers-lib mct)
    add_test(vector_test_${test_file_name} vector_test_${test_file_name})
endforeach ()