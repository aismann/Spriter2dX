cmake_minimum_required(VERSION 3.12)
project(spriter2dx VERSION 1.0 LANGUAGES CXX)

find_package(tinyxml2 REQUIRED)

add_library(spriter2dx STATIC
    src/ccimagefile.cpp
    src/ccsoundfile.cpp
    src/ccfilefactory.cpp
    src/ccsoundobjectinforeference.cpp
    src/ccobjectfactory.cpp
    src/cctriggerobjectinfo.cpp
    src/ccboxinstanceinfo.cpp
    src/ccboneinstanceinfo.cpp
    src/ccpointinstanceinfo.cpp
    src/tinyxmlspriterfileattributewrapper.cpp
    src/tinyxmlspriterfiledocumentwrapper.cpp
    src/tinyxmlspriterfileelementwrapper.cpp
    src/AnimationNode.cpp
)

add_library(spriter2dx::spriter2dx ALIAS spriter2dx)

target_compile_features(spriter2dx PUBLIC cxx_std_11)

target_include_directories(spriter2dx
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/spriter2dx
)

target_link_libraries(spriter2dx PUBLIC
    spriterplusplus::spriterengine
    cocos2d::cocos2d
    tinyxml2::tinyxml2
)

set_target_properties(spriter2dx PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
