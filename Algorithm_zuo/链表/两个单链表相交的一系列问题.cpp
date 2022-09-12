/*
问题：两个单链表相交的一系列问题，如果两个链表相交，返回相交的第一个节点
分解为三个问题：
问题一：如何判断一个链表是否有环，如果有，返回进入环的第一个节点
问题二：如何判断两个无环链表是否相交，相交则返回第一个相交节点
问题三：如何判断两个有环链表是否相交，相交则返回第一个相交节点
结论一：一个有环，一个无环，不可能相交！！
 */
#include <iostream>
#include <vector>

struct Node{
    int value;
    Node* next;

    Node(int data){
        value=data;
    }
};

//问题一：判断链表是否有环，使用快慢指针。
//  如果环的位置在开始，那么slow走一圈，fast走两圈。两个在开始位置相遇
//  如果环在中间位置，fast和slow在环中第一次相遇的位置。距离环入口位置就等于开始位置距离环入口的位置。

Node* getLoopNode(Node* head){
    if(head==NULL||head->next==NULL||head->next->next==NULL){
        return NULL;
    }
    Node* fast=head->next->next;
    Node* slow=head->next;
    Node* cur=head;
    while(fast!=slow){
        if(slow->next==NULL||fast->next->next==NULL){
            return NULL;
        }
        fast=fast->next->next;
        slow=slow->next;
    }
    fast=head;
    while(fast!=slow){
        fast=fast->next;
        slow=slow->next;
    }
    return fast;
}

//问题二：判断两个无环链表是否相交,相交就返回相交节点，否则返回null
//  解法：先遍历两个链表，如果最后节点一样，则相交，否则不相交。
//       相交情况下找到相交节点：记录两个链表长度len1和len2,x = |len1 - len2| 谁长谁先走x步，然后一起走，走到相等就是相交节点
Node* noLoop(Node* head1,Node* head2){
    if(head1==NULL||head2==NULL){
        return NULL;
    }
    int n=0;
    Node* cur1=head1;
    Node* cur2=head2;
    while(cur1->next!=NULL){
        n++;
        cur1=cur1->next;
    }
    while(cur2->next!=NULL){
        n--;
        cur2=cur2->next;
    }
    if(cur1!=cur2){
        return NULL;
    }
    cur1=n>0?head1:head2;
    cur2=cur1==head1?head2:head1;
    n=abs(n);
    while(n!=0){
        n--;
        cur1=cur1->next;
    }
    while(cur1!=cur2){
        cur1=cur1->next;
        cur2=cur2->next;
    }
    return cur1;
}

//问题三：判断两个有环链表是否相交，相交则返回第一个节点，否则返回null.
//如果两个链表入环节点为同一个节点，则判断方法同方法二，
//如果两个链表入环节点不一样，其一：两个链表不相交，直接返回null; 其二：两个链表在环里相交，返回任一入环节点即可。
Node * bothLoop(Node* head1,Node* loop1,Node* head2,Node* loop2){
    Node* cur1=NULL;
    Node* cur2=NULL;
    if(loop1==loop2){
        int n=0;
        cur1=head1;
        cur2=head2;
        while(cur1->next!=loop1){
            n++;
            cur1=cur1->next;
        }
        while(cur2->next!=loop2){
            n--;
            cur2=cur2->next;
        }
        cur1=n>0?head1:head2;
        cur2=cur1==head1?head2:head1;
        n=abs(n);
        while(n!=0){
            n--;
            cur1=cur1->next;
        }
        while(cur1!=cur2){
            cur1=cur1->next;
            cur2=cur2->next;
        }
        return cur1;
    }else{
        cur1=loop1->next;
        while(cur1!=loop1){
            if(cur1==loop2){
                return loop1;
            }
            cur1=cur1->next;
        }
        return NULL;
    }
}

Node* getIntersectNode(Node* head1,Node* head2){
    if(head1==NULL||head2==NULL){
        return NULL;
    }
    Node* loop1=getLoopNode(head1);
    Node* loop2=getLoopNode(head2);
    if(loop1==NULL&&loop2==NULL){
        return noLoop(head1,head2);
    }
    if(loop1!=NULL&&loop2!=NULL){
        return bothLoop(head1,loop1,head2,loop2);
    }
    return NULL;
}