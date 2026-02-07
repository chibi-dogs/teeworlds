add_library(engine_external_wavpack OBJECT)

target_sources(engine_external_wavpack
        PRIVATE
        bits.c
        float.c
        metadata.c
        unpack.c
        words.c
        wputils.c
        PUBLIC
        wavpack.h
)

target_compile_features(engine_external_wavpack
        PUBLIC cxx_std_23
)

target_include_directories(engine_external_wavpack
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
