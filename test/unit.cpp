#include "DoubleList.h"
#include "CVector.h"
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
#include "HashTable.h"
#include "Map.h"
#include "Set.h"
#include "BinTree.h"

#include "bandit/bandit.h"
#include <vector>

using namespace bandit;

template<typename C, typename T>
void test_push_back(C &c, const std::vector<T> &contents) {
    it("can be added to via push_back(), while keeping back() in sync", [&](){
        for (auto t : contents) {
            uint sizeBefore = c.size();
            c.push_back(t);
            AssertThat(c.size(), Equals(sizeBefore + 1));
            AssertThat(c.back(), Equals(t));
        }
    });
}

template<typename C, typename T>
void test_pop_back(C &c, const std::vector<T> &contents) {
    it("can be popped via pop_back(), while keeping back() in sync", [&](){
        for (auto it=contents.rbegin(); it!=contents.rend(); it++) {
            uint sizeBefore = c.size();
            c.pop_back();
            AssertThat(c.size(), Equals(sizeBefore - 1));
            AssertThat(c.back(), Equals(*it));            
        }
    });
}

template<typename C, typename T>
void test_iterator(const C &c, const std::vector<T> &contents) {
    it("iterates fine, and contains what it should", [&](){
        typename C::Iterator it=c.begin();
        for (auto t : contents) {
            AssertThat(it.elem(), Equals(t));
            it.next();
        }
        AssertThat(it, Equals(c.end()));
    });
}

template<typename C, typename T>
void test_grow(C &c, const T &t, uint size) {
    it("grows fine", [&](){
        uint sizeBefore = c.size();
        for (uint i=0; i<size; i++) {
            c.push_back(t);
        }
        uint sizeAfter = c.size();
        AssertThat(sizeAfter, Equals(sizeBefore + size));
        for (uint i=0; i<size; i++) {
            c.pop_back();
        }
        AssertThat(c.size(), Equals(sizeBefore));
    });    
}

template<typename C>
void test_shrink(C &c, uint size) {
    it("shrinks back fine", [&](){
        int pops = 0;
        while(c.size()) {
            c.pop_back();
            pops ++;
        }
        AssertThat(pops, Equals(size));
    });
}

template<typename C, typename T>
void test_linear(C &c, const std::vector<T> &contents) {
    it("is empty", [&](){
        AssertThat(c.size(), Equals(0));
    });
    it("fails when we attempt to retrieve from empty", [&](){
        AssertThrows(AbstractException, c.begin().elem());
    });
    it("fails when we attempt to retrieve beyond last", [&](){
        AssertThrows(AbstractException, c.end().elem());
    });
    test_push_back(c, contents);
    it("allows access to first", [&](){
        AssertThat(c.begin().elem(), Equals(contents[0]));
    });
    test_iterator(c, contents);
    test_pop_back(c, contents);
    test_grow(c, 0, 100000);
    it("fails when we attempt to retrieve beyond last", [&](){
        AssertThrows(AbstractException, c.end().elem());
    });
    test_shrink(c, 100000);
}    

go_bandit([](){
    describe("vector:", [](){
        Vector<int> v;        
    });    
    
    describe("linear:", [](){
        std::vector<int> o = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};      
        describe("vector:", [&](){
            Vector<int> v;
            test_linear(v, o);
        });
        describe("circular-vector:", [&](){
            CVector<int> c;
            test_linear(c, o);
        });
        describe("double-list:", [&](){
            DoubleList<int> d;
            test_linear(d, o);
        });
    });
});

int main(int argc, char* argv[]) {
    return bandit::run(argc, argv);
}