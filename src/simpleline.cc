#include "libs/exceptionpp/exception.h"

#include "src/simpleline.h"

cachepp::SimpleLine::SimpleLine(cachepp::identifier id, bool is_corrupt) : Line(id), is_corrupt(is_corrupt) {
	this->data->push_back(id % 256);
}

void cachepp::SimpleLine::set_checksum() { this->parity = this->calculate_parity(); }

void cachepp::SimpleLine::aux_load() {}

void cachepp::SimpleLine::aux_unload() {
	this->set_is_dirty(true);
}

bool cachepp::SimpleLine::aux_validate() {
	return(this->parity == this->calculate_parity(this->is_corrupt));
}

/**
 * intentionally corrupt the data to encourage Line::validate to throw an exception
 */
bool cachepp::SimpleLine::calculate_parity(bool is_corrupt) {
	uint32_t result = 0;
	for(std::vector<uint8_t>::iterator it = this->data->begin(); it != this->data->end(); ++it) {
		result += *it;
	}
	return((is_corrupt + (result % 2)) % 2);
}
