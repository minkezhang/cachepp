Implementing the Line
====

We now need to implement the line interface. Let's take a look at [lineinterface.h](../../include/src/lineinterface.h) and the [API](../api/lineinterface.md):

```cpp
template <typename T>
class LineInterface {
	private:
		virtual void aux_load() = 0;
		virtual void aux_unload() = 0;
		virtual ... hash() = 0;
};
```

We are loading and unloading files -- it would make sense then that we need an additional property `filename` stored in the data struct. With this, we set out creating 
the header (see [filedata.h](../../refs/filedata.h) for source file):

```cpp
/* /include/src/filedata.h */

#ifndef FILEDATA_H
#define FILEDATA_H

#include <string>

#include "libs/cachepp/globals.h"
#include "libs/cachepp/lineinterface.h"

class FileData : public cachepp::LineInterface<...> {
	public:
		FileData(...);

	private:
		... filename;
		virtual void aux_load() final;
		...
};

#include "src/templates/filedata.tpp"

#endif
```

We are choosing a very simple hash function for this datatype -- the first char of the file:

```cpp
/* /include/src/templates/filedata.tpp */

#ifndef FILEDATA_TEMPLATE
#define FILEDATA_TEMPLATE

#include <fstream>
#include <string>

#include "libs/cachepp/globals.h"
#include "libs/cachepp/lineinterface.h"
#include "libs/exceptionpp/exception.h"

#include "src/filedata.h"

FileData::FileData(id, filename) : cachepp::LineInterface<...>::LineInterface(id), filename(filename) {}

... FileData::hash() {
	if(this->get_is_loaded()) {
		return(this->data.at(0));
	}
	throw(exceptionpp::RuntimeError("FileData::hash", "attempting to hash data which is not loaded"));
}

#endif
```

For loading and unloading the file, we simply need to read and write to the filename:

```cpp
void FileData::aux_load() {
	this->data.clear();
	FILE *fp = fopen(this->filename.c_str(), "r");

	// get file size
	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	rewind(fp);

	char *buf = (char *) malloc(sizeof(char) * size);
	size_t n_bytes = fread(buf, 1, size, fp);

	this->data.insert(this->data.begin(), buf, buf + n_bytes);

	free(buf);
	fclose(fp);
}

void FileData::aux_unload() {
	FILE *fp = fopen(this->filename.c_str(), "w");
	// http://bit.ly/1vS52ky
	fputs(std::string(this->data.begin(), this->data.end()).c_str(), fp);
	fclose(fp);
}
```

Done!

Further Reading
----

* Prev -- [Implementing the Cache Interface](cache.md)
* Next -- [Testing the Cache](testing.md)

