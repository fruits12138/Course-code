#include"queue.h";
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
//-------------------------���ú���-----------------------------
Time plus(Time a, Time b) {//ʱ�����
	Time c;
	c.tmHour = a.tmHour + b.tmHour;
	c.tmMin = a.tmMin + b.tmMin;
	return c;
}

bool judge(Time a, Time b) {//�ж�ʱ���Ƿ����
	if (a.tmHour == b.tmHour && a.tmMin == b.tmMin)
		return true;
	else
		return false;
}

int genRand(int min, int max) { // ����[min, max]���������
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
	//���п�ҵʱ��
	bank->startTime.tmHour = 8;
	bank->startTime.tmMin = 30;
	//���й���ʱ��
	bank->endTime.tmHour = 17;
	bank->endTime.tmMin = 00;
	//��������ʱ��
	bank->midRest_StartTime.tmHour = 12;
	bank->midRest_StartTime.tmMin = 00;

	bank->midRest_EndTime.tmHour = 14;
	bank->midRest_EndTime.tmMin = 00;

	//���д�����
	bank->windowsNum = 4;
	//�����Ƿ�����
	bank->midRest = midRest;
	//���и������ڵĳ�ʼ��
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
		//�����ж�
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
	//����
	//bubble_sort(bank.waitCustomer, numCustomer);
	bubbleSort(&bank->waitCustomer, Length(&bank->waitCustomer));
	//�ܵĹ˿�������ʼ��
	bank->sumCustomer = 0;
}

void dynamicBank(Bank* bank, Time timer) {
	int countInBank = 0;
	int numMor = 0;//���ϵ�����
	int numMoon = 0;//���������

	while (!judge(timer, bank->endTime)) {//��Ҫ������ϵͳ���ж�̬ˢ�� 
			//ѭ���жϵ�ǰ��n�������еĵ�һλ�˿��Ƿ����
		for (int j = 0; j < bank->windowsNum; j++) {
			if (bank->queWindows[j].customerQue.front->next != NULL) {
				if (bank->queWindows[j].customerQue.front->next->data.serviceTimeRemain.tmMin == 0) {//Ĭ�Ϸ���ʱ�����ᳬ��20min

					bank->queWindows[j].customerQue.front->next->data.leavingTime.tmHour = timer.tmHour;
					bank->queWindows[j].customerQue.front->next->data.leavingTime.tmMin = timer.tmMin;

					bank->queWindows[j].sumTime.tmMin += Subtraction(bank->queWindows[j].customerQue.front->next->data.leavingTime, \
						bank->queWindows[j].customerQue.front->next->data.arrivalTime);//ֻ�з��ӣ�

					bank->queWindows[j].sumPerson++;
					bank->queWindows[j].waitPerson--;
					bank->sumCustomer++;
					//���������ͳ��
					if (Subtraction(timer, bank->midRest_EndTime) >= 0 && bank->midRest) {
						numMoon++;
					}

					DeQueue(&bank->queWindows[j].customerQue);
				}
			}

		}
		//������ȴ��˿��Ƿ����
		while (true) {
			Customer* first = GetHead(&bank->waitCustomer);
			if (first == NULL || Subtraction(first->arrivalTime, timer) > 0)break;
			if (first != NULL) {
				if (judge(timer, first->arrivalTime)) {//����ʱ��������ʱ��ƥ��
					int numPeople = Length(&bank->queWindows[0].customerQue);
					int locWindow = 0;

					for (int j = 1; j < bank->windowsNum; j++) {//ѡ���������ٵĽ�
						int numPeople1 = Length(&bank->queWindows[j].customerQue);
						if (numPeople > numPeople1) {
							numPeople = numPeople1;
							locWindow = j;

						}
					}
					printf("��%dλ�ͻ����ʱ�䣺%d:%d,�ͻ�����ҵ������ʱ��%dmin\n", ++countInBank, timer.tmHour, timer.tmMin, first->serviceTime.tmMin);

					EnQueue(&bank->queWindows[locWindow].customerQue, *first);
					bank->queWindows[locWindow].waitPerson++;
					DeQueue(&bank->waitCustomer);
				}
			}
		}

		//��ʱ��++

		timer.tmMin++;
		if (timer.tmMin >= 60) {
			timer.tmHour++;
			timer.tmMin = 0;
		}

		//ˢ�¸������ڵ�ʣ�����ʱ�����ۼ��ܵȴ�ʱ��

		for (int j = 0; j < bank->windowsNum; j++) {
			if (bank->queWindows[j].customerQue.front->next) {
				bank->queWindows[j].customerQue.front->next->data.serviceTimeRemain.tmMin--;//����Ϊ�˿ͣ�ÿλ�˿͵�ʣ��ʱ������
			}
		}
		//�������
		if (judge(timer, bank->midRest_StartTime)) {
			if (bank->midRest) {
				for (int j = 0; j < bank->windowsNum; j++) {
					if (bank->queWindows[j].customerQue.front->next != NULL) {
						//---------------�����˿͵ȴ�����-------------------
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
				printf("���繲�Ӵ�����%d��\n", numMor);

				timer.tmHour = bank->midRest_EndTime.tmHour;
				timer.tmMin = bank->midRest_EndTime.tmMin;
			}
		}
	}
	//------------������ȴ��˿͵�ʱ��----------------
	for (int j = 0; j < bank->windowsNum; j++) {
		if (bank->queWindows[j].customerQue.front->next != NULL) {
			//---------------�����˿͵ȴ�����-------------------
			Customer* first = GetHead(&bank->queWindows[j].customerQue);
			bank->queWindows[j].sumPerson++;
			//���������ͳ��
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
		printf("���繲�ƽӴ�����%d��\n", numMoon);
}

double StaticInfoShow(Bank* bank, int numCustomer ) {


	double a = 0;//�ܵĹ˿Ͷ���ʱ��
	int numSer = 0;//�����ܵķ�������

	for (int k = 0; k < bank->windowsNum; k++) {
		a += bank->queWindows[k].sumTime.tmMin;
		numSer += bank->queWindows[k].sumPerson;
	}

	printf("--------------------------����Ϊ������Ϣ--------------------------\n");
	printf("|\n|\n|\n");
	printf("|���칲�Ӵ�%d���˿ͣ�����������%d,����˿͵�ƽ������ʱ��Ϊ��%.1fmin\n", numCustomer, numSer, a / bank->sumCustomer);
	printf("|\n|\n|\n");
	printf("--------------------------����Ϊ��̨��Ϣ--------------------------\n");
	for (int k = 0; k < bank->windowsNum; k++) {
		printf("��%d�Ŵ�̨���Ӵ���������%d�ˣ��˿͵ĵȴ�ʱ��%dmin\n", k + 1, bank->queWindows[k].sumPerson, bank->queWindows[k].sumTime.tmMin);
	}
	printf("------------------------------------------------------------------\n");

	//printf("--------------����Ϊһ�����Ϣ---------------\n");
	//printf("����˿͵�ƽ������ʱ��Ϊ��%.1fmin\n",a/bank->sumCustomer);
	return a;
}

double BankSimulation_Day(int numCustomer , bool midRest ) {//ģ������ģ��һ��
	/*����˵����
	*	numCustomer:��ʾ����ĵȴ��˿�����������������ȴ��˿�����
	*	midRest:��ʾ�����Ƿ�����
	*/

	//�Ծ���ʱ�����
	Bank bank;
	Time time;
	//���г�ʼ��
	InitBank(&bank, midRest);
	//����ǰ�Ĺ˿͵ȴ����г�ʼ��(�����ʼ��)
	genCustomer(&bank, numCustomer);
	//��ʱ����ʼ��
	Time timer;
	timer.tmHour = bank.startTime.tmHour;
	timer.tmMin = bank.startTime.tmMin;
	//���ж�̬ˢ�£�����ʱ��
	dynamicBank(&bank, timer);
	//�����ռ���չʾ
	double dayTime = StaticInfoShow(&bank, numCustomer);
	//����һ��Ĺ˿�ƽ���ȴ�ʱ��
	return dayTime / bank.sumCustomer;
}
