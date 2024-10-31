#ifndef __SLLIST_H_
#define __SLLIST_H_

#include <iterator>  // 包含 std::iterator


template<typename T>
class SLLNode
{
  private:
  SLLNode *next;
  T Data;

  public:
    // 默认构造函数
    SLLNode():next(nullptr){};
    // 带参数的构造函数
    SLLNode(T element,SLLNode *ptr=nullptr):Data(element),next(ptr){}
    // 获取下一个节点的指针
    SLLNode* getNext() const { return next; }
    // 设置下一个节点的指针
    void setNext(SLLNode* ptr) { next = ptr; }
    // 获取数据
    T& getData() { return Data; }
    // 获取数据（常量版本）
    const T& getData() const { return Data; }
};

template<typename T>
class SLList
{
  public:
    SLList();
    ~SLList();
    bool IsEmpty() const;
    void AddToHead(const T &item);
    void AddToTail(const T &item);
    T DeleteToHead();
    T DeleteToTail();
    bool DeleteNode(const T &item);
    SLLNode<T>* Prev(SLLNode<T>* PosPoint);
    SLLNode<T>* Prev(const T &item);
    SLLNode<T>* Find(T &item);
    void clear();
    int Length()const;
    bool IsInSLList(T &item) const;
    //SLLNode<T>* GetHead();
    //void SetHead(SLLNode<T> *ptr);
    //SLLNode<T>* Locate(int pos);
    //bool Insert(T &item, int pos);
    //bool Remove(int pos,T &item);
    //bool GetData(int pos,T &item);
    //bool SetData(int pos,T &item);
    void Print()const;
  class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(SLLNode<T>* ptr = nullptr) ;
        //T& operator*();
        const T& operator*() const;
        Iterator& operator++();

        //Iterator operator++(int);
        // 嵌套迭代器类
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const; 

    private:
        SLLNode<T>* current;
    };

    Iterator begin(); 
    Iterator end();
  private:
  SLLNode<T> *header;
  int length;
  SLLNode<T>* First();
  SLLNode<T>* Tail();
};

#endif
