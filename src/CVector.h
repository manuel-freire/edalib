/**
 * @file CVector.h
 *
 * A circular vector, also called a circular buffer.
 *
 * Estructura de Datos y Algoritmos
 *
 * Copyright (C) 2014
 * Facultad de Informática, Universidad Complutense de Madrid
 * This software is licensed under the Simplified BSD licence:
 *    (see the LICENSE file or
 *    visit opensource.org/licenses/BSD-3-Clause)
 */

#ifndef __CVECTOR_H
#define __CVECTOR_H

#include <iomanip>

#include "Util.h"

DECLARE_EXCEPTION(CVectorInvalidIndex)

/**
 * A circular vector, also called a circular buffer.
 * Random access, slightly slower than for a normal vector.
 * Efficient insertion and removal at both ends.
 * 
 * @author mfreire
 */
template <class Type>
class CVector {

    /// initial size to reserve for an empty vector
    static const uint INITIAL_SIZE = 16;
    
    Type* _v;    ///< dynamically-reserved array of elements
    uint _start; ///< index of first slot used
    uint _end;   ///< index of first free slot after start
    uint _used;  ///< number of slots used
    uint _max;   ///< total number of slots in _v
    
public:
    
    /**  */
    CVector() : _start(0), _end(0), _used(0), _max(INITIAL_SIZE) {
        _v = new Type[_max];
    }
    
    /**  */
    CVector(const CVector& other) :
        _start(other._start), _end(other._end),
        _used(other._used), _max(other._max) {
            
        _v = new Type[other._max];
        for (uint i=0; i<_max; i++) {
            _v[i] = other._v[i];
        }        
    }    
    
    /**  */
    ~CVector() {
        delete[] _v;
        _v = 0;
    }

    /** */
    CVector& operator=(const CVector& other) {
        delete _v;
        _max = other._max;
        _v = new Type[_max];
        _used = other.size();
        for (uint i=other._start, j=0; i!=other._end; i=other._inc(i)) {
            _v[j++] = other._v[i];
        }
        _start = 0;
        _end = _used;
        return (*this);
    }    
    
    /**  */
    uint size() const {
        return _used;
    }
    
    class Iterator {
    public:
        void next() {
            _pos = _cv->_inc(_pos);
        }
        
        const Type& elem() const {
            return _cv->_v[_pos];
        }
        
        Type& elem() { NON_CONST_VARIANT(Type, Iterator, elem()); }

        bool operator==(const Iterator &other) const {
            return _pos == other._pos;
        }
        
        bool operator!=(const Iterator &other) const {
            return _pos != other._pos;
        }
    protected:
        friend class CVector;
        
        const CVector* _cv;
        
        uint _pos;
        
        Iterator(const CVector *cv, uint pos)
            : _cv(cv), _pos(pos) {}
    };    
    
    /** */
    const Iterator find(const Type& e) const {
        for (uint i=_start, j=0; i!=_end; i=_inc(i)) {
            if (e == _v[i]) {
                return Iterator(this, i);
            }
        }
        return end();
    }
    
    /** */
    Iterator begin() const {
        return Iterator(this, _start);
    }
    
    /** */
    Iterator end() const {
        return Iterator(this, _end);
    }
    
    /** */
    const Type& at(uint pos) const {        
        if (pos < 0 || pos >= _used) {
            throw CVectorInvalidIndex("at");
        }
        return _v[_adjust(pos)];
    }

    /** */
    Type& at(uint pos) {
        NON_CONST_VARIANT(Type,CVector,at(pos));
    }

    /** */
    void push_back(const Type& e) {
        if (_inc(_end) == _start) {
            _grow();
        }
        _v[_end] = e;
        _end = _inc(_end);
        _used ++;
    }

    /** */
    const Type& back() const {
        if (_used == 0) {
            throw CVectorInvalidIndex("back");
        }
        return (const Type &)_v[_dec(_end)];
    }

    /** */
    Type& back() {
        NON_CONST_VARIANT(Type,CVector,back());
    }

    /**  */
    void pop_back() {
        if (_used == 0) {
            throw CVectorInvalidIndex("pop_back");
        }
        _end = _dec(_end);
        _used --;
    }

    /**  */
    void push_front(const Type& e) {
        if (_dec(_start) == _end) {
            _grow();
        }
        _start = _dec(_start);
        _v[_start] = e;
        _used ++;
    }
    
    /**  */
    const Type& front() const {
        if (_used == 0) {
            throw CVectorInvalidIndex("front");
        }
        return (const Type &)_v[_start];
    }

    /**  */
    Type& front() {
        NON_CONST_VARIANT(Type,CVector,front());
    }    

    /**  */
    void pop_front() {
        if (_used == 0) {
            throw CVectorInvalidIndex("pop_front");
        }
        _start = _inc(_start);
        _used --;
    }            
    
    /** */
    void print(std::ostream &out=std::cout) {
        for (uint i=0; i<_max; i++) {
            out << std::setw(2) << i << ": ";
            // NOTE: _inside() is O(n), which makes the metod O(n^2)
            if (_inside(i)) {
                out << _v[i];
            } else {
                out << "? ";
            }
            if (i == _start) out << "<-(start)";
            if (i == _end) out << "<-(end)";
            out << std::endl;
        }
    }    
    
private:

    void _grow() {
        Type *old = _v;
        _v = new Type[_max*2];
        
        for (uint i=_start, j=0; i!=_end; i=_inc(i)) {
            _v[j++] = old[i];
        }
        // if _max is changed before the copy is over, inc() fails
        _max *= 2;
        _start = 0;
        _end = _used;
        delete[] old;
    }

    uint _dec(uint i) const {
        return (i == 0) ? _max-1 : i-1;
    }

    uint _inc(uint i) const {
        return (i == _max-1) ? 0 : i+1;
    }

    bool _inside(uint i) const {
        for (uint j=_start; j!=_end; j=_inc(j)) {
            if (j == i) return true;
        }
        return false;
    }
    
    uint _adjust(uint external) const {
        uint internal = (external + _start);
        return (internal >= _max) ? internal - _max : internal;
    }
};

#endif // __CVECTOR_H
