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
	srand(2011); // 使用当前时间作为种子
	cout << genRand(0, 60) << endl;

	//-------------参数说明-------------
	double aver = 0,i,totalTime=0;
	int numCustomer[7];
	int flag = 0;//自动还是手动（0/1）
	int num = 0;//总的银行接待人数
	int workday = 6;//一周工作天数
	int mid = 0;//中午是否午休

	//BankSimulation_Day(100, true);
	printf("若想自动模拟（demo）：输入0，手动模拟：输入1：");
	scanf_s("%d", &flag);

	if (flag) {
		printf("\n----------------接下来请输入些银行的基本信息---------------------\n");
		printf("银行一周工作天数：");
		scanf_s("%d", &workday);
		printf("\n银行中午是否午休(0不午休，1午休)：");
		scanf_s("%d", &mid);
		printf("\n请输入接下来%d天每天到达的客户人数（默认20人）：",workday);
		printf("\n-------------------------------------------------------------------\n");
		//BankSimulation_Day();
		for (int k = 0; k < workday; k++) {
			printf("第%d天到达:", k + 1);
			scanf_s("%d人\n", &numCustomer[k]);
			num += numCustomer[k];
			i = BankSimulation_Day(numCustomer[k],(bool)mid);
			totalTime += i * numCustomer[k];
		}
	}
	else {
		printf("-------------------------------------------------\n");
		printf("-\n-\n-\n");
		printf("以下为银行的基本信息，一周工作6天，周天休息，中午不休息\n");
		printf("-\n-\n-\n");
		printf("-------------------------------------------------\n");
		for (int k = 0; k < workday; k++) {
			printf("第%d天到达:20人\n", k + 1);
			i = BankSimulation_Day();
			totalTime += i * 20;
		}
		num = 20 * workday;
	}
	
	printf("**************************以下为一周的数据**************************\n");
	printf("客户的一周工作日平均逗留时间为%.1fmin,工作日为%d天,总的接待人数为%d人", totalTime / num,workday,num);
	system("pause");
	return 0;
}
