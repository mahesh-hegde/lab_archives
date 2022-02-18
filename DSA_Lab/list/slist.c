#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	int val;
	struct node *next;
} Node;

Node *node_ref(int val, Node *next) {
	Node *nd = (Node *)malloc(sizeof(Node));
	nd->val = val;
	nd->next = next;
	return nd;
}

Node node(int val, Node *next) {
	Node nd = {.val = val, .next = next};
	return nd;
}

Node *last_node(Node *list) {
    if (!list) return NULL;
    while(list->next) {
		list = list->next;
	}
	return list;
}

Node *find_val(Node *list, int val, int *result) {
	int count = 0;
	*result = -1;
	if(list == NULL) return NULL;
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

Node *delete_end(Node *list) {
	Node *temp, *begin = list;
	if (list == NULL) return NULL;
	if (list->next == NULL) {
		free(list);
		return NULL;
	}
	while(list->next->next != NULL) {
		list = list->next;
	}
	temp = list->next;
	list->next = list->next->next;
	free(list->next);
	return begin;
}

Node *delete_front(Node *list) {
	Node *temp;
	if (list == NULL) return NULL;
	temp = list->next;
	free(list);
	return temp;
}

void delete_list(Node *list) {
	while(list != NULL) {
		Node *temp = list;
		list = list->next;
		free(temp);
	}
}

Node *read_list() {
	int n;
	Node nd = node(-1,NULL);
	Node *nd_ref = &nd;
	while(scanf("%d", &n) == 1) {
		nd_ref->next = node_ref(n,NULL);
		nd_ref = nd_ref->next;
	}
	scanf("end");
	return nd.next;
}

void print_list(Node *list) {
	printf("\e[31;1m");
    if (list == NULL) printf("[Empty List]");
	while(list) {
		printf("%d ", list->val);
		list = list->next;
	}
	printf("\e[0m\n");
}

Node *insert(Node *prev, int val) {
	if (prev == NULL) return node_ref(val, NULL);
	prev->next = node_ref(val, prev->next);
	return prev;
}

void remove_next(Node *prev) {
	Node *next = prev->next;
	if (next) {
		prev->next = next->next;
		free(next);
	}
}

int main(int argc, char **argv) {
	int choice, n, result;
	Node *list;
	printf("Enter list elements: ");
	list = read_list();
	print_list(list);
    while(1) {
        printf("0. Exit  ");
        printf("1. Insert at end  ");
        printf("2. find  ");
	printf("3. delete front  ");
	printf("4. delete end\n");
	printf("5. Re-enter list\n");
        scanf(" %d", &choice);
        switch(choice) {
        case 0: return 0;
        case 1: printf("Enter number to insert: ");
            scanf("%d", &n);
            if (list == NULL) {
                list = node_ref(n,NULL);
            } else {
                insert(last_node(list),n);
            }
            break;
        case 2: printf("Enter number to search for: ");
            scanf("%d", &n);
            find_val(list, n, &result);
            if (result != -1) {
                printf("\e[32m%d found at %d\e[0m\n", n, result);	
            } else {
                printf("\e[32m%d not found\e[0m\n", n);
            }
	    break;
	case 3: list = delete_front(list);
		break;
	case 4: list = delete_end(list);
		break;
	case 5: delete_list(list);
		printf("enter values in new list: ");
		list = read_list();
		break;
        default: printf("Invalid choice, try again\n");
        }
        print_list(list);
    }
    return 0;
}
