#include "SLList.hpp"
#include <iostream>

template<typename T>
SLList<T>::SLList():header(new SLLNode<T>()),length(0)
{
  if(this->IsEmpty())
    std::cerr<<"Error can't allocating Memory!"<<std::endl;
}

template<typename T>
SLList<T>::~SLList()
{
  this->clear();
  delete this->header;
}

template<typename T>
bool SLList<T>::IsEmpty() const //判断链表头节点后是否为空
{
  if(this->First()==nullptr)
  {
    return true;
  }
  return false;
}

template<typename T>
void SLList<T>::AddToHead(const T &item)
{
  this->header->setNext(new SLLNode<T>(item,this->header->getNext()));
  this->length++;
}



template<typename T>
void SLList<T>::AddToTail(const T &item)
{
  if(this->IsEmpty())
  {
    this->header->setNext(new SLLNode<T>(item));
    this->length++;
  }
  else
  {
    this->Tail()->next=new SLLNode<T>(item);
    this->length++;
  }
}
template<typename T>
T SLList<T>::DeleteToHead()
{
  if(this->IsEmpty())
  {
    return T();
  }
  T item=this->First()->getData(); //保存数据
  SLLNode<T> *tmp=this->First()->getNext(); //
  this->First()->setNext(this->First()->getNext());
  delete tmp;
  this->length--;
  return item;
}

template<typename T>
T SLList<T>::DeleteToTail()
{
    if (this->IsEmpty())
    {
        return T(); // 返回默认构造的 T 对象
    }

    if (this->First()->getNext() == nullptr)
    {
        return this->DeleteToHead(); // 只有一个节点，调用 DeleteToHead 删除并返回
    }

    SLLNode<T>* tail = this->Tail(); // 获取尾节点
    SLLNode<T>* prevNode = this->Prev(tail); // 获取尾节点的前驱

    prevNode->next = tail->next; // 更新前驱节点的 next 指针
    T item = tail->Data; // 存储尾节点的数据
    delete tail; // 删除尾节点
    this->length--;
    return item;
}

template<typename T>
bool SLList<T>::DeleteNode(const T &item)
{
    if (this->IsEmpty())
    {
        return false; // 链表为空，无法删除
    }

    // 特殊处理第一节点的情况
    if (this->First()->Data == item)
    {
        SLLNode<T>* tmp = this->First(); // 头节点
        this->First() = this->First()->next; // 更新头节点为下一个节点
        delete tmp; // 删除原头节点
        this->length--;
        return true; // 删除成功
    }

    // 查找待删除的节点
    SLLNode<T>* current = this->Find(item);
    SLLNode<T>* prevNode = this->Prev(current);

    if (prevNode == nullptr)
    {
        return false; // 节点未找到
    }
    SLLNode<T>* nodeToDelete = prevNode->next;
    prevNode->next = nodeToDelete->next; // 更新前驱节点的 next 指针
    delete nodeToDelete; // 删除节点
    this->length--;
    return true; // 删除成功
}

template<typename T>
SLLNode<T>* SLList<T>::Prev(SLLNode<T>* PosPoint)
{
  if(this->IsEmpty() || PosPoint == nullptr)
  {
    return nullptr;
  }
  SLLNode<T>* current;
  for(current=this->First();current!=nullptr && current->getNext()!=PosPoint;current=current->getNext());
  return current;
}


template<typename T>
SLLNode<T>* SLList<T>::Prev(const T &item)
{
  if(this->IsEmpty())
  {
    return nullptr;
  }
  for (SLLNode<T>* current = this->First(); current != nullptr && current->getNext()!= nullptr; current = current->getNext())
  {
    if (current->getNext()->getData() == item)
    {
        return current; // 返回前驱节点
    }
  }
  return nullptr;
}


template<typename T>
SLLNode<T>* SLList<T>::Find(T &item)
{
  SLLNode<T>* tmp;
  for (tmp = this->First(); tmp != nullptr && tmp->getData() == item  ; tmp = tmp->getNext());
  return tmp;
}


template<typename T>
void SLList<T>::clear()
{
  if(this->IsEmpty())
  {
    return;
  }
  for(SLList<T>* tmp=this->header;tmp->getNext()!=nullptr;this->DeleteToHead());
}

template<typename T>
int SLList<T>::Length()const
{
  return this->length;
}

template<typename T>
SLList<T>::Iterator::Iterator(SLLNode<T>* ptr ):current(ptr){}

//template<typename T>
//T& SLList<T>::Iterator::operator*()
//{
//  return this->current->getData();
//}

template<typename T>
const T& SLList<T>::Iterator::operator*() const
{
  return this->current->getData();
}

template<typename T>
SLList<T>::Iterator& SLList<T>::Iterator::operator++()
{
  if(current) this->current=this->current->getNext();
  return *this;
}

//template<typename T>
//SLList<T>::Iterator SLList<T>::Iterator::operator++(int) {
//    Iterator temp = *this;
//    ++(*this);
//    return temp;
//}
template<typename T>
bool SLList<T>::Iterator::operator==(const Iterator& other) const
{
  return this->current==other.current;
}

template<typename T>
bool SLList<T>::Iterator::operator!=(const Iterator& other) const
{
  return this->current!=other.current;
}

template<typename T>
SLList<T>::Iterator SLList<T>::begin()
{
  return Iterator(this->header->getNext());
}

template<typename T>
SLList<T>::Iterator SLList<T>::end()
{
  return Iterator(nullptr);
}

template<typename T>
void SLList<T>::Print()const
{
  int count{0};
  for(const T& item:*this)
  {
    ++count;
    std::cout<<count<<": "<<item<<std::endl;
  }
}

template<typename T>
bool SLList<T>::IsInSLList(T &item) const
{
  if(this->Find(item)!=nullptr)
    return true;
  return false;
}


template<typename T>
SLLNode<T>* SLList<T>::First()
{
  return this->header->getNext();
}

template<typename T>
SLLNode<T>* SLList<T>::Tail()
{
  if(this->IsEmpty())
  {
    return nullptr;
  }
  SLLNode<T>* Tail;
  for(Tail=this->First();Tail->getNext()!=nullptr;Tail->setNext(Tail->getNext()));
  return Tail;
}
