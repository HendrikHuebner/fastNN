target_sources(fastNN
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/activationFunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/costFunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DenseLayer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gradientDescent.cpp
    
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/updater/AdamGradientUpdater.cpp
)