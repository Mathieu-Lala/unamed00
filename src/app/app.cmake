function(make_app app_name)

    set(APP_SRC
        src/app/main.cpp
    )

    add_executable(${app_name} ${APP_SRC})

endfunction()
