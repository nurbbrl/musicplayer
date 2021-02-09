/*
    In the music player application, the circular doubly linked list due to the features such as the songs entering any part of the list and the list returning to the top.
It is appropriate to use data structure of circular doubly linked list. Thus the list is inverted for convenience and data can be added to the front or back of any song without iterating the phase.

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#pragma region database_code
/* The node structure for the doubly list includes the next and prev variables that hold the address of the next and previous node, and the data part to hold the song name.
*/
struct Node 
{ 
  char *data; 
  struct Node *next; 
  struct Node *prev;
}; 
/* The function that creates a new node in memory and gives this node to the string new_data */
struct Node * node_olustur(char *new_data) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
  
    new_node->data  = malloc(sizeof(new_data) +1); 
    strcpy(new_node->data, new_data);
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}
/* The function that adds the node at the top of the list */
void liste_basina_ekle(struct Node** head, char *new_data) {
    struct Node* new_node = node_olustur(new_data);

    if((*head) == NULL) {
        new_node->next = new_node->prev = new_node;
        (*head) = new_node;
        return;
    }

    struct Node* last = (*head)->prev;
    new_node->next = (*head);
    new_node->prev = last;

    (*head)->prev = new_node;
    last->next = new_node;

    (*head) = new_node;

}

/* Function that adds the new node to the end of the list */
void liste_sonuna_ekle(struct Node** head, char *new_data) {
    struct Node* new_node = node_olustur(new_data);

    if((*head) == NULL) {
        new_node->next = new_node->prev = new_node;
        (*head) = new_node;
        return;
    }

    struct Node* last = (*head)->prev;

    new_node->next = (*head);
    (*head)->prev = new_node;
    new_node->prev = last;
    last->next = new_node;

}
/* Function adding after searched value  */
/* Do not take action if the searched value is not available or the list is empty*/
void liste_aranan_degerin_arkasina_ekle(struct Node** head, char *new_data, char *look_data) {
    if(*head == NULL)
        return;
    
    struct Node* iter = (*head);
    int is_find = 0;
    
    while (iter->next != *head)
    {
        if(strcmp(iter->data, look_data) == 0) {
            is_find = 1;
            break;
        }
        iter = iter->next;
    }
    /* If the searched value shows head at the end of the list */
    if (is_find == 0 && strcmp(iter->data, look_data) == 0) {
        is_find = 1;
    }
    
    if(is_find != 1)
        return;
    
    struct Node* new_node = node_olustur(new_data);
    struct Node* temp = iter->next;
    iter->next = new_node;
    new_node->prev = iter;
    new_node->next = temp;
    temp->prev = new_node;

}
/* Adds the new node in front of the searched value */
void liste_aranan_degerin_onune_ekle(struct Node** head, char *new_data, char *look_data) {
    if(*head == NULL)
        return;
    
    struct Node* iter = (*head);
    int is_find = 0;
    
    while (iter->prev != *head)
    {
        if(strcmp(iter->data, look_data) == 0) {
            is_find = 1;
            break;
        }
        iter = iter->prev;
    }
    /* If the searched value shows head at the end of the list, add it to the end of the list */
    if (is_find == 0 && strcmp(iter->data, look_data) == 0) {
        is_find = 1;
    }
    
    if(is_find != 1)
        return;
    
    struct Node* new_node = node_olustur(new_data);
    struct Node* temp = iter->prev;
    iter->prev = new_node;
    new_node->prev = temp;
    new_node->next = iter;
    temp->next = new_node;

}
/* The function that deletes the node with the given value from the list */
void listeden_sil(struct Node** head, char* data) {
    if (*head == NULL)
        return;

    struct Node *iter = *head, *pre = NULL;
    int is_find = 0;
    while(strcmp(iter->data, data) != 0)
    {
        
        if (iter->next == *head)         //came to the head and is still not found
            return;

        pre = iter;
        iter = iter->next;
        
    }
  
    /* If the node to be deleted consists of head and only one node */
    if (iter->next == *head && pre == NULL) {
        *head = NULL;
        free(iter);
        return;
    }

    /* The node head to be deleted, but not the only one */
    if (iter == *head) {
        pre = (*head)->prev;
        (*head) = (*head)->next;
        pre->next = *head;
        (*head)->prev = pre;
    }
    /* If the node to delete is the last node */
    else if (iter->next == *head) { 
        pre->next = *head; 
        (*head)->prev = pre; 
        free(iter); 
    } 
    else { 
        // Keep the next of iter in a temporary variable
        struct Node* temp = iter->next; 
  
        pre->next = temp; 
        temp->prev = pre; 
        free(iter); 
    } 

}

/* return list as char * */
char * liste_duz_yaz(struct Node* head) {
    char current[2000], *temp;
    char l = '\n';
    struct Node* iter = head;
    while (iter->next != head)
    {
        //temp = calloc(sizeof(current) + sizeof(iter->data) +2, 1);
        //strcpy(temp, current);
        strcat(current, iter->data);
        strncat(current, &l, 1);
        //current = temp;
        iter = iter->next;
    }
    //temp = calloc(sizeof(current) + sizeof(iter->data) +2, 1);
    //strcpy(temp, current);
    strcat(temp, iter->data);
    strncat(temp, &l, 1);
    //current = temp;   

    return current; 
}

char * liste_ters_yaz(struct Node* head) {
    char *current="\0", *temp;
    char l = '\n';
    struct Node* iter = head->prev;
    while (iter != head)
    {
        temp = calloc(sizeof(current) + sizeof(iter->data) +2, 1);
        strcpy(temp, current);
        strcat(temp, iter->data);
        strncat(temp, &l, 1);
        current = temp;
        iter = iter->prev;
    
    }
    temp = calloc(sizeof(current) + sizeof(iter->data) +2, 1);
    strcpy(temp, current);
    strcat(temp, iter->data);
    strncat(temp, &l, 1);
    current = temp;

    return current;    
}
#pragma endregion

/* music_list is the variable that holds the starting address of the values ​​in the whole list
current_song is the variable that holds the address of the currently playing song. */
struct Node *muzik_listesi = NULL, *current_song=NULL;

#define LEN             100
#define PRINTPLAYLIST   "PrintPlaylist"
#define REVERSEPLAYLIST "ReversePlaylist"
#define INSERTSONG      "InsertSong"
#define MOVESONG        "MoveSong"
#define REMOVESONG      "RemoveSong"
#define PLAYSONG        "PlaySong"

/* Adds at the beginning of the list with H and at the end with T*/
void insert_song(char w, char *song_name) {
    if(w == 'H')
        liste_basina_ekle(&muzik_listesi, song_name);
    if(w == 'T')
        liste_sonuna_ekle(&muzik_listesi, song_name);
}
/*It is added before with B and after with A */
/* Delete from list first and then add to add place */
void move_song(char w, char *song_name, char *lookign_for_song) {
    listeden_sil(&muzik_listesi, song_name);
    if (w == 'B')
        liste_aranan_degerin_onune_ekle(&muzik_listesi, song_name, lookign_for_song);
    if ( w== 'A')
        liste_aranan_degerin_arkasina_ekle(&muzik_listesi, song_name, lookign_for_song);
}

void remove_song(char *song_name) {
    listeden_sil(&muzik_listesi, song_name);
}
char * print_play_list(char w) {
    char *liste;
    if ( w == 'F')
        liste = liste_duz_yaz(muzik_listesi);
    if ( w == 'R')
        liste = liste_ters_yaz(muzik_listesi);

    return liste;
}
/* N play next song, P play previous song */
void playsong(char w) {
    if (w == 'N') {
        if (current_song == NULL) 
            current_song = muzik_listesi;
        else
            current_song = current_song->next;
    }
     if (w == 'P') {
        if (current_song == NULL) 
            current_song = muzik_listesi;
        else
            current_song = current_song->prev;
    }
}
void dizi_bosalt(char dizi[LEN]) {
    for (int i = 0; i < LEN; i++)
    {
        dizi[i] = '\0';
    }
    
}
int main() {
    /* Get command set from file */
    FILE *fs = fopen("input.txt","r");
    if(fs == NULL){
        printf("dosya açılamadı");
        return 0;
    }
    char c;
    char dizi[250][4][LEN];             //Command set is kept in 3 dimensional array variable
    char okunan[LEN];
    dizi_bosalt(okunan);
    int i = 0, sa = 0, j = 0;
    while ( (c=getc(fs)) != EOF )
    {
       /* Add the received string to the array when it comes to tab character or bottom line character */
        if ( c == '\t' || c =='\n') {
            strcpy(dizi[sa][j], okunan);
            dizi_bosalt(okunan);
            if( j < 4)
                j++;
            i= 0;
            if(c == '\n') {
                sa++;
                j = 0;
            }
                

            continue;
        }
        okunan[i] = c;
        i++;

    }
    fclose(fs);
    i = 0;
    fs = fopen("output3.txt", "w");
    while (dizi[i][0][0] != '\0')
    {
        if(strcmp(dizi[i][0],INSERTSONG) == 0) {
            insert_song(dizi[i][1][0], dizi[i][2]);
            fprintf(fs, dizi[i][2]);
            fprintf(fs, "\n*****\n");
        } 
        else if(strcmp(dizi[i][0],REMOVESONG) == 0) {
            
            if (current_song != NULL) {
            if(strcmp(current_song->data, dizi[i][1])== 0) {
                fprintf(fs, "cannot remove playing son");
                fprintf(fs, "\n*****\n");
                i++;
                continue;
            }
            }
            remove_song(dizi[i][1]);
        } 
        else if(strcmp(dizi[i][0],PRINTPLAYLIST) == 0) {
            if(muzik_listesi == NULL) {
                fprintf(fs, "No Songs To Print");
                fprintf(fs, "\n*****\n");
                i++;
                continue;
            }
            struct Node *iter = muzik_listesi;
            while (iter->next != muzik_listesi)
            {
                char dx[25];
                strcpy(dx, iter->data);
                fprintf(fs, dx);
                fprintf(fs, "\n*****\n");
                iter = iter->next;
            }
            
        }
        else if(strcmp(dizi[i][0],PLAYSONG) == 0) {
            if(muzik_listesi == NULL) {
                fprintf(fs, "No music for playing");
                fprintf(fs, "\n*****\n");
                i++;
                continue;
            }
            playsong(dizi[i][1][0]);
            char ds[25];
            strcpy(ds, current_song->data);
            fprintf(fs, ds);
            fprintf(fs, "\n*****\n");
            
        }
        else if(strcmp(dizi[i][0],MOVESONG) == 0) {
            if(muzik_listesi == NULL) {
                i++;
                continue;
            }
            move_song(dizi[i][1][0], dizi[i][2], dizi[i][3]);
        }
        if(i > 100)
            break;
        i++;
    }
    fclose(fs);

/*
//The code written to test whether functions are working
   insert_song('T', "Song_A");
   insert_song('T', "Song_2");
   insert_song('H', "Song_3");
   insert_song('H', "Song_4");
   insert_song('H', "Song_5");
   move_song('B', "Song_A", "Song_4");

   
   char *liste = print_play_list('F');
   printf("%s\n", liste); 
   //liste = print_play_list('R');
   //printf("%s\n", liste); 
*/

}