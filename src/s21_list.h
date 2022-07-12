#include <iostream>

template <class T>
class s21_list {
    //=========================================================================
    // List Member type
    //=========================================================================
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

   private:
    typedef struct node_t {
        value_type value_;
        struct node_t* next_;
        struct node_t* prev_;
    } node_t;
    node_t node_;
    node_t* head_;

   public:
    class ListConstIterator {
       protected:
        node_t* ptr_;

       public:
        ListConstIterator() { ptr_ = nullptr; }
        ~ListConstIterator() { ptr_ = nullptr; }
        const value_type& operator*() { return ptr_->value_; }
        bool operator==(const ListConstIterator& other) {
            return ((this->ptr_)->value_ == (other.ptr_)->value_);
        }
        bool operator!=(const ListConstIterator& other) {
            return ((this->ptr_)->value_ != (other.ptr_)->value_);
        }
        node_t* get_ptr() { return ptr_; }
    };
    class ListIterator : public ListConstIterator {
       public:
        void operator=(const node_t& node) {
            this->ListConstIterator::ptr_ = &(const_cast<node_t&>(node));
        }
        void operator++() {
            if ((this->ListConstIterator::ptr_)->next_) {
                this->ListConstIterator::ptr_ =
                    (this->ListConstIterator::ptr_)->next_;
            }
        }
        void operator--() {
            if ((this->ListConstIterator::ptr_)->prev_) {
                this->ListConstIterator::ptr_ =
                    (this->ListConstIterator::ptr_)->prev_;
            }
        }
    };

    using iterator = ListIterator;
    using const_iterator = ListConstIterator;

    //=========================================================================
    // List Functions
    //=========================================================================
    s21_list() {
        this->node_.next_ = nullptr;
        this->node_.prev_ = nullptr;
        this->head_ = nullptr;
        memset(&(this->node_.value_), 0, sizeof(value_type));
    }
    s21_list(size_type n) {
        this->node_.prev_ = nullptr;
        if (n == 0) {
            this->head_ = nullptr;
        } else {
            this->head_ = &(this->node_);
            node_t* tmp = &(this->node_);
            // 1, так как под 1 элемент память уже выделена
            for (; n > 1; n--) {
                create_empty_node(tmp);
            }
        }
    }
    s21_list(std::initializer_list<value_type> items) {
        this->node_.prev_ = nullptr;
        if (items.begin() == items.end()) {
            this->head_ = nullptr;
        } else {
            this->head_ = &(this->node_);
            node_t* tmp = &(this->node_);
            auto i = items.begin();
            for (auto element : items) {
                tmp->value_ = element;
                if (i != items.end() - 1) {
                    create_new_node(tmp);
                }
                i++;
            }
        }
    }
    s21_list(const s21_list& l) { copy_constructor(l); }
    s21_list(s21_list&& l) {
        if (this != &l) {
            copy_constructor(l);
            clear(l);
        }
    }
    ~s21_list() { clear(*this); }
    const s21_list& operator=(s21_list&& l) {
        if (this != &l) {
            copy_constructor(l);
        }
        return *this;
    }

    void copy_constructor(const s21_list& l) {
        if (this != &l) {
            this->head_ = &(this->node_);
            this->node_.prev_ = nullptr;
            node_t* tmp = &(this->node_);
            node_t* l_tmp = l.head_;
            while (l_tmp) {
                tmp->value_ = l_tmp->value_;
                if (l_tmp->next_) {
                    create_new_node(tmp);
                    l_tmp = l_tmp->next_;
                } else {
                    break;
                }
            }
        }
    }
    void create_new_node(node_t*& tmp) {
        tmp->next_ = new node_t;
        (tmp->next_)->prev_ = tmp;
        tmp = tmp->next_;
        tmp->next_ = nullptr;
    }
    void create_empty_node(node_t*& tmp) {
        memset(&(tmp->value_), 0, sizeof(value_type));
        create_new_node(tmp);
    }

    //=========================================================================
    // List Element access
    //=========================================================================
    const_reference front() { return this->node_.value_; }
    const_reference back() {
        node_t* tmp = head_;
        while (tmp->next_) {
            tmp = tmp->next_;
        }
        return tmp->value_;
    }

    //=========================================================================
    // List Iterators
    //=========================================================================
    iterator begin() {
        iterator itr;
        itr = *this->head_;
        return itr;
    }
    iterator end() {
        node_t* tmp = head_;
        while (tmp->next_) {
            tmp = tmp->next_;
        }
        iterator itr;
        itr = *tmp;
        return itr;
    }

    //=========================================================================
    // List Capacity
    //=========================================================================
    bool empty() { return !this->head_; }
    size_type size() {
        size_type counter = 0;
        if (this->head_) {
            counter++;
            node_t* tmp = this->head_;
            while (tmp->next_) {
                tmp = tmp->next_;
                counter++;
            }
        }
        return counter;
    }
    // size_type size() {
    //     iterator itr_begin = this->begin();
    //     iterator itr_end = this->end();
    //     size_type counter = 1;
    //     for (; itr_begin != itr_end; counter++) {
    //         ++itr_begin;
    //     }
    //     return counter;
    // }
    size_type max_size() { return SIZE_MAX; }

    //=========================================================================
    // List Modifiers
    //=========================================================================
    void clear(s21_list& obj) {
        node_t* tmp = obj.node_.next_;
        int flag = false;
        while (obj.node_.next_) {
            if (flag == false) {
                flag = true;
            } else {
                tmp = tmp->next_;
            }
            delete tmp;
            obj.node_.next_ = tmp;
        }
        delete tmp;
        obj.head_ = nullptr;
    }
    // iterator insert(iterator pos, const_reference value) {

    // }
    void erase(const const_iterator& pos) {
        if (const_cast<const_iterator&>(pos).get_ptr()) {
            if ((const_cast<const_iterator&>(pos).get_ptr())->prev_) {
                ((const_cast<const_iterator&>(pos).get_ptr())->prev_)->next_ =
                    (const_cast<const_iterator&>(pos).get_ptr())->next_;
            } else {
                this->head_ =
                    (const_cast<const_iterator&>(pos).get_ptr())->next_;
            }
            if ((const_cast<const_iterator&>(pos).get_ptr())->next_) {
                ((const_cast<const_iterator&>(pos).get_ptr())->next_)->prev_ =
                    (const_cast<const_iterator&>(pos).get_ptr())->prev_;
            }
            if (const_cast<const_iterator&>(pos).get_ptr() != &(this->node_))
                delete const_cast<const_iterator&>(pos).get_ptr();
        }
    }
    void push_front(const_reference value) {
        node_t tmp;
        tmp = this->node_;
        tmp.value_ = value;
        tmp.next_ = &(this->node_);
        this->node_ = tmp;
    }
};