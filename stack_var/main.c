#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

struct node
{
	long long int mem[2];
	struct node* next;
};

long long int engine(struct node* head)
{
	static FILE* stream = NULL;
	if (!stream) stream = fopen("input.txt", "r");
	int input = 0;
	if (fscanf_s(stream, "%d", &input) <= 0)
	{
		if (!head->next) fclose(stream);
		return -1;
	}
	else if ((*head->mem) & 1LL << 33)
	{
		*head->mem = input;
		*head->mem &= ~(1LL << 33);
		return 2;
	}
	else switch (input)
	{
	case 1:
		*head->mem |= 1LL << 33;
		break;
	case 2:
		if (!head->next) fclose(stream);
		return 0;
		break;
	case 3:
		if(head->next) printf("%d\n", (int)(*head->next->mem));
		break;
	}
	return 1;

}

void push()
{
	static long long int flag = 0;
	static struct node* head = NULL;
	char data[sizeof(struct node)] = { 0 };
	{
		struct node* next = (struct node*)&data;
		next->next = head;
		head = next;
	}
	while (1)
	{
		flag = engine(head);
		switch (flag)
		{
		case 1:
			continue;
			break;
		case 2:
			push();
			continue;
			break;
		}
		break;
	}
	head = head->next;
}

int main(int argc, char** argv)
{
	push();
	return 0;
}