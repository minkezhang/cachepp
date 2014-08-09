#ifndef _CACHEPP_IMPOSTER_H
#define _CACHEPP_IMPOSTER_H

#include "src/globals.h"

/**
 * cache line scaffolding headers
 */

namespace cachepp {
	class Imposter {
		public:
			Imposter(identifier id);
			identifier get_identifier();

			void load();
			void unload();

		private:
			identifier id;
	};
}

#endif
