Beginner's Guide
====

Motivation
----

`cachepp` is an exercise in good interface design, and an attempt is made to unify the way in which different caches behave. Though numerous caching libraries exist, 
there does not seem to be a similar demand for caching *frameworks* -- that is, something that will allow the developer to easily design their own cache. Moreover, these 
caching libraries are almost always written in languages such as Java and Python, with little to no attention paid to the C++ community.

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
