#include <iostream>
#include "ArrayInt.h"
#include <vector>


class Card
{
public:
    enum rank {
        ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        JACK, QUEEN, KING
    };
    enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };

    Card(rank r = ACE, suit s = SPADES, bool ifu = true);
    int GetValue() const;
    void Flip();

private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

Card::Card(rank r, suit s, bool ifu) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu)
{}

int Card::GetValue() const
{
    int value = 0;
    if (m_IsFaceUp)
    {
        value = m_Rank;
        if (value > 10)
        {
            value = 10;
        }
    }
    return value;
}

void Card::Flip()
{
    m_IsFaceUp = !(m_IsFaceUp);
}


// Task 3. Реализовать класс Hand, который представляет собой коллекцию карт.В классе будет одно поле : вектор указателей карт(удобно использовать вектор, 
   // т.к.это по сути динамический массив, а тип его элементов должен быть - указатель на объекты класса Card).Также в классе Hand должно быть 3 метода :
   //       метод Add, который добавляет в коллекцию карт новую карту, соответственно он принимает в качестве параметра указатель на новую карту
   //       метод Clear, который очищает руку от карт
   //       метод GetValue, который возвращает сумму очков карт руки(здесь предусмотреть возможность того, что туз может быть равен 11).

class Hand
{
public:
    Hand();
    virtual ~Hand();

   void Add(Card* pCard);
   void Clear();
   int GetTotal() const;

protected:
    std::vector<Card*> m_Cards;
};

Hand::Hand()
{
    m_Cards.reserve(7);
}

Hand::~Hand()
{
    Clear();
}

void Hand::Add(Card* pCard)
{
    m_Cards.push_back(pCard);
}

void Hand::Clear()
{
    std::vector<Card*>::iterator iter = m_Cards.begin();
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        delete* iter;
        *iter = 0;
    }
    m_Cards.clear();
}


int Hand::GetTotal() const
{
    // проверяет, пустая ли рука
    if (m_Cards.empty())
    {
        return 0;
    }

    // находит сумму очков всех карт (тузу в enum присвоено значение 1)
    int total = 0;
    std::vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        total += (*iter)->GetValue();
    }

    // определяет, держит ли рука туз
    bool containsAce = false;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        if ((*iter)->GetValue() == Card::ACE)
        {
            containsAce = true;
        }
    }

    // если сумма меньше или =11, туз можно считать за 11. 1 очко мы уже за него посчитали, теперь добавим еще 10
    if (containsAce && total <= 11)
    {
        total += 10;
    }

    //по хорошему надо что-то сделать с остальными тузами, их все-таки 4 в колоде, но я уже запуталась. Кажется, если более одного туза,
    //такую проверку даже не надо проводить в принципе, и жестко считать второй и далее за 1 очко. Иначе сразу будет перебор и проигрыш.

    return total;
}


int main()
{
    std::cout << "Task 1. " << std::endl;
    std::cout << '\n';
   

    // Task  1. Добавить в контейнерный класс, который был написан в этом уроке, методы:
    //         для удаления последнего элемента массива(аналог функции pop_back() в векторах)
    //         для удаления первого элемента массива(аналог pop_front() в векторах)
    //         для сортировки массива
    //         для вывода на экран элементов.
    // см. ArrayInt.h
    
    ArrayInt array1;
    array1.push_back (10);
    array1.push_back(9);
    array1.push_back(8);
    array1.push_back(7);
    array1.push_back(6);
    array1.push_back(5);
    array1.push_back(4);
    array1.push_back(3);
    array1.push_back(2);
    array1.push_back(1);
    std::cout << "Original massiv:" << std::endl;
    array1.printArray();

    // для удаления последнего элемента массива(аналог функции pop_back() в векторах)
    std::cout << "Last element deleted:" << std::endl;
    array1.deleteLast();
    array1.printArray();

    // для удаления первого элемента массива(аналог pop_front() в векторах)
    std::cout << "First element deleted:" << std::endl;
    array1.deleteFirst();
    array1.printArray();

    // для сортировки массива. Тоже непонятно, как сортировать, сделала по возрастарнию, это непринципиально, наверно. 
    std::cout << "Ascending order:" << std::endl;
    array1.sortAscending();
    array1.printArray();

    // для вывода на экран элементов.
    // тут я не очень понеяла,элементов по одному или всех, поэтому два варианта

    std::cout << "Single element:" << std::endl;
    array1.printElement(2);
    std::cout << "All elements:" << std::endl;
    array1.printArray();


    std::cout << '\n';
    std::cout << '\n';
    std::cout << "Task 2. " << std::endl;
    std::cout << '\n';
    
    // Task 2. Дан вектор чисел, требуется выяснить, сколько среди них различных. Постараться использовать максимально быстрый алгоритм.

    std::vector <int> vectorTest = { 1,2,1,2,3,4,1 };
    std::vector <int> vectorTemp = vectorTest;   // создаем временно идентичный вектор
    

    // Вывод вектора
    int lenght = vectorTest.size();
    std::cout << "VectorTest  " << std::endl;
    for (int index = 0; index < lenght; ++index)
    {
        std::cout << vectorTest[index] << " ";
    }
    std::cout << '\n';

    // Сравниваем числа во временном векторе, дубликаты удаляем
    for (auto base = vectorTemp.begin(); base != vectorTemp.end(); ++base)
    {
        for (auto it = base + 1; it != vectorTemp.end(); )
        {
            if (*base == *it)
            {
                it = vectorTemp.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
    // Вывод временного вектора для удобства проверки
    int lenghtTmp = vectorTemp.size();
    std::cout << "VectorTemp  " << std::endl;
    for (int index = 0; index < lenghtTmp; ++index)
    {
        std::cout << vectorTemp[index] << " ";
    }
    std::cout << '\n';

    // вывод результата
    if (vectorTemp.size() == 1)
        std::cout << "In this vector, all the numbers are the same." << std::endl;
    else
    {
        std::cout << "In this vector are " << vectorTemp.size() << " identical numbers" << std::endl;
    }
    vectorTemp.~vector(); // удаляем временный вектор, чтобы не засорять память


    return 0;
}

