Beginner's Guide
====

Motivation
----

`cachepp` is an exercise in good interface design, and an attempt is made to unify the way in which different caches behave. Though numerous caching libraries exist, 
there does not seem to be a similar demand for caching *frameworks* -- that is, something that will allow the developer to easily design their own cache. Moreover, these 
caching libraries are almost always written in languages such as Java and Python, with little to no attention paid to the C++ community.

On Work Required
----

**`cachepp` still requires a programmer to write a cache.** This is a *framework*, not a *library*, in the sense that the end functionality needed (caching) is **not** 
provided. A *scaffold* is given to the programmer instead -- the programmer is expected to build a cache around the scaffold, much like many websites and network 
applications are built around their own frameworks -- [CakePHP](http://cakephp.org/), [Node.js](http://nodejs.org/), etc.

Interface Basics
----

In return for this additional level of indirection, programmers who *do* use the framework provided will be able to **easily share their cache designs** with 
everyone else who also use the same framework. This is important, as `cachepp` makes a clear distinction between the *cache* and the *data* -- that is, the cache is 
*data-agnostic*. Therefore, any caches designed using this framework **will be able to be drop-deployable* to any other application also using `cachepp`**

One such "application" which takes advantage of this standardized interface is the testing suite provided within the framework -- because each cache a programmer writes 
within `cachepp` has expected functionality, then once an application is built around the *interface*, that application automatically supports *all* cache designs.

In order for the cache to interact with data in an agnostic way, `cachepp` also provides the *data interface* which data structs will have to conform to. However, the 
structure itself is general enough that *arbitrary data* can be stored in the cache, as long as the appropriate `load` and `unload` functions are provided for the data. 
This means that **the data endpoint is generalized** -- the cache doesn't care if data resides locally in the hard drive, or halfway around the world -- as long as the 
data loads and unloads in the expected manner, the actual data itself will be treated equally in the cache.

Example
----

But enough talk -- often it is easier to demonstrate the advantages of a framework rather than explaining in words. Let us consider some use-case of a cache: a browser 
(e.g. Chrome or Firefox) which will need to keep track of all the tabs open. Let us suppose that the original cache design for this browser was *random eviction*. The 
programmer diligently writes code for this cache and fills in all the virtual functions of the cache and data interfaces:

```cpp
class RandomEvictCache : cachepp::CacheInterface<...> { ... };
class TabData : cachepp::LineInterface<...> { ... };
```

After uisng this cache in development for several days, the programmer decides to run the test suite on this cache to test performance:

```cpp
auto test = cachepp::TestSuite(RandomEvictCache<TabData>(...));
test.correctness(...);
test.performance(...);
std::cout << test.get_result().to_string();
```

Unfortunately, he sees that this cache performs quite poorly.

After several days, this programmer comes up with an LRU cache which also conforms to the `cachepp` interface:

```cpp
class LRUCache : cachepp::CacheInterface<...> { ... };
```

In order to test this new cache, the programmer runs:

```
auto test = cachepp::TestSuite(LRUCache<TabData>(...));
test.correctness(...);
test.performance(...);
std::cout << test.get_result().to_string();
```

**Every other line in the test suite invocation remains the same.** After running these tests, the programmer decides he is much happier with the LRU cache performance 
than with the cache with random eviction. Going back to his application, he simply finds all instances of `RandomEvictCache` and change the constructor to `LRUCache`.

Let us then consider this programmer's friend who also uses `cachepp` -- for some reason or another, the friend requires the use of a random eviction cache on file i/o 
data. The friend conformed to the data interface, but could not come up with a random eviction cache. After hearing the friend's problem, the programmer in question 
simply shares his `RandomEvictCache` header and template declarations with his friend, who can now (with very little work) drop in this random eviction cache into his 
application:

```cpp
#include "dropin/randomcache.h"

auto c = RandomEvictCache<FileIOData>(...);
```

The friend **did not need to adjust the cache to handle separate data** -- this was all done for him inside the C++ template system.

For a more in-depth look at building from the framework, see the [tutorial](docs/tutorial/index.md).

Installation
----

Get a copy of the `cachepp` framework library, including all dependencies.

```bash
git clone https://github.com/cripplet/cachepp.git
cd cachepp
git submodule update --init --recursive
make test
```

Updating
----

Updating the framework and all dependencies.

```bash
git pull
git submodule foreach --recursive git checkout master
git submodule foreach --recursive git pull
```

Further Reading
----

* [applications](applications.md) -- a list of possible use-cases for this framework
* [api](api/index.md) -- the API documentation index
* [file structure](structure.md) -- a walkthrough of the folder hierarchy in this library
* [planned features](future.md)
* [tutorial](tutorial/index.md)
