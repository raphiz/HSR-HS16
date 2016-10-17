#include <iosfwd>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>

#include "sevensegment.h"

std::vector<std::vector<std::string>> const DIGITS {
		{" - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - ", " - ", "   ", "   "},
		{"| |", "  |", "  |", "  |", "| |", "|  ", "|  ", "  |", "| |", "| |", "|  ", "   ", "   "},
		{"   ", "   ", " - ", " - ", " - ", " - ", " - ", "   ", " - ", " - ", " - ", " - ", " - "},
		{"| |", "  |", "|  ", "  |", "  |", "  |", "| |", "  |", "| |", "  |", "|  ", "|  ", "| |"},
		{" - ", "   ", " - ", " - ", "   ", " - ", " - ", "   ", " - ", " - ", " - ", "   ", " - "},
	};

void do_print(std::string s, std::ostream &out, unsigned const scale){
	int counter {0};
	for_each(cbegin(DIGITS), cend(DIGITS), [s, &out, &counter, scale](auto line){
		++counter;
		const int repetitions {(counter == 2 || counter == 4) ? scale : 1};
		for (int var = 0; var < repetitions; ++var) {
			for_each(cbegin(s), cend(s), [line, &out, &counter, scale](auto x){
				switch(x){
					case 'E':
						out << line.at(10);
						break;
					case 'r':
						out << line.at(11);
						break;
					case 'o':
						out << line.at(12);
						break;
					default:
						int num{x - '0'};
						out << line.at(num);
				}
			});
			out << '\n';
		}
	});
}

void printError(std::ostream &out, unsigned const scale){
	std::string s{"Error"};
	do_print(s, out, scale);
}

void printLargeNumber(int const i, std::ostream &out, unsigned const scale, unsigned const maxWidth){
	auto s = std::to_string(i);
	if(maxWidth > 0 && s.length() > maxWidth){
		printError(out, scale);
	}else{
		do_print(s, out, scale);
	}
}

void printLargeDigit(int const i, std::ostream &out) {
	for_each(cbegin(DIGITS), cend(DIGITS), [i, &out](auto x){
		out << x.at(i) << '\n';
	});
}