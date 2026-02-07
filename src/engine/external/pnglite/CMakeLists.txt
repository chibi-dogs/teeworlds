add_library(engine_external_pnglite OBJECT)

target_sources(engine_external_pnglite
        PRIVATE pnglite.c
        PUBLIC  pnglite.h
)

target_compile_features(engine_external_pnglite
        PUBLIC cxx_std_23
)

target_include_directories(engine_external_pnglite
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
