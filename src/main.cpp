#include "main.hpp"

int main()
{
  IntSLList Slist;
  Slist.Push(5);
  Slist.Push(4);
  Slist.Push(3);
  Slist.Push(2);
  Slist.Push(1);
  Slist.Append(6);
  Slist.Insert(0,Slist.Head());
  std::cout<<"链表内容:"<<std::endl;
  for(auto i:Slist)
  {
      std::cout<<i<<std::endl;
  }
  int* value=Slist.Pop();
  std::cout<<"delete Node :"<<*value<<std::endl;
  delete value;
  Slist.Print();
	return 0;
}
