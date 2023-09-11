set(TARGET Main)
set(OUTPUT_NAME Main)

set(SOURCE_FILES main.cpp)

add_executable(${TARGET} ${SOURCE_FILES})

target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
									 PRIVATE $<TARGET_PROPERTY:Logger,SOURCE_DIR>/..)
