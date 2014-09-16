edalib
======

An [STL](http://en.wikipedia.org/wiki/Standard_Template_Library)-like library for use in teaching EDA (algorithms and data-structures). The focus is on readability, correctness and compactness (which aids the former two), and optimal big-O efficiency (except in search trees, which are currently unbalanced). Additionally, all structures can generate traces of their internal state to aid with debugging.

##### Linear containers

Do not depend on anything else, and provide linear storage. Support the full range of operations, as long as they are efficient for the specific container type.

* [Vector.h](https://github.com/manuel-freire/edalib/blob/master/src/Vector.h): similar to [`std::vector`](http://en.cppreference.com/w/cpp/container/vector).
* [CVector.h](https://github.com/manuel-freire/edalib/blob/master/src/CVector.h): a circular vector.
* [SingleList.h](https://github.com/manuel-freire/edalib/blob/master/src/SingleList.h): a singly-linked list; insert at front and back, remove only from front. Similar to [`std::forward_list`](http://en.cppreference.com/w/cpp/container/forward_list).
* [DoubleList.h](https://github.com/manuel-freire/edalib/blob/master/src/DoubleList.h): a doubly-linked list; similar to [`std::list`](http://en.cppreference.com/w/cpp/container/list).

##### Derived linear structures

Decorate one of the previous linear containers, allowing fewer operations but providing a cleaner interface.

* [Stack.h](https://github.com/manuel-freire/edalib/blob/master/src/Stack.h): decorates a Vector (could also decorate CVector or DoubleList; since it requires ```push_back()```, it cannot decorate a singly-linked list unless the lists' notion of front and back is reversed). Similar to [`std::stack`](http://en.cppreference.com/w/cpp/container/stack).
* [Queue.h](https://github.com/manuel-freire/edalib/blob/master/src/Queue.h): decorates a CVector or Single or DoubleList. Similar to [`std::queue`](http://en.cppreference.com/w/cpp/container/queue).
* [Deque.h](https://github.com/manuel-freire/edalib/blob/master/src/Deque.h): decorates a CVector or DoubleList. Similar to [`std::deque`](http://en.cppreference.com/w/cpp/container/deque).

##### Associative containers

Allow quick lookup, addition and removal of elements indexed by a key. Support the full range of associative operations.

* [HashTable.h](https://github.com/manuel-freire/edalib/blob/master/src/HashTable.h): hash table implemented with a [DoubleList](https://github.com/manuel-freire/edalib/blob/master/src/DoubleList.h) for each bucket. Similar to [`std:unordered_map`](http://en.cppreference.com/w/cpp/container/unordered_map)
* [TreeMap.h](https://github.com/manuel-freire/edalib/blob/master/src/TreeMap.h): (not really balanced) search tree implemented over a [BinTree](https://github.com/manuel-freire/edalib/blob/master/src/BinTree.h). Similar to [`std::map`](http://en.cppreference.com/w/cpp/container/map)

##### Derived associative containers.

Decorate an associative container, allowing fewer operations but with a cleaner interface.

* [Map.h](https://github.com/manuel-freire/edalib/blob/master/src/Map.h): conventional maps. Use ```Map<KeyType, ValueType>::T``` for the tree and ```Map<KeyType, ValueType>::H``` for the hash versions.
* [Set.h](https://github.com/manuel-freire/edalib/blob/master/src/Set.h): conventional sets. Use ```Set<KeyType>::T``` for the tree and ```Set<KeyType>::H``` for the hash version. ```Set<KeyType>::T``` is similar to [`std::set`](http://en.cppreference.com/w/cpp/container/set), while `Set<KeyType>::H` is similar to [`std::unordered_set`](http://en.cppreference.com/w/cpp/container/unordered_set).

##### Misc. Utilities

All previous files ```#include``` [Util.h](https://github.com/manuel-freire/edalib/blob/master/src/Util.h) for macros and typedefs.

* [BinTree.h](https://github.com/manuel-freire/edalib/blob/master/src/BinTree.h): provides a fully-exposed implementation of binary tree nodes and operations (including pretty-printing). Useful to implement customized trees. Used in the implementation of the [TreeMap](https://github.com/manuel-freire/edalib/blob/master/src/TreeMap.h).
* [Util.h](https://github.com/manuel-freire/edalib/blob/master/src/Util.h): provides a few useful macros, allows printing out any structure with iterators, and copying into any structure with a ```push_back()``` inserter.

##### Other files

* [test/test.cpp](https://github.com/manuel-freire/edalib/blob/master/test/test.cpp): a set of unit tests, which is neither exhaustive nor particularly organized. Mostly for testing during development.
* `.travis.yml`: TravisCI test enviroment config file. Runs the above tests when pushing to github, both compiling with Clang and GCC.
* LICENSE: the BSD 3-clause license, under which *edalib* is licensed.
* doxyfile: to generate documentation. Install doxygen and launch using ```doxygen doxyfile``` from the root of the project.
* SConstruct: to build the tests in a cross-platform manner. Install SCons and launch via ```scons``` from the root of the project. Use ```scons -c``` to clean compilation products.
