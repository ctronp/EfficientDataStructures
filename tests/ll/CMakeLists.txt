file(GLOB ll_test_files CONFIGURE_DEPENDS "*.c")

foreach (test_file ${ll_test_files})
    get_filename_component(test_file_name ${test_file} NAME)
    add_executable(ll_test_${test_file_name} ${test_file})
    target_link_libraries(ll_test_${test_file_name} INTERFACE headers-lib mct)
    add_test(ll_test_${test_file_name} ll_test_${test_file_name})
endforeach ()