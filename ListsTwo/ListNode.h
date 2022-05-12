#ifndef LISTNODE_H
#define LISTNODE_H
#include <memory>

namespace bavykin
{
  template< typename T >
  struct ListNode
  {
    using pointer = std::shared_ptr< ListNode >;

    T m_Data;
    pointer m_PointerNext;
    pointer m_PointerPrevious;

    ListNode(const T& data = T(), pointer pNext = nullptr, pointer pPrevious = nullptr) :
      m_Data(data),
      m_PointerNext(pNext),
      m_PointerPrevious(pPrevious)
    {
    }
  };
}
#endif
