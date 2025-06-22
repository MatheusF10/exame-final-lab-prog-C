#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct  {
    int id;
    int places;
    int occupation;
} Table;

typedef struct  {
    char group;
    int people;
    int table;
} Customers;

typedef struct {
    long size;
    char *buffer;
    int lines;
} File;

Table *tables;
int global_tables = 0;
Customers *customers;
int global_customers = 0;

FILE *file_customers;
FILE *file_tables;

long get_file_size(FILE *fp) {
    fseek(fp, 0L, SEEK_END);  

    long size = ftell(fp);  

    rewind(fp);

    return size;
}

File get_file(FILE *fp){
    File file;
    
    file.size = get_file_size(fp);

    if (file.size <= 0) {
        printf("Arquivo vazio ou erro ao obter tamanho.\n");

        fclose(fp);
       
        exit(1);
    }

    char *buffer = (char *)malloc(file.size + 1);

    file.buffer = buffer;

    if(!file.buffer){
        printf("Erro ao definir buffer do arquivo.");

        fclose(fp);

        free(buffer);

        exit(1);
    }

    fread(file.buffer, 1, file.size, fp);

    file.buffer[file.size] = '\0';

    file.lines = 0;

    for(int i = 0; file.buffer[i]; i++){
        if(file.buffer[i] != '\n'){ 
            continue;
        }

        file.lines++;
    }

    free(buffer);

    return file;
}

void initialize_customers(){
    File file = get_file(file_customers);
    char *line = strtok(file.buffer, "\n");
    customers = malloc(sizeof(Customers) * file.lines);
    
    // Pula o header do arquivo CSV
    line = strtok(NULL, "\n");
    
    // Atribui e inicializa a struct de mesas
    for(int i = 0; i < file.lines; i++){
        sscanf(line, "%c ,%d", &customers[i].group, &customers[i].people);
        customers[i].table = -1;
        line = strtok(NULL, "\n");
    }
    // Salva variável global de clientes para fins de iteração
    global_customers = file.lines;
}

void load_customers(){
    char path[100];

    printf("Indique o caminho do ficheiro de clientes: \n");
    scanf("%s", path);
    
    file_customers = fopen(path, "r+");

    if(!file_customers){
        printf("Erro ao abrir o arquivo de clientes.\n");

        exit(1);
    }

    printf("Carregado arquivos de clientes.\n");

    initialize_customers();
}

void initialize_tables(){
    File file = get_file(file_tables);
    char *line = strtok(file.buffer, "\n");
    tables = malloc(sizeof(Table) * file.lines);
    
    // Pula o header do arquivo CSV
    line = strtok(NULL, "\n");
    
    // Atribui e inicializa a struct de mesas
    for(int i = 0; i < file.lines; i++){
        sscanf(line, "%d,%d,%d", &tables[i].id, &tables[i].places, &tables[i].occupation);
        line = strtok(NULL, "\n");
    }

    global_tables = file.lines;
}

void load_tables(){
    char path[100];

    printf("Indique o caminho do ficheiro de mesas: \n");
    scanf("%s", path);
    
    file_tables = fopen(path, "r+");

    if(!file_tables){
        printf("Erro ao abrir o arquivo de mesas.\n");

        exit(1);
    }

    printf("Carregado arquivos de mesas.\n");

    initialize_tables();
}

void assign_tables(){    
    for(int i = 0; i < global_tables; i++){
        Table current_table = tables[i];

        for(int j = 0; j < global_customers; j++){ 
            Customers current_customer = customers[j];

            if(current_customer.table != -1){
                continue;
            }

            if(!current_table.occupation && current_table.places >= current_customer.people){
                tables[i].occupation = current_customer.people;
                customers[j].table = current_table.id;
                
                break;
            }
        }
    }
    
    printf("Mesas atribuidas...\n");
}

void see_table(Table table){
    printf(" Mesa | Lugares | Ocupacao \n ");

    printf("  %d      %d         %d    \n", table.id, table.places, table.occupation);
}

void edit_table(Table table){
    Table edited_table = table;

    printf("Editando mesa...\n");

    printf("Indique lugares e ocupação da mesa\n");
    scanf("%d %d", &edited_table.places, &edited_table.occupation);

    for(int i = 0; i < global_tables; i++){
        if(tables[i].id != edited_table.id){
            continue;
        }

        tables[i] = edited_table;

        break;
    }

    printf("Mesa editada com sucesso!\n");

    see_table(edited_table);
}

void delete_table(Table table){
    int found = 0;

    printf("Deletando mesa...\n");

    for (int i = 0; i < global_tables; i++) {
        if (tables[i].id == table.id) {
            found = 1;

            // Move todos os elementos à frente uma posição para trás
            for (int j = i; j < global_tables - 1; j++) {
                tables[j] = tables[j + 1];
            }

            // Reduz o número de mesas
            global_tables--; 

            break;
        }
    }

    if(!found){
        printf("Erro, nao foi possivel encontrar a mesa especificada.\n");

        exit(1);
    }

    printf("Mesa deletada com sucesso!\n");
}

void manage_table(){
    int table_number, option, found = 0;
    Table table;

    printf("Gerir mesas...\n");

    printf("Indique o numero da mesa\n");

    scanf("%d", &table_number);

    for(int i = 0; i < global_tables; i++){
        if(tables[i].id != table_number){
            continue;
        }

        found = 1;
        
        table = tables[i];
        
        break;
    }

    if(!found){
        printf("Erro, nao foi possivel encontrar a mesa especificada.\n");

        exit(1);
    }

    printf("1 - Ver Mesa\n");
    printf("2 - Editar Mesa\n");
    printf("3 - Deletar Mesa\n");

    scanf("%d", &option);

    switch(option){
        case 1: 
            see_table(table);
            break;
        case 2:
            edit_table(table);
            break;
        default:
            delete_table(table);
    }
}

void clean_occupation(){
    int table_number, found = 0;

    printf("Indique o numero da mesa\n");
    scanf("%d", &table_number);

    printf("Limpando ocupacao\n");

    // Mapeia a mesa selecionada
    for(int i = 0; i < global_tables; i++){
        if(tables[i].id != table_number){
            continue;
        }

        // Desvincula cliente a mesa (desocupação)
        for(int j = 0; j < global_customers; j++){
            if(customers[j].table != table_number){
                continue;
            }

            customers[j].table = -1;
        }

        found = 1;
    
        tables[i].occupation = 0;
        
        break;
    }
}

void display_tables(){
    printf("Mostrando mesas:\n");

    for(int j = 0; j < global_customers; j++){
        Customers current_customer = customers[j];

        if(current_customer.table == -1){
            printf("Grupo %c - Aguarda\n", current_customer.group);

            continue;
        }

        printf("Grupo %c - Mesa %d\n", current_customer.group, current_customer.table);
    }
}

void save_tables(){
    char path[100];

    if (!file_tables) {
        printf("Erro ao abrir o ficheiro para escrita.\n");
    
        exit(1);
    }

    rewind(file_tables);
    
    // Escreve o cabeçalho
    fprintf(file_tables, "Mesa,Lugares,Ocupacao\n");

    // Escreve cada mesa com os dados atualizados
    for (int i = 0; i < global_tables; i++) {
        fprintf(file_tables, "%d,%d,%d\n", tables[i].id, tables[i].places, tables[i].occupation);
    }

    printf("Ficheiro de mesas salvo com sucesso!\n");
}

void menu(){
    int option;

    do {
        printf("Pressione uma opcao para iniciar:\n");

        printf("1 - Carregar clientes e mesas apartir de um CSV\n");
        printf("2 - Atribuir uma mesa a cada grupo de clientes\n");
        printf("3 - Ver, editar ou remover mesa existente\n");
        printf("4 - Limpar ocupacao de uma mesa\n");
        printf("5 - Apresentar as mesas atribuidas a cada grupo de clientes\n");
        printf("6 - Guardar o ficheiro de mesas CSV\n");
        printf("7 - Fechar o programa e sair\n");
    
        scanf("%d", &option);

        if(option > 6 || option < 1){
            printf("Opcao invalida. Por favor, escolha uma opcao entre 1 e 6.\n");

            menu();
        };

        switch(option){
        case 1: 
            load_customers();
            load_tables();
            break;
        case 2:
            assign_tables();
            break;
        case 3:
            manage_table();
            break;
        case 4:
            clean_occupation();
            break;
        case 5:
            display_tables();
            break;
        case 6:
            save_tables();
            break;
        default:
            free(tables);
            free(customers);
            fclose(file_tables);
            fclose(file_customers);
            exit(0);
        };

    } while (option != 6);
}