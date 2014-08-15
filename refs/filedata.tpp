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
	std::string line;
	std::ifstream fp (this->filename.c_str());
	while(getline(fp, line)) {
		std::vector<uint8_t> buf (line.begin(), line.end());
		this->data.insert(this->data.end(), buf.begin(), buf.end());
	}
	fp.close();
}

void FileData::aux_unload() {
	FILE *fp = fopen(this->filename.c_str(), "w");
	// http://bit.ly/1vS52ky
	fputs(std::string(this->data.begin(), this->data.end()).c_str(), fp);
	fclose(fp);
}

#endif
