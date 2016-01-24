set(H_LIST Wizard.h
           WizardPage.h
           FileDialog.h
           FileSystemModel.h
)
set(SRC_LIST Wizard.cpp
             WizardPage.cpp
             FileDialog.cpp
             FileSystemModel.cpp
)

add_library(components ${H_LIST}
                       ${SRC_LIST})
                       
target_link_libraries(components ${Wt_LIBRARY}
                                 ${Boost_LIBRARIES})

add_executable(component-gallery Application.h Application.cpp main.cpp)
target_link_libraries(component-gallery components ${Wt_LIBRARY} ${Wt_HTTP_LIBRARY})

install(TARGETS component-gallery
        DESTINATION dist)