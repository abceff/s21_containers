#include <iostream>
#include <cstring>

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
    // Мы должны запретить операцию
    // присваивания для обычного ListConstIterator
    // и разрешить для ListIterator
    class ListConstIterator {
       protected:
        node_t* ptr_;

       public:
        ListConstIterator() { ptr_ = nullptr; }
        ~ListConstIterator() { ptr_ = nullptr; }
        node_t* get_ptr() { return ptr_; }
    };
    class ListIterator : public ListConstIterator {
       public:
        void operator=(const node_t& node) {
            this->ListConstIterator::ptr_ = &(const_cast<node_t&>(node));
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
        this->head_ = &(this->node_);
        memset(&(this->node_.value_), 0, sizeof(value_type));
    }
    s21_list(size_type n) {
        this->node_.prev_ = nullptr;
        if (n == 0) {
            this->head_ = nullptr;
        } else {
            this->head_ = &(this->node_);
            node_t* tmp = &(this->node_);
            for (; n > 0; n--) {
                create_new_node(tmp);
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
    void create_new_node(node_t*& tmp) {
        tmp->next_ = new node_t;
        (tmp->next_)->prev_ = tmp;
        tmp = tmp->next_;
        tmp->next_ = nullptr;
    }
    s21_list(const s21_list& l) { copy_constructor(l); }
    s21_list(s21_list&& l) { move_constructor(l); }
    void copy_constructor(const s21_list& l) {
        if (this != &l) {
            this->head_ = &(this->node_);
            this->node_.prev_ = nullptr;
            node_t* tmp = &(this->node_);
            node_t* l_tmp = l.head_;
            while (l_tmp) {
                tmp->value_ = l_tmp->value_;
                tmp->next_ = l_tmp->next_;
                if (l_tmp->next_) {
                    create_new_node(tmp);
                    l_tmp = l_tmp->next_;
                }
            }
        }
    }
    void move_constructor(s21_list&& l) {
        if (this != &l) {
            copy_constructor(l);
            ~s21_list(l);
        }
    }
    ~s21_list() { clear(); }
    const s21_list& operator=(s21_list&& l) {
        if (this != &l) {
            ~s21_list();
            move_constructor(l);
        }
        return *this;
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
        itr = this->node_;
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
        node_t* tmp = head_;
        while (tmp->next_) {
            tmp = tmp->next_;
            counter++;
        }
        return counter;
    }
    size_type max_size() { return SIZE_MAX; }

    //=========================================================================
    // List Modifiers
    //=========================================================================
    void clear() {
        node_t* tmp = this->node_.next_;
        int flag = false;
        while (this->node_.next_) {
            if (flag == false) {
                flag = true;
            } else {
                tmp = tmp->next_;
            }
            delete tmp;
            this->node_.next_ = tmp;
        }
        delete tmp;
        head_ = nullptr;
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

    void get_node_values() {
        // node_t* tmp = head_;
        // while (tmp) {
        //     std::cout << tmp->value_ << std::endl;
        //     tmp = tmp->next_;
        // }
        std::cout << this->node_.value_ << std::endl;
    }
    void get_node_value() {
        return this->node_.value_;
    }

    // void pop_front() {
    //     s21_list node = this->node_;
    //     this->node_. = this->next_;
    //     delete *tmp;
    // }
    void push_front(const_reference value) {
        node_t tmp;
        tmp = this->node_;
        tmp.value_ = value;
        tmp.next_ = &(this->node_);
        this->node_ = tmp;
    }
};