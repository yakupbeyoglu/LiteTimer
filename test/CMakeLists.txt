include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

option(ENABLE_ADDRESS_SANITIZER "Enable address sanitizer" ON)
enable_testing()


set(SOURCE
  timer.cc
  priority_queue.cc
)

set(TEST_NAME lite_timer_test)
add_executable(${TEST_NAME} ${SOURCE})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/ DESTINATION include)

target_link_libraries(
  ${TEST_NAME}
  GTest::gtest_main
)

set(COMPILER_OPTIONS
  -Wall
  -Wextra
  -Werror
  -Wshadow
  -Wpedantic
  -pedantic-errors
)

target_compile_options(${TEST_NAME} PRIVATE -fsanitize=address)
target_link_options(${TEST_NAME} PRIVATE -fsanitize=address)


# Below for running on build using ctest
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})

if(ENABLE_ADDRESS_SANITIZER)
target_compile_options(${TEST_NAME} PRIVATE -fsanitize=address)
target_link_options(${TEST_NAME} PRIVATE -fsanitize=address)
endif(ENABLE_ADDRESS_SANITIZER)
