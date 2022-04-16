#define _CRT_SECURE_NO_WARNINGS

#include "Tree.h"

int main()
{
	Tree* root = NULL;
	char buff[16] = { 0 };
	char c = 0;
	int value = 0;

	while (fgets(buff, 16, stdin))
	{
		sscanf(buff, "%c %d", &c, &value);

		switch (c)
		{
		case 'a':
		{
			root = Insert(root, value);
		} break;

		case 'r':
		{
			root = Delete(root, value);
		} break;

		case 'f':
		{
			if (Search(root, value) != NULL)
			{
				printf("yes\n");
			}
			else
			{
				printf("no\n");
			}
		} break;

		case 'p':
		{
			PrintTree(root);
		} break;

		default:
		{

		} break;
		}
	}

	return 0;
}
