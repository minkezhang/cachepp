#include <memory>
#include <random>
#include <vector>

#include <iostream>

#include "libs/catch/catch.hpp"
#include "libs/exceptionpp/exception.h"

#include "src/simpleconcurrentcache.h"
#include "src/simpleline.h"
#include "src/simpleserialcache.h"
#include "src/testsuite.h"

TEST_CASE("cachepp|testsuite-testresult") {
	cachepp::TestResult r = cachepp::TestResult();
	REQUIRE_THROWS_AS(r.to_string(), exceptionpp::InvalidOperation);
}

TEST_CASE("cachepp|testsuite-testsuite-correctness") {
	std::shared_ptr<std::vector<std::shared_ptr<cachepp::SimpleLine>>> v (new std::vector<std::shared_ptr<cachepp::SimpleLine>>());
	for(cachepp::identifier i = 0; i < 10; ++i) {
		v->push_back(std::shared_ptr<cachepp::SimpleLine> (new cachepp::SimpleLine(rand(), false)));
	}

	std::shared_ptr<cachepp::SimpleSerialCache<cachepp::SimpleLine>> serial_cache (new cachepp::SimpleSerialCache<cachepp::SimpleLine>(2));
	cachepp::TestSuite<cachepp::SimpleSerialCache<cachepp::SimpleLine>, cachepp::SimpleSerialCacheData, cachepp::SimpleLine> serial_cache_suite = cachepp::TestSuite<cachepp::SimpleSerialCache<cachepp::SimpleLine>, cachepp::SimpleSerialCacheData, cachepp::SimpleLine>(serial_cache);

	REQUIRE_THROWS_AS(serial_cache_suite.correctness(v, 1, true, 2), exceptionpp::InvalidOperation);
	REQUIRE_THROWS_AS(serial_cache_suite.correctness(v, 1, false, 2), exceptionpp::InvalidOperation);

	serial_cache_suite.correctness(v, 1000, false);

	std::shared_ptr<cachepp::SimpleConcurrentCache<cachepp::SimpleLine>> concurrent_cache (new cachepp::SimpleConcurrentCache<cachepp::SimpleLine>(2));
	cachepp::TestSuite<cachepp::SimpleConcurrentCache<cachepp::SimpleLine>, cachepp::SimpleConcurrentCacheData, cachepp::SimpleLine> concurrent_cache_suite = cachepp::TestSuite<cachepp::SimpleConcurrentCache<cachepp::SimpleLine>, cachepp::SimpleConcurrentCacheData, cachepp::SimpleLine>(concurrent_cache);

	concurrent_cache_suite.correctness(v, 1000, false);
	// concurrent_cache_suite.correctness(v, 1000000, true, 16);

	std::shared_ptr<std::vector<cachepp::identifier>> pattern = concurrent_cache_suite.generate_access_pattern(256, 10000);
	REQUIRE(pattern->size() == 10000);
	for(size_t i = 0; i < pattern->size(); ++i) {
		REQUIRE(pattern->at(i) >= 0);
		REQUIRE(pattern->at(i) < 256);
	}
}
