/*
  File: characterRecord.h 
  Author: Khalid Alghamdi
  Email Id: algka002@mymail.unisa.edu.pk
  Description: Programming Assignment 2 -- Programming with C --
  This is my own work as defined by the University's Academic Misconduct policy.

  DO NOT MODIFY THIS FILE!
    (You will need to complete the CharacterRecord data structure declaration
	 seen below - this is the ONLY change that is allowed to be made on this file.)
*/

#ifndef CHARACTERRECORD_H
#define CHARACTERRECORD_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define MAX_CHARACTERS 20    /* maximum number of character (hero and villain) entries */

#define STRING_LENGTH  25    /* maximum length of strings        */


typedef struct {
	/* You will need to complete this data structure declaration by
	   adding the data members as specified in the assignment specs.
	*/

	char name[STRING_LENGTH + 1]; // name of entity
	char secret_identity[STRING_LENGTH + 1];  // secret identity of entity
	int hero; // 1 for hero and 0 for villian
	int no_battles; // number of battles
	int no_won; // number of battles won
	int no_lost; // number of battles lost
	int no_drawn; // number of battles drawn
	int health; // health of entity

} CharacterRecord;



/* All the function prototypes in this file represent functions
   you will need to implement in order to complete this assignment.
   All functions must be implemented according to the specs provided.
   Function specifications are provided below and in the assignment handout.

   *** IMPORTANT: Please do not alter the function prototypes within this file.
*/



/* This function takes a file name and reads the contents of
   that file into the array of characters (heroes and villains)
   passed as a parameter into the function.

   The function returns the number of characters (heroes and villains)
   stored in the file.

   The file will already have been opened for reading before being
   passed into this function.
*/
int read_character_record(FILE*, CharacterRecord[]);


/* This function will take the character (heroes and villains) array, the
   number of characters (heroes and villains) stored in the array and the
   display status (i.e. display all characters, display villains, or display
   heroes) and will output the contents of the array to the screen accordingly.
   If the display status is 0, all characters will be displayed to the screen.
   If the display status is 1, only heroes will be displayed to the screen.
   if the display status is 2, only villains will be displayed to the screen.

   This function displays the information to the screen in the format specified
   in the assignment specifications under the section - 'Screen Format'.
*/
void display_characters(CharacterRecord[], int, int);


/* This function takes the character (heroes and villains) array, the
   character's position (index) in the array and an integer representing the
   amount of damage to the character's health.  This function updates the
   character's health status by subtracting the amount of damage from the health value.
   If the result is less than or equal to 0, return 0.  Otherwise, return 1.

   You should validate the position (index) of the character (second parameter)
   making sure it does not exceed array bounds.  If the position exceeds array
   bounds, an error message is displayed and the function returns -1.
*/
int update_character_health(CharacterRecord[], int, int);


/* This function will take the character's name, the array of characters (heroes and villains)
   and the number of characters (heroes and villains) stored in the array and will return the
   position (index) of the character found in the array of character (heroes and villains).

   If the character is not found, the function returns -1 (indicating the character could
   not be found).
*/
int find_character(char[], CharacterRecord[], int);


/* This function takes the array of characters (heroes and villains), the character's name,
   and the number of characters (heroes and villains) stored in the array and determines
   whether the character exists in the array of characters (heroes and villains).  If the
   character is found, the characters's health is reset back to 100 and the function
   returns 1 (indicating the character's health has been reset back to 100).
   If the character is not found in the characters (heroes and villains) array, the function
   returns 0 (indicating the character's health has not been reset).

   Hint:  this function MUST make use of the find_character function
*/
int reset_health(CharacterRecord[], char[], int);


/* This function takes the array of characters (heroes and villains),
   the character's name, secret_identity, hero status and the number of
   characters (heroes and villains) as a call-by-reference parameter.
   If the character does not already exist (i.e. a match is not found
   on character name), it adds the character into the array of characters (heroes and
   villains) (note that the health data member should be set to 100 and the other data
   members should be initialised to zero).  Increment the number of characters (heroes
   and villains) by one if the character is added into the array.

   The character must be added after the last character entry stored in the array.
   You will need to check that you are not exceeding array bounds.

   If the array of characters (heroes and villains) is full, the function does not add the
   new character and returns -1.

   If the character name already exists, the function does not add the
   new character and returns 0.

   If the character is successfully added to the array, the function
   returns 1.

   Hint:  this function MUST make use of the find_character function.
*/
int add_character(CharacterRecord[], char[], char[], int, int*);


/* This function takes the array of characters (heroes and villains),
   the character's name and the number of characters (heroes and villains)
   as a call-by-reference parameter and determines whether the character
   exists in the array of characters (heroes and villains).

   If the character is found, the character is removed from the character (heroes
   and villains) array at the position returned by function find_character and the
   function returns 1 (indicating the character has been successfully removed).

   The information must be removed maintaining the order of the
   character (heroes and villains) array (Hint: shift all elements one position
   down the array).

   If the character is not found in the characters (heroes and villains) array,
   the function returns 0 (indicating the character has not been removed).

   Hint:  this function MUST make use of the find_character function.
*/
int remove_character(CharacterRecord[], char[], int*);


/* This function takes the array of characters (heroes and villains) and the
   position of the two characters that are about to do battle (i.e. position is
   the location/index of the character stored in the array of characters.  This
   is useful so we can update the character's health value after every battle and
   battle statistics).

   This function prompts for and reads the number of battle rounds the heroes/villains
   will undertake (a number between 1-5 inclusive).  The function allows the heroes/villains
   to battle until either an opponent dies (health status is reduced to zero) or the number
   of battle rounds have been completed.  For each individual battle round, the hero/villain
   will sustain a certain amount of damage to their health rating.  The amount of damage
   sustained from the battle will be a randomly generated value between (0 - 50 inclusive).

   Algorithm is as follows-

		 while (number of battle rounds have not been completed and both oppenents are still alive) {

			  randomly generate a damage value sustained from battle and update opponent 1's health
			  value by subtracting the damage value.

			  randomly generate a damage value sustained from battle and update opponent 2's health
			  value by subtracting the damage value.

			  display opponent 1 round results
			  display opponent 2 round results
		 }

		 determine the winner of the battles - the character with the most health left at the end of
		 all battle rounds is the winner.

		 display the winner to the screen and also report if a character has died as a result of battle.

		 update opponent 1's battle statistics.  Hint: Increment the number of battles by one, number won, lost, drawn
												 accordingly.  We increment battles by one because battles may consist of
												 a number of battle rounds.

		 update oppenent 2's battle statistics.  Hint: Increment the number of battles by one, number won, lost, drawn
												 accordingly.  We increment battles by one because battles may consist of
												 a number of battle rounds.

   Hint:  this function MUST make use of the update_character_health function.
*/
void do_battle(CharacterRecord[], int, int);


/* This function takes the array of characters (heroes and villains)
   and the number of characters (heroes and villains) stored in the array as
   parameters and outputs the contents of the character (heroes and villains) array
   to a file in the same format as the input file.

   The file will need to be opened for writing in this function (and
   of course closed once all writing has been done).
*/
void write_to_file(CharacterRecord[], int);


#endif