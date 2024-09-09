if (AVX_MODE)
    target_sources(fastNN
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/matrix_avx_sp.cpp
        ${CMAKE_CURRENT_LIST_DIR}/vector_avx_sp.cpp
    )
endif()