#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "libs/exceptionpp/exception.h"

#include "src/testsuite.h"

cachepp::TestResult::TestResult() : size(0) {}

void cachepp::TestResult::push_back(size_t n_acquire, size_t total_data, double read_rate, double miss_rate, double line_size, double total_runtime, bool is_parallel, size_t n_threads) {
	this->n_acquire.push_back(n_acquire);
	this->total_data.push_back(total_data);
	this->read_rate.push_back(read_rate);
	this->miss_rate.push_back(miss_rate);
	this->line_size.push_back(line_size);
	this->total_runtime.push_back(total_runtime);
	this->is_parallel.push_back(is_parallel);
	this->n_threads.push_back(n_threads);
	this->size++;
}

double cachepp::TestResult::get_read_rate(size_t index) { return(this->read_rate.at(index) * 100); }
double cachepp::TestResult::get_miss_rate(size_t index) { return(this->miss_rate.at(index) * 100); }
double cachepp::TestResult::get_throughput(size_t index) { return(this->total_data.at(index) / this->total_runtime.at(index)); }
double cachepp::TestResult::get_latency(size_t index) { return(this->n_acquire.at(index) / this->total_runtime.at(index)); }
double cachepp::TestResult::get_line_size(size_t index) { return(this->line_size.at(index)); }
bool cachepp::TestResult::get_is_parallel(size_t index) { return(this->is_parallel.at(index)); }
size_t  cachepp::TestResult::get_n_threads(size_t index) { return(this->n_threads.at(index)); }

std::string cachepp::TestResult::to_string() {
	if(this->size == 0) {
		throw(exceptionpp::InvalidOperation("cachepp::TestResult::to_string", "reporting zero trials"));
	}

	std::stringstream buffer;
	buffer << "trial\tread rate (%)\tmiss rate (%)\tthroughput (bytes/ms)\tlatency (ms)\tline size (bytes)\tparallel\tthread count" << std::endl \
		<< "============" << std::endl;
	for(size_t index = 0; index < this->size; ++index) {
		buffer << this->get_read_rate(index) << "\t" << this->get_miss_rate(index) << "\t" << this->get_throughput(index) << "\t" << this->get_latency(index) << "\t" << this->get_line_size(index) << "\t" << this->get_is_parallel(index) << "\t";
		if(this->get_is_parallel(index)) {
			buffer << this->get_n_threads(index);
		} else {
			buffer << "--";
		}
		buffer << std::endl;
	}
	return(buffer.str());
}

std::ostream& operator<< (std::ostream& os, cachepp::TestResult& obj) {
	os << obj.to_string();
	return(os);
}
