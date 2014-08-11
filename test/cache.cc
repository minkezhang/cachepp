#include <cstdlib>
#include <memory>
#include <vector>

#include "libs/catch/catch.hpp"
#include "libs/exceptionpp/exception.h"

#include "src/simpleconcurrentcache.h"
#include "src/simpleserialcache.h"
#include "src/simpleline.h"

TEST_CASE("cachepp|concurrentcache") {
	std::shared_ptr<cachepp::SimpleConcurrentCache<cachepp::SimpleLine>> c (new cachepp::SimpleConcurrentCache<cachepp::SimpleLine>(2));

	std::vector<std::shared_ptr<cachepp::SimpleLine>> v;
	for(size_t i = 0; i < 10; ++i) {
		v.push_back(std::shared_ptr<cachepp::SimpleLine> (new cachepp::SimpleLine(rand(), false)));
	}

	for(size_t i = 0; i < 10; ++i) {
		REQUIRE(v.at(i)->get_is_loaded() == false);
	}

	// test cache line juggling
	for(size_t i = 0; i < 10; ++i) {
		c->acquire(v.at(i));
		REQUIRE(v.at(i)->get_is_loaded() == true);
	}

	size_t loaded_lines = 0;
	for(size_t i = 0; i < 10; ++i) {
		loaded_lines += v.at(i)->get_is_loaded();
	}

	REQUIRE(loaded_lines == 2);

	c->clear();

	loaded_lines = 0;
	for(size_t i = 0; i < 10; ++i) {
		loaded_lines += v.at(i)->get_is_loaded();
	}

	REQUIRE(loaded_lines == 0);

	// test selection policy
	c->acquire(v.at(0));
	c->acquire(v.at(1));

	REQUIRE_THROWS_AS(c->access(v.at(2)), exceptionpp::RuntimeError);

	c->access(v.at(0));
	c->acquire(v.at(2));

	REQUIRE(v.at(0)->get_is_loaded() == true);
	REQUIRE(v.at(1)->get_is_loaded() == false);
	REQUIRE(v.at(2)->get_is_loaded() == true);

	c->acquire(v.at(3));

	REQUIRE(v.at(0)->get_is_loaded() == false);
	REQUIRE(v.at(2)->get_is_loaded() == true);
	REQUIRE(v.at(3)->get_is_loaded() == true);
}

TEST_CASE("cachepp|serialcache") {
	std::shared_ptr<cachepp::SimpleSerialCache<cachepp::SimpleLine>> c (new cachepp::SimpleSerialCache<cachepp::SimpleLine>(2));

	std::vector<std::shared_ptr<cachepp::SimpleLine>> v;
	for(size_t i = 0; i < 10; ++i) {
		v.push_back(std::shared_ptr<cachepp::SimpleLine> (new cachepp::SimpleLine(rand(), false)));
	}

	for(size_t i = 0; i < 10; ++i) {
		REQUIRE(v.at(i)->get_is_loaded() == false);
	}

	// test cache line juggling
	for(size_t i = 0; i < 10; ++i) {
		c->acquire(v.at(i));
		REQUIRE(v.at(i)->get_is_loaded() == true);
	}

	size_t loaded_lines = 0;
	for(size_t i = 0; i < 10; ++i) {
		loaded_lines += v.at(i)->get_is_loaded();
	}

	REQUIRE(loaded_lines == 2);

	c->clear();

	loaded_lines = 0;
	for(size_t i = 0; i < 10; ++i) {
		loaded_lines += v.at(i)->get_is_loaded();
	}

	REQUIRE(loaded_lines == 0);

	// test selection policy
	c->acquire(v.at(0));
	c->acquire(v.at(1));

	REQUIRE_THROWS_AS(c->access(v.at(2)), exceptionpp::RuntimeError);

	c->access(v.at(0));
	c->acquire(v.at(2));

	REQUIRE(v.at(0)->get_is_loaded() == true);
	REQUIRE(v.at(1)->get_is_loaded() == false);
	REQUIRE(v.at(2)->get_is_loaded() == true);

	c->acquire(v.at(3));

	REQUIRE(v.at(0)->get_is_loaded() == false);
	REQUIRE(v.at(2)->get_is_loaded() == true);
	REQUIRE(v.at(3)->get_is_loaded() == true);
}
