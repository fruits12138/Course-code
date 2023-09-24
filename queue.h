#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


//---------------------�������͵Ľṹ��-------------------------
// 
typedef struct Time {
	int tmHour;
	int tmMin;
}Time;

typedef struct  Customer {
	//int id; // �˿����
	Time arrivalTime;//����ʱ��
	Time serviceTime;//��Ҫ�ķ���ʱ��
	Time serviceTimeRemain;//����ʣ��ʱ��
	Time leavingTime;//�뿪ʱ��
}Customer;
//��������
#define ElemType Customer

//���н������
typedef struct QueueNode
{
	ElemType data;          //������
	struct QueueNode* next; //ָ����
}QueueNode;

//��ʽ���й���ṹ
typedef struct LinkQueue
{
	QueueNode* front;  //��ͷָ��
	QueueNode* tail;   //��βָ��
}LinkQueue;



typedef struct Window {
	Time remainingTime;//ʣ��ʱ��,��̬��,û��
	Time sumTime;//�˿������еȴ�����ʱ������̬��,ÿ����һ������һ��,ͳ��ÿ���˿͵Ķ���ʱ��
	int sumPerson;//�Ӵ�������
	int waitPerson;//�Ŷ�����
	LinkQueue customerQue;
}Window;

typedef struct Bank {
	Time startTime;//Ĭ��8��30
	Time endTime;//Ĭ��17��00
	int windowsNum;//Ĭ��Ϊ4
	bool midRest;//Ĭ�ϲ�����
	Time midRest_StartTime;//���ݿ�ʼʱ��
	Time midRest_EndTime;//���ݽ���ʱ��
	Window queWindows[4];//Ĭ��Ϊ4������,һ�ѳ�ʼ��,��̬ˢ��
	LinkQueue waitCustomer;//�ȴ��˿�(����˿������͹˿͵�ҵ�����ʱ��͹˿͵ĵ���ʱ��)��һ��ʼ�̶�
	int sumCustomer;//�ܵĹ˿���
}Bank;


//-----------------���нṹ��-------------------
void InitQueue(LinkQueue* Q);
void EnQueue(LinkQueue* Q, ElemType x);
void DeQueue(LinkQueue* Q);
void ShowQueue(LinkQueue* Q);
int Length(LinkQueue* Q);
void ClearQueue(LinkQueue* Q);
void DestroyQueue(LinkQueue* Q);
Customer* GetHead(LinkQueue* que);

//------------���ú���------------------
Time plus(Time a, Time b);

bool judge(Time a, Time b);

int genRand(int min, int max);

int Subtraction(Time a, Time b);

int bubbleSort(LinkQueue* Q, int len);

void InitBank(Bank* bank, bool midRest = false);

void genCustomer(Bank* bank, int numCustomer = 20);

void dynamicBank(Bank* bank, Time timer);

double StaticInfoShow(Bank* bank, int numCustomer = 20);

double BankSimulation_Day(int numCustomer = 20, bool midRest = false);












////
//template<typename T>
//
//class Queue {
//public:
//	Queue(int size = 0) {
//		array = new T[size];
//		i = 0;
//		j = 0;
//		num = 0;
//		this->size = size;
//	}
//	void push(T val) {
//		if (num < size && i < size - 1) {
//			array[i] = val;
//			i++;
//			num++;
//		}
//		else if (num < size && i == size - 1) {
//			array[0] = val;
//			i = 1;
//		}
//	}
//	void pop() {
//		if (j == size - 1) {
//			j = 0;
//		}
//		else {
//			j++;
//		}
//		num--;
//	}
//	int size() {
//		return num;
//	}
//	int capacity() {
//		return size;
//	}
//	T front() {
//		return array[j];
//	}
//	~queue() {
//		delete[] array;
//	}
//protected:
//	T* array;
//	int i;
//	int j;
//	int size;
//	int num;
//};
//
//
////
//
//
//class Customer {
//private:
//	//int custormer_ID;
//	
//	Time arrivalTime;//����ʱ��
//	int total_time;//����ɷ���
//
//	int serviceTime;//��Ҫ�ķ���ʱ��
//	int serviceTimeRemain;//����ʣ��ʱ��
//	int leavingTime;//�뿪ʱ��
//public:
//	//���캯���������ʼ��
//	Customer() {
//		this->arrivalTime.tmHour = genRand(8, 16);
//		this->arrivalTime.tmMin = genRand(0, 59);
//
//		this->serviceTime = genRand(3, 20);
//		
//		this->serviceTimeRemain = this->serviceTime;
//		
//		this->leavingTime = 0;
//	}
//	//����
//	void bubbleSort(Customer arr[],int len) {
//		int i, j;
//		Customer temp;
//		for (i = 0; i < len - 1; i++)
//			for (j = 0; j < len - 1 - i; j++)
//				if (Subtraction(arr[j].arrivalTime, arr[j + 1].arrivalTime) > 0) {
//					temp = arr[j];
//					arr[j] = arr[j + 1];
//					arr[j + 1] = temp;
//				}
//	}
//
//	//�������Ե�get����
//	int getCustomerArriveTime() {//����ɷ���
//		int t = this->arrivalTime.tmHour * 60 + this->arrivalTime.tmMin;
//		return t;
//	}
//
//	int getCustomerServiceTime() {
//		return this->serviceTime;
//	}
//
//	int getCustomerRemainTime() {
//		return this->serviceTimeRemain;
//	}
//	int getCustomerLeaveTime() {
//		return this->leavingTime;
//	}
//
//	////�������Ե�set����
//	//void setCustomerArriveTime(Time _a) {
//	//	this->arrivalTime.tmHour = _a.tmHour;
//	//	this->arrivalTime.tmMin = _a.tmMin;
//	//}
//
//	//void setCustomerServiceTime(int _a) {
//	//	this->serviceTime = _a;
//	//}
//	//void setCustomerRemainTime(int _a) {
//	//	this->serviceTimeRemain = _a;
//	//}
//	//void setCustomerLeaveTime(int _a) {
//	//	this->leavingTime = _a;
//	//}
//};
//
//
//class Bank {
//
//	//Ĭ�Ϸ�װ
//private:
//	Time startTime;//Ĭ��8��30
//	Time endTime;//Ĭ��17��00
//	int windowsNum;//Ĭ��Ϊ4
//	bool midRest;//Ĭ�ϲ�����
//	Customer* waitCus;//�Ŷ�����
//	int sumCustomer;//�ܵĽӴ��˿���
//	Window* win;
//public:
//	Bank(Time start,Time end,int _windowsNum,bool _midRest,int _sumCustomer,Customer* _cus,Window* _win) {
//		this->startTime = start;
//		this->endTime = end;
//		this->windowsNum = _windowsNum;
//		this->midRest = _midRest;
//		this->sumCustomer = _sumCustomer;
//		this->waitCus = _cus;
//		this->win = _win;
//	}
//
//	//�������Ե�get����
//	int getStartTime() {
//		int t = this->startTime.tmHour * 60 + this->startTime.tmMin;
//		return t;
//	}
//	int getEndTime() {
//		int t = this->endTime.tmHour * 60 + this->endTime.tmMin;
//		return t;
//	}
//	int getWindowsNum() {
//		return this->windowsNum;
//	}
//	bool getMidRest() {
//		return this->midRest;
//	}
//	int getSumCustomer() {
//		return this->sumCustomer;
//	}
//	Customer* getCusQueue() {
//		return this->waitCus;
//	}
//	Window* getWindows() {
//		return this->win;
//	}
//	////�������Ե�set����
//	//void setStartTime(Time _a) {
//	//	this->startTime = _a;
//	//}
//	//void setEndTime(Time _a) {
//	//	this->endTime = _a;
//
//	//}
//	//void setWindowsNum(int _a) {
//	//	this->windowsNum = _a;
//
//	//}
//	//void setMidRest(bool _a) {
//	//	this->midRest = _a;
//
//	//}
//	//void setSumCustomer(int _a) {
//	//	this->sumCustomer = _a;
//	//}
//};
//
//
//
//class Window {
//private:
//	int remainingTime;//ʣ��ʱ��,��̬��,û��
//	int sumTime;//�˿������д�����ʱ������̬��,ÿ����һ������һ��,ͳ��ÿ���˿͵Ķ���ʱ��
//	Customer* cus;
//public:
//	Window(int _remainintTime,int _sumTime,Customer* _cus) {
//		this->remainingTime = _remainintTime;
//		this->sumTime = _sumTime;
//		this->cus = _cus;
//	}
//	//�������Ե�get����
//	int getRemainTime() {
//		return this->remainingTime;
//	}
//	int getSumTime() {
//		return this->sumTime;
//	}
//	Customer* getCustormerQueue() {
//		return this->cus;
//	}
//	//�������Ե�set����
//};


//
////��������
//#define ElemType Customer
//#define num 4
//
////���н������
//typedef struct QueueNode
//{
//	ElemType data;          //������
//	struct QueueNode* next; //ָ����
//}QueueNode;
//
////��ʽ���й���ṹ
//typedef struct LinkQueue
//{
//	QueueNode* front;  //��ͷָ��
//	QueueNode* tail;   //��βָ��
//}LinkQueue;

//-----------------------����ϵͳ----------------------------




//----------------------------------���ú���--------------------------------------
//
//Time plus(Time a, Time b);
//bool judge(Time a, Time b);
//int genRand(int min, int max);
//void bubble_sort(Customer arr[], int len);
//int Subtraction(Time a, Time b);
//void OpenForDay();



#endif //__LINKQUEUE_H__
