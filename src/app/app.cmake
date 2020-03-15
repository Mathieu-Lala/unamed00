function(make_app app_name)

    set(APP_SRC
        src/app/main.cpp
        src/app/Core.cpp
        src/app/shell/Parser.cpp
        src/app/shell/Reader.cpp
    )

    add_executable(${app_name} ${APP_SRC})

endfunction()
