#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H
    
typedef struct  {
    int id;
    int places;
    int occupation;
} Table;

typedef struct  {
    char group;
    int people;
} Customers;

void menu();

void load_customers();

void load_tables();

void assign_tables();

void manage_table();

void display_tables();

void save_tables();
    
#endif