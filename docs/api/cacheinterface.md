Cache Interface
====

Overview
----

The cache interface is the central template for the `cachepp` framework. It is a list of features that each cache design must implement in order to take advantage of the 
automated testing suite. The cache interface implements several analytical functions which can be called to check on live cache performance outside the testing suite.

### Template Arguments

The cache interface must be provided with several template arguments in order to be fully user-callable:

* `typename C`

	The internal structure needed to store cache lines, such as a `std::map` or `std::vector`.

* `typename D`

	Each cache may need auxiliary data in a call to accessing the cache, in order to implement custom eviction algorithms. `D` is the type of the class which will 
	provide this feature.

* `typename T`

	The datatype of an implemented `LineInterface` (see [api](lineinterface.md)). This datatype is where data loading and unloading is handled.

### Properties

* `cachepp::identifier size`

	The maximum size heuristic of `typename C`. The API **does not** provide a way to change this field, though obviously this feature could be implemented in a 
	particular instantiation of the interface.

* `bool is_thread_safe`

	It will be desirable for the user to explicitly state the thread-safeness of a particular cache instantiation -- this field is checked in the `TestSuite` (see 
	[api](testinterface.md)) to check if parallel testing is appropriate or not.

* `std::atomic<cachepp::identifier> n_acquire`

	This is incremented every time the cache is called. This field is initialized to `0` in the constructor.

* `std::atomic<cachepp::identifier> n_miss`

	This is incremented every time a cache miss occurs. This field is initialized to `0` in the constructor.

* `C cache`

	The internal structure which will keep track of `LineInterface` implementations.

### Methods

* `(constructor)`

	Creates a `CacheInterface` instance. Initializes `CacheInterface::n_acquire` and `CacheInterface::n_miss` to `0`.

* `r(arg, aux)`

	Takes in a pointer `arg` to an instance of type `T` and auxiliary data `aux` of type `D`, and returns a byte array representing the data which is stored in 
	`arg`. Calls `CacheInterface::acquire` and `CacheInterface::release`.

* `w(arg, val, aux)`

	Takes in a pointer `arg` to an instance of type `T`, a byte array `val`, and auxiliary data `aux`, and sets the data of `arg` to `val`.

* `acquire(arg, aux)`

	Takes in a pointer `arg` to an instance of type `T` and auxiliary data `aux`. Ensures that `arg` is represented in `CacheInterface::cache`.

* `release(arg, aux)`

	Takes in a pointer `arg` to an instance of type `T`. Releases a hold on the cache line storing a representation of `arg` in `CacheInterface::cache`. This does 
	not have to be implemented, but all implementations of `CacheInterface` must contain at least an empty function to fulfill the template.

* `clear()`

	Explicitly flushes `CacheInterface::cache` of all cache lines. Calls `LineInterface::unload` on each cache line.

* `remove(arg)`

	Explicitly flushes `CacheInterface::cache` of a particular cache line.

* `reset()`

	Resets `CacheInterface::n_acquire` and `CacheInterface::n_miss` to `0` **and** calls `CacheInterface::clear`.

* `get_miss_rate()`

	Returns the current miss rate of the cache as a decimal (i.e. between `0` and `1`).

* `get_size()`

	Returns `CacheInterface::size`. **Does not** return the current number of lines represented in `CacheInterface::cache`.

* `get_is_thread_safe()`

	Returns `CacheInterface::is_thread_safe`.

* `access(arg, aux)`

	Takes in a pointer `arg` to an instance of type `T` which is being accessed, and auxiliary data `aux` with any relevant access pattern data for the cache to 
	take into account when selecting a line to evict.

* `in(arg)`

	Takes in a pointer `arg` to an instance of type `T`, and returns whether or not the line exists in the internal cache representation.

* `allocate(arg)`

	Takes in a pointer `arg` to an instance of type `T` -- inserts `arg` into `CacheInterface::cache` if `arg` is not present in the cache.

* `select()`

	Returns a line to be evicted from `CacheInterface::cache` but **does not** evict inside `CacheInterface::select`.

* `heuristic(arg)`

	Takes in a pointer `arg` to an instance of type `T` and returns a recommendation of whether or not `arg` should be evicted. A return value of `0` indicates the 
	line should **not** be evicted. Due to the abstract nature of `cachepp`, this may not have to be an implemented function (though a placeholder function must 
	exist in any implemententation of `CacheInterface` in order to compile).
	
Examples
----

[simpleserialcache](../../include/src/simpleserialcache.h) and [simpleconcurrentcache](../../include/src/simpleconcurrentcache.h) implement `CacheInterface`.

Further Reading
====

* [cacheinterface.h](../../include/src/cacheinterface.h)
* [cacheinterface.template](../../include/src/templates/cacheinterface.template)
* [line interface](lineinterface.md)
* [test suite](testsuite.md)
