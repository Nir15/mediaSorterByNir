cmake_minimum_required(VERSION 3.5)

project(mediaSorterByNir VERSION 0.1 LANGUAGES CXX)

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")

# when using libraw.dll the optimization makes the program crash, need to not optimize
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O0 -DNDEBUG")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets)

set(PROJECT_SOURCES
    main.cpp
    widget.cpp
    widget.h
    widget.ui
    startupscreen.h
    startupscreen.cpp
    startupscreen.ui
    pathsscreen.h
    pathsscreen.cpp
    pathsscreen.ui
    mainsortingwindow.h
    mainsortingwindow.cpp
    mainsortingwindow.ui
    clickablelabel.h
    clickablelabel.cpp
    custommessagebox.cpp
    custommessagebox.h
    hoveredobject.cpp
    hoveredobject.h
    resource.qrc
)

include_directories(C:/Qt/QtProjects/mediaSorterByNir/libRaw/libraw)
set(LIBRAW_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libRaw/lib")
set(LIBRAW_LIB "${LIBRAW_LIB_PATH}/libraw.dll")
link_directories("${LIBRAW_LIB_PATH}/libraw.dll")

# making sure cmake knows how to read .rc files
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    enable_language("RC")
    set (WIN32_RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/appIcon.rc")
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mediaSorterByNir
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${WIN32_RESOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET mediaSorterByNir APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(mediaSorterByNir SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(mediaSorterByNir
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(mediaSorterByNir PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets ${LIBRAW_LIB})

# Ensure the DLL is copied to the output directory
add_custom_command(TARGET mediaSorterByNir POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/libRaw/lib/libraw.dll"
    $<TARGET_FILE_DIR:mediaSorterByNir>
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.mediaSorterByNir)
endif()
set_target_properties(mediaSorterByNir PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS mediaSorterByNir
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(mediaSorterByNir)
endif()
