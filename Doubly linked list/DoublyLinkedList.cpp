#include <iostream>


struct DoubleLinkedListItem
{
    DoubleLinkedListItem* pPrevious;
    int item;
    DoubleLinkedListItem* pNext;
};

class DoubleLinkedList
{
private:
    DoubleLinkedListItem* pFirstItem;
    DoubleLinkedListItem* pLastItem;
    unsigned long long int size = 0;
    
public:
    DoubleLinkedList()
    : pFirstItem(nullptr)
    , pLastItem(nullptr)
    { }
    
    bool is_empty()
    {
        return size == 0;
    }
    
    unsigned long long int getLenght()
    {
        return size;
    }
    
    void push_front(int new_item)
    {
        DoubleLinkedListItem* tmp = new DoubleLinkedListItem;   // создание новой переменной
        tmp->item = new_item;                                   // инициализация новой переменной (указание значения)
        if (is_empty())                                         // если список пуст:
        {
            tmp->pNext = tmp;                                        // то адрес следующего элемента укажет на первый элемент (то есть на самого себя)
            tmp->pPrevious = tmp;                                    // то адрес предыдущего элемента укажет на первый элемент (то есть на самого себя)
            pLastItem = tmp;                                         // новая переменная становится последней в списке (либо первой в изначально пустом);
        }
        else                                                    // если список не пуст:    
        {
            tmp->pNext = pFirstItem;                                  // адрес первого элемента становится следующим для текущего
            tmp->pPrevious = pLastItem;                               // адрес последнего элемента становится предыдущим для текущего
            pFirstItem->pPrevious = tmp;
        }
        pFirstItem = tmp;                                        // новая переменная становится первой в списке (либо первой в изначально пустом);
        size++;                                                 // увеличение размера списка
    }
    
    void push_back(int new_item)
    {
        DoubleLinkedListItem* tmp = new DoubleLinkedListItem;   // создание новой переменной
        tmp->item = new_item;   // инициализация новой переменной (указание значения)
        if (is_empty())
        {
            tmp->pNext = tmp;
            tmp->pPrevious = tmp;
            pFirstItem = tmp;
        }
        else
        {
            tmp->pNext = pFirstItem;
            tmp->pPrevious = pLastItem;
            pLastItem->pNext = tmp;
        }
        pLastItem = tmp; // новая переменная становится последней в списке (либо первой в изначально пустом);
        size++;
    }
    
    void push_index(int new_item, long long int index = -1)
    {
        DoubleLinkedListItem* tmp = new DoubleLinkedListItem;
        tmp->item = new_item;
        
        if (is_empty())
        {
            tmp->pNext = tmp;
            tmp->pPrevious = tmp;
            pFirstItem = tmp;
            pLastItem = tmp;
            size++;
        }
        else
        {
            if (index < 0)
            {
                if ((-index - 1) % size == 0)
                {
                    index = size;
                }
                else
                {
                    index = size - (-index % size) + 1;
                }
            }
            else if (index > size)
            {
                if (index % size == 0)
                {
                    index = size;
                }
                else
                {
                    index = index % size;
                }
            }
            DoubleLinkedListItem* curentItem = getItem(index);

            if (index == 0)
            {
               push_front(new_item);
               pLastItem->pNext = pFirstItem;
            }
            else if (index == size)
            {
                push_back(new_item);
                pFirstItem->pPrevious = pLastItem;
            }
            else
            {
                tmp->pNext = curentItem;
                tmp->pPrevious = curentItem->pPrevious;
            
                curentItem->pPrevious->pNext = tmp;
                curentItem->pPrevious = tmp;
                size++;
            }
        }
    }
    
    void pop_front()                                                                                      
    {
        if (size == 1)
        {
            delete pFirstItem;
            pFirstItem = nullptr;
            delete pLastItem;
            pLastItem = nullptr;
            size--;
        }
        else if (size > 1)
        {
            DoubleLinkedListItem* tmp = pFirstItem->pNext;
            delete pFirstItem;
            pFirstItem = tmp;
            pFirstItem->pPrevious = pLastItem;
            pLastItem->pNext = pFirstItem;
            size--;
        }
    }
    
    void pop_back()
    {
        if (size == 1)
        {
            delete pFirstItem;
            pFirstItem = nullptr;
            delete pLastItem;
            pLastItem = nullptr;
            size--;
        }
        else if (size > 1)
        {
            DoubleLinkedListItem* tmp = pLastItem->pPrevious;
            delete pLastItem;
            pLastItem = tmp;
            pLastItem->pNext = pFirstItem;
            pFirstItem->pPrevious = pLastItem;
            size--;
        }
    }
    
    void pop_index(long long int index)
    {
        if (index < 0)
        {
            index = (size - (std::abs(index) % size)) % size;
        }
        else if (index >= size)
        {
            index = index % size;
        }
        DoubleLinkedListItem* currentItem = getItem(index);
        if (index == 0)
        {
            pop_front();
        }
        else if (index == size)
        {
            pop_back();
        }
        else
        {
            currentItem->pPrevious->pNext = currentItem->pNext;
            currentItem->pNext->pPrevious = currentItem->pPrevious;
            delete currentItem;
            size--;
        }
    }
    
    void displayList()
    {
        DoubleLinkedListItem* currentItem =  pFirstItem;
        unsigned long long int index = size;
        while (index--)
        {
            std::cout << currentItem->item << " ";
            currentItem = currentItem->pNext;
        }
        std::cout << std::endl;
    }
    
    DoubleLinkedListItem* getItem(long long int index)
    {
        DoubleLinkedListItem* currentItem = pFirstItem;
        if (index < 0)
        {
            index = (size - (std::abs(index) % size)) % size;
        }
        else if (index >= size)
        {
            index = index % size;
        }
        while(index--)
        {
            currentItem = currentItem->pNext;
        }
        return currentItem;
    }
    
    void slideLeft(unsigned long long int step)
    {
        DoubleLinkedListItem* curentItem = getItem(step);
        pFirstItem = curentItem;
        pLastItem = curentItem->pPrevious;
    }
    
    void slideRight(unsigned long long int step)
    {
        if (step >= size)
        {
            step = step  % size;
        }
        slideLeft(size - step);
    }
};
    


int main()
{
    DoubleLinkedList pDLL;
    
    pDLL.push_back(4);
    pDLL.push_front(3);
    pDLL.push_back(5);
    pDLL.push_front(2);
    pDLL.push_back(6);
    pDLL.push_front(1);
    pDLL.push_back(7);
    pDLL.push_front(0);
    pDLL.push_back(8);
    pDLL.push_front(-1);
    pDLL.push_back(9);
    pDLL.push_back(10);
    
    
    std::cout << "lenght = " << pDLL.getLenght() << ":" << std::endl;
    pDLL.displayList();
    
    pDLL.pop_back();
    std::cout << "lenght = " << pDLL.getLenght() << ":" << std::endl;
    pDLL.displayList();
    
    pDLL.pop_front();
    std::cout << "lenght = " << pDLL.getLenght() << ":" << std::endl;
    pDLL.displayList();
    
    std::cout << "item 24 = " << pDLL.getItem(24)->item << std::endl;
    std::cout << "item -26 = " << pDLL.getItem(-26)->item << std::endl;
    
    pDLL.push_index(666, 5);
    std::cout << "lenght = " << pDLL.getLenght() << ":" << std::endl;
    pDLL.displayList();
    
    pDLL.pop_index(5);
    std::cout << "lenght = " << pDLL.getLenght() << ":" << std::endl;
    pDLL.displayList();
    
    pDLL.slideRight(4);
    std::cout << "lenght = " << pDLL.getLenght() << ":" << std::endl;
    pDLL.displayList();
    
    pDLL.slideLeft(4);
    std::cout << "lenght = " << pDLL.getLenght() << ":" << std::endl;
    pDLL.displayList();
    
    // std::cout << std::endl;
    // std::cout << std::endl;
    // for (int i = 0; i < pDLL.getLenght(); i++)
    // {
        
        // std::cout << pDLL.getItem(i)->pPrevious->item << " " << pDLL.getItem(i)->item << " " << pDLL.getItem(i)->pNext->item << std::endl;
    // }
    
    // std::cout << std::endl;
    // std::cout << std::endl;
    // DoubleLinkedList test_list = DoubleLinkedList();
    // int n = 12;
    // for(int i = 1; i <= n; i++)
    // {
        // test_list.push_index(i, n);
        // test_list.displayList();
    // }
    
    // std::cout << std::endl;
    
    // for(int i = 1; i <= n; i++)
    // {
        // test_list.pop_front();
        // test_list.displayList();
    // }
    
    // std::cout << test_list.is_empty() << std::endl;
    
    
    return 0;
};





