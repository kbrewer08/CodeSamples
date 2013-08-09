/*
    Written by  : Keith Brewer
    Date written: March 2011

    This file was written by me as part of a group project in a data structures
    class that used C. Our assignment was to use a hash table (with linked list
    collision resolution) and a binary search tree to store some information.
    We chose to store and manage basic DVD movie information. My job was to 
    handle the user's movie search interface, and the screen output manager and
    functions. My other tasks were:
    
    - Check load factor of hash table and rehash it if necessary.
    - During rehash
          - destroy old hash table
          - destroy old linked list
          - recreate hash table using a table twice the size of the old one
          - recreate the linked lists in the hash table
    - Interface with team member 1's hash table functions, having only the 
      prototypes on hand.
    - Interface with team member 2's binary search tree functions, having only
      the prototypes on hand.
    - Find a way to test my code without having the other source files handy,
      since they were in the process of themselves being written.

    It should be noted that earlier in the class we had to write our own hash
    table and binary search trees for other assignments, so even though I had
    a less technical role in this project, I had actually made a hash table
    and binary search tree during previous assignments in the class.
    
    One thing that I am proud of regarding my code, other than its easy
    readability, is using fgets to get input from the user; and creating my
    "flush_fgets_stdin" function to clean up the string and the input buffer
    afterward.
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "movieDB.h"

#define FLUSH while(getchar() != '\n')

/* ========================= findMovieManager =================================
    Interacts with the user to search through the movie list to find user
    specified movie titles.
    Pre:  movieHead - the main header of the entire collection of structures
    Post: nothing, really. the user may or may not have searched for a movie.
          If they did though and it was successful, it displays the info in a
          label format. If they did and it was not successful, it says so.
*/
void findMovieManager(const MOVIE_HEAD* movieHead)
{
    int    goAgain;
    char   choice;
    char*  targetTitle;
    MOVIE* movie;

    goAgain = 1;
    choice  = 'y';
    movie   = NULL;

    while(goAgain)
    {
        fputs("\nEnter the title of the movie you would like to search for.", stdout);
        fputs("\n\nTitle: ", stdout);
        targetTitle = getTargetTitle();

        movie = searchMovie(movieHead, targetTitle);

        if(movie)
        {
            fputs("\n\tMovie found!\n", stdout);
            printSingleMovie(movie);
        }
        else
            fputs("\n\tNo movies were found with that title.\n\n", stdout);
        free(targetTitle);

        fputs("Do you want to search for another movie? <y/n>: ", stdout);
        scanf(" %c", &choice);
        choice = tolower(choice);
        FLUSH;
        if(choice == 'n')
            goAgain = 0;
    }

    return;
}

/* ========================= listMovieTable ===============================
    prints the titles of all the movies in the order that they appear in the
    hash table.
    Pre:  movieHead - the main header of the entire collection of structures
    Post: list of movie titles has been printed to the screen.
*/
void listMovieTable(const MOVIE_HEAD* movieHead)
{
    int         i;
    int         j;
    MOVIE*      dataOut;
    HASH_ENTRY* hashTable;

    hashTable = movieHead->pHash;

    fputs("\n\tMovies listed in hash table sequence\n\n", stdout);
    for( i = 0; i < movieHead->hashTableSize; i++ )
    {
        if(hashTable[i].pData)
            printf("%s\n", ((MOVIE*)hashTable[i].pData)->title);
        if(listCount(hashTable[i].list))
            for(j = 0; j < listCount(hashTable[i].list); j++)
            {
                traverse(hashTable[i].list, j, (void**)&dataOut);
                printf("\t%s\n", dataOut->title);
            }
    }

    return;
}

/* ========================= listMovieSorted ==================================
    Prints the movie titles in alphabetical order by recursively traversing the
    binary search tree using an inorder traversal (left - root - right).
    Pre:  root - initially, the root of the binary search tree; then roots of
                 subtrees as the tree is traversed.
    Post: DVD titles printed in alphabetical order
*/
void listMovieSorted(const TREE_NODE* root)
{
    if(root)
    {
        listMovieSorted(root->left);
        printf("\t%s\n", ((MOVIE*)(root->pData))->title);
        listMovieSorted(root->right);
    }

    return;
}

/* ========================= checkReHash ======================================
    Checks the load factor of the hash table. If it goes above 75%, the table
    is rehashed. A new hash table is created, with its size set to the first
    prime number larger than twice the size of the old table. The old table is
    then traversed, and each entry is sent back through the hash function to
    find its new location in the new table. When this is done, the pointer to
    the old table is freed, and the pointer to the new table is assigned to
    movieHead.
    Pre:  movieHead - the main header of the entire collection of structures
    Post: Table has been rehashed, if necessary, as described above.
*/
void checkReHash(MOVIE_HEAD* movieHead)
{
    int         i;
    int         j;
    int         newTableSize;
    float       hashTableLoad;
    MOVIE_HEAD* tempMovie;
    HASH_ENTRY* newTable;
    MOVIE*      data;

    tempMovie = NULL;
    newTable  = NULL;
    data      = NULL;

    hashTableLoad = getLoadFactor(movieHead);

    if(hashTableLoad > 0.75) //to force rehash, lower or remove value on right
    {
        tempMovie = (MOVIE_HEAD*)calloc(1, sizeof(MOVIE_HEAD));
        if (!tempMovie)
        {
            fputs("Error allocating tempMovie\n", stdout);
            exit(401);
        }

        tempMovie->numEntries = movieHead->numEntries;

        newTableSize             = findPrime(2 * movieHead->hashTableSize);
        tempMovie->hashTableSize = newTableSize;

        newTable         = createHashTable(newTableSize);
        tempMovie->pHash = newTable;

        for( i = 0; i < movieHead->hashTableSize; i++ ) //copy from old to new
        {
            if(movieHead->pHash[i].pData)//rehash data in prime area
                addToHashTable(tempMovie, (MOVIE*)movieHead->pHash[i].pData);
            if(listCount(movieHead->pHash[i].list))//rehash data in linked list
                for(j = 0; j < listCount(movieHead->pHash[i].list); j++)
                {
                    traverse(movieHead->pHash[i].list, j, (void**)&data);
                    addToHashTable(tempMovie, data);
                }
        }

        destroyOldTable(movieHead);//free memory of old table
        movieHead->hashTableSize = newTableSize;//set new table size
        movieHead->pHash = tempMovie->pHash;//set new table to movieHead
        free(tempMovie);//remove temp movie header structure
    }
	else
		fputs("\n\tNo reahash necessary, load factor not high enough.\n", stdout);
    return;
}

/* ========================= getTargetTitle ================================
    Gets a target movie title to search for from the user. I know dynamic memory
    searches are generally not advised since it's unnecessary extra work to keep
    track of the allocated memory, but I believe I won't have a problem with it.
    Pre:  none
    Post: returns the user's string, in the form of a pointer to the first
          character
*/
char* getTargetTitle(void)
{
    char* targetTitle;
    char tempName[128];

    fgets(tempName, sizeof(tempName), stdin);
    flush_fgets_stdin(tempName);

    if(!(targetTitle = (char*)calloc(strlen(tempName) + 1, sizeof(char))))
    {
        fputs("\nMemory allocation for targetTitle string failed.\n", stdout);
        exit(401);
    }
    strncpy(targetTitle, tempName, strlen(tempName));

    return targetTitle;
}

/* ========================= printSingleMovie ==============================
    Prints the information of a single movie entry in a label format
    Pre:  movie - pointer to the structure holding the movie information
    Post: information for one movie has been printed.
*/
void  printSingleMovie(const MOVIE* movie)
{
    printf("\n\tTitle    : %s\n", movie->title);
    printf("\tDirector : %s\n", movie->director);
    printf("\tYear     : %d\n", movie->year);
    printf("\tGenre    : %s\n\n", movie->genre);
    return;
}

/* ========================= flush_fgets_stdin ===============================
    Checks the given string to make sure there is a newline character. If not,
    the input buffer overflowed (even if it only left the newline). If the
    newline is not present, it flushes the input buffer. If the newline is
    present, it just changes it to \0.
    Pre:  string - the string to be checked
    Post: If overflow occurred, buffer is flushed. If not, \n is changed to \0
*/
void flush_fgets_stdin(char* str)
{
          int c   = 0;
    const int len = strlen(str);

     //if buffer overflows, flush it
    if(str[len - 1] != '\n')
        while(((c = getchar()) != '\n') && (c != EOF))
            ;

    //no buffer overflow, so get rid of newline character
    if(str[len - 1] == '\n')
        str[len - 1] = '\0';

    //regardless of overflow state, make sure string is null terminated
    if(str[len] != '\0')
        str[len] = '\0';

    return;
}

/* ========================= printManagerMenu ===============================
   Shows the menu for a print manager function.
   PRE : none
   POST: menu printed to screen
*/
void printManagerMenu(void)
{
    fputs("\n", stdout);
    fputs("\t\t*********************************\n", stdout);
    fputs("\t\t*                               *\n", stdout);
    fputs("\t\t*         Print Manager         *\n", stdout);
    fputs("\t\t*                               *\n", stdout);
    fputs("\t\t*                               *\n", stdout);
    fputs("\t\t*     H - Hash Table Sequence   *\n", stdout);
    fputs("\t\t*     I - BST Inorder           *\n", stdout);
    fputs("\t\t*     P - BST Preorder          *\n", stdout);
    fputs("\t\t*     O - BST Postorder         *\n", stdout);
    fputs("\t\t*     T - Tree structure        *\n", stdout);
    fputs("\t\t*     M - Menu                  *\n", stdout);
    fputs("\t\t*     B - Back to Main Menu     *\n", stdout);
    fputs("\t\t*                               *\n", stdout);
    fputs("\t\t*********************************\n", stdout);
    fputs("\n", stdout);

    return;
}

/* ========================= getPrintOption ===============================
   Gets a validated option for the print manager from the user.
   PRE : none
   POST: returns a char representing a valid print manager menu option
*/
char getPrintOption(void)
{
    char option;

    fputs("Enter option (M for Menu, B to go back): ", stdout);
    scanf(" %c", &option);
    FLUSH;
    option = tolower(option);

    while(!strchr("hipotmb", option))
    {
        fputs("Enter option (M for Menu, B to go back): ", stdout);
        scanf(" %c", &option);
        FLUSH;
        option = tolower(option);
    }

    return option;
}

/* ========================= printManager ===============================
   Prints data from tree or hash table in various forms depending on users
   choice.
   PRE : movieHead - the main header of the entire collection of structures
   POST: tree or hash table contents printed to screen. Maybe.
*/
void printManager(MOVIE_HEAD* movieHead)
{
    char option;

    printManagerMenu();
    option = getPrintOption();

    while(option != 'b')
    {
        switch(option)
        {
            case 'h': listMovieTable(movieHead);
                    break;
            case 'i': fputs("\n\tMovies listed in inorder traversal\n\n", stdout);
                      traverseBST(movieHead->pTree, printOneTitle, 'I');
                    break;
            case 'p': fputs("\n\tMovies listed in preorder traversal\n\n", stdout);
                      traverseBST(movieHead->pTree, printOneTitle, 'P');
                    break;
            case 'o': fputs("\n\tMovies listed in postorder traversal\n\n", stdout);
                      traverseBST(movieHead->pTree, printOneTitle, 'O');
            case 't': fputs("\n\tMovies listed in indented tree order\n\n", stdout);
                      printIndented(movieHead->pTree);
                    break;
            case 'm': printManagerMenu();
                    break;
        }
        option = getPrintOption();
    }

    return;
}

/* ========================= printOneTitle ===============================
   This is the function that is passed to the BST traversal function to print
   data to the screen.
   PRE : arg1 - pointer to data in current node of tree traversal
   POST: single movie title printed to screen
*/
void printOneTitle(void* arg1)
{
    MOVIE* movie = (MOVIE*)arg1;

    printf("%s\n", movie->title);

    return;
}

/* ========================= destroyOldTable ===============================
   Destroys the old hash table, but doesn't free the data pointers since they
   are still needed for the rehashed table.
   PRE : movieHead - the main header of the entire collection of structures
   POST: old table destroyed
*/
void destroyOldTable(MOVIE_HEAD* movieHead)
{
    int         i;
    int         tableSize;
    HASH_ENTRY* pHash;

    tableSize = movieHead->hashTableSize;
    pHash = movieHead->pHash;

    for(i = 0; i < tableSize; i++)
    {
        pHash[i].pData = NULL;
        pHash[i].list = destroyListPartial(pHash[i].list);
    }

    free(pHash);

    return;
}

/*	======================== destroyListPartial ============================
	Frees the nodes in a list, but leaves data pointers intact.
	   Pre    List is a pointer to a valid list.
	   Post   Nodes and head structure deleted
	   Return null head pointer
*/
LIST* destroyListPartial(LIST* pList)
{
	NODE* deletePtr;

	if (pList)
    {
	    while (pList->count > 0)
        {
            deletePtr    = pList->head;
	        pList->head  = pList->head->link;
	        pList->count--;
	        free (deletePtr);
        }
	    free (pList);
    }
	return NULL;
}
