File Structure
====

The directory in `cachepp` is somewhat dogmatic to the author and is replete with symbolic links. As such, an explanation of the contents of each directory may be of use 
to the confused.

* [/](../) -- the root directory
	* [docs/](../docs/) -- all documentation resides here
		* [api/](../docs/api/) -- guide to the `cachepp` interface
		* [tutorial/](../docs/tutorial/)
	* [external/](../external/) -- all **raw** external libraries (i.e., a `git clone` of relevant dependencies) -- files from these directories are then 
		symbolically linked to match the existing structure
	* [include/](../include/) -- all header files
		* [libs/](../include/libs/) -- header files for each library from /libs/
		* [src/](../include/src/) -- header files for the /src/ directory
			* [templates/](../include/src/templates/) -- all `cachepp` template files here
	* [libs/](../libs/) -- all source files from the external files are linked here
	* [refs/](../refs/) -- reference files for the tutorial
	* [src/](../src/) -- all source files for `cachepp`
	* [tests/](../tests/) -- all unit testing files for `cachepp`
	* [tutorial/](../tutorial/) -- the live tutorial work directory
