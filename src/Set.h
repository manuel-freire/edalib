/**
 * @file Set.h
 *
 * Set
 * 
 * Estructura de Datos y Algoritmos
 * 
 * Copyright (C) 2014
 * Facultad de Informática, Universidad Complutense de Madrid
 * This software is licensed under the Simplified BSD licence:
 *    (see the LICENSE file or
 *     visit opensource.org/licenses/BSD-3-Clause)
 */

#ifndef __SET_H
#define __SET_H

// default implementation
#include "HashTable.h"

struct EmptyClass {};
/// std::ostream output
std::ostream& operator<<(std::ostream& out, const EmptyClass &e) {
    return out;
}
    
/**
 * Sets allow quick insertion, lookup and removal of elements.
 * Duplicate insertions are ignored.
 * 
 * Built on top of an associative container.
 * 
 * @author mfreire
 */
template <class KeyType, 
    class Container = HashTable<KeyType, EmptyClass> >
class Set {
    
    /** */
    Container _m;

public:

    /** */
    typedef typename Container::Iterator Iterator;    
    
    /**  */
    Iterator begin() const {
        return _m.begin();
    }
    
    /**  */
    Iterator end() const {
        return _m.end();
    }
    
    /**  */
    bool contains(const KeyType& key) const {
        return _m.find(key) != _m.end();
    }
    
    /**  */
    void insert(const KeyType& key) {
        _m.insert(key, EmptyClass());
    }

    /**  */
    void erase(const KeyType& key) {
        _m.erase(key);
    }

    /**  */    
    uint size() const {
        return _m.size();
    }
};

#endif // __SET_H
