  enable_testing()

  add_executable(
          tests
          hash.cpp
  )
  target_link_libraries(
          tests
          GTest::gtest_main
          Base
  )

  include(GoogleTest)
  gtest_discover_tests(tests)