#include "counting.h"

#include <algorithm>
#include <iterator>
#include <string>

int chcount(std::istream &in){
	using it=std::istream_iterator<char>;
	return distance(it{in}, it{});

}

int chacount(std::istream &in){
	using it=std::istreambuf_iterator<char>;
	return distance(it{in}, it{});
}

int wcount(std::istream &in){
	using it=std::istream_iterator<std::string>;
	return distance(it{in}, it{});

}

int acount(std::istream &in){
	using it=std::istream_iterator<char>;
	return count(it{in}, it{}, 'a');

}

int lcount(std::istream &in){
	using it=std::istreambuf_iterator<char>;
	return count(it{in}, it{}, '\n');
}