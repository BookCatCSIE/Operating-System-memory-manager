#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
typedef struct node
{
    int data;
    struct node *next;
} Node;

//串列建立函數
Node *createList(int *arr,int len)
{
    int i;
    Node *first,*current,*previous;
    for(i=0; i<len; i++)
    {
        current=(Node *) malloc(sizeof(Node));//建立新節點
        current->data=arr[i];  //設定節點的資料成員
        if(i==0)
        {
            first=current;  //如果是第一個成員把指標frist指向目前的節點
        }
        else
        {
            previous->next=current;//把前一個的next指向目前的節點
        }
        current->next=NULL; //把目前的節點的next指向NULL
        previous=current; //把前一個節點設成目前的節點
    }
    return first;
}

//串列列印函數
Node printList(Node *first)
{
    Node *node=first; //將node指向第一個節點
    if(first==NULL)
    {
        printf("List is empty!\n");
    }
    else
    {
        while(node!=NULL)
        {
            printf("%3d",node->data);
            node=node->next;
        }
        printf("\n");
    }
}

//釋放串列記憶空間函數
void freeList(Node *first)
{
    Node *current,*tmp;
    current=first;
    while(current!=NULL)
    {
        tmp=current;
        current=current->next;
        free(tmp);
    }
}

//搜尋節點函數
Node *searchNode(Node *first,int item)
{
    Node *node=first;
    while(node!=NULL)
    {
        if(node->data ==item)  //如果node的data等於item
        {
            return node;  //傳回node為該節點的位址
        }
        else
        {
            node=node->next; //否則將指標指向下一個節點
        }
    }
    return NULL; //如果找不到符合的節點，則傳回NULL
}

//插入節點函數
void *insertNode(Node *node,int item)
{
    Node *newnode;
    newnode=(Node *) malloc(sizeof(Node));
    newnode->data=item;
    newnode->next=node->next;
    node->next=newnode;
}

//刪除節點函數
Node *deleteNode(Node *first,Node *node)
{
    Node* ptr=first;
    if(first==NULL)  //如果串列是空的，則印出Nothing to delete!
    {
        printf("Nothing to delete!\n");
        return NULL;
    }
    if(node==first)   //如果刪除的是第一個節點
    {
        first=first->next;//把first指向下一個節點(NULL)
    }
    else
    {
        while(ptr->next!=node)  //找到要刪除之節點的前一個節點
        {
            ptr=ptr->next;
        }
        ptr->next=node->next; //重新設定ptr的next成員
    }
    free(node);
    return first;
}
*/
//-----------------------------------------------------------------------------

int total_count =0;
int miss_count =0;
int i,j =0;
int used_frame_count = 0; // <=N

typedef struct
{
    //type type_name;
    int page_num;
    int in_physical_index;
    int in_disk_index;
    int in_queue_index;
    int in_use_bit; //ever been used or not
    int present_bit; // in physical memory or not

    //---for ESCA---
    int reference_bit;
    int dirty_bit;
    //int start_check_pointer;

    //---for SLRU---
    int page_active;
    int page_reference;
    int inactive_list_index;
    int active_list_index;

} my_page;

typedef struct
{
    int disk_page_num;
} my_disk;

typedef struct
{
    int frame_page_num;
    //int start_check_pointer;
} my_frame;  // for ESCA

int start_check_pointer = 0;  // for ESCA


//int used_inactive_count = 0; // for SLRU
//int used_active_count = 0; // for SLRU



int main(int argc,char* argv[])
{

    /*
        FILE *fptr;
        fptr = fopen("input.txt","r");

        if(fptr == NULL)
        {
            printf("opening input failed \n");
            return 0;
        }

        int c;
    */

    //while((c=fgetc(fptr))!=EOF){
    //    printf("%c",c);
    //}
    //c=fgetc(fptr);
    //printf("%c",c);
    //printf("\n");

    /*
        char str[1000][100];
        int index=0;
        while((c=fscanf(fptr,"%s",str[index]))!=EOF)
        {
            printf("%s\n",str[index]);
            index++;
        }

        fclose(fptr);
    */

    /*
    Node *first,*node;
    int arr[]={12,38,57};
    first=createList(arr,3);
    printList(first);


    node=searchNode(first,38); //找出節點值為38的位址
    first=deleteNode(first,node); //刪除節點38
    printList(first);

    first=deleteNode(first,first); //刪除第一個節點
    printList(first);

    first=deleteNode(first,first); //刪除第一個節點
    printList(first);
    freeList(first);
    */


    char str[20][100];
    int M = 0; // virtual page
    int N = 0; // physical frame
    /*
    int index =0;
    while(scanf("%s",&str[index])!=EOF){
        //printf("%s\n",str[index]);
    index++;
    }
    */
    for(i=0; i<6; i++)
    {
        scanf("%s",&str[i]);
    }

    scanf("%d",&M);

    for(i=6; i<10; i++)
    {
        scanf("%s",&str[i]);
    }

    scanf("%d",&N);

    scanf("%s",&str[10]);

    //printf("%d\n",M);
    //printf("%d\n",N);

    char str2[1000][20]; // Read/Write
    int index =0;
    while(scanf("%s",&str2[index])!=EOF)
    {
        //printf("%s\n",str2[index]);
        index++;
        //even index --> Write/Read
        //odd index --> page number
    }


    if((strcmp(str[1],"FIFO")==0) || ((strcmp(str[1],"SLRU")==0) && N == 1))
    {
        //printf("FIFO\n");

        my_page PP[M];
        for(i=0; i<M; i++)
        {
            PP[i].page_num = i;
            PP[i].in_physical_index = -1;
            PP[i].in_disk_index = -1;
            PP[i].in_queue_index = -1;
            PP[i].in_use_bit = 0;
            PP[i].present_bit = 0;
        }

        my_disk DD[1000];
        for(i=0; i<1000; i++)
        {
            DD[i].disk_page_num = -1;
        }

        for(i=0; i<index/2; i++) // deal with page read/write   // total_count  miss_count
        {
            //printf("%d\n",((int)str2[2*i+1][0]-48)); // (int)str2[2*i+1][0] --> ASCII code
            total_count+=1;
            int num = ((int)str2[2*i+1][0]-48);
            PP[num].in_use_bit = 1;
            int miss_or_not = 1;
            for(j=0; j<M; j++)
            {
                if(PP[j].page_num==num && PP[j].present_bit==1)
                {
                    miss_or_not = 0;
                }
            }

            if(miss_or_not == 1)
            {
                miss_count+=1;
                printf("Miss, ");
                if(used_frame_count<N)  // physical memory not full
                {
                    PP[num].in_physical_index = used_frame_count;
                    printf("%d, -1>>-1, %d<<-1\n",used_frame_count,num);
                    used_frame_count+=1;

                    PP[num].present_bit = 1;
                    PP[num].in_queue_index+=1;
                    for(j=0; j<M; j++)
                    {
                        if(PP[j].in_queue_index != -1 && PP[j].page_num != num)
                        {
                            PP[j].in_queue_index+=1;
                        }
                    }
                }
                else  // physical memory full
                {
                    int max_queue_index = -1;
                    int page_out_num = -1;
                    for(j=0; j<M; j++)
                    {
                        if(PP[j].in_queue_index > max_queue_index && PP[j].page_num != num)
                        {
                            max_queue_index = PP[j].in_queue_index;
                            page_out_num = PP[j].page_num;
                        }
                    }

                    PP[num].present_bit = 1;
                    PP[num].in_physical_index = PP[page_out_num].in_physical_index;
                    //printf("%d, %d>>%d, %d<<%d\n",PP[num].in_physical_index,page_out_num,PP[page_out_num].in_physical_index,num,PP[num].in_disk_index);
                    PP[num].in_queue_index+=1;
                    for(j=0; j<M; j++)
                    {
                        if(PP[j].in_queue_index != -1 && PP[j].page_num != num)
                        {
                            PP[j].in_queue_index+=1;
                        }
                    }

                    PP[page_out_num].in_physical_index = -1;
                    PP[page_out_num].present_bit = 0;
                    PP[page_out_num].in_queue_index = -1;

                    for(j=0; j<1000; j++)
                    {
                        if(DD[j].disk_page_num == -1)
                        {
                            DD[j].disk_page_num = page_out_num;
                            PP[page_out_num].in_disk_index = j;
                            break;
                        }
                    }

                    printf("%d, %d>>%d, %d<<%d\n",PP[num].in_physical_index,page_out_num,PP[page_out_num].in_disk_index,num,PP[num].in_disk_index);

                    PP[num].in_disk_index = -1;
                    for(j=0; j<1000; j++)
                    {
                        if(DD[j].disk_page_num == num)
                        {
                            DD[j].disk_page_num = -1;
                            break;
                        }
                    }

                }

            }
            else
            {
                printf("Hit, %d=>%d\n",num,PP[num].in_physical_index);
            }


        }
    }
    else if(strcmp(str[1],"ESCA")==0)
    {
        //printf("ESCA\n");

        my_page PP[M];
        for(i=0; i<M; i++)
        {
            PP[i].page_num = i;
            PP[i].in_physical_index = -1;
            PP[i].in_disk_index = -1;

            PP[i].in_use_bit = 0;
            PP[i].present_bit = 0;

            PP[i].reference_bit = 0;
            PP[i].dirty_bit = -1;
            //PP[i].start_check_pointer = 0;
        }

        my_disk DD[1000];
        for(i=0; i<1000; i++)
        {
            DD[i].disk_page_num = -1;
        }

        my_frame FF[N];
        for(i=0; i<N; i++)
        {
            FF[i].frame_page_num = -1;
            //FF[i].start_check_pointer = 0;
        }

        for(i=0; i<index/2; i++) // deal with page read/write   // total_count  miss_count
        {
            //printf("%d\n",((int)str2[2*i+1][0]-48)); // (int)str2[2*i+1][0] --> ASCII code
            total_count+=1;
            int num = ((int)str2[2*i+1][0]-48);
            PP[num].in_use_bit = 1;

            if(strcmp(str2[2*i],"Write")==0)
            {
                PP[num].dirty_bit = 1;
            }
            else
            {
                PP[num].dirty_bit = 0;
            }

            PP[num].reference_bit = 1;

            int miss_or_not = 1;
            for(j=0; j<M; j++)
            {
                if(PP[j].page_num==num && PP[j].present_bit==1)
                {
                    miss_or_not = 0;
                }
            }

            if(miss_or_not == 1)
            {
                miss_count+=1;
                printf("Miss, ");
                if(used_frame_count<N)  // physical memory not full
                {
                    PP[num].in_physical_index = used_frame_count;
                    FF[used_frame_count].frame_page_num = PP[num].page_num;
                    printf("%d, -1>>-1, %d<<-1\n",used_frame_count,num);
                    used_frame_count+=1;

                    PP[num].present_bit = 1;

                }
                else  // physical memory full
                {
                    int page_out_num = -1;
                    int next_start_check_pointer = -1;
                    //int frame_out_num = -1;

                    //--find (0,0)

                    if(page_out_num == -1)
                    {
                        for(j=start_check_pointer; j<N; j++)
                        {
                            if(PP[FF[j].frame_page_num].reference_bit == 0  && PP[FF[j].frame_page_num].dirty_bit == 0)
                            {
                                page_out_num = FF[j].frame_page_num;
                                FF[j].frame_page_num = num;

                                if(j==N-1)
                                {
                                    next_start_check_pointer = 0;
                                }
                                else
                                {
                                    next_start_check_pointer = j+1;
                                }

                                break;
                            }
                        }
                    }

                    if(page_out_num == -1)
                    {
                        for(j=0; j<start_check_pointer; j++)
                        {
                            if(PP[FF[j].frame_page_num].reference_bit == 0  && PP[FF[j].frame_page_num].dirty_bit == 0)
                            {
                                page_out_num = FF[j].frame_page_num;
                                FF[j].frame_page_num = num;

                                if(j==N-1)
                                {
                                    next_start_check_pointer = 0;
                                }
                                else
                                {
                                    next_start_check_pointer = j+1;
                                }

                                break;
                            }
                        }
                    }

                    //--find (0,1)

                    if(page_out_num == -1)
                    {
                        for(j=start_check_pointer; j<N; j++)
                        {
                            if(PP[FF[j].frame_page_num].reference_bit == 0  && PP[FF[j].frame_page_num].dirty_bit == 1)
                            {
                                page_out_num = FF[j].frame_page_num;
                                FF[j].frame_page_num = num;

                                if(j==N-1)
                                {
                                    next_start_check_pointer = 0;
                                }
                                else
                                {
                                    next_start_check_pointer = j+1;
                                }

                                break;
                            }
                            else
                            {
                                PP[FF[j].frame_page_num].reference_bit = 0;
                            }
                        }
                    }

                    if(page_out_num == -1)
                    {
                        for(j=0; j<start_check_pointer; j++)
                        {
                            if(PP[FF[j].frame_page_num].reference_bit == 0  && PP[FF[j].frame_page_num].dirty_bit == 1)
                            {
                                page_out_num = FF[j].frame_page_num;
                                FF[j].frame_page_num = num;

                                if(j==N-1)
                                {
                                    next_start_check_pointer = 0;
                                }
                                else
                                {
                                    next_start_check_pointer = j+1;
                                }

                                break;
                            }
                            else
                            {
                                PP[FF[j].frame_page_num].reference_bit = 0;
                            }
                        }
                    }


                    //--find (0,0) again

                    if(page_out_num == -1)
                    {
                        for(j=start_check_pointer; j<N; j++)
                        {
                            if(PP[FF[j].frame_page_num].reference_bit == 0  && PP[FF[j].frame_page_num].dirty_bit == 0)
                            {
                                page_out_num = FF[j].frame_page_num;
                                FF[j].frame_page_num = num;

                                if(j==N-1)
                                {
                                    next_start_check_pointer = 0;
                                }
                                else
                                {
                                    next_start_check_pointer = j+1;
                                }

                                break;
                            }
                        }
                    }

                    if(page_out_num == -1)
                    {
                        for(j=0; j<start_check_pointer; j++)
                        {
                            if(PP[FF[j].frame_page_num].reference_bit == 0  && PP[FF[j].frame_page_num].dirty_bit == 0)
                            {
                                page_out_num = FF[j].frame_page_num;
                                FF[j].frame_page_num = num;

                                if(j==N-1)
                                {
                                    next_start_check_pointer = 0;
                                }
                                else
                                {
                                    next_start_check_pointer = j+1;
                                }

                                break;
                            }
                        }
                    }

                    //--find (0,1) again

                    if(page_out_num == -1)
                    {
                        for(j=start_check_pointer; j<N; j++)
                        {
                            if(PP[FF[j].frame_page_num].reference_bit == 0  && PP[FF[j].frame_page_num].dirty_bit == 1)
                            {
                                page_out_num = FF[j].frame_page_num;
                                FF[j].frame_page_num = num;

                                if(j==N-1)
                                {
                                    next_start_check_pointer = 0;
                                }
                                else
                                {
                                    next_start_check_pointer = j+1;
                                }

                                break;
                            }
                            else
                            {
                                PP[FF[j].frame_page_num].reference_bit = 0;
                            }
                        }
                    }

                    if(page_out_num == -1)
                    {
                        for(j=0; j<start_check_pointer; j++)
                        {
                            if(PP[FF[j].frame_page_num].reference_bit == 0  && PP[FF[j].frame_page_num].dirty_bit == 1)
                            {
                                page_out_num = FF[j].frame_page_num;
                                FF[j].frame_page_num = num;

                                if(j==N-1)
                                {
                                    next_start_check_pointer = 0;
                                }
                                else
                                {
                                    next_start_check_pointer = j+1;
                                }

                                break;
                            }
                            else
                            {
                                PP[FF[j].frame_page_num].reference_bit = 0;
                            }
                        }
                    }




                    start_check_pointer = next_start_check_pointer;

                    PP[num].present_bit = 1;
                    PP[num].in_physical_index = PP[page_out_num].in_physical_index;
                    //printf("%d, %d>>%d, %d<<%d\n",PP[num].in_physical_index,page_out_num,PP[page_out_num].in_physical_index,num,PP[num].in_disk_index);

                    PP[page_out_num].in_physical_index = -1;
                    PP[page_out_num].present_bit = 0;

                    for(j=0; j<1000; j++)
                    {
                        if(DD[j].disk_page_num == -1)
                        {
                            DD[j].disk_page_num = page_out_num;
                            PP[page_out_num].in_disk_index = j;
                            break;
                        }
                    }

                    printf("%d, %d>>%d, %d<<%d\n",PP[num].in_physical_index,page_out_num,PP[page_out_num].in_disk_index,num,PP[num].in_disk_index);

                    PP[num].in_disk_index = -1;
                    for(j=0; j<1000; j++)
                    {
                        if(DD[j].disk_page_num == num)
                        {
                            DD[j].disk_page_num = -1;
                            break;
                        }
                    }

                }

            }
            else
            {
                printf("Hit, %d=>%d\n",num,PP[num].in_physical_index);
            }


        }

    }
    else if(strcmp(str[1],"SLRU")==0)
    {
        //printf("SLRU\n");

        int total_inactive_count =0;
        int total_active_count =0;
        if(N%2!=0)
        {
            total_inactive_count = (N+1)/2;
            total_active_count = (N-1)/2;
        }
        else
        {
            total_inactive_count = N/2;
            total_active_count = N/2;
        }

        int used_inactive_count = 0;
        int used_active_count = 0;

        my_page PP[M];
        for(i=0; i<M; i++)
        {
            PP[i].page_num = i;
            PP[i].in_physical_index = -1;
            PP[i].in_disk_index = -1;

            PP[i].in_use_bit = 0;
            PP[i].present_bit = 0;

            PP[i].page_active = -1;
            PP[i].page_reference = -1;
            PP[i].inactive_list_index = -1;
            PP[i].active_list_index = -1;
        }

        my_disk DD[1000];
        for(i=0; i<1000; i++)
        {
            DD[i].disk_page_num = -1;
        }

        for(i=0; i<index/2; i++) // deal with page read/write   // total_count  miss_count
        {
            //printf("%d\n",((int)str2[2*i+1][0]-48)); // (int)str2[2*i+1][0] --> ASCII code
            total_count+=1;
            int num = ((int)str2[2*i+1][0]-48);
            PP[num].in_use_bit = 1;
            int miss_or_not = 1;
            for(j=0; j<M; j++)
            {
                if(PP[j].page_num==num && PP[j].present_bit==1)
                {
                    miss_or_not = 0;
                }
            }

            if(miss_or_not == 1)
            {
                miss_count+=1;
                printf("Miss, ");
                if(used_inactive_count < total_inactive_count)  // inactive list not full
                {
                    PP[num].in_physical_index = used_frame_count;
                    printf("%d, -1>>-1, %d<<-1\n",used_frame_count,num);
                    used_frame_count+=1;

                    PP[num].present_bit = 1;

                    used_inactive_count+=1;
                    PP[num].page_active = 0;
                    PP[num].page_reference = 1;
                    PP[num].inactive_list_index = 0;

                    if(used_inactive_count >1)
                    {
                        for(j=0; j<M; j++)
                        {
                            if(PP[j].page_active ==0 && PP[j].page_num != num)
                            {
                                PP[j].inactive_list_index +=1;
                            }
                        }
                    }
                }
                else  // inactive list full
                {
                    int page_out_num = -1;
                    int inactive_tail_num = -1;

                    while(page_out_num == -1)
                    {
                        // find inactive list tail
                        for(j=0; j<M; j++)
                        {
                            if(PP[j].inactive_list_index == total_inactive_count-1)
                            {
                                inactive_tail_num = j;
                                break;
                            }
                        }

                        if(PP[inactive_tail_num].page_reference == 0)
                        {
                            page_out_num = inactive_tail_num;
                        }
                        else
                        {
                            PP[inactive_tail_num].page_reference = 0;
                            PP[inactive_tail_num].inactive_list_index = 0;
                            for(j=0; j<M; j++)
                            {
                                if(PP[j].page_active ==0 && PP[j].page_num != inactive_tail_num)
                                {
                                    PP[j].inactive_list_index +=1;
                                }
                            }

                        }
                    }

                    PP[num].present_bit = 1;
                    PP[num].in_physical_index = PP[page_out_num].in_physical_index;
                    //printf("%d, %d>>%d, %d<<%d\n",PP[num].in_physical_index,page_out_num,PP[page_out_num].in_physical_index,num,PP[num].in_disk_index);
                    PP[num].page_active = 0;
                    PP[num].page_reference = 1;

                    PP[num].inactive_list_index = 0;
                    for(j=0; j<M; j++)
                    {
                        if(PP[j].page_active ==0 && PP[j].page_num != num)
                        {
                            PP[j].inactive_list_index +=1;
                        }
                    }

                    PP[page_out_num].in_physical_index = -1;
                    PP[page_out_num].present_bit = 0;
                    PP[page_out_num].page_active = -1;
                    PP[page_out_num].page_reference = -1;
                    PP[page_out_num].inactive_list_index = -1;

                    for(j=0; j<1000; j++)
                    {
                        if(DD[j].disk_page_num == -1)
                        {
                            DD[j].disk_page_num = page_out_num;
                            PP[page_out_num].in_disk_index = j;
                            break;
                        }
                    }

                    printf("%d, %d>>%d, %d<<%d\n",PP[num].in_physical_index,page_out_num,PP[page_out_num].in_disk_index,num,PP[num].in_disk_index);

                    if(PP[num].in_disk_index != -1)
                    {
                        for(j=0; j<1000; j++)
                        {
                            if(DD[j].disk_page_num == num)
                            {
                                DD[j].disk_page_num = -1;
                                break;
                            }
                        }
                    }
                    PP[num].in_disk_index = -1;

                }

            }
            else
            {
                printf("Hit, %d=>%d\n",num,PP[num].in_physical_index);
                //...
                if(PP[num].page_active == 0)  // hit in inactive list
                {
                    if(PP[num].page_reference == 1)
                    {
                        if(used_active_count == total_active_count)  // active list full
                        {
                            //PP[num].page_active = 1;
                            //PP[num].page_reference = 0;
                            int temp_index = PP[num].inactive_list_index;
                            PP[num].inactive_list_index = -1;
                            //PP[num].active_list_index = 0;

                            if(used_inactive_count >1)
                            {
                                for(j=0; j<M; j++)
                                {
                                    if(PP[j].page_active ==0 && PP[j].inactive_list_index > temp_index)
                                    {
                                        PP[j].inactive_list_index -=1;
                                    }
                                }
                            }

                            int page_out_num = -1;
                            int active_tail_num = -1;

                            while(page_out_num == -1)
                            {
                                // find active list tail
                                for(j=0; j<M; j++)
                                {
                                    if(PP[j].active_list_index == total_active_count-1)
                                    {
                                        active_tail_num = j;
                                        break;
                                    }
                                }

                                if(PP[active_tail_num].page_reference == 0)
                                {
                                    page_out_num = active_tail_num;
                                }
                                else
                                {
                                    PP[active_tail_num].page_reference = 0;
                                    PP[active_tail_num].active_list_index = 0;
                                    for(j=0; j<M; j++)
                                    {
                                        if(PP[j].page_active ==1 && PP[j].page_num != active_tail_num)
                                        {
                                            PP[j].active_list_index +=1;
                                        }
                                    }

                                }
                            }

                            PP[num].page_active = 1;
                            PP[num].page_reference = 0;
                            PP[num].active_list_index = 0;

                            PP[page_out_num].page_active = 0;
                            PP[page_out_num].active_list_index = -1;
                            PP[page_out_num].inactive_list_index = used_inactive_count-1;


                        }
                        else   // active list not full
                        {
                            used_inactive_count -=1;
                            used_active_count +=1;
                            PP[num].page_active = 1;
                            PP[num].page_reference = 0;
                            int temp_index = PP[num].inactive_list_index;
                            PP[num].inactive_list_index = -1;
                            PP[num].active_list_index = 0;

                            if(used_active_count >1)
                            {
                                for(j=0; j<M; j++)
                                {
                                    if(PP[j].page_active ==1 && PP[j].page_num != num)
                                    {
                                        PP[j].active_list_index +=1;
                                    }
                                }
                            }

                            if(used_inactive_count >=1)
                            {
                                for(j=0; j<M; j++)
                                {
                                    if(PP[j].page_active ==0 && PP[j].inactive_list_index > temp_index)
                                    {
                                        PP[j].inactive_list_index -=1;
                                    }
                                }
                            }

                        }

                    }
                    else  // PP[num].page_reference == 0
                    {
                        PP[num].page_reference = 1;
                        if(PP[num].inactive_list_index != 0)
                        {
                            int temp_index = PP[num].inactive_list_index;
                            //PP[num].inactive_list_index = 0;
                            for(j=0; j<M; j++)
                            {
                                if(PP[j].page_active ==0 && PP[j].inactive_list_index < temp_index)
                                {
                                    PP[j].inactive_list_index +=1;
                                }
                            }
                            PP[num].inactive_list_index = 0;
                        }


                    }

                }
                else   // hit in active list
                {
                    PP[num].page_reference = 1;
                    if(PP[num].active_list_index != 0)
                    {
                        int temp_index = PP[num].active_list_index;
                        //PP[num].active_list_index = 0;
                        for(j=0; j<M; j++)
                        {
                            if(PP[j].page_active ==1 && PP[j].active_list_index < temp_index)
                            {
                                PP[j].active_list_index +=1;
                            }
                        }
                        PP[num].active_list_index = 0;
                    }

                }

            }



        }

    }
    else
    {
        printf("Wrong Policy\n");
        return 0;
    }





    printf("Page Fault Rate: %.3f\n",((float)miss_count/(float)total_count));

    return 0;
}
