//
// Created by Patrick Thomas on 05/13/2025
//

#ifndef SINGLY_LIST_HPP
#define SINGLY_LIST_HPP

#include <cstddef>
#include <memory>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <ranges>
#include <unordered_set>
#include <compare>
#include <concepts>


namespace adt {

    template<class T, class Allocator = std::allocator<T>>
    class singly_list {
    public:
        /* -----------------------------------------------Definitions----------------------------------------------- */
        using value_type = T;

        using allocator_type = Allocator;

        using size_type = std::size_t;

        using difference_type = std::ptrdiff_t;

        using reference = value_type&;

        using const_reference = const value_type&;

        using pointer = typename std::allocator_traits<allocator_type>::pointer;

        using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;

    private:
        /* -------------------------------------------------Node---------------------------------------------------- */
        struct _Node {
            /* --------------------------------------------Fields--------------------------------------------------- */
            value_type value;

            _Node* next;

            /* -----------------------------------------Constructors------------------------------------------------ */
            constexpr _Node() noexcept : value(value_type()), next(nullptr) {}

            constexpr _Node(const_reference value) noexcept : value(value), next(nullptr) {}

            constexpr _Node(const_reference value, _Node* next) noexcept : value(value), next(next) {}

            constexpr _Node(const _Node&) noexcept = default;

            constexpr _Node(_Node&&) noexcept = default;

            /* -------------------------------------------Destructor------------------------------------------------ */
            constexpr ~_Node() noexcept = default;

            /* --------------------------------------Overloaded Operators------------------------------------------- */
            constexpr _Node& operator=(const _Node&) noexcept = default;

            constexpr _Node& operator=(_Node&&) noexcept = default;

            [[nodiscard]] constexpr bool operator==(const _Node&) const noexcept = default;

            [[nodiscard]] constexpr auto operator<=>(const _Node&) const noexcept = default;

        };

        /* ----------------------------------------------Definitions------------------------------------------------ */
        using allocator_traits = typename std::allocator_traits<allocator_type>;

        using _NodeAllocator = typename allocator_traits::template rebind_alloc<_Node>;

        using node_allocator_traits = typename std::allocator_traits<_NodeAllocator>;

        /* ------------------------------------------------Fields--------------------------------------------------- */
        _Node dummy;

        _Node* head;

        allocator_type allocator;

        _NodeAllocator node_allocator;

        size_type sz;

        /* ------------------------------------------------Methods-------------------------------------------------- */
        constexpr _Node* _create_node(const_reference value, _Node* next = nullptr) noexcept {
            _Node* node = node_allocator_traits::allocate(this->node_allocator, 1);
            node_allocator_traits::construct(this->node_allocator, node, value, next);
            return node;
        }

        constexpr _Node* _delete_node(_Node* node) noexcept {
            if (node == nullptr) {
                return nullptr;
            }

            node_allocator_traits::destroy(this->node_allocator, node);
            node_allocator_traits::deallocate(this->node_allocator, node, 1);
            return nullptr;
        }

        constexpr void _clear() noexcept {
            _Node* node = this->head->next,
                 * next;

            while (node != nullptr) {
                next = node->next;

                this->_delete_node(node);

                node = next;
            }
        }

        constexpr _Node* _insert_after(_Node* node, const_reference value) noexcept {
            // Save a copy of the node after `node`
            _Node* next = node->next;

            // Create a new node to store `value` and point `node->next` to the new node
            node->next = this->_create_node(value, next);
            
            // Update the size counter
            this->sz++;

            return node->next;
        }

        constexpr _Node* _erase_after(_Node* node) noexcept {
            // Save a copy of the node two nodes after `node`
            _Node* next = node->next->next;

            // Delete the node after `node`
            this->_delete_node(node->next);

            // Point the node after `node` to `next`
            node->next = next;

            // Update the size counter
            this->sz--;

            return node->next;
        }

        constexpr void _splice_after(_Node* pos_node, singly_list& other) noexcept {
            _Node* other_prev = other.head->next;
            _Node* temp;

            while (other_prev != nullptr) {
                // Copy the current node from `other` and insert it after `pos_node`
                pos_node->next = this->_create_node(other_prev->value, pos_node->next);
                pos_node = pos_node->next;
                this->sz++;

                // Remove the node containing `other_node->next->value` from `other`
                temp = other_prev;
                other_prev = other_prev->next;
                this->_delete_node(temp);
            }

            other.head->next = nullptr;
            other.sz = 0;
        }

        constexpr void _splice_after(_Node* pos_node, singly_list& other, _Node* it_node) noexcept {
            // Copy and insert the node following `it_node` after `pos_node`
            pos_node->next = this->_create_node(it_node->next->value, pos_node->next);
            this->sz++;

            // Remove the node following `it_node` from `other`
            _Node* temp = it_node->next;
            it_node->next = it_node->next->next;
            this->_delete_node(temp);
            other.sz--;
        }

        constexpr void _splice_after(_Node* pos_node, singly_list& other,
                                     _Node* first_node, _Node* last_node) noexcept {
            _Node* temp;

            // While in the range (`first`, `last`) and the end of the list has NOT been reached...
            while (first_node != nullptr && first_node->next != nullptr && first_node->next != last_node) {
                // Copy the current node from other and insert it after `pos_node`
                pos_node->next = this->_create_node(first_node->next->value, pos_node->next);
                this->sz++;

                // Delete the original node from other
                temp = first_node->next->next;
                this->_delete_node(first_node->next);
                first_node->next = temp;
                other.sz--;

                // Advance to the next node
                pos_node = pos_node->next;
            }
        }

        constexpr void _resize(size_type new_size, const_reference value) noexcept {
            if (new_size > this->sz) {
                // Calculate the number of new nodes to allocate
                size_type num_nodes_to_alloc = new_size - this->sz;

                // Update the `this->sz`
                this->sz = new_size;

                // Get to the tail of the list
                _Node* tail = this->head;
                while (tail->next != nullptr) {
                    tail = tail->next;
                }

                // Insert `num_nodes_to_alloc` nodes after `tail`
                for (size_type i = 0; i < num_nodes_to_alloc; i++) {
                    tail->next = this->_create_node(value);
                    tail = tail->next;
                }
            } else if (new_size < this->sz) {
                // Get to the new tail (`num_nodes_to_dealloc`th node)
                _Node* new_tail = this->head,
                     * next;
                for (size_type i = 0; i < new_size; i++) {
                    new_tail = new_tail->next;
                }

                // For all nodes after `new_tail`
                while (new_tail->next != nullptr) {
                    // Save a copy of the next node
                    next = new_tail->next->next;

                    // Delete the current node
                    this->_delete_node(new_tail->next);
                    
                    // Go to the next node
                    new_tail->next = next;
                }
                new_tail->next = nullptr;

                // Update the size counter
                this->sz = new_size;
            }
        }

        static constexpr _Node* _merge_sort_split(_Node* node) noexcept {
            _Node* fast = node,
                 * slow = node,
                 * temp;

            // While the end of the list has NOT been reached...
            while (fast != nullptr && fast->next != nullptr) {
                // Point `fast` two nodes ahead
                fast = fast->next->next;

                // If the end of the list has NOT been reached...
                if (fast != nullptr) {
                    // Point `slow` one node ahead
                    slow = slow->next;
                }
            }

            // Split the list in half
            temp = slow->next;
            slow->next = nullptr;

            // Return the second half
            return temp;
        }

        template<class Compare>
        static constexpr _Node* _merge_sort_merge(_Node* first_half, _Node* second_half, Compare comp) noexcept {
            if (first_half == nullptr) {
                return second_half;
            }

            if (second_half == nullptr) {
                return first_half;
            }

            // Compare the values between `first_half` and `second_half`
            if (comp(first_half->value, second_half->value)) {
                // Recursively merge the rest of the lists and link the result to the current node
                first_half->next = _merge_sort_merge(first_half->next, second_half, comp);
                return first_half;
            }

            // Recursively merge the rest of the lists and link the result to the current node
            second_half->next = _merge_sort_merge(first_half, second_half->next, comp);
            return second_half;
        }

        template<class Compare>
        static constexpr _Node* _merge_sort(_Node* first_half, Compare comp) noexcept {
            // Base case
            if (first_half == nullptr || first_half->next == nullptr) {
                return first_half;
            }

            // Split the list in half
            _Node* second_half = _merge_sort_split(first_half);

            // Recursively sort each half
            first_half = _merge_sort(first_half, comp);
            second_half = _merge_sort(second_half, comp);

            // Merge the two sorted halves
            return _merge_sort_merge(first_half, second_half, comp);
        }

        template<class Compare>
        [[nodiscard]] constexpr bool _is_sorted(Compare comp) const noexcept {
            // Return true if the list is empty
            if (this->head->next == nullptr) {
                return false;
            }

            _Node* node = this->head->next;

            // While there are two consecutive nodes to be traversed...
            while (node != nullptr && node->next != nullptr) {
                // If the two consecutive nodes are not comparable..
                if (!comp(node->value, node->next->value)) {
                    return false;
                }

                // Go to the next two consecutive nodes
                node = node->next;
            }

            return true;
        }

    public:
        /* --------------------------------------------Constant Iterator-------------------------------------------- */
        class const_iterator {
        private:
            /* ---------------------------------------------Fields-------------------------------------------------- */
            const singly_list* parent;

            const _Node* node;

            /* -------------------------------------------Constructors---------------------------------------------- */
            constexpr const_iterator(const singly_list* parent, const _Node* node) noexcept 
                : parent(parent), node(node) {}

            /* ---------------------------------------------Friends------------------------------------------------- */
            friend class singly_list;
            
        public:
            /* -------------------------------------------Definitions----------------------------------------------- */
            using iterator_category = std::forward_iterator_tag;

            using value_type = typename singly_list::value_type;

            using allocator_type = typename singly_list::allocator_type;

            using size_type = typename singly_list::size_type;

            using difference_type = typename singly_list::difference_type;

            using reference = value_type&;

            using const_reference = const value_type&;

            using pointer = typename std::allocator_traits<allocator_type>::pointer;

            using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;

            /* ------------------------------------------Constructors----------------------------------------------- */
            constexpr const_iterator() noexcept : parent(nullptr), node(nullptr) {}

            explicit constexpr const_iterator(std::nullptr_t) noexcept : parent(nullptr), node(nullptr) {}

            explicit constexpr const_iterator(const singly_list& list) noexcept
                : parent(&list), node(list.head->next) {}

            constexpr const_iterator(const const_iterator&) noexcept = default;

            constexpr const_iterator(const_iterator&&) noexcept = default;

            /* -------------------------------------------Destructor------------------------------------------------ */
            constexpr ~const_iterator() noexcept = default;

            /* ---------------------------------------Overloaded Operators------------------------------------------ */
            constexpr const_iterator& operator=(const const_iterator&) noexcept = default;

            constexpr const_iterator& operator=(const_iterator&& rhs) noexcept = default;

            constexpr const_iterator& operator=(std::nullptr_t) noexcept {
                this->node = nullptr;
                return *this;
            }

            [[nodiscard]] const_reference operator*() const {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }
                return this->node->value;
            }

            [[nodiscard]] const_pointer operator->() const {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }
                return &(this->node->value);
            }

            const_iterator& operator++() {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }

                this->node = this->node->next;
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator temp = *this;
                ++(*this);
                return temp;
            }

            [[nodiscard]] const_iterator operator+(size_type n) const {
                const _Node* curr = this->node;

                for (size_type i = 0; i < n; i++) {
                    if (curr == nullptr) {
                        throw std::runtime_error("segmentation fault");
                    }

                    curr = curr->next;
                }

                return const_iterator(this->parent, curr);
            }

            const_iterator& operator+=(size_type n) {
                for (size_type i = 0; i < n; i++) {
                    if (this->node == nullptr) {
                        throw std::runtime_error("segmentation fault");
                    }

                    this->node = this->node->next;
                }

                return *this;
            }

            [[nodiscard]] constexpr bool operator==(const const_iterator& rhs) const noexcept {
                return this->node == rhs.node;
            }

            [[nodiscard]] constexpr bool operator==(std::nullptr_t) const noexcept { return this->node == nullptr; }

            [[nodiscard]] constexpr auto operator<=>(const const_iterator& rhs) const noexcept {
                return this->node <=> rhs.node;
            }

            [[nodiscard]] constexpr auto operator<=>(std::nullptr_t) const noexcept { return this->node <=> nullptr; }

        };

        /* ------------------------------------------------Iterator------------------------------------------------- */
        class iterator {
        private:
            /* ---------------------------------------------Fields-------------------------------------------------- */
            const singly_list* parent;

            _Node* node;

            /* -------------------------------------------Constructors---------------------------------------------- */
            constexpr iterator(const singly_list* parent, _Node* node) noexcept : parent(parent), node(node) {}

            /* ---------------------------------------------Friends------------------------------------------------- */
            friend class singly_list;

            friend class const_iterator;
        
        public:
            /* -------------------------------------------Definitions----------------------------------------------- */
            using iterator_category = std::forward_iterator_tag;

            using value_type = typename singly_list::value_type;

            using allocator_type = typename singly_list::allocator_type;

            using size_type = typename singly_list::size_type;

            using difference_type = typename singly_list::difference_type;

            using reference = value_type&;

            using const_reference = const value_type&;

            using pointer = typename std::allocator_traits<allocator_type>::pointer;

            using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;


            /* ------------------------------------------Constructors----------------------------------------------- */
            constexpr iterator() noexcept : parent(nullptr), node(nullptr){}

            explicit constexpr iterator(std::nullptr_t) noexcept : parent(nullptr), node(nullptr) {}

            explicit constexpr iterator(const singly_list& list) noexcept : parent(&list), node(list.head->next) {}

            constexpr iterator(const iterator&) noexcept = default;

            constexpr iterator(iterator&&) noexcept = default;

            /* -------------------------------------------Destructor------------------------------------------------ */
            constexpr ~iterator() noexcept = default;

            /* ---------------------------------------Overloaded Operators------------------------------------------ */
            constexpr iterator& operator=(const iterator& rhs) noexcept = default;

            constexpr iterator& operator=(iterator&&) noexcept = default;

            constexpr iterator& operator=(std::nullptr_t) noexcept {
                this->node = nullptr;
                return *this;
            }

            [[nodiscard]] reference operator*() const {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }
                
                return this->node->value;
            }

            [[nodiscard]] pointer operator->() const {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }

                return &(this->node->value);
            }

            iterator& operator++() {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }
                
                this->node = this->node->next;
                return *this;
            }

            iterator operator++(int) {
                iterator temp = *this;
                ++(*this);
                return temp;
            }

            [[nodiscard]] iterator operator+(size_type n) const {
                _Node* curr = this->node;

                for (size_type i = 0; i < n; i++) {
                    if (curr == nullptr) {
                        throw std::runtime_error("segmentation fault");
                    }
                    
                    curr = curr->next;
                }

                return iterator(this->parent, curr);
            }

            iterator& operator+=(size_type n) {
                for (size_type i = 0; i < n; i++) {
                    if (this->node == nullptr) {
                        throw std::runtime_error("segmentation fault");
                    }
                    this->node = this->node->next;
                }

                return *this;
            }

            [[nodiscard]] constexpr bool operator==(const iterator& rhs) const noexcept {
                return this->node == rhs.node;
            }

            [[nodiscard]] constexpr bool operator==(std::nullptr_t) const noexcept { return this->node == nullptr; }

            [[nodiscard]] constexpr auto operator<=>(const iterator& rhs) const noexcept {
                return this->node <=> rhs.node;
            }

            [[nodiscard]] constexpr auto operator<=>(std::nullptr_t) const noexcept { return this->node <=> nullptr; }

            [[nodiscard]] constexpr operator const_iterator() const noexcept {
                const_iterator cit;
                cit.node = this->node;
                return cit;
            }

        };

        /* -----------------------------------------------Node Type------------------------------------------------- */
        class node_type {
        private:
            /* ---------------------------------------------Fields-------------------------------------------------- */
            _Node* node;

            _NodeAllocator node_allocator;

            /* ---------------------------------------------Methods------------------------------------------------- */
            constexpr _Node* _create_node(typename singly_list::const_reference value) noexcept {
                _Node* node = node_allocator_traits::allocate(this->node_allocator, 1);
                node_allocator_traits::construct(this->node_allocator, node, value);
                return node;
            }

            constexpr _Node* _delete_node(_Node* node) noexcept {
                if (node == nullptr) {
                    return nullptr;
                }

                node_allocator_traits::destroy(this->node_allocator, node);
                node_allocator_traits::deallocate(this->node_allocator, node, 1);
                return nullptr;
            }

            /* ---------------------------------------------Friends------------------------------------------------- */
            friend class iterator;

        public:
            /* -------------------------------------------Definitions----------------------------------------------- */
            using allocator_type = _NodeAllocator;

            /* ------------------------------------------Constructors----------------------------------------------- */
            constexpr node_type() noexcept : node(nullptr) {}

            constexpr explicit node_type(std::nullptr_t) noexcept : node(nullptr) {};

            constexpr explicit node_type(const_iterator pos) noexcept {
                if (pos.node == nullptr) {
                    this->node = nullptr;
                    return;
                }
                this->node = this->_create_node(pos.node->value);
            }

            constexpr node_type(const node_type& other) noexcept {
                this->node_allocator = other.node_allocator;

                if (other.node == nullptr) {
                    this->node = nullptr;
                    return;
                }

                this->node = this->_create_node(other.node->value);
            }

            constexpr node_type(node_type&& other) noexcept {
                this->node_allocator = other.node_allocator;

                if (other.node == nullptr) {
                    this->node = nullptr;
                    return;
                }

                this->node = other.node;
                other.node = nullptr;
            }

            /* -------------------------------------------Destructor------------------------------------------------ */
            constexpr ~node_type() noexcept { this->node = this->_delete_node(this->node); }

            /* ---------------------------------------Overloaded Operators------------------------------------------ */
            constexpr node_type& operator=(const node_type& rhs) noexcept {
                this->node_allocator = rhs.node_allocator;

                // Protect against self-assignment
                if (this->node == rhs.node) {
                    return *this;
                }

                // Delete the current node pointed to by `*this`
                this->_delete_node(this->node);

                // If `rhs` is nullptr...
                this->node = (rhs.node == nullptr)
                    ? nullptr // Point the current node to nullptr
                    : this->_create_node(rhs.node->value); // Otherwise, copy over the node from `rhs`

                return *this;
            }

            constexpr node_type& operator=(node_type&& rhs) noexcept {
                this->node_allocator = rhs.node_allocator;

                // Delete the current node pointed to by `*this`
                this->_delete_node(this->node);

                this->node = rhs.node;
                rhs.node = nullptr;

                return *this;
            }

            constexpr node_type& operator=(std::nullptr_t) noexcept {
                this->node = this->_delete_node(this->node);
                return *this;
            }

            constexpr node_type& operator=(iterator pos) noexcept {
                if (pos.node == nullptr) {
                    this->node = nullptr;
                    return *this;
                }

                this->_delete_node(this->node);
                this->node = this->_create_node(pos.node->value);
                return *this;
            }

            [[nodiscard]] constexpr bool operator==(const node_type&) const noexcept = default;

            [[nodiscard]] constexpr bool operator==(std::nullptr_t) const noexcept { return this->node == nullptr; }

            [[nodiscard]] constexpr auto operator<=>(const node_type&) const noexcept = default;

            [[nodiscard]] constexpr auto operator<=>(std::nullptr_t) const noexcept {
                return this->node <=> nullptr;
            }

            /* ---------------------------------------------Methods------------------------------------------------- */
            [[nodiscard]] constexpr bool empty() const noexcept { return this->node == nullptr; }

            reference value() {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }
                return this->node->value;
            }

            [[nodiscard]] const_reference value() const {
                if (this->node == nullptr) {
                    throw std::runtime_error("segmentation fault");
                }
                return this->node->value;
            }

            [[nodiscard]] constexpr allocator_type get_allocator() const noexcept { return this->node_allocator; }

        };
    
    private:
        /* ------------------------------------------------Friends-------------------------------------------------- */
        friend class const_iterator;

        friend class iterator;

    public:
        /* ----------------------------------------------Constructors----------------------------------------------- */
        constexpr singly_list() noexcept : head(&dummy), sz(0) {}

        constexpr singly_list(std::initializer_list<value_type> values) noexcept : head(&dummy), sz(values.size()) {
            // For every value in `values`
            _Node* node = this->head;
            for (const_reference value : values) {
                // Create a node to store `value`
                node->next = this->_create_node(value);
                
                // Go to the next node
                node = node->next;
            }
        }

        constexpr singly_list(std::initializer_list<value_type> values, const allocator_type& allocator) noexcept
            : singly_list(values) { this->allocator = allocator; }

        explicit constexpr singly_list(size_type size) noexcept : head(&dummy), sz(size) {
            // Create `size` nodes
            _Node* node = this->head;
            for (size_type i = 0; i < size; i++) {
                node->next = this->_create_node(value_type());
                node = node->next;
            }
        }

        explicit constexpr singly_list(const allocator_type& allocator) noexcept 
            : head(&dummy), sz(0), allocator(allocator) {}

        constexpr singly_list(const singly_list& other) noexcept 
            : head(&dummy), allocator(other.allocator), sz(other.sz) {
            _Node* this_curr = this->head;
            _Node* other_curr = other.head;

            // For every node in `other`
            while (other_curr->next != nullptr) {
                // Copy the current node
                this_curr->next = this->_create_node(other_curr->next->value);
                    
                // Go to the next node
                other_curr = other_curr->next;
                this_curr = this_curr->next;
            }
        }

        constexpr singly_list(const singly_list& other, const allocator_type& allocator) noexcept 
            : singly_list(other) { this->allocator = allocator; }

        constexpr singly_list(singly_list&& other) noexcept
            : head(&dummy), allocator(other.allocator), sz(other.sz) {
            this->head->next = other.head->next;
            other.head->next = nullptr;
            
            other.sz = 0;
            other.allocator = allocator_type();
        }

        constexpr singly_list(singly_list&& other, const allocator_type& allocator) noexcept : singly_list(other) {
            this->allocator = allocator;
        }

        template<std::input_iterator InputIt>
        constexpr singly_list(InputIt first, InputIt last) noexcept : head(&dummy), sz(0) {
            // For each iterator
            _Node* node = this->head;
            for (InputIt it = first; it != last; it++) {
                // Create a new node to store the value at the current iterator
                node->next = this->_create_node(*it);
                
                // Update the size counter
                this->sz++;

                // Go to the next node
                node = node->next;
            }
        }

        template<std::input_iterator InputIt>
        constexpr singly_list(InputIt first, InputIt last, const allocator_type& allocator) noexcept 
            : singly_list(first, last) { this->allocator = allocator; }

        template<class R> 
        constexpr singly_list(std::from_range_t, R&& range, const allocator_type& allocator = allocator_type()) 
            noexcept requires (std::convertible_to<std::ranges::range_reference_t<R>, value_type> && 
                               std::ranges::input_range<R>) : head(&dummy), allocator(allocator), sz(0) {
            _Node* curr = this->head;
            for (auto value : range) {
                curr->next = this->_create_node(value);
                curr = curr->next;
                this->sz++;
            }
        }

        singly_list(size_type size, const_reference value) : head(&dummy) {
            if (size > 0) {
                this->sz = size;
                this->allocator = allocator;

                // Create `size` nodes all initialized to `value`
                _Node* node = this->head;
                for (size_type i = 0; i < size; i++) {
                    node->next = this->_create_node(value);
                    node = node->next;
                }

                return;
            }
            throw std::invalid_argument("\"size\" must exceed 0");
        }

        singly_list(size_type size, const_reference value, const allocator_type& allocator)
            : singly_list(size, value) { this->allocator = allocator; }

        /* -----------------------------------------------Destructor------------------------------------------------ */
        constexpr ~singly_list() noexcept {
            this->_clear();
            this->head->next = nullptr;
            this->sz = 0;
        }

        /* ------------------------------------------Overloaded Operators------------------------------------------- */
        constexpr singly_list& operator=(const singly_list& rhs) noexcept {
            // Protect against self-assignment
            if (this != &rhs) {
                // Free all nodes except the head
                this->_clear();

                // Copy the list from `rhs`
                _Node* lhs_curr = this->head,
                     * rhs_curr = rhs.head;
                
                while (rhs_curr->next != nullptr) {
                    lhs_curr->next = this->_create_node(rhs_curr->next->value);
                    
                    lhs_curr = lhs_curr->next;
                    rhs_curr = rhs_curr->next;
                }

                this->sz = rhs.sz;
                this->allocator = rhs.allocator;
            }
                
            return *this;
        }

        constexpr singly_list& operator=(singly_list&& rhs) noexcept {
            // Delete all nodes except the head
            this->_clear();

            // Move the nodes from `rhs` to `*this`
            this->head->next = rhs.head->next;
            rhs.head->next = nullptr;

            this->sz = rhs.sz;
            rhs.sz = 0;
                
            return *this;
        }

        [[nodiscard]] constexpr bool operator==(const singly_list& rhs) const noexcept {
            return std::equal(iterator(*this), iterator(nullptr), iterator(rhs), iterator(nullptr));
        }

        template<class R> 
        [[nodiscard]] constexpr bool operator==(R&& range) const noexcept 
            requires (std::convertible_to<std::ranges::range_reference_t<R>, value_type> && 
                      std::ranges::input_range<R> && !std::is_same_v<std::remove_cvref_t<R>, singly_list>) {
            _Node* prev = this->head;
            
            for (value_type value : range) {
                // Return false if the current node's value from the list doesn't equal `value` or
                // if the number of values in the list don't match the number of values in `R`
                if (prev->next == nullptr || prev->next->value != value) {
                    return false;
                }
                prev = prev->next;
            }
            return true;
        }

        [[nodiscard]] constexpr auto operator<=>(const singly_list& rhs) const noexcept
            requires(std::three_way_comparable<value_type>) {
            // Compare this BST's size with the other BST's size
            if (size_type cmp = this->sz <=> rhs.sz; cmp != 0) {
                return cmp;
            }

            // If comparing the sizes fails, then lexicographically compare this BST's elements
            // with the other BST's elements
            return std::lexicographical_compare_three_way(this->begin(), this->end(), rhs.begin(), rhs.end());
        }

        /* ------------------------------------------------Methods-------------------------------------------------- */
        [[nodiscard]] constexpr const_iterator cbefore_begin() const noexcept {
            return const_iterator(this, this->head);
        }

        [[nodiscard]] constexpr const_iterator cbegin() const noexcept { return const_iterator(*this); }

        [[nodiscard]] constexpr const_iterator cend() const noexcept { return const_iterator(this, nullptr); }

        [[nodiscard]] constexpr iterator before_begin() const noexcept { return iterator(this, this->head); }

        [[nodiscard]] constexpr iterator begin() const noexcept { return iterator(*this); }

        [[nodiscard]] constexpr iterator end() const noexcept { return iterator(this, nullptr); }

        constexpr void assign(size_type count, const_reference value) noexcept {
            _Node* curr = this->head;
            for (size_type i = 0; i < count; i++) {
                if (curr->next != nullptr) {
                    curr->next->value = value;
                } else {
                    curr->next = this->_create_node(value);
                    this->sz++;
                }
                curr = curr->next;
            }
        }

        template<std::input_iterator InputIt>
        constexpr void assign(InputIt first, InputIt last)  noexcept {
            _Node* prev = this->head;
            for (InputIt it = first; it != last; ++it) {
                // If there are more nodes in the list...
                if (prev->next != nullptr) {
                    // Overwrite the current node's value with `*it`
                    prev->next->value = *it;
                } else {
                    // Create a new node initialized with `*it`
                    prev->next = this->_create_node(*it);
                    this->sz++;
                }
                prev = prev->next;
            }
        }

        constexpr void assign(std::initializer_list<value_type> values) noexcept {
            _Node* curr = this->head;
            for (const_reference value : values) {
                if (curr->next != nullptr) {
                    curr->next->value = value;
                } else {
                    curr->next = this->_create_node(value);
                    this->sz++;
                }
                curr = curr->next;
            }
        }

        template<class R>
        constexpr void assign_range(R&& range) noexcept 
            requires (std::assignable_from<reference, std::ranges::range_reference_t<R>> &&
                      std::ranges::input_range<R>) {
            _Node* curr = this->head;
            for (auto value : range) {
                if (curr->next != nullptr) {
                    curr->next->value = value;
                } else {
                    curr->next = this->_create_node(value);
                    this->sz++;
                }

                curr = curr->next;
            }
        }

        [[nodiscard]] constexpr allocator_type get_allocator() const noexcept { return this->allocator; }

        [[nodiscard]] constexpr reference front() const {
            if (this->head->next != nullptr) {
                return this->head->next->value;
            }
            throw std::runtime_error("segmentation fault");
        }

        [[nodiscard]] constexpr reference back() const {
            for (_Node* node = this->head->next; node != nullptr; node = node->next) {
                if (node->next == nullptr) {
                    return node->value;
                }
            }
            throw std::runtime_error("segmentation fault");
        }

        [[nodiscard]] constexpr size_type size() const noexcept { return this->sz; }

        [[nodiscard]] constexpr size_type max_size() const noexcept {
            return std::numeric_limits<difference_type>::max();
        }

        [[nodiscard]] constexpr bool empty() const noexcept { return this->sz == 0; }

        constexpr void clear() noexcept {
            this->_clear();
            this->head->next = nullptr;
            this->sz = 0;
        }

        iterator insert_after(const_iterator pos, const_reference value)
            requires (std::is_copy_constructible_v<value_type>) {
            if (pos == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "insert_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            return iterator(this, this->_insert_after(const_cast<_Node*>(pos.node), value));
        }

        iterator insert_after(const_iterator pos, reference& value) 
            requires (std::is_move_constructible_v<value_type>) {
            if (pos == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "insert_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            return iterator(this, this->_insert_after(const_cast<_Node*>(pos.node), value));
        }

        iterator insert_after(const_iterator pos, size_type count, const_reference value)
            requires (std::is_copy_constructible_v<value_type>) {
            if (pos.node == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "insert_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            // Cast away the `const`ness of the node at `pos`
            _Node* pos_node = const_cast<_Node*>(pos.node);

            if (count == 0) {
                // Return an iterator starting at `pos`
                return iterator(this, pos_node);
            }

            for (size_type i = 0; i < count; i++) {
                this->_insert_after(pos_node, value);
            }

            // Return an instance of `iterator` starting one node after `pos`
            return iterator(this, pos_node->next);
        }

        template<std::input_iterator InputIt>
        iterator insert_after(const_iterator pos, InputIt first, InputIt last) {
            if (pos == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "insert_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            // Cast away the `const`ness of the node at `pos`
            _Node* pos_node = const_cast<_Node*>(pos.node);

            for (InputIt input_it = first; input_it != last; ++input_it) {
                this->_insert_after(pos_node, *input_it);
                pos_node = pos_node->next;
            }
            
            return iterator(this, pos_node);
        }

        iterator insert_after(const_iterator pos, std::initializer_list<value_type> values) {
            if (pos.node == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "insert_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            _Node* pos_node = const_cast<_Node*>(pos.node);
            for (const_reference value : values) {
                this->_insert_after(pos_node, value);
                pos_node = pos_node->next;
            }

            return iterator(this, pos_node);
        }

        template<class R>
        iterator insert_range_after(const_iterator pos, R&& range) 
            requires (std::convertible_to<std::ranges::range_reference_t<R>, value_type> && 
                      std::ranges::input_range<R>) {
            if (pos == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "insert_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }
            
            // Cast away the `const`ness of the node at `pos`
            _Node* pos_node = const_cast<_Node*>(pos.node);

            for (auto value : range) {
                this->_insert_after(pos_node, value);
                pos_node = pos_node->next;
            }

            return iterator(this, pos_node);
        }

        template<class... Args>
        iterator emplace_after(const_iterator pos, Args&&... args)
            requires (std::constructible_from<value_type, Args...>) {
            if (pos == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "emplace_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            _Node* pos_node = const_cast<_Node*>(pos.node);

            // Save a copy of the next node after `pos_node`
            _Node* next = pos_node->next;

            // Create a new node
            pos_node->next = this->_create_node(value_type(std::forward<Args>(args)...), next);
                
            // Update the size counter
            this->sz++;

            // Return an iterator to the node after `pos_node`
            return iterator(this, pos_node->next);
        }
    
        iterator erase_after(const_iterator pos) {
            if (pos == nullptr || pos + 1 == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "erase_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            return iterator(this, this->_erase_after(const_cast<_Node*>(pos.node)));
        }

        iterator erase_after(const_iterator first, const_iterator last) {
            if (first == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (first.parent != this) {
                throw std::invalid_argument(
                    "erase_after() error: \"first\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            if (last.parent != this) {
                throw std::invalid_argument(
                    "insert_after() error: \"last\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            // Cast away the `const`ness of `first.node` and `last.node`
            _Node* first_node = const_cast<_Node*>(first.node);
            _Node* last_node = const_cast<_Node*>(last.node);

            while (first_node->next != nullptr && first_node->next != last_node) {
                this->_erase_after(first_node);
            }

            return iterator(this, first_node->next);
        }

        void splice_after(const_iterator pos, singly_list& other) {
            // If `pos` does NOT point to a node...
            if (pos == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "splice_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            // If `*this` and `other` are the same instance...
            if (this == &other) {
                throw std::invalid_argument("splice_after() error: \"other\" and \"*this\" cannot be from the same instance");
            }

            // If the other list is empty...
            if (other.head->next == nullptr) {
                // Exit
                return;
            }

            this->_splice_after(const_cast<_Node*>(pos.node), other);
        }

        void splice_after(const_iterator pos, singly_list&& other) {
            // If `pos` does NOT point to a node
            if (pos == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "splice_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            // If `other` and `*this` are from the same instance
            if (this == &other) {
                throw std::invalid_argument("splice_after() error: \"other\" and \"*this\" cannot be from the same instance");
            }

            // If the other list is empty
            if (other.head->next == nullptr) {
                // Exit
                return;
            }

            this->_splice_after(const_cast<_Node*>(pos.node), other);
        }

        void splice_after(const_iterator pos, singly_list& other, const_iterator it) {
            if (pos == nullptr || it == nullptr || it + 1 == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "insert_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            // If the other list is empty...
            if (other.head->next == nullptr) {
                // Exit
                return;
            }

            this->_splice_after(const_cast<_Node*>(pos.node), other, const_cast<_Node*>(it.node));
        }

        void splice_after(const_iterator pos, singly_list&& other, const_iterator it) {
            if (pos == nullptr || it == nullptr || it + 1 == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "splice_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            // If the other list is empty...
            if (other.head->next == nullptr) {
                // Exit
                return;
            }

            this->_splice_after(const_cast<_Node*>(pos.node), other, const_cast<_Node*>(it.node));
        }

        void splice_after(const_iterator pos, singly_list& other, const_iterator first, const_iterator last) {
            if (pos == nullptr || first == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "splice_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            if (first.parent != last.parent) {
                throw std::invalid_argument(
                    "splice_after() error: \"first\" and \"last\" must be from the same adt::singly_list instance"
                );
            }

            if (other.head->next == nullptr) {
                return;
            }

            this->_splice_after(const_cast<_Node*>(pos.node), 
                                other,
                                const_cast<_Node*>(first.node),
                                const_cast<_Node*>(last.node));
        }

        void splice_after(const_iterator pos, singly_list&& other, const_iterator first, const_iterator last) {
            if (pos == nullptr || first == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "splice_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            if (first.parent != last.parent) {
                throw std::invalid_argument(
                    "splice_after() error: \"first\" and \"last\" must be from the same adt::singly_list instance"
                );
            }

            if (other.head->next == nullptr) {
                return;
            }

            this->_splice_after(const_cast<_Node*>(pos.node), 
                                other,
                                const_cast<_Node*>(first.node),
                                const_cast<_Node*>(last.node));
        }

        constexpr void push_back(const_reference value) noexcept
            requires(std::is_copy_constructible_v<value_type>) {
            // Get to the current tail of the list
            _Node* tail = this->head;
            while (tail->next != nullptr) {
                tail = tail->next;
            }

            // Create a new node and append it to the list
            tail->next = this->_create_node(value);
            
            // Update the size counter
            this->sz++;
        }

        constexpr void push_back(reference& value) noexcept
            requires(std::is_move_constructible_v<value_type>) {
            // Get to the current tail of the list
            _Node* tail = this->head;
            while (tail->next != nullptr) {
                tail = tail->next;
            }

            // Create a new node and append it to the list
            tail->next = this->_create_node(std::forward<value_type>(value));
            
            // Update the size counter
            this->sz++;
        }

        constexpr void push_front(const_reference value) noexcept
            requires(std::is_copy_constructible_v<value_type>) {
            _Node* new_front = this->_create_node(value, this->head->next);
            this->head->next = new_front;

            this->sz++;
        }

        constexpr void push_front(reference& value) noexcept
            requires(std::is_move_constructible_v<value_type>) {
            this->head->next = this->_create_node(std::forward<value_type>(value), this->head->next);
            this->sz++;
        }

        template<class... Args>
        constexpr reference emplace_back(Args&&... args) noexcept {
            // Get to the tail of the list
            _Node* tail = this->head;
            while (tail->next != nullptr) {
                tail = tail->next;
            }

            // Create a new node after the tail
            tail->next = this->_create_node(value_type(std::forward<Args>(args)...));
            
            // Update the size counter
            this->sz++;

            return tail->next->value;
        }

        template<class... Args>
        constexpr reference emplace_front(Args&&... args) noexcept {
            this->head->next = this->_create_node(value_type(std::forward<Args>(args)...), this->head->next);
            this->sz++;

            return this->head->next->value;
        }

        template<class R>
        constexpr void prepend_range(R&& range) noexcept
            requires (std::convertible_to<std::ranges::range_reference_t<R>, value_type> && 
                      std::ranges::input_range<R>) {
            _Node* node = this->head;
            for (auto value : range) {
                this->_insert_after(node, value);
                node = node->next;
            }
        }

        template<class R>
        requires (std::convertible_to<std::ranges::range_reference_t<R>, value_type> && std::ranges::input_range<R>)
        constexpr void append_range(R&& range) noexcept {
            // Get to the end of the list
            _Node* node = this->head;
            while (node->next != nullptr) {
                node = node->next;
            }
            
            for (auto value : range) {
                this->_insert_after(node, value);
                node = node->next;
            }
        }

        void pop_back() {
            // Check if the list is empty
            if (this->head->next != nullptr) {
                // Get to the node before the tail of the list
                _Node* node = this->head;
                while (node->next->next != nullptr) {
                    node = node->next;
                }

                // Delete the tail node
                node->next = this->_delete_node(node->next);
                
                // Update the size counter
                this->sz--;
            } else {
                throw std::runtime_error("cannot pop from an empty list");
            }
        }

        void pop_front() {
            // Check if the list is empty
            if (this->head->next != nullptr) {
                // Save a copy of the current front node
                _Node* node = this->head->next;

                // Overwrite the front node with the node after it
                this->head->next = this->head->next->next;

                // Delete the copy of the old front node
                this->_delete_node(node);
                
                // Update the size counter
                this->sz--;
            } else {
                throw std::runtime_error("cannot pop from an empty list");
            }
        }

        constexpr void resize(size_type new_size) { this->_resize(new_size, value_type()); }

        constexpr void resize(size_type new_size, const_reference value) { this->_resize(new_size, value); }
        
        constexpr size_type remove(const_reference value) noexcept {
            // Return 0 if the list is empty
            if (this->head->next == nullptr) {
                return 0;
            }
            
            size_type vals_removed = 0;
            _Node* prev = this->head,
                 * next;
            
            // While the end of the list has NOT been reached...
            while (prev != nullptr && prev->next != nullptr) {
                // If the current node's value equals `value`...
                if (prev->next->value == value) {
                    // Remove the node from the list
                    next = prev->next->next;
                    this->_delete_node(prev->next);
                    prev->next = next;

                    // Update the list size and the number of values removed
                    this->sz--;
                    vals_removed++;

                    // Proceed to the next iteration
                    continue;
                }

                // Advance to the next node
                prev = prev->next;
            }

            return vals_removed;
        }

        template<class Predicate>
        constexpr size_type remove_if(Predicate pred) noexcept 
            requires (std::predicate<Predicate, value_type>) {
            // Return 0 if the list is empty
            if (this->head->next == nullptr) {
                return 0;
            }

            size_type vals_removed = 0;
            _Node* prev = this->head,
                 * next;

            // While the end of the list has NOT been reached...
            while (prev != nullptr && prev->next != nullptr) {
                // If the predicate `pred` returns true for the current node's value...
                if (pred(prev->next->value)) {
                    // Remove the current node
                    next = prev->next->next;
                    this->_delete_node(prev->next);
                    prev->next = next;

                    // Update the list size and the number of values removed
                    this->sz--;
                    vals_removed++;

                    // Proceed to the next iteration
                    continue;
                }

                // Advance to the next node
                prev = prev->next;
            }

            return vals_removed;
        }

        constexpr void swap(singly_list& other) noexcept {
            _Node* temp = this->head->next;
            this->head->next = other.head->next;
            other.head->next = temp;
        }

        constexpr void reverse() noexcept {
            _Node* prev = nullptr,
                 * curr = this->head->next,
                 * next;
            
            while (curr != nullptr) {
                // Save a copy of the next node
                next = curr->next;

                // Reverse the current node
                curr->next = prev;

                // Go to the next node
                prev = curr;
                curr = next;
            }

            // Point the old front to the new front
            this->head->next = prev;
        }

        constexpr size_type unique() noexcept {
            // Check if the list contains more than 1 node
            if (this->head->next != nullptr && this->head->next->next != nullptr) {
                std::unordered_set<value_type> seen;
                size_type dups_removed = 0;
                _Node* node = this->head,
                     * dup;

                do {
                    if (seen.find(node->next->value) != seen.end()) {
                        // Save a copy of the duplicate
                        dup = node->next;

                        // Skip past the duplicate
                        node->next = node->next->next;

                        // Delete the duplicate copy
                        this->_delete_node(dup);
                        
                        // Update the size counter
                        this->sz--;

                        // Update the number of duplicates removed
                        dups_removed++;
                    } else {
                        // Add the element to the seen set
                        seen.insert(node->next->value);

                        // Go to the next node
                        node = node->next;
                    }
                } while (node->next != nullptr);

                return dups_removed;
            }
            
            // 0 duplicates removed
            return 0;
        }

        constexpr void sort() noexcept { this->head->next = _merge_sort(this->head->next, std::less<value_type>{}); }

        template<class Compare>
        constexpr void sort(Compare comp) noexcept { this->head->next = _merge_sort(this->head->next, comp); }

        [[nodiscard]] constexpr bool is_sorted() const noexcept { return this->_is_sorted(std::less<value_type>{}); }

        template<class Compare>
        [[nodiscard]] constexpr bool is_sorted(Compare comp) const noexcept { return this->_is_sorted(comp); }

        node_type extract_after(const_iterator pos) {
            if (pos == nullptr) {
                throw std::runtime_error("segmentation fault");
            }

            if (pos.parent != this) {
                throw std::invalid_argument(
                    "extract_after() error: \"pos\" must belong to the same instance of adt::singly_list as *this"
                );
            }

            // Create a node handle to hold the value after `pos`
            node_type node_handle(pos + 1);

            // If the node handle is empty (i.e the node points to nullptr)...
            if (node_handle.empty()) {
                // Return the empty node handle
                return node_handle;
            }

            // Get the node at `pos`
            _Node* pos_node = const_cast<_Node*>(pos.node);

            // Unlink the node after `pos` from the list
            _Node* temp = pos_node->next->next;
            this->_delete_node(pos_node->next);
            pos_node->next = temp;
            this->sz--;

            return node_handle;
        } 

    };

} // adt

namespace std {
    
    template<class T, class Allocator>
    constexpr void swap(adt::singly_list<T, Allocator>& lhs, adt::singly_list<T, Allocator>& rhs) noexcept {
        // Do nothing if both lists are empty
        if (lhs.empty() && rhs.empty()) {
            return;
        }

        return lhs.swap(rhs);
    }

    template<class T, class Allocator, class U = T>
    constexpr typename adt::singly_list<T, Allocator>::size_type erase(adt::singly_list<T, Allocator>& list, const U& value) noexcept {
        return list.remove_if([&](const auto& elem) -> bool { return elem == value; });
    }

    template<class T, class Allocator, class Predicate>
    constexpr typename adt::singly_list<T, Allocator>::size_type erase_if(adt::singly_list<T, Allocator>& list, Predicate pred) noexcept 
        requires (std::predicate<Predicate, T>) { return list.remove_if(pred); }

} // std


#endif // SINGLY_LIST_HPP
