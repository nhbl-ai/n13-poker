cmake_minimum_required(VERSION 3.24)
project(N13Poker VERSION 1.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
include(FetchContent)

# Compile SFML with the selected compiler; never link the old MSVC .lib files.
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(SFML_USE_STATIC_STD_LIBS ON CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)
set(SFML_INSTALL_PKGCONFIG_FILES OFF CACHE BOOL "" FORCE)
set(N13_SFML_ARCHIVE "${CMAKE_CURRENT_SOURCE_DIR}/third_party/SFML-2.6.2.zip")
if(NOT EXISTS "${N13_SFML_ARCHIVE}")
    set(N13_SFML_ARCHIVE "https://github.com/SFML/SFML/archive/refs/tags/2.6.2.zip")
endif()
FetchContent_Declare(SFML URL "${N13_SFML_ARCHIVE}"
    URL_HASH SHA256=19d6dbd9c901c74441d9888c13cb1399f614fe8993d59062a72cfbceb00fed04
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
FetchContent_MakeAvailable(SFML)

add_library(poker_logic STATIC
    N13/LogicGame.cpp N13/LogicFiveCards.cpp N13/LogicThreeCards.cpp N13/PokerHand.cpp)
target_include_directories(poker_logic PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/N13")

add_executable(N13Poker
    N13/N13.cpp N13/RuntimePaths.cpp N13/Choiceboard.cpp
    N13/CountNumberPlayers.cpp N13/credits.cpp N13/Database.cpp
    N13/Fivecardspoker.cpp N13/gameWindow.cpp N13/Icongame.cpp
    N13/Leaderboard.cpp N13/Login.cpp N13/LoginWindow.cpp
    N13/OptionWindow.cpp N13/Player.cpp N13/pokerChooseGame.cpp
    N13/Register.cpp N13/table.cpp N13/ThreeCards.cpp N13/tittle.cpp
    N13/window.cpp N13/word2.cpp)
target_link_libraries(N13Poker PRIVATE poker_logic sfml-graphics sfml-audio)
set_target_properties(N13Poker PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/run")
if(MINGW)
    target_link_libraries(N13Poker PRIVATE user32)
    target_link_options(N13Poker PRIVATE -mwindows -static-libgcc -static-libstdc++)
endif()
if(NOT WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
    target_link_libraries(N13Poker PRIVATE stdc++fs)
endif()

file(GLOB GAME_ASSETS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/N13/*.png" "${CMAKE_CURRENT_SOURCE_DIR}/N13/*.jpg"
    "${CMAKE_CURRENT_SOURCE_DIR}/N13/*.ttf" "${CMAKE_CURRENT_SOURCE_DIR}/N13/*.wav"
    "${CMAKE_CURRENT_SOURCE_DIR}/N13/*.mp3")
list(APPEND GAME_ASSETS "${CMAKE_CURRENT_SOURCE_DIR}/N13/credits.txt")
set(ASSET_NAMES "")
foreach(ASSET IN LISTS GAME_ASSETS)
    get_filename_component(NAME "${ASSET}" NAME)
    string(APPEND ASSET_NAMES "${NAME}\n")
endforeach()
file(WRITE "${CMAKE_BINARY_DIR}/resources.manifest" "${ASSET_NAMES}")

set(OPENAL_DLL "")
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(OPENAL_DLL "${sfml_SOURCE_DIR}/extlibs/bin/x64/openal32.dll")
    else()
        set(OPENAL_DLL "${sfml_SOURCE_DIR}/extlibs/bin/x86/openal32.dll")
    endif()
endif()
configure_file(cmake/StageAssets.cmake.in StageAssets.cmake @ONLY)
add_custom_command(TARGET N13Poker POST_BUILD
    COMMAND "${CMAKE_COMMAND}" "-DDESTINATION=$<TARGET_FILE_DIR:N13Poker>"
            -P "${CMAKE_BINARY_DIR}/StageAssets.cmake")

install(TARGETS N13Poker RUNTIME DESTINATION . COMPONENT Game)
install(FILES ${GAME_ASSETS} "${CMAKE_BINARY_DIR}/resources.manifest" DESTINATION . COMPONENT Game)
if(OPENAL_DLL)
    install(FILES "${OPENAL_DLL}" DESTINATION . COMPONENT Game)
endif()
foreach(DATA_FILE users.txt player.txt Leaderboard.txt)
    install(CODE "if(NOT EXISTS \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/${DATA_FILE}\")\nfile(INSTALL \"${CMAKE_CURRENT_SOURCE_DIR}/data/defaults/${DATA_FILE}\" DESTINATION \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}\")\nendif()" COMPONENT Game)
endforeach()
install(FILES docs/PLAYING.md DESTINATION . RENAME README.md COMPONENT Game)
install(FILES THIRD_PARTY_NOTICES.md FIXES.md VERIFICATION.md DESTINATION . COMPONENT Game)
install(DIRECTORY licenses/ DESTINATION licenses COMPONENT Game)

include(CTest)
if(BUILD_TESTING)
    add_executable(logic_regression tests/logic_regression.cpp)
    target_link_libraries(logic_regression PRIVATE poker_logic)
    if(MINGW)
        target_link_options(logic_regression PRIVATE -static-libgcc -static-libstdc++)
    endif()
    add_test(NAME logic_regression COMMAND logic_regression)
    foreach(TEST_NAME bug_regression poker_exhaustive)
        add_executable(${TEST_NAME} tests/${TEST_NAME}.cpp)
        target_link_libraries(${TEST_NAME} PRIVATE poker_logic)
        if(MINGW)
            target_link_options(${TEST_NAME} PRIVATE -static-libgcc -static-libstdc++)
        endif()
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endforeach()
    add_test(NAME packaged_resources COMMAND N13Poker --check-resources)
    set_tests_properties(packaged_resources PROPERTIES WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

set(CPACK_GENERATOR ZIP)
set(CPACK_PACKAGE_FILE_NAME "N13-Poker-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}")
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON)
set(CPACK_COMPONENTS_ALL Game)
include(CPack)
