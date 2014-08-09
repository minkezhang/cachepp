#include "src/cache.h"

template <typename T> cachepp::Cache<T>::Cache(cachepp::identifier size) : size(size) {}

template <typename T> bool cachepp::Cache<T>::in(const std::shared_ptr<T>& arg) {
	this->l.lock();
	bool succ = false;
	try {
		this->cache.at(arg->get_identifier());
	} catch(const std::out_of_range& e) {
	}
	this->l.unlock();
	return(succ);
}

template <typename T> void cachepp::Cache<T>::allocate(const std::shared_ptr<T>& arg) {
	this->l.lock();
	if(this->in(arg)) {
		this->l.unlock();
		return;
	}
	if(this->cache.size() > this->size) {
		this->cache.erase(this->select()->get_identifier());
	}
	this->cache.insert(std::pair<cachepp::identifier, std::shared_ptr<T>> (arg->get_identifier, arg));
	this->l.unlock();
}

template <typename T> std::shared_ptr<T> cachepp::Cache<T>::select() {
	this->l.lock();
	cachepp::identifier heuristic = 0;
	cachepp::identifier target = 0;
	for(typename std::map<cachepp::identifier, std::shared_ptr<T>>::iterator it = this->cache.begin(); it != this->cache.end(); ++it) {
		if(heuristic >= this->heuristic(it->second)) {
			heuristic = this->heuristic(it->second);
			target = it->first;
		}
	}
	this->cache.at(target)->unload();
	this->l.unlock();
}

int main() { return(0); }
