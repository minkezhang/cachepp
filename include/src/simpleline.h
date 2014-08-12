#ifndef _CACHEPP_SIMPLELINE_H
#define _CACHEPP_SIMPLELINE_H

#include "src/globals.h"
#include "src/lineinterface.h"

namespace cachepp {
	/**
	 * simple concrete implementation of the Line interface
	 */
	class SimpleLine : public LineInterface<bool> {
		public:
			SimpleLine(identifier id, bool is_corrupt);

		private:
			bool is_corrupt;

			virtual void aux_load() final;
			virtual void aux_unload() final;
			virtual bool hash() final;
	};
}

#endif
