#include "libs/catch/catch.hpp"
#include "libs/exceptionpp/exception.h"

#include "src/cache.h"
#include "src/line.h"

TEST_CASE("cachepp|line") {
	REQUIRE_THROWS_AS(std::shared_ptr<cachepp::SimpleNChanceCache<cachepp::SimpleLine>> c (new cachepp::SimpleNChanceCache<cachepp::SimpleLine>(10)), exceptionpp::RuntimeError);
	// REQUIRE_THROWS_AS(std::shared_ptr<cachepp::SimpleNChanceCache<cachepp::SimpleLine>> c (new cachepp::SimpleNChanceCache<cachepp::SimpleLine>(10)), exceptionpp::RuntimeError);
}
