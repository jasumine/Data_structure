#include "telephone.h"


void telephone::init_directory()
{
	names = (char**)malloc(INIT_CAPACITY * sizeof(char*));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char*)); // 메모리를 숫자로 직접 적는것 보다 바람직하다
}

void telephone::process_command()
{
	char command_line[BUFFER_SIZE];
	char* command, * argument1, * argument2;
	char* command2;

	while (1)
	{
		printf("$ ");

		if (read_line(command_line, BUFFER_SIZE) <= 0) // 아무것도 입력하지 않았다면
			continue; // 아래 코드를 건너뛰고 처음으로  돌아간다.

		command = strtok_s(command_line, " ", &command2);
		if (command == NULL) continue;

		// read
		if (strcmp(command, "read") == 0)
		{
			argument1 = strtok_s(NULL, " ", &command2);
			if (argument1 == NULL)
			{
				printf("File name required.\n");
				continue;
			}
			load(argument1);
		}

		// add
		else if (strcmp(command, "add") == 0)
		{
			argument1 = strtok_s(NULL, " ", &command2); // add 뒤에오는 것은 name이고,
			argument2 = strtok_s(NULL, " ", &command2); // 이름뒤에 오는것은 number임

			if (argument1 == NULL || argument2 == NULL) // 둘중 하나라도 비어있다 == 입력되지 않음
			{
				printf("Invalid arguments/\n");
				continue;
			}

			add(argument1, argument2); // 둘다 채워져있을경우 add함수 호출
			printf("%s was added successfully.\n", argument1);
		}

		//find
		else if (strcmp(command, "find") == 0)
		{
			argument1 = strtok_s(NULL, " ", &command2);
			if (argument1 == NULL) // 이름이 입력되지 않으면,
			{
				printf("Invalid arguments/\n");
				continue;
			}
			find(argument1); // 입력되면 find 함수 호출
		}

		// status
		else if (strcmp(command, "status") == 0)
			status();

		// delete
		else if (strcmp(command, "delete") == 0)
		{
			argument1 = strtok_s(NULL, " ", &command2);
			if (argument1 == NULL) // 이름이 입력되지 않으면,
			{
				printf("Invalid arguments/\n");
				continue;
			}
			remove(argument1); // 입력되면 remove 함수 호출
		}
	}
}

int telephone::read_line(char str[], int limit) // 배열 str과, str의 크기 == limit
{
	int ch, i = 0;

	while ((ch = getchar()) != '\n') // 줄바꿈 문자가 나오기 전까지 읽는다.
	{
		if (i < limit - 1) // 배열의 크기를 초과하지 않을만큼 저장
			str[i++] = ch;
	}
	str[i] = '/0'; // 마지막에는 널문자를 넣는다.

	return i; //  실제로 읽은 문자수를 반환
}

void telephone::load(char* fileName)
{
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	FILE* fp = NULL;
	if (fopen_s(&fp,fileName, "r") != 0)
	{
		printf("Open faild.\n");
		return;
	}
	 
	while (fscanf_s(fp, "%s", buf1) != EOF)
	{
		fscanf_s(fp, "%s", buf2);
		add(buf1, buf2);
	}
	fclose(fp);
}

void telephone::add(char* name, char* number)
{
	if (n >= capacity) // 여유공간이 없을경우 재할당
	{
		reallocate();
	}

	// 이름을 알파벳 순으로 정렬
	int i = n - 1;
	while (i >= 0 && strcmp(names[i], name) > 0)
	{
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}

	names[i + 1] = _strdup(name);
	numbers[i + 1] = _strdup(number);

	n++;
}

void telephone::status()
{
	for (int i = 0; i < n; i++)
	{
		printf("%s %s\n", names[i], numbers[i]);
		printf("Total %d persons.\n", n);
	}
}

void telephone::find(char* name)
{
	int index = search(name);
	if (index == -1) printf("No person named '%s' exists.\n", name);
	else printf("%s\n", numbers[index]);
}

int telephone::search(char* name)
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(name, names[i]) == 0)
		{
			return i;
		}
		return -1;
	}
}

void telephone::remove(char* name)
{
	int i = search(name);
	if (i == -1)
	{
		printf("No person named '%s' exists.\n", name);
		return;
	}
	for (int j = i; j < n - 1; j++)
	{
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully. \n", name);
}

void telephone::save(char* fileName)
{
	FILE* fp;
	if (fopen_s(&fp,fileName, "w") !=0)
	{
		printf("Open failed. \n");
		return;
	}
	for (int i = 0; i < n; i++)
	{
		fprintf(fp, "%s %s \n", names[i], numbers[i]);
	}
	fclose(fp);
}

void telephone::reallocate()
{ 
	// 배열의 크기가 2배인 배열을 새로 할당한다.
	capacity *= 2;
	char** tmp1 = (char**)malloc(capacity * sizeof(char*));
	char** tmp2 = (char**)malloc(capacity * sizeof(char*));

	for (int i = 0; i < n; i++)
	{
		// 새로운 배열에 복사
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}

	// 메모리 해제
	free(names);
	free(numbers);

	// 포인터 변수가 새로운 배열을 가르키도록 한다.
	names = tmp1;
	numbers = tmp2;
}