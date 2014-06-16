edalib
======

An stl-like library for use in teaching EDA (algorithms and data-structures).


##### Linear containers

Do not depend on anything else, and provide linear storage. Support the full range of operations, as long as they are efficient for the specific container type.

* Vector.h: similar to stl::vector
* CVector.h: a circular vector
* SingleList.h: a singly-linked list; insert at front and back, remove only from front
* DoubleList.h: a doubly-linked list; similar to stl::list

##### Derived linear structures

Decorate one of the previous linear containers, allowing fewer operations but providing a cleaner interface.

* Stack.h: decorates a Vector (could also decorate CVector or DoubleList; since it requires push_back, it cannot decorate a singly-linked list unless the lists' notion of front and back is reversed). Similar to stl::stack.
* Queue.h: decorates a CVector or Single or DoubleList. Similar to stl::queue.
* Deque.h: decorates a CVector or DoubleList. Similar to stl::deque.

##### Associative containers

Allow quick lookup, addition and removal of elements indexed by a key. Support the full range of associative operations.

* HashTable.h: hash table implemented with a DoubleList for each bucket
* TreeMap.h: (not really balanced) search tree implemented over a BinTree. Similar to stl::map

##### Derived associative containers.

Decorate an associative container, allowing fewer operations but with a cleaner interface.

* Map.h: conventional maps. Use Map<KeyType, ValueType>::T for the tree and ::H for the hash versions
* Set.h: conventional sets. Use Set<KeyType>::T for the tree and Set<KeyType>::H for the hash version; Set<KeyType>::T is similar to stl::set

##### Misc. Utilities

All previous files #include ```Util.h``` for macros and typedefs.

* BinTree.h: provides a fully-exposed implementation of binary tree nodes and operations (including pretty-printing). Useful to implement customized trees. Used in TreeMap.h.
* Util.h: provides a few useful macros and typedefs, allows printing out any structure with iterators, and copying into any structure with a push_back inserter.

##### Other files

* test/test.cpp: a set of tests, which is neither exhaustive nor particularly organized. Mostly for testing during development.
* LICENSE: the BSD 3-clause license, under which edalib is licensed
* doxyfile: to generate documentation. Install doxygen and launch using ```doxygen doxyfile``` from the root of the project
* SConstruct: to build the tests in a cross-platform manner. Install SCons and launch via ```scons``` from the root of the project. Use ```scons -c``` to clean products
