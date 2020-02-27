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
			throw "The queue is full£¬cannot keep pushing.";
		}
		m_data[m_rear] = data;
		m_rear = (m_rear + 1) % m_size;
	}
	void pop()
	{
		if (isEmpty())
		{
			throw new exception("The queue is empty£¬cannot keep poping.");
		}
		m_front = (m_front + 1) % m_size;
	}
	void popall()
	{
		if (isEmpty())
		{
			throw new exception("The queue is empty£¬cannot keep poping.");
		}
		while (m_front != m_rear)
			m_front = (m_front + 1) % m_size;
	}
	T top()
	{
		if (isEmpty())
		{
			throw new exception("The queue is empty£¬cannot access the top element.");
		}
		return m_data[m_front];
	}
};