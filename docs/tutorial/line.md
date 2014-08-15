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
the header:

```cpp
/* /include/src/filedata.h */

#ifndef FILEDATA_H
#define FILEDATA_H

#include <string>

class FileData : public LineInterface<char> {
	public:
		FileData(id, filename);

	private:
		std::string filename;
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

#include <string>

#include "libs/exceptionpp/exception.h"

#include "src/filedata.h"

FileData::FileData(id, filename) : filename(filename), cachepp::LineInterface<char>::LineInterface(id) {}

... FileData::hash() {
	if(this->get_is_loaded() {
		return(this->data.at(0));
	}
	throw(exceptionpp::RuntimeError("FileData::hash", "attempting to hash an unloaded line"));
}

#endif
```

For loading and unloading the file, we simply need to read and write to the filename:

```cpp
FileData::aux_load() {
	std::string line;
	ifstream fp (this->filename.c_str());
	while(getline(fp, line)) {
		std::vector<uint8_t> buf (line.begin(), line.end());
		this->data.insert(this->data.end, buf.begin(), buf.end());
	}
	fp.close();
}

FileData::aux_unload() {
	FILE *fp = fopen(this->filename.c_str(), "r+");
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

