/********* definitions.c ********
    Student Name 	= Daniel Yonkeu-Cheunko
    Student Number	= 101263845
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#include <assert.h>
#include <stdbool.h>


// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password) {

    user_t *added_user = malloc(sizeof(user_t)); // creates allocates memory for a new user.
    assert(added_user != NULL);
    strcpy(added_user->username, username); //gives the user a username
    strcpy(added_user->password, password); //gives the user a password
    added_user->next = NULL;
    added_user->friends = NULL;
    added_user->posts = NULL;

    if (users == NULL) { // if there are no users
        added_user->next = users;
        return added_user;
    }

    if (users->next == NULL || strcmp(users->username, added_user->username) > 0) { //case for what to do with one or two friends in the linked list.
        added_user->next = users->next;
        users->next = added_user;
    } else {
        user_t *temp = users;
        while (temp->next != NULL && strcmp(temp->username, added_user->username) < 0) {
            temp = temp->next;
        }
        added_user->next = temp->next; 
        temp->next = added_user;
    }
    return users;
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username) {
    user_t *current = users;

    while (current != NULL) { //iterates through all the users and if the usernames match return that user.
        if (strcmp(current->username, username) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username) { // creates a node of type friend_t

    friend_t *friend = malloc(sizeof(friend_t));
    strcpy(friend->username, username);
    friend->next = NULL;
    
    return friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend) { 
    friend_t *new_friend = create_friend(friend);

    if (user->friends == NULL || strcmp(new_friend->username, user->friends->username) < 0) { //case for what to do with one or two friends in the linked list.
        new_friend->next = user->friends;
        user->friends = new_friend;
    } else {
        friend_t *current = user->friends;
        while(current->next != NULL && strcmp(new_friend->username, current->next->username) > 0) {
            current = current->next;
        }
        new_friend->next = current->next;
        current->next = new_friend;
    }

}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name) {
    friend_t *temp;
    if (user->friends == NULL) { //if the user has no friends :(
        return false;
    }

    if (strcmp(user->friends->username, friend_name) == 0) { //if the friend node is located at the start of the linked list.
        temp = user->friends;
        user->friends = user->friends->next;
        free(temp);
        return true;
    }
    
    
    friend_t *current = user->friends;
    while (current->next != NULL) {
        if (strcmp(current->next->username, friend_name) == 0) {
            temp = current->next;
            current->next = temp->next;
            free(temp);
            return true;
        }
        current = current->next;
    }
    return false;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text) { //creates a node of type post_t
    post_t *new_post = malloc(sizeof(post_t));
    strcpy(new_post->content, text);
    new_post->next = NULL;  
    
    return new_post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text) { //case for what to do with one or two friends in the linked list.
    post_t *new_post = create_post(text);

    if (user->posts != NULL) {
        new_post->next = user->posts;
    } 
    user->posts = new_post;
    
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number) {

    if (user->posts == NULL) { //if the user has no posts
        return false;
    }

    post_t *current = user->posts;
    post_t *temp;
    if (number == 1) { //if the post number is 1 or the head of the linked list.
        temp = user->posts;
        user->posts = user->posts->next;
        free(temp);
        return true;
    } else {

        for (int i = 0; i < number-2; i++) {
            current = current->next;
        }

        if (current->next == NULL) {
            return false;
        }

        temp = current->next;
        current->next = temp->next;
        free(temp);
        return true;
    }
    return false;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user) {

    post_t *current = user->posts;

    printf("\n-----------------------------------------------\n");
    printf("            %s's posts\n", user->username);

    if (user->posts == NULL) { // if the user has no posts
        printf("No posts available for %s.\n", user->username);
    } else {
        int postNumber = 1;
        while (current != NULL) {
        printf("%d- %s: %s\n", postNumber, user->username, current );
        current = current->next;
        postNumber++;
        }
    }
    printf("-----------------------------------------------\n");
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user) {

    printf("\nList of %s's friends\n", user->username);

    friend_t *current = user->friends;

    if (user->friends == NULL) {
        printf("No friends available for %s.\n", user->username);
    } else {
        int friendNumber = 1;
        while (current != NULL) {
        printf("%d- %s\n", friendNumber, current->username);
        current = current->next;
        friendNumber++;
        }
        printf("\n");
    }
    
    
}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users) {
    
    int enable = 1;

    user_t *current = users;
    post_t *post = current->posts;
    
    while (enable) {
        char input = 'c';

        printf("\n\n");
        int i = 0;
        while (i < 2) { // iterates twice.
            int postNumber = 1;
            while (post != NULL) { // prints out the users posts
                printf("%d- %s: %s\n", postNumber, current->username, post);
                postNumber++;
                post = post->next;
            }
            i++;
            current = current->next;

            if (current == NULL) {
                break;
            }

            post = current->posts;
        }

        if (current == NULL) {
            printf("\n******** All posts have been displayed! *******\n");
            enable = 0;
            break;
        }

        while (input != 'Y' && input != 'y' && input != 'N' && input != 'n') {
            printf("\n\nDo you want to display next 2 users posts? (Y/N): ");
            scanf(" %c", &input);

            if (input != 'Y' && input != 'y' && input != 'N' && input != 'n') {
                printf("Invalid input!");
            }
        }

        if (input == 'n' || input == 'N') {
            enable = 0;
        }
    }

}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users) {
   user_t *temp;

   while (users != NULL) {
    temp = users;
    users = users->next;
    free(temp);
   }
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu() {
   printf("\n***********************************************\n");
   printf("                MAIN MENU:                     \n");
   printf("***********************************************\n");
   printf("1. Register a new User                         \n");
   printf("2. Manage a user's profile (change password)   \n");
   printf("3. Manage a user's posts (display/add/remove)  \n");
   printf("4. Manage a user's friends (display/add/remove)\n");
   printf("5. Display All Posts                           \n");
   printf("6. Exit                                        \n");
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}

/*
   Function that displays post options
*/
void display_post_options() {
    printf("\n1. Add a new user post\n");
    printf("2. Remove a users post\n");
    printf("3. Return to main menu\n");
}

/*
    Function that displays friend options
*/
void display_friend_options(user_t *user) {
    printf("\n-----------------------------------------------\n");
    printf("             %s's friends\n", user->username);
    printf("-----------------------------------------------\n");
    printf("\n1. Display all user's friends\n");
    printf("2. Add a new friend\n");
    printf("3. Delete a friend\n");
    printf("4. Return to main menu\n");
}

/*
    Function that Welcomes the user.
*/
void welcome() {
    printf("***********************************************\n");
    printf("      Welcome to Text-Based Facebook\n");
    printf("***********************************************\n");
}