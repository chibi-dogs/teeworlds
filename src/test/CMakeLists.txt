  enable_testing()

  add_executable(
          tests
          hash_tests.cpp
  )
  target_link_libraries(
          tests
          GTest::gtest_main
          Base
  )

  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(tests PRIVATE -fsanitize=address,undefined -g -O1)
    target_link_options(tests PRIVATE -fsanitize=address,undefined)
  endif()

  include(GoogleTest)
  gtest_discover_tests(tests)