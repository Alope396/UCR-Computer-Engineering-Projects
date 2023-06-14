#include "IntList.h"

#include <ostream>

using namespace std;

IntList::IntList() : head(0) {}


void IntList::push_front(int val) {
   if (!head) {
      head = new IntNode(val);
   } else {
      IntNode *temp = new IntNode(val);
      temp->next = head;
      head = temp;
   }
}

bool IntList::exists(int val) const{
   return exists(head, val);
}

bool IntList::exists(IntNode * curr, int val) const{
   if(curr == nullptr){
      return false;
   }
   if(curr->data == val){
      return true;
   }
   else{
      IntNode* next = curr->next;
      return exists(next, val);
   }
}

ostream & operator<<(ostream & out, const IntList& list){
   if(list.head == nullptr){
      out << "";
      return out;
   }
   else{
      out<< list.head->data;
      if(list.head->next != nullptr){
         return operator<<(out, list.head->next);
      }
      return out;
   }
}

ostream & operator<<(ostream & out, IntNode* curr){
   if(curr->next == nullptr){
      out<< " " << curr->data;
      return out;
   }
   else{
      out<< " " << curr->data;
      operator<<(out, curr->next);
      return out;
   }
}