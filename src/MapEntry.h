/**
 * @file MapEntry.h
 *
 * An entry for associative containers (maps)
 *
 * Estructura de Datos y Algoritmos
 *
 * Copyright (C) 2014
 * Facultad de Informática, Universidad Complutense de Madrid
 * This software is licensed under the Simplified BSD licence:
 *    (see the LICENSE file or
 *    visit opensource.org/licenses/BSD-3-Clause)
 */

#ifndef EDA_MAP_ENTRY_H
#define EDA_MAP_ENTRY_H

#include <iostream>

/**
 * Generic entry for maps, consisting of a key-value pair.
 */
template <class KeyType, class ValueType>
struct MapEntry {
    KeyType _key;     ///< key: used to index and search
    ValueType _value; ///< value: associated with key
    
    MapEntry() {}
    MapEntry(KeyType key, ValueType value)
        : _key(key), _value(value) {}

    // for iostream output
    template <class K, class V>
    friend std::ostream& operator<<(
        std::ostream& out, const MapEntry<K, V> &e);
};

/**
 * std::ostream output for a MapEntry
 */
template <class K, class V>
std::ostream& operator<<(
    std::ostream& out, const MapEntry<K, V> &e) {
    return out << e._key << ": " << e._value;
}

#endif // EDA_MAP_ENTRY
