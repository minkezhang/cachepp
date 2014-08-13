#include <memory>
#include <random>
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

	std::vector<std::shared_ptr<cachepp::SimpleLine>> v;
	for(cachepp::identifier i = 0; i < 10; ++i) {
		v.push_back(std::shared_ptr<cachepp::SimpleLine> (new cachepp::SimpleLine(rand(), false)));
	}

	REQUIRE_THROWS_AS(s.correctness(v, 1, true, 2), exceptionpp::InvalidOperation);
	REQUIRE_THROWS_AS(s.correctness(v, 1, false, 2), exceptionpp::InvalidOperation);

	s.correctness(v, 1000, false);
}
