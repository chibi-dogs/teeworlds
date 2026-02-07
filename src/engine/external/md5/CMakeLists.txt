add_library(engine_external_md5 OBJECT)

target_sources(engine_external_md5
        PRIVATE md5.c
        PUBLIC  md5.h
)

target_compile_features(engine_external_md5
        PUBLIC cxx_std_23
)

target_include_directories(engine_external_md5
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
