cmake_minimum_required (VERSION 3.12)

project (Almond VERSION 1.0.0
                  DESCRIPTION "Almond"
                  LANGUAGES CXX)

set(ALMOND_SOURCES
"Almond/main.cpp"
)

add_executable(almond ${ALMOND_SOURCES})
target_include_directories(almond PRIVATE
    ${ALMOND_ROOT_DIR}/Source
)

target_link_libraries(almond PRIVATE AlmondDependencies)


if(ALMOND_DEBUG_BUILD)
    add_definitions(ASSET_FOLDER_PATH=\"${ALMOND_ROOT_DIR}/assets/\")
elseif(ALMOND_RELEASE_BUILD)
    add_definitions(ASSET_FOLDER_PATH=\"./assets/\")
endif()