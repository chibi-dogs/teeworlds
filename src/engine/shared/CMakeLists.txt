
add_library(Engine_Shared STATIC)

set(PROTOCOL_HEADER "${CMAKE_BINARY_DIR}/src/generated/protocol.h")
set(PROTOCOL_SOURCE "${CMAKE_BINARY_DIR}/src/generated/protocol.cpp")


add_custom_command(
        OUTPUT "${PROTOCOL_HEADER}"
        COMMAND ${Python3_EXECUTABLE} ${PROJECT_SOURCE_DIR}/datasrc/compile.py network_header > "${PROTOCOL_HEADER}"
        DEPENDS
        ${PROJECT_SOURCE_DIR}/datasrc/compile.py
        ${PROJECT_SOURCE_DIR}/datasrc/content.py
        ${PROJECT_SOURCE_DIR}/datasrc/network.py
        ${PROJECT_SOURCE_DIR}/datasrc/datatypes.py
        COMMENT "Generating protocol.h"
)

add_custom_command(
        OUTPUT "${PROTOCOL_SOURCE}"
        COMMAND ${Python3_EXECUTABLE} ${PROJECT_SOURCE_DIR}/datasrc/compile.py network_source > "${PROTOCOL_SOURCE}"
        DEPENDS
        ${PROJECT_SOURCE_DIR}/datasrc/compile.py
        ${PROJECT_SOURCE_DIR}/datasrc/content.py
        ${PROJECT_SOURCE_DIR}/datasrc/network.py
        ${PROJECT_SOURCE_DIR}/datasrc/datatypes.py
        "${PROTOCOL_HEADER}"  # Ensure header is generated first
        ${CMAKE_CURRENT_SOURCE_DIR}/protocol.h  # Original protocol.h
        COMMENT "Generating protocol.cpp"
)

# --- Generate nethash.cpp ---
set(NETHASH_SOURCE "${CMAKE_BINARY_DIR}/src/generated/nethash.cpp")

add_custom_command(
        OUTPUT "${NETHASH_SOURCE}"
        COMMAND ${Python3_EXECUTABLE} ${PROJECT_SOURCE_DIR}/scripts/cmd5.py
        ${CMAKE_CURRENT_SOURCE_DIR}/protocol.h
        ${PROJECT_SOURCE_DIR}/src/game/tuning.h
        ${PROJECT_SOURCE_DIR}/src/game/gamecore.cpp
        "${PROTOCOL_HEADER}"
        > "${NETHASH_SOURCE}"
        DEPENDS
        ${PROJECT_SOURCE_DIR}/scripts/cmd5.py
        ${CMAKE_CURRENT_SOURCE_DIR}/protocol.h
        ${PROJECT_SOURCE_DIR}/src/game/tuning.h
        ${PROJECT_SOURCE_DIR}/src/game/gamecore.cpp
        "${PROTOCOL_HEADER}"
        COMMENT "Generating nethash.cpp"
)

target_sources(Engine_Shared
        PRIVATE
        compression.cpp
        config.cpp
        console.cpp
        datafile.cpp
        demo.cpp
        econ.cpp
        engine.cpp
        filecollection.cpp
        huffman.cpp
        jobs.cpp
        jsonparser.cpp
        jsonwriter.cpp
        kernel.cpp
        linereader.cpp
        map.cpp
        mapchecker.cpp
        masterserver.cpp
        memheap.cpp
        netban.cpp
        network.cpp
        network_client.cpp
        network_conn.cpp
        network_console.cpp
        network_console_conn.cpp
        network_server.cpp
        network_token.cpp
        packer.cpp
        ringbuffer.cpp
        snapshot.cpp
        storage.cpp
        ${PROTOCOL_SOURCE}
        ${NETHASH_SOURCE}
        PUBLIC
        compression.h
        config.h
        config_variables.h
        console.h
        datafile.h
        demo.h
        econ.h
        filecollection.h
        huffman.h
        jobs.h
        jsonparser.h
        jsonwriter.h
        linereader.h
        mapchecker.h
        memheap.h
        netban.h
        network.h
        packer.h
        protocol.h
        ringbuffer.h
        snapshot.h
        ${PROTOCOL_HEADER}
)

target_compile_features(Engine_Shared
        PUBLIC cxx_std_23
)

target_include_directories(Engine_Shared
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/src>
)

target_link_libraries(Engine_Shared PUBLIC engine_external_json base engine_external_zlib)
