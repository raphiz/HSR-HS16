#ifndef CALC_H_
#define CALC_H_

#include <iosfwd>

int calc(int lhs, int rhs, char op, bool& error);
int calc(std::istream& in, bool& error);


#endif /* CALC_H_ */