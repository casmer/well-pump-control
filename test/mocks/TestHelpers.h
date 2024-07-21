
#ifndef MOCKS_TEST_HELPERS
#define MOCKS_TEST_HELPERS

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

#define TEST_ASSERT_EQ_ENH(expected, actual)  TEST_ASSERT_EQUAL_MESSAGE(expected, actual, ("Expected [" #expected "] on line " __FILE__ ":" LINE_STRING));
#endif //MOCKS_TEST_HELPERS