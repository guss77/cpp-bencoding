/**
* @file      BString.h
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Representation of a string.
*/

#ifndef BENCODING_BSTRING_H
#define BENCODING_BSTRING_H

#include <memory>
#include <string>

#include "BItem.h"

namespace bencoding {

/**
* @brief Representation of a string.
*
* Use create() to create instances of the class.
*/
class BString: public BItem {
public:
	/// Type of the underlying string value.
//	using ValueType = std::string;
    using ValueType = std::shared_ptr<std::string>;
public:
    static std::unique_ptr<BString> create(std::string value);
	static std::unique_ptr<BString> create(ValueType value);

	ValueType value() const;
	void setValue(ValueType value);
    void setValue(std::string value);
    int64_t length() const;

	/// @name BItemVisitor Support
	/// @{
	virtual void accept(BItemVisitor *visitor) override;
	/// @}

private:
	explicit BString(ValueType value);
    explicit BString(std::string value);

private:
	ValueType _value;
};

} // namespace bencoding

#endif
