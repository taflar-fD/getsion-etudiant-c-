#include <ncurses.h>
#include <string.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#define OPTION_COUNT 7

void cpu() {
    printw("\n");
    printw("\n");
    printw("\n");
    
    
    attron(COLOR_PAIR(1));  
    printw("\t            d8888b.         .d8888b. 88888888888 888     888 8888888b.  8888888888 888b    888 88888888888       \n");
    printw("\t          d88P  Y88b       d88P  Y88b    888     888     888 888   Y88b 888        8888b   888     888           \n");
    printw("\t          888    888       Y88b.         888     888     888 888    888 888        88888b  888     888           \n");
    printw("\t          888                Y888b.      888     888     888 888    888 8888888    888Y88b 888     888           \n");
    printw("\t          888  88888            Y88b.    888     888     888 888    888 888        888 Y88b888     888           \n");
    printw("\t          888    888 888888       888    888     888     888 888    888 888        888  Y88888     888           \n");
    printw("\t          Y88b  d88P       Y88b  d88P    888     Y88b. .d88P 888  .d88P 888        888   Y8888     888           \n");
    printw("\t            Y8888P88         Y8888P      888       Y88888P   8888888P   8888888888 888    Y888     888           \n");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
}

void loading() {
    printw("\n");

    printw("\n");
    printw("\n");


    attron(COLOR_PAIR(3));
    printw("\n\n\t\t                                         *LOADING*                                  \n\n\t\t");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(3));

    for (int i = 0; i < 100; i++) {
        attron(COLOR_YELLOW);
        printw("#");
        attroff(COLOR_YELLOW);
        refresh();
        napms(50);

    }
   
    attron(COLOR_PAIR(2)); 
  attroff(COLOR_PAIR(2));
}



int selection(int p) {
    int input;
    char h[OPTION_COUNT][50] = {
        "add_student",
        "record_of_student",
        "search_student",
        "update",
        "delete-student",
        "calculate_the_average",
        "Exit"
    };
    initscr();
    keypad(stdscr,TRUE);

    do {
        clear();

        for (int i = 0; i < OPTION_COUNT; i++) {
            if (p == i) {
                attron(COLOR_PAIR(3));
                printw("\n");
                printw("\t\t\t\t\t    __________________________________________\n");
                printw("\t\t\t\t\t\t\t\t");
                printw("\n");
                printw("\t\t\t\t\t               -->%s       \n", h[i]);
                printw("\t\t\t\t\t    __________________________________________\n");
                attron(COLOR_PAIR(3));
            } else {
                attron(COLOR_PAIR(2));
                printw("\n");
                printw("\t\t\t\t\t    __________________________________________\n");
                printw("\t\t\t\t\t\t\t\t");
                printw("\n");
                printw("\t\t\t\t\t                  %s       \n", h[i]);
                printw("\t\t\t\t\t    __________________________________________\n");
                attron(COLOR_PAIR(2));
            }
        }

        input = getch();
        if (input == KEY_DOWN) {
            p++;
            if(p>=OPTION_COUNT ){

                p=OPTION_COUNT-1;
            }

        }
        else if (input == KEY_UP) {
            p--;
            if(p < 0){

               p=0; 
            }
        }
    } while (input != '\n');
    
    return p;
}
typedef struct module {
    char nom_module[20];
    float coefficient;
    float note;
} module;
typedef struct student {
    char first_name[20];
    char last_name[20];
    long id;
    int age;
    char adresse[30];
    char email[30];
} student;

void add_student() {
    
    clear();
    char another;
    FILE* fk;
    student stu;
    char filename[100];
    do {
        clear();
        printw("\t\t\t\t============================== Add student info===================================\n\n\n");
        printw("\n\t\t\tEnter first name: ");
        scanw("%s", stu.first_name);
        printw("\n\t\t\tEnter last name: ");
        scanw("%s", stu.last_name);
        sprintf(filename, "database/%s_%s.txt", stu.first_name, stu.last_name);

        if (access("database", F_OK) == -1) {
            mkdir("database", 0777);
        }

        fk = fopen(filename, "a+");
        if (fk == NULL) {
            printw("\t\t\tCan't open file\n");
        } else {
            printw("\t\t\tStored successfully\n");
        }

        printw("\n\t\t\tId: ");
        scanw("%li", &stu.id);
        do {
            printw("\n\t\t\tEnter age: ");
            scanw("%d", &stu.age);
        } while (stu.age < 0 || stu.age > 150);

        printw("\n\t\t\tEnter address (state): ");
        scanw("%s", stu.adresse);
        printw("\n\t\t\tEnter Email (<foo>@<bar>.<baz>): ");
        scanw("%s", stu.email);

        fprintf(fk, "first_name:%s last_name: %s id: %li age:%d adress:%s email:%s\n", stu.first_name, stu.last_name, stu.id, stu.age, stu.adresse, stu.email);
        fclose(fk);

        fk = fopen("database/record.txt", "a+");
        if (fk == NULL) {
            printw("\t\t\tCan't open file\n");
        } else {
            fprintf(fk, "first_name:%s last_name: %s id: %li age:%d adress:%s email:%s\n", stu.first_name, stu.last_name, stu.id, stu.age, stu.adresse, stu.email);
            fclose(fk);
        }

        printw("\t\t\tDo you want to add another student? (y/n): ");
        scanw(" %c", &another);
    } while (another == 'y');

    endwin();
}



void search_st() {
    clear();
    char first[50];
    char last[50];
    student stu;
    int isfound = 0;
    printw("Enter the name of the student for search: ");
    scanw("%s %s", first, last);
    refresh();

    FILE* fk;
    fk = fopen("database/record.txt", "r");
    char line[256];
    while (fgets(line, sizeof(line), fk) != NULL) {
        sscanf(line, "first_name:%s last_name: %s id: %li age:%d adress:%s email:%s\n", stu.first_name, stu.last_name, &stu.id, &stu.age, stu.adresse, stu.email);;
        if (strcmp(first, stu.first_name) == 0 && strcmp(last, stu.last_name) == 0) {
            isfound = 1;
            break;
        }
    }

    if (isfound == 1) {
        printw("\t===================================the record=============================================\n");
        printw("\n\t\t\tId: %li", stu.id);
        printw("\n\t\t\tFirst Name: %s", stu.first_name);
        printw("\n\t\t\tLast Name: %s", stu.last_name);
        printw("\n\t\t\tAge: %d", stu.age);
        printw("\n\t\t\tAdresse: %s", stu.adresse);
        printw("\n\t\t\tEmail: %s", stu.email);
        printw("\n");
        printw("\n");

        printw("\t======================================== press any key to return =====================================");
    } else {
        printw("Sorry, no record found.");
    }

    fclose(fk);
    refresh();
    getch();
}



void Record() {
    clear();
    FILE* fk;
    //student stu;
    char bn[1000];
    printw("\t\t\t\t=================================== Record===================================\n\n\n");
    fk = fopen("database/record.txt", "r");

    if (fk == NULL) {
        printw("\t\t\tcan't open file");
    } else {
        printw("\t\t\t records:\n");
    }
   

while (fgets(bn, sizeof(bn),fk)) {
    printw("\n\t %s ",bn);
    
}

    fclose(fk);
    getch();
}
void dellet_stu() {
    clear();
    printw("==================================================delete record====================================================\n");
    char first[50];
    char last[50]; 
    student stu;
    int isfound = 0;
    printw("enter the name of student : ");
    refresh();
    scanw("%s %s", first, last);
    FILE* fk, * tempe;
    fk = fopen("database/record.txt", "r");
    tempe = fopen("tempe.txt", "w");

    
    char line[256];
    while (fgets(line, sizeof(line), fk)) {
        sscanf(line, "first_name:%s last_name: %s id: %li age:%d adress:%s email:%s\n", stu.first_name, stu.last_name, &stu.id, &stu.age, stu.adresse, stu.email);
        if (strcmp(first, stu.first_name) == 0 && strcmp(last, stu.last_name) == 0) {
            isfound = 1;
        } else {
            fprintf(tempe, "first_name:%s last_name: %s id: %li age:%d adress:%s email:%s\n", stu.first_name, stu.last_name, stu.id, stu.age, stu.adresse, stu.email);
        }
    }
    fclose(fk);
    fclose(tempe);
    printw("===================================================================================================================\n");
    if (isfound == 1) {
        fk = fopen("database/record.txt", "w");
        tempe = fopen("tempe.txt", "r");

        if (fk == NULL || tempe == NULL) {
            printw("Error opening file.\n");
            fclose(fk);
            fclose(tempe);
            return;
        }

        while (fgets(line, sizeof(line), tempe)) {
            sscanf(line, "first_name:%s last_name: %s id: %li age:%d adress:%s email:%s\n", stu.first_name, stu.last_name, &stu.id, &stu.age, stu.adresse, stu.email);
            fprintf(fk, "first_name:%s last_name: %s id: %li age:%d adress:%s email:%s\n", stu.first_name, stu.last_name, stu.id, stu.age, stu.adresse, stu.email);
        }

        fclose(fk);
        fclose(tempe);
        printw("the record is delete\n");
    } else {
        printw("the record is not delete\n");
    }
    printw("=====================================================================================================================");
    getch();
}

void mod_student() {
    clear();
    char first[50];
    char last[50];
    int isfound = 0;
    student stu;
    FILE* fk, * fk1;
    fk = fopen("database/record.txt", "r");
    fk1 = fopen("kkkk.txt", "w");
    printw("Enter the name for update:\n");
    refresh();
    scanw("%s %s", first, last);
    printw("=============================================================================================================");

    char line[256];
    while (fgets(line, sizeof(line), fk) != NULL) {
       sscanf(line, "first_name:%s last_name: %s id: %li age:%d adress:%s email:%s\n", stu.first_name, stu.last_name, &stu.id, &stu.age, stu.adresse, stu.email);
        if (strcmp(first, stu.first_name)== 0 && strcmp(last, stu.last_name)== 0) {
            
            printw("\n\t\t\tNew first name: ");
            scanw("%s", stu.first_name);
            printw("\n\t\t\tNew last name: ");
            scanw("%s", stu.last_name);
            printw("\n\t\t\tNew ID: ");
            scanw("%li", &stu.id);
            printw("\n\t\t\tNew age: ");
            scanw("%d", &stu.age);
            printw("\n\t\t\tNew address: ");
            scanw("%s", stu.adresse);
            printw("\n\t\t\tNew Email: ");
            scanw("%s", stu.email);
            
            isfound = 1;
            
        }
         fprintf(fk1,"first_name:%s last_name: %s id: %li age:%d adress:%s email:%s\n", stu.first_name, stu.last_name, stu.id, stu.age, stu.adresse, stu.email);
    }

    printw("\n");
    printw("\n");
    printw("========================================= Press any key to return ============================================");
    fclose(fk);
    fclose(fk1);

    if (isfound==1) {
        fk1 = fopen("kkkk.txt", "r");
        fk = fopen("database/record.txt", "w");

        while (fgets(line, sizeof(line), fk1) != NULL) {
            sscanf(line,"first_name:%s last_name: %s id: %li age:%d adress:%s email:%s\n", stu.first_name, stu.last_name, &stu.id, &stu.age, stu.adresse, stu.email);
            fprintf(fk, "first_name:%s last_name: %s id: %li age:%d adress:%s email:%s\n", stu.first_name, stu.last_name, stu.id, stu.age, stu.adresse, stu.email);
        }

        fclose(fk);
        fclose(fk1);
    } else {
        printw("\nNo record found!");
    }

    getch();
}


void calculate_the_average() {
    clear();
    printw("===============================================calculer moyenne================================================\n\n");
    char first[100];
    char last[100];
    int nb_modules;
    student stu;
    printw("Entrez le nom de l'etudiant : ");
    scanw("%s %s", first, last);
    printw("================================================================================================================\n\n");

    printw("==================================================================================================================\n");

    module moyenne;
    FILE* fk;
    fk = fopen("database/record.txt", "r");

    FILE* fk2;
    fk2 = fopen("tek.txt", "a");
    int isfound = 0;

    if (fk2 == NULL) {
        printw("Erreur lors de l'ouverture du fichier.\n");
        fclose(fk);
        fclose(fk2);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fk) != NULL) {
        sscanf(line, "first_name:%s last_name: %s id: %li age:%d adress:%s email:%s\n", stu.first_name, stu.last_name, &stu.id, &stu.age, stu.adresse, stu.email);
        if (strcmp(first, stu.first_name) == 0 && strcmp(last, stu.last_name) == 0) {
            isfound = 1;
            break;
        }
    }


    if (isfound == 1) {
        printw("Entrez le nombre de modules : ");
        refresh();
        scanw("%d", &nb_modules);

        for (int i = 0; i < nb_modules; i++) {
            printw("Entrez le nom du module : ");
            refresh();
            scanw("%s", moyenne.nom_module);

            printw("Entrez le coefficient du module : ");
            refresh();
            scanw("%f", &moyenne.coefficient);

            printw("Entrez la note de l'etudiant pour ce module : ");
            refresh();
            scanw("%f", &moyenne.note);

            fprintf(fk2, "Module : %s, Coefficient : %.2f, Note : %.2f\n", moyenne.nom_module, moyenne.coefficient, moyenne.note);
        }

        float total_points = 0;
        float total_coefficients = 0;

        for (int i = 0; i < nb_modules; i++) {
            total_points += moyenne.coefficient * moyenne.note;
            total_coefficients += moyenne.coefficient;
        }

        float moyenne = total_points / total_coefficients;

        fprintf(fk2, "Moyenne : %.2f\n\n", moyenne);

        printw("\n\n=======================================================================================================");
        printw("\nLa moyenne de l'etudiant %s est : %.2f\n", first, moyenne);
    } else {
        printw("no work!");
    }

    fclose(fk);
    fclose(fk2);
    printw("\n======================================press any key to returne=================================================");
    getch();
}





int main(){ 
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    
    noecho();
    cbreak();
    echo();
    curs_set(0);

    int p = 0;
    int ch;

    cpu();
    loading();
    do {
        ch = selection(p);

        switch (ch) {
            case 0:
                
                add_student();
                break;

            case 1:
            
                Record();
                break;

            case 2:
                search_st();
                break;

            case 3:
                mod_student();
                break;

            case 4:
                dellet_stu();
                break;
            case 5:
                calculate_the_average();
              break;  
        }


        p = ch;
    } while (ch != 6);

    endwin();
    return 0;
}
