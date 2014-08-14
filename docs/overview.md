Beginner's Guide
====

Motivation
----

Add motivation here.

* stemmed from [giga](https://github.com/cripplet/giga.git)
* practice in good interface design
* lack of C++ caching frameworks

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
