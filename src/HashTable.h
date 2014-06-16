/**
 * @file HashTable.h
 *
 * An open hash-table.
 *
 * Estructura de Datos y Algoritmos
 *
 * Copyright (C) 2014
 * Facultad de Informática, Universidad Complutense de Madrid
 * This software is licensed under the Simplified BSD licence:
 *    (see the LICENSE file or
 *    visit opensource.org/licenses/BSD-3-Clause)
 */

#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include "MapEntry.h"
#include "Util.h"

DECLARE_EXCEPTION(HashTableNoSuchElement)

/// hash for (unsigned) ints
inline uint hash(uint key) {
    return key;
}

/// hash for (signed) ints
inline uint hash(int key) {
    return (uint)key;
}

/// hash for chars
inline uint hash(char key) {
    return (uint)key;
}

/// used in Java jdk7
inline uint hash(std::string key) {
    uint h = 0;
    for (uint i=0; i<key.length(); i++) {
        h = 31*h + key[i];
    }
    return h;
}

/**
 * Generic hash function for user classes
 */
template<class KeyType>
uint hash(const KeyType& key) {
    return key.hash();
}

/**
 * An open hash-table. Insertion, existence and
 * removal are quick -- as long as the hash-function
 * for the keys is good.
 * 
 * @author mfreire
 */
template <class KeyType, class ValueType>
class HashTable {
    typedef MapEntry<KeyType, ValueType> Entry;
    typedef DoubleList<Entry> Bin;
    typedef typename Bin::Iterator BinIterator;
    
    /** if _entryCount * _size exceed this, grow */
    static const uint MAX_LOAD_FACTOR = 4;
    
    /** initial number of bins */
    static const uint INITIAL_SIZE = 16;
    
    Bin* _bins;         ///< bins to store elements in
    uint _size;         ///< current number of bins
    uint _entryCount;   ///< number of key-value entries stored

public:

    /**  */
    HashTable() : _size(INITIAL_SIZE), _entryCount(0) {
        _bins = new Bin[_size];
    }
    
    /**  */
    ~HashTable() {
        delete[] _bins;
        _bins = 0;
    }
    
    /** */
    HashTable& operator=(const HashTable& other) {
        delete[] _bins;
        _size = other._size;
        _bins = new Bin[_size];
        _entryCount = other.size();
        for (uint i=0; i<other.size(); i++) {
            _bins[i] = other._bins[i];
        }
        return (*this);
    }    

    /**  */
    uint size() const {
        return _entryCount;
    }

    class Iterator {
    public:
        void next() {
            _it.next();
            _advance();
        }
        
        const Entry& elem() const {
            return _it.elem();
        }
        
        const ValueType& value() const {
            return _it.elem()._value;
        }
        
        const KeyType& key() const {
            return _it.elem()._key;
        }
        
        bool operator==(const Iterator &other) const {
            return _it == other._it;
        }
        
        bool operator!=(const Iterator &other) const {
            return _it != other._it;
        }
    protected:
        friend class HashTable;
        
        const HashTable* _hm;
        Bin* _bin;
        BinIterator _it;
        const Bin* _lastBin;
        
        Iterator(const HashTable *hm, uint binNumber, const BinIterator &it)
            : _hm(hm), _bin(hm->_bins + binNumber), _it(it) {
                
            _lastBin = _hm->_bins + (_hm->_size - 1);
            _advance();
        }
        
        void _advance() {
            while (_it == _bin->end() && _bin < _lastBin) {
                _bin ++;
                _it = _bin->begin();
            }
        }
    };
    
    /** */
    const Iterator find(const KeyType& key) const {
        uint binNumber = _binFor(key);
        const Bin& bin = _bins[binNumber];
        const BinIterator& it = _findIn(bin, key);
        return (it == bin.end()) ? end() 
            : Iterator(this, binNumber, it);
    }
    
    /** */
    Iterator begin() const {
        return Iterator(this, 0, _bins[0].begin());
    }
    
    /** */
    Iterator end() const {
        return Iterator(this, _size-1, _bins[_size-1].end());
    }
    
    /** */
    const ValueType& at(const KeyType& key) const {        
        const Bin& bin  = _bins[_binFor(key)];
        const BinIterator it = _findIn(bin, key);
        if (it == bin.end()) {
            throw HashTableNoSuchElement("at");
        }
        return it.elem()._value;
    }
    
    /** */
    ValueType& at(const KeyType& key) {
        NON_CONST_VARIANT(ValueType,HashTable,at(key));
    }
    
    /** */
    void insert(const KeyType& key, const ValueType& value) {
        Bin& bin  = _bins[_binFor(key)];
        BinIterator it = _findIn(bin, key);
        if (it == bin.end()) {
            bin.push_back(Entry(key, value));
            _entryCount ++;
            if (_entryCount / _size >= MAX_LOAD_FACTOR) {
                _grow();
            }
        } else {
            it.set(Entry(key, value));
        }
    }
    
    /** */
    void erase(const KeyType& key) {
        Bin& bin = _bins[_binFor(key)];
        BinIterator it = _findIn(bin, key);
        if (it == bin.end()) {
            throw HashTableNoSuchElement("erase");
        } else {
            bin.erase(it);
            _entryCount --;
        }
    }
    
    /** */
    void print(std::ostream &out=std::cout) {
        for (uint i=0; i<_size; i++) {
            out << "bin " << i << ": [";
            ::print(_bins[i].begin(), _bins[i].end(), out, "], [");
            out << "]" << std::endl;
        }
    } 
    
    /** */
    void histogram(std::ostream &out=std::cout) {
        Vector<uint> sizes;
        for (uint i=0; i<_size; i++) {
            uint s = _bins[i].size();
            while (s >= sizes.size()) {
                sizes.push_back(0);
            }
            sizes.at(s) ++;
        }
        out << _size << " bins total; chain sizes range from 0 to " 
            << (sizes.size() - 1) << ":" << std::endl;
        for (uint i=0; i<sizes.size(); i++) {
            out << std::setw(2) << i << ": " << sizes.at(i) << std::endl;
        }      
    }
    
private:

    uint _rehash(uint h) const {
        // based on FastHash (https://code.google.com/p/fast-hash)
        h ^= h >> 11;
        h *= 4294967291; // large 32-bit prime
        h ^= h >> 23;
        return h;
    }
    
    int _binFor(const KeyType& key) const {
        return _rehash(::hash(key)) % _size;
    }
    
    BinIterator _findIn(const Bin& bin, const KeyType& key) const {
        for (BinIterator it=bin.begin(); it!=bin.end(); it.next()) {
            if (it.elem()._key == key) {
                return it;
            }
        }
        return bin.end();
    }
    
    void _grow() {
        Bin allEntries;
        for (uint i=0; i<_size; i++) {
            allEntries.concat(_bins[i]);
        }
        delete[] _bins;
        _size *= 2;
        _bins = new Bin[_size];
        _entryCount = 0;
        while (allEntries.size()) {
            const Entry& entry = allEntries.back();            
            Bin& bin  = _bins[_binFor(entry._key)];
            allEntries.moveBackTo(bin);
            _entryCount ++;
        }
    }
};

#endif // __HASHTABLE_H
