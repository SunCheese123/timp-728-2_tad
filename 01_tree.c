#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// определяем элемент списка
typedef struct node_q {
        struct node *value;   // узел дерева в очереди
        struct node_q *next;  // ссылка на следующий элемент списка
} node_q;

// определяем сам список
typedef struct list {
        struct node_q *head;  // начало списка
        struct node_q *tail;
        struct node_q *current;
} list;

// Структура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node {
        int value;
        struct node *left;
        struct node *right;
        struct node *parent;
} node;

// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree {
        struct node *counter;
        struct node *current;
        struct node *root;
        int numbers;
} tree;

bool is_empty_queue(list *l)
{
	if (l->head == NULL)
		return 1;
	else
		return 0;
}

// инициализация пустого списка
void init_queue(list *l)
{
  l->head = NULL;
}

// удалить все элементы из списка
void clean_queue(list *l)
{
        while (l->head != NULL)
        {
                l->current = l->head;
                l->head = l->head->next;
                free(l->current);
        }
}

// вставка значения в конец списка, вернуть 0 если успешно
int add(list *l, node *t)
{
        l->tail = l->head;
        if (l->tail != NULL)
        {
                while (l->tail->next != NULL)
                {
                        l->tail = l->tail->next;
                }
                l-> current = malloc(sizeof(node_q));
                l->current->value = t;
                l->current->next = NULL;
                l->tail->next = l->current;
                return 0;
                }
        else
        {
                l->current = malloc(sizeof(node_q));
                l->current->value = t;
                l->current->next = NULL;
                l->head = l->current;
        }
}

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
node_q *del(list *l)
{
	node_q *counter = NULL;
        if (l->head == NULL)
        {
		printf("_");
                return 0;
        }
	counter = l->head;
        l->head = l->head->next;
        return counter;
}

// Инициализация дерева
void init(tree* t)
{
	t->root=NULL;
}

node* returnroot(tree* t) //Функция, которая возвращает указатель на корень
{
	return t->root;
} 

node* clear(node* t) //рекурсивная функция чистки
{
	if(t!=NULL)
	{
		clear(t->left); //рекрсивно чистим левого потомка
		clear(t->right); //рекурсивно чистим парвого потомка
		if(t->parent!=NULL)
			t->parent = NULL;
		if(t->left!=NULL)
			t->left = NULL;
		if(t->right!=NULL)
			t->right = NULL;
		free(t); //освобождаем память
	}
	return NULL;
}

// Удалить все элементы из дерева
void clean(tree* t)
{
        node* newroot = returnroot(t); //получаем указатель на корень
        clear(newroot); //вызываем функцию для чистки дерева
        t->root = NULL;
}


// Поиск элемента по значению. Вернуть NULL если элемент не найден
node* find(tree* t, int value)
{
	t->current = t->root; //начинаем поиск с корня
	while(t->current->value != value) //пока не нашли нужный узел
	{
		if(t->current->value > value) //если значение, которое нужно найти меньше значения в узле
		{
			t->current = t->current->left; //переходим в левого потомка
		}
		else
		{
			t->current = t->current->right; // переходим в правого потомка
		}
		if(t->current == NULL) //если не нашли нужный узел
		{
			return NULL;
		}
	}
	return t->current; //возвращаем указатель на узел с нужным значением
}

void print_num(tree* t) //функция для вывода количества элементов в списке
{
	printf("%d", t->numbers);
}

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
int insert(tree* t, int value)
{
	node *root2 = t->root, *root3 = NULL; //переменные счётчики для нахождения нужного места
	t->current = malloc(sizeof(node)); //выделяем память под новый узел дерева
	t->current->value = value; //присваиваем значение новому узлу
	if (t->root == NULL) //если дерево пусто
	{
		t->current->parent = NULL; //родитель корня - нуль
		t->current->left = NULL; //левый потомок корня - нуль
		t->current->right = NULL; //правый потомок корня  нуль
		t->root = t->current; //присваиваем указатель корня - нашему новому узлу
		t->numbers = 1; //увеличиваем число узлов
		return 0; //конец
	}
	while (root2 != NULL) //ведём поиск нужного места для вставки //если счётчик не нуль
	{
		root3 = root2; //присваиваем второму счётчику значение первого
		if (value == root2->value) //если значение уже есть в дереве
                {
                        return 1; //конец
                }
		if (value < root2->value) //если значение нового узла меньше чем то, которое в узле счётчика
		{
			root2 = root2->left; // счётчик переходит в левого потомка
		}
		else //иначе
		{
			root2 = root2->right; // переход в правого
		}
	} //когда root2 дойдёт до нулевого узла - у root3 всё ещё будет значение предыдущего узла
	t->current->parent = root3; //присваиваем новому узлу ссылку на родитителя - узел со счётчиком root3
	t->current->left = NULL; //оба предка нового узла - нули
	t->current->right = NULL;
	if (value < root3->value) //если значение в новом узле меньше чем в узле родителе
	{
		root3->left = t->current; //новый узел - левый предок
		t->numbers = t->numbers + 1; //увеличиваем число узлов
		return 0; //конец
	}
	if (value > root3->value) //если значение в номо узле больше чем в узле родителе
	{
		root3->right = t->current; //новый узел - правый предок
		t->numbers = t->numbers +1; // увеличиваем число узлов
		return 0; //конец
	}
}

// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента

int remove_min(node* n)
{
	int b;
	node *curr = n; //curr - корень поддерева
	while (curr->left != NULL) //пока слева не нуль ищем минимум
	{
		curr = curr->left; //переходим влево 
	}
	b = curr->value; //минимум найден присваивем новой переменной его значение
	if(curr->right != NULL)
	{
		if(b < curr->parent->value)
		{
			curr->parent->left = curr->right;
			free(curr);
			return b;
		}
		else
		{
			curr->parent->right = curr->right;
			free(curr);
			return b;
		}
	}
	else
	{
		if (b < curr->parent->value)
		{
			curr->parent->left = NULL;
			free(curr);
			return b;
		}
		else
		{
			curr->parent->right = NULL;
			free(curr);
			return b;
		}
	}
}

// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree* t, int value)
{
	int b;
	node *todel = find(t, value); //находим нужный узел, присваиваем переменной todel указатель на неё
	if (todel == NULL) //если узла нет возвращаем 1
		return 1;
	if (todel->left==NULL && todel->right==NULL) //если найденный элемент - лист
	{
		if(todel != t->root) //если лист не корень
		{
			if (todel->value < todel->parent->value) //если значение в листе меньше чем в родителе, значит лист - левый потомок
			{
				todel->parent->left = NULL; //зануляем левого потомка
				free(todel); //освобождаем память
				t->numbers = t->numbers-1; // уменьшаем количество элементов в дереве
				return 0; //конец
			}
			else //иначе - лист правый потомок
			{
				todel->parent->right = NULL; //зануляем правого потомка
				free(todel); //освобождаем память
				t->numbers = t->numbers-1; //уменьшаем количество элементов в списке
				return 0; //конец
			}
		}
		else //если лист корень
		{
			free(todel); //освобождаем память
			t->root = NULL; //указатель на корень - NULL
			t->numbers = 0;
			return 0; //конец
		}
	}
	if (todel->left==NULL && todel->right!=NULL) //если у найденного элемента нет левого потомка, но есть правый
	{
		if(todel != t->root) //если элемент - не корень
		{
			if (todel->value < todel->parent->value) //если элемент - левый потомок родителя
			{
				todel->parent->left = todel->right; //левым потомком родителя становится единственный потомок удаляемого элемента (правый)
				todel->right->parent = todel->parent; //родителем единственного потомка становится родитель удаляемого элемента
				free(todel); //освобождаем память
				t->numbers = t->numbers-1; //уменьшаем количество элементов
				return 0; //конец
			}
			else //если элемент - правый потомок родителя
			{
				todel->parent->right = todel->right; //правым потомком родителя становится единственный потомок удаляемого элемента (правый)
				todel->right->parent = todel->parent; //родителем единственного потомка становится родитель удаляемого элемента
				free(todel); //освобождаем память
				t->numbers = t->numbers-1; //уменьшаем количество элементов
				return 0; //конец
			}
		}
		else // если элемент - корень
		{
			todel->right->parent = NULL; //родитель единственного потомка - нуль
			t->root = todel->right; //указатель на корень передаётся единственному потомку
			free(todel); //освобождаем память
			t->numbers = t->numbers-1; //уменьшаем количество элементов
			return 0; //конец
		}
	}
	if (todel->left!=NULL && todel->right==NULL) //если у найденного элемента нет правого потомка, но есть левый
	{
		if(todel !=t->root) //если элемент не корень
		{
			if (todel->value < todel->parent->value) //если элемент - правый потомок родителя
			{
				todel->parent->left = todel->left;
				todel->left->parent = todel->parent;
				free(todel);
				t->numbers = t->numbers-1;
				return 0;
			}
			else //элемент - левый потомок родителя
			{
				todel->parent->right = todel->left;
				todel->left->parent = todel->parent;
				free(todel);
				t->numbers = t->numbers-1;
				return 0;
			}
		}
		else //если элемент - корень
		{
			todel->left->parent = NULL; //родитель единственного потомка - нуль
			t->root = todel->left; //указатель на корень передаётся единственному потомку
			free(todel); //освобождаем память
			t->numbers = t->numbers-1; //умеьшаем количество элементов
			return 0; // конец
		}
	}
	if(todel->right!=NULL && todel->left!=NULL) // если есть оба потомка
	{
		b = remove_min(todel->right); //вызываем функцию удаления минимального элемента правого поддерева, которая возвращает значение удалённого элемента
		todel->value = b; //присваиваем значение бывшего минимального элемента правого поддерева нашему узлу
		t->numbers = t->numbers-1; // уменьшаем количество элементов
		return 0; //конец
	}
}

// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно 
int rotate_right(node* n)
{
	node* y = n;
	node* x = y->left;
        node* b = x->right;
        x->parent = y->parent;
        if(y->parent != NULL)
        {
                if(y->parent->value > y->value)
                {
                        y->parent->left = x;
                }
                else
                {
                        y->parent->right = x;
                }
        }
        if(b!=NULL)
        {
        b->parent = y;
        }
        y->left = b;
        y->parent = x;
        x->right = y;
        return 0;
}

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(node* n)
{
	node* x = n;
	node* y = x->right;
	node* b = y->left;
        y->parent = x->parent;
	if(x->parent != NULL)
	{
		if(x->parent->value > x->value)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}
	if(b!=NULL)
	{
	b->parent = x;
	}
	x->right = b;
	x->parent = y;
	y->left = x;
	return 0;
}

int rotate_root_left(tree* t)
{
        rotate_left(t->root);
	if (t->root->parent != NULL)
		t->root = t->root->parent;
	return 0;
}

int rotate_root_right(tree* t)
{
        rotate_right(t->root);
	if (t->root->parent != NULL)
	        t->root = t->root->parent;
        return 0;
}


// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке. 
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _. 
// Если дерево пусто, вывести -
void print(node* n);


// Вывести все значения дерева t, аналогично функции print
void print_tree(tree* t)
{
	if (t->root == NULL)
	{
		printf("-\n"); //обработка случая, когда дерево пустое
		return;
	}
	struct list list1; //первая очередь
	struct list list2; //вторая очередь
	int f=0;
	init_queue(&list1);
	init_queue(&list2);
	add(&list1, t->root);
	while(!is_empty_queue(&list1) || !is_empty_queue(&list2))  // цикл для смены очередей местами, если пустая - вернёт 1
	{
		while(!is_empty_queue(&list1)) //проверка очереди на пустоту в условии для цикла вывода первой очереди
		{
			node_q *curr = del(&list1); //удаляет первый элемент из очереди и присваивает пременной curr ссылку на бывший первый элемент
			if (curr->value == NULL) //если элемент, который обрабатываем - нуль
			{
				printf("_ "); //выводим _
				add(&list2, NULL); //добавляем нулевой элемент во вторую очередь
                		add(&list2, NULL); //добавляем нулевой элемент во вторую очередь
			}
			else //элемент, который обрабатываем не нуль
			{
				f++;
				printf("%d", curr->value->value); //выводим значение
				printf(" "); // и пробел
				add(&list2, curr->value->left); //добавляем во вторую очередь левого потомка
				add(&list2, curr->value->right); // добавляем во вторую очередь второго потомка
			}
		}
		printf("\n"); //переходим на новую строку
		if (f == t->numbers)
			return;
		while(!is_empty_queue(&list2)) //проверка второй очереди на пустоту в условии
		{
                        node_q *curr = del(&list2); //удаляет первый элемент из второй очереди и присваивает переменной curr ссылку на бывший первый элемент
                        if (curr->value == NULL) // если элемент, который обрабатываем - нуль
                        {
				printf("_ "); // выводим _
				add(&list1, NULL);
                            	add(&list1, NULL); //добавляем нулевой элемент в первую очередь 2 раза
                        }
                        else
                        {
                        	f++;
			        printf("%d", curr->value->value); //выводим значение эемента во второй очереди
                                printf(" "); //выводим пробел
				add(&list1, curr->value->left); //добавляем в первую очередь левого потомка
				add(&list1, curr->value->right); //добавляем в первую очередь правого потомка
			}
                }
		printf("\n"); // переходим на новую строчку
		if (f == t->numbers)
                        return;
	}
}

void checkrelatives(tree* t, int value)
{
	node *tmp = find(t, value);
        if(tmp==NULL)
        {
                printf("-");
                printf("\n");
        }
        else
        {
                if (tmp->parent != NULL)
                {
                printf("%d", tmp->parent->value);
                printf(" ");
                }
                else
                {
                        printf("_ ");
                }
                if(tmp->left)
                {
                        printf("%d", tmp->left->value);
                }
                else
                {
                        printf("_");
                }
                printf(" ");
                if(tmp->right)
                {
                printf("%d", tmp->right->value);
                }
                else
                {
                        printf("_");
                }
                printf("\n");
        }
        printf("\n");
}

int main()
{
	int a, i, m1, m2;
	struct tree bintree;
	init(&bintree);
	//вводим 4 числа
	for (i=0; i<4; i++)
	{
		scanf("%d", &a);
		insert(&bintree, a);
	}
	//выводим дерево
	print_tree(&bintree);
	printf("\n");
	//вводим 3 числа
	for (i=0; i<3; i++)
	{
		scanf("%d", &a);
		insert(&bintree, a);
	}
	print_tree(&bintree);
	printf("\n");
	scanf("%d", &m1);
	checkrelatives(&bintree, m1);
	scanf("%d", &m1);
        checkrelatives(&bintree, m1);
	scanf("%d", &m1);
	//удаляем узел
	remove_node(&bintree, m1);
	print_tree(&bintree);
	printf("\n");
	//ротация влево до конца
	node* newroot = returnroot(&bintree);
	if (newroot != NULL)
	{
		while (newroot->right != NULL)
		{
			rotate_root_left(&bintree);
        		newroot = returnroot(&bintree);
		}
	}
	printf("\n");
        print_tree(&bintree);
	// ротация вправо до конца
	newroot = returnroot(&bintree);
	if(newroot != NULL)
	{
	        while (newroot->left != NULL)
	        {
		        rotate_root_right(&bintree);
	                newroot = returnroot(&bintree);
	        }
        }
	printf("\n");
        print_tree(&bintree);
	//по кол-ву элементов
	printf("\n");
	print_num(&bintree);
	printf("\n\n");
	//очистка дерева
	clean(&bintree);
	print_tree(&bintree);
	return 0;
};
