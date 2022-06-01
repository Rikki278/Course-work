#include <fstream>
#include <iostream>
#include <cstring>

#define BUFFER_SIZE 4096

#define ADD_PRODUCT 1
#define DELETE_PRODUCT 2
#define UPDATE_PRODUCT 3
#define PRINT_LIST 4
#define PRINT_DATA_WITH_CURRENT_DATE 5
#define SEARCH_BY_LIST_OF_PRODUCTS 6
#define EMPTY_STORE_PLACE 7
#define SEARCH_BY_CATEGORY 8
#define SORTING 9
#define SAVE_TO_FILE 10
#define READ_FROM_FILE 11
#define EXIT 12

using namespace std;

typedef struct product product;

static product *head = NULL;

struct product {
    char *name;
    char *category;
    int amount_in_storage;
    //expiration_date;
    int day_expiration, month_expiration, year_expiration; //day, month, year
    //date_of_deliver;
    int day_of_deliver, month_of_deliver, year_of_deliver; //day, month, year
    int amount_of_storage_space_for_category;
    product *next;
};

//Prototypes
int menu();
void add_node(); //ADDING PRODUCT
void delete_node(product **head); //DELETING PRODUCT
void update_data(); //UPDATE DATA OF PRODUCT
void print_list(); //PRINT ALL PRODUCTS
void print_data_with_current_date(); //PRINT ALL PRODUCTS WITH EXPIRED DATE
void search_by_list_of_products(); //PRINT PRODUCTS BY LIST OF PRODUCTS
void empty_store_place(); //PRINT EMPTY STORE PLACE OF PRODUCT
void search_by_category(); //SEARCH PRODUCTS BY CATEGORY
void sorting(); //SORTING LIST OF PRODUCTS
void save_to_file(); //SAVE INFO IN FILE
void read_from_file(); //READ INFO FROM FILE

//Secondary used functions
void add_product_to_list(product *ptr); //adding product to list
void write_data(product *ptr); //write data of product
int node_count(product *head, int count); //count of products
int position_for_deleting(); //entering position of product that you want to delete
void pauseConsole(); //just pause

//Check functions
void check_for_expiration_date(product *ptr);
void check_for_date_of_deliver(product *ptr);
void check_for_storage_place(product *ptr);
int check_for_amount_of_nodes(int number_of_node, int count);
int check_for_position_of_nodes(int position, int count);
int check_for_current_day(int day_cur);
int check_for_current_month(int month_cur);
int check_for_current_year(int year_cur);


int main() {
    cout << "Welcome to my program\n";
    int position = 0;

    while (1) {
        switch (menu()) {
            case ADD_PRODUCT:
                add_node();
                break;
            case DELETE_PRODUCT:
                delete_node(&head);
                break;
            case UPDATE_PRODUCT:
                update_data();
                break;
            case PRINT_LIST:
                print_list();
                break;
            case PRINT_DATA_WITH_CURRENT_DATE:
                print_data_with_current_date();
                break;
            case SEARCH_BY_LIST_OF_PRODUCTS:
                search_by_list_of_products();
                break;
            case EMPTY_STORE_PLACE:
                empty_store_place();
                break;
            case SEARCH_BY_CATEGORY:
                search_by_category();
                break;
            case SORTING:
                sorting();
                break;
            case SAVE_TO_FILE:
                save_to_file();
                break;
            case READ_FROM_FILE:
                read_from_file();
                break;
            case EXIT:
                cout << "Goodbye...";
                pauseConsole();
                exit(0);
            default:
                cout << "Something went wrong -_-\nEnter correct number\n";
        }
    }
}

int menu() {
    int choice = 0;
    do {
        cout << "Menu\n";
        cout << "1. Add element\n";
        cout << "2. Delete element\n";
        cout << "3. Update element\n";
        cout << "4. Print all data\n";
        cout << "5. Print list with expired date on current date\n";
        cout << "6. Find product and amount on storage\n";
        cout << "7. Print empty storage places for products\n";
        cout << "8. Find product by the category\n";
        cout << "9. Sort by name and date\n";
        cout << "10. Save to file\n";
        cout << "11. Read from file\n";
        cout << "12. Exit\n\n";
        cout << "Enter your choice here-> ", cin >> choice;
        system("cls");
    } while (choice > 13);
    return choice;
}

void add_node() {    //creating product
    cout << "ADDING NEW PRODUCT\n";
    //allocation memory
    product *ptr = (product *) malloc(sizeof(product));
    //creat NULL element
    ptr->next = NULL;

    write_data(ptr);//writing info about product

    add_product_to_list(ptr);//adding product to list

    pauseConsole();//pause
    system("cls");//clear
}

void write_data(product *ptr) { //product info

    //add name
    ptr->name = (char *) malloc(64 * sizeof(char));
    cout << "Enter name:";
    cin >> ptr->name;

    //add category
    ptr->category = (char *) malloc(64 * sizeof(char));
    cout << "\nEnter category: ";
    cin >> ptr->category;

    //add amount in storage
    cout << "\nEnter amount in storage: ";
    cin >> ptr->amount_in_storage;

    //check for amount in storage
    if (ptr->amount_in_storage < 0) {
        cout << "\nWrong data.";

        do {
            cout << "Write correct amount in storage:";
            cin >> ptr->amount_in_storage;
        } while (ptr->amount_in_storage < 0);

        if (ptr->amount_in_storage > 0) {
            cout << "New data saved\n";
        }
    }

    //add expiration date
    cout << "\nEnter expiration date:\n";
    cout << "Enter day:";
    cin >> ptr->day_expiration;
    cout << "Enter month:";
    cin >> ptr->month_expiration;
    cout << "Enter year:";
    cin >> ptr->year_expiration;
    check_for_expiration_date(ptr);//check for expiration sar

    //add date of deliver
    cout << "\nEnter date of deliver:\n";
    cout << "Enter day:";
    cin >> ptr->day_of_deliver;
    cout << "Enter month:";
    cin >> ptr->month_of_deliver;
    cout << "Enter year:";
    cin >> ptr->year_of_deliver;
    check_for_date_of_deliver(ptr);//check for date of deliver

    //add amount of storage place for category
    cout << "\nEnter storage place for category:";
    cin >> ptr->amount_of_storage_space_for_category;
    check_for_storage_place(ptr);//check for storage place

}

void add_product_to_list(product *ptr) { //adding product to list
   //if list is empty
    if (head == NULL) {
        head = ptr;
        return;
    }

    product *tmp = head;
    //finding last element
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = ptr;


}

void delete_node(product **head) {
  /*  int position;
    //take position of delete element
    position = position_for_deleting();*/
    int position;
    product *current = *head;
    product *previous = *head;

    if (*head == NULL) {
        cout << "List is empty\n";
        pauseConsole();
        system("cls");
        return;
    }else{
        //take position of delete element
        position = position_for_deleting();
    }
    if (position == 1) { //first position and don't need to go through the structure
        *head = current->next;
        free(current);//clear memory and delete element
        current = NULL;
        cout << "\nProduct has been deleted\n";
    } else {
        while (position != 1) {
            previous = current;
            current = current->next;
            position--;
        }
        previous->next = current->next;
        free(current);
        current = NULL;
        cout << "\nProduct has been deleted\n";
    }
    pauseConsole();
    system("cls");
}

int position_for_deleting() {
    int count = 0;
    count = node_count(head, count);//counting nodes
    int number_of_node;

    cout << "\nEnter position of node:",cin >> number_of_node, cout <<"\n ";


    //check
    number_of_node = check_for_amount_of_nodes(number_of_node, count); //check of enter number of product
    int position = number_of_node;
    return position;
}

void update_data() {

    if (head == NULL) {
        cout << "List is empty\n";
        pauseConsole();
        system("cls");
        return;
    }

    int count = 0;
    count = node_count(head, count);//counting elements
    int number_of_node;

    cout << "\nData of which product you want to edit: ";
    cin >> number_of_node;

    //check
    number_of_node = check_for_amount_of_nodes(number_of_node, count);//check for number of product

    product *tmp = head;
    product *temp = head;
    int i = 1;
    while (tmp != NULL) {
        if (i == number_of_node) {
            temp = tmp;
        }
        i++;
        tmp = tmp->next;
    }

    cout << "\nEnter new data\n";
    product *ptr = temp;
    write_data(ptr);//entering new data
    cout << "\nData is successfully saved";

    pauseConsole();
    system("cls");
}

int node_count(product *head, int count) {
    //int count = 0 ;
    if (head == NULL) {
        cout << "\nList is empty\n";
        pauseConsole();
        system("cls");
        return 0;
    }
    product *ptr = NULL;
    ptr = head;
    //go through the structure and count elements
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }
    cout << "Amount of products: " << count;
    return count;
}

void print_list() {

    cout << "LIST OF PRODUCTS: \n\n";

    if (head == NULL) {
        cout << "LIST IS EMPTY! \n\n";
        pauseConsole();
        system("cls");
        return;
    }

    product *tmp = head;
    //go through structure and print all data
    while (tmp != NULL) {
        cout << "-----------------\n";
        cout << "NAME:" << tmp->name << "\n";
        cout << "CATEGORY:" << tmp->category << "\n";
        cout << "AMOUNT IN STORAGE:" << tmp->amount_in_storage << "\n";
        cout << "EXPIRATION DATE: Day:" << tmp->day_expiration << " Month:" << tmp->month_expiration << " Year:"
             << tmp->year_expiration << "\n";
        cout << "DATE OF DELIVER: Day:" << tmp->day_of_deliver << " Month:" << tmp->month_of_deliver << " Year:"
             << tmp->year_of_deliver << "\n";
        cout << "AMOUNT OF STORAGE PLACE FOR CATEGORY:" << tmp->amount_of_storage_space_for_category << "\n";
        cout << "-----------------\n";

        tmp = tmp->next;
    }
    pauseConsole();
    system("cls");
}

void print_data_with_current_date() {

    if (head == NULL) {
        cout << "LIST IS EMPTY! \n\n";
        pauseConsole();
        system("cls");
        return;
    }

    int day_cur, month_cur, year_cur; //current date
    cout << "Enter current date: \n";//entering data
    cout << "Day:";
    cin >> day_cur;
    cout << "Month:";
    cin >> month_cur;
    cout << "Year:";
    cin >> year_cur;

    //check for mistakes for date
    day_cur = check_for_current_day(day_cur);
    month_cur = check_for_current_month(month_cur);
    year_cur = check_for_current_year(year_cur);
    //printing current date
    cout << "Current date: Day:" << day_cur << " Month:" << month_cur << " Year:" << year_cur;



    product *tmp = head;
    //printing products with expired date
    while (tmp != NULL) {
        if (tmp->day_expiration < day_cur || tmp->month_expiration < month_cur || tmp->year_expiration < year_cur) {

            cout << "\n-----------------\n";
            cout << "NAME:" << tmp->name << "\n";
            cout << "CATEGORY:" << tmp->category << "\n";
            cout << "AMOUNT IN STORAGE:" << tmp->amount_in_storage << "\n";
            cout << "EXPIRATION DATE: Day:" << tmp->day_expiration << " Month:" << tmp->month_expiration << " Year:"
                 << tmp->year_expiration << "\n";
            cout << "DATE OF DELIVER: Day:" << tmp->day_of_deliver << " Month:" << tmp->month_of_deliver << " Year:"
                 << tmp->year_of_deliver << "\n";
            cout << "AMOUNT OF STORAGE PLACE FOR CATEGORY:" << tmp->amount_of_storage_space_for_category << "\n";
            cout << "-----------------\n";
        }
        tmp = tmp->next;
    }
    pauseConsole();
    system("cls");
}

void empty_store_place() {
    char name_of_product[20];//array for product
    int check = 0;//check

    product *tmp = head;

    if (head == NULL) {
        cout << "LIST IS EMPTY! \n\n";
        pauseConsole();
        system("cls");
        return;
    }


    cout << "Enter name of product:";
    cin >> name_of_product;

    while (tmp != NULL) {
        if (strcmp(name_of_product,tmp->name) == 0) {
            int empty_space;
            //counting empty space
            empty_space = tmp->amount_of_storage_space_for_category - tmp->amount_in_storage;
            //printing
            cout << "-----------------\n";
            cout << "NAME:" << tmp->name << "\n";
            cout << "EMPTY STORAGE PLACE:" << empty_space << "\n";
            cout << "-----------------\n";
            check++;
        }
        tmp = tmp->next;
    }

    if (!check){
        int choice;
        cout << "\nWrong name\n";
        cout << "Do you want to try again?(1-yes, 2-no)";
        cin >> choice;
        if (choice == 1) {
            //pointer on function to invoke her again
            void (*empty_sp_ptr)();
            empty_sp_ptr = empty_store_place;
            empty_sp_ptr();
            return;
        }
    }

    pauseConsole();
    system("cls");
}

void search_by_category() {
    char search_category[80];//array for category
    int check = 0; //for check

    product *tmp = head;

    if (head == NULL) {
        cout << "LIST IS EMPTY! \n\n";
        pauseConsole();
        system("cls");
        return;
    }

    cout << "SEARCH PRODUCTS BY CATEGORY\n";
    cout << "\nEnter category:", cin >> search_category;


    while (tmp != NULL) {
        if (strcmp(search_category, tmp->category) == 0) {

            cout << "-----------------\n";
            cout << "List of product with " << search_category << " category\n";
            cout << "NAME:" << tmp->name << "\n";
            cout << "CATEGORY:" << tmp->category << "\n";
            cout << "AMOUNT IN STORAGE:" << tmp->amount_in_storage << "\n";
            cout << "EXPIRATION DATE: Day:" << tmp->day_expiration << " Month:" << tmp->month_expiration << " Year:"
                 << tmp->year_expiration << "\n";
            cout << "DATE OF DELIVER: Day:" << tmp->day_of_deliver << " Month:" << tmp->month_of_deliver << " Year:"
                 << tmp->year_of_deliver << "\n";
            cout << "AMOUNT OF STORAGE PLACE FOR CATEGORY:" << tmp->amount_of_storage_space_for_category << "\n";
            cout << "-----------------\n";
            check++;
        }
        tmp = tmp->next;
    }

    if(!check){
        int choice;
        cout << "\nWrong category\n";
        cout << "Do you want to try again?(1-yes, 2-no)";
        cin >> choice;
        if (choice == 1) {
            void (*search_by_category_ptr)();
            search_by_category_ptr = search_by_category;
            search_by_category_ptr();
            return;
        }
    }

    pauseConsole();
    system("cls");
}

void search_by_list_of_products() {

    char **strings;
    int amount;//amount of products

    product *tmp = head;

    if (head == NULL) {
        cout << "LIST IS EMPTY! \n\n";
        pauseConsole();
        system("cls");
        return;
    }

    cout << "Enter amount of products in list:";
    cin >> amount;

    strings = (char **) malloc(amount * sizeof(char *));

    char buffer[BUFFER_SIZE];
    int length = 0;

    while (getchar() != '\n');

    cout << "\n";

    //getting string
    for (int i = 0; i < amount; ++i) {
        cout << "Enter product " << i + 1 << "(products that not in list won't be printed):";
        fgets(buffer, BUFFER_SIZE, stdin);
        length = strlen(buffer);
        buffer[length - 1] = '\0';
        strings[i] = (char *) malloc(length * sizeof(char));
        strcpy(strings[i], buffer);
    }

    cout << "Result:";
    for (int i = 0; i < amount; i++) {
        cout << "Product " << i + 1 << ": " << strings[i] << "\n";
    }
    cout << "\n";


    //printing
    while (tmp != NULL) {
        for (int i = 0; i < amount; ++i) {
            if (strcmp(strings[i], tmp->name) == 0) {

                cout << "-----------------\n";
                cout << "NAME:" << tmp->name << "\n";
                cout << "AMOUNT IN STORAGE:" << tmp->amount_in_storage << "\n";
                cout << "-----------------\n";
            }
        }
        tmp = tmp->next;
    }

    free(strings);
    pauseConsole();
    system("cls");
}

void swap_char(char *p, char *q) { //function to sort by name
    char a[50] = "";
    strcpy(a, p);
    strcpy(p, q);
    strcpy(q, a);
}

void sorting() {
    if (head == NULL) {
        cout << "LIST IS EMPTY! \n\n";
        pauseConsole();
        system("cls");
        return;
    } else {
        product *temp = head, *index = NULL;
        int d_del, m_del, y_del; //date of deliver

        int d_exp, m_exp, y_exp; //date of expiration

        int store, space; //amount int storage and amount in storage place

        while (temp != NULL) {
            index = temp->next;
            while (index != NULL) {
                if (strcmp(temp->name, index->name) > 0) {
                    swap_char(index->name, temp->name);
                    swap_char(index->category, temp->category);
                }
                if (temp->day_of_deliver > index->day_of_deliver || temp->month_of_deliver > index->month_of_deliver ||
                    temp->year_of_deliver > index->year_of_deliver) {
                    //sorting date of deliver
                    d_del = temp->day_of_deliver;
                    m_del = temp->month_of_deliver;
                    y_del = temp->year_of_deliver;

                    temp->day_of_deliver = index->day_of_deliver;
                    temp->month_of_deliver = index->month_of_deliver;
                    temp->year_of_deliver = index->year_of_deliver;

                    index->day_of_deliver = d_del;
                    index->month_of_deliver = m_del;
                    index->year_of_deliver = y_del;
                    //sorting date of expiration
                    d_exp = temp->day_expiration;
                    m_exp = temp->month_expiration;
                    y_exp = temp->year_expiration;

                    temp->day_expiration = index->day_expiration;
                    temp->month_expiration = index->month_expiration;
                    temp->year_of_deliver = index->year_of_deliver;

                    index->day_expiration = d_exp;
                    index->month_expiration = m_exp;
                    index->year_of_deliver = y_exp;
                    //sorting amount in storage
                    store = temp->amount_in_storage;
                    temp->amount_in_storage = index->amount_in_storage;
                    index->amount_in_storage = store;
                    //sorting storage space for category
                    space = temp->amount_of_storage_space_for_category;
                    temp->amount_of_storage_space_for_category = index->amount_of_storage_space_for_category;
                    index->amount_of_storage_space_for_category = space;
                }
                index = index->next;
            }
            temp = temp->next;
        }
    }
    cout << "List has been sorted";
    // print_list();
    pauseConsole();
    system("cls");
}

void save_to_file() {
    ofstream product_file_write("Products.txt");//open file to save

    product *tmp = head;

    //go through structure and save data in file
    while (tmp != NULL) {
        product_file_write << "\n" << tmp->name;
        product_file_write << "\n" << tmp->category;
        product_file_write << "\n" << tmp->amount_in_storage;
        product_file_write << "\n" << tmp->day_expiration;
        product_file_write << "\n" << tmp->month_expiration;
        product_file_write << "\n" << tmp->year_expiration;
        product_file_write << "\n" << tmp->day_of_deliver;
        product_file_write << "\n" << tmp->month_of_deliver;
        product_file_write << "\n" << tmp->year_of_deliver;
        product_file_write << "\n" << tmp->amount_of_storage_space_for_category;
        product_file_write << "\n";

        tmp = tmp->next;//next element
    }
    cout << "File has been written";
    pauseConsole();
    system("cls");
}

void read_from_file() {
    ifstream product_file_read("Products.txt");//open file from what will read
    ifstream text("Products.txt");
    string s;
    int i, n = 0;
    //count amount of strings in file
    while (getline(text, s)) {
        n++;
    }

    //every product 10 elements for entering so divide amount of strings on 10
    for (i = 0; i < n / 10; i++) {
        //allocation memory
        product *ptr = (product *)(malloc(sizeof(product)));

        ptr->next = NULL;
        //allocation memory
        ptr->name = (char *)(malloc(64 * sizeof(char)));
        ptr->category = (char *)(malloc(64 * sizeof(char)));
        //read from file
        product_file_read >> ptr->name >> ptr->category >> ptr->amount_in_storage >> ptr->day_expiration
                          >> ptr->month_expiration >> ptr->year_expiration >> ptr->day_of_deliver
                          >> ptr->month_of_deliver >> ptr->year_of_deliver >> ptr->amount_of_storage_space_for_category;
        //send element in function to add in structure
        add_product_to_list(ptr);
    }
    //close file
    product_file_read.close();
    cout << "File has been loaded";
    pauseConsole();
    system("cls");

}

int check_for_current_day(int day_cur){
    if (day_cur <= 0 || day_cur > 31) {
        cout << "\nWrong data.";

        do {
            cout << "Write correct day:";
            cin >> day_cur;
        } while (day_cur <= 0 || day_cur > 31);

        if (day_cur > 0 && day_cur < 31) {
            cout << "New data saved\n";
        }
    }
    return day_cur;
}

int check_for_current_month(int month_cur){
    if (month_cur <= 0 || month_cur > 12) {
        cout << "\nWrong data.";

        do {
            cout << "Write correct month:";
            cin >> month_cur;
        } while (month_cur <= 0 || month_cur > 12);

        if (month_cur > 0 && month_cur < 12) {
            cout << "New data saved\n";
        }
    }
    return month_cur;
}

int check_for_current_year(int year_cur){
    if (year_cur <= 0) {
        cout << "\nWrong data.";

        do {
            cout << "Write correct year:";
            cin >> year_cur;
        } while (year_cur <= 0);

        if (year_cur > 0) {
            cout << "New data saved\n";
        }
    }
    return year_cur;
}


void check_for_expiration_date(product *ptr) {

    if (ptr->day_expiration <= 0 || ptr->day_expiration > 31) {
        cout << "\nWrong data. ";

        do {
            cout << "Write correct day:";
            cin >> ptr->day_expiration;
        } while (ptr->day_expiration <= 0 || ptr->day_expiration > 31);

        if (ptr->day_expiration > 0 && ptr->day_expiration < 31) {
            cout << "New data saved\n";
        }
    }
    if (ptr->month_expiration <= 0 || ptr->month_expiration > 12) {
        cout << "\nWrong data. ";

        do {
            cout << "Write correct month:";
            cin >> ptr->month_expiration;
        } while (ptr->month_expiration <= 0 || ptr->month_expiration > 12);

        if (ptr->month_expiration > 0 && ptr->month_expiration < 12) {
            cout << "New data saved\n";
        }
    }
    if (ptr->year_expiration <= 0) {
        cout << "\nWrong data.";

        do {
            cout << "Write correct year:";
            cin >> ptr->year_expiration;
        } while (ptr->year_expiration <= 0);

        if (ptr->year_expiration > 0) {
            cout << "New data saved\n";
        }
    }

}

void check_for_date_of_deliver(product *ptr) {
    //date of deliver must be earlier than date of expiration
    if (ptr->day_of_deliver <= 0 || ptr->day_of_deliver > 31) {
        cout << "\nWrong data.";

        do {
            cout << "Write correct day:";
            cin >> ptr->day_of_deliver;
        } while (ptr->day_of_deliver <= 0 || ptr->day_of_deliver > 31);

        if (ptr->day_of_deliver > 0 && ptr->day_of_deliver < 31) {
            cout << "New data saved\n";
        }
    }
    if (ptr->month_of_deliver <= 0 || ptr->month_of_deliver > 12 ) {
        cout << "\nWrong data.";

        do {
            cout << "Write correct month:";
            cin >> ptr->month_of_deliver;
        } while (ptr->month_of_deliver <= 0 || ptr->month_of_deliver > 12);

        if (ptr->month_of_deliver > 0 && ptr->month_of_deliver < 12) {
            cout << "New data saved\n";
        }
    }
    if (ptr->year_of_deliver <= 0) {
        cout << "\nWrong data. ";

        do {
            cout << "Write correct year:";
            cin >> ptr->year_of_deliver;
        } while (ptr->year_of_deliver <= 0);

        if (ptr->year_of_deliver > 0 ) {
            cout << "New data saved\n";
        }
    }
}

void check_for_storage_place(product *ptr) {

    if (ptr->amount_of_storage_space_for_category < ptr->amount_in_storage) {
        cout << "Amount of storage place can't be less than amount in storage\n";
        cout << "Write more than or equal to " << ptr->amount_of_storage_space_for_category << " amount in storage: ";
        do {
            cin >> ptr->amount_of_storage_space_for_category;
        } while (ptr->amount_of_storage_space_for_category < ptr->amount_in_storage);
        if (ptr->amount_of_storage_space_for_category > ptr->amount_in_storage) {
            cout << "New data saved\n";
        }
    }

    if (ptr->amount_of_storage_space_for_category < 0) {
        cout << "\nWrong data.";

        do {
            cout << "Write correct storage place for category:";
            cin >> ptr->amount_of_storage_space_for_category;
        } while (ptr->amount_of_storage_space_for_category < 0);

        if (ptr->amount_of_storage_space_for_category > 0) {
            cout << "New data saved\n";
        }
    }

}

int check_for_amount_of_nodes(int number_of_node, int count) {
    if (number_of_node > count || number_of_node < 0) {
        cout << "\nWrong number of node\n";
        cout << "Enter right number of node:";
        cin >> number_of_node;

        if (number_of_node < count && number_of_node != 0) {
            cout << "\nData saved";
        }

            //making pointer on function to involve her again in case if number is still wrong
        else {
            int (*ptr_check_for_amount_of_nodes)(int, int);
            ptr_check_for_amount_of_nodes = check_for_amount_of_nodes;
            ptr_check_for_amount_of_nodes(number_of_node, count);
        }
    }
    return number_of_node;
}

int check_for_position_of_nodes(int position, int count) {
    if (position > count || position < 0) {
        cout << "\nWrong number of products\n";
        cout << "Enter right number of products:";
        cin >> position;

        if (position < count && position != 0) {
            cout << "\nData saved";
            return position;
        }

            //making pointer on function to involve her again in case if number is still wrong
        else {
            int (*ptr_check_for_position_of_nodes)(int, int);
            ptr_check_for_position_of_nodes = check_for_position_of_nodes;
            ptr_check_for_position_of_nodes(position, count);
        }
    }
    return 0;
}
//just pause
void pauseConsole() {
    cout << "\n\nPress any key to continue...";
    while (getchar() != '\n');
    getchar();
}
