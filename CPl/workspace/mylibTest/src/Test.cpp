#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <iostream>

#include "src/sayhello.h"
#include "src/Hello.h"

void testHelloWorld() {

	// ostringstream: wraps a raw string device into a into a higher-level stream based interface
	std::ostringstream out{};

	sayHello(out);
	ASSERT_EQUAL("Hello, world!\n", out.str());
}

void testHelloWorldClass() {

	// ostringstream: wraps a raw string device into a into a higher-level stream based interface
	std::ostringstream out{};
	Hello h{};
	h.sayHello(out);
	ASSERT_EQUAL("Hello, C++!\n", out.str());
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };

	s.push_back(CUTE(testHelloWorld));
	s.push_back(CUTE(testHelloWorldClass));


	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
