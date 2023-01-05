// 긴 문자열을 구분문자를 이용해 짜르는걸 tokenizing 이라고 한다.
// strtok을 이용

#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[] = "now # is the time # to start preparing ### for the exam#"; // 대상 문자열
	char* str2 = NULL;
	char delim[] = "#"; // 구분 문자

	char* token = strtok_s(str, delim, &str2); 
	// str을 delim(구분문자)로 구분하는 함수, delim이 연속해서 나와도(###) 1개로 인식(#)해서 구분
	// str2 == 자르고 남은 문자열을 저장하는 위치
	
	while (token != NULL)
	{
		printf("next token is: %s:%d\n", token, strlen(token));
		token = strtok_s(NULL, delim, &str2); 
		// null을 넣어 이전에 찾았던 토큰 바로 다음 문자부터 다음 구분문자까지 분리
		// null이 아닌 str을 넣을경우 같은 문자만 나온다.
	}

	return 0;
	/* 출력 예시
	* 공백을 포함하여 구분한다.
	next token is : now :4
	next token is :  is the time : 13
	next token is :  to start preparing : 20
	next token is :  for the exam: 13
	*/
}