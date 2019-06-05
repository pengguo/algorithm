/*
 * check_dup.h
 *
 *  Created on: 2013-7-14
 *      Author: guopeng01
 */

#ifndef CHECK_DUP_H_
#define CHECK_DUP_H_

template <typename T>
class SpeicalQueue
{
public:
	SpeicalQueue(unsigned _cap):capbilty(_cap),idx(0),size(0)
	{
		assert(capbilty > 0);
		array = new T[capbilty];
		hash = new T[capbilty];
		// init, cannot be i+1 in hash[i]
		for (unsigned i = 0; i < capbilty; ++i)
		{
			hash[i] = i + 1;
		}
	}
	virtual ~SpeicalQueue()
	{
		delete [] array;
		array = NULL;
		delete [] hash;
		hash = NULL;
	}
	bool Push(const T &item)
	{
		if (size < capbilty) // not full
		{
			array[idx] = item;
			size++;
			unsigned curr_hash_idx = item%capbilty;
			hash[curr_hash_idx] = item;
			idx = (idx+1)%capbilty;
		}
		else // full, replace
		{
			const T &pre_item = array[idx];
			unsigned pre_hash_idx = pre_item%capbilty;
			hash[pre_hash_idx] = pre_hash_idx + 1; // init
			array[idx] = item;
			unsigned curr_hash_idx = item%capbilty;
			hash[curr_hash_idx] = item;
			idx = (idx+1)%capbilty;
		}
		return true;
	}
	bool IsDup(const T &item)
	{
		unsigned hash_idx = item % capbilty;
		bool flag = false;
		if (item == hash[hash_idx])
			flag = true;
		else
			flag = false;
		return flag;
	}
	void ToString() const
	{
		std::cout << "------begin display queue_item-----------" << std::endl;
		for (unsigned i = 0; i < size; i++)
		{
			std::cout << array[i] << ",";
		}
		std::cout << std::endl;

		std::cout << "------begin display hash_item-----------" << std::endl;
		for (unsigned i = 0; i < size; i++)
		{
			std::cout << hash[i] << ",";
		}
		std::cout << std::endl;
	}
private:
	unsigned capbilty;
	unsigned idx;
	unsigned size;
	T *array; // store item
	T *hash; // dup_flag
};

void TestDup()
{
	SpeicalQueue<unsigned> queue(10);
	unsigned item = 3;
	queue.Push(item);
	item = 4;
	queue.Push(item);
	item = 2;
	queue.Push(item);
	item = 5;
	queue.Push(item);
	item = 7;
	queue.Push(item);
	item = 6;
	queue.Push(item);
	item = 8;
	queue.Push(item);
	item = 10;
	queue.Push(item);
	item = 9;
	queue.Push(item);
	item = 12;
	queue.Push(item);
	item = 11;
	queue.Push(item);
	queue.ToString();

	item = 4;
	std::cout << queue.IsDup(item) << std::endl;
	item = 13;
	std::cout << queue.IsDup(item) << std::endl;
	queue.Push(item);
	std::cout << queue.IsDup(item) << std::endl;
	queue.ToString();
}

#endif /* CHECK_DUP_H_ */
