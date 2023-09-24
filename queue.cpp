#include"queue.h"

//初始化队列
void InitQueue(LinkQueue* Q)
{
	//申请头结点内存空间
	QueueNode* s = (QueueNode*)malloc(sizeof(QueueNode));
	assert(s != NULL);
	//初始化时，将头指针和尾指针都指向头结点
	Q->front = Q->tail = s;
	//将头结点的下一结点赋空
	Q->tail->next = NULL;
}
//入队操作：在队尾执行插入操作
void EnQueue(LinkQueue* Q, ElemType x)
{
	//申请队列结点
	QueueNode* s = (QueueNode*)malloc(sizeof(QueueNode));
	assert(s != NULL);
	//为申请的队列结点赋值
	s->data = x;
	s->next = NULL;
	//将申请的队列结点插入到队尾
	Q->tail->next = s;
	//更改队列管理结点中尾指针的指向
	Q->tail = s;
}
//出队操作：删除队头的第一个有效结点
void DeQueue(LinkQueue* Q)
{
	//如果队中无有效结点，无需进行操作
	if (Q->front == Q->tail)
		return;

	//获取队头的第一个有效结点
	QueueNode* p = Q->front->next;
	//将队头的第一个有效结点从队列中断开
	Q->front->next = p->next;
	//释放该结点
	free(p);
	//如果删除的结点是最后一个有效结点，需要更改尾指针的指向
	if (p == Q->tail)
		Q->tail = Q->front;
}
//打印队列内的数据
void ShowQueue(LinkQueue* Q)
{
	//获取队列中第一个有效结点
	QueueNode* p = Q->front->next;
	printf("Front:>");
	//将队列中每个有效结点中的数据打印
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("<:Tail.\n");
}
//求队列的长度
int Length(LinkQueue* Q)
{
	int len = 0;//初始长度为0
	//获取队头的第一个有效结点
	QueueNode* p = Q->front->next;
	//遍历队列，获取一个结点，将队列长度加一
	while (p != NULL)
	{
		len++;
		p = p->next;
	}
	//返回长度值
	return len;
}
//清空队列：释放所有的有效结点
void ClearQueue(LinkQueue* Q)
{
	//如果队中无有效结点，无需进行操作
	if (Q->front == Q->tail)
		return;
	//获取队头的第一个有效结点
	QueueNode* p = Q->front->next;
	//遍历队列中的有效结点
	while (p != NULL)
	{
		//移除结点
		Q->front->next = p->next;
		//释放结点
		free(p);
		//指向下一个结点
		p = Q->front->next;
	}
	Q->tail = Q->front;
}
//销毁队列
void DestroyQueue(LinkQueue* Q)
{
	//清空队列
	ClearQueue(Q);
	//释放头结点
	free(Q->front);
	//将管理结点中的头指针和尾指针都指向空
	Q->front = Q->tail = NULL;
}


Customer* GetHead(LinkQueue* que) 
{
	if (que->front->next == NULL)
		return NULL;
	return &que->front->next->data;
}