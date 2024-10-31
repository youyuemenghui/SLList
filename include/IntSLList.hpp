#include "type.hpp"

class IntSLLNode
{
public:
  IntSLLNode():_item(0),_next(nullptr){}
  IntSLLNode(int el,IntSLLNode* ptr=0):_item(el),_next(ptr){}
  void SetNext(IntSLLNode *ptr){_next=ptr;}
  void SetData(int data){_item=data;}
  IntSLLNode* GetNext()const {return this->_next;}
  int GetData()const {return this->_item;}
private:
  int _item;
  IntSLLNode * _next;
};

class Iterator
{
public:
  Iterator(IntSLLNode *ptr):_current(ptr){}
  bool operator!=(const Iterator& other)const;
  int operator*()const;
  const Iterator& operator++();
private:
  IntSLLNode* _current;
};

class IntSLList
{
public:
  IntSLList();
  ~IntSLList();
  bool IsEmpty(); //判空
  int GetLength(); //获取链表长度
  IntSLLNode* Head(); //返回头指针
  IntSLLNode* Tail(); //返回尾指针
  void Push(int data);    //插入开头
  void Append(int data);  //插入末尾
  void Insert(int data,IntSLLNode *pos);  //插入
  void Insert(int data,int index);  //插入
  int* Shift();    //删除开头
  int* Remove(IntSLLNode *pos);   //删除
  int* Remove(int index);   //删除
  int* Pop();      //删除末尾
  bool clear();   //清空链表
  bool Inlist(const IntSLLNode* pos); //判断节点是否在链表中
  bool Inlist(const int target);  //判断数据所在节点是否在链表中
  IntSLLNode* Find(int target) const; //查找函数
  void Print()const;  //遍历打印
  //迭代
  Iterator begin()const;  
  Iterator end()const;

private:
  int _Length;
  IntSLLNode *_header,*_tail;
};

