add_library(Engine_Interface INTERFACE)
target_sources(Engine_Interface
        INTERFACE
        client.h
        config.h
        console.h
        contacts.h
        demo.h
        editor.h
        engine.h
        graphics.h
        input.h
        kernel.h
        keys.h
        map.h
        mapchecker.h
        masterserver.h
        message.h
        server.h
        serverbrowser.h
        sound.h
        storage.h
        textrender.h
)

add_subdirectory(external)
add_subdirectory(shared)