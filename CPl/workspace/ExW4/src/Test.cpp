#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <string>

#include "mixed.h"

void testWlistSimple() {
	std::istringstream in {"FOO foo FoO baa hello world"};
	std::set<std::string> lst = wlist(in);
	auto it = lst.begin();
	ASSERT_EQUAL("baa", *it);
	ASSERT_EQUAL("foo", *(++it));
	ASSERT_EQUAL("hello", *(++it));
	ASSERT_EQUAL("world", *(++it));
	ASSERT_EQUAL(lst.end(), ++it);
}

void testWlistEmpty() {
	std::istringstream in {};
	std::set<std::string> lst = wlist(in);
	auto it = lst.begin();
	ASSERT_EQUAL(lst.end(), it);
}

void lowerFirstCharacter() {
	std::string str("Hello!");
	ASSERT_EQUAL(1, countingToLower(str));
	ASSERT_EQUAL("hello!", str);
}

void lowerSeveralCharacters() {
	std::string str("Hello World, its ME!");
	ASSERT_EQUAL(4, countingToLower(str));
	ASSERT_EQUAL("hello world, its me!", str);
}

void lowerNone() {
	std::string str("no uppercase characters here");
	ASSERT_EQUAL(0, countingToLower(str));
	ASSERT_EQUAL("no uppercase characters here", str);
}

void lowerAll() {
	std::string str("LOL");
	ASSERT_EQUAL(3, countingToLower(str));
	ASSERT_EQUAL("lol", str);
}

void lowerEmpty() {
	std::string str("");
	ASSERT_EQUAL(0, countingToLower(str));
	ASSERT_EQUAL("", str);
}

void umlautsAreNotChanged() {
	std::string str("ÄÖÜ");
	ASSERT_EQUAL(0, countingToLower(str));
	ASSERT_EQUAL("ÄÖÜ", str);
}
bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testWlistSimple));
	s.push_back(CUTE(testWlistEmpty));
	s.push_back(CUTE(umlautsAreNotChanged));
	s.push_back(CUTE(lowerFirstCharacter));
	s.push_back(CUTE(lowerSeveralCharacters));
	s.push_back(CUTE(lowerNone));
	s.push_back(CUTE(lowerAll));
	s.push_back(CUTE(lowerEmpty));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner { cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}