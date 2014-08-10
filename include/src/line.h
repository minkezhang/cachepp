#ifndef _CACHEPP_LINE_H
#define _CACHEPP_LINE_H

#include <memory>
#include <vector>

#include "src/globals.h"

namespace cachepp {
	/**
	 * basic cache line interface -- this is NOT directly callable by the user
	 */
	class Line {
		public:
			Line(identifier id);

			identifier get_identifier();
			std::shared_ptr<std::vector<uint8_t>> get_data();

			bool get_is_loaded();
			bool get_is_dirty();

			/**
			 * loads and unloads data from RAM
			 */
			void load();
			void unload();

		protected:
			identifier id;
			std::shared_ptr<std::vector<uint8_t>> data;

			bool is_loaded;
			bool is_dirty;

			void validate();

			void set_is_loaded(bool is_loaded);
			void set_is_dirty(bool is_dirty);

			/**
			 * produces the checksum and store internally
			 */
			virtual void set_checksum() = 0;

			/**
			 * derived class to implement the specifics
			 */
			virtual void aux_load() = 0;
			virtual void aux_unload() = 0;
			virtual bool aux_validate() = 0;
	};
}

#endif
