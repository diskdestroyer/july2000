include_directories("${CMAKE_CURRENT_LIST_DIR}/")

# dll code
if(HOOKS)
        add_definitions(-DHOOKS)
        set(SRC_HOOKS "hooks/dllmain.cpp"
                      "hooks/hook.cpp"
                      "hooks/init_hooks.cpp")
endif()

# cncnet code
if(CNCNET)
        add_definitions(-DCNCNET)
        set(SRC_CNCNET "cncnet/ini.cpp"
                       "cncnet/d2kini.cpp")
endif()

# game code
set(SRC_CODE "code/cd.cpp"
             "code/file.cpp"
             "code/globals.cpp"
             "code/memory.cpp"
             "code/particle.cpp")

set(SRC_ALL "${SRC_ALL}" "${SRC_HOOKS}" "${SRC_CNCNET}" "${SRC_CODE}")

if(HOOKS)
        add_library(july2000 SHARED "${SRC_ALL}")
else()
        add_executable(july2000 "${SRC_ALL}")
endif()
