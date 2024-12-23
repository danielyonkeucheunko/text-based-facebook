/********* main.c ********
    Student Name 	= Daniel Yonkeu-Cheunko
    Student Number	= 101263845
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE 
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    
    /* IMPORTANT: You must use the users linked list created in the code above. 
                  Any new users should be added to that linked list.
    */

    // Your solution goes here
    welcome();
    bool loop_end = 0;
    while(loop_end == 0) {
        int input = 0;

        print_menu();
        printf("\nEnter your choice: ");
        scanf("%i", &input);

        switch (input) {
            case 1: { //option 1
                char username[30];
                char password[15];
                printf("Enter a username: ");
                scanf("%s", &username);
                printf("Enter a password (15 characters max): ");
                scanf("%s", &password);
                add_user(users, username, password);
                printf("\n**** User Added! ****");
            }
                break;
            case 2: { //option 2
                char username[30];
                char password[15];
                printf("Enter a username to update their password: ");
                scanf("%s", &username);
                user_t *user = find_user(users, username);

                if (user == NULL) {
                    printf("\n-----------------------------------------------\n");
                    printf("             User not found.\n");
                    printf("-----------------------------------------------\n");
                } else {
                    printf("Enter a new password (15 characters max): ");
                    scanf("%s", &password);
                    strcpy(user->password, password);
                    printf("\n**** Password changed! ****\n");
                }
            }
                break;
            case 3: { //option 3
                char username[30];
                bool enabled = true;
                printf("Enter a username to manage their posts: ");
                scanf("%s", &username);
                user_t *user = find_user(users, username);

                while (enabled) {
                    if (user == NULL) {
                        printf("\n-----------------------------------------------\n");
                        printf("             User not found.\n");
                        printf("-----------------------------------------------\n");
                        enabled = false;
                    } else {
                        int option = 0;
                        display_user_posts(user);
                        display_post_options();
                        printf("\nYour choice: ");
                        scanf("%i", &option);

                        switch (option) {
                        case 1: //post menu option 1
                            char text[250];
                            printf("Enter your post content: ");
                            scanf(" %[^\n]", &text);
                            add_post(user, text);
                            printf("Post added to your profile.");
                            break;
                        case 2: //post menu option 2
                            int post = 0;
                            printf("Which post you want to delete? ");
                            scanf("%i", &post);
                            
                            bool is_post_deleted = delete_post(user, post);
                            if (is_post_deleted) {
                                printf("Post %i was deleted successfully!", post);
                            } else {
                                printf("Invalid post number.");
                                enabled = false;
                            }
                            break;
                        case 3: //post menu option 3
                            enabled = false;
                            break;
                        }
                    }
                }
            }
                break;
            case 4: { //option 4
                char username[30];
                bool enabled = true;
                printf("\nEnter a username to manage their friends: ");
                scanf("%s", &username);
                user_t *user = find_user(users, username);
                
                while (enabled) {

                    if (user == NULL) {
                        printf("\n-----------------------------------------------\n");
                        printf("             User not found.\n");
                        printf("-----------------------------------------------\n");
                        enabled = false;
                    } else {
                        int option = 0;
                        display_friend_options(user);
                        printf("\nYour choice: ");
                        scanf("%i", &option);

                        switch (option) {
                        case 1: //friend menu option 1
                            display_user_friends(user);
                            break;
                        case 2: //friend menu option 2
                            char username[30];
                            printf("\nEnter a new friends' name: ");
                            scanf("%s", &username);
                            add_friend(user, username);
                            printf("Friend added to the list.\n");
                            break;
                        case 3: { //friend menu option 3
                            char username[30];
                            display_user_friends(user);
                            printf("\nEnter a friends' name to delete: ");
                            scanf("%s", &username);

                            bool is_friend_deleted = delete_friend(user, username);
                            if (is_friend_deleted) {
                                display_user_friends(user);
                            } else {
                                printf("Invalid friend's name.");
                                enabled = false;
                            }
                        }    
                            break;
                        case 4:
                            enabled = false;
                            break;
                        }
                    }
                }
            }
                break;
            case 5: //option 5
                display_all_posts(users);
                break;
            case 6: //option 6
                teardown(users);
                printf("\n***********************************************\n");
                printf("  Thank you for using Text-Based Facebook\n");
                printf("             Goodbye!\n");
                printf("***********************************************\n");
                loop_end = 1;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}