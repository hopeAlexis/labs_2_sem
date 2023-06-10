#include <iostream>
#include <vector>

struct BitInfo {
	size_t byteIndex;
	unsigned char bitIndex;
};


template<>
class std::vector<bool> {
private:
	unsigned char* m_arr;
	size_t m_availableBytes; // amount of elements in the array
	size_t m_usedBits; // how much space is used

	BitInfo getBitInfo(size_t bitIndex)
	{
		return BitInfo
		{
			(size_t)(bitIndex / 8.0),
			(unsigned char)(bitIndex % 8)
		};
	}

	void set(unsigned char* byte, unsigned char index)	//1
	{
		*byte |= (1 << index);
	}

	void reset(unsigned char* byte, unsigned char index)	//0
	{
		*byte &= ~(1 << index);
	}

	bool check(unsigned char* byte, unsigned char index)
	{
		return (*byte & (1 << (index))) != 0;
	}

	void setBit(unsigned char* array, size_t bitIndex, bool value) 
	{

		BitInfo bitInfo = getBitInfo(bitIndex);
		unsigned char* byte = &array[bitInfo.byteIndex];

		if (value) {
			set(byte, bitInfo.bitIndex);
		}
		else {
			reset(byte, bitInfo.bitIndex);
		}
	}

	bool getBit(unsigned char* array, size_t bitIndex) 
	{
		BitInfo bitInfo = getBitInfo(bitIndex);
		return check(&array[bitInfo.byteIndex], bitInfo.bitIndex);
	}

public:
	std::vector<bool>() : m_arr(new unsigned char[1]), m_availableBytes(1), m_usedBits(0) {}

	void add(bool value)
	{
		setBit(m_usedBits, value);

		if (++m_usedBits == m_availableBytes * 8) 			// adds one byte if not enough space
		{
			unsigned char* temp = new unsigned char[++m_availableBytes];
			for (size_t i = 0; i < m_availableBytes - 1; i++) {
				temp[i] = m_arr[i];
			}

			delete[] m_arr;
			m_arr = temp;
		}
	}

	void insert(size_t bitIndex, bool value)	// insert a value by pushing all elements forward
	{
		if (m_usedBits + 1 == m_availableBytes * 8) {
			m_availableBytes++;
		}

		unsigned char* newArr = new unsigned char[m_availableBytes];
		size_t currentIndex = 0;
		while (currentIndex != bitIndex) {
			setBit(newArr, currentIndex, getBit(m_arr, currentIndex));
			currentIndex++;
		}

		setBit(newArr, currentIndex++, value);

		size_t j = bitIndex;
		while (j < m_usedBits) {
			setBit(newArr, currentIndex++, getBit(m_arr, j));
			j++;
		}

		m_usedBits++;

		delete[] m_arr;
		m_arr = newArr;
	}

	void erase(size_t startIndex, size_t endIndex) //delete values in a range
	{
		
		if (m_usedBits == 0 || endIndex >= m_usedBits || endIndex < startIndex) // error check
			throw std::exception();

		size_t bitsToRemove = endIndex - startIndex + 1;
		size_t newUsedBits = m_usedBits - bitsToRemove;
		size_t newAllocatedBytes = (size_t)std::ceill(newUsedBits / 8.0); // std::ceill computes the smallest integer value not less than the arguement

		unsigned char* newArr = new unsigned char[newAllocatedBytes];

		size_t newIndex = 0;
		for (size_t oldIndex = 0; oldIndex < m_usedBits; oldIndex++) {
			if (oldIndex < startIndex || oldIndex > endIndex) {
				setBit(newArr, newIndex++, getBit(m_arr, oldIndex));
			}
		}

		delete[] m_arr;

		m_arr = newArr;
		m_availableBytes = newAllocatedBytes;
		m_usedBits = newUsedBits;
	}

	size_t size()
	{
		return m_usedBits;
	}

	void setBit(size_t bitIndex, bool value)
	{
		setBit(m_arr, bitIndex, value);
	}

	bool getBit(size_t bitIndex)
	{
		return getBit(m_arr, bitIndex);
	}

	void print()
	{
		for (size_t i = 0; i < m_usedBits; i++) {
			std::cout << getBit(i);
		}
	}
};


int main() {

	std::vector<bool> vector;
	vector.add(true);					//1
	vector.add(false);					//10
	vector.insert(1, true);				//110
	vector.print();
	std::cout << "\n";

	vector.add(true);					//1101
	vector.add(true);					//11011
	vector.erase(1, 3);					//11
	vector.print();
	std::cout << "\n";

	vector.setBit(vector.size() - 1, false);		//10
	vector.print();
}