add_library(game_shared
        STATIC)

target_sources(game_shared
        PRIVATE
        collision.cpp
        gamecore.cpp
        layers.cpp

        PUBLIC
        collision.h
        commands.h
        gamecore.h
        layers.h
        mapitems.h
        tuning.h
        variables.h
        version.h
        voting.h
)

target_link_libraries(game_shared PUBLIC base engine_shared)