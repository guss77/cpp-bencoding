/**
* @file      BString.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Implementation of the BString class.
*/

#include "BString.h"

#include "BItemVisitor.h"

namespace bencoding {

/**
* @brief Constructs the string with the given @a value.
*/
BString::BString(ValueType value): _value(value) {}

BString::BString(std::string value) {
    _value = std::shared_ptr<std::string>(new std::string(value));
}

/**
* @brief Creates and returns a new string.
*/
std::unique_ptr<BString> BString::create(ValueType value) {
	return std::unique_ptr<BString>(new BString(value));
}

std::unique_ptr<BString> BString::create(std::string value) {
    return std::unique_ptr<BString>(new BString(value));
}

/**
* @brief Returns the string's value.
*/
auto BString::value() const -> ValueType {
	return _value;
}

/**
* @brief Sets a new value.
*/
void BString::setValue(ValueType value) {
	_value = value;
}

void BString::setValue(std::string value) {
    _value = std::shared_ptr<std::string>(new std::string(value));
}

/**
* @brief Returns the number of characters in the string.
*/
int64_t BString::length() const{
	return _value->length();
}

void BString::accept(BItemVisitor *visitor) {
	visitor->visit(this);
}

} // namespace bencoding
