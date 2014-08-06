/**
* @file      BItemVisitor.h
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Base class for all visitors of the subclasses of BItem.
*/

#ifndef BENCODING_BITEMVISITOR_H
#define BENCODING_BITEMVISITOR_H

namespace bencoding {

class BInteger;

/**
* @brief Base class for all visitors of the subclasses of BItem.
*
* Implements the <a
* href="http://en.wikipedia.org/wiki/Visitor_design_pattern">Visitor design
* pattern</a>.
*/
class BItemVisitor {
public:
	virtual ~BItemVisitor();

	virtual void visit(BInteger *bInteger) = 0;

protected:
	BItemVisitor();
};

} // namespace bencoding

#endif
