#include "SLList.hpp"

int main()
{
  SLList<int> lklist;
  lklist.AddToHead(1);
  lklist.AddToHead(2);
  lklist.AddToHead(3);
  lklist.Print();
	return 0;
}
