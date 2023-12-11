// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem=v.pMem;
      for (size_t i = 0; i < sz; i++)
          pMem[i] = v.pMem[i];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      pMem = v.pMem;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)//копирующий оператор присваивания
  {
      if (this == &v) return *this;
      if (sz != v.sz)
      {
          T* p = new T[v.sz];
          sz = v.sz;
          delete[] pMem;
          pMem = p;
      }
      std::copy(v.pMem, v.pMem + sz, pMem);
      retun* this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this, v);
      v.pMem = nullptr;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      if (ind > 0 && ind < sz) return pMem[ind];
      else throw("Inalidal Index");
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind > 0 && ind < sz) return pMem[ind];
      else throw("Inalidal Index");
  }
  const T& at(size_t ind) const
  {
      if (ind > 0 && ind < sz) return pMem[ind];
      else throw("Inalidal Index");
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz == v.sz)
      {
          for (size_t i = 0; i < sz; i++)
              if (pMem[i] == v.pMem[i]) return 1;
              else return 0;
      }
      else return 0;
             
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return 1;
      else
      {
          for (size_t i = 0; i < sz; i++)
              if (pMem[i] != v.pMem[i]) return 1;
              else return 0;
      }
  }

  // скалярные операции
  TDynamicVector operator+(T val)//прибавление ко всем координатам вектора числа val
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
      {
          tmp.pMem[i] = pMem[i] + val;
      }
      return tmp;
  }
  TDynamicVector operator-(T val)//вычитание из всех координат вектора числа val
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
      {
          tmp.pMem[i] = pMem[i] - val;
      }
      return tmp;
  }
  TDynamicVector operator*(T val)// умножение всех координат вектора на число val
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
      {
          tmp.pMem[i] = pMem[i] * val;
      }
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz == v.sz)
      {
          TDynamicVector tmp(sz);
          for (size_t i = 0; i < sz; i++)
          {
              tmp.pMem[i] = this->pMem[i] + v.pMem[i];
          }
          return tmp;
      }
      else throw ("Invalidal sz");
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz == v.sz)
      {
          TDynamicVector tmp(sz);
          for (size_t i = 0; i < sz; i++)
          {
              tmp.pMem[i] = this->pMem[i] - v.pMem[i];
          }
          return tmp;
      }
      else throw ("Invalidal sz");
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))// скалярное умножение векторов
  {
      if (sz == v.sz)
      {
          T tmp = 0;
          for (size_t i = 0; i < sz; i++)
          {
              tmp = tmp+ v.pMem[i]*pMem[i];
          }
          return tmp;
      }
      else throw ("Invalidal sz");

  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz == m.sz)
      {
          for (size_t i = 0; i < sz; i++)
              if (pMem[i] == m.pMem[i]) return 1;
              else return 0;
      }
      else return 0;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix<T> tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] * val;
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz == v.sz)
      {
          TDynamicVector<T> tmp1(sz);
          for (size_t i = 0; i < sz; i++)
          {
              T tmp2 = 0;
              for (size_t j = 0; j < sz; j++)
                  tmp2 = tmp2 + pMem[i][j] * v.pMem[j];
          }
          tmp.pMem[i] = tmp2;
          return tmp1;
      }
      else throw ("Invalidal sz");
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz == m.sz)
      {
          TDynamicMatrix<T> tmp(sz);
          for (size_t i = 0; i < sz; i++)
          {
              for (size_t j = 0; j < sz; j++)
                  tmp.pMem[i][j] = pMem[i][j] + m.pMem[i][j];
          }
          return tmp;
      }
      else throw ("Invalidal size");
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz == m.sz)
      {
          TDynamicMatrix<T> tmp(sz);
          for (size_t i = 0; i < sz; i++)
          {
              for (size_t j = 0; j < sz; j++)
                  tmp.pMem[i][j] = pMem[i][j] - m.pMem[i][j];
          }
          return tmp;
      }
      else throw ("Invalidal size");
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz == m.sz)
      {
          TDynamicMatrix<T> tmp1(sz);
          for (size_t i = 0; i < sz; i++)
          {
              for (size_t j = 0; j < sz; j++)
              {
                  T tmp2 = 0;
                  for (size_t k = 0; k < sz; k++)
                  {
                      tmp2 = tmp2 + pMem[i][j] * m.pMem[k][j];
                  }
                  tmp1.pMem[i][j] = tmp2;
              }
          }
      }
      else throw ("Invalidal sz");
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i];
      return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << '\n';
      return ostr;
  }
};
#endif
