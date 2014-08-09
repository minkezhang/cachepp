#ifndef _CACHEPP_SIMPLELINE_H
#define _CACHEPP_SIMPLELINE_H

#include "src/globals.h"
#include "src/line.h"

/**
 * cache line scaffolding headers
 */

namespace cachepp {
	class SimpleLine : public Line {
		public:
			SimpleLine(identifier id, bool is_corrupt);

		private:
			bool parity;
			bool is_corrupt;

			bool calculate_parity(bool is_corrupt = false);

			virtual void set_hash();
			virtual void load_aux();
			virtual void unload_aux();
			virtual bool checksum_aux();
	};
}

#endif
