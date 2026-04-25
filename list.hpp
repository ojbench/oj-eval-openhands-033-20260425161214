#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include <cstddef>
#include <memory>
#include <exception>

namespace sjtu {

class container_is_empty : public std::exception {
public:
    const char *what() const noexcept override {
        return "Container is empty";
    }
};

template <typename T>
class list {
protected:
    struct node {
        T data;
        node *prev;
        node *next;
        
        node() : prev(nullptr), next(nullptr) {}
        node(const T &value) : data(value), prev(nullptr), next(nullptr) {}
        node(const T &value, node *p, node *n) : data(value), prev(p), next(n) {}
    };
    
    node *head;
    node *tail;
    size_t list_size;
    
    node *insert(node *pos, node *cur) {
        cur->next = pos;
        cur->prev = pos->prev;
        pos->prev->next = cur;
        pos->prev = cur;
        list_size++;
        return cur;
    }
    
    node *erase(node *pos) {
        node *next_node = pos->next;
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;
        list_size--;
        return next_node;
    }

public:
    class const_iterator;
    class iterator {
    private:
        node *current;
        list *container;
        
    public:
        iterator(node *p = nullptr, list *c = nullptr) : current(p), container(c) {}
        
        iterator operator++(int) {
            iterator tmp = *this;
            current = current->next;
            return tmp;
        }
        
        iterator &operator++() {
            current = current->next;
            return *this;
        }
        
        iterator operator--(int) {
            iterator tmp = *this;
            current = current->prev;
            return tmp;
        }
        
        iterator &operator--() {
            current = current->prev;
            return *this;
        }
        
        T &operator*() const {
            if (current == nullptr || (container && current == container->tail)) {
                throw container_is_empty();
            }
            return current->data;
        }
        
        T *operator->() const noexcept {
            if (current == nullptr || (container && current == container->tail)) {
                return nullptr;
            }
            return &(current->data);
        }
        
        bool operator==(const iterator &rhs) const {
            return current == rhs.current;
        }
        
        bool operator==(const const_iterator &rhs) const {
            return current == rhs.current;
        }
        
        bool operator!=(const iterator &rhs) const {
            return current != rhs.current;
        }
        
        bool operator!=(const const_iterator &rhs) const {
            return current != rhs.current;
        }
        
        node *get_node() const { return current; }
        
        friend class list;
        friend class const_iterator;
    };
    
    class const_iterator {
    private:
        const node *current;
        const list *container;
        
    public:
        const_iterator(const node *p = nullptr, const list *c = nullptr) : current(p), container(c) {}
        const_iterator(const iterator &other) : current(other.current), container(other.container) {}
        
        const_iterator operator++(int) {
            const_iterator tmp = *this;
            current = current->next;
            return tmp;
        }
        
        const_iterator &operator++() {
            current = current->next;
            return *this;
        }
        
        const_iterator operator--(int) {
            const_iterator tmp = *this;
            current = current->prev;
            return tmp;
        }
        
        const_iterator &operator--() {
            current = current->prev;
            return *this;
        }
        
        const T &operator*() const {
            if (current == nullptr || (container && current == container->tail)) {
                throw container_is_empty();
            }
            return current->data;
        }
        
        const T *operator->() const noexcept {
            if (current == nullptr || (container && current == container->tail)) {
                return nullptr;
            }
            return &(current->data);
        }
        
        bool operator==(const iterator &rhs) const {
            return current == rhs.current;
        }
        
        bool operator==(const const_iterator &rhs) const {
            return current == rhs.current;
        }
        
        bool operator!=(const iterator &rhs) const {
            return current != rhs.current;
        }
        
        bool operator!=(const const_iterator &rhs) const {
            return current != rhs.current;
        }
        
        const node *get_node() const { return current; }
        
        friend class list;
    };

    list() : list_size(0) {
        head = new node();
        tail = new node();
        head->next = tail;
        tail->prev = head;
    }
    
    list(const list &other) : list_size(0) {
        head = new node();
        tail = new node();
        head->next = tail;
        tail->prev = head;
        
        for (const_iterator it = other.cbegin(); it != other.cend(); ++it) {
            push_back(*it);
        }
    }
    
    virtual ~list() {
        clear();
        delete head;
        delete tail;
    }
    
    list &operator=(const list &other) {
        if (this != &other) {
            clear();
            for (const_iterator it = other.cbegin(); it != other.cend(); ++it) {
                push_back(*it);
            }
        }
        return *this;
    }
    
    const T &front() const {
        if (empty()) {
            throw container_is_empty();
        }
        return head->next->data;
    }
    
    const T &back() const {
        if (empty()) {
            throw container_is_empty();
        }
        return tail->prev->data;
    }
    
    T &front() {
        if (empty()) {
            throw container_is_empty();
        }
        return head->next->data;
    }
    
    T &back() {
        if (empty()) {
            throw container_is_empty();
        }
        return tail->prev->data;
    }
    
    iterator begin() {
        return iterator(head->next, this);
    }
    
    const_iterator cbegin() const {
        return const_iterator(head->next, this);
    }
    
    iterator end() {
        return iterator(tail, this);
    }
    
    const_iterator cend() const {
        return const_iterator(tail, this);
    }
    
    virtual bool empty() const {
        return list_size == 0;
    }
    
    virtual size_t size() const {
        return list_size;
    }
    
    virtual void clear() {
        while (!empty()) {
            pop_front();
        }
    }
    
    virtual iterator insert(iterator pos, const T &value) {
        node *new_node = new node(value);
        insert(pos.current, new_node);
        return iterator(new_node, this);
    }
    
    virtual iterator erase(iterator pos) {
        if (empty() || pos.current == tail) {
            throw container_is_empty();
        }
        node *next_node = erase(pos.current);
        delete pos.current;
        return iterator(next_node, this);
    }
    
    void push_back(const T &value) {
        insert(end(), value);
    }
    
    void pop_back() {
        if (empty()) {
            throw container_is_empty();
        }
        erase(--end());
    }
    
    void push_front(const T &value) {
        insert(begin(), value);
    }
    
    void pop_front() {
        if (empty()) {
            throw container_is_empty();
        }
        erase(begin());
    }
};

} // namespace sjtu

#endif // SJTU_LIST_HPP
