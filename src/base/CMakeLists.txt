add_library(base)

target_include_directories(base
        PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)

target_sources(base
        PRIVATE
        hash.c
        hash_bundled.c
        hash_libtomcrypt.c
        hash_openssl.c
        system.c
        PUBLIC
        color.h
        detect.h
        hash.h
        hash_ctxt.h
        math.h
        system.h
        tl/algorithm.h
        tl/allocator.h
        tl/array.h
        tl/range.h
        tl/sorted_array.h
        tl/string.h
        tl/threading.h
        vmath.h

)
target_link_libraries(base PUBLIC engine_external_md5)