#ifndef _CACHEPP_TESTSUITE_H
#define _CACHEPP_TESTSUITE_H

#include <ostream>
#include <string>
#include <vector>

namespace cachepp {
	class  TestResult {
		public:
			TestResult();

			void push_back(size_t n_acquire, size_t total_data, double read_rate, double miss_rate, double line_size, double total_runtime, bool is_parallel, size_t n_threads);

			double get_read_rate(size_t index);
			double get_miss_rate(size_t index);
			double get_throughput(size_t index);
			double get_latency(size_t index);
			double get_line_size(size_t index);
			bool get_is_parallel(size_t index);
			size_t get_n_threads(size_t index);

			std::string to_string(bool is_tsv = false);

		private:
			size_t size;

			std::vector<size_t> n_acquire;
			std::vector<size_t> total_data;
			std::vector<double> read_rate;
			std::vector<double> miss_rate;
			std::vector<double> line_size;
			std::vector<double> total_runtime;
			std::vector<bool> is_parallel;
			std::vector<size_t> n_threads;
	};

}

std::ostream& operator<< (std::ostream& os, cachepp::TestResult& obj);

#endif
