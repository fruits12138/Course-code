#include"queue.h"
#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include < vector> 
#include<sstream>
using namespace std;





int main() {
	srand(2011); // ʹ�õ�ǰʱ����Ϊ����
	cout << genRand(0, 60) << endl;

	//-------------����˵��-------------
	double aver = 0,i,totalTime=0;
	int numCustomer[7];
	int flag = 0;//�Զ������ֶ���0/1��
	int num = 0;//�ܵ����нӴ�����
	int workday = 6;//һ�ܹ�������
	int mid = 0;//�����Ƿ�����

	//BankSimulation_Day(100, true);
	printf("�����Զ�ģ�⣨demo��������0���ֶ�ģ�⣺����1��");
	scanf_s("%d", &flag);

	if (flag) {
		printf("\n----------------������������Щ���еĻ�����Ϣ---------------------\n");
		printf("����һ�ܹ���������");
		scanf_s("%d", &workday);
		printf("\n���������Ƿ�����(0�����ݣ�1����)��");
		scanf_s("%d", &mid);
		printf("\n�����������%d��ÿ�쵽��Ŀͻ�������Ĭ��20�ˣ���",workday);
		printf("\n-------------------------------------------------------------------\n");
		//BankSimulation_Day();
		for (int k = 0; k < workday; k++) {
			printf("��%d�쵽��:", k + 1);
			scanf_s("%d��\n", &numCustomer[k]);
			num += numCustomer[k];
			i = BankSimulation_Day(numCustomer[k],(bool)mid);
			totalTime += i * numCustomer[k];
		}
	}
	else {
		printf("-------------------------------------------------\n");
		printf("-\n-\n-\n");
		printf("����Ϊ���еĻ�����Ϣ��һ�ܹ���6�죬������Ϣ�����粻��Ϣ\n");
		printf("-\n-\n-\n");
		printf("-------------------------------------------------\n");
		for (int k = 0; k < workday; k++) {
			printf("��%d�쵽��:20��\n", k + 1);
			i = BankSimulation_Day();
			totalTime += i * 20;
		}
		num = 20 * workday;
	}
	
	printf("**************************����Ϊһ�ܵ�����**************************\n");
	printf("�ͻ���һ�ܹ�����ƽ������ʱ��Ϊ%.1fmin,������Ϊ%d��,�ܵĽӴ�����Ϊ%d��", totalTime / num,workday,num);
	system("pause");
	return 0;
}
