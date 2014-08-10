#ifndef _CACHEPP_SIMPLELINE_H
#define _CACHEPP_SIMPLELINE_H

#include "src/globals.h"
#include "src/line.h"

namespace cachepp {
	/**
	 * simple concrete implementation of the Line interface
	 */
	class SimpleLine : public Line {
		public:
			SimpleLine(identifier id, bool is_corrupt);

		private:
			bool parity;
			bool is_corrupt;

			bool calculate_parity(bool is_corrupt = false);

			virtual void set_checksum();
			virtual void aux_load();
			virtual void aux_unload();
			virtual bool aux_validate();
	};
}

#endif
