#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la estructura
typedef struct s_list {
    void *content;
    struct s_list *next;
} t_list;

// Implementación de ft_calloc (igual que calloc) con while
void *ft_calloc(size_t count, size_t size) {
    void *ptr = malloc(count * size);
    if (!ptr) {
        return NULL;  // Si malloc falla, devolvemos NULL
    }
    // Inicializamos la memoria a 0 usando while
    size_t i = 0;
    while (i < count * size) {
        ((unsigned char *)ptr)[i] = 0;
        i++;
    }
    return ptr;
}

// Función para crear una copia de la lista
t_list *copy_list(t_list *original) {
    t_list *copy_head = NULL;
    t_list *copy_tail = NULL;

    while (original) {
        // Usamos ft_calloc en lugar de malloc
        t_list *new_node = (t_list *)ft_calloc(1, sizeof(t_list));
        if (!new_node) {
            return NULL; // Si falla ft_calloc, retornamos NULL
        }

        new_node->content = original->content; // Copiar el contenido
        new_node->next = NULL;

        if (!copy_head) {
            copy_head = new_node;
            copy_tail = new_node;
        } else {
            copy_tail->next = new_node;
            copy_tail = new_node;
        }

        original = original->next;
    }

    return copy_head;
}

// Función para ordenar la lista (usando merge sort)
t_list *merge(t_list *left, t_list *right, int (*cmp)(void *, void *)) {
    if (!left) return right;
    if (!right) return left;

    if (cmp(left->content, right->content) <= 0) {
        left->next = merge(left->next, right, cmp);
        return left;
    } else {
        right->next = merge(left, right->next, cmp);
        return right;
    }
}

void split(t_list *head, t_list **front, t_list **back) {
    t_list *fast, *slow;
    slow = head;
    fast = head->next;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = head;
    *back = slow->next;
    slow->next = NULL;
}

t_list *merge_sort(t_list *head, int (*cmp)(void *, void *)) {
    if (!head || !head->next) return head;

    t_list *front, *back;
    split(head, &front, &back);

    front = merge_sort(front, cmp);
    back = merge_sort(back, cmp);

    return merge(front, back, cmp);
}

int cmp_string(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

// Función para imprimir la lista
void print_list(t_list *head) {
    while (head) {
        printf("%s\n", (char *)head->content);
        head = head->next;
    }
}

int main() {
    // Crear lista de ejemplo
    t_list node1 = {(void *)"Zebra", NULL};
    t_list node2 = {(void *)"Apple", NULL};
    t_list node3 = {(void *)"Mango", NULL};
    t_list node4 = {(void *)"Banana", NULL};
    node1.next = &node2;
    node2.next = &node3;
    node3.next = &node4;

    // Copiar y ordenar la lista
    t_list *copied_list = copy_list(&node1);
    t_list *sorted_list = merge_sort(copied_list, cmp_string);

    // Imprimir lista ordenada
    printf("Lista ordenada alfabéticamente:\n");
    print_list(sorted_list);

    return 0;
}
