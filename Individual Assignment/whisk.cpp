#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=================HomePage=====================

struct ingredients {
    char ing [100];
    ingredients *next;
};

ingredients *createIng (const char ing[]){
    ingredients *newIng = (ingredients*) malloc (sizeof (ingredients));
    strcpy (newIng->ing, ing);
    newIng->next = NULL;
    return newIng;
}

struct instruction {
    char step [1000];
    ingredients *headIng, *tailIng;
    instruction *next;
    instruction *prev;
};

instruction *createInstruction (const char step[]){
    instruction *newStep = (instruction*) malloc (sizeof(instruction));
    strcpy (newStep->step, step);
    newStep->next = newStep->prev = NULL;
    newStep->headIng = newStep->tailIng = NULL;
    return newStep;
}

struct recipe{
    char foodName [100];
    instruction *headStep, *tailStep;
    ingredients *headIng, *tailIng;
    recipe *next;
    recipe *nextSelected;
} *head, *tail, *selectedHead, *selectedTail, *searchHead, *searchTail;

recipe *createRecipe (const char foodName[]){
    recipe *newR = (recipe*) malloc (sizeof(recipe));
    strcpy (newR->foodName , foodName);
    newR->headIng = newR->tailIng = NULL;
    newR->headStep = newR->headStep = NULL;
    newR -> next = NULL;
    newR -> nextSelected = NULL;
    return newR;
}

void pushRecipe (const char foodName[]){
    recipe *temp = createRecipe (foodName);

    if (!head){
        head= tail = temp;
    }
    else { 
        tail->next = temp;
        tail =  temp;
    }
}

void pushIngredients (const char foodName[],const char step[], const char ing[]){
    recipe *curr = head;
    while (curr){
        if (strcmp (foodName, curr->foodName)==0){
            break;
        }
        curr = curr->next;
    }
    ingredients *newIng = createIng (ing);
    if (!curr->headIng){
        curr->headIng = curr->tailIng = newIng;
    }
    else {
        curr->tailIng->next = newIng;
        curr->tailIng = newIng; 
    }

    ingredients *newIng2 = createIng (ing);
    instruction *curr2 = curr->headStep;
    while (curr2){
        if (strcmp(curr2->step, step)==0){
            break;
        }
        curr2= curr2->next;
    }
    if (!curr2->headIng){
        curr2->headIng = curr2->tailIng = newIng2;
    }
    else {
        curr2->tailIng->next = newIng2;
        curr2->tailIng = newIng2;
    }
}

void pushStep (const char foodName[], const char step[]){
    recipe *curr = head;
    while (curr){
        if (strcmp (foodName, curr->foodName)==0){
            break;
        }
        curr = curr->next;
    }
    instruction *newStep = createInstruction (step);
    if (!curr->headStep){
        curr->headStep = curr->tailStep = newStep;
    }
    else {
        curr->tailStep->next = newStep;
        newStep->prev = curr->tailStep;
        curr->tailStep = newStep; 
    }
}

void printAllStep (const char name[]){
    recipe *curr = head;
    while (curr){
        if (strcmp (curr->foodName, name)==0){
            printf ("How To Cook %s:\n", name);
            break;
        }
        curr= curr->next;
    }
    instruction *curr1 = curr->headStep;
    int idx=1;
    while (curr1){
        printf ("%d. %s\n", idx, curr1->step);
        ingredients *temp = curr1->headIng;
        printf ("  Ingredients:\n");
        int idx2=1;
        while (temp){
            printf ("  %d. %s\n", idx2, temp->ing);
            idx2++;
            temp = temp->next;
        }
        idx++;
        curr1= curr1->next;
    }
}

void selectRecipe (const char foodName[]){
    recipe *curr= head;
    while (curr){
        if (strcmp (curr->foodName, foodName)==0){
            break;
        }
        curr= curr->next;
    }

    if (!selectedHead){
        selectedHead = selectedTail = curr;
    }
    else {
        selectedTail->nextSelected = curr;
        selectedTail = curr;
    }
}

void printAllSelectedRecipes (){
    recipe *curr = selectedHead;
    printf ("\nYour Selected Recipes:\n");
    int idx=1;
    while (curr){
        printf ("%d. %s\n", idx, curr->foodName);
        idx++;
        curr = curr->nextSelected;
    }
}

void printAllIngredients (recipe *curr){
    printf ("\nIngredients of %s:\n", curr->foodName);
    int count =1;
    ingredients *temp = curr->headIng;
    while (temp){
        printf ("%d. %s\n", count, temp->ing);
        count++;
        temp = temp->next;
    }
    puts ("");
}

void startCooking (recipe *curr){
    int idx = 1;
    instruction *temp = curr->headStep;

    instruction *count = curr->headStep;
    int totalstep=0;
    while (count){
        totalstep++;
        count = count->next;
    }

    while (temp){
        printf ("        %s\n", curr->foodName);
        printf ("        ");
        for (int i=0; i<totalstep; i++){
            printf("-");
        }
        printf ("\n        ");
        for (int i=0; i<idx; i++){
            printf("O");
        }
        printf ("\n        ");
        for (int i=0; i<totalstep; i++){
            printf("-");
        }
        puts("");

        printf ("Step %d        ? 5 min\n", idx);
        printf ("%s\n", temp->step);
        printf ("\nIngredients:\n");
        int num =1;
        ingredients *tamp = temp->headIng;
        while (tamp){
            printf ("%d. %s\n", num, tamp->ing);
            num++;
            tamp = tamp->next;
        }
        printf ("\n< or >\n= ");
        char key;
        scanf ("%c", &key);getchar ();

        if (key == '<'){
            if (temp->prev!= NULL){
                temp = temp->prev;
                idx--;
                system("clear");
            }
            else {
                system("clear");
            }
        }
        else if (key == '>'){
            if (temp->next != NULL){
                temp = temp->next;
                idx++;
                system("clear");
            }
            else {
                system("clear");
                printf ("\nDonee!!! Enjoy Your Food!!????\n\n");
                break;
            }
        }
        
    }
}

void printFiltered (){
    recipe *curr = searchHead;
    printf ("\nYour Filtered Recipes:\n");
    int idx=1;
    while (curr){
        printf ("%d. %s\n", idx, curr->foodName);
        idx++;
        curr = curr->nextSelected;
    }
}

void filterSearch(const char keyword[]){
  recipe *curr = head;
  int len = strlen(keyword);
  int i = 1;
  while(curr){
    if(strncmp(curr->foodName,keyword,len) == 0){
      printf("%d. %s\n",i,curr->foodName);
      i++;

      if(!searchHead){
        searchHead = searchTail = curr;
      }else{
        searchTail->nextSelected = curr;
        searchTail = curr;
      }
    }
    curr = curr->next;
  }
}

int homePage (){
    // DUMMY
        // recipe 1
    pushRecipe ("Nasi Goreng");
    pushStep ("Nasi Goreng", "Buatlah Nasi Putih");
    pushStep ("Nasi Goreng", "Halus kan bawang putih, merah, dan cabe");
    pushStep ("Nasi Goreng", "Goreng Telur Orak arik");
    pushStep ("Nasi Goreng", "Tumis bumbu dan masukkan ayam cincang, telur, dan daun bawang");
    pushStep ("Nasi Goreng", "Tambahkan kecap, garam dan merica");
    pushStep ("Nasi Goreng", "Masukkan nasi dan aduk hingga rata");
    pushIngredients ("Nasi Goreng", "Buatlah Nasi Putih", "Nasi");
    pushIngredients ("Nasi Goreng", "Halus kan bawang putih, merah, dan cabe", "bawang merah dan putih");
    pushIngredients ("Nasi Goreng", "Halus kan bawang putih, merah, dan cabe", "cabe");
    pushIngredients ("Nasi Goreng", "Goreng Telur Orak arik", "Telur");
    pushIngredients ("Nasi Goreng", "Tumis bumbu dan masukkan ayam cincang, telur, dan daun bawang", "ayam cincang");
    pushIngredients ("Nasi Goreng", "Tumis bumbu dan masukkan ayam cincang, telur, dan daun bawang", "daun bawang");
    pushIngredients ("Nasi Goreng", "Tambahkan kecap, garam dan merica", "kecap");
    pushIngredients ("Nasi Goreng", "Tambahkan kecap, garam dan merica", "garam");
    pushIngredients ("Nasi Goreng", "Tambahkan kecap, garam dan merica", "merica");
    pushIngredients ("Nasi Goreng", "Masukkan nasi dan aduk hingga rata", "minyak");
    
        // recipe 2
    pushRecipe ("Rendang Sapi");
        // recipe 3
    pushRecipe ("Telor dadar");
    pushStep ("Telor dadar", "masukkan telor mentah kedalam gelas");
    pushStep ("Telor dadar", "masukkan garam");
    pushStep ("Telor dadar", "siapkan panci dan sedikit minyak");
    pushStep ("Telor dadar", "tuangkan telor yang sudah diaduk");
    pushStep ("Telor dadar", "jangan lupa di balik, tunggu sampai jadi, tambahkan saos");
    pushIngredients ("Telor dadar", "masukkan telor mentah kedalam gelas", "Telor mentah");
    pushIngredients ("Telor dadar", "masukkan garam", "garam");
    pushIngredients ("Telor dadar", "siapkan panci dan sedikit minyak", "minyak goreng");
    pushIngredients ("Telor dadar", "jangan lupa di balik, tunggu sampai jadi, tambahkan saos", "saos sambal");
        // recipe 4
    pushRecipe ("Ramen Special");
        // recipe 5
    pushRecipe ("Indomie Goreng Original");
    pushStep ("Indomie Goreng Original", "siapkan panci dan air");
    pushStep ("Indomie Goreng Original", "tunggu sampai air mendidih");
    pushStep ("Indomie Goreng Original", "masukkan mie instan, tunggu sampai mendidih");
    pushStep ("Indomie Goreng Original", "buka bumbu nya dan taruh di piring");
    pushStep ("Indomie Goreng Original", "tuang mie yang sudah mendidih ke piring");
    pushStep ("Indomie Goreng Original", "aduk sampai rata");
    pushIngredients ("Indomie Goreng Original", "siapkan panci dan air", "Air");
    pushIngredients ("Indomie Goreng Original", "tunggu sampai air mendidih", "Kompor Gas");
    pushIngredients ("Indomie Goreng Original", "masukkan mie instan, tunggu sampai mendidih", "Mie instan");
    pushIngredients ("Indomie Goreng Original", "buka bumbu nya dan taruh di piring", "bumbu- bumbu mie instan");
        // DIATAS ADALAH DUMMY UNTUK SEMUA RESEP


    // DUMMY UNTUK RESEP YANG SUDAH DI SELECT
    selectRecipe ("Nasi Goreng");
    selectRecipe ("Telor dadar");
    selectRecipe ("Indomie Goreng Original");


    // FUNCTION NYA KITCHEN START DARI SINI
    bool onApps = true;
    while (onApps){
        printf ("????----------------------????\n");
        printf ("|          HomePage           |\n");
        printf ("????---------------------????\n\n");
        puts ("[1] Recipe Suggestions");
        puts ("[2] Search");
        puts ("[3] Exit");

        int x;
        printf (">> ");
        scanf ("%d", &x);getchar ();
        if (x==1){
            printAllSelectedRecipes ();
            printf ("\nView Recipe?[0 to exit]\n>> ");
            int idx;
            scanf ("%d", &idx); getchar ();
            system("clear");
            printf ("\n");
            while (idx > 0){
                recipe *temp = selectedHead;
                int idx2= idx;
                while (idx2>1){
                    temp = temp->nextSelected;
                    idx2--;
                }
                printAllStep (temp->foodName);
                
                printAllSelectedRecipes ();
                printf ("\nView Recipe?[0 to exit]\n>> ");
                scanf ("%d", &idx); getchar ();
                system("clear");
                printf ("\n");
            }
        }else if(x == 2){
          printf("Input your search key:");
          char searchKey[255];
          scanf("%s",searchKey);
          filterSearch(searchKey);
          printf("%s\n",searchKey);
          printFiltered();

          printf ("\nView Recipe?[0 to exit]\n>> ");
            int idx;
            scanf ("%d", &idx); getchar ();
            system("clear");
            printf ("\n");
            while (idx > 0){
                recipe *temp = searchHead;
                int idx2= idx;
                while (idx2>1){
                    temp = temp->nextSelected;
                    idx2--;
                }
                printAllStep (temp->foodName);
                
                printFiltered();
                printf ("\nView Recipe?[0 to exit]\n>> ");
                scanf ("%d", &idx); getchar ();
                system("clear");
                printf ("\n");
            }
          
        }
        else if (x==3){
            printf("Thank You, enjoy your food????\n");
            onApps = false;
        }
    }

    
    return 0;
}
//=================Cookbook=====================
void printRecipe(){
  int i = 1;
  recipe *curr = head;
  printf ("\nAll of your Recipes:\n");
  while(curr){
    printf("[%d] %s\n",i,curr->foodName);
    i++;
    curr = curr->next;
  }
}
int cookBook (){
    // DUMMY
        // recipe 1
    pushRecipe ("Nasi Goreng");
    pushStep ("Nasi Goreng", "Buatlah Nasi Putih");
    pushStep ("Nasi Goreng", "Halus kan bawang putih, merah, dan cabe");
    pushStep ("Nasi Goreng", "Goreng Telur Orak arik");
    pushStep ("Nasi Goreng", "Tumis bumbu dan masukkan ayam cincang, telur, dan daun bawang");
    pushStep ("Nasi Goreng", "Tambahkan kecap, garam dan merica");
    pushStep ("Nasi Goreng", "Masukkan nasi dan aduk hingga rata");
    pushIngredients ("Nasi Goreng", "Buatlah Nasi Putih", "Nasi");
    pushIngredients ("Nasi Goreng", "Halus kan bawang putih, merah, dan cabe", "bawang merah dan putih");
    pushIngredients ("Nasi Goreng", "Halus kan bawang putih, merah, dan cabe", "cabe");
    pushIngredients ("Nasi Goreng", "Goreng Telur Orak arik", "Telur");
    pushIngredients ("Nasi Goreng", "Tumis bumbu dan masukkan ayam cincang, telur, dan daun bawang", "ayam cincang");
    pushIngredients ("Nasi Goreng", "Tumis bumbu dan masukkan ayam cincang, telur, dan daun bawang", "daun bawang");
    pushIngredients ("Nasi Goreng", "Tambahkan kecap, garam dan merica", "kecap");
    pushIngredients ("Nasi Goreng", "Tambahkan kecap, garam dan merica", "garam");
    pushIngredients ("Nasi Goreng", "Tambahkan kecap, garam dan merica", "merica");
    pushIngredients ("Nasi Goreng", "Masukkan nasi dan aduk hingga rata", "minyak");
    
        // recipe 2
    pushRecipe ("Rendang Sapi");
        // recipe 3
    pushRecipe ("Telor dadar");
    pushStep ("Telor dadar", "masukkan telor mentah kedalam gelas");
    pushStep ("Telor dadar", "masukkan garam");
    pushStep ("Telor dadar", "siapkan panci dan sedikit minyak");
    pushStep ("Telor dadar", "tuangkan telor yang sudah diaduk");
    pushStep ("Telor dadar", "jangan lupa di balik, tunggu sampai jadi, tambahkan saos");
    pushIngredients ("Telor dadar", "masukkan telor mentah kedalam gelas", "Telor mentah");
    pushIngredients ("Telor dadar", "masukkan garam", "garam");
    pushIngredients ("Telor dadar", "siapkan panci dan sedikit minyak", "minyak goreng");
    pushIngredients ("Telor dadar", "jangan lupa di balik, tunggu sampai jadi, tambahkan saos", "saos sambal");
        // recipe 4
    pushRecipe ("Ramen Special");
        // recipe 5
    pushRecipe ("Indomie Goreng Original");
    pushStep ("Indomie Goreng Original", "siapkan panci dan air");
    pushStep ("Indomie Goreng Original", "tunggu sampai air mendidih");
    pushStep ("Indomie Goreng Original", "masukkan mie instan, tunggu sampai mendidih");
    pushStep ("Indomie Goreng Original", "buka bumbu nya dan taruh di piring");
    pushStep ("Indomie Goreng Original", "tuang mie yang sudah mendidih ke piring");
    pushStep ("Indomie Goreng Original", "aduk sampai rata");
    pushIngredients ("Indomie Goreng Original", "siapkan panci dan air", "Air");
    pushIngredients ("Indomie Goreng Original", "tunggu sampai air mendidih", "Kompor Gas");
    pushIngredients ("Indomie Goreng Original", "masukkan mie instan, tunggu sampai mendidih", "Mie instan");
    pushIngredients ("Indomie Goreng Original", "buka bumbu nya dan taruh di piring", "bumbu- bumbu mie instan");
        // DIATAS ADALAH DUMMY UNTUK SEMUA RESEP


    // DUMMY UNTUK RESEP YANG SUDAH DI SELECT
    selectRecipe ("Nasi Goreng");
    selectRecipe ("Telor dadar");
    selectRecipe ("Indomie Goreng Original");


    // FUNCTION NYA KITCHEN START DARI SINI
    bool onApps = true;
    while (onApps){
        printf ("????----------------------????\n");
        printf ("|          Cookbook           |\n");
        printf ("????---------------------????\n\n");
        puts ("[1] Saved Recipes");
        puts ("[2] Search");
        puts ("[3] Exit");

        int x;
        printf (">> ");
        scanf ("%d", &x);getchar ();
        if (x==1){
            printRecipe();
            printf ("\nView Recipe?[0 to exit]\n>> ");
            int idx;
            scanf ("%d", &idx); getchar ();
            system("clear");
            printf ("\n");
            while (idx > 0){
                recipe *temp = selectedHead;
                int idx2= idx;
                while (idx2>1){
                    temp = temp->nextSelected;
                    idx2--;
                }
                printAllStep (temp->foodName);
                
                printRecipe();
                printf ("\nView Recipe?[0 to exit]\n>> ");
                scanf ("%d", &idx); getchar ();
                system("clear");
                printf ("\n");
            }
        }else if(x == 2){
          printf("Input your search key:");
          char searchKey[255];
          scanf("%s",searchKey);
          filterSearch(searchKey);
          printf("%s\n",searchKey);
          printFiltered();

          printf ("\nView Recipe?[0 to exit]\n>> ");
            int idx;
            scanf ("%d", &idx); getchar ();
            system("clear");
            printf ("\n");
            while (idx > 0){
                recipe *temp = searchHead;
                int idx2= idx;
                while (idx2>1){
                    temp = temp->nextSelected;
                    idx2--;
                }
                printAllStep (temp->foodName);
                
                printFiltered();
                printf ("\nView Recipe?[0 to exit]\n>> ");
                scanf ("%d", &idx); getchar ();
                system("clear");
                printf ("\n");
            }
          
        }
        else if (x==3){
            printf("Thank You, enjoy your food????\n");
            onApps = false;
        }
    }

    
    return 0;
}
//=================Kitchen=====================
int kitchen (){
    // DUMMY
        // recipe 1
    pushRecipe ("Nasi Goreng");
    pushStep ("Nasi Goreng", "Buatlah Nasi Putih");
    pushStep ("Nasi Goreng", "Halus kan bawang putih, merah, dan cabe");
    pushStep ("Nasi Goreng", "Goreng Telur Orak arik");
    pushStep ("Nasi Goreng", "Tumis bumbu dan masukkan ayam cincang, telur, dan daun bawang");
    pushStep ("Nasi Goreng", "Tambahkan kecap, garam dan merica");
    pushStep ("Nasi Goreng", "Masukkan nasi dan aduk hingga rata");
    pushIngredients ("Nasi Goreng", "Buatlah Nasi Putih", "Nasi");
    pushIngredients ("Nasi Goreng", "Halus kan bawang putih, merah, dan cabe", "bawang merah dan putih");
    pushIngredients ("Nasi Goreng", "Halus kan bawang putih, merah, dan cabe", "cabe");
    pushIngredients ("Nasi Goreng", "Goreng Telur Orak arik", "Telur");
    pushIngredients ("Nasi Goreng", "Tumis bumbu dan masukkan ayam cincang, telur, dan daun bawang", "ayam cincang");
    pushIngredients ("Nasi Goreng", "Tumis bumbu dan masukkan ayam cincang, telur, dan daun bawang", "daun bawang");
    pushIngredients ("Nasi Goreng", "Tambahkan kecap, garam dan merica", "kecap");
    pushIngredients ("Nasi Goreng", "Tambahkan kecap, garam dan merica", "garam");
    pushIngredients ("Nasi Goreng", "Tambahkan kecap, garam dan merica", "merica");
    pushIngredients ("Nasi Goreng", "Masukkan nasi dan aduk hingga rata", "minyak");
    
        // recipe 2
    pushRecipe ("Rendang Sapi");
        // recipe 3
    pushRecipe ("Telor dadar");
    pushStep ("Telor dadar", "masukkan telor mentah kedalam gelas");
    pushStep ("Telor dadar", "masukkan garam");
    pushStep ("Telor dadar", "siapkan panci dan sedikit minyak");
    pushStep ("Telor dadar", "tuangkan telor yang sudah diaduk");
    pushStep ("Telor dadar", "jangan lupa di balik, tunggu sampai jadi, tambahkan saos");
    pushIngredients ("Telor dadar", "masukkan telor mentah kedalam gelas", "Telor mentah");
    pushIngredients ("Telor dadar", "masukkan garam", "garam");
    pushIngredients ("Telor dadar", "siapkan panci dan sedikit minyak", "minyak goreng");
    pushIngredients ("Telor dadar", "jangan lupa di balik, tunggu sampai jadi, tambahkan saos", "saos sambal");
        // recipe 4
    pushRecipe ("Ramen Special");
        // recipe 5
    pushRecipe ("Indomie Goreng Original");
    pushStep ("Indomie Goreng Original", "siapkan panci dan air");
    pushStep ("Indomie Goreng Original", "tunggu sampai air mendidih");
    pushStep ("Indomie Goreng Original", "masukkan mie instan, tunggu sampai mendidih");
    pushStep ("Indomie Goreng Original", "buka bumbu nya dan taruh di piring");
    pushStep ("Indomie Goreng Original", "tuang mie yang sudah mendidih ke piring");
    pushStep ("Indomie Goreng Original", "aduk sampai rata");
    pushIngredients ("Indomie Goreng Original", "siapkan panci dan air", "Air");
    pushIngredients ("Indomie Goreng Original", "tunggu sampai air mendidih", "Kompor Gas");
    pushIngredients ("Indomie Goreng Original", "masukkan mie instan, tunggu sampai mendidih", "Mie instan");
    pushIngredients ("Indomie Goreng Original", "buka bumbu nya dan taruh di piring", "bumbu- bumbu mie instan");
        // DIATAS ADALAH DUMMY UNTUK SEMUA RESEP


    // DUMMY UNTUK RESEP YANG SUDAH DI SELECT
    selectRecipe ("Nasi Goreng");
    selectRecipe ("Telor dadar");
    selectRecipe ("Indomie Goreng Original");


    // FUNCTION NYA KITCHEN START DARI SINI
    bool onApps = true;
    while (onApps){
        printf ("????----------------------????\n");
        printf ("|          KITCHEN           |\n");
        printf ("????---------------------????\n\n");
        puts ("[1] View Selected Recipes");
        puts ("[2] View Ingredients List");
        puts ("[3] Start Cooking");
        puts ("[4] Exit");

        int x;
        printf (">> ");
        scanf ("%d", &x);getchar ();
        if (x==1){
            printAllSelectedRecipes ();
            printf ("\nView Recipe?[0 to exit]\n>> ");
            int idx;
            scanf ("%d", &idx); getchar ();
            system("clear");
            printf ("\n");
            while (idx > 0){
                recipe *temp = selectedHead;
                int idx2= idx;
                while (idx2>1){
                    temp = temp->nextSelected;
                    idx2--;
                }
                printAllStep (temp->foodName);
                
                printAllSelectedRecipes ();
                printf ("\nView Recipe?[0 to exit]\n>> ");
                scanf ("%d", &idx); getchar ();
                system("clear");
                printf ("\n");
            }
        }
        else if (x==2){
            printAllSelectedRecipes ();
            printf("\nView Ingredients? [0 to exit]\n>> ");
            int idx;
            scanf ("%d", &idx); getchar ();
            system("clear");
            while (idx>0){
                recipe *temp = selectedHead;
                int idx2= idx;
                while (idx2>1){
                    temp = temp->nextSelected;
                    idx2--;
                }
                printAllIngredients (temp);
                printAllSelectedRecipes ();
                printf("\nView Ingredients? [0 to exit]\n>> ");
                scanf ("%d", &idx); getchar ();
                system("clear");
            }
        }
        else if (x==3){
            printAllSelectedRecipes ();
            printf ("\nWhich food do you want to cook?[1..n]\n>> ");
            int idx;
            scanf("%d", &idx); getchar ();
            system("clear");
            printf ("\n");

            recipe *temp = selectedHead;
            while (idx>1){
                temp = temp->nextSelected;
                idx--;
            }
            startCooking (temp);
        }
        else if (x==4){
            printf("Thank You, enjoy your food????\n");
            onApps = false;
        }
    }

    
    return 0;
}
//=================Pantry=====================
struct Contain {
  int qty;
  char nama[255];
  int exp;
  char jenis[255];
  Contain *next, *prev;
};

struct Group {
  char grup[255];
  Contain *head_contain, *tail_contain;
  Group *next;
}*head_group, *tail_group;



Group *createGroup(const char *nama){
  Group *temp = (Group*)malloc(sizeof(Group));
  strcpy(temp->grup, nama);
  temp->next = NULL;
  temp->head_contain =temp->tail_contain = NULL;
  return temp;
};

Contain *createIsi(const char *nama, const char *jenis, int qty, int exp) {
  Contain *temp = (Contain*)malloc(sizeof(Contain));
  strcpy(temp->nama, nama);
  strcpy(temp->jenis, jenis);
  temp->qty = qty;
  temp->exp = exp;
  temp->next =temp->prev =  NULL;

  return temp;
};


void pushGroup(const char *nama) {
  Group *temp = createGroup(nama);
  if(!head_group) {
    head_group = tail_group = temp;
  }else {
    tail_group->next = temp;
    tail_group = temp;
  }
}

void pushIsi(Group *root, const char *nama, const char *jenis, int qty, int exp) {
  Contain *temp = createIsi(nama, jenis, qty, exp);
  if(!root->head_contain) {
    root->head_contain = root->tail_contain = temp;
  } else if(strcmp(nama, root->head_contain->nama ) <0){
    temp->next = root->head_contain;
    root->head_contain->prev = temp;
    root->head_contain = temp;
  }else if(strcmp(nama, root->head_contain->nama )>0){
    temp->prev = root->tail_contain;
    root->tail_contain->next = temp;
    root->tail_contain = temp;
  }else {
    Contain *curr = root->head_contain;
    while(strcmp(nama, curr->nama) > 0){
      curr = curr->next;
    }
    temp->prev = curr->prev;
    temp->next = curr;
    temp->prev->next = temp;
    curr->prev = temp;
  }
}

Group *cariRoot(const char *name) {
  Group *curr = head_group;
  while(curr){
    if(strcmp(curr->grup, name) == 0){
      break;
    }
    curr = curr->next;
  }

  return curr;
}

void popHead_isi(Group *root) {
  if(!root->head_contain){
    return;
  }else if(root->head_contain == root->tail_contain){
    root->head_contain = root->tail_contain = NULL;
  }else {
    Contain *temp = root->head_contain->next; // buat angka setelah head itu temp;
    root->head_contain->next = temp->prev = NULL; // jadi NULL < 18 > N || NULL
    root->head_contain = NULL;
    free(root->head_contain);
    root->head_contain = temp;
  }
}

void popTail_isi(Group *root){
  if(!root->head_contain){
    return;
  }else if(root->head_contain == root->tail_contain){
    root->head_contain = root->tail_contain = NULL;
    free(root->head_contain);
  }else {
    Contain *temp = root->tail_contain->prev; // buat angka sebelum tail itu temp
    root->tail_contain->prev = temp->next = NULL; // tail kanan, temp kiri = NULL, putus hubungan
    root->tail_contain = NULL; // tail dijadikan null
    free(root->tail_contain); // free tail
    root->tail_contain = temp;
  }
}


void removeIsi(Group *root, const char *name) {
  if(!root->head_contain){
    return;
  }else if(strcmp(name, root->head_contain->nama) == 0){
    popHead_isi(root);
  }else if(strcmp(name, root->tail_contain->nama) == 0){
    popTail_isi(root);
  }else {
    Contain *curr = root->head_contain;
    while(curr != NULL && strcmp(name, curr->nama) !=0) {
      curr = curr->next;
    }

    if(!curr){
      puts("The item you wish to delete is not present at the moment");
      return;
    }

    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    curr->next = curr->prev = NULL;
    curr = NULL;
    free(curr);
  }
} 

void addRemoveList() {
  puts("Would you like to add or remove your list?");
  printf("1. Add\n2. Remove\n3. Exit\n");
  printf("Please input your choice:");
  int scan = 0;
  scanf("%d", &scan);
  if(scan == 1) {
    
    // cari group
    Group *node = NULL;
    do{
      printf("Please input group name:");      
      char group[255] = "";
      getchar();
      scanf("%[^\n]", group);
      Group *nod = cariRoot(group);
      node = nod;
    }while(!node);
  
  
    // input name
    printf("Please input item name:");
    char asing[255] = "";
    getchar();
    scanf("%[^\n]", asing);

    //cari qty
    printf("Please input item qty:");
    int qty = 0;
    scanf("%d", &qty);

    // cari jenis
    printf("1. gal.\n2. oz.\n3. tbs.\n4. pcs.\n");
    printf("Please input item type:");
    int scan2 = 0;
    scanf("%d", &scan2);

   char type[255] = "";
    if(scan2 == 1){
      strcpy(type, "gal.");
    }else if(scan2 == 2) {
      strcpy(type, "oz.");
    }else if(scan2 == 3) {
      strcpy(type, "tbs.");
    }else if(scan2 == 4) {
      strcpy(type, "pcs.");
    }else {
      printf("Input invalid, please try again.\n");
      addRemoveList();
    }

    int exp = 0;
    printf("How many days will this item last?\n");
    printf("Input:");
    scanf("%d", &exp);

    pushIsi(node, asing, type, qty, exp);
  }else if(scan == 2) {
    // cari group
    Group *node = NULL;
    do{
      printf("Please input group name you wish to delete:");      
      char asing[255] = "";
      getchar();
      scanf("%[^\n]", asing);
      Group *nod = cariRoot(asing);
      node = nod;
    }while(!node);

    char asing[255] = "";
    printf("Please input item name you wish to delete:");
    getchar();
    scanf("%[^\n]", asing);
    
    removeIsi(node, asing);
  }else if(scan == 3){
    return;
  }else{
    puts("Sorry, your input is invalid");
    addRemoveList();
  }

return;
}


void Pantry() {
  Group *curr = head_group;
  puts("Your Pantry List");
  int z = 1;
  while(curr) {
    printf("%d. %s\n", z, curr->grup);
    puts("------------------------------");
    z++;
    Contain *curr2 = curr->head_contain;
    int j = 1;
      printf("\tNo. Name      Qty  Type (Expire in)\n");    
    while(curr2) {

      printf("\t%d.  %-10s %-3d %-4s %d day(s)",j,  curr2->nama, curr2->qty, curr2->jenis, curr2->exp);
      j++;
      if(curr2->exp <= 7){
        puts("(near expired)");
      }else {
        puts("");
      }
      curr2 = curr2->next;
    }
    puts("=============================");
    curr = curr->next;
  }

  addRemoveList();
  printf("Would you like to continue?\n1. Yes\n2. No\n");
  int a = 0;
  scanf("%d", &a);
  if(a == 1){
    Pantry();
  }else {
    return;
  }
}

int pantry(){
  pushGroup("Dairy");
  pushGroup("Fruits");
  pushGroup("Meats");
  Pantry();
  puts("Thank you for using this app!");
  return 0;
}
//=================Profile=====================
int profile(){
  
  printf ("????----------------------????\n");
  printf ("|          Profile           |\n");
  printf ("????---------------------????\n\n");
  puts("==========OUTPLAY==============");
  puts("Creator:");
  puts(">>Bryan Tamin");
  puts(">>Darnell Kiko");
  puts(">>Lucky Laurens");
  printf("Press any key to go back\n>>");
  getchar();getchar();
  return 0;
}
//=================Main=====================
void printTemplate(){
  printf("========================================\n");
  printf("          Welcome To Whisk\n");
  printf("========================================\n");
  printf("[1] Home Page\n");
  printf("[2] Cookbook\n");
  printf("[3] Kitchen\n");
  printf("[4] Pantry\n");
  printf("[5] Profile\n");
  printf("[0] Exit\n");
  printf("Select Menu\n>>");
}

int main(){
  printTemplate();
  bool isEnd = false;
  while(!isEnd){
    printTemplate();
    int input = 0;
    do{
     scanf("%d",&input);
    }
    while(input < 0 || input > 5);
    if(input == 1)homePage();
    else if(input == 2)cookBook();
    else if(input == 3)kitchen();
    else if(input == 4)pantry();
    else if(input == 5)profile();
    else if(input == 0){
      printf("Thank you for using Whisk...\n");
      return 0;
    }
  }
}
