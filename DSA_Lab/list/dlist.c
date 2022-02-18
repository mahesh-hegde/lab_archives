#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int val;
	struct node *prev, *next;
} Node;

Node *node_ref(int val, Node *prev, Node *next) {
	Node *nd = (Node *)malloc(sizeof(Node));
	nd->val = val;
	nd->prev = prev;
	nd->next = next;
	return nd;
}

Node node(int val, Node *prev, Node *next) {
	Node nd = {.val = val, .prev = prev, .next = next};
	return nd;
}

Node *delete_end(Node *list) {
	Node *temp = NULL, *begin = list;
	if (list == NULL) return NULL;
	if (list->next == NULL) {
		free(list);
		return NULL;
	}

	while(list->next->next != NULL) {
		list = list->next;
	}

	temp = list->next;
	list->next = NULL;
	free(list->next);
	return begin;
}

Node *delete_front(Node *list) {
	Node *temp;
	if (list == NULL) return NULL;
	temp = list->next;
	free(list);
	if (temp) temp->prev = NULL;
	return temp;
}

void delete_list(Node *list) {
	while(list != NULL) {
		Node *temp = list;
		list = list->next;
		free(temp);
	}
}

Node *first_node(Node *end) {
	if (end == NULL) return NULL;
	while(end->prev) {
		end = end->prev;
	}
	return end;
}

Node *last_node(Node *list) {
	if (!list) return NULL;
	while(list->next) {
		list = list->next;
	}
	return list;
}

Node *find_rev(Node *end, int val, int *result) {
	int count = 0;
	*result = -1;
	while(end) {
		if (end->val == val) {
			*result = count;
			return end;
		}
		end = end->prev;
		count++;
	}
	return end;
}

Node *find_val(Node *list, int val, int *result) {
	int count = 0;
	*result = -1;
	while(list) {
		if (list->val == val) {
			*result = count;
			return list;
		}
		list = list->next;
		count++;
	}
	return list;
}

Node *read_list() {
	int n;
	Node nd = node(-1,NULL,NULL);
	Node *nd_ref = &nd;
	while(scanf("%d", &n) == 1) {
		nd_ref->next = node_ref(n,nd_ref,NULL);
		nd_ref = nd_ref->next;
	}
	scanf("end");
	if (nd.next) {
		(nd.next)->prev = NULL;
	}
	return nd.next;
}

void print_list(Node *list) {
	printf("\e[31;1mList = ");
	if (list == NULL) printf("[Empty List]");
	while(list) {
		printf("%d ", list->val);
		list = list->next;
	}
	printf("\e[0m\n");
}

Node *insert(Node *prev, int val) {
	if (prev == NULL) return node_ref(val,NULL,NULL);
	prev->next = node_ref(val,prev,prev->next);
	return prev;
}

void remove_next(Node *prev) {
	Node *next = prev->next;
	if (next) {
		prev->next = next->next;
		free(next);
	}
}

int count(Node *list) {
	return (list == NULL) ? 0 : 1 + count(list->next);
}

int main() {
	int choice, n, result;
	Node *list;
	printf("Enter list elements, terminated by \'end\': ");
	list = read_list();
	print_list(list);
	while(1) {
		printf("0. Exit  ");
		printf("1. Insert  ");
		printf("2. find ");
		printf("3. find backwards\n");
		printf("4. delete front  ");
		printf("5. delete end  ");
		printf("6. re-enter list\n");
		printf("7. Count\n");

		scanf(" %d", &choice);
		switch(choice) {
			case 0: return 0;
			case 1: printf("Enter number to insert: ");
				scanf("%d", &n);
				if (list == NULL) {
					list = node_ref(n,NULL,NULL);
				} else {
					insert(last_node(list),n);
				}
				break;
			case 2: printf("Enter number to search for: ");
				scanf("%d", &n);
				find_val(list, n, &result);
				if (result != -1) {
					printf("\e[32m%d found at %d\e[0m\n", n,
					       result);
				} else {
					printf("\e[32m%d not found\e[0m\n", n);
				}
				break;
			case 3: printf("Enter number to search for: ");
				scanf("%d", &n);
				find_rev(last_node(list),n,&result);
				if (result != -1) {
					printf("\e[32m%d found at %d from end\e[0m\n", n,
					       result);
				} else {
					printf("\e[32m%d not found\e[0m\n", n);
				}
				break;
			case 4: list = delete_front(list);
				break;
			case 5: list = delete_end(list);
				break;
			case 6: delete_list(list);
				printf("Enter values in new list:  ");
				list = read_list();
				break;
			case 7: printf("count = %d\n", count(list));
				break;
			default: printf("Invalid choice, try again\n");
		}
		print_list(list);
	}
	return 0;
}
