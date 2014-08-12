#include <atomic>
#include <cstdlib>
#include <memory>
#include <thread>
#include <vector>

#include <iostream>

#include "libs/catch/catch.hpp"
#include "libs/exceptionpp/exception.h"

#include "src/simpleconcurrentcache.h"
#include "src/simpleserialcache.h"
#include "src/simpleline.h"

void concurrentcache_multithread_worker(std::shared_ptr<std::atomic<size_t>> result, std::shared_ptr<cachepp::SimpleConcurrentCache<cachepp::SimpleLine>> c, std::shared_ptr<std::vector<std::shared_ptr<cachepp::SimpleLine>>> v) {
	size_t n_attempts = 1000;
	size_t n_success = 0;

	for(size_t attempt = 0; attempt < n_attempts; ++attempt) {
		cachepp::identifier index = rand() % v->size();
		c->acquire(v->at(index));
		n_success += v->at(index)->get_is_loaded();
		c->release(v->at(index));
	}

	*result += (n_success == n_attempts);
	return;
}


TEST_CASE("cachepp|serialcache") {
	std::shared_ptr<cachepp::SimpleSerialCache<cachepp::SimpleLine>> c (new cachepp::SimpleSerialCache<cachepp::SimpleLine>(2));

	std::vector<std::shared_ptr<cachepp::SimpleLine>> v (0);
	for(size_t i = 0; i < 10; ++i) {
		v.push_back(std::shared_ptr<cachepp::SimpleLine> (new cachepp::SimpleLine(i, false)));
	}

	for(size_t i = 0; i < v.size(); ++i) {
		REQUIRE(v.at(i)->get_is_loaded() == false);
	}

	/**
	 * test cache line juggling
	 */

	for(size_t i = 0; i < v.size(); ++i) {
		c->acquire(v.at(i));
		REQUIRE(v.at(i)->get_is_loaded() == true);
	}

	size_t loaded_lines = 0;
	for(size_t i = 0; i < v.size(); ++i) {
		loaded_lines += v.at(i)->get_is_loaded();
	}

	REQUIRE(loaded_lines == 2);

	c->clear();

	loaded_lines = 0;
	for(size_t i = 0; i < v.size(); ++i) {
		loaded_lines += v.at(i)->get_is_loaded();
	}

	REQUIRE(loaded_lines == 0);

	/**
	 * test selection policy
	 */

	c->acquire(v.at(0));
	c->acquire(v.at(1));

	c->acquire(v.at(0));
	c->acquire(v.at(2));

	REQUIRE(v.at(0)->get_is_loaded() == true);
	REQUIRE(v.at(1)->get_is_loaded() == false);
	REQUIRE(v.at(2)->get_is_loaded() == true);

	c->acquire(v.at(3));

	REQUIRE(v.at(0)->get_is_loaded() == true);
	REQUIRE(v.at(3)->get_is_loaded() == true);

	std::cout << "cachepp|serialcache: " << c->get_miss_rate() << std::endl;
}

TEST_CASE("cachepp|concurrentcache-singlethread") {
	std::shared_ptr<cachepp::SimpleConcurrentCache<cachepp::SimpleLine>> c (new cachepp::SimpleConcurrentCache<cachepp::SimpleLine>(2));

	std::vector<std::shared_ptr<cachepp::SimpleLine>> v (0);
	for(size_t i = 0; i < 10; ++i) {
		v.push_back(std::shared_ptr<cachepp::SimpleLine> (new cachepp::SimpleLine(i, false)));
	}

	for(size_t i = 0; i < v.size(); ++i) {
		REQUIRE(v.at(i)->get_is_loaded() == false);
	}

	/**
	 * test cache line juggling
	 */

	for(size_t i = 0; i < v.size(); ++i) {
		c->acquire(v.at(i));
		REQUIRE(v.at(i)->get_is_loaded() == true);
	}

	size_t loaded_lines = 0;
	for(size_t i = 0; i < v.size(); ++i) {
		loaded_lines += v.at(i)->get_is_loaded();
	}

	REQUIRE(loaded_lines == 2);

	c->clear();

	loaded_lines = 0;
	for(size_t i = 0; i < v.size(); ++i) {
		loaded_lines += v.at(i)->get_is_loaded();
	}

	REQUIRE(loaded_lines == 0);

	/**
	 * test selection policy
	 */

	c->acquire(v.at(0));
	c->acquire(v.at(1));

	c->acquire(v.at(0));
	c->acquire(v.at(2));

	REQUIRE(v.at(0)->get_is_loaded() == true);
	REQUIRE(v.at(1)->get_is_loaded() == false);
	REQUIRE(v.at(2)->get_is_loaded() == true);

	c->acquire(v.at(3));

	REQUIRE(v.at(0)->get_is_loaded() == true);
	REQUIRE(v.at(3)->get_is_loaded() == true);

	std::cout << "cachepp|concurrentcache-singlethread: " << c->get_miss_rate() << std::endl;
}

TEST_CASE("cachepp|concurrentcache-multithread") {
	size_t n_threads = 16;
	size_t n_attempts = 1000;

	std::shared_ptr<cachepp::SimpleConcurrentCache<cachepp::SimpleLine>> c (new cachepp::SimpleConcurrentCache<cachepp::SimpleLine>(2));
	std::shared_ptr<std::vector<std::shared_ptr<cachepp::SimpleLine>>> v (new std::vector<std::shared_ptr<cachepp::SimpleLine>> (0));

	for(size_t i = 0; i < 10; ++i) {
		v->push_back(std::shared_ptr<cachepp::SimpleLine> (new cachepp::SimpleLine(i, false)));
	}

	std::vector<std::shared_ptr<std::thread>> threads;

	std::shared_ptr<std::atomic<size_t>> result (new std::atomic<size_t>());

	std::cout << "cachepp|concurrentcache-multithread: " << std::flush;

	for(size_t attempt = 0; attempt < n_attempts; ++attempt) {
		threads.clear();

		for(size_t i = 0; i < n_threads; ++i) {
			std::shared_ptr<std::thread> t (new std::thread(concurrentcache_multithread_worker, result, c, v));
			threads.push_back(t);
		}

		for(size_t i = 0; i < n_threads; ++i) {
			threads.at(i)->join();
		}

		if((attempt % 100) == 0) {
			std::cout << "." << std::flush;
		}
	}

	std::cout << std::endl;

	REQUIRE(*result == (n_attempts * n_threads));

	std::cout << "cachepp|concurrentcache-multithread: " << c->get_miss_rate() << std::endl;
}
