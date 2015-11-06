/*************************************************************************************

Program:			CS 4250 Assignment 3: 3D Roller Coaster

Author:				Alexander Bagnall
Email:				ab667712@ohio.edu

Description:		Interface/template file for the MinHeap class. This is based on
					a heap implementation I wrote for CS 3610. It is used by
					PathFinder in the implementation of Dijkstra's shortest path
					algorithm.

Date:				November 9, 2015

*************************************************************************************/

#ifndef MINHEAP_H
#define MINHEAP_H

#include <utility>
#include <vector>

namespace Bagnall
{
	template<class K, class V>
	class MinHeap
	{
	public:
		void Push(K key, V value)
		{
			// check for duplicate
			/*for (size_t i = 0; i < heap.size(); ++i)
			{
				if (heap[i].first == key)
				{
					return;
				}
			}*/

			heap.push_back(std::pair<K, V>(key, value));
			heapify_up(heap.size() - 1);
		}

		void ChangeValue(const K& key, V value)
		{
			for (size_t i = 0; i < heap.size(); ++i)
			{
				if (heap[i].first == key)
				{
					heap[i].second = value;
					heapify(i);
					return;
				}
			}
		}

		std::pair<K, V> Top() const
		{
			return heap[0];
		}

		void Pop()
		{
			if (!heap.size())
				return;

			iter_swap(heap.begin(), heap.begin() + heap.size() - 1);
			heap.pop_back();
			heapify_down(0);
		}

		std::size_t Size()
		{
			return heap.size();
		}

		void Clear()
		{
			heap.clear();
		}

	private:

		void heapify(int index)
		{
			heapify_up(index);
			heapify_down(index);
		}
		void heapify_up(int index)
		{
			int parent_index = (index - 1) / 2;
			if (parent_index >= 0 && parent_index != index)
			{
				if (heap[index].second < heap[parent_index].second)
				{
					iter_swap(heap.begin() + index, heap.begin() + parent_index);
					heapify_up(parent_index);
				}
			}
		}
		void heapify_down(int index)
		{
			size_t child_index;
			size_t left_child_index = 2 * index + 1;
			size_t right_child_index = left_child_index + 1;

			if (left_child_index >= heap.size())
				return;
			else if (right_child_index >= heap.size() ||
				heap[left_child_index].second < heap[right_child_index].second)
				child_index = left_child_index;
			else
				child_index = right_child_index;

			if (heap[child_index].second < heap[index].second)
			{
				iter_swap(heap.begin() + index, heap.begin() + child_index);
				heapify_down(child_index);
				return;
			}
		}

		std::vector<std::pair<K, V> > heap;
	};
}

#endif
