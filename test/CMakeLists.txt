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

    target_link_libraries(${file_without_ext} list)

    add_test(${file_without_ext} ${file_without_ext})
	        
endforeach()
