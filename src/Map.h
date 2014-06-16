/**
 * @file Map.h
 *
 * Map
 * 
 * Estructura de Datos y Algoritmos
 * 
 * Copyright (C) 2014
 * Facultad de Informática, Universidad Complutense de Madrid
 * This software is licensed under the Simplified BSD licence:
 *    (see the LICENSE file or
 *     visit opensource.org/licenses/BSD-3-Clause)
 */

#ifndef __MAP_H
#define __MAP_H

// default implementation
#include "TreeMap.h"

/**
 * Maps allow key, value pairs to be stored. The keys are used
 * to index the values. Quick insertion, lookup (by key)
 * and removal (by key) are available. 
 * 
 * Trying to insert a key, value pair under an already-inserted key
 * results in overwriting the previous key, value pair with the new one.
 * 
 * @author mfreire
 */
template <class KeyType, class ValueType, 
    class Container = TreeMap<KeyType, ValueType> >
class Map {
    
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
    ValueType& at(const KeyType& key) const {
        return _m.at(key);
    }
    
    /**  */
    ValueType& at(const KeyType& key) {
        return _m.at(key);
    }
    
    /**  */
    bool contains(const KeyType& key) const {
        return _m.find(key) != _m.end();
    }
    
    /**  */
    void insert(const KeyType& key, const ValueType& value) {
        _m.insert(key, value);
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

#endif // __MAP_H
