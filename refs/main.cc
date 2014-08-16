#include <iostream>
#include <random>
#include <string>

#include "libs/cachepp/simpleline.h"
#include "libs/cachepp/testsuite.h"

#include "src/filedata.h"
#include "src/lru.h"

void test_correctness(const std::shared_ptr<LRUCache<FileData>>& c) {

	std::shared_ptr<std::vector<std::shared_ptr<FileData>>> l (new std::vector<std::shared_ptr<FileData>>());
	for(size_t i = 0; i < 10; ++i) {
		l->push_back(std::shared_ptr<FileData> (new FileData(rand(), "files/foo")));
	}

	auto t = cachepp::TestSuite<LRUCache<FileData>, LRUCacheData, FileData>(c);

	t.correctness(l, 1000, false);
}

void test_performance(const std::shared_ptr<LRUCache<FileData>>& c) {
	std::shared_ptr<std::vector<std::shared_ptr<FileData>>> l (new std::vector<std::shared_ptr<FileData>>());
	l->push_back(std::shared_ptr<FileData> (new FileData(rand(), "files/foo")));
	l->push_back(std::shared_ptr<FileData> (new FileData(rand(), "files/bar")));

	auto t = cachepp::TestSuite<LRUCache<FileData>, LRUCacheData, FileData>(c);

	std::shared_ptr<std::vector<size_t>> rnd_access (new std::vector<size_t> { 0, 1, 0, 0, 1, 0, 1 });
	std::shared_ptr<std::vector<size_t>> sam_access (new std::vector<size_t> { 1, 1, 1, 1, 1, 1, 1 });

	// don't supply any auxiliary data for the access pattern
	std::shared_ptr<std::vector<std::shared_ptr<LRUCacheData>>> aux (new std::vector<std::shared_ptr<LRUCacheData>>());

	for(size_t i = 0; i < 10; ++i) {
		// each line's data is capped at 128 bytes
		std::shared_ptr<std::vector<size_t>> l_size (new std::vector<size_t> (10, 1024 * (2 * (i + 1))));

		t.performance("RND", l, l_size, rnd_access, aux, .5, 1000, false);
		t.performance("SAM", l, l_size, sam_access, aux, .5, 1000, false);
	}

	std::cout << t.get_result().to_string(false);
}

int main() {
	// test to make sure LRUCache is okay
	std::shared_ptr<LRUCache<cachepp::SimpleLine>> c (new LRUCache<cachepp::SimpleLine>(1));

	// compiler will return an error on non-pointer instances of the cache (LRUCache<FileData> d ...)
	std::shared_ptr<LRUCache<FileData>> d (new LRUCache<FileData>(1));

	// CacheInterface::r has the default D() aux data argument as input
	std::shared_ptr<FileData> foo (new FileData(1, "files/foo"));
	std::shared_ptr<FileData> bar (new FileData(2, "files/bar"));

	// read some data
	std::vector<uint8_t> foo_buf = d->r(foo);
	std::vector<uint8_t> bar_buf = d->r(bar);

	// output
	std::cout << std::string(foo_buf.begin(), foo_buf.end()) << std::endl;
	std::cout << std::string(bar_buf.begin(), bar_buf.end()) << std::endl;

	// write some data
	d->w(bar, std::vector<uint8_t> { 'b', 'a', 'z', '\n' });

	// unload the data
	d->remove(bar);

	// load into the cache agian
	std::vector<uint8_t> baz_buf = d->r(bar);

	// assert the changes have been made
	std::cout << std::string(baz_buf.begin(), baz_buf.end()) << std::endl;

	d->w(foo, std::vector<uint8_t> { 'f', 'o', 'o', '\n'});
	d->w(bar, std::vector<uint8_t> { 'b', 'a', 'r', '\n'});
	d->clear();

	test_correctness(d);
	test_performance(d);

	// reset the files
	d->w(foo, std::vector<uint8_t> { 'f', 'o', 'o', '\n'});
	d->w(bar, std::vector<uint8_t> { 'b', 'a', 'r', '\n'});
	d->clear();

	return(0);
}
