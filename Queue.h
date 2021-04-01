#pragma once
#define MemorySize 15           // Размер памяти по умолчанию
#include <iostream>
#include <fstream>
#include <string>

template <class T>
class queue {
protected:
    T*   pMem;                     
    int  hi;                       
    int  li;                       
    int  MemSize;                 
    int  DataCount;                
    int  GetNextIndex(int index);  

public:
    queue(int Size = MemorySize);
    ~queue();

    bool Empty(void) const;
    bool Full(void) const;
    void Put(const T& Val);
    int  Size()const;

    T Pop(void);
    T Back(void)const;
    T Front(void)const;

    void InFile(std::string file_name);
    void FromFile(std::string file_name);

    T FindMax(void);
    T FindMin(void);
    void Print(void);
};

template <class T>
queue<T>::queue(int Size)
{
    MemSize = Size;
    DataCount = 0;
    hi = -1;
    li = 0;
    pMem = new T[MemSize];
}

template<class T>
queue<T>::~queue()
{
    delete[] pMem;
    pMem = NULL;
}

template <class T>
int queue<T>::GetNextIndex(int index)
{
    return ++index % MemSize;
}

template <class T>
bool queue<T>::Full(void) const
{
    return DataCount == MemSize;
}

template <class T>
void queue<T>::Put(const T& Val)
{
    if (pMem == NULL) {
        throw std::logic_error("Cannot put element in queue: empty memory.");
    }
    else if (Full()) {
        throw std::logic_error("Cannot put element in queue: full queue.");
    }
    else {
        hi = GetNextIndex(hi);
        pMem[hi] = Val;
        DataCount++;
    }
}

template<class T>
inline int queue<T>::Size() const
{
    return DataCount;
}

template <class T>
bool queue<T>::Empty(void) const
{
    return DataCount == 0;
}

template <class T>
T queue<T>::Front()const
{
    if (pMem == NULL) {
        throw std::logic_error("Cannot get element from queue: empty memory.");
    }
    else if (Empty()) {
        throw std::logic_error("Cannot get element from queue: empty queue.");
    }
    else {
        return pMem[li];
    }
}

template <class T>
T queue<T>::Back()const
{
    if (pMem == NULL) {
        throw std::logic_error("Cannot get element from queue: empty memory.");
    }
    else if (Empty()) {
        throw std::logic_error("Cannot get element from queue: empty queue.");
    }
    else {
        return pMem[hi];
    }
}

template <class T>
T queue<T>::Pop()
{
    if (pMem == NULL) {
        throw std::logic_error("Cannot get element from queue: empty memory.");
    }
    else if (Empty()) {
        throw std::logic_error("Cannot get element from queue: empty queue.");
    }
    else {
        DataCount--;
        li = GetNextIndex(li);
        return pMem[li];
    }
}

template<class T>
void queue<T>::InFile(std::string file_name)
{
    std::fstream fs;
    fs.open(file_name, std::fstream::in | std::fstream::out);
    if (!fs.is_open())
    {
        std::cout << "Error open file!" << std::endl;
        return;
    }
    queue<T> tmp(MemSize);
    while (!Empty())
    {
        T val = Pop();
        tmp.Put(val);
        fs << val << " ";
    }
    while (!tmp.Empty())
    {
        Put(tmp.Pop());
    }
    std::cout << "File opened and rewritten!" << std::endl;
    fs.close();
}

template<class T>
void queue<T>::FromFile(std::string file_name)
{
    std::fstream fs;
    fs.open(file_name, std::fstream::in | std::fstream::out);
    if (!fs.is_open())
    {
        std::cout << "Error open file." << std::endl;
        return;
    }
    std::string str;
    getline(fs, str);

    char num[20];                   // Запись числа из файла
    int* nums = new int[MemSize];   // Храним числа из файла

    int j = 0, k = 0;  
    bool isNum = true;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ')
        {
            isNum = false;
            nums[k] = atoi(num);
            k++;
            j = 0;
            for (int m = 0; m < 20; m++)
            {
                num[m] = ' ';
            }
        }
        else { isNum = true; }

        if (isNum)
        {
            if((str[i] >= 48) && (str[i] <= 57))
            {
                num[j] = str[i];
                j++;
            }
            else
            {
                Put(str[i]);
                j++;
            }
        }
    }

    for (int i = 0; i < MemSize; i++)
    {
        try
        {
            Put(nums[i]);
        }
        catch(std::logic_error err)
        {
            break;
        }
    }

    std::cout << "File is open and read!" << std::endl;

    fs.close();
} 

template <class T>
inline T queue<T>::FindMax(void)
{
    queue<T> tmp(MemSize);
    T val = Pop();
    tmp.Put(val);
    while (!Empty())
    {
        if (val < Front())
        {
            val = Front();
        }
        tmp.Put(Pop());
    }
    while (!tmp.Empty())
    {
        Put(tmp.Pop());
    }

    return val;
}

template<class T>
inline T queue<T>::FindMin(void)
{
    queue<T> tmp(MemSize);
    T val = Pop();
    tmp.Put(val);
    while (!Empty())
    {
        if (val > Front())
        {
            val = Front();
        }
        tmp.Put(Pop());
    }
    while (!tmp.Empty())
    {
        Put(tmp.Pop());
    }

    return val;
}

template <class T>
void queue<T>::Print()
{
    for (int i = 0; i < DataCount; i++)
    {
        std::cout << pMem[i] << " ";
    }
    std::cout << "\n";
}