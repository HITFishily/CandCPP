/**************************************************************************************************
* File Name : ring_queue_nolock.h
* Created : 20 / 02 / 10
* Author : GYT
* Description : �������ζ���
* 1.Ring_Queue��payloadǰ����һ��ͷ������ʾ��ǰ�ڵ��״̬
* 2.��ǰ�ڵ��״̬�������Զ�������д�����ڶ�������д
* 3.������ɺ󽫽ڵ�״̬��Ϊ����д����д��ɺ󽫽ڵ�״̬��Ϊ���Զ�
* 4.Ring_Queueʹ��ʱ����������������ģ�ͣ�������������д��һ�����ýڵ㣬�����߻�ã���������ͷ�ڵ�
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
	* Description : ���캯��
	* Date : 20 / 02 / 10
	* Parameter : int nmemb�����д�С int size��Payload����
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
	* Description : ��������
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
	* Description : ��ȡ����
	* Date : 20 / 02 / 10
	* Parameter : none
	* Return Code : ָ��payload��ָ��
	* Author : GYT
	**************************************************************************************************/
	u_char * Read();
	/**************************************************************************************************
	* Function Name : Read_Over
	* Description : ��ȡ֮��Ĳ��������ڵ�״̬������Ϊ������д���������ɶ��ڵ�ָ����һ��λ��
	* Date : 20 / 02 / 10
	* Parameter : none
	* Return Code : none
	* Author : GYT
	**************************************************************************************************/
	void Read_Over();
	/**************************************************************************************************
	* Function Name : Write
	* Description : д�뺯��
	* Date : 20 / 02 / 10
	* Parameter : none
	* Return Code : ��ʱ����һ����ȫ�ġ���������д���ݵ�ָ�룬�����д�������������ִ��
	* Author : GYT
	**************************************************************************************************/
	u_char * Write();
	/**************************************************************************************************
	* Function Name : Write_Over
	* Description : д��֮��Ĳ��������ڵ�״̬������Ϊ�����Զ�����������д�ڵ�ָ����һ��λ��
	* Date : 20 / 02 / 10
	* Parameter : none
	* Return Code : none
	* Author : GYT
	**************************************************************************************************/
	void Write_Over();
private:
	/**************************************************************************************************
	* Function Name : queue_peek_nth
	* Description : ��Ϊ����������u_char���飬��Ҫ�����ֽ���ƫ����ָ��λ��
	* Date : 20 / 02 / 10
	* Parameter : u_char *queue_p������ int pos����Ҫƫ�Ƶ�λ��
	* Return Code : none
	* Author : GYT
	**************************************************************************************************/
	u_char *queue_peek_nth(u_char *queue_p, int pos);
	u_char*		 m_queue_p;			//����ָ��
	int			 m_inmemb;			//���д�С
	int			 m_isize;			//�����д�����ݵĳ���
	volatile int m_iread_now;		//��ǰ�ɶ��ڵ�
	volatile int m_iwrite_now;		//��ǰ��д�ڵ�
};