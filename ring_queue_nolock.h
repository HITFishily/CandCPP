/**************************************************************************************************
* File Name : ring_queue_nolock.h
* Created : 20 / 02 / 10
* Author : GYT
* Description : 无锁环形队列
* 1.Ring_Queue在payload前加入一个头，来表示当前节点的状态
* 2.当前节点的状态包括可以读、可以写、正在读、正在写
* 3.当读完成后将节点状态改为可以写，当写完成后将节点状态改为可以读
* 4.Ring_Queue使用时参照生产者消费者模型，生产者生产（写）一个可用节点，消费者获得（读）队列头节点
**************************************************************************************************/
#include <assert.h>
#include <string.h> 
#include <sys/types.h>        

typedef unsigned char u_char;

#define CAN_WRITE 0x00
#define CAN_READ  0x01
#define READING   0x02
#define WRITING   0x03

typedef struct tag
{
	u_char tag_value;
}TAG;

class Ring_Queue
{
public:
	/**************************************************************************************************
	* Function Name : Ring_Queue
	* Description : 构造函数
	* Date : 20 / 02 / 10
	* Parameter : int nmemb：队列大小 int size：Payload长度
	* Return Code : none
	* Author : GYT
	**************************************************************************************************/
	Ring_Queue(int nmemb, int size):m_inmemb(nmemb), m_isize(size)
		, m_iread_now(0), m_iwrite_now(0)
	{
		if (nmemb <= 0 || size <= 0)
		{
			assert(0);
		}
		m_queue_p = NULL;
		m_queue_p = new u_char[nmemb * (sizeof(TAG)+size)];
		memset(m_queue_p, 0, nmemb * (sizeof(TAG)+size));
	}
	/**************************************************************************************************
	* Function Name : Ring_Queue
	* Description : 析构函数
	* Date : 20 / 02 / 10
	* Parameter : none
	* Return Code : none
	* Author : GYT
	**************************************************************************************************/
	~Ring_Queue()
	{
		if (m_queue_p) delete[]m_queue_p;

	}
	/**************************************************************************************************
	* Function Name : Read
	* Description : 读取函数
	* Date : 20 / 02 / 10
	* Parameter : none
	* Return Code : 指向payload的指针
	* Author : GYT
	**************************************************************************************************/
	u_char * Read();
	/**************************************************************************************************
	* Function Name : Read_Over
	* Description : 读取之后的操作，将节点状态跟更新为‘可以写’，并将可读节点指向下一个位置
	* Date : 20 / 02 / 10
	* Parameter : none
	* Return Code : none
	* Author : GYT
	**************************************************************************************************/
	void Read_Over();
	/**************************************************************************************************
	* Function Name : Write
	* Description : 写入函数
	* Date : 20 / 02 / 10
	* Parameter : none
	* Return Code : 此时返回一个安全的、可以用来写数据的指针，具体的写入操作由生产者执行
	* Author : GYT
	**************************************************************************************************/
	u_char * Write();
	/**************************************************************************************************
	* Function Name : Write_Over
	* Description : 写入之后的操作，将节点状态跟更新为‘可以读’，并将可写节点指向下一个位置
	* Date : 20 / 02 / 10
	* Parameter : none
	* Return Code : none
	* Author : GYT
	**************************************************************************************************/
	void Write_Over();
private:
	/**************************************************************************************************
	* Function Name : queue_peek_nth
	* Description : 因为整个队列是u_char数组，需要根据字节数偏移至指定位置
	* Date : 20 / 02 / 10
	* Parameter : u_char *queue_p：队列 int pos：需要偏移的位置
	* Return Code : none
	* Author : GYT
	**************************************************************************************************/
	u_char *queue_peek_nth(u_char *queue_p, int pos);
	u_char*		 m_queue_p;			//队列指针
	int			 m_inmemb;			//队列大小
	int			 m_isize;			//队列中存放数据的长度
	volatile int m_iread_now;		//当前可读节点
	volatile int m_iwrite_now;		//当前可写节点
};