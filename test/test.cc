#include <iostream>

#include "libs/catch/catch.hpp"
#include "libs/exceptionpp/exception.h"

#include "src/testsuite.h"

TEST_CASE("cachepp|testsuite-testresult") {
	cachepp::TestResult r = cachepp::TestResult();
	REQUIRE_THROWS_AS(r.to_string(), exceptionpp::InvalidOperation);
	r.push_back(1000, 1000, .5, .5, 10, 1000, 0, 0);
	r.push_back(1000, 1000, .5, .5, 10, 1000, 1, 10);
	std::cout << r;
}
