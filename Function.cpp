#include"queue.h";
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
//-------------------------常用函数-----------------------------
Time plus(Time a, Time b) {//时间相加
	Time c;
	c.tmHour = a.tmHour + b.tmHour;
	c.tmMin = a.tmMin + b.tmMin;
	return c;
}

bool judge(Time a, Time b) {//判断时间是否相等
	if (a.tmHour == b.tmHour && a.tmMin == b.tmMin)
		return true;
	else
		return false;
}

int genRand(int min, int max) { // 生成[min, max]的随机整数
	return (rand() % (max - min + 1)) + min;
}

int Subtraction(Time a, Time b) {
	int res = a.tmHour * 60 + a.tmMin - b.tmHour * 60 - b.tmMin;
	return res;
}


int bubbleSort(LinkQueue* Q, int len) {
	QueueNode* p1 = Q->front->next;
	QueueNode* p0 = Q->front;
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - 1 - i; j++) {
			if (Subtraction(p1->data.arrivalTime, p1->next->data.arrivalTime) > 0) {
				QueueNode* p2 = p1->next;
				p1->next = p2->next;
				p2->next = p1;
				p0->next = p2;

				p1 = p2;
			}
			p0 = p0->next;
			p1 = p1->next;
			if (p1->next == NULL)break;
		}
		p1 = Q->front->next;
		p0 = Q->front;
	}
	QueueNode* q = Q->front;
	while (q->next != NULL) {
		q = q->next;
	}
	Q->tail = q;
	return 0;
}

void InitBank(Bank* bank, bool midRest ) {
	//银行开业时间
	bank->startTime.tmHour = 8;
	bank->startTime.tmMin = 30;
	//银行关门时间
	bank->endTime.tmHour = 17;
	bank->endTime.tmMin = 00;
	//银行午休时间
	bank->midRest_StartTime.tmHour = 12;
	bank->midRest_StartTime.tmMin = 00;

	bank->midRest_EndTime.tmHour = 14;
	bank->midRest_EndTime.tmMin = 00;

	//银行窗口数
	bank->windowsNum = 4;
	//银行是否午休
	bank->midRest = midRest;
	//银行各个窗口的初始化
	for (int i = 0; i < bank->windowsNum; i++) {
		bank->queWindows[i].remainingTime.tmHour = 0;
		bank->queWindows[i].remainingTime.tmMin = 0;
		bank->queWindows[i].sumTime.tmHour = 0;
		bank->queWindows[i].sumTime.tmMin = 0;
		bank->queWindows[i].sumPerson = 0;
		bank->queWindows[i].waitPerson = 0;
		InitQueue(&bank->queWindows[i].customerQue);
	}
}

void genCustomer(Bank* bank, int numCustomer ) {
	InitQueue(&bank->waitCustomer);
	if (!bank->midRest) {
		//午休判断
		while (Length(&bank->waitCustomer) < numCustomer) {
			Customer cus;
			cus.arrivalTime.tmHour = genRand(8, 16);
			cus.arrivalTime.tmMin = genRand(0, 59);
			cus.serviceTime.tmHour = 0;
			cus.serviceTime.tmMin = genRand(3, 20);
			cus.serviceTimeRemain.tmHour = cus.serviceTime.tmHour;
			cus.serviceTimeRemain.tmMin = cus.serviceTime.tmMin;
			cus.leavingTime.tmHour = 0;
			cus.leavingTime.tmMin = 0;
			if (Subtraction(cus.arrivalTime, bank->startTime) < 0 || Subtraction(cus.arrivalTime, bank->endTime) > 0) {
				continue;
			}
			EnQueue(&bank->waitCustomer, cus);
		}
	}
	else {
		while (Length(&bank->waitCustomer) < numCustomer) {
			Customer cus;
			cus.arrivalTime.tmHour = genRand(8, 16);
			cus.arrivalTime.tmMin = genRand(0, 59);
			cus.serviceTime.tmHour = 0;
			cus.serviceTime.tmMin = genRand(3, 20);
			cus.serviceTimeRemain.tmHour = cus.serviceTime.tmHour;
			cus.serviceTimeRemain.tmMin = cus.serviceTime.tmMin;
			cus.leavingTime.tmHour = 0;
			cus.leavingTime.tmMin = 0;
			if (Subtraction(cus.arrivalTime, bank->startTime) < 0 || Subtraction(cus.arrivalTime, bank->endTime) > 0 ||
				(Subtraction(cus.arrivalTime, bank->midRest_StartTime) > 0 && Subtraction(cus.arrivalTime, bank->midRest_EndTime) < 0)) {
				continue;
			}
			EnQueue(&bank->waitCustomer, cus);
		}
	}
	//排序
	//bubble_sort(bank.waitCustomer, numCustomer);
	bubbleSort(&bank->waitCustomer, Length(&bank->waitCustomer));
	//总的顾客数量初始化
	bank->sumCustomer = 0;
}

void dynamicBank(Bank* bank, Time timer) {
	int countInBank = 0;
	int numMor = 0;//早上的人数
	int numMoon = 0;//下午的人数

	while (!judge(timer, bank->endTime)) {//需要对银行系统进行动态刷新 
			//循环判断当前的n个窗口中的第一位顾客是否出队
		for (int j = 0; j < bank->windowsNum; j++) {
			if (bank->queWindows[j].customerQue.front->next != NULL) {
				if (bank->queWindows[j].customerQue.front->next->data.serviceTimeRemain.tmMin == 0) {//默认服务时长不会超出20min

					bank->queWindows[j].customerQue.front->next->data.leavingTime.tmHour = timer.tmHour;
					bank->queWindows[j].customerQue.front->next->data.leavingTime.tmMin = timer.tmMin;

					bank->queWindows[j].sumTime.tmMin += Subtraction(bank->queWindows[j].customerQue.front->next->data.leavingTime, \
						bank->queWindows[j].customerQue.front->next->data.arrivalTime);//只有分钟，

					bank->queWindows[j].sumPerson++;
					bank->queWindows[j].waitPerson--;
					bank->sumCustomer++;
					//下午的数据统计
					if (Subtraction(timer, bank->midRest_EndTime) >= 0 && bank->midRest) {
						numMoon++;
					}

					DeQueue(&bank->queWindows[j].customerQue);
				}
			}

		}
		//银行外等待顾客是否入队
		while (true) {
			Customer* first = GetHead(&bank->waitCustomer);
			if (first == NULL || Subtraction(first->arrivalTime, timer) > 0)break;
			if (first != NULL) {
				if (judge(timer, first->arrivalTime)) {//到达时间与现在时间匹配
					int numPeople = Length(&bank->queWindows[0].customerQue);
					int locWindow = 0;

					for (int j = 1; j < bank->windowsNum; j++) {//选择人数最少的进
						int numPeople1 = Length(&bank->queWindows[j].customerQue);
						if (numPeople > numPeople1) {
							numPeople = numPeople1;
							locWindow = j;

						}
					}
					printf("第%d位客户到达，时间：%d:%d,客户办理业务所需时间%dmin\n", ++countInBank, timer.tmHour, timer.tmMin, first->serviceTime.tmMin);

					EnQueue(&bank->queWindows[locWindow].customerQue, *first);
					bank->queWindows[locWindow].waitPerson++;
					DeQueue(&bank->waitCustomer);
				}
			}
		}

		//计时器++

		timer.tmMin++;
		if (timer.tmMin >= 60) {
			timer.tmHour++;
			timer.tmMin = 0;
		}

		//刷新各个窗口的剩余服务时长和累计总等待时长

		for (int j = 0; j < bank->windowsNum; j++) {
			if (bank->queWindows[j].customerQue.front->next) {
				bank->queWindows[j].customerQue.front->next->data.serviceTimeRemain.tmMin--;//对象为顾客，每位顾客的剩余时长减少
			}
		}
		//午休情况
		if (judge(timer, bank->midRest_StartTime)) {
			if (bank->midRest) {
				for (int j = 0; j < bank->windowsNum; j++) {
					if (bank->queWindows[j].customerQue.front->next != NULL) {
						//---------------遍历顾客等待队列-------------------
						Customer* first = GetHead(&bank->queWindows[j].customerQue);
						bank->queWindows[j].sumPerson++;
						while (true) {
							bank->queWindows[j].sumTime.tmMin += Subtraction(bank->midRest_StartTime, \
								first->arrivalTime);

							bank->queWindows[j].waitPerson--;
							//bank.queWindows[j].sumPerson++;

							DeQueue(&bank->queWindows[j].customerQue);
							first = GetHead(&bank->queWindows[j].customerQue);
							if (first == NULL)break;
						}
					}
					numMor += bank->queWindows[j].sumPerson;
				}
				printf("上午共接待人数%d人\n", numMor);

				timer.tmHour = bank->midRest_EndTime.tmHour;
				timer.tmMin = bank->midRest_EndTime.tmMin;
			}
		}
	}
	//------------添加最后等待顾客的时间----------------
	for (int j = 0; j < bank->windowsNum; j++) {
		if (bank->queWindows[j].customerQue.front->next != NULL) {
			//---------------遍历顾客等待队列-------------------
			Customer* first = GetHead(&bank->queWindows[j].customerQue);
			bank->queWindows[j].sumPerson++;
			//下午的数据统计
			if (bank->midRest) {
				numMoon++;
			}
			while (true) {
				bank->queWindows[j].sumTime.tmMin += Subtraction(bank->endTime, \
					first->arrivalTime);

				bank->queWindows[j].waitPerson--;
				//bank.queWindows[j].sumPerson++;

				DeQueue(&bank->queWindows[j].customerQue);
				first = GetHead(&bank->queWindows[j].customerQue);
				if (first == NULL)break;
			}
		}
	}
	if (bank->midRest)
		printf("下午共计接待人数%d人\n", numMoon);
}

double StaticInfoShow(Bank* bank, int numCustomer ) {


	double a = 0;//总的顾客逗留时间
	int numSer = 0;//银行总的服务人数

	for (int k = 0; k < bank->windowsNum; k++) {
		a += bank->queWindows[k].sumTime.tmMin;
		numSer += bank->queWindows[k].sumPerson;
	}

	printf("--------------------------以下为银行信息--------------------------\n");
	printf("|\n|\n|\n");
	printf("|今天共接待%d个顾客，服务总人数%d,今天顾客的平均逗留时间为：%.1fmin\n", numCustomer, numSer, a / bank->sumCustomer);
	printf("|\n|\n|\n");
	printf("--------------------------以下为窗台信息--------------------------\n");
	for (int k = 0; k < bank->windowsNum; k++) {
		printf("第%d号窗台，接待服务人数%d人，顾客的等待时间%dmin\n", k + 1, bank->queWindows[k].sumPerson, bank->queWindows[k].sumTime.tmMin);
	}
	printf("------------------------------------------------------------------\n");

	//printf("--------------以下为一天的信息---------------\n");
	//printf("今天顾客的平均逗留时间为：%.1fmin\n",a/bank->sumCustomer);
	return a;
}

double BankSimulation_Day(int numCustomer , bool midRest ) {//模拟银行模拟一天
	/*参数说明：
	*	numCustomer:表示今天的等待顾客人数，就是银行外等待顾客人数
	*	midRest:表示今天是否午休
	*/

	//以绝对时间计算
	Bank bank;
	Time time;
	//银行初始化
	InitBank(&bank, midRest);
	//银行前的顾客等待队列初始化(随机初始化)
	genCustomer(&bank, numCustomer);
	//计时器初始化
	Time timer;
	timer.tmHour = bank.startTime.tmHour;
	timer.tmMin = bank.startTime.tmMin;
	//银行动态刷新，随着时间
	dynamicBank(&bank, timer);
	//数据收集并展示
	double dayTime = StaticInfoShow(&bank, numCustomer);
	//返回一天的顾客平均等待时长
	return dayTime / bank.sumCustomer;
}
