Testing the Cache
====

Before we start testing, let us consider how to use this cache in a coding project:

```cpp
/* src/main.cc */

#include <string>

#include "libs/cachepp/testsuite.h"

#include "src/filedata.h"
#include "src/lrucache.h"

int main() {
	// 10-line cache
	auto c = LRUCache<SimpleData>(1);
	std::shared_ptr<FileData> foo (new FileData("files/foo"));
	std::shared_ptr<FileData> bar (new FileData("files/bar"));

	// CacheInterface::r has the default D() aux data argument as input
	std::cout << c.r(foo) << std::endl;

	// swap out foo for bar in the cache
	std::cout << c.r(bar) << std::endl;

	c.w(bar, "baz");

	// unload the data
	c.remove(bar);

	// reload the data into the cache
	std::cout << c.r(bar) << std::endl;

	return(0);
}
```

We would like to ensure that `LRUCache` is doing what it's suppose to:

```cpp
void test_correctness() {
	std::shared_ptr<LRUCache<SimpleData>> c (new LRUCache<SimpleData>(2));
	std::shared_ptr<std::vector<FileData>> l (new std::vector<FileData> (10, std::shared_ptr<FileData> (new FileData("files/foo"))));

	auto t = TestSuite(c);

	t->correctness(l, 1000, false);
}
```

What about performance?

```cpp
void test_performance() {
	std::shared_ptr<LRUCache<SimpleData>> c (new LRUCache<SimpleData>(2));
	std::shared_ptr<std::vector<FileData>> l (new std::vector<FileData> (10, std::shared_ptr<FileData> (new FileData("files/foo"))));

	// each line's data is capped at 128 bytes
	std::shared_ptr<std::vector<size_t>> l_size (new std::vector<size_t> (10, 128));

	std::shared_ptr<std::vector<size_t>> rnd_access (new std::vector<size_t> { 0, 9, 5, 3, 2, 5, 8 });
	std::shared_ptr<std::vector<size_t>> sam_access (new std::vector<size_t> { 1, 1, 1, 1, 1, 1, 1 });

	// don't supply any auxiliary data for the access pattern
	std::shared_ptr<std::vector<std::shared_ptr<LRUCacheData>>> aux (new std::vector<std::shared_ptr<LRUCacheData>());

	auto t = TestSuite(c);

	t->performance("RND", l, l_size, rnd_access, aux, .5, 1000, false);
	t->performance("SAM", l, l_size, sam_access, aux, .5, 1000, false);

	std::cout << t->get_result()->to_string(false);
}
```

Further Reading
----

* Prev -- [Implementing the Line Interface](line.md)
