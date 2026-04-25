
#include "list.hpp"
#include <iostream>
#include <list>
#include <cassert>

int main() {
    // Basic test
    sjtu::list<int> mylist;
    std::list<int> stdlist;
    
    // Test push operations
    mylist.push_back(1);
    mylist.push_front(2);
    mylist.push_back(3);
    
    stdlist.push_back(1);
    stdlist.push_front(2);
    stdlist.push_back(3);
    
    // Test size and access
    assert(mylist.size() == stdlist.size());
    assert(mylist.front() == stdlist.front());
    assert(mylist.back() == stdlist.back());
    
    // Test iterators
    auto myit = mylist.begin();
    auto stdit = stdlist.begin();
    for (; myit != mylist.end() && stdit != stdlist.end(); ++myit, ++stdit) {
        assert(*myit == *stdit);
    }
    
    // Test copy constructor
    sjtu::list<int> mylist2(mylist);
    assert(mylist2.size() == mylist.size());
    assert(mylist2.front() == mylist.front());
    assert(mylist2.back() == mylist.back());
    
    // Test assignment
    sjtu::list<int> mylist3;
    mylist3 = mylist;
    assert(mylist3.size() == mylist.size());
    assert(mylist3.front() == mylist.front());
    assert(mylist3.back() == mylist.back());
    
    // Test insert and erase
    auto it = mylist.begin();
    ++it;
    mylist.insert(it, 5);
    
    stdit = stdlist.begin();
    ++stdit;
    stdlist.insert(stdit, 5);
    
    assert(mylist.size() == stdlist.size());
    
    // Test pop operations
    mylist.pop_front();
    mylist.pop_back();
    stdlist.pop_front();
    stdlist.pop_back();
    
    assert(mylist.size() == stdlist.size());
    
    // Test clear
    mylist.clear();
    assert(mylist.empty());
    assert(mylist.size() == 0);
    
    std::cout << "All basic tests passed!" << std::endl;
    return 0;
}
