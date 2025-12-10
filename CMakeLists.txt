cmake_minimum_required(VERSION 3.19)
project(SLIC_App LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_resources(APP_RESOURCES resource/resource.qrc)

qt_add_executable(SLIC_App
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/window.cpp
    include/window.h
    src/window.ui
    include/image.h
    src/image.cpp
    ${APP_RESOURCES}
    include/slic.h
    src/slic.cpp
)

qt_add_translations(
    TARGETS SLIC_App
    TS_FILES SLIC_App_fr_FR.ts
)

target_include_directories(SLIC_App
    PRIVATE
        include
)

target_link_libraries(SLIC_App
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS SLIC_App
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SLIC_App
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
