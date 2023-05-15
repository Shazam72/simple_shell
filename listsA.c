#include "shell.h"
#include "types_defines.h"

StringNode *add_string_node(StringNode **head, char *str)
{
	StringNode *new, *temp;

	new = malloc(sizeof(StringNode));
	if (new == NULL)
		return (NULL);
	new->str = (char *) malloc(sizeof(*new->str) * (_strlen(str) + 1));
	if (new->str == NULL)
		return (NULL);
	_strcpy(new->str, str);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (new);
}

/**
 * get_list_length - get list length
 * @head: list head
 * Return: list length
 */
int get_list_length(StringNode *const head)
{
	int len = 0;
	StringNode *tmp = NULL;

	if (head == NULL)
		return (0);
	tmp = head;
	for (; tmp; tmp = tmp->next)
		len++;
	return (len);
}

/**
 * delete_a_node_at_given_index - delete a node at given index
 * @head: pointer to list head
 * @index: index to delete
 * Return: 0 if no problem appear otherwise 1
 */
int delete_a_node_at_given_index(StringNode **head, unsigned int index)
{
	unsigned int list_len = 0, i = 0;
	StringNode *tmp = NULL, *tmp2 = NULL;

	if (head == NULL)
		return (1);
	tmp = *head;
	if (index == 0)
	{
		*head = tmp->next;
		free(tmp);
		return (0);
	}
	list_len = get_list_length(*head);
	if (index > list_len)
		return (1);
	for (; i < index - 1; i++)
		tmp = tmp->next;
	tmp2 = tmp->next;
	tmp->next = tmp2->next;
	free(tmp2);
	return (0);
}

/**
 * array_from_string_list - function that return an array of strings
 * from a string linked list
 * @head: list head
 * Return: a NULL terminated array of strings otherwise NULL
 */
char **array_from_string_list(StringNode *head)
{
	char **arr = NULL;
	int i = 0, list_len = 0;

	if (head == NULL)
		return (NULL);

	list_len = get_list_length(head);
	if (list_len == 0)
		return (NULL);

	arr = (char **) malloc(sizeof(*arr) * (list_len + 1));
	if (arr == NULL)
		return (NULL);
	for (i = 0; head; head = head->next)
	{
		arr[i] = malloc(sizeof(*arr[i]) * (strlen(head->str) + 1));
		if (arr[i] == NULL)
		{
			i--;
			for (; i >= 0; i--)
				free(arr[i]);
			free(arr);
			return (NULL);
		}
		strcpy(arr[i], head->str);
		i++;
	}
	arr[list_len] = NULL;
	return (arr);
}

/**
 * free_list - free a list
 * @head: list head to free
 */
void free_list(StringNode *head)
{
	StringNode *next = NULL;

	if (head == NULL)
		return;
	next = head->next;
	free(head->str);
	free(head);
	free_list(next);
}
