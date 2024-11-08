cmake_minimum_required(VERSION 3.28)
project(iarullin)

#if (WIN32)
if (MSVC)
    # https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
    list(APPEND compiler_flags
        "/WX" "/W4" "/permissive-" "/Za" "/fsanitize=address"

        # (not necessary) for runtime library static linkage
        "/MT"

        # (not necessary) use c++20
        "/std:c++20"
    )
else()
    list(APPEND compiler_flags
        # It is impossible to include all GCC warnings
        # https://stackoverflow.com/a/11720263
        "-Werror" "-Wall" "-Wextra" "-pedantic" "-fsanitize=address"
        "-static-libasan"

        # (not necessary) use c++20
        "-std=c++20"
    )
    list(APPEND linker_flags
        "-fsanitize=address"
        )
endif()

add_executable(iarullin gridlab.cpp)
target_compile_options(iarullin PRIVATE ${compiler_flags})
target_link_options(iarullin PRIVATE ${linker_flags})
