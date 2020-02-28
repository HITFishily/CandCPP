#include "ring_queue_nolock.h"

u_char * Ring_Queue::Read()
{
	u_char * g_p = 0;
	TAG * tag_p = 0;
	u_char *user_data = 0;

	g_p = queue_peek_nth(m_queue_p, m_iread_now);
	tag_p = (TAG *)g_p;
	if (tag_p->tag_value == CAN_READ)
	{
		user_data = (u_char *)g_p + sizeof(TAG);
		tag_p->tag_value = READING;
	}
	return user_data;
}

void Ring_Queue::Read_Over()
{
	u_char * g_p = 0;
	TAG * tag_p = 0;

	g_p = queue_peek_nth(m_queue_p, m_iread_now);
	tag_p = (TAG *)g_p;
	if (tag_p->tag_value == READING)
	{
		tag_p->tag_value = CAN_WRITE;
		m_iread_now = (m_iread_now + 1) % m_inmemb;
	}
}

u_char * Ring_Queue::Write()
{
	u_char * g_p = 0;
	TAG * tag_p = 0;
	u_char *user_data = 0;

	g_p = queue_peek_nth(m_queue_p, m_iwrite_now);
	tag_p = (TAG *)g_p;
	if (tag_p->tag_value == CAN_WRITE)
	{
		user_data = (u_char *)g_p + sizeof(TAG);
		tag_p->tag_value = WRITING;
	}
	return user_data;
}

void Ring_Queue::Write_Over()
{
	u_char * g_p = 0;
	TAG * tag_p = 0;

	g_p = queue_peek_nth(m_queue_p, m_iwrite_now);
	tag_p = (TAG *)g_p;
	if (tag_p->tag_value == WRITING)
	{
		tag_p->tag_value = CAN_READ;
		m_iwrite_now = (m_iwrite_now + 1) % m_inmemb;
	}
}

u_char* Ring_Queue::queue_peek_nth(u_char *queue_p, int pos)
{
	u_char *rst = 0;
	if (queue_p && pos < m_inmemb)
	{
		rst = queue_p + pos * (sizeof(TAG)+m_isize);
	}
	return rst;
}