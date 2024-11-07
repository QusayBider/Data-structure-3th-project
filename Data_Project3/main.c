//Qusay Bider            1220649             se:1
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>

#define max 50

struct AVL_node;
typedef struct AVL_node *AVL_T;
struct AVL_node {
    char word[max];
    int Height;
    int frequency;
    // int balance;
    AVL_T Left;
    AVL_T Right;
};
struct Hash {
    char word[max];
    char state;
    int freq;
};

void loadData();                                  // this function use for a load and print the data from file
char *checkIfItsAlfa(char Word[]);
int getHeight(struct AVL_node *);
int MAX(int x, int y);
AVL_T singleRotateLeft(AVL_T x);
AVL_T singleRotateRight(AVL_T y);
AVL_T doubleRotateLeft(AVL_T);
AVL_T doubleRotateRight(AVL_T);
AVL_T insert(AVL_T t, char *word);
AVL_T find_min(AVL_T T);
AVL_T delete(AVL_T T, char word[], int);
AVL_T find(char *word, AVL_T T);
void printInOrder(AVL_T t);
void creatHash(struct Hash array_hash[]);
void outInOrder(struct Hash array_hash[], AVL_T t);
void insert_to_hash(struct Hash array_hash[], char word[], int freq, int);
int hash(int, int);
int hashi(int, int, int);
int ascii_value(char []);
int search(struct Hash array_hash[], char word[], int);
void Delete_Hash(struct Hash array_hash[], int index, int);
void Rehash(struct Hash array_hash[]);
int get_size_of_rehash();
bool is_prime(int num);
int choiceOfDelete();
void getInOrder(AVL_T t, int);
void Menu();

///////////////////////////////////////////////////////////////////////////////////
int option;                             // this variable use for the inter-value from a user fo menu
int Percentage = 1;                       // this variable use for Notification regarding when the table is full
int countOfUn = 0;                        // this variable use to count the unique word
int countOfMost = 0;                      // this variable use to count the most word has frequent
struct AVL_node *root = NULL;
int size_Rehash;
int size = 1;
struct Hash array_rehash[10000];
struct Hash array_Hash[10000];
int is_rehash = 0;                        // this variable use to know in the function to use hash or rehash array
//////////////////////////////////////////////////////////////////////////////////
int main(void) {
    Menu();
    scanf("%d", &option);
    do {
        switch (option) {
            case 1:
                loadData();
                break;
            case 2: {
                char Inserted_word[max];
                printf("Enter the word\n");
                scanf("%s", Inserted_word);
                char *Insert = checkIfItsAlfa(Inserted_word);
                if (Insert == NULL) {
                    printf("The word not has alphabets\n");
                    break;
                }
                size++;
                root = insert(root, Insert);
                printf(" %s has been inserted\n", Inserted_word);
            }
                break;
            case 3: {
                char Inserted_word[max];
                printf("Enter the word\n");
                scanf("%s", Inserted_word);
                AVL_T Temp = find(Inserted_word, root);
                if (Temp != NULL) {
                    int choice;
                    if (Temp->frequency > 1) {
                        choice = choiceOfDelete();
                        delete(root, Inserted_word, choice);
                    } else {
                        delete(root, Inserted_word, -1);
                    }
                    printf(" %s has been deleted \n", Inserted_word);
                } else {
                    printf("The word not found\n");
                }
            }
                break;
            case 4: {
                if (root == NULL) {
                    printf("The Tree is empty\n");
                } else {
                    printInOrder(root);
                }
            }
                break;
            case 5: {
                creatHash(array_Hash);
                outInOrder(array_Hash, root);
                printf("The hash created\n");
            }
                break;
            case 6: {
                char Inserted_word[max];
                printf("Enter the word\n");
                scanf("%s", Inserted_word);
                if (is_rehash != 1)
                    insert_to_hash(array_Hash, Inserted_word, 1, size);
                else
                    insert_to_hash(array_rehash, Inserted_word, 1, size_Rehash);
                printf(" %s has been inserted\n", Inserted_word);
            }
                break;
            case 7: {
                char Inserted_word[max];
                printf("Enter the word\n");
                scanf("%s", Inserted_word);
                int index;
                if (is_rehash != 1)
                    index = search(array_Hash, Inserted_word, size);
                else
                    index = search(array_rehash, Inserted_word, size_Rehash);

                if (index == -1) {
                    printf("The %s is not found \n", Inserted_word);
                    break;
                } else {
                    int choice = -1;
                    if (is_rehash != 1) {
                        if (array_Hash[index].freq > 1)
                            choice = choiceOfDelete();
                        Delete_Hash(array_Hash, index, choice);
                    } else {
                        if (array_rehash[index].freq > 1)
                            choice = choiceOfDelete();
                        Delete_Hash(array_rehash, index, choice);
                    }
                    printf(" %s has been deleted\n", Inserted_word);
                }
            }
                break;
            case 8: {
                char Inserted_word[max];
                printf("Enter the word\n");
                scanf("%s", Inserted_word);
                int index;
                if (is_rehash != 1)
                    index = search(array_Hash, Inserted_word, size);
                else
                    index = search(array_rehash, Inserted_word, size_Rehash);
                if (index == -1) {
                    printf("The %s is not found \n", Inserted_word);
                } else {
                    if (is_rehash != 1)
                        printf("%s\t%d\n", array_Hash[index].word, array_Hash[index].freq);
                    else
                        printf("%s\t%d\n", array_rehash[index].word, array_rehash[index].freq);

                }
            }
                break;
            case 9: {
                int number;
                printf("Enter the number of repeated word \n");
                scanf("%d", &number);
                printf("words repeated more than specific threshold\n");
                getInOrder(root, number);
                printf("The unique word count=%d  and the most frequent word has frequent=%d", countOfUn, countOfMost);
            }

                break;
            case 10: {
                if (is_rehash == 1) {
                    for (int i = 0; i < size_Rehash; i++) {
                        if (array_rehash[i].state == 'O')
                            printf("%s(%d)  ", array_rehash[i].word, array_rehash[i].freq);
                    }
                } else {
                    for (int i = 0; i < size; i++) {
                        if (array_Hash[i].state == 'O')
                            printf("%s(%d) ", array_Hash[i].word, array_Hash[i].freq);
                    }
                }
            }
                break;
            case 11:
                exit(0);
            default:
                printf("The option is not valid.\n");
        }
        Menu();
        scanf("%d", &option);
    } while (option != 11);
    return 0;
}
void loadData() {
    FILE *in;
    char Temp_InputData[1000000];
    in = fopen("input.txt", "r");
    if (in == NULL) {
        printf("Error! can't open the file\n");
        return;
    }
    while (fgets(Temp_InputData, sizeof(Temp_InputData), in) != NULL) {
        Temp_InputData[strcspn(Temp_InputData, "\n")] = '\0';
        char *Temp_InputData2 = strtok(Temp_InputData, " ");
        while (Temp_InputData2 != NULL) {
            char Temp_InputData3[max];
            strcpy(Temp_InputData3, Temp_InputData2);
            char *Insert = checkIfItsAlfa(Temp_InputData3);
            if (Insert == NULL)
                break;
            size++;
            root = insert(root, Insert);
            Temp_InputData2 = strtok(NULL, " ");
        }
    }
    printf("The data has been loaded\n");
}
char *checkIfItsAlfa(char Word[]) {
    char Word2[max];
    strcpy(Word2, Word);
    strupr(Word2);
    int i = 0;
    while (i < strlen(Word)) {
        if (Word[i] != '\0' && (Word[i] < 'A' || (Word[i] > 'Z' && Word[i] < 'a') || Word[i] > 'z')) {
            for (int j = i; Word[j] != '\0'; j++) {
                Word[j] = Word[j + 1];
            }
        } else {
            i++;
        }
    }
    if (Word[0] == '\0')
        return NULL;

    return Word;
}
int getHeight(struct AVL_node *t) {
    if (t == NULL)
        return -1;
    else
        return t->Height;
}
int MAX(int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}
AVL_T singleRotateLeft(AVL_T x) {
    AVL_T y;
    y = x->Right;
    x->Right = y->Left;
    y->Left = x;

    x->Height = 1 + MAX(getHeight(x->Left), getHeight(x->Right));
    y->Height = 1 + MAX(getHeight(x), getHeight(y->Right));

    return y;
}
AVL_T singleRotateRight(AVL_T y) {
    AVL_T x;
    x = y->Left;
    y->Left = x->Right;
    x->Right = y;

    y->Height = 1 + MAX(getHeight(y->Right), getHeight(y->Left));
    x->Height = 1 + MAX(getHeight(y), getHeight(x->Left));

    return x;
}
AVL_T doubleRotateLeft(AVL_T T) {
    T->Left = singleRotateLeft(T->Left);
    return singleRotateRight(T);
}
AVL_T doubleRotateRight(AVL_T T) {
    T->Right = singleRotateRight(T->Right);
    return singleRotateLeft(T);
}
AVL_T insert(AVL_T t, char word[]) {
    if (t == NULL) {
        t = malloc(sizeof(struct AVL_node));
        strcpy(t->word, word);
        t->Height = 0;
        //t->balance = 0;
        t->frequency = 1;
        t->Left = t->Right = NULL;
    } else {
        if (strcasecmp(word, t->word) < 0) {
            t->Left = insert(t->Left, word);
            if (abs(getHeight(t->Left) - getHeight(t->Right)) >= 2) {
                if (strcasecmp(word, t->Left->word) < 0)
                    t = singleRotateRight(t);
                else
                    t = doubleRotateLeft(t);
            }
        } else if (strcasecmp(word, t->word) > 0) {
            t->Right = insert(t->Right, word);
            if (abs(getHeight(t->Left) - getHeight(t->Right)) >= 2) {
                if (strcasecmp(word, t->Right->word) > 0)
                    t = singleRotateLeft(t);
                else
                    t = doubleRotateRight(t);
            }
        } else {
            t->frequency++;
            size--;
        }
    }
    t->Height = 1 + MAX(getHeight(t->Right), getHeight(t->Left));
    // t->balance = abs(getHeight(t->Left)) - abs(getHeight(t->Right));

    return t;
}
void printInOrder(AVL_T t) {                            // this function use to print the Avl tree In Order
    if (t != NULL) {
        printInOrder(t->Left);
        printf("%s %d  ", t->word, t->frequency);
        printInOrder(t->Right);
    }
}
void outInOrder(struct Hash array_hash[],AVL_T t) {          //this function use to send the word from the Avl tree to hash table
    if (t != NULL) {
        outInOrder(array_hash, t->Left);
        insert_to_hash(array_hash, t->word, t->frequency, size);
        outInOrder(array_hash, t->Right);
    }
}
AVL_T find_min(AVL_T T) {
    if (T != NULL)
        while (T->Left != NULL)
            T = T->Left;
    return T;
}
AVL_T delete(AVL_T T, char word[], int choice) {
    AVL_T tmp_cell;
    if (T == NULL) {
        printf("Element not found\n");
        return T;
    }
    if (strcasecmp(word, T->word) < 0) {
        T->Left = delete(T->Left, word, choice);
        if (abs(getHeight(T->Left) - getHeight(T->Right)) >= 2) {
            if (getHeight(T->Left) > getHeight(T->Right)) {
                if (strcasecmp(word, T->Left->word) < 0)
                    T = singleRotateRight(T);
                else
                    T = doubleRotateLeft(T);
            } else {
                if (strcasecmp(word, T->Right->word) > 0)
                    T = singleRotateLeft(T);
                else
                    T = doubleRotateRight(T);
            }
        }
    } else if (strcasecmp(word, T->word) > 0) {
        T->Right = delete(T->Right, word, choice);
        if (abs(getHeight(T->Right) - getHeight(T->Left)) >= 2) {
            if (getHeight(T->Right) > getHeight(T->Left)) {
                if (strcasecmp(word, T->Right->word) > 0)
                    T = singleRotateLeft(T);
                else
                    T = doubleRotateRight(T);
            } else {
                if (strcasecmp(word, T->Left->word) < 0)
                    T = singleRotateRight(T);
                else
                    T = doubleRotateLeft(T);
            }
        }
    } else {
        if (choice == -1) {
            if (T->Left && T->Right) {
                tmp_cell = find_min(T->Right);
                strcpy(T->word, tmp_cell->word);
                T->Right = delete(T->Right, tmp_cell->word, choice);
            } else {
                tmp_cell = T;
                if (T->Left == NULL)
                    T = T->Right;
                else if (T->Right == NULL)
                    T = T->Left;
                free(tmp_cell);
            }
            size--;
        } else {
            T->frequency--;
        }
    }
    if (T != NULL)
        T->Height = MAX(getHeight(T->Left), getHeight(T->Right)) + 1;

    return T;
}
AVL_T find(char *word, AVL_T T) {
    if (T == NULL)
        return NULL;

    if (strcasecmp(strupr(word), strupr(T->word)) < 0)                //greater than x move to right
        return (find(word, T->Left));
    else                                                                            //Less than x move to left
    if (strcasecmp(strupr(word), strupr(T->word)) > 0)
        return (find(word, T->Right));
    else
        return T;
}
void creatHash(struct Hash array_hash[]) {              //this function use to creat hash table
    printf("Number of word = %d\n",size);
    size *= 2;
    while (!is_prime(size)) {
        size++;
    }
    printf("Hash table size = %d\n",size);
    for (int i = 0; i < size; i++) {                          //this for loop use for initial the state to Empty
        array_hash[i].state = 'E';
    }
}
void insert_to_hash(struct Hash array_hash[], char word[], int freq, int Size) {
    if ((float) Percentage / (float) Size >.65) {                           //this line use to check the percentage of full table
        if (is_rehash > 1) {
            printf("we need to do rehash again \n");
        } else {
            char Temp[max];
            strcpy(Temp, word);
            int Temp_freq = freq;
            is_rehash++;
            printf("Rehashing ..........\n");
            Percentage = 1;
            Rehash(array_hash);
            insert_to_hash(array_rehash, Temp, Temp_freq, size_Rehash);
        }
    } else {
        int i = 1;
        int index = hash(ascii_value(word), Size);
        while (array_hash[index].state =='O') {                    //this while use to insert word if it has a collision
            if (strcasecmp(array_hash[index].word, word) == 0) {
                array_hash[index].freq++;
                return;
            }
            index = hashi(index, i, Size);
            i++;
        }
        strcpy(array_hash[index].word, word);
        array_hash[index].state = 'O';
        array_hash[index].freq = freq;
        Percentage++;
    }
}
int hash(int value, int Size) {                            //this function use to get the index of word using is equation
    return value % Size;
}
int hashi(int index, int i,int Size) {                     //this function use to get the index in collision of word using is equation
    return (index + i) % Size;
}
int ascii_value(char word[]) {                             //this function gets the ascii_value of the word
    int value = 0;
    int i = 0;
    char copyWord[max];
    strcpy(copyWord, strupr(word));
    while (copyWord[i] != '\0') {                            // this while use for add all char in the word
        value = (value + copyWord[i]);
        i++;
    }
    return value;
}
int search(struct Hash array_hash[], char word[], int Size) {            // this function use to search of specific word
    int i = 1;
    int index = hash(ascii_value(word), Size);                         //this line use to get the index of the word
    while (array_hash[index].state == 'O') {
        if (strcasecmp(array_hash[index].word, word) == 0)
            return index;
        else {
            index = hashi(index, i,Size);                               // this line use to get the index after Collision
            i++;
        }
    }
    return -1;
}
void Delete_Hash(struct Hash array_hash[], int index,int choice) {                  //this function use for delete the word from hash table
    if (choice == 0) {
        array_hash[index].freq--;                                       // this line use for Reduce the number of repetitions
    } else {
        array_hash[index].state = 'D';
        Percentage--;
    }
}
void Rehash(struct Hash array_hash[]) {             //this function use for do the rehash when need
    size_Rehash = get_size_of_rehash();
    for (int k = 0; k < size; k++) {                       // this for loop use for copy the word from hash to rehash
        if (array_hash[k].state != 'E') {
            insert_to_hash(array_rehash, array_hash[k].word, array_hash[k].freq, size_Rehash);
        }
    }
}
int get_size_of_rehash() {                  //this function use to get size of rehash
    int new_size = size * 2;
    while (!is_prime(new_size)) {          // this while use to get the prime number after the size
        new_size++;
    }
    return new_size;
}
bool is_prime(int num) {                   // this function use to get the prime number
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    return true;
}
int choiceOfDelete() {               // this function use for ask the user if he wants to delete the completed word or reduce the frequent
    printf("The word is redundant :\n1-Delete completely\n2-Partial deletion\n ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
        return -1;                   //this means delete all words
    else {
        if (choice == 2)
            return 0;                // this means delete one of words
        else {
            return choiceOfDelete();
        }
    }
}
void getInOrder(AVL_T t, int number) {
    if (t != NULL) {
        getInOrder(t->Left, number);
        if (t->frequency == 1) {                          // Process the current node
            countOfUn++;
        } else {

            countOfUn++;                                  // Increment unique word count
            if (t->frequency > countOfMost) {
                countOfMost = t->frequency;
            }
            if (t->frequency >
                number)                     // print the word that has frequency uber of number that user intend
                printf("%s %d\n", t->word, t->frequency);
        }
        getInOrder(t->Right, number);
    }
}
void Menu() {
    printf("\n1. Load data from the file."
           "\n2. Insert a word to the AVL tree ."
           "\n3. Delete a word from the AVL tree."
           "\n4. Print the words as sorted in the AVL tree."
           "\n5. Create the Hash Table."
           "\n6. Insert a word to the Hash table."
           "\n7. Delete a word from the hash table."
           "\n8. Search for a word in the hash table and print its frequency."
           "\n9. Print words statistics."
           "\n10. Print the hash table ."
           "\n11. Exit the application.\n Please enter your option :\n");
}