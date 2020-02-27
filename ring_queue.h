/*
Copyright (c) 2005-2020, Fishily Guo
Permission to use, copy, modify, and/or distribute this software
for any purpose with or without fee is hereby granted, provided
that the above copyright notice and this permission notice appear
in all copies.
THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <iostream>
using namespace std;

template<typename T> class CircleQueue
{
private:
	unsigned int	m_size;
	int				m_front;
	int				m_rear;
	T*				m_data;
public:
	CircleQueue(unsigned int size)
	{
		m_front = 0;
		m_rear	= 0;
		m_size	= size + 1;
		m_data	= new T[m_size + 1];
	}
	~CircleQueue()
	{
		delete[] m_data;
	}
	bool isEmpty()
	{
		return m_front == m_rear;
	}
	bool isFull()
	{
		return m_front == (m_rear + 1) % m_size;
	}
	void push(T data)
	{
		if (isFull())
		{
			throw "The queue is full, cannot keep pushing.";
		}
		m_data[m_rear] = data;
		m_rear = (m_rear + 1) % m_size;
	}
	void pop()
	{
		if (isEmpty())
		{
			throw "The queue is empty, cannot keep poping.";
		}
		m_front = (m_front + 1) % m_size;
	}
	void popall()
	{
		if (isEmpty())
		{
			throw "The queue is empty, cannot keep poping.";
		}
		while (m_front != m_rear)
			m_front = (m_front + 1) % m_size;
	}
	T top()
	{
		if (isEmpty())
		{
			throw "The queue is empty, cannot access the top element.";
		}
		return m_data[m_front];
	}
};