#include "libs/exceptionpp/exception.h"

#include "src/imposter.h"

cachepp::Imposter::Imposter(cachepp::identifier id) : id(id) {}
cachepp::identifier cachepp::Imposter::get_identifier() { return(this->id); }
void cachepp::Imposter::load() {}
void cachepp::Imposter::unload() {}
