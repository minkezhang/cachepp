#include "libs/catch/catch.hpp"
#include "libs/exceptionpp/exception.h"

#include "src/testsuite.h"

TEST_CASE("cachepp|testsuite-testresult") {
	cachepp::TestResult r = cachepp::TestResult();
	REQUIRE_THROWS_AS(r.to_string(), exceptionpp::InvalidOperation);
}
