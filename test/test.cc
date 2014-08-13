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

	REQUIRE(r.get_size() == 0);
	REQUIRE_THROWS_AS(r.to_string(), exceptionpp::InvalidOperation);

	r.push_back(1, 1, 1, 1, 1, 1, 1, 1, 2);
	REQUIRE(r.get_size() == 1);
}

TEST_CASE("cachepp|testsuite-testsuite-correctness") {
	std::shared_ptr<std::vector<std::shared_ptr<cachepp::SimpleLine>>> v (new std::vector<std::shared_ptr<cachepp::SimpleLine>>());
	for(cachepp::identifier i = 0; i < 256; ++i) {
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
}

TEST_CASE("cachepp|testsuite-testsuite-performance") {
	std::shared_ptr<std::vector<std::shared_ptr<cachepp::SimpleLine>>> v (new std::vector<std::shared_ptr<cachepp::SimpleLine>>());
	for(cachepp::identifier i = 0; i < 256; ++i) {
		v->push_back(std::shared_ptr<cachepp::SimpleLine> (new cachepp::SimpleLine(rand(), false)));
	}

	std::shared_ptr<cachepp::SimpleConcurrentCache<cachepp::SimpleLine>> concurrent_cache (new cachepp::SimpleConcurrentCache<cachepp::SimpleLine>(2));
	cachepp::TestSuite<cachepp::SimpleConcurrentCache<cachepp::SimpleLine>, cachepp::SimpleConcurrentCacheData, cachepp::SimpleLine> concurrent_cache_suite = cachepp::TestSuite<cachepp::SimpleConcurrentCache<cachepp::SimpleLine>, cachepp::SimpleConcurrentCacheData, cachepp::SimpleLine>(concurrent_cache);

	std::shared_ptr<std::vector<cachepp::identifier>> access_pattern = concurrent_cache_suite.generate_access_pattern(v->size(), 10000);
	REQUIRE(access_pattern->size() == 10000);
	for(size_t i = 0; i < access_pattern->size(); ++i) {
		REQUIRE(access_pattern->at(i) >= 0);
		REQUIRE(access_pattern->at(i) < v->size());
	}

	std::shared_ptr<std::vector<size_t>> line_size (new std::vector<size_t>(v->size(), 256));
	std::shared_ptr<std::vector<std::shared_ptr<cachepp::SimpleConcurrentCacheData>>> access_pattern_aux (new std::vector<std::shared_ptr<cachepp::SimpleConcurrentCacheData>>());

	REQUIRE_THROWS_AS(concurrent_cache_suite.performance(v, line_size, access_pattern, access_pattern_aux, .5, 1000, true, 0), exceptionpp::InvalidOperation);
	REQUIRE_THROWS_AS(concurrent_cache_suite.performance(v, line_size, access_pattern, access_pattern_aux, .5, 1000, false, 1), exceptionpp::InvalidOperation);

	concurrent_cache_suite.performance(v, line_size, access_pattern, access_pattern_aux, .5, 1, false, 0);
	concurrent_cache_suite.performance(v, line_size, access_pattern, access_pattern_aux, .5, 4, false, 0);
	std::cout << concurrent_cache_suite.get_result().to_string();
}
