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
			std::shared_ptr<std::vector<uint8_t>> get_data();

			/**
			 * loads and unloads data from RAM
			 */
			void load();
			void unload();

		protected:
			identifier id;
			std::shared_ptr<std::vector<uint8_t>> data;

			void checksum();

			/**
			 * produces the checksum and store internally
			 */
			virtual void set_hash() = 0;

			/**
			 * derived class to implement the specifics
			 */
			virtual void load_aux() = 0;
			virtual void unload_aux() = 0;
			virtual bool checksum_aux() = 0;
	};

	class SimpleLine : Line {
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
