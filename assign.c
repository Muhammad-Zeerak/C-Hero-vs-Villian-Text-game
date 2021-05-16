/*
  File: assign.c 
  Author: Khalid Alghamdi
  Email Id: algka002@mymail.unisa.edu.pk
  Description: Programming Assignment 2 -- Programming with C --
  This is my own work as defined by the University's Academic Misconduct policy.
*/

#include "CharacterRecord.h"

#include <stdbool.h>

#define MAX_INPUT_SIZE 8   // maximum input size of input this will be villians

int main() {

	CharacterRecord characters[MAX_CHARACTERS] = { 0 }; // holds the data from the file
	int no_characters = 0; // total num of characters

	// open the file
	FILE* fp;
	fp = fopen("characters.txt", "r");

	// write data to file and read the total characters
	no_characters = read_character_record(fp, characters);

	char input[MAX_INPUT_SIZE];

	bool quit_flag = false;

	printf("Please enter command\n");
	printf("[list, heroes, villains, search, reset, add, remove, battle, quit]: ");
	gets(input);
	printf("\n");

	while (!quit_flag) {

		if (strcmp(input, "list") == 0) {
			display_characters(characters, no_characters, 0);
		}
		else if (strcmp(input, "heroes") == 0) {
			display_characters(characters, no_characters, 1);
		}
		else if (strcmp(input, "villains") == 0) {
			display_characters(characters, no_characters, 2);
		}
		else if (strcmp(input, "search") == 0) {
			char take_in_name[25];
			printf("Please enter character's name: ");
			gets(take_in_name);

			int imdex = find_character(take_in_name, characters, no_characters);

			if (imdex != -1) {
				printf("\nAll about %s --> %s\n", characters[imdex].name, characters[imdex].hero == 1 ? "HERO" : "VILLIAN");
				printf("\nSecret identity: %s\n", characters[imdex].secret_identity);
				printf("\nBattles fought: %d\n", characters[imdex].no_battles);
				printf("  > No won: \t%d\n", characters[imdex].no_won);
				printf("  > No won: \t%d\n", characters[imdex].no_lost);
				printf("  > No won: \t%d\n", characters[imdex].no_drawn);
				printf("\nCurrent health: %d%%\n", characters[imdex].health);
			}
			else {
				printf("\n %s not found in character list.", take_in_name);
			}
		}
		else if (strcmp(input, "reset") == 0) {
			char take_in_name[25];
			printf("Please enter character's name: ");
			gets(take_in_name);

			int stat = reset_health(characters, take_in_name, no_characters);
			if (stat == 1) printf("\nSuccessfully reset %s's health.", take_in_name);
			else printf("\n%s not found in character list.", take_in_name);
		}
		else if (strcmp(input, "add") == 0) {
			char take_in_name[25];
			char take_in_iden[25];
			char hero_villian[1];
			printf("Please enter character's name: ");
			gets(take_in_name);
			printf("Please enter character's secret identity: ");
			gets(take_in_iden);
			printf("Is this character a hero or villian [h|v]? ");
			gets(hero_villian);
			int status = hero_villian == 'h' ? 1 : 0;

			if (find_character(take_in_name, characters, no_characters) != -1) {
				printf("\n%s is alrady in characters list.", take_in_name);
			}
			else {
				add_character(characters, take_in_name, take_in_iden, status, &no_characters);
				printf("\nSuccessfully added %s to character list.", take_in_name);
			}
		}
		else if (strcmp(input, "remove") == 0) {
			char take_in[25];
			printf("Please enter character's name: ");
			gets(take_in);

			int  determine = remove_character(characters, take_in, &no_characters);
			if (determine == 1) printf("\nSuccessfully removed %s from characters list.", take_in);
			else if (determine == 0) printf("\n%s is not found in characters list.", take_in);
		}
		else if (strcmp(input, "battle") == 0) {
			char name1[50];
			char name2[50];
			bool falg = false;
			int found1, found2;

			while (!falg) {
				printf("Please enter opponent's one name: ");
				gets(name1);
				found1 = find_character(name1, characters, no_characters);
				if (found1 != -1) falg = true;
				else {
					printf("%s not found in character list. Please enter another opponent!\n\n", name1);
				}
			}
			falg = false;
			while (!falg) {
				printf("Please enter opponent's two name: ");
				gets(name2);
				found2 = find_character(name2, characters, no_characters);
				if (found2 != -1) falg = true;
				else {
					printf("%s not found in character list. Please enter another opponent!\n\n", name2);
				}
			}
			do_battle(characters, found1, found2);
		}
		else if (strcmp(input, "quit") == 0) {
			printf("NOTE: Your program should output the following information to a file - new_characters.txt.\n\n");
			int  i = 0;

			while (i < no_characters) {
				printf("%s\n", characters[i].name);
				printf("%s\n", characters[i].secret_identity);
				char temp = characters[i].hero == 1 ? 'h' : 'v';
				printf("%c %d %d %d %d %d\n", temp, characters[i].no_battles, characters[i].no_won,
					characters[i].no_lost, characters[i].no_drawn, characters[i].health);
				i++;
			}

			printf("\n\n-- Program Terminating --\n\n");
			quit_flag = true;
			
			// write to file
			write_to_file(characters, no_characters);
		}
		else {
			printf("Not a valid command - please try again.\n\n");
		}
		printf("\n\nPlease enter command\n");
		printf("[list, heroes, villains, search, reset, add, remove, battle, quit]: ");
		gets(input);
		printf("\n");
	}
	return 0;
}
