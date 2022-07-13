file(GLOB test_files "*.c")

foreach (test_file ${test_files})
    get_filename_component(test_file_name ${test_file} NAME)
    add_executable(test_${test_file_name} ${test_file})
    target_link_libraries(test_${test_file_name} PUBLIC headers-lib)
    add_test(test_${test_file_name} test_${test_file_name})
endforeach ()