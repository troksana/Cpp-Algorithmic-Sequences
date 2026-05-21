#include "sequence.hpp"
#include "split.hpp"
#include <iostream>
#include <string>


int main(){

    std::cout << "---------------------TEST---------------------\n\n";
    //Empty lists
    Sequence<int,std::string> seq;
    Sequence<int, std::string> seq2;

    std::cout<<"Testing pushFront()------------------------------\n";
    seq.pushFront(4, "Cat");
    seq.pushFront(2, "Hamster");

    std::cout<<"Printing 2 nodes after inserting them by pushFront():\n";
    seq.print();

    std::cout<<"Testing pushEnd()---------------------\n";
    seq.pushEnd(11, "Goldfish");
    seq.pushEnd(8, "Ferret");
    seq.pushEnd(92, "Chinchilla");

    std::cout<<"Printing 4 nodes after inserting 2 nodes by pushEnd():\n";
    seq.print();

    std::cout<<"Testing insertAfter & popFront & popEnd-----------------------------\n";
    seq.insertAfter(8,"Capybara",4);
    if(seq.popEnd())
    {
        std::cout<<"Successfuly deleted last node\n";
    }
    else
        std::cout<<"Error: popEnd()\n";

    if(seq.popFront())
    {
        std::cout<<"Successfuly deleted first node\n";
    }
    else
        std::cout<<"Error!: popFront()\n";

    std::cout<<"Printing 4 nodes and  Capybara added after cat by insertAfter()\n";
    seq.print();
    std::cout<<"Testing remove------------------------------\n";
    seq.remove(8,2);
    std::cout<<"Should print 3 nodes without 2st instance of node with key 8 (Capybara should disappear)\n";
    seq.print();

    seq.pushEnd(3, "Parrot");
    seq.pushEnd(6, "Penguin");
    seq.pushEnd(3, "Coala");

    std::cout<<"Testing removeAll----------------------\n";
    int numberOfRemovedElements= seq.removeAll(3);
    std::cout<<"All elements with key 3 should disappear:\n";
    seq.print();
    std::cout<<"Number of removed elements:\t"<<numberOfRemovedElements;

    std::cout<<"Testing contains-----------------------\n";
    if(!seq.contains(44))
    {
        std::cout<<"Should fail test, no such element with key 44:\t";
        std::cout<<seq.contains(44);
    }
    else
        std::cout<<"\nError: contains doesn't work properly\n";

    std::string result;
    if(seq.getInfo(result,6,1))
    {
        std::cout<<"\nSuccessfully found and printed info into result\n";
    }
    std::cout<<"Should contain Penguin:\t";
    std::cout<<result;

    int size = seq.getSize();
    std::cout<<"Number of all elements should be 4:\t"<<size;
    seq.clear();
    std::cout<<"\nAfter clear() list should be empty:\n";
    seq.print();

    //refilling seq and introducing new seq2 to the test
    seq.pushFront(11, "Goldfish");
    seq.pushFront(8, "Ferret");
    seq.pushFront(2, "Mouse");
    seq.pushFront(2, "Pomeranian");
    seq.pushFront(8, "Corgi");

    std::cout<<"\n\nSequence refilled after clear():\n";
    seq.print();
    std::cout<<"Testing sort() on seq---------------------------\n";
    seq.sort();
    std::cout<<seq;

    seq2 = seq;
    std::cout<<"\nCopied seq to seq2 by operator=--------------------------\n";
    std::cout<<seq2;

    Sequence<int, std::string> seqCopy(seq);
    std::cout << "\nCopy of seq (by copy constructor): \n";
    std::cout<<seqCopy;

    if(seq == seq2)
        std::cout<<"\nTest of operator == succede!d\n";
    else
        std::cout<<"\nTest of operator == failed!\n";
    if(!(seq != seqCopy))
        std::cout<<"Test of operator != succeded\n";
    else
        std::cout<<"\nTest of operator != failed!\n";

    std::cout<<"Testing reverse()------------------------\n";
    seqCopy.reverse();
    std::cout<<"Printing reversed seqCopy:------------------\n";
    std::cout<<seqCopy;
    std::cout<<"\n\nIntroducing new seq3:\n";
    Sequence<int, std::string> seq3;
    seq3.pushFront(1, "Nano fish");
    seq3.pushFront(4, "Polka Dot Catfish");
    seq3.pushFront(77, "Nano fish");
    seq3.pushFront(456456, "Guppy");
    seq3.pushFront(2, "Clown Loach");
    seq3.pushFront(0, "Angelfish");
    seq3.pushFront(6, "Gourami");
    std::cout<<seq3;

    std::cout<<"\nTesting swap()---------------------------\n";
    seq.swap(seq3);
    std::cout<<"seq:\n";
    std::cout<<seq;
    std::cout<<"\nseq3:\n";
    std::cout<<seq3;

    std::cout<<"\nTesting subsequence()------------------------\n";
    seqCopy.clear();
    seqCopy = seqCopy + seq3;
    Sequence<int, std::string> sub = seqCopy.subsequence(2, 8, 1, 2);//Subsequence to ferret no corgi
    std::cout<<"\nShould print subsequence from seqCopy starting with Pomeranian and ending with Ferret\n";
    std::cout<<sub;
    std::cout<<"\nTesting getInfo():------------------------------\n";
    std::string result2;
    sub.getInfo(result2,2,2);
    std::cout<<"Should output info at 2nd occurence of key 2 in sub (mouse):\n";
    std::cout<<result2;

    sub.pushEnd(5,"Rat");
    sub.pushEnd(4,"Gorilla");
    sub = sub.subsequenceFrom(2,2);
    std::cout<<"\nTesting subsequenceFrom()-------------------------\n";
    std::cout<<"Should print subsequence from sub starting with Mouse to the end (Gorilla):\n";
    std::cout<<sub;
    std::cout<<"\nTesting subsequenceTo()-------------------------\n";
    sub = sub.subsequenceTo(5);
    std::cout<<"Should print subsequence to sub ending with Rat:\n";
    std::cout<<sub;
    
    std::cout<<"\n\nTesting split_pos-------------------------\n";
    seq.pushEnd(4,"Monkey");
    seq.pushEnd(2,"Zebra");
    seq.pushEnd(4,"Hippo");
    seq.pushEnd(11,"Shark");
    seq3 =seq;//Copying all elements from seq to seq3 for later tests
    std::cout<<"seq before splitting:\n";
    std::cout<<seq;
    Sequence<int,std::string> seq1;
    seq3 =seq;//Copying all elements from seq to seq3 for later tests
    split_pos(seq,3,2,3,2,seq1,seq2);
    std::cout<<"Should start splitting from 3th element which goes to seq1";
    std::cout<<"\nseq1:\n";
    std::cout<<seq1;
    std::cout<<"\nseq2:\n";
    std::cout<<seq2;
    std::cout<<"\nseq:\n";
    std::cout<<seq;

    std::cout<<"\n\nTesting split_key--------------------------\n";
    seq3.pushEnd(5,"Bunny");
    seq3.pushEnd(4,"Bear");
    seq3.pushEnd(1,"Puppy");
    seq3.pushEnd(79,"Turtle");
    seq3.pushEnd(0,"Platypus");
    std::cout<<"seq3 before splitting:\n";
    std::cout<<seq3;
    split_key(seq3,2,2,2,3,2,seq1,seq2);
    std::cout<<"\nShould start splitting from key 2 with 2nd occurence\n";
    std::cout<<"\nseq1:\n";
    std::cout<<seq1;
    std::cout<<"\nseq2:\n";
    std::cout<<seq2;
    std::cout<<"\nseq3:\n";
    std::cout<<seq3;
    
    return 0;
}