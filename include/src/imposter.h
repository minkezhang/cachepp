#ifndef _CACHEPP_IMPOSTER_H
#define _CACHEPP_IMPOSTER_H

#include "src/globals.h"

namespace cachepp {
	/**
	 * this is attempting to mirror the interface provided by Line in line.h
	 * a call to Cache<Imposter> will result in an exceptionpp::InvalidOperation being thrown
	 */
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
