#include<stdlib.h>
#include<stdio.h>

struct node_t {
    int m;
};

struct Node{
    struct node_t *t;
    struct Node *next;
};

void deleteElem(struct Node** head, struct node_t *elem)
{
    if(*head == NULL) {
        return;
    } else if((*head)->t ==  elem){
        *head = (*head)->next;
        return;
    }
    struct Node* prev = (*head)->next;
    struct Node* temp = *head;
    while(temp != NULL) {
        if((temp->t) == elem) {
            prev->next = temp->next;
            printf("vi kanske gjorde det idk\n");
            free(prev);
            free(temp);
            return; //Duplicate, no put in plz
        }
        prev = temp;
        temp = temp->next;
    }
    free(prev);
    free(temp);
    return;
}

void deleteStart(struct Node** head){
    struct Node* temp = *head;
  
    // If head is NULL it means Singly Linked List is empty
    if(*head == NULL){
        printf("Impossible to delete from empty Singly Linked List");
        return;
    }
    
    // move head to next node
    *head = (*head)->next;
    printf("Deleted: %d\n", (temp->t)->m);
    free(temp);
}

void insertStart(struct Node** head, struct node_t *data){
    struct Node* temp = *head;

    while(temp != NULL) {
        if((temp->t) == data) {
            printf("Duplicate, can't add to Set");
            return; //Duplicate, no put in plz
        }
        temp = temp->next;
    }
    
    // dynamically create memory for this newNode
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    
    // assign data value
    newNode->t = data;
    // change the next node of this newNode 
    // to current head of Linked List
    newNode->next = *head;

    //re-assign head to this newNode
    *head = newNode;
    printf("Inserted %d\n",(newNode->t)->m);
}

void display(struct Node* node){
    printf("\nLinked List: ");
    // as linked list will end when Node is Null
    while(node!=NULL){
        printf("%d ",(node->t)->m);
        node = node->next;
    }
    printf("\n");
}

int main()
{
    struct Node* head = NULL;

    // Need '&' i.e. address as we need to change head
    struct node_t t;
    t.m = 10;
    struct node_t s;
    s.m = 100;
    struct node_t a;
    a.m = 200;
    insertStart(&head,&t);
    insertStart(&head,&s);
    deleteElem(&head, &s);
    insertStart(&head,&a);
    deleteElem(&head, &a);
    deleteElem(&head, &t);


    // No Need for '&' as not changing head in display operation
    display(head);
    
    //deleteStart(&head);
    //deleteStart(&head);
    //display(head);
    
    return 0; 
}