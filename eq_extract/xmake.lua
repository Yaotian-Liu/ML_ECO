add_rules("mode.release", "mode.debug")
target("eq_extract")
    set_kind("binary")

    set_targetdir(".")
    set_languages("c")
    add_toolchains("clang")
    add_cflags("-Wall -Wno-unused-function -Wno-write-strings -Wno-sign-compare")

    if is_mode("debug") then
        set_optimize("none")
    end

    if is_mode("release") then
        set_optimize("fastest")
    end

    add_includedirs("../abc/src")

    add_linkdirs("../abc")
    add_rpathdirs("../abc")
    add_links("abc")
    add_links("m")
    add_links("dl")
    add_links("readline")
    add_links("pthread")

    -- Refer to ../abc/Makefile
    add_defines("LIN64")
    add_defines("SIZEOF_VOID_P=8")
    add_defines("SIZEOF_LONG=8")
    add_defines("SIZEOF_INT=4")
    add_defines("ABC_USE_CUDD=1")
    add_defines("ABC_USE_READLINE")
    add_defines("ABC_USE_PTHREADS")

    add_includedirs("src/")
    add_headerfiles("src/**.h")
    add_files("src/**.c")
    add_files("main.c")