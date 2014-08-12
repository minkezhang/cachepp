#ifndef _CACHEPP_LINE_H
#define _CACHEPP_LINE_H

#include <memory>
#include <vector>

#include "src/globals.h"

namespace cachepp {
	/**
	 * basic cache line interface -- this is NOT directly callable by the user
	 */
	template <typename T>
	class Line {
		public:
			Line(identifier id);

			identifier get_identifier();
			std::vector<uint8_t> get_data();
			void set_data(std::vector<uint8_t> data);

			bool get_is_loaded();
			bool get_is_dirty();

			/**
			 * loads and unloads data from RAM
			 */
			void load();
			void unload();

		protected:
			identifier id;
			std::vector<uint8_t> data;

			bool is_loaded;
			bool is_dirty;

			T checksum;

			void validate();

			void set_is_loaded(bool is_loaded);
			void set_is_dirty(bool is_dirty);
			void set_checksum(T);
			T get_checksum();

			/**
			 * derived class to implement the specifics
			 */
			virtual void aux_load() = 0;
			virtual void aux_unload() = 0;
			virtual T hash() = 0;
	};
}

#include "src/templates/line.template"

#endif
