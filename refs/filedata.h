#ifndef FILEDATA_H
#define FILEDATA_H

#include <string>

#include "libs/cachepp/globals.h"
#include "libs/cachepp/lineinterface.h"

class FileData : public cachepp::LineInterface<char> {
	public:
		FileData(cachepp::identifier, std::string filename);

	private:
		std::string filename;
		virtual void aux_load() final;
		virtual void aux_unload() final;
		virtual char hash() final;
};

#include "src/templates/filedata.tpp"

#endif
