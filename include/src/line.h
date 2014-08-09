#ifndef _CACHEPP_LINE_H
#define _CACHEPP_LINE_H

#include <memory>
#include <vector>

#include "src/globals.h"

/**
 * cache line scaffolding headers
 */

namespace cachepp {
	/**
	 * base cache line interface
	 */
	class Line {
		public:
			Line(identifier id);

			identifier get_identifier();

			/**
			 * loads and unloads data from RAM
			 */
			virtual void load() = 0;
			virtual void unload() = 0;

		protected:
			identifier id;
			std::shared_ptr<std::vector<uint8_t>> data;

			/**
			 * checks the data in this->data
			 *
			 * raises exceptionpp::RuntimeError if the data is not valid
			 */
			virtual void checksum() = 0;
	};
}

#endif
