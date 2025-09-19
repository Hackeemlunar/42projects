/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:17:11 by kahiatak          #+#    #+#             */
/*   Updated: 2025/09/16 14:59:16 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *link;
};

struct linked_list
{
	int size;
	struct node *head;
};

struct node *head = NULL;

void insertEnd(int value)
{
	struct node *newNode = (struct node *)malloc(sizeof(struct node));
	if (!newNode)
	{
		printf("Memory Allocation failed");
		return;
	}
	newNode->data = value;
	newNode->link = NULL;
	if (head == NULL)
	{
		head = newNode;
	}
	else
	{
		struct node *temp = head;
		while (temp->link != NULL)
		{
			temp = temp->link;
		}
		temp->link = newNode;
	}
}

void displayList()
{
	int i;
	i = 0;
	struct node *ptr;
	ptr = head;
	if (ptr == NULL)
	{
		printf("\nNo nodes Available\n");
		return;
	}
	while (ptr != NULL)
	{
		printf("\nNode %d: %d\n", i, ptr->data);
		ptr = ptr->link;
		i++;
	}
	printf("\n\nTotal Nodes Available :  %d\n", i);
}

void deleteNode(int value)
{
	int i = 1;
	struct node *ptr;
	struct node *prev;
	prev = NULL;

	ptr = head;
	if (ptr == NULL)
	{
		printf("\nNo nodes Available or No node with such value found\n");
		return;
	}
	while (ptr != NULL)
	{
		if (ptr->data == value)
		{
			if (prev == NULL)
			{
				head = ptr->link;
			}
			else
			{
				prev->link = ptr->link;
			}
			free(ptr);
			printf("\nYou have deleted node %d\n", i);
			return;
		}
		i++;
		prev = ptr;
		ptr = ptr->link;
	}
}

int main()
{
	int i;
	int value;
	while (1)
	{
		printf("\n1. Insert\n2. Display List\n3. Delete\n4. Exit\n\n");
		printf("\nChoose a task to perform : ");
		scanf("%d", &i);
		switch (i)
		{
		case 1:
			printf("\nEnter a value to store : ");
			scanf("%d", &value);
			insertEnd(value);
			printf("\nYou have successfully added a new node with value : %d\n", value);
			break;
		case 2:
			displayList();
			break;
		case 3:
			printf("\nEnter a value delete : ");
			scanf("%d", &value);
			deleteNode(value);
			printf("\nYou have successfully deleted the first node with the value : %d\n", value);
			break;
		case 4:
			return 0;
		default:
			printf("Invalid entry, Only integers from 0 to 4 is allowed");
		}
	}
}