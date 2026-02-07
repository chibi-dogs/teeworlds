add_library(engine_external_zlib STATIC)

target_sources(engine_external_zlib
        PRIVATE
        adler32.c
        crc32.c
        compress.c
        deflate.c
        inffast.c
        infback.c
        inflate.c
        inftrees.c
        trees.c
        uncompr.c
        zutil.c
        PUBLIC
        crc32.h
        deflate.h
        gzguts.h
        inffast.h
        inffixed.h
        inflate.h
        inftrees.h
        trees.h
        zconf.h
        zlib.h
        zutil.h
)

target_compile_features(engine_external_zlib
        PUBLIC cxx_std_23
)

target_include_directories(engine_external_zlib
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
