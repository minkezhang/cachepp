#include "libs/catch/catch.hpp"
#include "libs/exceptionpp/exception.h"

#include "src/simpleline.h"

TEST_CASE("cachepp|line") {
	std::shared_ptr<cachepp::SimpleLine> s (new cachepp::SimpleLine(111, false));

	REQUIRE(s->get_is_loaded() == false);
	REQUIRE(s->get_is_dirty() == false);
	REQUIRE_THROWS_AS(s->get_data(), exceptionpp::RuntimeError);
	REQUIRE_THROWS_AS(s->set_data(std::vector<uint8_t> (0)), exceptionpp::RuntimeError);
	s->load();
	REQUIRE(s->get_is_loaded() == true);
	REQUIRE(s->get_data().at(0) == 111);

	s->load();
	REQUIRE(s->get_is_loaded() == true);

	s->unload();
	REQUIRE(s->get_is_loaded() == false);
	REQUIRE(s->get_is_dirty() == false);

	s->unload();
	REQUIRE(s->get_is_loaded() == false);

	s->load();
	REQUIRE(s->get_is_loaded() == true);

	s->set_data(std::vector<uint8_t>());
	REQUIRE(s->get_is_dirty() == true);

	s->unload();
	s->load();

	std::shared_ptr<cachepp::SimpleLine> t (new cachepp::SimpleLine(111, true));

	t->load();
	t->set_data(std::vector<uint8_t>());
	t->unload();

	REQUIRE(t->get_is_dirty() == true);

	REQUIRE_THROWS_AS(t->load(), exceptionpp::RuntimeError);
}
