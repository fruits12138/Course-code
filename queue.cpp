#include"queue.h"

//��ʼ������
void InitQueue(LinkQueue* Q)
{
	//����ͷ����ڴ�ռ�
	QueueNode* s = (QueueNode*)malloc(sizeof(QueueNode));
	assert(s != NULL);
	//��ʼ��ʱ����ͷָ���βָ�붼ָ��ͷ���
	Q->front = Q->tail = s;
	//��ͷ������һ��㸳��
	Q->tail->next = NULL;
}
//��Ӳ������ڶ�βִ�в������
void EnQueue(LinkQueue* Q, ElemType x)
{
	//������н��
	QueueNode* s = (QueueNode*)malloc(sizeof(QueueNode));
	assert(s != NULL);
	//Ϊ����Ķ��н�㸳ֵ
	s->data = x;
	s->next = NULL;
	//������Ķ��н����뵽��β
	Q->tail->next = s;
	//���Ķ��й�������βָ���ָ��
	Q->tail = s;
}
//���Ӳ�����ɾ����ͷ�ĵ�һ����Ч���
void DeQueue(LinkQueue* Q)
{
	//�����������Ч��㣬������в���
	if (Q->front == Q->tail)
		return;

	//��ȡ��ͷ�ĵ�һ����Ч���
	QueueNode* p = Q->front->next;
	//����ͷ�ĵ�һ����Ч���Ӷ����жϿ�
	Q->front->next = p->next;
	//�ͷŸý��
	free(p);
	//���ɾ���Ľ�������һ����Ч��㣬��Ҫ����βָ���ָ��
	if (p == Q->tail)
		Q->tail = Q->front;
}
//��ӡ�����ڵ�����
void ShowQueue(LinkQueue* Q)
{
	//��ȡ�����е�һ����Ч���
	QueueNode* p = Q->front->next;
	printf("Front:>");
	//��������ÿ����Ч����е����ݴ�ӡ
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("<:Tail.\n");
}
//����еĳ���
int Length(LinkQueue* Q)
{
	int len = 0;//��ʼ����Ϊ0
	//��ȡ��ͷ�ĵ�һ����Ч���
	QueueNode* p = Q->front->next;
	//�������У���ȡһ����㣬�����г��ȼ�һ
	while (p != NULL)
	{
		len++;
		p = p->next;
	}
	//���س���ֵ
	return len;
}
//��ն��У��ͷ����е���Ч���
void ClearQueue(LinkQueue* Q)
{
	//�����������Ч��㣬������в���
	if (Q->front == Q->tail)
		return;
	//��ȡ��ͷ�ĵ�һ����Ч���
	QueueNode* p = Q->front->next;
	//���������е���Ч���
	while (p != NULL)
	{
		//�Ƴ����
		Q->front->next = p->next;
		//�ͷŽ��
		free(p);
		//ָ����һ�����
		p = Q->front->next;
	}
	Q->tail = Q->front;
}
//���ٶ���
void DestroyQueue(LinkQueue* Q)
{
	//��ն���
	ClearQueue(Q);
	//�ͷ�ͷ���
	free(Q->front);
	//���������е�ͷָ���βָ�붼ָ���
	Q->front = Q->tail = NULL;
}


Customer* GetHead(LinkQueue* que) 
{
	if (que->front->next == NULL)
		return NULL;
	return &que->front->next->data;
}