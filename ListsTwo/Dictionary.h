#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <utility>
#include <stdexcept>
#include "BidirectionalList.h"

namespace bavykin
{
  template< typename K, typename V, typename Cmp = std::less< K > >
  class Dictionary
  {
  public:
    Dictionary(const std::string& name = "dictionary");
    Dictionary(const Dictionary& right);

    using iterator = typename list< std::pair< K, V > >::iterator;
    using const_iterator = typename list< std::pair< K, V > >::const_iterator;

    Dictionary& operator=(const Dictionary& right);
    V operator[](const K& key) const;

    size_t size() const noexcept;
    void insert(const K& key, const V& value);
    iterator find(const K& key);
    const_iterator find(const K& key) const;
    bool contains(const K& key) const;
    void extract(const K& key);

    void changeName(std::string name);

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

  private:
    list< std::pair< K, V > > m_Data;
    std::string m_Name;

    void sort();
  };
  template< typename K, typename V, typename Cmp = std::less< K > >
  using dictionary = Dictionary< K, V, Cmp >;

  template< typename K, typename V, typename Cmp >
  Dictionary< K, V, Cmp >::Dictionary(const std::string& name)
  {
    m_Data = list< std::pair< K, V > >();
    m_Name = name;
  }

  template< typename K, typename V, typename Cmp >
  Dictionary< K, V, Cmp >::Dictionary(const Dictionary& right)
  {
    m_Data = right.m_Data;
    m_Name = right.m_Name;
  }

  template< typename K, typename V, typename Cmp >
  void Dictionary< K, V, Cmp >::changeName(std::string name)
  {
    m_Name = name;
  }

  template< typename K, typename V, typename Cmp >
  size_t Dictionary< K, V, Cmp >::size() const noexcept
  {
    return m_Data.getCount();
  }

  template< typename K, typename V, typename Cmp >
  void Dictionary< K, V, Cmp >::insert(const K& key, const V& value)
  {
    if (contains(key))
    {
      extract(key);
    }
    m_Data.pushFront(std::pair< K, V >(key, value));

    sort();
  }

  template< typename K, typename V, typename Cmp >
  bool Dictionary< K, V, Cmp >::contains(const K& key) const
  {
    try
    {
      find(key);
      return true;
    }
    catch (const std::runtime_error&)
    {
      return false;
    }
  }

  template< typename K, typename V, typename Cmp >
  void Dictionary< K, V, Cmp >::sort()
  {
    list< std::pair< K, V > > tempData = m_Data;

    for (size_t i = 0; i < m_Data.size() - 1; i++)
    {
      for (size_t j = 0; j < m_Data.size() - i - 1; j++)
      {
        if (Cmp{}(tempData[j + 1].first, tempData[j].first))
        {
          std::swap(tempData[j], tempData[j + 1]);
        }
      }
    }

    m_Data = tempData;
  }

  template< typename K, typename V, typename Cmp >
  typename Dictionary< K, V, Cmp >::iterator Dictionary< K, V, Cmp >::find(const K& key)
  {
    for (iterator i = m_Data.begin(); i != m_Data.end(); ++i)
    {
      if ((*i).first == key)
      {
        return i;
      }
    }

    throw std::runtime_error("Trying to find value from dictionary by key, which is not present.");
  }

  template< typename K, typename V, typename Cmp >
  typename Dictionary< K, V, Cmp >::const_iterator Dictionary< K, V, Cmp >::find(const K& key) const
  {
    for (const_iterator i = m_Data.cbegin(); i != m_Data.cend(); ++i)
    {
      if ((*i).first == key)
      {
        return i;
      }
    }

    throw std::runtime_error("Trying to find value from dictionary by key, which is not present.");
  }

  template< typename K, typename V, typename Cmp >
  void Dictionary< K, V, Cmp >::extract(const K& key)
  {
    bool keyWasFound = false;

    for (size_t i = 0; i < m_Data.size(); i++)
    {
      if (m_Data[i].first == key)
      {
        keyWasFound = true;
        m_Data.removeAt(i);
      }
    }

    if (!keyWasFound)
    {
      throw std::runtime_error("Trying to find value from dictionary by key, which is not present.");
    }
  }

  template< typename K, typename V, typename Cmp >
  typename Dictionary< K, V, Cmp >::iterator Dictionary< K, V, Cmp >::begin()
  {
    return m_Data.begin();
  }

  template< typename K, typename V, typename Cmp >
  typename Dictionary< K, V, Cmp >::iterator Dictionary< K, V, Cmp >::end()
  {
    return m_Data.end();
  }

  template< typename K, typename V, typename Cmp >
  typename Dictionary< K, V, Cmp >::const_iterator Dictionary< K, V, Cmp >::cbegin() const
  {
    return m_Data.cbegin();
  }

  template< typename K, typename V, typename Cmp >
  typename Dictionary< K, V, Cmp >::const_iterator Dictionary< K, V, Cmp >::cend() const
  {
    return m_Data.cend();
  }

  template< typename K, typename V, typename Cmp >
  Dictionary< K, V, Cmp >& Dictionary< K, V, Cmp >::operator=(const Dictionary& right)
  {
    m_Data = right.m_Data;
    m_Name = right.m_Name;

    return *this;
  }

  template< typename K, typename V, typename Cmp >
  V Dictionary< K, V, Cmp >::operator[](const K& key) const
  {
    return (*find(key)).second;
  }
}
#endif
