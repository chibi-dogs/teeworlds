add_library(engine_external_json OBJECT)

target_sources(engine_external_json
        PRIVATE json.c
        PUBLIC  json.h
)

target_compile_features(engine_external_json
        PUBLIC cxx_std_23
)

target_include_directories(engine_external_json
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
