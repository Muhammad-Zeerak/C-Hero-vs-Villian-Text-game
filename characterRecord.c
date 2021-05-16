/*
  File: characterRecord.c 
  Author: Khalid Alghamdi
  Email Id: algka002@mymail.unisa.edu.pk
  Description: Programming Assignment 2 -- Programming with C --
  This is my own work as defined by the University's Academic Misconduct policy.
*/

#include "CharacterRecord.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include<time.h>

/*
  This function reads the content of file that will already be opened in main
  In the characters array which will be used through out the program
  and return the total number of rows in the character array i.e, total character
*/
int read_character_record(FILE* infile, CharacterRecord characters[]) {

	char name[STRING_LENGTH + 1];
	int  i = 0;
	char hero;

	fgets(name, STRING_LENGTH + 1, infile);

	while (i < MAX_CHARACTERS && !feof(infile)) {
		name[strlen(name) - 1] = '\0';
		strcpy(characters[i].name, name);

		fgets(name, STRING_LENGTH + 1, infile);
		name[strlen(name) - 1] = '\0';
		strcpy(characters[i].secret_identity, name);

		fscanf(infile, "%c", &hero);
		if (hero == 'h')
			characters[i].hero = 1;
		else
			characters[i].hero = 0;
		fscanf(infile, "%d %d %d %d %d ", &characters[i].no_battles, &characters[i].no_won,
			&characters[i].no_lost, &characters[i].no_drawn, &characters[i].health);

		i++;

		fgets(name, STRING_LENGTH + 1, infile);
	}

	return i;
}

/*
  This function prints all the information of the characters 
  The output is formatted according to the given specifications
  Characters are printed according to status
  0 for All, 1 for Heroes, 2 for Villians
*/
void display_characters(CharacterRecord character[], int total_num, int status) {

	printf("|====================================================|\n");
	printf("|          Characters (Heroes & Villains)            |\n");
	printf("|====================================================|\n");
	printf("|                                                    |\n");
	printf("|  Character Name              B  W  L  D    Health  |\n");
	printf("|====================================================|\n");
	
	if (status == 0) { // print all characters
		for (int i = 0; i < total_num; i++) {
			printf("|  %-26s %2d %2d %2d %2d %7d%%   |\n", character[i].name, character[i].no_battles, character[i].no_won,
				character[i].no_lost, character[i].no_drawn, character[i].health);
			printf("|----------------------------------------------------|\n");
		}
	}
	else if (status == 1) { // print only heroes
		for (int i = 0; i < total_num; i++) {
			if (character[i].hero == 1) {
				printf("|  %-26s %2d %2d %2d %2d %7d%%   |\n", character[i].name, character[i].no_battles, character[i].no_won,
					character[i].no_lost, character[i].no_drawn, character[i].health);
				printf("|----------------------------------------------------|\n");
			}
		}
	}
	else if (status == 2) { // print only villians
		for (int i = 0; i < total_num; i++) {
			if (character[i].hero == 0) {
				printf("|  %-26s %2d %2d %2d %2d %7d%%   |\n", character[i].name, character[i].no_battles, character[i].no_won,
					character[i].no_lost, character[i].no_drawn, character[i].health);
				printf("|----------------------------------------------------|\n");
			}
		}
	}

	printf("|====================================================|\n\n");
}

/*
  This function subtractes the damage from the health of character present at 
  index "position" in the character array 
*/
int update_character_health(CharacterRecord character[], int position, int damage) {
	int result;
	if (position < MAX_CHARACTERS) { // array bound check

		result = character[position].health - damage;
		if (result > 0) {
			character[position].health = result;
			return 1;
		}
		else {
			character[position].health = 0;
			return 0;
		}
	}
}

/*
  This function searches for the name in character array
  Returns index of character in array if it is found
  Else returns -1
*/
int find_character(char name[], CharacterRecord character[], int total_num) {

	for (int i = 0; i < total_num; i++) {
		if (strcmp(name, character[i].name) == 0) return i;
	}
	return -1;
}

/*
  This function first determine whether name is in character array
  Uses find_character function
  If found then restores the character health back to 100 and return 1
  else returns 0
*/
int reset_health(CharacterRecord character[], char name[], int total_num) {
	int index = find_character(name, character, total_num);

	if (index != -1) {
		character[index].health = 100;
		return 1;
	}
	return 0;
}

/*
  This function first checks the array bound whether MAX_CHARACTERS reached or not
  If not then Checks whether character already exists, if it does then return 0
  else if found add the character to the character array, updates its info according to the input
  and finally increments 1 to total number of rows in character array  and return 1
  else return -1
*/
int add_character(CharacterRecord character[], char name[], char secret_iden[], int status, int* total_num) {
	int index = find_character(name, character, *total_num);
	if (*total_num < MAX_CHARACTERS) {
		if (index != -1) { // character already exists
			return 0;
		}
		else if (index == -1) {
			*total_num = *total_num + 1; // increment total count
			int temp = *total_num;
			// add in arary
			character[temp - 1].health = 100;
			character[temp - 1].hero = status;
			strcpy(character[temp - 1].name, name);
			character[temp - 1].no_battles = 0;
			character[temp - 1].no_drawn = 0;
			character[temp - 1].no_lost = 0;
			character[temp - 1].no_won = 0;
			strcpy(character[temp - 1].secret_identity, secret_iden);

			return 1;
		}
	}
	else { // array of characters is full
		return -1;
	}
}

/*
  This function checks if character is present
  If yes then we rewrite the contents of the character at its index with the character present below it
  this is done in loop until the end of character array
  then we decrement the total count of character array rows
  then return 1
  Else we return 0
*/
int remove_character(CharacterRecord character[], char name[], int* total_num) {
	int index = find_character(name, character, *total_num);

	if (index != -1) { // character exists
		for (int i = index - 1; i < *total_num; i++) { // Shifting all elements one position down the array
			character[index].health = character[index + 1].health;
			character[index].hero = character[index + 1].hero;
			strcpy(character[index].name, character[index + 1].name);
			character[index].no_battles = character[index + 1].no_battles;
			character[index].no_drawn = character[index + 1].no_drawn;
			character[index].no_lost = character[index + 1].no_lost;
			character[index].no_won = character[index + 1].no_won;
			strcpy(character[index].secret_identity, character[index + 1].secret_identity);
			index++;
		}
		*total_num = *total_num - 1; // increment total count
		return 1;
	}
	else {
		return 0;
	}
}

/*
  This function prompts for the number of battle rounds between 1-5
   Then they battle until either health reaches 0 i.e, they die
   Or number of battles ends
   A random damage between 1-50 is generated and subtracted from the both characters healths 
   using the update_chracter_health function
   Finally we determine the winner of battle on basis of health remaining
   If either health is 0 we print the character death prompt
   If not then the character with more health wins and the respective prompt is printed
   If both health is same after battle then Draw happens and prompt printed
   Finally we update the attributes of no_battles, wins, lost, drawn accordingly in each condition 
*/
void do_battle(CharacterRecord character[], int pos1, int pos2) {
	int num_battles = 0;
	char temp[2];
	bool flag = false;

	srand(time(0));

	printf("Please enter number of battle rounds: ");
	gets(temp);
	num_battles = atoi(temp);
	while (!flag) { // prompts to enter battle round between 1-5 inclusive
		if (num_battles < 1 || num_battles > 5) {
			printf("Please enter a value between 1-5 inclusive.\n");
			printf("Please enter number of battle rounds: ");
			gets(temp);
			num_battles = atoi(temp);
		}
		else {
			flag = true;
		}
	}

	printf("\n-- Battle --\n\n");
	printf("%s versus %s - %d rounds: \n\n", character[pos1].name, character[pos2].name, num_battles);

	//starting fight algorithm
	int i = 1;

	while (num_battles > 0 && character[pos1].health > 0 && character[pos2].health > 0) {
		printf("\nRound %d: \n", i);

		// random number between 1-50 inclusive
		int damage1 = (rand() % (50)) + 1;
		int damage2 = (rand() % (50)) + 1;

		// update characters health
		update_character_health(character, pos1, damage1);
		update_character_health(character, pos2, damage2);

		// display round results
		printf("  > %s - Damage: %d - Current health: %d\n", character[pos1].name, damage1, character[pos1].health);
		printf("  > %s - Damage: %d - Current health: %d\n", character[pos2].name, damage2, character[pos2].health);

		// update the values for next iteration
		num_battles--;
		i++;
	}

	// determine winner
	printf("\n-- End of Battle --\n\n");

	// if either dies
	if (character[pos1].health == 0) {
		printf("-- %s has died!  :(\n\n", character[pos1].name);
		character[pos1].no_battles++;
		character[pos2].no_battles++;
		character[pos1].no_lost++;
		character[pos2].no_won++;

		if (character[pos2].health > character[pos1].health) {
			printf("** %s wins! **\n", character[pos2].name);
		}
	}
	else if (character[pos2].health == 0) {
		printf("-- %s has died!  :(\n\n", character[pos2].name);
		character[pos1].no_battles++;
		character[pos2].no_battles++;
		character[pos1].no_won++;
		character[pos2].no_lost++;

		if (character[pos1].health > character[pos2].health) {
			printf("** %s wins! **\n", character[pos1].name);
		}
	}

	// if one wins and other loses
	else if (character[pos1].health > character[pos2].health && (character[pos1].health != 0 || character[pos2].health != 0)) {
		printf("** %s wins! **\n", character[pos1].name);
		character[pos1].no_battles++;
		character[pos2].no_battles++;
		character[pos1].no_won++;
		character[pos2].no_lost++;
	}
	else if (character[pos2].health > character[pos1].health && (character[pos1].health != 0 || character[pos2].health != 0)) {
		printf("** %s wins! **\n", character[pos2].name);
		character[pos1].no_battles++;
		character[pos2].no_battles++;
		character[pos1].no_lost++;
		character[pos2].no_won++;
	}

	// in-case of draw after battles both opponents health will be same
	else if (character[pos1].health == character[pos2].health) {
		printf("Battle drawn!\n\n");
		character[pos1].no_battles++;
		character[pos2].no_battles++;
		character[pos1].no_drawn++;
		character[pos2].no_drawn++;
	}
}

/*
  This function open a new file if it alrady exists then rewrite it
  Then it copies the data from character array into the file
  Then it closes the file
  We copy the data according to the input file format
*/
void write_to_file(CharacterRecord character[], int total_num) {
	FILE* f = fopen("new_characters.txt", "w");
	int  i = 0;

	while (i < total_num && !feof(f)) {

		fprintf(f, "%s\n", character[i].name);

		fprintf(f, "%s\n", character[i].secret_identity);

		if (character[i].hero == 1) {
			fprintf(f, "h %d %d %d %d %d\n", character[i].no_battles, character[i].no_won, character[i].no_lost, character[i].no_drawn, character[i].health);
		}
		else {
			fprintf(f, "v %d %d %d %d %d\n", character[i].no_battles, character[i].no_won, character[i].no_lost, character[i].no_drawn, character[i].health);
		}
		i++;
	}
	fclose(f);

	// as the program is finished so exit the program immediately
	exit(0);
}