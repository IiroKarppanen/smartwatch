zephyr_sources(gc9a01.c)

if(CONFIG_GC9A01)
  # Add GC9A01.h to the set of global include paths.
  #zephyr_include_directories(.)

  zephyr_library()
  zephyr_library_sources(
    gc9a01.c
    )
endif()