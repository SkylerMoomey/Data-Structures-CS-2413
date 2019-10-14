//
//  OULinkedListEnumerator.h
//  Project 2
//
//  Created by Skyler Moomey on 10/14/19.
//  Copyright © 2019 Skyler Moomey. All rights reserved.
//

#ifndef OU_LINKED_LIST_ENUMERATOR
#define OU_LINKED_LIST_ENUMERATOR

#include "Enumerator.h"
#include "OULink.h"

template <typename T>
class OULinkedListEnumerator : public Enumerator<T>
{
private:
    OULink<T>* current;
public:
    OULinkedListEnumerator(OULink<T>* first);
    bool hasNext() const;
    T next();            // throws ExceptionEnumerationBeyondEnd if no next item is available
    T peek() const;        // throws ExceptionEnumerationBeyondEnd if no next item is available
};

//default constructor for OULinkedListEnumerator
//sets @param current to first
template <typename T>
void OULinkedListEnumerator::OULinkedListEnumerator(OULink<T>* first)
{
    this->current = first;
}

//returns true if current link has a next link
template <typename T>
bool OULinkedListEnumerator::hasNext() const
{
    if(current->next != NULL)
    {
        return true;
    }
    
    return false;
}

template <typename T>
T OULinkedListEnumerator::next()
{
    if(!hasNext())
    {
        throw new ExceptionEnumerationBeyondEnd;
    }
    
    return current->next;
}
//returns the next link, throws ExceptionEnumerationBeyondEnd if no next item available
template <typename T>
T OULinkedListEnumerator::peek() const
{
    if(!hasNext())
    { 
        throw new ExceptionEnumerationBeyondEnd;
    }
    
    return current->next;
}
#endif // !OU_LINKED_LIST_ENUMERATOR
