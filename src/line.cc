#include "src/line.h"

cachepp::Line::Line(cachepp::identifier id) : id(id) {}

cachepp::identifier cachepp::Line::get_identifier() { return(this->id); }
