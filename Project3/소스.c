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
		printf("a형의 특징 : 부드럽고 섬세한 성격\n");
		break;

	case 'B':
	case 'b':
		printf("b형의 특징 : 주위 변화에 민감하게 대응\n");
		break;

	case 'C':
	case 'c':
		printf("AB형의 특징 : 대립하는 의견을 원만히 해결\n");
		break;

	case 'O': 
	case 'o':
		printf("O형의 특징 : 자기가 믿는 바를 끝까지 이행\n");
		break;

		default:
		printf("알파벳은 abco 만 허용\n");
		break;
	}
	return 0;

}