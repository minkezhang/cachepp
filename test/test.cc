#include "libs/catch/catch.hpp"
#include "libs/exceptionpp/exception.h"

#include "src/simpleline.h"
#include "src/simpleserialcache.h"
#include "src/testsuite.h"

TEST_CASE("cachepp|testsuite-testresult") {
	cachepp::TestResult r = cachepp::TestResult();
	REQUIRE_THROWS_AS(r.to_string(), exceptionpp::InvalidOperation);
	REQUIRE_THROWS_AS(r.push_back(1000, 10, 1000, .5, .5, 128, 1000, true, 0), exceptionpp::InvalidOperation);
	REQUIRE_THROWS_AS(r.push_back(1000, 10, 1000, .5, .5, 128, 1000, false, 1), exceptionpp::InvalidOperation);
}

TEST_CASE("cachepp|testsuite-testsuite") {
	std::shared_ptr<cachepp::SimpleSerialCache<cachepp::SimpleLine>> c (new cachepp::SimpleSerialCache<cachepp::SimpleLine>(2));
	cachepp::TestSuite<cachepp::SimpleSerialCache<cachepp::SimpleLine>, cachepp::SimpleSerialCacheData, cachepp::SimpleLine> s = cachepp::TestSuite<cachepp::SimpleSerialCache<cachepp::SimpleLine>, cachepp::SimpleSerialCacheData, cachepp::SimpleLine>(c);
}
