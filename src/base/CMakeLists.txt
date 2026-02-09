add_library(Base
        Sha256.h)

target_include_directories(Base
        PUBLIC
        ${PROJECT_SOURCE_DIR}/src
)

target_sources(Base
        PRIVATE
        hash.c
        hash_bundled.c
        hash_libtomcrypt.c
        hash_openssl.c
        system.c
        PUBLIC
        color.h
        Sha256.h
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
target_link_libraries(Base PUBLIC engine_external_md5)