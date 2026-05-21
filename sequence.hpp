#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <iostream>
#include <string>
template<typename Key, typename Info> class Sequence;

//---------------------------------------------------------------------------------------------------------------
template<typename Key, typename Info>
class Sequence{
    //private so user can't accidentally harm the data
    struct Node{
        Key key;
        Info info;
        Node* next;
    };
    Node* head;
public:
    Sequence() : head(nullptr) {}
    ~Sequence();
    Sequence(const Sequence& other);

    void pushFront(const Key& key, const Info& info);
    void pushEnd(const Key&, const Info&);
    bool insertAfter(Key newkey, Info info, const Key& key, int instance =1);
    bool popFront();
    bool popEnd();
    bool remove(const Key&, int instance = 1);
    int removeAll(const Key&);

    bool contains(const Key&) const;
    bool getInfo(Info& result, const Key&,int instance=1);
    unsigned int getSize();
    void clear();

    bool operator==(const Sequence<Key,Info>& sc) const;
    bool operator!=(const Sequence<Key,Info>& sc) const;
    Sequence<Key,Info>& operator=(const Sequence& other);
    Sequence<Key,Info> operator+(const Sequence<Key,Info>& other) const;

    void print();
    void swap(Sequence<Key,Info>& sc);
    void sort();
    void reverse();
    Sequence<Key,Info> subsequence(const Key& startKey, const Key& endKey, int startOccurrence =1, int endOccurrence=1);
    Sequence<Key,Info> subsequenceFrom(const Key& startKey, int startOccurrence =1);
    Sequence<Key,Info> subsequenceTo(const Key& endKey,int endOccurrence=1);

    template<typename K, typename I>
    friend std::ostream& operator<< (std::ostream&, const Sequence<K, I>&);

    //friend void split_pos<Key, Info>(Sequence<Key,Info>& seq, int start_pos, int len1, int len2, int count, 
    //Sequence<Key,Info>& seq1, Sequence<Key,Info>& seq2);
    
    //friend void split_key<Key, Info>(Sequence <Key, Info>& seq, const Key& start_key, int start_occ, int len1, int len2, int count, 
    //Sequence <Key, Info>& seq1, Sequence <Key, Info>& seq2);

    //Helper functions
     bool getFront(Key& k, Info& i) const
     {
        if (!head) return false;
        k = head->key;
        i = head->info;
        return true;
    }

    const void* rawHead() const
    {
        return head;
    }

    const void* rawNext(const void* node) const
    {
        return static_cast<const Node*>(node)->next;
    }
     const Key& rawKey(const void* node) const
     {
        return static_cast<const Node*>(node)->key;
    }
    
    const Info& rawInfo(const void* node) const
    {
        return static_cast<const Node*>(node)->info;
    }
    private:
    Node* mergeSort(Node* node);
    Node* merge(Node* node1, Node* node2);
    Node* getMiddle(Node* node);
};

//Destructor-----------------------------------------------------------------------------------
template<typename Key, typename Info>
Sequence<Key,Info>::~Sequence(){
    clear();
}
//Copy Constructor-----------------------------------------------------------------------------
template<typename Key, typename Info>
Sequence<Key,Info>::Sequence(const Sequence& other): head(nullptr)
{ 
    if(!other.head)
        return;
    
    head = new Node{other.head->key,other.head->info,nullptr};

    Node* current = head;
    Node* otherCurrent = other.head->next;

    while(otherCurrent)
    {
        current->next= new Node{otherCurrent->key, otherCurrent->info,nullptr};
        current = current->next;
        otherCurrent=otherCurrent->next;
    }
}
//Adds elements at the beginning of the list--------------------------------------------------
template<typename Key, typename Info>
void Sequence<Key,Info>::pushFront(const Key& key, const Info& info)
{
    Node* newNode = new Node{key, info, head};
    head = newNode;
}
//Adds elements at at the end of the list----------------------------------------------------
template<typename Key, typename Info>
void Sequence<Key,Info>::pushEnd(const Key& key, const Info& info)
{
    if(head == nullptr)
    {
        head = new Node{key, info, nullptr};
        return;
    }
    
    Node* current = head;
    while(current->next!= nullptr)
    {
        current = current->next;
    }
    current->next = new Node{key,info,nullptr};
}
//Inserts element after specified node-----------------------------------------------------
template<typename Key, typename Info>
bool Sequence<Key,Info>::insertAfter(Key newkey, Info info, const Key& key, int instance) // instance declared only once in header
{
    if (!head) 
        return false;

    Node* current = head;
    int occurence = 0;

    while(current != nullptr)
    {
        if(current->key == key)
        {
            occurence++;
            if(occurence == instance)
            {
                Node* nextNode = current->next;
                current->next = new Node{newkey, info, nextNode};
                return true;
            }
        }
        current = current->next;
    }
    return false;
}
//Remove first element----------------------------------------------------------
template<typename Key, typename Info>
bool Sequence<Key,Info>::popFront()
{
    if(head == nullptr)
        return false; //Since there is no element to be popped
    //We need to delete the first node from memory
    Node* temp = head;
    head = head->next;
    delete temp;

    return true;
}
//Remove last element----------------------------------------------------------
template<typename Key, typename Info>
bool Sequence<Key,Info>::popEnd()
{
    if(head == nullptr)
        return false;
    
    if (head->next == nullptr)
    {
        //Only one element in the list
        delete head;
        head = nullptr;
        return true;
    }
    //When there are more elements in the list
    Node* current = head;
    while(current->next->next !=nullptr)
    {
        current=current->next;
    }
    delete current->next;
    current->next = nullptr;
    return true;  
}
//Remove given occurence 
template<typename Key, typename Info>
bool Sequence<Key,Info>::remove(const Key& key, int instance)
{
    if (head == nullptr || instance <= 0) //Added check for instance <= 0
        return false;

    int occurence = 0;
    Node* current = head;
    Node* prev = nullptr; //Pointer to the node *before* current

    while (current) {
        if (current->key == key) {
            occurence++;
            if (occurence == instance) {
                // Found the node to delete
                if (prev == nullptr) {
                    // Deleting the head
                    head = current->next;
                } else {
                    // Deleting a middle/end node
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
        }
        // Move pointers forward (even if the key matched but not the instance)
        prev = current;
        current = current->next;
    }

    return false; // Key/instance not found
}
//Delete all nodes, that are matching the key-------------------------------------
//Returns how many elements were removed
template<typename Key, typename Info>
int Sequence<Key,Info>::removeAll(const Key& key)
{
    int count = 0;
    if(head && head->key ==key)
    {
        Node* temp = head;
        head= head->next;
        delete temp;
        count++;
    }

    Node* current = head;
    while(current && current->next)
    {
        if(current->next->key == key)
        {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            count++;
        }
        else
        {
            current = current->next;
        }
    }
    return count;
}
//Search for given key in list----------------------------------------------
template<typename Key, typename Info>
bool Sequence<Key,Info>::contains(const Key& key) const
{
    if(!head)
        return false;
    //using current for traversing
    Node* current = head;
    while(current != nullptr)
    {
        if(current->key == key)
            return true;
        current = current->next;
    }
    return false;
}
//Looks for node with given key and instance in the list, and returns info in result---------------------
//Returns true if key was found of given instance ,result contains info
//False otherwise
template<typename Key, typename Info>
bool Sequence<Key,Info>::getInfo(Info& result, const Key& key,int instance)
{
    int occurence =0;
    if(!head)
        return false;
    
    Node* current = head;
    while(current != nullptr)
    {
        if(current->key == key)
        {
            occurence++;
            if(occurence == instance)
            {
                result = current->info;
                return true;
            }
        }
        current = current->next;
    }
    return false;
}
//Gets size of Sequence, returns number------------------------------------------------------------------
template<typename Key, typename Info>
unsigned int Sequence<Key,Info>::getSize()
{
    int size =0;
    Node* current = head;

    while(current != nullptr)
    {
        size++;
        current = current->next;
    }
    return size;
}
//Clears list-------------------------------------------------------------------------------------------
template<typename Key, typename Info>
void Sequence<Key,Info>::clear()
{
    Node* current =head;
    while(current != nullptr)
    {
        Node* temp = current->next;
        delete current;
        current = temp;
    }
    head = nullptr;
}
//Compares Sequences for equality--------------------------------------------------------------
template<typename Key, typename Info>
bool Sequence<Key,Info>::operator==(const Sequence<Key,Info>& sc) const
{
    Node* seq1 = head;
    Node* seq2 = sc.head;
    while (seq1 != nullptr && seq2 != nullptr)
    {
        if (seq1->key != seq2->key || seq1->info != seq2->info)
            return false;
        seq1 = seq1->next;
        seq2 = seq2->next;
    }
    return seq1 == nullptr && seq2 == nullptr;
    //if traversing will come to the end of both lists, then tehse are the same;
}
//Compares Sequences for not equality-------------------------------------------------------------
template<typename Key, typename Info>
bool Sequence<Key, Info>::operator!=(const Sequence<Key, Info>& sc) const
{
    return !(*this == sc); // using here operator == so we dont need to repeat the logic
}
//Assigns one Sequence to the other--------------------------------------------------------------
template<typename Key, typename Info>
Sequence<Key,Info>& Sequence<Key, Info>::operator=(const Sequence& other)
{
   if(this == &other)
    return *this;

    clear(); // from sq1 so we can add nodes from seq2

    if(!other.head)
        return *this; // both seq are empty
    
    head = new Node{other.head->key, other.head->info, nullptr};
    //                                                   ^--- nullptr at beginning since seq1 and seq2 are independent
    Node* current = head;
    Node* otherCurrent = other.head->next; //next since we copied (made) the fist node

    while(otherCurrent)
    {
        current->next = new Node{otherCurrent->key, otherCurrent->info, nullptr};
        current=current->next;
        otherCurrent = otherCurrent->next;
    }
    return *this;
}
//Adds Sequences--------------------------------------------------------------------------------
template<typename Key, typename Info>
Sequence<Key,Info> Sequence<Key, Info>::operator+(const Sequence<Key,Info>& other) const
{
    Sequence<Key,Info> result(*this);//using copy constructor

    Node* current = other.head;
    while(current != nullptr)
    {
        result.pushEnd(current->key, current->info);
        current = current->next;
    }
    return result;
}
//Reverses whole sequence (all nodes)----------------------------------------------
template<typename Key, typename Info>
void Sequence<Key, Info>::reverse()
{
    Node* prev =nullptr;
    Node* current = head;
    Node* next = nullptr;

    while(current != nullptr)
    {
        next =current->next;
        current->next =prev;
        prev=current;
        current=next;
    }
    head =prev;
}
//Makes subsequence from one key to another key--------------------------------------------
template<typename Key, typename Info>
Sequence<Key,Info> Sequence<Key, Info>::subsequence(const Key& startKey, const Key& endKey, int startOccurrence, int endOccurrence)
{  
    Sequence<Key,Info> result;
    if(!contains(startKey) || !contains(endKey))
        return result; //returning empty list
    
    Node* current =head;
    int startCount = 0;
    int endCount = 0;

    while (current)
    {
        if (current->key == startKey)
        {
            ++startCount;
            if (startCount == startOccurrence)
                break;
        }
        current = current->next;
    }
    
    if(!current)
        return result;
    
    while(current)
    {
        result.pushEnd(current->key,current->info);
        if(current->key == endKey)
        {
             ++endCount;
            if (endCount == endOccurrence)
                break;
        }
        current = current->next;
    }
    return result;
}
//Makes subsequence from given key----------------------------------------------------------
template<typename Key, typename Info>
Sequence<Key,Info> Sequence<Key, Info>::subsequenceFrom(const Key& startKey, int startOccurrence)
{
    Sequence<Key,Info> result;

    if (!head || startOccurrence <= 0)
        return result;

    Node* current = head;
    int occurenceCount =0;
    while (current)
    {
       if(current->key == startKey)
         {   occurenceCount++;
            if(occurenceCount == startOccurrence)
                break;
         }
        current = current->next;
    }

    if (!current)
        return result;

    while (current)
    {
        result.pushEnd(current->key, current->info);
        current = current->next;
    }
    return result;
}
//Makes subsequence to given key------------------------------------------------
template<typename Key, typename Info>
Sequence<Key,Info> Sequence<Key, Info>::subsequenceTo(const Key& endKey,int endOccurrence)
{
     Sequence<Key,Info> result;

     if (!head || endOccurrence <= 0)
        return result;

     Node* current = head;
     int countEnd =0;
    
     while(current)
     {
        result.pushEnd(current->key, current->info);
        if(current->key == endKey)
        {
           countEnd++;
           if(countEnd == endOccurrence) 
                break;
        }
        current = current->next;
     }
     return result;
}
//Displays the Sequence-----------------------------------------------------------
template<typename Key, typename Info>
void Sequence<Key, Info>::print()
{
    Node* current =head;
    std::cout << "[";
    while(current)
    {
        std::cout << "(" << current->key << ", " << current->info << ")";

        if (current->next)
            std::cout << " -> ";
        current = current->next;
    }
    std::cout << "]" << std::endl;
}
//Displays the Sequence by stream--------------------------------------------------------------
template<typename Key, typename Info>
std::ostream& operator<<(std::ostream& os, const Sequence<Key, Info>& seq)
{
    using Node = typename Sequence<Key, Info>::Node;
    Node* current = seq.head;

    os<<"[";
    while(current)
    {
        os<<"("<<current->key<<", "<<current->info<<")";
        if(current->next)
            os<<" ->";
        current=current->next;
    }
    os<<"]";
    return os;
}
//Helper function for sort(), splits Sequence into two-----------------------------------------
template<typename Key, typename Info>
typename Sequence<Key, Info>::Node* Sequence<Key, Info>::getMiddle(Node* node)
{
    if(node == nullptr)
        return node;
    Node* slow = node;
    Node* fast = node->next;

    while (fast != nullptr)
    {
        fast = fast->next;
        if (fast != nullptr)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    return slow;
}
//Helper function for sort(), merges two sorted linked lists recursively--------------------------
template<typename Key, typename Info>
typename Sequence<Key, Info>::Node* Sequence<Key, Info>::merge(Node* node1, Node* node2)
{
    Node* result = nullptr;

    if (node1 == nullptr)
        return node2;
    if (node2 == nullptr)
        return node1;

    //Compare keys and recurse
    if (node1->key <= node2->key)
    {
        result = node1;
        result->next = merge(node1->next, node2);
    }
    else
    {
        result = node2;
        result->next = merge(node1, node2->next);
    }
    return result;
}
//Splits the sequences until one node is obtained (divider)----------------------------------------
template<typename Key, typename Info>
typename Sequence<Key, Info>::Node* Sequence<Key, Info>::mergeSort(Node* node)
{
    if (node == nullptr || node->next == nullptr)
        return node;

    //Find the middle of the list
    Node* middleNode = getMiddle(node);
    Node* nextOfMiddle = middleNode->next;

    //Break list into two halves
    middleNode->next = nullptr;

    //Recursively sort the two halves
    Node* left = mergeSort(node);
    Node* right = mergeSort(nextOfMiddle);

    // Merge the sorted halves
    Node* sortedList = merge(left, right);
    return sortedList;
}
//Sorts sequences from the lowest to the highest key----------------------------------------------
template<typename Key, typename Info>
void Sequence<Key, Info>::sort()
{
    if (!head || !head->next)
        return;
    head = mergeSort(head);
}
//Swaps Sequences--------------------------------------------------------------------------
template<typename Key, typename Info>
void Sequence<Key, Info>::swap(Sequence<Key,Info>& sc)
{
    std::swap(head, sc.head);
}
#endif