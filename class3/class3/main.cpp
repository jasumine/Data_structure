#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

// text[0]은 문자로 시작해야한다.
// 공백이면 없애준다
// 직전문자가 공백이 아니면 넘어간다.
int main()
{
	string text;
	while (1)
	{
		cout << "$";
		getline(cin, text);
		
		int size = text.size();

		// text[0]가 0이 아닐때까지 반복
		while (text[0] == ' ')
		{
			text.erase(0, 0);
			size--;
			for (int i = 0; i < text.size(); i++)
			{
				text[i] = text[i + 1];
			}
		}

		for (int i = 0; i < size; i++)
		{
			// 문자이거나, 공백인데 직전이 문자인 경우 ==continue 나머지 erase
			if (text[i] != ' ' || (text[i] == ' ' && text[i - 1] != ' '))
			{
				continue;
			}
			else
			{
				// 공백이 아닐때까지 반복
				while (text[i] ==' ')
				{
					text.erase(i, 0); 
					for (int j = i; j < size; j++)
					{
						text[j] = text[j + 1];
					}
					size--;
				}
			}

		}

		// 문자 끝이 공백이라면 비워준다.
		if (text[size-1] == ' ')
		{
			text[size - 1] = NULL;
			size--;
		}

		cout << text << ":" << size << endl;
	}
	return 0;
}