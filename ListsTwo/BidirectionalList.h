#ifndef BIDIRECTIONAL_LIST_H
#define BIDIRECTIONAL_LIST_H
#include <iostream>
#include <memory>
#include <stdexcept>
#include "ListIterator.h"
#include "ListNode.h"

namespace bavykin
{
  template < typename T >
  class BidirectionalList
  {
  public:
    using Node = ListNode< T >;
    using iterator = ListIterator< T, false >;
    using const_iterator = ListIterator< T, true >;

    BidirectionalList(const std::string& name = "list");
    BidirectionalList(const BidirectionalList& right);
    ~BidirectionalList();

    template< typename Type >
    friend std::ostream& operator<<(std::ostream& out, const BidirectionalList< T >& value);
    BidirectionalList& operator=(const BidirectionalList& right);
    T& operator[](size_t index) const;
    bool operator==(const BidirectionalList& right);
    bool operator!=(const BidirectionalList& right);

    size_t size() const noexcept;
    void popFront();
    void popBack();
    void removeAt(size_t index);
    void pushFront(const T& data);
    void pushBack(const T& data);
    void clear();

    std::string getName() const noexcept;
    BidirectionalList< T > replace(const T& oldItem, const T& replaceTo);
    BidirectionalList< T > replace(const T& oldItem, const BidirectionalList< T >& replaceTo);
    BidirectionalList< T > remove(const T& removeable);
    BidirectionalList< T > remove(const BidirectionalList< T >& removeable);
    BidirectionalList< T > concat(const BidirectionalList< BidirectionalList < T > >&);
    bool equal(const BidirectionalList< BidirectionalList < T > >&);

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

  private:
    size_t m_Size;
    Node* m_Head;
    Node* m_Tail;

    std::string m_Name;

    void deleteNode(Node* node);
    Node* searchNode(T item);
  };
  template < typename T >
  using list = BidirectionalList< T >;

  template < typename Type >
  std::ostream& operator<<(std::ostream& out, const BidirectionalList< Type >& value)
  {
    if (value.size() == 0)
    {
      out << "<EMPTY>";
      return out;
    }

    out << value.getName();
    for (auto i = value.cbegin(); i != value.cend(); ++i)
    {
      out << " ";
      out << *i;
    }

    return out;
  }

  template < typename T >
  typename BidirectionalList< T >::iterator BidirectionalList< T >::begin()
  {
    return iterator(m_Head);
  }

  template < typename T >
  typename BidirectionalList< T >::iterator BidirectionalList< T >::end()
  {
    return iterator();
  }

  template < typename T >
  typename BidirectionalList< T >::const_iterator BidirectionalList< T >::cbegin() const
  {
    return const_iterator(m_Head);
  }

  template < typename T >
  typename BidirectionalList< T >::const_iterator BidirectionalList< T >::cend() const
  {
    return const_iterator();
  }

  template < typename T >
  BidirectionalList< T >::~BidirectionalList()
  {
    clear();
  }

  template < typename T >
  std::string BidirectionalList< T >::getName() const noexcept
  {
    return m_Name;
  }

  template < typename T >
  size_t BidirectionalList< T >::size() const noexcept
  {
    return m_Size;
  }

  template < typename T >
  BidirectionalList< T >::BidirectionalList(const BidirectionalList& right)
  {
    m_Size = right.m_Size;
    m_Head = right.m_Head;
    m_Tail = right.m_Tail;
    m_Name = right.m_Name;
  }

  template<typename T>
  BidirectionalList<T>::BidirectionalList(const std::string& name) : m_Size(0), m_Head(nullptr), m_Tail(nullptr)
  {
    m_Name = name;
  }

  template < typename T >
  BidirectionalList< T >& BidirectionalList< T >::operator=(const BidirectionalList& right)
  {
    m_Size = right.m_Size;
    m_Head = right.m_Head;
    m_Tail = right.m_Tail;
    m_Name = right.m_Name;

    return *this;
  }

  template < typename T >
  void BidirectionalList< T >::popFront()
  {
    if (m_Size == 0)
    {
      throw std::length_error("The element cannot be pulled out.");
    }

    deleteNode(m_Head);
  }

  template < typename T >
  void BidirectionalList< T >::popBack()
  {
    if (m_Size == 0)
    {
      throw std::length_error("The element cannot be pulled out.");
    }

    deleteNode(m_Tail);
  }

  template < typename T >
  void BidirectionalList< T >::deleteNode(Node* node)
  {
    /*if (node->m_PointerNext == nullptr && node->m_PointerPrevious == nullptr)
    {
      m_Tail = nullptr;
      m_Head = nullptr;
    }
    else if (node->m_PointerNext == nullptr)
    {
      node->m_PointerPrevious->m_PointerNext = nullptr;
      m_Tail = node->m_PointerPrevious;
    }
    else if (node->m_PointerPrevious == nullptr)
    {
      node->m_PointerNext->m_PointerPrevious = nullptr;
      m_Head = node->m_PointerNext;
    }
    else
    {
      node->m_PointerPrevious->m_PointerNext = node->m_PointerNext;
      node->m_PointerNext->m_PointerPrevious = node->m_PointerPrevious;
    }*/

    if (node->m_PointerPrevious != nullptr)
    {
      (node->m_PointerPrevious)->m_PointerNext = node->m_PointerNext;
    }
    else
    {
      m_Head = node->m_PointerNext;
    }

    if (node->m_PointerNext != nullptr)
    {
      (node->m_PointerNext)->m_PointerPrevious = node->m_PointerPrevious;
    }
    else
    {
      m_Tail = node->m_PointerPrevious;
    }

    m_Size--;
  }

  template < typename T >
  void BidirectionalList< T >::pushFront(const T& data)
  {
    Node* newNode = new Node(data, m_Head, nullptr);

    if (m_Head != nullptr)
    {
      m_Head->m_PointerPrevious = newNode;
    }
    else
    {
      m_Tail = newNode;
    }
    m_Head = newNode;

    m_Size++;
  }

  template < typename T >
  void BidirectionalList< T >::pushBack(const T& data)
  {
    Node* newNode = new Node(data, nullptr, m_Tail);

    if (m_Tail != nullptr)
    {
      m_Tail->m_PointerNext = newNode;
    }
    else
    {
      m_Head = newNode;
    }
    m_Tail = newNode;

    m_Size++;
  }

  template < typename T >
  void BidirectionalList< T >::removeAt(size_t index)
  {
    if (index >= m_Size)
    {
      throw std::length_error("Specified index is not valid.");
    }

    if (index == 0)
    {
      popFront();
    }
    else if (index == m_Size - 1)
    {
      popBack();
    }
    else
    {
      Node* previous = m_Head;

      for (size_t i = 0; i < index - 1; i++)
      {
        previous = previous->m_PointerNext;
      }

      Node* toDelete = previous->m_PointerNext;

      previous->m_PointerNext = toDelete->m_PointerNext;

      m_Size--;
    }
  }

  template < typename T >
  void BidirectionalList< T >::clear()
  {
    while (m_Size)
    {
      popFront();
    }
  }

  template < typename T >
  typename BidirectionalList< T >::Node* BidirectionalList< T >::searchNode(T item)
  {
    Node* node = m_Head;
    while (node != nullptr && node->m_Data != item)
    {
      node = node->m_PointerNext;
    }
    return node;
  }

  template<typename T>
  BidirectionalList< T > BidirectionalList<T>::replace(const T& oldItem, const T& replaceTo)
  {
    Node* searchedNode = searchNode(oldItem);

    while (searchedNode != nullptr)
    {
      searchedNode->m_Data = replaceTo;
      searchedNode = searchNode(oldItem);
    }

    return *this;
  }

  template< typename T >
  BidirectionalList< T > BidirectionalList< T >::replace(const T& oldItem, const BidirectionalList< T >& replaceTo)
  {
    BidirectionalList< T > newList(m_Name);

    for (const_iterator i = cbegin(); i != cend(); i++)
    {
      if ((*i.m_Current).m_Data != oldItem)
      {
        newList.pushBack((*i.m_Current).m_Data);
      }
      else
      {
        for (size_t i = 0; i < replaceTo.size(); i++)
        {
          newList.pushBack(replaceTo[i]);
        }
      }
    }

    return newList;
  }

  template< typename T >
  BidirectionalList< T > BidirectionalList< T >::remove(const T& removeable)
  {
    while (searchNode(removeable) != nullptr)
    {
      deleteNode(searchNode(removeable));
    }

    return *this;
  }

  template< typename T >
  BidirectionalList< T > BidirectionalList< T >::remove(const BidirectionalList< T >& removeable)
  {
    for (size_t i = 0; i < removeable.size(); i++)
    {
      remove(removeable[i]);
    }

    return *this;
  }

  template< typename T >
  BidirectionalList< T > BidirectionalList< T >::concat(const BidirectionalList< BidirectionalList < T > >& lists)
  {
    BidirectionalList< T > newList(m_Name);

    for (size_t i = 0; i < lists.size(); i++)
    {
      for (size_t j = 0; j < lists[i].size(); j++)
      {
        newList.pushBack(lists[i][j]);
      }
    }

    return newList;
  }

  template< typename T >
  bool BidirectionalList< T >::equal(const BidirectionalList< BidirectionalList < T > >& lists)
  {
    for (size_t i = 0; i < lists.size() - 1; i++)
    {
      if (lists[i] != lists[i + 1])
      {
        return false;
      }
    }

    return true;
  }

  template < typename T >
  T& BidirectionalList< T >::operator[](size_t index) const
  {
    if (index >= m_Size)
    {
      throw std::length_error("Specified index is not valid.");
    }

    size_t counter = 0;
    Node* current = m_Head;

    while (current != nullptr)
    {
      if (counter == index)
      {
        return current->m_Data;
      }
      current = current->m_PointerNext;
      counter++;
    }

    return current->m_Data;
  }

  template < typename T >
  bool BidirectionalList< T >::operator==(const BidirectionalList& right)
  {
    if (size() != right.size())
    {
      return false;
    }

    for (size_t i = 0; i < size(); i++)
    {
      if (operator[](i) != right[i])
      {
        return false;
      }
    }

    return true;
  }

  template < typename T >
  bool BidirectionalList< T >::operator!=(const BidirectionalList& right)
  {
    return !(operator==(right));
  }
}
#endif
