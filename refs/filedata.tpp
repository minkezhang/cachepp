#ifndef FILEDATA_TEMPLATE
#define FILEDATA_TEMPLATE

#include <fstream>
#include <string>

#include "libs/cachepp/globals.h"
#include "libs/cachepp/lineinterface.h"
#include "libs/exceptionpp/exception.h"

#include "src/filedata.h"

FileData::FileData(cachepp::identifier id, std::string filename) : cachepp::LineInterface<char>::LineInterface(id), filename(filename) {}

char FileData::hash() {
	if(this->get_is_loaded()) {
		return(this->data.at(0));
	}
	throw(exceptionpp::RuntimeError("FileData::hash", "attempting to hash data which is not loaded"));
}

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

#endif
