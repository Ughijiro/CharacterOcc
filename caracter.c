#include <stdio.h>
#include <stdlib.h>

typedef struct Nodes{
    unsigned int current_number;
    unsigned int ocurrencies;
    struct Nodes *next;
}Node;


Node* create_node(unsigned int number){

    Node* new_node = (Node *)malloc(sizeof(Node));
    
    if(new_node == NULL){
        perror("ERROR, allocating memory.\n");
        exit(EXIT_FAILURE);
    }

    new_node->current_number = number;
    new_node->ocurrencies = 1;
    new_node->next = NULL;

    return new_node;
}

void add_node(Node **head, unsigned int nr){

    Node* current_node = *head;
    Node* previous_node = NULL;

    while(current_node != NULL && current_node->current_number < nr){
        
        previous_node = current_node;
        current_node= current_node->next;
    }
    if(current_node != NULL && current_node->current_number == nr){
        current_node->ocurrencies++;
    }
    else{
        Node* new_node = create_node(nr);
        if(previous_node == NULL){
            new_node->next = *head;
            *head = new_node;
        }
        else{
            previous_node->next = new_node;
            new_node->next = current_node;
        }
    }
}

void free_list(Node* head){

    Node* aux;
    while(head != NULL){
        aux = head;
        head = head->next;
        free(aux);
    }

}


int main(int argc, char *argv[]){
    
    if(argc < 3){
        printf("Error");
        exit(EXIT_FAILURE);
    }

    Node* head = NULL;

    FILE* input_file = fopen(argv[1], "rb");
    
    if(input_file == NULL){
        printf("ERROR opening file.\n");
        exit(EXIT_FAILURE);
    }

    unsigned int number;
    unsigned int total=0;
    while(fread(&number, sizeof(unsigned int), 1, input_file)){
        
        add_node(&head, number);
        total++;
    }
    fclose(input_file);

/*  if(input_file != NULL){
        printf("Error while closing.\n");
        exit(EXIT_FAILURE);
    }
 */
    FILE* output_file = fopen(argv[2], "w");

    if(output_file == NULL){
        printf("ERROR opening file.\n");
        exit(EXIT_FAILURE);
    }


    Node* current_node = head;

    while(current_node != NULL){

        double percentage = ((double)current_node->ocurrencies / total) * 100;

        fprintf(output_file, "%u : %u : %.4f%%\n", current_node->current_number, current_node->ocurrencies, percentage);
        current_node = current_node->next;
    }

    fclose(output_file);

    /* if(output_file != NULL){
        printf("Error while closing.\n");
        exit(EXIT_FAILURE);
    }
 */
    free_list(head);
    return 0;
}