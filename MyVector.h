#ifndef DATASTRUCTURES_MYVECTOR_H
#define DATASTRUCTURES_MYVECTOR_H
#pragma once
#include <cstdlib>
#include <cmath>
// стратегия изменения capacity
enum class SortedStrategy {
    Ascending,
    Descending
};
enum class ResizeStrategy {
	Additive,
	Multiplicative
};

// тип значений в векторе
// потом будет заменен на шаблон

template<class ValueType>
class MyVector
{
public:
    class Iterator
    {
    public:
        Iterator(ValueType *ptr)
        {
            this->ptr = ptr;
        }
        ~Iterator()
        {

        }
        bool operator==(const Iterator &i)
        {
            return this->ptr == i.ptr;
        }
        bool operator!=(const Iterator &i)
        {
            return this->ptr != i.ptr;
        }
        Iterator &operator++()
        {
            this->ptr++;
            return *this;
        }
        Iterator &operator--()
        {
            this->ptr--;
            return *this;
        }
        ValueType operator*()
        {
            return *this->ptr;
        }
        ValueType *operator->()
        {
            return this->ptr;
        }
    private:
        ValueType* ptr;
        friend class MyVector;
    };
	MyVector(size_t size = 0, ResizeStrategy resizeStrategy = ResizeStrategy::Additive, float coef = 1.5f)
    {
        if (size == 0)
        {
            this->_size = size;
            this->_capacity = 1;
            this->_data = new ValueType[this->_capacity];
            this->_strategy = resizeStrategy;
            this->_coef = coef;
        }
        else
        {
            if (resizeStrategy == ResizeStrategy::Additive)
            {
                this->_size = size;
                this->_capacity = size + round(coef);
                this->_data = new ValueType[this->_capacity];
                this->_strategy = ResizeStrategy::Additive;
                this->_coef = coef;
            }
            else
            {
                this->_size = size;
                this->_capacity = round(size * coef);
                this->_data = new ValueType[this->_capacity];
                this->_strategy = ResizeStrategy :: Multiplicative;
                this->_coef = coef;
            }
        }
    }

	MyVector(size_t size, ValueType value, ResizeStrategy resizeStrategy = ResizeStrategy::Multiplicative, float coef = 1.5f)
    {
        if (size == 0)
        {
            this->_size = size;
            this->_capacity = 1;
            this->_data = new ValueType[_capacity];
            this->_strategy = resizeStrategy;
            this->_coef = coef;
        }
        else
        {
            if (resizeStrategy == ResizeStrategy::Additive)
            {
                this->_size = size;
                this->_capacity = size + round(coef);
                this->_data = new ValueType[_capacity];
                this->_strategy = ResizeStrategy::Additive;
                this->_coef = coef;
                for (int i = 0; i < size; i++)
                {
                    this->_data[i] = value;
                }
            }
            else
            {
                this->_size = size;
                this->_capacity = round(size * coef);
                this->_data = new ValueType[_capacity];
                this->_strategy = ResizeStrategy::Multiplicative;
                this->_coef = coef;
                for (int i = 0; i < size; i++)
                {
                    this->_data[i] = value;
                }
            }
        }
    }

	MyVector(MyVector &&moveVec) noexcept
    {
        _data = moveVec._data;
        _size = moveVec._size;
        _capacity = moveVec._capacity;
        moveVec._data = nullptr;
        moveVec._capacity = 0;
        moveVec._size = 0;
    }

	MyVector(const MyVector& copy)
    {
        ValueType* newData = new ValueType[copy._capacity];
        for (int i = 0; i < copy._size; i++)
        {
            newData[i] = copy._data[i];
        }
        this->_data = newData;
        this->_strategy = copy._strategy;
        this->_capacity = copy._capacity;
        this->_size = copy._size;
    }

	MyVector& operator=(const MyVector& copy)
    {
        if (this == &copy)
            return *this;
        ValueType* newData = new ValueType[copy._capacity];
        for (int i = 0; i < copy._size; i++)
        {
            newData[i] = copy._data[i];
        }
        delete[] this->_data;
        this->_data = newData;
        this->_strategy = copy._strategy;
        this->_capacity = copy._capacity;
        this->_size = copy._size;
        this->_coef = copy._coef;
        return *this;
    }

	~MyVector()
    {
        delete[] _data;
    }

	// для умненьких — реализовать конструктор и оператор для перемещения

	size_t capacity() const
	{
	    return _capacity;
	}

	size_t size() const
    {
        return _size;
    }
	float loadFactor()
    {
        if (this->_capacity == 0)
            return 0;
        else
            return (float)this->_size / this->_capacity;
    }

	// доступ к элементу, 
	// должен работать за O(1)
	ValueType& operator[](const size_t i)
    {
        return this->_data[i];
    }
    ValueType& operator[](const size_t i) const
    {
        return const_cast<ValueType>(this->_data[i]);
    }

	// добавить в конец,
	// должен работать за amort(O(1))
	void pushBack(const ValueType& value)
    {
        if(this->_capacity < this->_size + 1)
        {
            reserve(this->_capacity + 1);
        }
        this->_data[this->_size] = value;
        this->_size++;
    }
	// вставить,
	// должен работать за O(n)
	void insert(const size_t i, const ValueType& value)
    {
        if (_size + 1 < _capacity)
        {
            this->reserve(_capacity + 1);
        }
        _size++;
        for (int j = this->_sise - 1; j > i; j--)
        {
            this->_data[j] =  this->_data[j - 1];
        }
        this->_data[i] = value;
    }// версия для одного значения
	void insert(const size_t i, const MyVector& value)
    {
        if (_size +value._size < _capacity)
        {
            this->reserve(_size + value._size);
        }
        this->_size = this->_size +value._size;

        for (int j = _size; j > i; j--)
            this->_data[j] = this->_data[j - value._size];


        for (size_t j = i; j < i + value._size; j++)
            this->_data[j] = value._data[value._size - i];
    }

	// удалить с конца,
	// должен работать за amort(O(1))
	void popBack()
    {
        this->_size--;
    }
	void popFront()
    {
        this->_size--;
        ValueType* newData = new ValueType[this->_capacity];
        for(int i = 1; i < this->_size + 1; i++)
        {
            newData[i - 1] = this->_data[i];
        }
        delete[] this->_data;
        this->_data = newData;
    }
	// удалить
	// должен работать за O(n)
	void erase(const size_t i)
    {
        ValueType* newData = new ValueType[this->_capacity];
        for (int j = 0; j < i; j++)
        {
            newData[j] = this->_data[j];
        }
        for (int j = i; j < this->_size - 1; j++)
        {
            newData[j] = this->_data[j + 1];
        }
        delete[] this->_data;
        this->_data = newData;
        this->_size--;
    }
	void erase(const size_t i, const size_t len)
    {
        ValueType* newData = new ValueType[this->_capacity];
        for (int j = 0; j < i; j++)
        {
            newData[j] = this->_data[j];
        }
        for (int j = i; j < this->_size - len; j++)
        {
            newData[j] = this->_data[j+ len];
        }
        delete[] this->_data;
        this->_data = newData;
        this->_size-= len;
    }// удалить len элементов начиная с i

	// найти элемент,
	// должен работать за O(n)
	// если isBegin == true, найти индекс первого элемента, равного value, иначе последнего
	// если искомого элемента нет, вернуть -1
	long long int find(const ValueType& value, bool isBegin = true) const
    {
        if (isBegin)
        {
            for (size_t i = 0; i < this->_size; i++)
            {
                if (this->_data[i] == value)
                    return i;
            }
            return -1;
        }
        else
        {
            for (size_t i = this->_size - 1; i > -1; i--)
            {
                if (this->_data[i] == value)
                    return i;
            }
            return -1;
        }
    }

	// зарезервировать память (принудительно задать capacity)
	void reserve(const size_t capacity)
    {
        if (capacity < this->_size)
        {
            this->_size = capacity;
            this->_capacity = capacity;
        }
        else
            this->_capacity = capacity;
        ValueType* newData = new ValueType[capacity];
        for (int i = 0; i < this->_size; i++)
        {
            newData[i] = this->_data[i];
        }
        delete[] this->_data;
        this->_data = newData;
    }

	// изменить размер
	// если новый размер больше текущего, то новые элементы забиваются дефолтными значениями
	// если меньше - обрезаем вектор
	void resize(const size_t size, const ValueType value)
    {
        if (this->_size == size)
            return;
        if (this->_size < size)
        {
            ValueType* newData = new ValueType[size];
            for (int i = 0; i < this->_size; i++)
            {
                newData[i] = this->_data[i];
            }
            for (int i = this->_size; i < size; i++)
            {
                newData[i] = value;
            }
            delete[] this->_data;
            this->_data = newData;
            this->_size = size;
        }
        if (this->_size > size)
        {
            ValueType* newData = new ValueType[size];
            for (int i = 0; i < size; i++)
            {
                newData[i] = this->_data[i];
            }
            delete[] this->_data;
            this->_data = newData;
            this->_size = size;
            this->_capacity = size;
        }
    }

	// очистка вектора, без изменения capacity
	void clear()
    {
        this->_size = 0;
        delete[] this->_data;
        this->_data = new ValueType [this->_capacity];
    }
	Iterator begin()
    {
        return Iterator(&this->_data[0]);
    }
	Iterator end()
    {
        return Iterator(&this->_data[this->_size - 1]);
    }
	const Iterator cbegin()
    {
        return Iterator(&this->_data[0]);
    }
	const Iterator cend()
    {
        return Iterator(&this->_data[_size - 1]);
    }
	ValueType getValue(Iterator i)
    {
        return *i.ptr;
    }
	void setValue(Iterator i, ValueType value)
    {
        *i.ptr = value;
    }
    void sortedSquares(SortedStrategy strategy)
    {
        ValueType* vec  = new ValueType[this->_size];
        if (strategy == SortedStrategy::Descending)
        {
            int i = 0;
            int j = this->size() - 1;
            int k = 0;
            while(this->_data[i] < 0 && this->_data[j] >= 0)
            {
                if (abs(this->_data[i]) >= abs(this->_data[j]))
                {
                    vec[k] = this->_data[i] * this->_data[i];
                    i++;
                    k++;
                }
                else
                {
                    vec[k] = this->_data[j] * this->_data[j];
                    j--;
                    k++;
                }
            }
            while(this->_data[i] < 0)
            {
                vec[k] = this->_data[i] * this->_data[i];
                i++;
                k++;
            }
            while(this->_data[j] >= 0)
            {
                vec[k] = this->_data[j] * this->_data[j];
                j--;
                k++;
            }
        }
        else
        {

            int i = 0;
            int j = this->size() - 1;
            int k = this->size() - 1;
            while(this->_data[i] < 0 && this->_data[j] >= 0)
            {
                if (abs(this->_data[i]) >= abs(this->_data[j]))
                {
                    vec[k] = this->_data[i] * this->_data[i];
                    //std:: cout << vector._data[k] << std::endl;
                    i++;
                    k--;
                }
                else
                {
                    vec[k] = this->_data[j] * this->_data[j];
                    //std:: cout << vector._data[k] << std:: endl;
                    j--;
                    k--;
                }
            }
            while(this->_data[i] < 0)
            {
                vec[k] = this->_data[i] * this->_data[i];
                i++;
                k--;
            }
            while(this->_data[j] >= 0)
            {
                vec[k] = this->_data[j] * this->_data[j];
                j--;
                k--;
            }
        }
        delete[] this->_data;
        this->_data = vec;
    }
    ValueType* _data;
    size_t _size;
    size_t _capacity;
    ResizeStrategy _strategy;
    float _coef;
//private:
//	ValueType* _data;
//	size_t _size;
//	size_t _capacity;
//	ResizeStrategy _strategy;
//	float _coef;
};
#endif //DATASTRUCTURES_LISTSTACK_H
