#include <algorithm>
#include <iomanip>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "libs/exceptionpp/exception.h"

#include "src/testsuite.h"

bool is_dup(char l, char r) { return(((l == ' ') || (l == '\n')) && (l == r)); }

cachepp::TestResult::TestResult() : size(0) {}

size_t cachepp::TestResult::get_size() { return(this->size); }

void cachepp::TestResult::push_back(std::string tag, size_t n_acquire, size_t pool_size, size_t cache_size, size_t total_data, double read_rate, double miss_rate, double line_size, double total_runtime, bool is_parallel, size_t n_threads, double r_time, double w_time) {
	// total_data and average line_size are in bits -- converting to bytes
	this->tag.push_back(tag);
	this->n_acquire.push_back(n_acquire);
	this->total_data.push_back(total_data / 8);
	this->read_rate.push_back(read_rate);
	this->miss_rate.push_back(miss_rate);
	this->line_size.push_back(line_size / 8);
	this->pool_size.push_back(pool_size);
	this->cache_size.push_back(cache_size);
	this->total_runtime.push_back(total_runtime);
	this->is_parallel.push_back(is_parallel);
	this->n_threads.push_back(n_threads);
	this->r_time.push_back(r_time);
	this->w_time.push_back(w_time);
	this->size++;
}

std::string cachepp::TestResult::get_tag(size_t index) { return(this->tag.at(index)); }
double cachepp::TestResult::get_read_rate(size_t index) { return(this->read_rate.at(index) * 100); }
double cachepp::TestResult::get_miss_rate(size_t index) { return(this->miss_rate.at(index) * 100); }
double cachepp::TestResult::get_throughput(size_t index) { return(this->total_data.at(index) / this->total_runtime.at(index)); }
double cachepp::TestResult::get_latency(size_t index) { return(this->total_runtime.at(index) / this->n_acquire.at(index)); }
double cachepp::TestResult::get_line_size(size_t index) { return(this->line_size.at(index)); }
size_t cachepp::TestResult::get_cache_size(size_t index) { return(this->cache_size.at(index)); }
size_t cachepp::TestResult::get_pool_size(size_t index) { return(this->pool_size.at(index)); }
bool cachepp::TestResult::get_is_parallel(size_t index) { return(this->is_parallel.at(index)); }
size_t  cachepp::TestResult::get_n_threads(size_t index) { return(this->n_threads.at(index)); }
double  cachepp::TestResult::get_r_time(size_t index) { return(this->r_time.at(index)); }
double  cachepp::TestResult::get_w_time(size_t index) { return(this->w_time.at(index)); }

std::string cachepp::TestResult::to_string(bool is_tsv) {
	size_t pad = 11;
	std::string sep = " | ";

	if(this->get_size() == 0) {
		throw(exceptionpp::InvalidOperation("cachepp::TestResult::to_string", "reporting zero trials"));
	}

	std::stringstream buffer;
	buffer << std::setw(pad) << "trial" << sep << std::setw(3) << "tag" << sep << std::setw(pad) << "pool size" << sep << std::setw(pad) << "cache size" << sep << std::setw(pad) << "read (%)" << sep << std::setw(pad) << "miss (%)" << sep << std::setw(pad) << "tput (B/us)" << sep << std::setw(pad) << "lat (us)" << sep << std::setw(pad) << "line (B)" << sep << std::setw(pad) << "parallel" << sep << std::setw(pad) << "n_threads" << sep << std::setw(pad) << "l-time (us)" << sep << std::setw(pad) << "u-time (us)" << std::endl;
	buffer << std::string(buffer.str().length(), '=') << std::endl;
	for(size_t index = 0; index < this->get_size(); ++index) {
		buffer << std::setprecision(2) << std::fixed;
		buffer << std::setw(pad) << index + 1 << sep << std::setw(3) << this->get_tag(index) << sep << std::setw(pad) << this->get_pool_size(index) << sep << std::setw(pad) << this->get_cache_size(index) << sep << std::setw(pad) << this->get_read_rate(index) << sep << std::setw(pad) << this->get_miss_rate(index) << sep << std::setw(pad) << this->get_throughput(index) << sep << std::setw(pad) << this->get_latency(index) << sep << std::setw(pad) << this->get_line_size(index) << sep << std::setw(pad) << this->get_is_parallel(index) << sep << std::setw(pad);

		if(this->get_is_parallel(index)) {
			buffer << this->get_n_threads(index);
		} else {
			buffer << "--";
		}
		buffer << sep << std::setw(pad) << this->get_r_time(index) << sep << std::setw(pad) << this->get_w_time(index) << std::endl;
	}

	std::string ret = buffer.str();
	// format to tabs
	if(is_tsv) {
		std::replace(ret.begin(), ret.end(), '|', '\t');
		// cf. http://bit.ly/1p6ATc7
		ret.erase(std::remove(ret.begin(), ret.end(), '='), ret.end());

		// cf. http://bit.ly/1ywrQSZ
		std::string::iterator end = std::unique(ret.begin(), ret.end(), is_dup);
		ret.erase(end, ret.end());

		// cf. http://bit.ly/1oN9U5R
		std::stringstream s;
		s << std::endl << "\t";
		size_t pos = 0;
		while((pos = ret.find(s.str())) != std::string::npos) {
			ret.erase(pos + 1, 1);
		}
		pos = 0;
		while((pos = ret.find(" \t ")) != std::string::npos) {
			ret.erase(pos + 2, 1);
			ret.erase(pos, 1);
		}

		ret = ret.substr(1);
	}
	return(ret);
}

std::ostream& operator<< (std::ostream& os, cachepp::TestResult& obj) {
	os << obj.to_string(false);
	return(os);
}
