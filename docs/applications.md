Applications
====

`cachepp` provides an abstraction system for both caches and cache data -- as such, a great degree of freedom is afforded to the programmer, whether in research or 
development.

Caching the Cloud
----

`LineInterface::aux_load` and `LineInterface::aux_unload` are completely abstracted from the loading process of data -- as such, we can create a subclass of 
`LineInterface`:

```cpp
class NetworkLine {
	private:
		std::string endpoint;
		std::string username;
		std::string password;

		virtual void aux_load() final;
		virtual void aux_unload() final;
};
```

Which, upon calling `NetworkLine::aux_load`, will connect to the appropriate server (provided by `NetworkLine::endpoint`) with the user credentials and pull data from a 
remote server. Likewise, `NetworkLine::aux_unload` will be able to push to a remote server.

Cache Performance Research
----

The automated testing suite provides a great deal of convenience to the programmer, as it tests the exposed `CacheInterface` functions for expected behavior, and can run 
performance tests on the provided `CacheInterface` implementation with a great degree of customization. The results given by the test suite will provide researchers and 
developers with both ease-of-mind in the correctness of their model, and bolster their confidence in the effiency of their cache eviction design.

Active Learning
----

Students can use the framework to implement canonical caches and to test their implementations without having to build the framework basics again. This will allow such 
students to gain hands-on experience with the inner workings of efficient cache design without being bogged down by segfaults and pointer chasing.

Further Reading
----

* [api](api/index.md)
* [planned features](future.md)
