#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H

template <typename Data> class List{
public:
    class Item{
    public:
        Item(Data data, Item* prev = nullptr, Item* next = nullptr) {   
            data_ = data;
            prev_ = prev;
            next_ = next;
        }

        Item* next(){ 
            return next_; 
        }
        Item* prev(){ 
            return prev_;
        }
        Data data() const{ 
            return data_; 
        }

        void setPrev(Item* prev) {
            prev_ = prev;
        }
        void setNext(Item* next) {
            next_ = next;
        }
    private:
        Data data_;
        Item* prev_;
        Item* next_;
    };

    // Creates new list
    List()
    {
        head_ = nullptr;
        tail_ = nullptr;    
    }

    // copy constructor
    List(const List &a)
    {
        head_ = nullptr;
        tail_ = nullptr;
        Item* temp = a.head_;
        while (temp) {
            insert(temp->data());
            temp = temp->next();
        }
    }

    // assignment operator
    List &operator=(const List &a)
    {
        if (this != &a) {
            while (head_) {
                Item* temp = head_;
                head_ = head_->next();
                delete temp;
            }
            Item* lastInserted = nullptr;
            Item* current = a.head_;
            while (current)
            {
                if (lastInserted == nullptr)
                {
                    lastInserted = insert(current->data());
                }
                else
                {
                    lastInserted = insert_after(lastInserted, current->data());
                }
                current = current->next();
            }

        }
        return *this;
    }
    
    // Destroys the list and frees the memory
    ~List() 
    {
        while (head_) {
            Item* deleted = head_;
            head_ = head_->next();
            delete deleted;
        }
    }

    // Retrieves the first item from the list
    Item* first()
    {
        return head_;
    }

    // Inserts new list item into the beginning
    Item* insert(Data data)
    {
        Item* newNode = new Item(data, nullptr, head_);
        if (head_) {
            head_->setPrev(newNode);
        }
        else {
            tail_ = newNode;
        }
        head_ = newNode;
        return newNode;
    }

    // Inserts new list item after the specified item
    Item* insert_after(Item* item, Data data)
    {
        if (!item) {
            return insert(data);
        }
        else {
            Item* newNode = new Item(data, item, item->next());
            if (item->next()) {
                item->next()->setPrev(newNode);
            }
            else {
                tail_ = newNode;
            }
            item->setNext(newNode);
            return newNode;
        }
    }

    // Deletes the first list item.
    // Returns pointer to the item next to the deleted one.
    Item* erase_first()
    {
        if (head_) {
            Item* deleted = head_;
            head_ = head_->next();
            delete deleted;
            if (head_) {
                head_->setPrev(nullptr);
            }
            else {
                tail_ = nullptr;
            }
        }
        return head_;
    }

    // Deletes the list item following the specified one.
    // Returns pointer to the item next to the deleted one.
    // Should be O(1)
    Item* erase_next(Item* item)
    {
        if (item && item->next()) {
            Item* deleted = item->next();
            item->setNext(deleted->next());
            delete deleted;
            if (item->next()) {
                item->next()->setPrev(item);
            }
            else {
                tail_ = item;
            }
        }
        return item->next();
    }

    Item* last() 
    {
        return tail_;
    }

    Item* operator[](size_t index) const 
    {
        Item* current = head_;
        size_t i = 0;

        while (current && i < index) {
            current = current->next();
            ++i;
        }

        return current;
    }

private:
    Item* head_;
    Item* tail_;
};

#endif
