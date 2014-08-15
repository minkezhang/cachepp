Line Interface
====

Overview
----

The line interface provides a uniform way in which to link abstract data types with the the cache.

### Template Arguments

The line interface must be provided with one template argument in order to be fully user-callable:

* `typename T`

	The internal representation of the checksum, such as `char` or `int`, etc.

### Properties

* `cachepp::identifer id`

	A **unique** id of the line.

* `std::vector<uint8_t> data`

	The internal representation of the data as a byte array.

* `bool is_loaded`

	If the current line is stored in a cache. Initialized to `false` in the constructor.

* `bool is_dirty`

	If the current line has been modified since loaded. Initialized to `false` in the constructor.

* `T checksum`

	The checksum value.

### Methods

* `(constructor)`

	Constructs an instance of `LineInterface`. Initializes `LineInterface::is_loaded` and `LineInterface::is_dirty` to `false`.

* `get_data()`

	Returns the byte array of data stored internally. Raises `exceptionpp::RuntimeError` if `LineInterface::is_loaded` is `false`.

* `set_data(data)`

	Takes in a byte array of `data` and sets `LineInterface::data` to this value. Raises `exceptionpp::RuntimeError` if `LineInterface::is_loaded` is `false`.

* `get_is_loaded()`

	Returns `LineInterface::is_loaded`.

* `get_is_dirty()`

	Returns `LineInterface::is_dirty`.

* `load()`

	Loads from arbitrary endpoint (depending on subclass implementation) the data and store internally in `LineInterface::data`.

* `unload()`

	Saves `LineInterface::data` to arbitrary endpoint if `LineInterface::is_dirty` is set.

* `validate()`

	Checks that `LineInterface::checksum` is consistent with the data currently stored. Raises `exceptionpp::RuntimeError` if mismatch occurs.

* `set_is_dirty(is_dirty)`

	Sets `LineInterface::is_dirty` to appropriate value.

* `set_is_loaded(is_loaded)`

	Sets `LineInterface::is_loaded` to appropriate value.

* `set_checkum(checksum)`

	Sets `LineInterface::checksum` to appropriate value.

* `get_checksum()`

	Returns the checksum of the instance.

* `aux_load()`

	Implementation-specific loading function to pull from the appropriate endpoint.

* `aux_unload()`

	Implementation-specific unloading function to push to the appropriate endpoint.

* `hash()`

	Returns a hash of `LineInterface::data`.

### Examples

[simpleline](../../src/simpleline.cc) implements `LineInterface`.

Further Reading
----

* [cache interface](cacheinterface.md)
* [exceptionpp](https://github.com/cripplet/exceptionpp)
* [lineinterface.h](../../include/src/lineinterface.h)
* [lineinterface.template](../../include/src/templates/lineinterface.template)
* [test suite](testsuite.md)
