#ifndef _CACHEPP_TESTSUITE_H
#define _CACHEPP_TESTSUITE_H

#include <atomic>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "src/globals.h"

namespace cachepp {
	class  TestResult {
		public:
			TestResult();

			void push_back(size_t n_acquire, size_t pool_size, size_t cache_size, size_t total_data, double read_rate, double miss_rate, double line_size, double total_runtime, bool is_parallel, size_t n_threads);

			/**
			 * get the number of records currently stored in the object
			 */
			size_t get_size();

			double get_read_rate(size_t index);
			double get_miss_rate(size_t index);
			double get_throughput(size_t index);
			double get_latency(size_t index);
			double get_line_size(size_t index);
			size_t get_cache_size(size_t index);
			size_t get_pool_size(size_t index);
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
			std::vector<size_t> cache_size;
			std::vector<size_t> pool_size;
			std::vector<double> total_runtime;
			std::vector<bool> is_parallel;
			std::vector<size_t> n_threads;
	};

	/**
	 * Test suite template class
	 *
	 * typename X -- cache
	 * typename D -- cache data
	 * typename L -- cache line
	 */
	template <typename X, typename D, typename T>
	class TestSuite {
		public:
			TestSuite(const std::shared_ptr<X>& cache);

			/**
			 * run correctness tests on the cache
			 */
			void correctness(const std::shared_ptr<std::vector<std::shared_ptr<T>>>& lines, size_t n_attempts, bool is_parallel, size_t n_threads = 0);

			/**
			 * run performance tests on the cache -- add to test results
			 */

			void performance(const std::shared_ptr<std::vector<std::shared_ptr<T>>>& lines, const std::shared_ptr<std::vector<size_t>>& line_size, std::shared_ptr<std::vector<identifier>>& access_pattern, std::shared_ptr<std::vector<std::shared_ptr<D>>>& access_pattern_aux, double read_rate, size_t n_attempts, bool is_parallel, size_t n_threads);

			/**
			 * get performance test results
			 */
			TestResult get_result();

			/**
			 * generate access patterns to be used in performance tests
			 *
			 * this should be static -- but is included as an instance method to save the non-trivial task fo specifying all the different types again
			 */
			std::shared_ptr<std::vector<identifier>> generate_access_pattern(identifier n_lines, size_t length, uint8_t mode = 0);

		private:
			std::shared_ptr<X> cache;
			TestResult result;

			void aux_correctness(const std::shared_ptr<std::atomic<size_t>>& n_success, const std::shared_ptr<std::vector<std::shared_ptr<T>>>& lines, size_t n_attempts);
			void aux_performance(const std::shared_ptr<std::atomic<size_t>>& data, const std::shared_ptr<std::atomic<double>>& runtime, const std::shared_ptr<std::vector<std::shared_ptr<T>>>& lines, const std::shared_ptr<std::vector<size_t>>& line_size, const std::shared_ptr<std::vector<identifier>>& access_pattern, const std::shared_ptr<std::vector<std::shared_ptr<D>>>& access_pattern_aux, double read_rate, size_t n_attempts);

			void aux_(const std::shared_ptr<std::vector<std::shared_ptr<T>>>& a);
	};
}

std::ostream& operator<< (std::ostream& os, cachepp::TestResult& obj);

#include "src/templates/testsuite.template"

#endif
