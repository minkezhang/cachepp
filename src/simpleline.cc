#include "libs/exceptionpp/exception.h"

#include "src/simpleline.h"

cachepp::SimpleLine::SimpleLine(cachepp::identifier id, bool is_corrupt) : cachepp::LineInterface<bool>::LineInterface(id), is_corrupt(is_corrupt) {
	this->data.push_back(id % 256);
}

void cachepp::SimpleLine::aux_load() {}

void cachepp::SimpleLine::aux_unload() { this->set_is_dirty(true); }

/**
 * intentionally corrupt the data to encourage Line::validate to throw an exception
 */
bool cachepp::SimpleLine::hash() {
	if(this->is_corrupt) {
		// return the wrong parity
		return(!this->get_checksum());
	}

	uint32_t result = 0;
	for(std::vector<uint8_t>::iterator it = this->data.begin(); it != this->data.end(); ++it) {
		result += *it;
	}
	return(result % 2);
}
