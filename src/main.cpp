#include "main.hpp"

int main()
{
  IntSLList<float> Slist;
  Slist.Push(5.0);
  Slist.Push(4.0);
  Slist.Push(3.0);
  Slist.Push(2.0);
  Slist.Push(1.0);
  Slist.Append(6.0);
  Slist.Insert(0,Slist.Head());
  std::cout<<"链表内容:"<<std::endl;
  for(auto i:Slist)
  {
      std::cout<<i<<std::endl;
  }
  auto* value=Slist.Pop();
  std::cout<<"delete Node :"<<*value<<std::endl;
  delete value;
  Slist.Print();
	return 0;
}
