#ifndef SPLIT_HPP
#define SPLIT_HPP

#include "sequence.hpp"
#include <iostream>
#include <string>
//Function #1 - creates two sequences by splitting the existing one 
//(moves elements from the source collection seq 
// to the target collections: seq1, seq2 
// the starting element in the source sequence is specified by a position number index 
template <typename Key, typename Info> 
void split_pos(Sequence <Key, Info>& seq, int startPos, int len1, int len2, int count, 
    Sequence <Key, Info>& seq1, Sequence <Key, Info>& seq2)
{
   if(startPos <0 || len1 <0 || len2 < 0 || count <= 0)
    return;

    if(seq.getSize() == 0)
        return;

    seq1.clear();
    seq2.clear();

    Sequence<Key, Info> temp(seq);
    const void* cur = temp.rawHead();
    int index = 0;

    while (cur && index < startPos) {
        cur = temp.rawNext(cur);
        index++;
    }

    int rounds = 0;
    while (cur && rounds < count)
    {

        for (int i = 0; i < len1 && cur; ++i) {
            seq1.pushEnd(temp.rawKey(cur), temp.rawInfo(cur));
            cur = temp.rawNext(cur);
        }

        for (int i = 0; i < len2 && cur; ++i) {
            seq2.pushEnd(temp.rawKey(cur), temp.rawInfo(cur));
            cur = temp.rawNext(cur);
        }
        rounds++;
    }

    Sequence<Key, Info> remainder;
    Sequence<Key, Info> copy(seq);

    const void* it = copy.rawHead();
    int pos = 0;
    int taken = count * (len1 + len2);

    while (it && pos < startPos)
    {
        remainder.pushEnd(copy.rawKey(it), copy.rawInfo(it));
        it = copy.rawNext(it);
        pos++;
    }
    for (int i = 0; i < taken && it; i++) {
        it = copy.rawNext(it);
    }

 
    while (it)
    {
        remainder.pushEnd(copy.rawKey(it), copy.rawInfo(it));
        it = copy.rawNext(it);
    }

    seq.swap(remainder);
}
// Function #2 - creates two sequences by splitting the existing one 
//(moves elements from the source collection seq 
// to the target collections: seq1, seq2 
// the starting element in the source sequence is specified by a Key value  
// and occurrence number 
template <typename Key, typename Info>
void split_key(Sequence<Key, Info>& seq,
               const Key& startKey,
               int startOcc,
               int len1,
               int len2,
               int count,
               Sequence<Key, Info>& seq1,
               Sequence<Key, Info>& seq2)
{
    if (len1 <= 0 || len2 <= 0 || startOcc <= 0 || count <= 0)
        return;
    if (seq.getSize() == 0)
        return;

    seq1.clear();
    seq2.clear();

    Sequence<Key, Info> temp(seq);

    const void* cur = temp.rawHead();
    int occ = 0;
    int pos = 0;


    while (cur) {
        if (temp.rawKey(cur) == startKey) {
            occ++;
            if (occ == startOcc)
                break;
        }
        cur = temp.rawNext(cur);
        pos++;
    }

    if (!cur)
        return;

    int rounds = 0;

    while (cur && rounds < count)
    {
        
        for (int i = 0; i < len1 && cur; ++i) {
            seq1.pushEnd(temp.rawKey(cur), temp.rawInfo(cur));
            cur = temp.rawNext(cur);
        }

        for (int i = 0; i < len2 && cur; ++i) {
            seq2.pushEnd(temp.rawKey(cur), temp.rawInfo(cur));
            cur = temp.rawNext(cur);
        }

        rounds++;
    }

    Sequence<Key, Info> remainder;
    Sequence<Key, Info> original(seq);

    const void* it = original.rawHead();

    for (int i = 0; i < pos; i++)
    {
        remainder.pushEnd(original.rawKey(it), original.rawInfo(it));
        it = original.rawNext(it);
    }

    int skip = count * (len1 + len2);
    for (int i = 0; i < skip && it; i++)
        it = original.rawNext(it);

    while (it)
    {
        remainder.pushEnd(original.rawKey(it), original.rawInfo(it));
        it = original.rawNext(it);
    }

    seq.swap(remainder);
}
// Function #3 (Challenge) - exchange every second element mutually
// REWRITTEN to use ONLY public member functions (popFront, pushEnd, getFront)
template <typename Key, typename Info>
void exchange(Sequence <Key, Info>& seq1, Sequence <Key, Info>& seq2)
{
    // 1. Create two temporary sequences by copying the originals.
    Sequence<Key, Info> temp1 = seq1;
    Sequence<Key, Info> temp2 = seq2;
    
    // 2. Clear the originals to rebuild them with exchanged elements.
    seq1.clear();
    seq2.clear();

    // Key/Info buffers for transferring data
    Key k1, k2;
    Info i1, i2;
    
    // Determine the number of pairs to process, limited by the smaller list's size.
    int minSize = std::min(temp1.getSize(), temp2.getSize());
    
    // We iterate up to half the size of the shorter list, processing two elements at a time.
    for (int i = 0; i < minSize / 2; ++i)
    {
        // --- Pair 1: Index 2i (Elements to be KEPT in original sequence) ---
        
        // 1A. Get and pop front from temp1 (Node A)
        if (temp1.getFront(k1, i1)) {
            temp1.popFront();
            seq1.pushEnd(k1, i1); // Node A goes back to seq1
        }
        // 1B. Get and pop front from temp2 (Node C)
        if (temp2.getFront(k2, i2)) {
            temp2.popFront();
            seq2.pushEnd(k2, i2); // Node C goes back to seq2
        }

        // --- Pair 2: Index 2i + 1 (Elements to be EXCHANGED) ---
        
        // 2A. Get and pop front from temp1 (Node B)
        if (temp1.getFront(k1, i1)) {
            temp1.popFront();
            seq2.pushEnd(k1, i1); // Node B (from temp1) goes to seq2
        }
        // 2B. Get and pop front from temp2 (Node D)
        if (temp2.getFront(k2, i2)) {
            temp2.popFront();
            seq1.pushEnd(k2, i2); // Node D (from temp2) goes to seq1
        }
    }

    // 3. Append any remaining elements from the temporary sequences.
    
    // Append remaining elements from temp1 (if s1 was longer)
    while (temp1.getFront(k1, i1)) {
        temp1.popFront();
        seq1.pushEnd(k1, i1);
    }
    
    // Append remaining elements from temp2 (if s2 was longer)
    while (temp2.getFront(k2, i2)) {
        temp2.popFront();
        seq2.pushEnd(k2, i2);
    }
}
/*std::string to_string_helper(int val)
 {
    std::stringstream ss;
    ss << val;
    return ss.str();
 }
 // NEW PUBLIC ACCESSOR: Retrieves Key and Info of the head node
template<typename Key, typename Info>
bool Sequence<Key,Info>::getFront(Key& key, Info& info)
{
    if (!head)
        return false; // List is empty
    key = head->key;
    info = head->info;
    return true; // Successfully retrieved data
} */
#endif