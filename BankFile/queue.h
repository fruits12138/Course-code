#ifndef __LINKQUEUE_H__
#define __LINKQUEUE_H__

#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


//---------------------各个类型的结构体-------------------------
// 
typedef struct Time {
	int tmHour;
	int tmMin;
}Time;

typedef struct  Customer {
	//int id; // 顾客序号
	Time arrivalTime;//到达时间
	Time serviceTime;//需要的服务时间
	Time serviceTimeRemain;//服务剩余时间
	Time leavingTime;//离开时间
}Customer;
//数据类型
#define ElemType Customer

//队列结点类型
typedef struct QueueNode
{
	ElemType data;          //数据域
	struct QueueNode* next; //指针域
}QueueNode;

//链式队列管理结构
typedef struct LinkQueue
{
	QueueNode* front;  //队头指针
	QueueNode* tail;   //队尾指针
}LinkQueue;



typedef struct Window {
	Time remainingTime;//剩余时长,动态量,没用
	Time sumTime;//顾客在银行等待的总时长，动态量,每服务一个增加一点,统计每个顾客的逗留时长
	int sumPerson;//接待总人数
	int waitPerson;//排队人数
	LinkQueue customerQue;
}Window;

typedef struct Bank {
	Time startTime;//默认8：30
	Time endTime;//默认17：00
	int windowsNum;//默认为4
	bool midRest;//默认不午休
	Time midRest_StartTime;//午休开始时间
	Time midRest_EndTime;//午休结束时间
	Window queWindows[4];//默认为4个窗口,一堆初始化,动态刷新
	LinkQueue waitCustomer;//等待顾客(随机顾客数量和顾客的业务办理时间和顾客的到达时间)，一开始固定
	int sumCustomer;//总的顾客数
}Bank;


//-----------------队列结构体-------------------
void InitQueue(LinkQueue* Q);
void EnQueue(LinkQueue* Q, ElemType x);
void DeQueue(LinkQueue* Q);
void ShowQueue(LinkQueue* Q);
int Length(LinkQueue* Q);
void ClearQueue(LinkQueue* Q);
void DestroyQueue(LinkQueue* Q);
Customer* GetHead(LinkQueue* que);

//------------常用函数------------------
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
//	Time arrivalTime;//到达时间
//	int total_time;//换算成分钟
//
//	int serviceTime;//需要的服务时间
//	int serviceTimeRemain;//服务剩余时间
//	int leavingTime;//离开时间
//public:
//	//构造函数，随机初始化
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
//	//排序
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
//	//各个属性的get方法
//	int getCustomerArriveTime() {//换算成分钟
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
//	////各个属性的set方法
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
//	//默认封装
//private:
//	Time startTime;//默认8：30
//	Time endTime;//默认17：00
//	int windowsNum;//默认为4
//	bool midRest;//默认不午休
//	Customer* waitCus;//排队序列
//	int sumCustomer;//总的接待顾客数
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
//	//所有属性的get方法
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
//	////所有属性的set方法
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
//	int remainingTime;//剩余时长,动态量,没用
//	int sumTime;//顾客在银行待的总时长，动态量,每服务一个增加一点,统计每个顾客的逗留时长
//	Customer* cus;
//public:
//	Window(int _remainintTime,int _sumTime,Customer* _cus) {
//		this->remainingTime = _remainintTime;
//		this->sumTime = _sumTime;
//		this->cus = _cus;
//	}
//	//所有属性的get方法
//	int getRemainTime() {
//		return this->remainingTime;
//	}
//	int getSumTime() {
//		return this->sumTime;
//	}
//	Customer* getCustormerQueue() {
//		return this->cus;
//	}
//	//所有属性的set方法
//};


//
////数据类型
//#define ElemType Customer
//#define num 4
//
////队列结点类型
//typedef struct QueueNode
//{
//	ElemType data;          //数据域
//	struct QueueNode* next; //指针域
//}QueueNode;
//
////链式队列管理结构
//typedef struct LinkQueue
//{
//	QueueNode* front;  //队头指针
//	QueueNode* tail;   //队尾指针
//}LinkQueue;

//-----------------------银行系统----------------------------




//----------------------------------常用函数--------------------------------------
//
//Time plus(Time a, Time b);
//bool judge(Time a, Time b);
//int genRand(int min, int max);
//void bubble_sort(Customer arr[], int len);
//int Subtraction(Time a, Time b);
//void OpenForDay();



#endif //__LINKQUEUE_H__
