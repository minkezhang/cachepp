#include "libs/exceptionpp/exception.h"

#include "src/line.h"

/**
 * Line
 */

cachepp::Line::Line(cachepp::identifier id) : id(id), is_loaded(0), is_dirty(0) {
	this->data = std::shared_ptr<std::vector<uint8_t>> (new std::vector<uint8_t> ());
}

cachepp::identifier cachepp::Line::get_identifier() { return(this->id); }

std::shared_ptr<std::vector<uint8_t>> cachepp::Line::get_data() {
	if(!this->get_is_loaded()) {
		throw(exceptionpp::RuntimeError("cachepp::Line::get_data", "attempting to get data when line is not loaded"));
	}
	return(this->data);
}

bool cachepp::Line::get_is_loaded() { return(this->is_loaded); }
bool cachepp::Line::get_is_dirty() { return(this->is_dirty); }

void cachepp::Line::load() {
	if(this->get_is_loaded()) {
		return;
	}
	this->load_aux();
	this->checksum();
	this->set_is_loaded(true);
}

void cachepp::Line::unload() {
	if(!this->get_is_loaded()) {
		return;
	}
	this->set_hash();
	this->unload_aux();
	this->set_is_loaded(false);
}

/**
 * checks the data in this->data
 *
 * raises exceptionpp::RuntimeError if the data is not valid
 */
void cachepp::Line::checksum() {
	if(!this->get_is_dirty()) {
		return;
	}
	if(!this->checksum_aux()) {
		throw(exceptionpp::RuntimeError("cachepp::Line::checksum", "calculated checksum did not match data"));
	}
}

void cachepp::Line::set_is_loaded(bool is_loaded) { this->is_loaded = is_loaded; }
void cachepp::Line::set_is_dirty(bool is_dirty) { this->is_dirty = is_dirty; }

/**
 * SimpleLine
 */

cachepp::SimpleLine::SimpleLine(cachepp::identifier id, bool is_corrupt) : Line(id), is_corrupt(is_corrupt) {
	this->data->push_back(id % 256);
}

void cachepp::SimpleLine::set_hash() { this->parity = this->calculate_parity(); }

void cachepp::SimpleLine::load_aux() {}

void cachepp::SimpleLine::unload_aux() {
	this->set_is_dirty(true);
}

bool cachepp::SimpleLine::checksum_aux() {
	return(this->parity == this->calculate_parity(this->is_corrupt));
}

bool cachepp::SimpleLine::calculate_parity(bool is_corrupt) {
	uint32_t result = 0;
	for(std::vector<uint8_t>::iterator it = this->data->begin(); it != this->data->end(); ++it) {
		result += *it;
	}
	return((is_corrupt + (result % 2)) % 2);
}

/**
 * Random
 */

cachepp::Random::Random(cachepp::identifier id) : id(id) {}
cachepp::identifier cachepp::Random::get_identifier() { return(this->id); }
void cachepp::Random::load() {}
void cachepp::Random::unload() {}
