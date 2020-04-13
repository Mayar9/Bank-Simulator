#include <stdio.h>
#include <stdlib.h>

typedef struct Client Client;
typedef struct Teller Teller;
typedef struct List List;

struct Client
{
    Client *c_next;
    Client *c_prev;
    int ArrivalTime;
    int TransactionTime;
};

Client* CreateClient();
void AddClient(Client **pfirst,Client **plast,Client *newnode);
void Display(Client *pfirst);
void Swap(Client **head,Client **tail,Client **firstnode);
void BubbleSort(Client **head,Client **tail);
Client* RemoveNode(Client **phead,Client **ptail);


struct List
{
    Client *head;
    Client *tail;
};

struct Teller
{
    List teller_node;
    int TotalWaitingTime;
    float Av_WaitingTime;
    int TotalTransactionTime;
    float Av_TransactionTime;
    int TDepartureTime;
    int TUserNo;
};

void InitTeller(Teller* teller);
Teller* MinWaitingList(Teller t[],int size);
void TellerStatistics(Teller *tel,Client *node);
void Link_C_In_T(Teller* tel,Client *node);
void Display_BankInfo(Teller t[],int size);

int main()
{
    Client *c_head=NULL,*c_tail=NULL;
    Client* C1=NULL;
    int UserNo=0;
    char ch;
    //This is the main list of clients
    do
    {
        C1=CreateClient();
        AddClient(&c_head,&c_tail,C1);
        UserNo++;
        printf("\nto continue press c\n");
        ch=getch();
    }while(ch=='c');
    system("cls");
    Display(c_head);
    BubbleSort(&c_head,&c_tail);
    printf("\n Sorted Data \n");
    Display(c_head);
    printf("Number of users are:");
    printf("%d \n",UserNo);
    printf("===================== \n");
    /////////////////////////////////////////////
    //Create Bank's Windows
    Teller teller[3];
    for(int i=0;i<3;i++)
    {
        InitTeller(&teller[i]);
    }
////////////////////////////////////////////////////
     int flag=1;
     Client *node1;
     Teller* tel;
     while(flag==1)
     {
        node1=RemoveNode(&c_head,&c_tail);
        tel= MinWaitingList(teller,3);
        TellerStatistics(tel,node1);
        Link_C_In_T(tel,node1);
        if(c_head == c_tail)
        {
          node1=RemoveNode(&c_head,&c_tail);
          tel= MinWaitingList(teller,3);
          TellerStatistics(tel,node1);
          Link_C_In_T(tel,node1);
          flag=0;
        }
     }
     Display_BankInfo(teller,3);
    return 0;
}

Client* CreateClient()
{
     Client *pnode=(Client*) malloc(sizeof(Client));
     printf("Enter Client Data:\n");
     printf("ArrivalTime & TransactionTime:\n");
     scanf("%d ",&pnode->ArrivalTime);
     scanf("%d",&pnode->TransactionTime);
     pnode->c_next=pnode->c_prev=NULL;
     return pnode;
}

void AddClient(Client **pfirst,Client **plast,Client *newnode)
{
    if(*pfirst==NULL) //empty list
    {
       *pfirst=*plast=newnode;
    }
    else
    {
       newnode->c_prev=*plast;
       (*plast)->c_next=newnode;
       *plast=newnode;
    }
}

void Display(Client *pfirst)
{
    Client *PDisplay=pfirst;
    while(PDisplay!=NULL)
    {
        printf("ArrivalTime\t TransactionTime \n");
        printf("%d\t\t %d \n",PDisplay->ArrivalTime,PDisplay->TransactionTime);
        PDisplay=PDisplay->c_next;
    }
}

void Swap(Client **head,Client **tail,Client **firstnode)
{
    Client *temp, *temp2;
    Client* secondnode = (*firstnode)->c_next;
    if((*firstnode) == (*head))
    {
      temp = secondnode->c_next;
      temp->c_prev=(*firstnode);
      secondnode->c_next=(*firstnode);
      secondnode->c_prev=NULL;
      (*firstnode)->c_next=temp;
      (*firstnode)->c_prev=secondnode;
      (*head)=secondnode;

    }
    else if((*firstnode)->c_next == (*tail))
    {
        temp=(*firstnode)->c_prev;            temp->c_next=secondnode;
        secondnode->c_prev=temp;              secondnode->c_next=(*firstnode);
        (*firstnode)->c_next=NULL;            (*firstnode)->c_prev=secondnode;
        (*tail)=(*firstnode);

    }
    else
    {
         temp=secondnode->c_next;               secondnode->c_next->c_prev=(*firstnode);
         temp2=(*firstnode)->c_prev;            temp2->c_next=secondnode;
         secondnode->c_next=(*firstnode);       secondnode->c_prev=(*firstnode)->c_prev;
         (*firstnode)->c_prev=secondnode;       (*firstnode)->c_next=temp;

    }
}

void BubbleSort(Client **phead,Client **ptail)
{
    int swapped;
    Client* pointer=NULL;
    Client **ptr1=phead,**ptr2=ptail;
    Client* node1= *phead;
    Client **h= &node1;
    //check if list empty
    if((*h) == NULL)
        return;
   do
   {
         ptr1=phead;
         ptr2=ptail;
         node1=*phead;
         swapped=0;
        while(node1->c_next != pointer)
        {
             if(node1->ArrivalTime > node1->c_next->ArrivalTime)
             {
              Swap(ptr1,ptr2,&node1);
              swapped=1;
             }
             else
             {
                node1=node1->c_next;
             }
        }
        pointer=node1;
   }while(swapped);
}

Client* RemoveNode(Client **phead,Client **ptail)
{
     Client* rem_node= *phead;
     if(*phead == *ptail)
     {
        (*phead)=NULL;
     }
     else
     {
        (*phead)=rem_node->c_next;
        (*phead)->c_prev=NULL;
     }
    rem_node->c_next=NULL;
    rem_node->c_prev=NULL;
    return rem_node;
}

void InitTeller(Teller* teller)
{
     teller->teller_node.head = teller->teller_node.tail = NULL;
     teller->TotalTransactionTime=0;
     teller->TotalWaitingTime=0;
     teller->TDepartureTime=0;
     teller->Av_TransactionTime=0;
     teller->Av_WaitingTime=0;
     teller->TUserNo=0;
}

Teller* MinWaitingList(Teller t[],int size)
{
    int i,j,MinWT;
    MinWT=t[0].TotalWaitingTime;
    j=0;
    for(i=1;i<3;i++)
    {
        if(MinWT > t[i].TotalWaitingTime || t[j].TUserNo > t[i].TUserNo)
        {
            MinWT=t[i].TotalWaitingTime;
            j=i;
        }
    }
    return (t+j);
}

void TellerStatistics(Teller *tel,Client *node)
{
    if(tel->TUserNo == 0)
    {
        tel->TotalWaitingTime=0;
        tel->TDepartureTime=node->ArrivalTime + node->TransactionTime;
    }
    else if(tel->TDepartureTime <= node->ArrivalTime)
    {
        tel->TotalWaitingTime += 0;
        tel->TDepartureTime += node->TransactionTime;

    }
    else if(tel->TDepartureTime > node->ArrivalTime)
    {
        tel->TotalWaitingTime += tel->TDepartureTime - node->ArrivalTime;
        tel->TDepartureTime += node->TransactionTime;
    }
    tel->TotalTransactionTime += node->TransactionTime;
    tel->TUserNo++;
}

 void Link_C_In_T(Teller* tel,Client *node)
 {
     if(tel->teller_node.head ==NULL)
     {
        tel->teller_node.head=tel->teller_node.tail=node;
     }
     else
     {
        node->c_prev=tel->teller_node.tail;
        tel->teller_node.tail->c_next=node;
        tel->teller_node.tail=node;
     }
 }

  void Display_BankInfo(Teller t[],int size)
  {
     int BankTUserNo=0;
     float BankAv_TransactionTime;
     float BankAv_WaitingTime;
     for(int i=0;i<3;i++)
     {
        t[i].Av_WaitingTime = ((float)t[i].TotalWaitingTime) / (t[i].TUserNo);
        t[i].Av_TransactionTime = ((float)t[i].TotalTransactionTime) / (t[i].TUserNo);
        BankTUserNo += t[i].TUserNo;
        BankAv_TransactionTime += t[i].Av_TransactionTime;
        BankAv_WaitingTime += t[i].Av_WaitingTime;
     }

     for(int i=0;i<3;i++)
     {
        printf("\n");
        printf("teller %d: \n", i+1);
        printf("TotalNumberUser/teller: %d \n",t[i].TUserNo);
        printf("Av_TransactionTime/teller: %f\n",t[i].Av_TransactionTime);
        printf("Av_WaitingTime/teller: %f \n",t[i].Av_WaitingTime);
     }
     printf("=================================== \n");
     printf("TotalNumberUser/Bank: %d \n",BankTUserNo);
     printf("Av_TransactionTime/Bank: %f\n",BankAv_TransactionTime);
     printf("Av_WaitingTime/Bank: %f \n",BankAv_WaitingTime);
  }
