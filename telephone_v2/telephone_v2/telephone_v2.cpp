#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char* names[CAPACITY];
char* numbers[CAPACITY];
int n = 0;

void add();
void find();
void status();
void remove();
void load();
void save();

int main()
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("$ ");
		scanf_s("%s", buffer);

		if (strcmp(buffer, "read") == 0) load();
		else if (strcmp(buffer, "add") == 0) add();
		else if (strcmp(buffer, "find") == 0) find();
		else if (strcmp(buffer, "status") == 0) status();
		else if (strcmp(buffer, "delete") == 0) remove();
		else if (strcmp(buffer, "save") == 0) save();
		else if (strcmp(buffer, "exit") == 0) break;
	}

	return 0;
}

void add()
{
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf_s("%s", buf1);
	scanf_s("%s", buf2);


	int i = n - 1; // n-1이 배열의 제일 끝
	while (i >= 0 && strcmp(names[i], buf1) > 0) // names[i] 사전순으로 뒤에 있을경우 1이 반환
	{
		// 이름과 번호를 다음칸에 넣으면서 자리를 마련
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	// 남은 자리에 이름과 번호를 입력
	names[i+1] = strdup(buf1);
	numbers[i+1] = strdup(buf2);
	n++; // 배열의 크기 증가

	printf("%s was added successfully.\n", buf1);

}
void find()
{
	char buf[BUFFER_SIZE];
	scanf_s("%s", buf);
	
	int index = search(buf);
	if(index == -1) printf("No Person named '%s' exists.\n", buf);
	else printf("%s\n", numbers[index]);
}
void status()
{
	for (int i = 0; i < n; i++)
	{
		printf("%s %s\n", names[i], numbers[i]);
	}
	printf("Total %d persons.\n", n);
}

void remove()
{
	char buf[BUFFER_SIZE];
	scanf_s("%s", buf);

	int index = search(buf); // 이름이 존재하지 않으면 1을 반환
	if (index == -1)
	{
		printf("No person named '%s' exists.\n", buf);
		return;
	}
	for (int j = index; j < n - 1; j++)
	{
		// 지운자리에 다음 칸의 이름을 넣는다.
		names[j] = names[j + 1];
		numbers[j] = numbers[j - 1];
	}
	n--; // 1번 지웠기에 배열의 개수도 -1
	printf(" '%s' was deleted successfully. \n", buf);
}

void load()
{
	char fileName[BUFFER_SIZE];
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	scanf_s("%s", fileName); // 파일 이름을 입력받고

	FILE* fp = fopen(fileName, "r"); // 파일을 open
	if (fp == NULL)
	{
		printf("Open faild.\n");
		return;
	}
	while ((fscanf_s(fp, "%s", buf1) != EOF)) //반복해서 배열에 저장한다.
	{
		fscanf_s(fp, "%s", buf2);
		names[n] = strdup(buf1);
		numbers[n] = strdup(buf2);
		n++;
	}

	fclose(fp); // 파일 닫기
}
void save()
{
	char fileName[BUFFER_SIZE];
	char tmp[BUFFER_SIZE];

	scanf_s("%s", tmp);
	scanf_s("%s", fileName);

	FILE* fp = fopen(fileName, "w"); // "w" = write 모드
	if (fp == NULL)
	{
		printf("Open faild.\n");
		return;
	}
	for (int i = 0; i < n; i++)
	{
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp); // 열면 꼭 닫아주기
}

int  search(char* name)
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(name, names[i])== 0)
		{
			return i;
		}
		return -1;
	}
}