/*
 * Hello.h
 *
 *  Created on: Sep 23, 2016
 *      Author: rzi
 */

#ifndef SRC_HELLO_H_
#define SRC_HELLO_H_

#include <ostream>

struct Hello {
	void sayHello(std::ostream &out) const;
};
#endif /* SRC_HELLO_H_ */
