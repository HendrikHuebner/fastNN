target_sources(fastNN
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Model.h
    ${CMAKE_CURRENT_LIST_DIR}/activationFunction.h
    ${CMAKE_CURRENT_LIST_DIR}/costFunction.h
    ${CMAKE_CURRENT_LIST_DIR}/DenseLayer.h
    ${CMAKE_CURRENT_LIST_DIR}/gradientDescent.h
    ${CMAKE_CURRENT_LIST_DIR}/Layer.h
    ${CMAKE_CURRENT_LIST_DIR}/OutputLayer.h
    
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/weightInit.h
    ${CMAKE_CURRENT_LIST_DIR}/updater/AdamGradientUpdater.h
    ${CMAKE_CURRENT_LIST_DIR}/updater/SGDGradientUpdater.h
)