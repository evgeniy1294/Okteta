cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

set(TARGET oktetacore)
set(TARGET_NAMESPACE Okteta)
set(INCLUDE_PREFIX "")
set(LIBRARY_DIST_SUFFIX "")

set(OKTETACORE_VERSION ${OKTETALIBS_LIB_VERSION})
set(OKTETACORE_SO_VERSION ${OKTETALIBS_LIB_SOVERSION})

project(${TARGET} VERSION ${OKTETACORE_VERSION} LANGUAGES CXX)
option(${TARGET}_INSTALL "Generate the install target" ON)
option(${TARGET}_INSTALL_HEADERS "Generate the install target public headers" OFF)

set(CMAKE_AUTOMOC ON)

# ------------ [ Sources ] ------------
set(
  CodecsSources
        src/Codecs/BinaryByteCodec.cpp
        src/Codecs/ValueCodec.cpp
        src/Codecs/CharCodec.cpp
        src/Codecs/DecimalByteCodec.cpp
        src/Codecs/USASCIICharCodec.cpp
        src/Codecs/EBCDIC1047CharCodec.cpp
        src/Codecs/IBM874CharCodec.cpp
        src/Codecs/JISX0201CharCodec.cpp
        src/Codecs/HexadecimalByteCodec.cpp
        src/Codecs/OctalByteCodec.cpp
        src/Codecs/TextCharCodec.cpp
)

set(
  PiecetableSources
        src/PieceTable/PieceList.cpp
        src/PieceTable/PieceTable.cpp
        src/PieceTable/AbstractPieceTableChange.cpp
#         src/PieceTable/FillPieceTableChange.cpp
        src/PieceTable/InsertPieceTableChange.cpp
        src/PieceTable/RemovePieceTableChange.cpp
        src/PieceTable/ReplacePieceTableChange.cpp
        src/PieceTable/SwapRangesPieceTableChange.cpp
        src/PieceTable/GroupPieceTableChange.cpp
        src/PieceTable/PieceTableChangeHistory.cpp
        src/PieceTable/RevertablePieceTable.cpp
)

set(
  CoreSources
    src/OktetaCore.cpp
    src/AbstractByteArrayModel.cpp
    src/ByteArrayModel.cpp
    src/ByteArrayModelPrivate.cpp
    #src/FileByteArrayModel
    src/PieceTableByteArrayModel.cpp
    src/PieceTableByteArrayModelPrivate.cpp
    src/TextByteArrayAnalyzer.cpp
    src/FileByteArrayModel.cpp
    src/FileByteArrayModelPrivate.cpp
    src/FixedSizeByteArrayModel.cpp
    src/NullModel.cpp
    src/BookmarkListConstIteratorAdapter.cpp
    src/AddressRangeList.cpp
    src/BookmarkList.cpp
)

set(
  CodecsHeaders
    include/Okteta/Codecs/BinaryByteCodec.hpp
    include/Okteta/Codecs/DecimalByteCodec.hpp
    include/Okteta/Codecs/EBCDIC1047CharCodec.hpp
    include/Okteta/Codecs/HexadecimalByteCodec.hpp
    include/Okteta/Codecs/IBM874CharCodec.hpp
    include/Okteta/Codecs/JISX0201CharCodec.hpp
    include/Okteta/Codecs/OctalByteCodec.hpp
    include/Okteta/Codecs/TextCharCodec.hpp
    include/Okteta/Codecs/USASCIICharCodec.hpp
)

set(
  PiecetableHeaders
    include/Okteta/PieceTable/AbstractPieceTableChange.hpp
    include/Okteta/PieceTable/GroupPieceTableChange.hpp
    include/Okteta/PieceTable/InsertPieceTableChange.hpp
    include/Okteta/PieceTable/Piece.hpp
    include/Okteta/PieceTable/PieceList.hpp
    include/Okteta/PieceTable/PieceTable.hpp
    include/Okteta/PieceTable/PieceTableChangeHistory.hpp
    include/Okteta/PieceTable/RemovePieceTableChange.hpp
    include/Okteta/PieceTable/ReplacePieceTableChange.hpp
    include/Okteta/PieceTable/RevertablePieceTable.hpp
    include/Okteta/PieceTable/SwapRangesPieceTableChange.hpp
)

set(
  CoreHeaders
    include/Okteta/AbstractByteArrayModel.hpp
    include/Okteta/AbstractByteArrayModelPrivate.hpp
    include/Okteta/Address.hpp
    include/Okteta/AddressRange.hpp
    include/Okteta/AddressRangeList.hpp
    include/Okteta/ArrayChangeMetrics.hpp
    include/Okteta/ArrayChangeMetricsList.hpp
    include/Okteta/Bookmarkable.hpp
    include/Okteta/BookmarkList.hpp
    include/Okteta/BookmarkListConstIteratorAdapter.hpp
    include/Okteta/BookmarksConstIterator.hpp
    include/Okteta/BookmarksConstIteratorAdapter.hpp
    include/Okteta/ByteArrayChange.hpp
    include/Okteta/ByteArrayModel.hpp
    include/Okteta/ByteArrayModelPrivate.hpp
    include/Okteta/ChangeHistory.hpp
    include/Okteta/ChangesDataStorage.hpp
    include/Okteta/ChangesDescribable.hpp
    include/Okteta/Character.hpp
    include/Okteta/CharCodec.hpp
    include/Okteta/FileByteArrayModel.hpp
    include/Okteta/FileByteArrayModelPrivate.hpp
    include/Okteta/FixedSizeByteArrayModel.hpp
    include/Okteta/NullModel.hpp
    include/Okteta/NumberRange.hpp
    include/Okteta/OktetaCore.hpp
    include/Okteta/PieceTableByteArrayModel.hpp
    include/Okteta/PieceTableByteArrayModelPrivate.hpp
    include/Okteta/Range.hpp
    include/Okteta/Size.hpp
    include/Okteta/TextByteArrayAnalyzer.hpp
    include/Okteta/ValueCodec.hpp
    include/Okteta/Versionable.hpp
)

set(
  SOURCES_LIST
    ${CodecsSources}
    ${CodecsHeaders}
    ${PiecetableSources}
    ${PiecetableHeaders}
    ${CoreSources}
    ${CoreHeaders}
)



add_library(${TARGET} SHARED)
target_sources(${TARGET} PRIVATE ${SOURCES_LIST})

add_library(${TARGET_NAMESPACE}::Core ALIAS ${TARGET})

# ------------ [ ExportHeader ] ------------
include(GNUInstallDirs)
include(GenerateExportHeader)

generate_export_header(${TARGET}
        EXPORT_FILE_NAME "${INCLUDE_PREFIX}${TARGET_NAMESPACE}/export/oktetacore_cfg.hpp"
        EXPORT_MACRO_NAME OKTETACORE_EXPORT
        NO_EXPORT_MACRO_NAME OKTETACORE_NO_EXPORT
        DEPRECATED_MACRO_NAME OKTETACORE_DEPRECATED
        NO_DEPRECATED_MACRO_NAME OKTETACORE_NO_DEPRECATED
)

# ------------ [ Depends ] ------------
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
if(NOT DEFINED QT_BUILD_VERSION)
    set(QT_BUILD_VERSION ${QT_VERSION_MAJOR})
endif()

find_package(Qt${QT_BUILD_VERSION} COMPONENTS Core REQUIRED)

target_link_libraries(${TARGET}
    PUBLIC
      Qt${QT_BUILD_VERSION}::Core
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
        include/Okteta/OktetaCore.hpp
        include/Okteta/Range.hpp
        include/Okteta/NumberRange.hpp
        include/Okteta/Address.hpp
        include/Okteta/AddressRange.hpp
        include/Okteta/Size.hpp
        include/Okteta/Byte.hpp
        include/Okteta/AbstractByteArrayModel.hpp
        include/Okteta/Versionable.hpp
        include/Okteta/Bookmarkable.hpp
        include/Okteta/ChangesDescribable.hpp
        include/Okteta/ChangeHistory.hpp
        include/Okteta/ByteArrayModel.hpp
        include/Okteta/PieceTableByteArrayModel.hpp
        include/Okteta/Character.hpp
        include/Okteta/ArrayChangeMetrics.hpp
        include/Okteta/ArrayChangeMetricsList.hpp
        include/Okteta/ByteArrayChange.hpp
        include/Okteta/Bookmark.hpp
        include/Okteta/BookmarksConstIteratorAdapter.hpp
        include/Okteta/BookmarksConstIterator.hpp
        include/Okteta/TextByteArrayAnalyzer.hpp
        include/Okteta/ValueCodec.hpp
        include/Okteta/CharCodec.hpp
    )
    #---------------------------------------------------------------------------------------
    # if we plan to export built library to CMAKE_INSTALL_PREFIX
    # (by default it's /usr/local or C:/Program Files/${PROJECT_NAME})
    #---------------------------------------------------------------------------------------
    if(${TARGET}_INSTALL_HEADERS)
        install(FILES ${PublicHeaders} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${INCLUDE_PREFIX}${TARGET_NAMESPACE}/" COMPONENT devel)
        install(FILES "${PROJECT_BINARY_DIR}/${INCLUDE_PREFIX}${TARGET_NAMESPACE}/export/oktetacore_cfg.hpp" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${INCLUDE_PREFIX}${TARGET_NAMESPACE}/export")
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
