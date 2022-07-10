#include <stdlib.h>
#include <initializer_list>
#include <cstddef>
#include <iostream>

template <class T>
class s21_list {
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

   private:
    typedef struct t_node {
        value_type value_;
        struct t_node* next_;
    } t_node;
    t_node node_;
    t_node* head_;

   public:
    // Мы должны запретить операцию
    // присваивания для обычного ListConstIterator
    // и разрешить для ListIterator
    class ListConstIterator {
       protected:
        value_type* ptr_;
        void operator=(const ListConstIterator& other);

       public:
        ListConstIterator(value_type* ptr) { this->ptr_ = ptr; }
        ~ListConstIterator() { delete ptr_; }
        value_type& operator*() { return *ptr_; }
    };
    class ListIterator : ListConstIterator {
       public:
        void operator=(const_reference other) {
            this->ptr_ = &(const_cast<value_type&>(other));
        }
    };

    using iterator = ListIterator;
    using const_iterator = ListConstIterator;

    s21_list() { this->node_.next_ = nullptr;
        head_ = nullptr;
    }
    // s21_list(size_type n) {
    //     head_ = nullptr;
    //     if (n > 0) {
    //         t_node tmp;
    //         for (; n > 0; n--) {
    //             t_node other;
    //             this->node_.next_ = &other;
    //             tmp = this->node_;
    //             this->node_ = other;
    //         }
    //         this->node_ = tmp;
    //     }
    // }
    s21_list(std::initializer_list<value_type> items) {
        this->head_ = &(this->node_);
        t_node* tmp = &(this->node_);
        auto i = items.begin();
        for (auto element : items) {
            tmp->value_ = element;
            if (i != items.end() - 1) {
                create_new_node(tmp);
            }
            i++;
        }
        // this->node_ = *tmp;
    }
    void create_new_node(t_node*& tmp) {
        tmp->next_ = new t_node;
        tmp = tmp->next_;
        tmp->next_ = nullptr;
    }
    // s21_list(const s21_list &l) {
    //     s21_list* tmp = this;
    //     s21_list* tmp_l = &l;
    //     while (l) {
    //         this->value_ = l.value_;
    //         if (l.next_) {
    //             s21_list other();
    //             this->next_ = &other;
    //             this = other;
    //             &l = &l.next_;
    //         }
    //     }
    //     this = tmp;
    //     &l = tmp_l;
    // }
    // s21_list(s21_list &&l) {  конструктор перемещения сделаю потом

    // }
    ~s21_list() {
        t_node* tmp = this->node_.next_;
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

    void get_node_values() {
        t_node* tmp = head_;
        while (tmp) {
            std::cout << tmp->value_ << std::endl;
            tmp = tmp->next_;
        }
    }

    // void pop_front() {
    //     s21_list node = this->node_;
    //     this->node_. = this->next_;
    //     delete *tmp;
    // }
    void push_front(const_reference value) {
        t_node tmp;
        tmp = this->node_;
        tmp.value_ = value;
        tmp.next_ = &(this->node_);
        this->node_ = tmp;
    }
};