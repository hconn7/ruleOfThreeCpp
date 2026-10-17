#include <cassert>
#include <cstddef>
#include <iostream>
#include <ostream>

class IntArray {
private:
  int m_length{0};
  int* m_array{nullptr};

public:
  friend std::ostream& operator<<(std::ostream& out, IntArray& array);

  explicit IntArray(int length) : m_length{length} {
    assert(length > 0);

    m_array = new int[static_cast<std::size_t>(length)];
  }

  IntArray(IntArray& intArray)
      : m_length{intArray.m_length}, m_array{intArray.m_array} {

    deepCopy(intArray);
  }

  ~IntArray() { delete[] m_array; }

  IntArray& operator=(IntArray& intArray);

  void deepCopy(IntArray& intArray) {

    m_length = intArray.m_length;

    if (intArray.m_array) {

      m_array = new int[static_cast<std::size_t>(m_length)];

      for (int i{0}; i < m_length; ++i)
        m_array[i] = intArray.m_array[i];

    } else
      m_array = nullptr;
  }

  int& operator[](int idx) { return m_array[idx]; }
};

std::ostream& operator<<(std::ostream& out, IntArray& array) {
  for (std::size_t count{0}; count < array.m_length; ++count) {
    out << array.m_array[static_cast<int>(count)] << " ";
  }
  return out;
}
IntArray& IntArray::operator=(IntArray& other) {
  if (this == &other) {
    return *this;
  }
  if (m_array) {
    delete[] m_array;
  }
  m_length = other.m_length;

  m_array = new int[static_cast<std::size_t>(m_length)];
  if (other.m_array) {
    for (int i{0}; i < m_length; ++i) {
      m_array[i] = other.m_array[i];
    }
  } else {
    m_array = nullptr;
  }
  return *this;
}

int main() {
  IntArray arr1(3);
  arr1[0] = 10;
  arr1[1] = 20;
  arr1[2] = 30;
  std::cout << "arr1: " << arr1 << '\n';

  IntArray arr2(arr1);
  std::cout << "arr2 (copied from arr1): " << arr2 << '\n';

  arr1[0] = 99;
  std::cout << "\nAfter modifying arr1[0] to 99:\n";
  std::cout << "arr1: " << arr1 << '\n';
  std::cout << "arr2 (should still start with 10): " << arr2 << '\n';

  IntArray arr3(5);
  arr3 = arr2;
  std::cout << "\narr3 (assigned from arr2): " << arr3 << '\n';

  arr3 = arr3;
  std::cout << "arr3 after self-assignment: " << arr3 << '\n';

  return 0;
}
