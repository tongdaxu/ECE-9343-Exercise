/*
10.2 Linked List
you should not use null too much, use null ptr
*/
#include <stdio.h>
#include <vector>
#include <iostream>

template<class T>
class ListNode {
public:
    T val;
    ListNode<T>* prev = NULL;
    ListNode<T>* next = NULL;
    
    ListNode(){}
    ListNode(T _val, ListNode* _next = NULL, ListNode* _prev = NULL){
        val = _val;
        prev = _prev;
        next = _next;
    }
    ~ListNode(){}
};

template<class T>
class LinkedList {

public:

    ListNode<T>* head = NULL;
    ListNode<T>* tail = NULL;
    bool circular = 0;
    
    LinkedList(bool _circular = 0){
        
        if (! _circular){
            head = new ListNode<T>(0);
            tail = new ListNode<T>(0);
            head->next = tail;
            tail->prev = head;
        }
        
        if (_circular){
            head = new ListNode<T>(0);
            head->prev = head;
            head->next = head;
            circular = 1;
        }
    }
    
    void ListInsert(ListNode<T>* temp){
        temp->prev = head;
        temp->next = head->next;
        head->next->prev = temp;
        head->next = temp;
    }
    
    void ListDelete(ListNode<T>* temp){
        
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        
        delete temp;
    }
    
    ListNode<T>* ListSearch(T key){
        ListNode<T>* curr = head->next;
        
        while (curr!= tail && curr->val != key){
            curr = curr->next;
        }
        
        if (curr == tail){
            return NULL;
        } else {
            return curr;
        }
    }
    
    ~LinkedList(){
        //circular or not
        while (head->next != tail && head->next != head){
            ListDelete(head->next);
        }
        
        delete head;
        
        if (!circular){
            delete tail;
        }
    }
};

int main()
{   
    LinkedList<int> myLinkedList;
    ListNode<int>* temp = new ListNode<int>(8);
    
    myLinkedList.ListInsert(temp);
    std::cout<<myLinkedList.head->next->val<<"\n";
    
    ListNode<int>* result = myLinkedList.ListSearch(8);
    std::cout<<result->val<<"\n";

    
    myLinkedList.ListDelete(temp);
    std::cout<<myLinkedList.head->next->val<<"\n";

    return 0;
}
