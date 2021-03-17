
#ifndef ARRAYINT_H
#define ARRAYINT_H

#include <cassert>
#include <iostream>
#include <algorithm>

class ArrayInt
{
private:
    int m_length;
    int* m_data;

public:
    ArrayInt() : m_length(0), m_data(nullptr)
    { }

    ArrayInt(int length) :
        m_length(length)
    {
        assert(length >= 0);

        if (length > 0)
            m_data = new int[length];
        else
            m_data = nullptr;
    }

    ~ArrayInt()
    {
        delete[] m_data;
    }


    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }
    int getLength() { return m_length; }

    int& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }
    void resize(int newLength)
    {
        if (newLength == m_length)
            return;
        if (newLength <= 0)
        {
            erase();
            return;
        }
        int* data = new int[newLength];
        if (m_length > 0)
        {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;
            for (int index = 0; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }
        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        assert(index >= 0 && index <= m_length);
        int* data = new int[m_length + 1];
        for (int before = 0; before < index; ++before)
            data[before] = m_data[before];

        data[index] = value;

        for (int after = index; after < m_length; ++after)
            data[after + 1] = m_data[after];
        delete[] m_data;
        m_data = data;
        ++m_length;
    }
    void push_back(int value) { insertBefore(value, m_length); };


    // 1.Добавить в контейнерный класс, который был написан в этом уроке, методы:
//         для удаления последнего элемента массива(аналог функции pop_back() в векторах)
//         для удаления первого элемента массива(аналог pop_front() в векторах)
//         для сортировки массива
//         для вывода на экран элементов.
    // для удаления последнего элемента массива(аналог функции pop_back() в векторах)

    void deleteLast()
    {
        // Проверка корректности длины массива - должна быть больше нуля, иначе при удалении элемента окажется отрицательной
        assert(m_length>0);

        // Создаем новый массив на один элемент меньше старого массива
        int* data = new int[m_length - 1];

        // Копируем все элементы, исключая последний
        for (int index = 0; index < (m_length - 1); ++index)
            data[index] = m_data[index];

        // Удаляем старый массив и используем вместо него новый 
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    // для удаления первого элемента массива(аналог pop_front() в векторах)
    void deleteFirst()
    {
        // Проверка корректности длины массива - должна быть больше нуля, т.к. при удалении элемента окажется отрицательной
        assert(m_length > 0);

        // Создаем новый массив на один элемент меньше старого массива
        int* data = new int[m_length - 1];

        // Копируем все элементы, исключая первый
        for (int index = 0; index < (m_length - 1); ++index)
            data[index] = m_data[index + 1];

        // Удаляем старый массив и используем вместо него новый 
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    // для сортировки массива      
    void sortAscending() {
       for (int startIndex = 0; startIndex < m_length - 1; ++startIndex)
            {
                int smallestIndex = startIndex;

                for (int currentIndex = startIndex + 1; currentIndex < m_length; ++currentIndex)
                {
                    // Если мы нашли элемент, который меньше нашего наименьшего элемента,
                    if (m_data[currentIndex] < m_data[smallestIndex])
                        // то запоминаем его
                        smallestIndex = currentIndex;
                }

                // smallestIndex теперь наименьший элемент. 
                        // Меняем местами наше начальное наименьшее число с тем, которое мы обнаружили
                std::swap(m_data[startIndex], m_data[smallestIndex]);
            }

    };

    // для вывода на экран элементов - одиночный элемент
    void printElement(int m_length) {
        std::cout << m_data[m_length] << std::endl;
    };
    // для вывода на экран элементов - все элементы
    void printArray() {
        for (int index = 0; index < m_length; ++index)
        {
            std::cout << m_data[index] <<" ";
        }
        std::cout << '\n';
    };
    
};

#endif

