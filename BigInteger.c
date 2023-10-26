#include <stdlib.h>
#include "BigInteger.h"
#include <stdio.h>


void signchange(struct node **head)
{
    struct node *temp = *head;
    while (temp != NULL)
    {
        temp->data = temp->data * (-1);
        temp = temp->next;
    }
}


struct BigInteger initialize(char *s)
{
    struct BigInteger p1;
    p1.head = NULL;
    struct node *itr = NULL;
    p1.sign = 1;
    int i, l = 0;
    for (i = 0; s[i] != '\0'; i++)
    {

        if (s[i] == '\n')
            break;
        if (s[i] == '-')
            p1.sign = -1;
        else
        {
            if (!itr)
            {
                p1.head = newnode(s[i] - '0');
                itr = p1.head;
            }
            else
            {
                itr = newnode(s[i] - '0');
                itr->next = p1.head;
                p1.head = itr;
            }
            l++;
        }
    }
    p1.length = l;
    return p1;
}
struct node *newnode(int val)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    if (!new)
    {
        printf("memory allocation failed");
        return NULL;
    }
    new->data = val;
    new->next = NULL;
    return new;
}

void insertAtHead(struct node **head, int val)
{
    struct node *new = (struct node *)malloc(sizeof(struct node));
    if (new == NULL)
    {
        printf("\nmemory allocation failed\n");
        return;
    }
    new->data = val;
    new->next = *head;
    *head = new;
}
void reverse(struct node **head)
{
    if (*head == NULL || (*head)->next == NULL)
        return;
    struct node *prev = NULL;
    struct node *forward = NULL;
    struct node *curr = *head;
    while (curr)
    {
        forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
    }
    *head = prev;
}




void display(struct BigInteger p1)
{
    reverse(&p1.head);
    struct node *temp = p1.head;
    if (p1.sign == -1)
        printf("-");
    while (temp)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }
    printf("\n");
    reverse(&p1.head);
}

int check0(struct node *head)
{
    while (head)
    {
        if (head->data != 0)
            return 1;
        head = head->next;
    }
    return 0;
}
struct node *addition(struct node *a, struct node *b)
{
    struct node *res = NULL, *itr;
    int carry = 0, sum = 0;

    while (a && b)
    {
        sum = a->data + b->data + carry;
        if (sum > 9)
        {
            sum -= 10;
            carry = 1;
        }
        else
            carry = 0;
        if (res == NULL)
        {

            res = newnode(sum);
            itr = res;
        }
        else
        {
            itr->next = newnode(sum);
            itr = itr->next;
        }
        a = a->next;
        b = b->next;
    }
    while (a)
    {
        if (res == NULL)
        {

            res = newnode((a)->data);
            itr = res;
        }
        else
        {
            itr->next = newnode((a)->data + carry);
            carry = 0;
            itr = itr->next;
        }
        a = a->next;
    }

    while (b) 
    {
        if (res == NULL)
        {

            res = newnode((b)->data);
            itr = res;
        }
        else
        {
            itr->next = newnode((b)->data + carry);
            carry = 0;
            itr = itr->next;
        }
        b = b->next;
    }
    if (carry) 
    {
        itr->next = newnode(carry);
        itr = itr->next;
    }
    return res;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{

    struct BigInteger res, pro;
    res.sign = 1;
    res.head = NULL;
    pro.head = NULL;
    if (!check0(a.head) || !check0(b.head))
    {
        res.head = newnode(0);
        return res;
    }
    struct node *itr = NULL, *temp = NULL, *temp1 = NULL;
    pro.sign = a.sign * b.sign;
    int sum = 0, carry = 0, c = 0, n = 0;
    while (b.head)
    {
        res.head = NULL;
        itr = NULL;
        temp = a.head;
        while (temp)
        {
            sum = temp->data * b.head->data + carry;
            carry = sum / 10;
            sum %= 10;
            if (!res.head)
            {
                res.head = newnode(sum);
                itr = res.head;
            }
            else
            {
                itr->next = newnode(sum);
                itr = itr->next;
            }
            temp = temp->next;
        }
        if (carry)
        {
            itr->next = newnode(carry);
            itr = itr->next;
        }
        n = c;
        while (n--)
        {
            temp1 = newnode(0);
            temp1->next = res.head;
            res.head = temp1;
        }
        pro.head = addition(res.head, pro.head);
        carry = 0;
        c += 1;
        b.head = b.head->next;
    }
    return pro;
}
struct node *subtraction(struct node *a, struct node *b)
{
    signchange(&(b));
    struct node *res = NULL, *itr;
    int borrow = 0, diff = 0;
    while (a && b)
    {
        diff = a->data + b->data - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        if (res == NULL)
        {
            res = newnode(diff);
            itr = res;
        }
        else
        {
            itr->next = newnode(diff);
            itr = itr->next;
        }
        a = a->next;
        b = b->next;
    }
    while (a) // if b becomes NULL
    {
        diff = a->data - borrow;
        borrow = 0;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        if (res == NULL)
        {
            res = newnode(diff);
            itr = res;
        }
        else
        {
            itr->next = newnode(diff);
            itr = itr->next;
        }
        a = a->next;
    }
    while (b) // if b becomes NULL
    {
        diff = b->data - borrow;
        borrow = 0;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        if (res == NULL)
        {
            res = newnode(diff);
            itr = res;
        }
        else
        {
            itr->next = newnode(diff);
            itr = itr->next;
        }
        b = b->next;
    }
    return res;
}
struct BigInteger add(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger res;
    if (a.sign == b.sign)
    {
        res.sign = a.sign;
        res.head = addition(a.head, b.head);
        return res;
    }
    if (check0(b.head) == 0)
    {
        return a;
    }
    if (check0(a.head) == 0)
    {
        res.sign = -1 * b.sign;
        res.head = b.head;
        return res;
    }
    if (compare(a, b) == 1)
    {
        res.sign = a.sign;
        res.head = subtraction(a.head, b.head);
        signchange(&b.head);
        return res;
    }
    res.sign = b.sign;
    res.head = subtraction(b.head, a.head);
    signchange(&a.head);
    return res;
}
struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger res;
    res.sign = a.sign;
    if (a.sign != b.sign)
    {
        res.head = addition(a.head, b.head); // for unequal signs like a-(-b)=a+b and -a-(b)=-(a+b)
        return res;
    }
    if (check0(a.head) == 0)
    {
        res.sign = -b.sign;
        res.head = b.head;
        return res;
    }
    if (check0(b.head) == 1)
    {
        if (compare(a, b) == 2)
        {
            res.sign = -a.sign;
            res.head = subtraction(b.head, a.head);
            signchange(&a.head);
            return res;
        }
        if (compare(a, b) == 1)
        {
            res.head = subtraction(a.head, b.head); // for equal signs like a-(b)=a-b and -a-(-b)=-a+b=b-a
            signchange(&b.head);
            return res;
        }
        else
        {
            res.head = newnode(0);
            return res;
        }
        return res;
    }
    else
        return a;
}

void delete(struct node **head)
{
    struct node *temp = *head;
    *head = (*head)->next;
    free(temp);
}
void truncate(struct BigInteger *a) // removes truncate zeroes eg 00123 = 123
{
    while (a->head != NULL && (a->head)->data == 0)
    {
        delete (&(a->head));
        --a->length;
    }
}
int compare(struct BigInteger a, struct BigInteger b)
{
    truncate(&a);
    truncate(&b);
    int l1 = a.length;
    int l2 = b.length;
    if (l1 > l2)
        return 1;
    else if (l2 > l1)
        return 2;
    int res=0;
    struct node*itr1=a.head,*itr2=b.head;
    while(itr1!=NULL){
        if(itr1->data>itr2->data)
        res=1;
        else if(itr1->data<itr2->data)
        res=2;
        itr1=itr1->next;
        itr2=itr2->next;
    }
    return res;
}

struct BigInteger div1(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger result;
    struct BigInteger rem, quo, one;
    result.sign = a.sign * b.sign;
    rem = a;
    rem.sign = 1;
    b.sign = 1;
    one.head = newnode(1);
    one.sign = 1;
    quo.head = newnode(0);
    quo.sign = 0;
    int f;
    f = compare(rem, b);
    while (f == 2)
    {
        rem = sub(rem, b);
        quo = add(quo, one);
        f = compare(rem, b);
    }
    result.head = quo.head;
    int count=0;
    return result;
}