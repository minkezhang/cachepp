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

			void push_back(size_t n_acquire, size_t cache_size, size_t total_data, double read_rate, double miss_rate, double line_size, double total_runtime, bool is_parallel, size_t n_threads);

			double get_read_rate(size_t index);
			double get_miss_rate(size_t index);
			double get_throughput(size_t index);
			double get_latency(size_t index);
			double get_line_size(size_t index);
			size_t get_cache_size(size_t index);
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
			// void performance(std::vector<D> lines, std::vector<size_t> line_size, std::vector<identifier> access_pattern, std::vector<D> access_pattern_aux, size_t n_attempts, bool is_parallel, size_t n_threads);

			TestResult get_result();

			/**
			 * generate access patterns to be used in performance tests
			 */
			std::shared_ptr<std::vector<identifier>> generate_access_pattern(identifier n_lines, size_t length, uint8_t mode = 0);

		private:
			std::shared_ptr<X> cache;
			TestResult result;

			void aux_correctness(const std::shared_ptr<std::atomic<size_t>>& n_success, const std::shared_ptr<std::vector<std::shared_ptr<T>>>& lines, size_t n_attempts);
			// void aux_performance();
	};
}

std::ostream& operator<< (std::ostream& os, cachepp::TestResult& obj);

#include "src/templates/testsuite.template"

#endif
