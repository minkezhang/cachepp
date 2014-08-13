#include <vector>

#include "libs/catch/catch.hpp"
#include "libs/exceptionpp/exception.h"

#include "src/simpleline.h"
#include "src/simpleserialcache.h"
#include "src/testsuite.h"

TEST_CASE("cachepp|testsuite-testresult") {
	cachepp::TestResult r = cachepp::TestResult();
	REQUIRE_THROWS_AS(r.to_string(), exceptionpp::InvalidOperation);
}

TEST_CASE("cachepp|testsuite-testsuite") {
	std::shared_ptr<cachepp::SimpleSerialCache<cachepp::SimpleLine>> c (new cachepp::SimpleSerialCache<cachepp::SimpleLine>(2));
	cachepp::TestSuite<cachepp::SimpleSerialCache<cachepp::SimpleLine>, cachepp::SimpleSerialCacheData, cachepp::SimpleLine> s = cachepp::TestSuite<cachepp::SimpleSerialCache<cachepp::SimpleLine>, cachepp::SimpleSerialCacheData, cachepp::SimpleLine>(c);

	REQUIRE_THROWS_AS(s.correctness(std::vector<cachepp::SimpleLine>(), 1, true, 2), exceptionpp::InvalidOperation);
	REQUIRE_THROWS_AS(s.correctness(std::vector<cachepp::SimpleLine>(), 1, false, 2), exceptionpp::InvalidOperation);
}
