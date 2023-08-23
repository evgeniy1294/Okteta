cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

set(TARGET oktetagui)
set(TARGET_NAMESPACE Okteta)
set(INCLUDE_PREFIX "")
set(LIBRARY_DIST_SUFFIX "")

set(OKTETAGUI_VERSION ${OKTETALIBS_LIB_VERSION})
set(OKTETAGUI_SO_VERSION ${OKTETALIBS_LIB_SOVERSION})

project(${TARGET} VERSION ${OKTETAGUI_VERSION} LANGUAGES CXX)
option(${TARGET}_INSTALL "Generate the install target" ON)
option(${TARGET}_INSTALL_HEADERS "Generate the install target public headers" OFF)

set(CMAKE_AUTOMOC ON)

set(
  ControllerSources
    src/Controller/AbstractController.cpp
    src/Controller/AbstractMouseController.cpp
    src/Controller/AbstractWheelController.cpp
    src/Controller/AbstractEditor.cpp
    src/Controller/KeyNavigator.cpp
    src/Controller/TabController.cpp
    src/Controller/ClipboardController.cpp
    src/Controller/UndoRedoController.cpp
    src/Controller/CharEditor.cpp
    src/Controller/ValueEditor.cpp
    src/Controller/MouseNavigator.cpp
    src/Controller/MousePaster.cpp
    src/Controller/TapNavigator.cpp
    # src/Controller/Dragger
    src/Controller/ZoomWheelController.cpp
    src/Controller/ZoomPinchController.cpp
    src/Controller/Dropper.cpp

    src/Controller/TouchOnlyTapAndHoldGesture.cpp
    src/Controller/TouchOnlyTapAndHoldGestureRecognizer.cpp
)

set(
  ColumnsViewSources
    src/LibColumnsView/AbstractColumnStylist.cpp
    src/LibColumnsView/AbstractColumnRenderer.cpp
    src/LibColumnsView/ColumnsView.cpp
    src/LibColumnsView/ColumnsViewPrivate.cpp
)

set(
  ColorsSources
    src/Colors/KColorSpaces.cpp
    src/Colors/KColorUtils.cpp
)

set(
  GuiSources
    src/OktetaGui.cpp

    src/CoordRangeList.cpp

    src/AbstractByteArrayColumnRenderer.cpp
    src/AbstractByteArrayColumnRendererPrivate.cpp
    src/CharByteArrayColumnRenderer.cpp
    src/CharByteArrayColumnRendererPrivate.cpp
    src/ValueByteArrayColumnRenderer.cpp
    src/ValueByteArrayColumnRendererPrivate.cpp
    src/ByteArrayRowColumnRenderer.cpp
    src/ByteArrayRowColumnRendererPrivate.cpp
    src/OffsetColumnRenderer.cpp
    src/OffsetColumnRendererPrivate.cpp
    src/BorderColumnRenderer.cpp
    src/BorderColumnRendererPrivate.cpp

    src/AbstractByteArrayView.cpp
    src/AbstractByteArrayViewPrivate.cpp
    src/ByteArrayColumnView.cpp
    src/ByteArrayColumnViewPrivate.cpp

    src/OffsetFormat.cpp
    src/ByteArrayTableRanges.cpp
    src/ByteArrayRowView.cpp
    src/ByteArrayRowViewPrivate.cpp
    src/ByteArrayTableLayout.cpp
    src/WidgetColumnStylist.cpp

    src/ColorScheme.cpp

    src/GlobalConfigStorage.cpp

    src/ByteArrayTableCursor.cpp
    src/Cursor.cpp
)

set(
  ControllerHeaders
    include/Okteta/Controller/AbstractController.hpp
    include/Okteta/Controller/AbstractEditor.hpp
    include/Okteta/Controller/AbstractMouseController.hpp
    include/Okteta/Controller/AbstractWheelController.hpp
    include/Okteta/Controller/CharEditor.hpp
    include/Okteta/Controller/ClipboardController.hpp
    include/Okteta/Controller/Dropper.hpp
    include/Okteta/Controller/KeyNavigator.hpp
    include/Okteta/Controller/MouseNavigator.hpp
    include/Okteta/Controller/MousePaster.hpp
    include/Okteta/Controller/TabController.hpp
    include/Okteta/Controller/TapNavigator.hpp
    include/Okteta/Controller/TouchOnlyTapAndHoldGesture.hpp
    include/Okteta/Controller/TouchOnlyTapAndHoldGestureRecognizer.hpp
    include/Okteta/Controller/UndoRedoController.hpp
    include/Okteta/Controller/ValueEditor.hpp
    include/Okteta/Controller/ZoomPinchController.hpp
    include/Okteta/Controller/ZoomWheelController.hpp
)

set(
  ColumnsViewHeaders
    include/Okteta/LibColumnsView/AbstractColumnRenderer.hpp
    include/Okteta/LibColumnsView/AbstractColumnRendererPrivate.hpp
    include/Okteta/LibColumnsView/AbstractColumnStylist.hpp
    include/Okteta/LibColumnsView/AbstractColumnStylistPrivate.hpp
    include/Okteta/LibColumnsView/ColumnsView.hpp
    include/Okteta/LibColumnsView/ColumnsViewPrivate.hpp
    include/Okteta/LibColumnsView/PixelMetrics.hpp
)

set(
  ColorsHeaders
    include/Okteta/Colors/kcolorspaces_p.h
    include/Okteta/Colors/kcolorutils.h
    include/Okteta/Colors/kguiaddons_colorhelpers_p.h
)

set(
  GuiHeaders
    include/Okteta/AbstractByteArrayColumnRenderer.hpp
    include/Okteta/AbstractByteArrayColumnRendererPrivate.hpp
    include/Okteta/AbstractByteArrayView.hpp
    include/Okteta/AbstractByteArrayViewPrivate.hpp
    include/Okteta/BorderColumnRenderer.hpp
    include/Okteta/BorderColumnRendererPrivate.hpp
    include/Okteta/ByteArrayColumnView.hpp
    include/Okteta/ByteArrayColumnViewPrivate.hpp
    include/Okteta/ByteArrayRowColumnRenderer.hpp
    include/Okteta/ByteArrayRowColumnRendererPrivate.hpp
    include/Okteta/ByteArrayRowView.hpp
    include/Okteta/ByteArrayRowViewPrivate.hpp
    include/Okteta/ByteArrayTableCursor.hpp
    include/Okteta/ByteArrayTableLayout.hpp
    include/Okteta/ByteArrayTableRanges.hpp
    include/Okteta/ByteArrayTableRangesPrivate.hpp
    include/Okteta/CharByteArrayColumnRenderer.hpp
    include/Okteta/CharByteArrayColumnRendererPrivate.hpp
    include/Okteta/ColorScheme.hpp
    include/Okteta/ColorSchemeHelpersPrivate.hpp
    include/Okteta/Coord.hpp
    include/Okteta/CoordRange.hpp
    include/Okteta/CoordRangeList.hpp
    include/Okteta/Cursor.hpp
    include/Okteta/GlobalConfigStorage.hpp
    include/Okteta/Helper.hpp
    include/Okteta/Line.hpp
    include/Okteta/LinePosition.hpp
    include/Okteta/LinePositionRange.hpp
    include/Okteta/LineRange.hpp
    include/Okteta/OffsetColumnRenderer.hpp
    include/Okteta/OffsetColumnRendererPrivate.hpp
    include/Okteta/OffsetFormat.hpp
    include/Okteta/OktetaGui.hpp
    include/Okteta/Selection.hpp
    include/Okteta/ValueByteArrayColumnRenderer.hpp
    include/Okteta/ValueByteArrayColumnRendererPrivate.hpp
    include/Okteta/WidgetColumnStylist.hpp
    include/Okteta/WidgetColumnStylistPrivate.hpp
)

set(
  SOURCES_LIST
    ${ControllerSources}
    ${ControllerHeaders}
    ${ColumnsViewSources}
    ${ColumnsViewHeaders}
    ${ColorsSources}
    ${ColorsHeaders}
    ${GuiSources}
    ${GuiHeaders}
)

add_library(${TARGET} SHARED)
target_sources(${TARGET} PRIVATE ${SOURCES_LIST})

add_library(${TARGET_NAMESPACE}::Gui ALIAS ${TARGET})

# ------------ [ ExportHeader ] ------------
include(GNUInstallDirs)
include(GenerateExportHeader)

generate_export_header(${TARGET}
        EXPORT_FILE_NAME "${INCLUDE_PREFIX}${TARGET_NAMESPACE}/export/oktetagui_cfg.hpp"
        EXPORT_MACRO_NAME OKTETAGUI_EXPORT
        NO_EXPORT_MACRO_NAME OKTETAGUI_NO_EXPORT
        DEPRECATED_MACRO_NAME OKTETAGUI_DEPRECATED
        NO_DEPRECATED_MACRO_NAME OKTETAGUI_NO_DEPRECATED
)

# ------------ [ Depends ] ------------
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
if(NOT DEFINED QT_BUILD_VERSION)
    set(QT_BUILD_VERSION ${QT_VERSION_MAJOR})
endif()

find_package(Qt${QT_BUILD_VERSION} COMPONENTS Core Gui Widgets REQUIRED)

target_link_libraries(${TARGET}
    PRIVATE
    Qt${QT_BUILD_VERSION}::Core
    Qt${QT_BUILD_VERSION}::Widgets
    Okteta::Core
)


# ------------ [ Properties and compile definitions ] ------------
set_target_properties(${TARGET} PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 17
)

target_include_directories(${TARGET} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/>
)

target_include_directories(
  ${TARGET} PRIVATE
      include/${TARGET_NAMESPACE}
      ${PROJECT_BINARY_DIR}/${INCLUDE_PREFIX}export/
)

if(${TARGET}_INSTALL)
    message(STATUS "Generating install for ${TARGET}")

    set(
      PublicHeaders
        include/Okteta/LibColumnsView/AbstractColumnStylist.hpp
        include/Okteta/LibColumnsView/AbstractColumnRenderer.hpp
        include/Okteta/LibColumnsView/ColumnsView.hpp
        include/Okteta/LibColumnsView/PixelMetrics.hpp

        include/Okteta/OktetaGui.hpp

        include/Okteta/Line.hpp
        include/Okteta/LinePosition.hpp
        include/Okteta/LinePositionRange.hpp
        include/Okteta/LineRange.hpp

        include/Okteta/Coord.hpp
        include/Okteta/CoordRange.hpp
        include/Okteta/CoordRangeList.hpp
        include/Okteta/Selection.hpp

        include/Okteta/AbstractByteArrayColumnRenderer.hpp
        include/Okteta/CharByteArrayColumnRenderer.hpp
        include/Okteta/ValueByteArrayColumnRenderer.hpp
        include/Okteta/ByteArrayRowColumnRenderer.hpp
        include/Okteta/OffsetColumnRenderer.hpp
        include/Okteta/BorderColumnRenderer.hpp

        include/Okteta/AbstractByteArrayView.hpp
        include/Okteta/ByteArrayColumnView.hpp

        include/Okteta/OffsetFormat.hpp
        include/Okteta/ByteArrayTableRanges.hpp
        include/Okteta/ByteArrayRowView.hpp
        include/Okteta/ByteArrayTableLayout.hpp
        include/Okteta/WidgetColumnStylist.hpp
    )
    #---------------------------------------------------------------------------------------
    # if we plan to export built library to CMAKE_INSTALL_PREFIX
    # (by default it's /usr/local or C:/Program Files/${PROJECT_NAME})
    #---------------------------------------------------------------------------------------
    if(${TARGET}_INSTALL_HEADERS)
        install(FILES ${PublicHeaders} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${INCLUDE_PREFIX}${TARGET_NAMESPACE}/" COMPONENT devel)
        install(FILES "${PROJECT_BINARY_DIR}/${INCLUDE_PREFIX}${TARGET_NAMESPACE}/export/oktetagui_cfg.hpp" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${INCLUDE_PREFIX}${TARGET_NAMESPACE}/export")
    endif()

    install(TARGETS ${TARGET} EXPORT ${TARGET}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/${TARGET_NAMESPACE}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/${TARGET_NAMESPACE}"
    )

    #---------------------------------------------------------------------------------------
    # installing cmake config file allows importing our library into other projects via "find_package"
    #---------------------------------------------------------------------------------------

    # set(project_config_in "${CMAKE_CURRENT_BINARY_DIR}/cmake/${TARGET}_config.cmake.in")
    set(project_config_out  "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_config.cmake")
    set(version_config_file "${CMAKE_CURRENT_BINARY_DIR}/${TARGET}_config_version.cmake")
    set(config_targets_file "${TARGET}_config_targets.cmake")
    set(export_dest_dir     "${CMAKE_INSTALL_LIBDIR}/${TARGET_NAMESPACE}/cmake")

    install(EXPORT ${TARGET}
            DESTINATION ${export_dest_dir}
            NAMESPACE ${TARGET_NAMESPACE}::
            FILE ${config_targets_file})

    include(CMakePackageConfigHelpers)
    # configure_file("${project_config_in}" "${project_config_out}" @ONLY)
    write_basic_package_version_file("${version_config_file}" COMPATIBILITY SameMajorVersion)
    install(FILES "${version_config_file}" DESTINATION "${export_dest_dir}")

endif()
