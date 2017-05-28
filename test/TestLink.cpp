#include <iostream>
#include <stdlib.h>

using namespace std;

// 链表结点结构体
typedef struct node
{
    int number;
    struct node *next;
} Node;

Node *Delete(Node *head, int key)
{
    Node *node1 = head;
    Node *node2 = NULL;
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        if (node1->number == key)
        {
            head = head->next;
            // node1->next = NULL;
            free(node1);
            return head;
        }
        else
        {
            while (node1 != NULL)
            {
                node2 = node1;
                node2 = node2->next;
                if (node2->number == key)
                {
                    node1->next = node2->next;
                    free(node2);
                    break;
                }
                node1 = node1->next;
            }
            return head;
        }
    }
}
//int main()
//{
//    Node *head=(Node*)malloc(sizeof(Node));
//    Node *p,*q,*q1;
//    int key;
//    p=(Node*)malloc(sizeof(Node));
//    q1=q=head;
//    int i;
//    for (i=1;i<10;i++)
//    {
//        p->number=i;
//        head->next=p;
//        head=p;
//        p=(Node*)malloc(sizeof(Node));
//    }
//    head->next=NULL;
//    cout<<"原链表数据： "<<endl;
//    q1=q1->next;
//    while (q1!=NULL)
//    {
//        cout<<q1->number<<" ";
//        q1=q1->next;
//    }
//    cout<<endl;
//    cout<<"输入要删除的数据：";
//    cin>>key;
//    p=Delete(q->next,key);
//    cout<<"删除一个"<<key<<"之后的链表数据： "<<endl;
//    while (p!=NULL)
//    {
//        cout<<p->number<<" ";
//        p=p->next;
//    }
//    cout<<endl;
//    free(p);
//    free(head);
//    return 0;
//}
