
#ifndef MOCKS_TEST_HELPERS
#define MOCKS_TEST_HELPERS

/// @brief returns the number of milliseconds in the provided value for minutes
#define MINUTES_ms(minutes) (minutes * 1000 * 60)
/// @brief returns the number of milliseconds in the provided value for seconds
#define SECONDS_ms(seconds) (seconds * 1000)
#endif //MOCKS_TEST_HELPERS