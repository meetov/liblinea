set(MINUNIT_FLAGS -lrt -lm)

file(GLOB files "test_*.c")
foreach(file ${files})
    string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" file_without_ext ${file})

    add_executable(${file_without_ext} ${file})

    target_include_directories(${file_without_ext} 
        PRIVATE 
        ${PROJECT_SOURCE_DIR}/src)

	target_include_directories(${file_without_ext} 
        PRIVATE 
        ${PROJECT_SOURCE_DIR}/include)

	target_compile_options(${file_without_ext}
		BEFORE
		PUBLIC ${MINUNIT_FLAGS}
	) # for minuint

    target_link_libraries(${file_without_ext} linea)

    add_test(${file_without_ext} ${file_without_ext})

    set_tests_properties(${file_without_ext}
        PROPERTIES
        PASS_REGULAR_EXPRESSION "PASS")

    set_tests_properties(${file_without_ext}
        PROPERTIES
        FAIL_REGULAR_EXPRESSION "FAIL")
        
endforeach()
