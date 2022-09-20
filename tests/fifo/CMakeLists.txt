file(GLOB fifo_test_files CONFIGURE_DEPENDS "*.c")

foreach (test_file ${fifo_test_files})
    get_filename_component(test_file_name ${test_file} NAME)
    add_executable(fifo_test_${test_file_name} ${test_file})
    target_link_libraries(fifo_test_${test_file_name} INTERFACE headers-lib mct)
    add_test(fifo_test_${test_file_name} fifo_test_${test_file_name})
endforeach ()