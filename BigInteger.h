#ifndef BigInteger_h
#define BigInteger_h

struct node
{
    int data;
    struct node *next;
};
struct BigInteger
{
    struct node *head;
    int length, sign;
};
struct node *newnode(int);
void display(struct BigInteger);
int compare(struct BigInteger, struct BigInteger);
void delete(struct node **);
void truncate(struct BigInteger *);
void reverse(struct node **);
struct node *addition(struct node*, struct node*);
struct node *subtraction(struct node*, struct node*);
void signchange(struct node **);
int check0(struct node*);

struct BigInteger initialize(char *s);
void insertAtHead(struct node **, int);
struct BigInteger add(struct BigInteger, struct BigInteger);
struct BigInteger sub(struct BigInteger, struct BigInteger);
struct BigInteger mul(struct BigInteger, struct BigInteger);
struct BigInteger div1(struct BigInteger, struct BigInteger);
#endif
