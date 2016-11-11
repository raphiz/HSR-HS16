#ifndef WORD_H_
#define WORD_H_
#include <string>
#include <iosfwd>
#include <vector>
#include <set>

namespace testat {

class Word {
std::string value;

bool isValid(std::string test) const;
public:
	Word();
	Word(std::string in);
	std::ostream & print(std::ostream & out) const;
	std::istream & read(std::istream & in);

	bool operator<(Word const & otherWord) const;
};


std::set<Word> wlist(std::istream & in);

std::ostream & operator<<(std::ostream & out, Word const & word);
std::istream & operator>>(std::istream & in, Word & word);
std::istream & operator>>(std::string & in, Word & word);

inline bool operator>(Word const & lhs, Word const & rhs) {
    return rhs < lhs;
}
inline bool operator>=(Word const & lhs, Word const & rhs) {
    return !(lhs < rhs);
}
inline bool operator<=(Word const & lhs, Word const & rhs) {
    return !(rhs < lhs);
}
inline bool operator==(Word const & lhs, Word const & rhs) {
    return !(lhs < rhs) && !(rhs < lhs);
}
inline bool operator!=(Word const & lhs, Word const & rhs) {
    return !(lhs == rhs);
}


}

#endif /* WORD_H_ */
