/**
 * @file Util.h
 *
 * Common definitions, exceptions, and utility functions
 *
 * Estructura de Datos y Algoritmos
 *
 * Copyright (C) 2014
 * Facultad de Informática, Universidad Complutense de Madrid
 * This software is licensed under the Simplified BSD licence:
 *    (see the LICENSE file or
 *    visit opensource.org/licenses/BSD-3-Clause)
 */

#ifndef EDA_UTIL_H
#define EDA_UTIL_H

#include <string>
#include <iostream>
#include <iosfwd>

typedef unsigned int uint;
typedef unsigned long ulong;

/**
 * Class that all exception types inherit from
 */
class AbstractException {
public:
    AbstractException () {}
    AbstractException (const std::string &msg) : _msg(msg) {}

    const std::string msg() const { return _msg; }

    friend std::ostream &operator<<(std::ostream &out, const AbstractException  &e);

protected:
    std::string _msg;
};

inline std::ostream &operator<<(std::ostream &out, const AbstractException &e) {
    return out << e._msg;
}

/// Macro to create subclasses of the base exception.
///     use as: DECLARE_EXCEPTION(UniqueExceptionName)
#define DECLARE_EXCEPTION(ExceptionSubclass) \
class ExceptionSubclass : public AbstractException { \
public: \
    ExceptionSubclass() {}; \
    ExceptionSubclass(const std::string &msg) : AbstractException(msg) {} \
};

/// Macro to constify an operation.
///     given an operation like const Something& MyClass::myOperation(...),
///     use to provide the implementation of a non-const variant as:
///        NON_CONST_VARIANT(Something,Myclass,myOperation(...));
#define NON_CONST_VARIANT(Return,Class,Call) \
return const_cast<Return&>(static_cast<const Class*>(this)->Call)

/**
 * Copies all elements between first and last at the back of a given container
 */
template<class It, class Container>
void copy_back(It first, It last, Container& target) {
    for (It& current=first; current != last; current.next()) {
        target.push_back(current.elem());
    }
}

/**
 * Prints all elements between first and last to a given stream.
 *     Places a separator string between each pair of elements.
 *     Defaults to printing to std::cout with ", " as separator
 */ 
template<class It>
void print(It first, It last, std::ostream &out = std::cout,
           std::string separator = std::string(", ")) {
    if (first != last) {
        It& current = first;
        out << current.elem();
        for (current.next(); current != last; current.next()) {
            out << separator << current.elem();
        }
    }
}

/**
 * Prints all elements in an iterable collection to a given stream.
 *     Places a separator string between each pair of elements.
 *     Defaults to printing to std::cout with ", " as separator
 */
template<class Container>
void print(std::string message, const Container &c, std::ostream &out = std::cout,
           std::string separator = std::string(", ")) {
    out << message << " (size " << c.size() << "): ";
    print(c.begin(), c.end(), out, separator);
    out << std::endl;
}
           
#endif // EDA_UTIL_H
