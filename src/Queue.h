/**
 * @file Queue.h
 *
 * Queue.
 * 
 * Estructura de Datos y Algoritmos
 * 
 * Copyright (C) 2014
 * Facultad de Informática, Universidad Complutense de Madrid
 * This software is licensed under the Simplified BSD licence:
 *    (see the LICENSE file or
 *     visit opensource.org/licenses/BSD-3-Clause)
 */

#ifndef EDA_QUEUE_H
#define EDA_QUEUE_H

// default implementation
#include "SingleList.h"

/**
 * Queues allow elements to be added at the back and extracted
 * from the front: first in, first out
 * 
 * @author mfreire
 */
template <class Type, class Container = SingleList<Type> >
class Queue {

    /** */
    Container _v;

public:

    /**  */    
    void push(const Type& e) {
        _v.push_back(e);
    }

    /**  */    
    void pop() {
        _v.pop_front();
    }

    /**  */
    const Type& top() const {
        return front();
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

#endif // EDA_QUEUE_H
