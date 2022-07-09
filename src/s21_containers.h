
template <class T>
class list {
    using value_type = T;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = ListIterator<value_type>;
    using const_iterator = ListConstIterator<T>;
    using size_type = size_t;

    private:
        value_type value_;
        list* next_;
    public:
        // Мы должны запретить операцию
        // присваивания для обычного ConstListIterator
        class ConstListIterator<value_type> {
            protected:
                value_type* ptr_;
                operator=(const ConstListIterator& other);
            public:
                ConstListIterator(value_type* ptr) {
                    this->ptr = ptr_;
                }
                ~ConstListIterator() {
                    delete ptr_;
                }
                value_type& operator*() {
                    return *ptr_;
                }
        };
        class ListIterator<value_type> : ConstListIterator<value_type> {
            public:
                operator=(const_reference other) {
                    this->ptr_ = other.ptr_;
                }
        }

        list() {
            this->next = nullptr;
        }
        list(size_type n) {
            list tmp = *this;
            for (; n >= 0; n--) {
                list other();
                this->next_ = other;
                this = other;
            }
            *this = tmp;
        }





};