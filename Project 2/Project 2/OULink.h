//
//  OULink.h
//  Project 2
//
//  Created by Skyler Moomey on 10/14/19.
//  Copyright © 2019 Skyler Moomey. All rights reserved.
//

#ifndef OU_LINK_H
#define OU_LINK_H

template <typename T>
class OULink {
    template <typename T>
    friend class OULinkedList;
    template <typename T>
    friend class OULinkedListEnumerator;
    private
    T data{};                  // data item of any type
    OULink* next = NULL;       // pointer to next link
public:
    OULink(T item);
    virtual ~OULink();
};

template <typename T>
void OULink::OULink(T item)
{
    this->data = item;
}
#endif /* OU_LINK_H */
