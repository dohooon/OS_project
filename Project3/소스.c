#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	

int main(void)
{
	char choice;
	scanf("%c", &choice);

	switch (choice)
	{
	case 'A':
	case 'a':
		printf("a���� Ư¡ : �ε巴�� ������ ����\n");
		break;

	case 'B':
	case 'b':
		printf("b���� Ư¡ : ���� ��ȭ�� �ΰ��ϰ� ����\n");
		break;

	case 'C':
	case 'c':
		printf("AB���� Ư¡ : �븳�ϴ� �ǰ��� ������ �ذ�\n");
		break;

	case 'O': 
	case 'o':
		printf("O���� Ư¡ : �ڱⰡ �ϴ� �ٸ� ������ ����\n");
		break;

		default:
		printf("���ĺ��� abco �� ���\n");
		break;
	}
	return 0;

}