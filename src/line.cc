#include "libs/exceptionpp/exception.h"

#include "src/line.h"

/**
 * line
 */

cachepp::Line::Line(cachepp::identifier id) : id(id) {
	this->data = std::shared_ptr<std::vector<uint8_t>> (new std::vector<uint8_t> ());
}

cachepp::identifier cachepp::Line::get_identifier() { return(this->id); }

/**
 * simpleline
 */

cachepp::SimpleLine::SimpleLine(cachepp::identifier id, bool is_corrupt) : Line(id), is_corrupt(is_corrupt) {
	this->data->push_back(0);
}

void cachepp::SimpleLine::load() {
	this->set_hash();
}

void cachepp::SimpleLine::unload() {
	this->checksum();
}

bool cachepp::SimpleLine::calculate_parity(bool is_corrupt) {
	uint32_t result = 0;
	for(std::vector<uint8_t>::iterator it = this->data->begin(); it != this->data->end(); ++it) {
		result += *it;
	}
	return((is_corrupt + (result % 2)) % 2);
}

void cachepp::SimpleLine::checksum() {
	if(this->parity != this->calculate_parity(this->is_corrupt)) {
		throw(exceptionpp::RuntimeError("cachepp::SimpleLine::checksum", "calculated checksum did not match data"));
	}
}

void cachepp::SimpleLine::set_hash() { this->parity = this->calculate_parity(); }
