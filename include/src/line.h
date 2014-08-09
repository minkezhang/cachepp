#ifndef _CACHEPP_LINE_H
#define _CACHEPP_LINE_H

#include "src/globals.h"

/**
 * cache line scaffolding headers
 */

namespace cachepp {
	class Line {
		public:
			Line();

			virtual cachepp::identifier get_identifier() = 0;
			virtual void load() = 0;
			virtual void unload() = 0;
	};
}

#endif
