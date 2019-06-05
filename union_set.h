/*
 * union_set.h
 *
 *  Created on: 2013-6-28
 *      Author: guopeng01
 */

#ifndef UNION_SET_H_
#define UNION_SET_H_

#include <stdio.h>

int hash_idx[16] = {0, 0};
int MakeHash(int key)
{
	int idx = key % 16;
	if (0 == hash_idx[idx]) // not taken
	{
	    hash_idx[idx] = key;
	    return idx;
	}
	else // hash 冲突
	{
		while (idx < 16)
		{
			if (0 == hash_idx[++idx])
			{
				hash_idx[idx] = key;
				return idx;
			}
		}
	}
}

// 解决hash冲突： 线性探测\伪随机序列、
// 线性补偿法 （算法中的 j ＝ (j ＋ 1) % m 改为： j ＝ (j ＋ Q) % m ，而且要求 Q 与 m 是互质的，以便能探测到哈希表中的所有单元）
int duplicat_1(int key)
{
	int idx = key % 16;
	idx += 1;
	while ((0 != hash_idx[idx]) && (idx < 16))
		idx++;
	if (idx < 16)
	{
		hash_idx[idx] = key;
		return idx;
	}
	return -1;
}

typedef struct hash_node
{
	int key;
	struct hash_node *next;
} HashNode;

// return: 0: do not have this key
int GetHashIdx(int key)
{
	int idx = key % 16;
	if (key == hash_idx[idx])
		return idx;
	else
	{
		idx += 1;
		while (idx < 16)
		{
			if (key == hash_idx[idx])
				return idx;
			else if (0 == hash_idx[idx])
				return 0;
			else
				idx++;
		}
	}
}

static const unsigned MAX = 1024;

int father[MAX];
int rank[MAX];

void Make_Set(int x)
{
    father[x] = x;
    rank[x] = 0; //理解为树的高度
}

/* 查找x元素所在的集合,回溯时压缩路径*/
int Find_Set(int x)
{
    if (x != father[x])
    {
    	father[x] = Find_Set(father[x]); //这个回溯时的压缩路径是精华
    }
    return father[x];
}

/*
 
按秩合并x,y所在的集合
下面的那个if else结构不是绝对的，具体根据情况变化
但是，宗旨是不变的即，按秩合并，实时更新秩。
*/
void Union(int x, int y)
{
    x = Find_Set(x);
    y = Find_Set(y);

    if (x == y) return;

    if (rank[x] > rank[y])
    {
    	father[y] = x;
    }
    else
    {
    	father[x] = y;
    	if (rank[x] == rank[y])
    	{
    		rank[y]++;
    	}
    }
}

#endif /* UNION_SET_H_ */
