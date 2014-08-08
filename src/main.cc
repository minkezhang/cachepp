#include "libs/exceptionpp/exception.h"

int main() {
	throw(exceptionpp::RuntimeError("main", "blah"));
	return(0);
}
