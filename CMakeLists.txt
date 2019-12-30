cmake_minimum_required(VERSION 3.12)
project(spriter2dx VERSION 1.0 LANGUAGES CXX)

find_package(tinyxml2 REQUIRED)

add_library(spriter2dx STATIC
    include/spriter2dx/ccimagefile.cpp
    include/spriter2dx/ccsoundfile.cpp
    include/spriter2dx/ccfilefactory.cpp
    include/spriter2dx/ccsoundobjectinforeference.cpp
    include/spriter2dx/ccobjectfactory.cpp
    include/spriter2dx/cctriggerobjectinfo.cpp
    include/spriter2dx/ccboxinstanceinfo.cpp
    include/spriter2dx/ccboneinstanceinfo.cpp
    include/spriter2dx/ccpointinstanceinfo.cpp
    include/spriter2dx/tinyxmlspriterfileattributewrapper.cpp
    include/spriter2dx/tinyxmlspriterfiledocumentwrapper.cpp
    include/spriter2dx/tinyxmlspriterfileelementwrapper.cpp
    include/spriter2dx/AnimationNode.cpp
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
