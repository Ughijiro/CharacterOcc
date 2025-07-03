#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Nodes{
    char letter;
    unsigned int occurencies;
    struct Nodes *next;
}Node;

Node* create_nod(char letter){

    Node *new_node = (Node *) malloc(sizeof(Node));

    if(new_node == NULL){

        perror("Error allocating memory.\n");
        exit(EXIT_FAILURE);
    }

    new_node->letter = letter;
    new_node->occurencies = 1;
    new_node->next = NULL;

    return new_node;
}

void add_node(Node **head, char letter){

    Node *current_node = *head;
    Node *previous_node = NULL;

    while(current_node != NULL && current_node->letter < letter){
        previous_node = current_node;
        current_node = current_node->next;
    }
    if(current_node != NULL && current_node->letter == letter){
        current_node->occurencies++;
    }
    else{
        Node *new_node = create_nod(letter);

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



int main(int argc, char **argv){
    
    if(argc < 3){
        printf("Not enough arguments.\n");
        exit(EXIT_FAILURE);
    }

    FILE *input_file = fopen(argv[1], "r");

    if(input_file == NULL){
        printf("ERROR while opening file.\n");
        exit(EXIT_FAILURE);
    }

    Node *head;
    Node *other;
    other->occurencies = 0;

    char line[1000];
    char *word;
    unsigned int total = 0;

    while(fgets(line, sizeof(line), input_file)){

        word = strtok(line, " ");
        while(word != NULL){
            for(int i = 0; i < strlen(word); i++){
                
                if(isalpha(word[i])){
                    add_node(&head, word[i]);
                }
                else{
                    other->occurencies++;
                }
                total++;
            }
            word = strtok(NULL, " ");
        }
    }
    fclose(input_file);

    FILE* output_file = fopen(argv[2], "w");

    if(output_file == NULL){
        printf("ERROR opening file.\n");
        exit(EXIT_FAILURE);
    }


    Node* current_node = head;

    while(current_node != NULL){

        double percentage = ((double)current_node->occurencies/total)  * 100;
        fprintf(output_file, "%c - %.3f%%\n", current_node->letter, percentage);
        current_node = current_node->next;
    }

    double p = ((double)other->occurencies/total)  * 100;
    
    fprintf(output_file, "other - %.3f%%", p);
    fclose(output_file);
    free_list(head);
    
    return 0;
}
