Applications
====

`cachepp` provides an abstraction system for both caches and cache data -- as such, a great degree of freedom is afforded to the programmer, whether in research or 
development.

Caching the Cloud
----

`LineInterface::aux_load` and `LineInterface::aux_unload` are completely abstracted from the loading process of data -- as such, we can create a subclass of 
`LineInterface`:

```cpp
class NetworkLine : public LineInterface<...> {
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

Hierarchical Caching
----

Just as the L1 caches the L2, which caches L3 or RAM, so too we may desire a hierarchical caching schema for certain applications. We can accomplish this within 
`cachepp` by the use of *variadic templates*:

```cpp
// C and D have their usual template argument meanings
template <typename T1, typename... Tn>
class HierarchicalCache : public CacheInterface<C, D, T1> {
	public:
		HierarchicalCache(Tn&... data_types);
	private:
		HierarchicalCache<Tn> next;
		virtual void allocate(arg) final;
}

template <typename T1, typename... Tn>HierarchicalCache<T1, Tn>::HierarchicalCache(Tn&... data_types) {
	if(sizeof...(data_types)) == 0 {
		this->next = NULL;
	} else {
		this->next = HierarchicalCache<data_types>(...);
	}
}

template <typename T1, typename... Tn>HierarchicalCache<T1, Tn>::allocate(arg) {
	if(this->next != NULL) {
		this->next.allocate(arg);
	} else { ... }
}
```

Here, `typename T1` is the type of the first level of data, and `typename... Tn` represents the rest of the data (similar to `hd:tl` list syntax in functional 
programming). Such a hypothetical cache can be invoked along the lines of:

```cpp
auto hc = HierarchicalCache<FastData, MediumData, SlowData>(...);
```

See [Wikipedia](http://en.wikipedia.org/wiki/Variadic_template) for more information on template metaprogramming.

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
