add_subdirectory(model)
add_subdirectory(math)

target_sources(fastNN
    
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/util/DataSet.h
    ${CMAKE_CURRENT_LIST_DIR}/util/helpers.h
)