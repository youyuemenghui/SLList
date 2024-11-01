#include "type.hpp"
#include <iostream>
#ifndef __SLLIST_HPP_
#define __SLLIST_HPP_

template <typename T>
class SLLNode
{
public:
  SLLNode():_item(0),_next(nullptr){}
  SLLNode(T el,SLLNode* ptr=0):_item(el),_next(ptr){}
  void SetNext(SLLNode *ptr){_next=ptr;}
  void SetData(T data){_item=data;}
  SLLNode* GetNext()const {return this->_next;}
  T GetData()const {return this->_item;}
private:
  T _item;
  SLLNode * _next;
};
//链表的for迭代循环支持
template <typename T>
class Iterator
{
public:
  Iterator(SLLNode<T> *ptr):_current(ptr){}
  bool operator!=(const Iterator& other)const;
  T operator*()const;
  const Iterator& operator++();
private:
  SLLNode<T>* _current;
};
//迭代器不等于运算符重载
//判断当前迭代器实例是否不等于传入的迭代器实例
template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other)const
{
  return this->_current!=other._current;
}
//迭代器解指针运算符重载
//拿取当前迭代器中的节点数据
template <typename T>
T Iterator<T>::operator*()const
{
  return this->_current->GetData();
}
//迭代器的自增运算符重载
//当前迭代器移动到下一节点
template <typename T>
const Iterator<T>& Iterator<T>::operator++()
{
  if(_current)
  {
    this->_current=this->_current->GetNext();
  }
  return *this;
}

template <typename T>
class SLList
{
public:
  SLList();
  ~SLList();
  bool IsEmpty(); //判空
  int GetLength(); //获取链表长度
  SLLNode<T>* Head(); //返回头指针
  SLLNode<T>* Tail(); //返回尾指针
  void Push(T data);    //插入开头
  void Append(T data);  //插入末尾
  void Insert(T data,SLLNode<T> *pos);  //插入
  void Insert(T data,int index);  //插入
  T* Shift();    //删除开头
  T* Remove(SLLNode<T> *pos);   //删除
  T* Remove(int index);   //删除
  T* Pop();      //删除末尾
  bool clear();   //清空链表
  bool Inlist(const SLLNode<T> *pos); //判断节点是否在链表中
  bool Inlist(const T target);  //判断数据所在节点是否在链表中
  SLLNode<T>* Find(T target) const; //查找函数
  void Print()const;  //遍历打印
  //迭代
  Iterator<T> begin()const;  
  Iterator<T> end()const;

private:
  int _Length;
  SLLNode<T> *_header,*_tail;
};
//链表初始化构造
template <typename T>
SLList<T>::SLList()
{
  this->_header=this->_tail=nullptr;
  this->_Length=0;
}
//链表析构
template <typename T>
SLList<T>::~SLList()
{
  this->clear();
}

//判空函数
template <typename T>
bool SLList<T>::IsEmpty()
{
  return this->_Length==0;
}
//长度获取
template <typename T>
int SLList<T>::GetLength()
{
  return this->_Length;
}
//返回头节点
template <typename T>
SLLNode<T>* SLList<T>::Head()
{
  return this->_header;
}
//返回尾节点
template <typename T>
SLLNode<T>* SLList<T>::Tail()
{
  return this->_tail;
}

template <typename T>
void SLList<T>::Push(T data)
{
  this->_header=new SLLNode<T>(data,this->_header);
  if(this->_tail==nullptr)
  {
    this->_tail=this->_header;
  }
  this->_Length++;
}
template <typename T>
void SLList<T>::Append(T data)
{
  if(this->_tail!=nullptr)
  {
    this->_tail->SetNext(new SLLNode<T>(data));
    this->_tail=this->_tail->GetNext();
    this->_Length++;
  }
  else
  {
    this->_header=this->_tail=new SLLNode<T>(data);
    this->_Length++;
  }
}
template <typename T>
void SLList<T>::Insert(T data,SLLNode<T> *pos)
{
  //处理指针为空
  if(pos==nullptr)
  {
    std::cout<<"Error: Invalid Pos!"<<std::endl;
    return;
  }
  //处理插入位置指针与头节点相等
  if(pos==this->_header)
  {
    this->Push(data);
    return;
  }
  SLLNode<T>* CurrentPos = this->_header;
  for(;CurrentPos && CurrentPos->GetNext()!=pos;CurrentPos=CurrentPos->GetNext());
  if(CurrentPos!=nullptr)
  {
    CurrentPos->SetNext(new SLLNode<T>(data,pos));
  }
}
template <typename T>
void SLList<T>::Insert(T data,int index)
{
  //判断索引是否合法,index<0
  if(index>(this->_Length-1) || index<0)
  {
    std::cout<<"Error:Invalid index,Insert faild"<<std::endl;
    return ;
  }
  //处理index==0
  if(index==0)
  {
    this->Push(data);
    return;
  }
  //index>0
  SLLNode<T> *tmp=this->_header;
  for(int count=0;count<index-1;++count)
  {
    if(tmp==nullptr)
    {
      std::cout<< "Error:Reached end of list unexpectedly"<<std::endl;
      return;
    }
    tmp=tmp->GetNext();
  }
  tmp->SetNext(new SLLNode<T>(data,tmp->GetNext()));
  this->_Length++;
}
template <typename T>
T* SLList<T>::Shift()
{
  if(this->_Length<=0)
  {
    std::cout<<"Error : list is Empty!!";
    return nullptr;
  }
  T* value_ptr{new T(this->_header->GetData())};
  if(this->_header==this->_tail)
  {
    delete this->_header;
    this->_header=this->_tail=nullptr;
    this->_Length--;
    return value_ptr;
  }
  SLLNode<T>* tmp{this->_header};
  this->_header=this->_header->GetNext();
  delete tmp;
  this->_Length--;
  return value_ptr;
}
template <typename T>
T* SLList<T>::Remove(SLLNode<T> *pos)
{
  if (pos == nullptr) {
      std::cout << "Error: Invalid pos" << std::endl;
      return nullptr;
  }
  
  if (this->_Length <= 0) {
      std::cout << "Error: list is Empty!!" << std::endl;
      return nullptr;
  }

  T* value_ptr = new T(pos->GetData());
  
  // 处理单节点情况
  if (this->_Length == 1) {
      if (pos == this->_header) {
          delete pos;
          this->_header = this->_tail = nullptr;
          this->_Length--;
          return value_ptr;
      }
      delete value_ptr; // 清理已分配的内存
      return nullptr;
  }
  // 查找要删除的节点的前一个节点
  SLLNode<T>* tmp = this->_header;
  if (pos == this->_header)
  { // 处理头节点
      this->_header = pos->GetNext();
  } 
  else 
  {
    for(;tmp != nullptr && tmp->GetNext() != pos;tmp = tmp->GetNext());
    if (tmp == nullptr)
    { // 如果没有找到 pos
          delete value_ptr;
          return nullptr;
    }
    tmp->SetNext(pos->GetNext());
    
    // 如果是尾节点，更新尾指针
    if (pos == this->_tail) {
        this->_tail = tmp;
    }
  }
  delete pos; // 删除节点
  this->_Length--; // 减少长度
  return value_ptr;
}
template <typename T>
T* SLList<T>::Remove(int index)
{
  if (this->_Length <= 0)
  {
      std::cout << "错误：列表为空！" << std::endl;
      return nullptr;
  }

  if (index < 0 || index >= this->_Length)
  {
      std::cout << "错误：索引超出范围！" << std::endl;
      return nullptr;
  }

  SLLNode<T>* current = this->_header;
  SLLNode<T>* previous = nullptr;

  // 遍历到指定索引
  for (int i = 0; i < index; ++i)
  {
      previous = current;
      current = current->GetNext();
  }

  T* value_ptr = new T(current->GetData()); // 存储要删除节点的数据

  if (previous == nullptr) // 如果删除的是头节点
  {
      this->_header = current->GetNext();
  }
  else // 删除非头节点
  {
      previous->SetNext(current->GetNext());
  }

  if (current == this->_tail) // 如果删除的是尾节点
  {
      this->_tail = previous;
  }

  delete current; // 删除节点
  this->_Length--; // 减少长度
  return value_ptr; // 返回删除的值
}
template <typename T>
T* SLList<T>::Pop()
{
  if (this->_Length <= 0) {
      std::cout << "Error: list is Empty!!" << std::endl;
      return nullptr;
  }
  T* value_ptr=new T(this->_tail->GetData());
  if(this->_Length==1)
  {
    delete this->_tail;
    this->_header=this->_tail=nullptr;
    this->_Length--;
    return value_ptr;
  }
  SLLNode<T>* tmp=nullptr;
  for(tmp=this->_header;tmp != nullptr && tmp->GetNext() != this->_tail;tmp = tmp->GetNext());
  tmp->SetNext(this->_tail->GetNext());
  delete this->_tail;
  this->_tail=tmp;
  this->_Length--;
  return value_ptr;
}
template <typename T>
bool SLList<T>::clear()
{
  // 检查链表是否为空
  if (IsEmpty()) {
      return false; // 如果链表已经为空，返回false
  }

  SLLNode<T>* current = _header; // 从头节点开始
  SLLNode<T>* nextNode = nullptr;

  // 遍历链表并删除每个节点
  while (current != nullptr) {
      // 输出当前节点的数据
      std::cout << "Deleting node with data: " << current->GetData() << std::endl;

      nextNode = current->GetNext(); // 保存下一个节点
      delete current; // 删除当前节点
      current = nextNode; // 移动到下一个节点
  }

  // 清空链表的头尾指针和长度
  _header = nullptr;
  _tail = nullptr;
  _Length = 0; // 更新链表长度
  return true; // 返回true表示清空成功
}
template <typename T>
bool SLList<T>::Inlist(const SLLNode<T>* pos)
{
  if(pos==nullptr)
  {
    return false;
  }
  for(SLLNode<T>* tmp=this->_header;tmp!=nullptr;tmp=tmp->GetNext())
  {
    if(tmp==pos)
    {
      return true;
    }
  }
  return false;
}
template <typename T>
bool SLList<T>::Inlist(const T target)
{
  for(auto i:*this)
  {
    if(i==target)
    {
      return true;
    }
  }
  return false;
}
template <typename T>
void SLList<T>::Print()const //遍历打印
{
  SLLNode<T>* current = this->_header; // 从头节点开始
  while (current != nullptr) {    // 遍历链表
      std::cout << current->GetData() << " "; // 打印当前节点的数据
      current = current->GetNext(); // 移动到下一个节点
  }
  std::cout << std::endl; // 打印换行
}
template <typename T>
SLLNode<T>* SLList<T>::Find(T target) const //查找函数
{
  if(this->_Length==0)
  {
    std::cout<<"Error: List is Empty!!"<<std::endl;
    return nullptr;
  }
  SLLNode<T>* tmp=this->_header;
  for(;tmp!=nullptr && tmp->GetData()!= target;tmp=tmp->GetNext());
  if(tmp==nullptr)
  {
    std::cout<<"Error: target not in list!"<<std::endl;
    return nullptr;
  }
  return tmp;
}
template <typename T>
Iterator<T> SLList<T>::begin()const
{
  return Iterator<T>(this->_header);
}
template <typename T>
Iterator<T> SLList<T>::end()const
{
  return Iterator<T>(nullptr);
}
#endif // !__SLLIST_HPP_
