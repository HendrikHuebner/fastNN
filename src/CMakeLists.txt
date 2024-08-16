add_subdirectory(math)
add_subdirectory(model)

target_sources(fastNN
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/util/DataSet.cpp
)