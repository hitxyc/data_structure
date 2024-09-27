#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct LNode* List;
typedef struct LNode {
	int a;
	int e;
	struct LNode * next;
};

List create(int a, int e);
void insertList(List h, List nw);
void output(List h);
void Free(List h);
int get_a(List h, int n);
int get_e(List h, int n);
List multiply(List head1, List head2);
List add(List head1, List head2);
int main()
{
	int i;
	int n1, n2;//n1 n2 为多项式的项数
	List head1, head2;
	head1 = (List)malloc(sizeof(struct LNode));
	head2 = (List)malloc(sizeof(struct LNode));
	head1->next = NULL;
	head2->next = NULL;
	scanf("%d", &n1);
	head1->e = n1;
	for (i = 0; i < n1; i++) {
		int a, e;
		scanf("%d %d", &a, &e);
		if (a != 0) {
			List p = create(a, e);
			insertList(head1, p);
		}
	}
	scanf("%d", &n2);
	 head2->e = n2;
	for (i = 0; i < n2; i++) {
		int a, e;
		scanf("%d %d", &a, &e);
		if (a != 0) {
			List p = create(a, e);
			insertList(head2, p);
		}
	}
	List mul = multiply(head1, head2);
	List addition = add(head1, head2);
	output(mul);
	printf("\n");
	output(addition);
	Free(head1);
	Free(head2);
	Free(addition);
	Free(mul);
	return 0;
}
struct LNode* create(int a, int e)
{
	List list;
	list = (List)malloc(sizeof(struct LNode));
	list->a = a;
	list->e = e;
	list->next = NULL;
	return list;
}
void insertList(List h, List nw)
{
	List p, q;
	p = h;
	q = p->next;
	if (q == NULL) {
		p->next = nw;
	}
	else {
		while (q != 0)
		{
			//将nw降次插入链表
			if (nw->e < q->e) {
				p = q;
				q = p->next;
			}
			else break;
		}
		if (q != NULL && nw->e == q->e) {
			//如果两指数相等，就合并
			q->a = q->a + nw->a;
			free(nw);
			if (q->a == 0) {
				p->next = q->next;
				free(q);
			}
		}
		else {
			nw->next = p->next;
			p->next = nw;
		}
	}
}
void output(List h)
{
	List p, q;
	p = h;
	q = p->next;
	int count = 0;
	while (q != 0) {
		if (count == 0) { 
			printf("%d %d", q->a, q->e); 
			count++;
		}
		else printf(" %d %d", q->a, q->e);
		p = q;
		q = p->next;
	}
	//当为空链表时输出0 0
	if (p == h) printf("0 0");
}
void Free(List h)
{
	List p, q;
	p = h;
	q = p->next;
	while (q != 0) {
		p->next = q->next;
		free(q);
		q = p->next;
	}
	free(h);
}
int get_a(List h, int n)
{
	int i;
	int ret;
	List p, q;
	p = h;
	q = p->next;
	for (i = 0; i < n; i++) {
		if (q == 0) break;
		p = q;
		q = p->next;
	}
	if (i == 0) ret = 0;
	else ret = p->a;
	return ret;
}
int get_e(List h, int n)
{
	int i;
	int ret;
	List p, q;
	p = h;
	q = p->next;
	for (i = 0; i < n; i++) {
		if (q == 0) break;
		p = q;
		q = p->next;
	}
	if (i == 0) ret = 0;
	else ret = p->e;
	return ret;
}
List multiply(List head1, List head2)
{
	int i, j;
	int an, en;
	List h = (List)malloc(sizeof(struct LNode));
	h->next = NULL;
	for (i = 0; i < head1->e; i++) {
		for (j = 0; j < head2->e; j++) {
			an = get_a(head1, i + 1) * get_a(head2, j + 1);
			en = get_e(head1, i + 1) + get_e(head2, j + 1);
			if (an != 0) {
				List p = create(an, en);
				insertList(h, p);
			}
		}
	}
	return h;
}
List add(List head1, List head2)
{
	int i;
	int a, e;
	List h = (List)malloc(sizeof(struct LNode));
	h->next = NULL;
	for (i = 0; i < head1->e; i++) {
		a = get_a(head1, i + 1);
		e = get_e(head1, i + 1);
		if (a != 0) {
			List p = create(a, e);
			insertList(h, p);
		}
	}
	for (i = 0; i < head2->e; i++) {
		a = get_a(head2, i + 1);
		e = get_e(head2, i + 1);
		if (a != 0) {
			List p = create(a, e);
			insertList(h, p);
		}
	}
	return h;
}
