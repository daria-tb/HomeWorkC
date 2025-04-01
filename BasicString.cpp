#include <iostream>

template <class T> 
class BasicString
{
public:
	BasicString() : data(new T[1]), len(0), cap(1)
	{
		data[0] = '\0';
	}

	BasicString(const T* str) : len(std::strlen(str))
	{
		cap = len + 1;
		data = new T[cap];
		std::memcpy(data, str, len + 1);
	}

	BasicString(const BasicString& other)
	{
		len = other.len;
		cap = other.cap;
		data = new T[cap];
		std::memcpy(data, other.data, len + 1);
	}

	BasicString(BasicString&& other) noexcept : data(other.data), len(other.len), cap(other.cap)
	{
		other.data = nullptr;
		other.len = 0;
		other.cap = 0;
	}

	~BasicString()
	{
		delete[] data;
	}

	BasicString& operator=(const BasicString& other)
	{
		if (this != &other)
		{
			delete[] data;
			len = other.len;
			cap = other.cap;
			data = new T[cap];
			std::memcpy(data, other.data, len + 1);
		}
		return *this;
	}

	BasicString& operator=(BasicString&& other) noexcept
	{
		if (this != &other)
		{
			delete[] data;
			data = other.data;
			len = other.len;
			cap = other.cap;
			other.data = nullptr;
			other.len = 0;
			other.cap = 0;
		}
		return *this;
	}

	T& operator [](size_t index)
	{
		return data[index];
	}

	const T& operator [](size_t index) const
	{
		return data[index];
	}

	bool empty() const
	{
		return len == 0;
	}

	size_t size() const
	{
		return len;
	}

	size_t capacity() const
	{
		return cap;
	}

	void append(const T* str)
	{
		size_t addLen = std::strlen(str);
		resize(len + addLen + 1);
		std::memcpy(data + len, str, addLen + 1);
		len += addLen;
	}

	int find(const T* str) //str == "wor"
	{
		//this
		
		size_t strLen = std::strlen(str);
		
		if (len < strLen) return -1;

		
		for (int i = 0; i < len - strLen; i++)
		{
			//if(std::memcmp(data + i, str, strLen) == 0))
			int j = 0;
			if (str[j] == data[i])
			{
				while (j < strLen)
				{
					if (str[j++] != data[i++])
						break;
				}
				if (j == strLen)
					return i - j;
				else
				{
					i--; //may be
					continue;
				}
			}
		}
		return -1;
	}

	friend BasicString<T> operator+(const BasicString<T>& left, const BasicString<T>& right)
	{
		BasicString<T> result;
		result.resize(left.len + right.len + 1);
		std::memcpy(result.data, left.data, left.len);
		std::memcpy(result.data + left.len, right.data, right.len + 1);
		result.len = left.len + right.len;
		return result;
	}

private:
	T* data;
	size_t len;
	size_t cap;


	void resize(size_t newCapacity)
	{
		if (newCapacity > cap)
		{
			T* newData = new T[newCapacity];
			std::memcpy(newData, data, len * sizeof(T));
			delete[] data;
			data = newData;
			cap = newCapacity;
		}
	}
};

int main()
{
	BasicString<char> string_{ "Goodby, world!!!!" };

	const char* str = "war";

	int pos = string_.find(str);

	std::cout << "index = " << pos << '\n';
}
/*
data = "Hello world!!!" = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!', '!', '!', '\0'  "               "}
                          [0]  [1]  [2]  [3]  [4]   [5]  [6]  [7]  [8]  [9]  [10] [11] [12] [13] 

"Goodbye world!!!"

str = "wor" return 6
str = "war" return -1

1) шукаємо перше входження першого символа з рядка str (str[0], нехай цей 0 буде позначатися індексом j) в рядок data;
2) якщо не знайшли - повертаємо -1
3) якщо знайшли (нехай його індекс буде дорівнювати i)
	3.1) чи співпадає str[j + 1] з символом data[i + 1]?
	3.2) якщо так, то j++, i++ та перейти до 3.1
	3.3) якщо ні - то перейти до 4)
4) шукаємо наступне входження першого символа з рядка str в рядок data
5) повторюємо кроки 2-3

*/
