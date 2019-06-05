/*
 * hash.h
 *
 *  Created on: 2013-7-1
 *      Author: guopeng01
 */

#ifndef HASH_H_
#define HASH_H_

/*
 * hash 函数， 用node解决冲突问题
 */
class HashClass
{
public:
	HashClass(int _size):size(_size) {}

public:
	typedef struct node_t
	{
		node_t():key(0), next(NULL) {}
		int key;
		struct node_t *next;
	} NODE_T;

	typedef struct idx_node_t
	{
		idx_node_t():cnt(0), list(NULL) {}
		int cnt;
		NODE_T *list;
	} IDX_NODE_T;

	void MakeHash()
	{
		head = new IDX_NODE_T[size];
		for (int i = 0; i < size; i++)
		{
			(head+i)->list = NULL;
			(head+i)->cnt = 0;
		}
	}

	int InsertHash(int key)
	{
		int idx = key % size;

		NODE_T *node = new NODE_T();
		node->key = key;

		if ((head+idx)->list == NULL)
		{
			(head+idx)->list = node;
		}
		else if ((head+idx)->list->key > key)
		{
			node->next = (head+idx)->list;
			(head+idx)->list = node;
		}
		else // 冲突，链表递增
		{
			NODE_T *pre = (head+idx)->list;
			NODE_T *ptr = (head+idx)->list;
			while (NULL != ptr && ptr->key < key)
			{
				pre = ptr;
				ptr = ptr->next;
			}

			node->next = pre->next;
			pre->next = node;
		}
		(head+idx)->cnt++;
		return idx;
    }

	bool GetHash(int key)
	{
		int idx = key % size;
		NODE_T *ptr = (head+idx)->list;
		while ((NULL != ptr) && (ptr->key <= key))
		{
			if (key == ptr->key)
				return true;
			ptr = ptr->next;
		}
		return false;
	}

	void DisplayHash(int key)
	{
		int idx = key % size;
		std::cout << "idx=" << idx << ",cnt=" << (head+idx)->cnt << std::endl;

		NODE_T *ptr = (head+idx)->list;
		while (NULL != ptr)
		{
			std::cout << ptr->key << std::endl;
			ptr = ptr->next;
		}
	}
	bool DelHash(int key)
	{
		int idx = key % size;
		NODE_T *ptr = (head+idx)->list;
		NODE_T *pre = NULL;
		if (NULL == ptr)
			return false;
		else if (key == ptr->key)
		{

	 		(head+idx)->list = ptr->next;
			(head+idx)->cnt--;
			delete ptr;
			ptr = NULL;
			return true;
		}
		else
		{
			do
			{
			    pre = ptr;
			    ptr = ptr->next;

			    if (key == ptr->key)
				{
					pre->next = ptr->next;
					(head+idx)->cnt--;
					delete ptr;
			        ptr = NULL;
			        return true;
				}
			} while ((NULL != ptr) && (ptr->key <= key));
			return false;
		}
	}

private:
	int size;
	IDX_NODE_T *head;
};

#endif /* HASH_H_ */

