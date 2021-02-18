/*표기법 변환기
by yoonjin2
*/
#include <stdio.h>
#include <stdlib.h>
typedef enum bool {false, true} bool;
typedef struct node 
{
    int key;
    struct node *left;
    struct node *right;
}
node_binary;
typedef struct node_
{
    node_binary *key;
    struct node_ *next;
    struct node_ *prev;
}
node;
typedef struct node__
{
    struct node__ *next;
    node_binary *key;
} node_stack;
typedef struct stack
{
    node_stack *head;
    node_stack *tail;
    int size;
}
stack;
typedef struct queue
{
    node *front;
    node *rear;
    int size;
}
queue;
//큐 시작
void init_queue(queue *que)
{
    que->front=(node *)malloc(sizeof(node));
    que->rear=(node *)malloc(sizeof(node));
    que->front->next=que->rear;
    que->front->prev=que->front;
    que->rear->next=que->rear;
    que->rear->prev=que->front;
    que->size=0;
}
//큐 비우기
void empty_queue(queue *que)
{
    node *q=que->front->next;
    while(q->next!=que->rear)
    {
        free(q);
        q=q->next;
    }
    que->size=0;
}
//큐가 비었는지 확인
bool Isempty_queue(queue *que)
{
    if(que->size==0)
        return true;
    else
        return false;
}
//큐 해제
void free_queue(queue *que)
{
    empty_queue(que);
    free(que->front);
    free(que->rear);
}
//큐-푸시
void push_queue(queue *que, node_binary * item)
{
    node *q;
    if((q=(node *)malloc(sizeof(node)))==NULL)
        return ;
    else
    {
        q->key=item;
        que->rear->prev->next=q;
        q->prev=que->rear->prev;
        que->rear->prev=q;
        q->next=que->rear;
    }
    que->size++;
}
//큐-팝
node_binary *pop_queue(queue *que)
{
    node_binary *w;
    if(que->size==0)
    {
        puts("-1");
        return NULL;
    }
    else
    {
        node *q=que->front->next;
        que->front->next=que->front->next->next;
        que->front->next->prev=que->front;
        w=q->key;
        free(q);
        que->size--;
    }
    return w;
}
//큐 크기
int size_queue(queue *que)
{
    return que->size;
}
//큐의 front쪽 노드 반환
node_binary * front(queue *que)
{
    if(que->size==0)
        return NULL;
    else
        return que->front->next->key;
}
//큐의 back쪽 노드 반환
node_binary * back(queue *que)
{
    if(que->size==0)
        return NULL;
    else
        return que->rear->prev->key;
}

typedef struct binary_tree
{
    node_binary *head;
    node_binary *tail;
}
binary_tree;
//노드 방문
void visit(node_binary *t)
{
    printf("%c", t->key);
}
//트리 시작
void init_tree(binary_tree *tree)
{
    tree->head=malloc(sizeof(node_binary));
    tree->tail=malloc(sizeof(node_binary));
    tree->head->left=tree->tail;
    tree->head->right=tree->tail;
    tree->tail->left=tree->tail;
    tree->head->right=tree->tail;
}
//전위 순회
void preorder_traverse(node_binary *t, binary_tree *tree)
{
    if(t!=tree->tail)
    {
        visit(t);        
        preorder_traverse(t->left, tree);
        preorder_traverse(t->right,tree);
    }
}
//인오더 순회
void inorder_traverse(node_binary *t, binary_tree *tree)
{
    if(t!=tree->tail)
    {
        inorder_traverse(t->left, tree);
        visit(t);
        inorder_traverse(t->right,tree);        
    }
}
//후위 순회
void postorder_traverse(node_binary *t, binary_tree *tree)
{
    if(t!=tree->tail)
    {
        postorder_traverse(t->left, tree);
        postorder_traverse(t->right, tree);
        visit(t);        
    }
}
//레벨 순서 순회
void levelorder_traverse(node_binary *t, binary_tree *tree, queue *q)
{
    push_queue(q, t);
    while(!Isempty_queue(q))
    {
    t=pop_queue(q);
    visit(t);
    if(t->left!=tree->tail)
        push_queue(q,t->left);
    if(t->right!=tree->tail)
        push_queue(q,t->right);
    }    
}
//스택 시작
void init_stack(stack *st)
{
    st->head=(node_stack *)malloc(sizeof(node_stack));
    st->tail=(node_stack *)malloc(sizeof(node_stack));
    st->head->next=st->tail;
    st->tail->next=st->tail;
}
//스택-푸시
void push_stack(stack *sta, node_binary *st)
{
    node_stack *t;
    if((t=(node_stack *)malloc(sizeof(node_stack)))==NULL)
        return;
    t->key=st;
    t->next=sta->head->next;
    sta->head->next=t;
}
//스택-팝
node_binary * pop_stack(stack *sta)
{
    node_stack *t;
    node_binary *i;
    if(sta->head->next==sta->tail)
        return NULL;
    t=sta->head->next;
    i=t->key;
    sta->head->next=t->next;
    free(t);
    return i;
}
//스택 비우기
void clear_stack(stack *sta)
{
    node_stack *t, *s;
    t=sta->head->next;
    while(t!=sta->tail)
    {
        s=t;
        t=t->next;
        free(s);
    }
    sta->head->next=sta->tail;    
}
//스택 해제
void free_stack(stack *sta)
{
    clear_stack(sta);
    free(sta->head);
    free(sta->tail);
};
//연산자인지 확인
bool is_operator(int k)
{
    return (bool)((k=='+') | (k=='-') | (k=='*') | (k=='/'));
}
//파스 트리 만들기
node_binary *make_parse_tree(stack *sta, char *p, binary_tree *tree)
{
    node_binary *t;
    while(*p)
    {
        while(*p==' ')
            p++;
        t=(node_binary *)malloc(sizeof(node_binary));
        t->key=*p;
        t->left=tree->tail;
        t->right=tree->tail;
        if(is_operator(*p))
        {
            t->right=pop_stack(sta);
            t->left=pop_stack(sta);
        }
        push_stack(sta, t);
        p++;
    }
    return pop_stack(sta);
}
//옳은 수식인지 검증
bool is_legal(char *s)
{
    int f=0;
    while(*s)
    {
        while(*s==' ')
            s++;
        if(is_operator(*s))
            f--;
        else
            f++;
        if(f<1)
            break;
        s++;
    }
    return (bool)(f==1);
}
int main()
{
    //수식을 저장할 배열
    char post[256]={'\0'};
    //스택, 이진트리, 큐 생성
    binary_tree tree; 
    stack sta;
    queue q;
    //스택. 이진트리 동적 할당
    init_tree(&tree);
    init_stack(&sta);
    init_queue(&q);
    while(1)
    {
        //수식 스캔
        scanf("%255s%*s", post);
        //수식이 비었으면 리턴값 1을 반환 후 프로그램을 종료
        if(*post=='\0')
            return 1;
        //수식이 부정확하다면 계산하지 않는다
        if(!is_legal(post))
            continue;
        //파스 트리 생성
        tree.head->right=make_parse_tree(&sta, post, &tree);
        //전위 표기법
        printf("\nPreorder traverse : ");
        preorder_traverse(tree.head->right,&tree);
        // 중위 표기법
        printf("\nInorder traverse : ");
        inorder_traverse(tree.head->right,&tree);
        //후위 표기법
        printf("\nPostorder_traverse : ");
        postorder_traverse(tree.head->right,&tree);
        //레벨 순서 순회를 이용한 표기법
        printf("\nLevelorder traverse : ");
        levelorder_traverse(tree.head->right,&tree,&q);
    }
    //큐, 스택의 동적 할당을 해제
    free_queue(&q);
    free_stack(&sta);
    //0을 반환하며 프로그램을 정상적으로 종료
    return 0;
}
