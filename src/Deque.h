/**
 * @file Deque.h
 *
 * Deque.
 * 
 * Estructura de Datos y Algoritmos
 * 
 * Copyright (C) 2014
 * Facultad de Inform�tica, Universidad Complutense de Madrid
 * This software is licensed under the Simplified BSD licence:
 *    (see the LICENSE file or
 *     visit opensource.org/licenses/BSD-3-Clause)
 */

#ifndef EDA_DEQUE_H
#define EDA_DEQUE_H

// default implementation
#include "DoubleList.h"

/**
 * Double-ended queues allow push and pops from both sides.
 * 
 * @author mfreire
 */
template <class Type, class Container = DoubleList<Type> >
class Deque {

    /** */
    Container _v;

public:

    /**  */    
    void push_back(const Type& e) {
        _v.push_back(e);
    }
    /**  */
    void pop_front() {
        _v.pop_front();
    }
    
    /**  */
    void push_front(const Type& e) {
        _v.push_front(e);
    }

    /**  */
    const Type& front() const {
        return _v.front();
    }

    /**  */
    const Type& back() const {
        return _v.back();
    }
    
    /**  */    
    uint size() const {
        return _v.size();
    }
};

#endif // EDA_DEQUE_H
