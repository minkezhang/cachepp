#include "libs/catch/catch.hpp"
#include "libs/exceptionpp/exception.h"

#include "src/line.h"

TEST_CASE("cachepp|line") {
	cachepp::SimpleLine s = cachepp::SimpleLine(111, false);

	REQUIRE(s.get_is_loaded() == false);
	REQUIRE(s.get_is_dirty() == false);
	REQUIRE_THROWS_AS(s.get_data(), exceptionpp::RuntimeError);
	s.load();
	REQUIRE(s.get_is_loaded() == true);
	REQUIRE(s.get_data()->at(0) == 111);
	s.load();
	REQUIRE(s.get_is_loaded() == true);
	s.unload();
	REQUIRE(s.get_is_loaded() == false);
	REQUIRE(s.get_is_dirty() == true);
	s.unload();
	REQUIRE(s.get_is_loaded() == false);
	s.load();
	REQUIRE(s.get_is_loaded() == true);

	cachepp::SimpleLine t = cachepp::SimpleLine(112, true);
	t.load();
	t.unload();
	REQUIRE(t.get_is_dirty() == true);
	REQUIRE_THROWS_AS(t.load(), exceptionpp::RuntimeError);
}
