/*
 * @file     delimiters.cpp
 * @author   Phillip Wu
 * @date     2019 - 10 - 06
 * @version  1.2
 * @since 1.2 Fixed bug with returning true and false at wrong points in code
 * @since 1.1 Changed to follow Marmoset's main() function to output 1s and 0s
 */

#include <iostream>
#include <cassert>
#include "project_1.hpp"

//function declarations
int main();
void print_program();
bool does_delimiter_match(char delimiter);
bool do_delimiters_nest();

//function definitions
int main(){
	print_program();
	std::cout << does_delimiter_match('(') << std::endl;
	std::cout << does_delimiter_match('[') << std::endl;
	std::cout << does_delimiter_match('{') << std::endl;
	std::cout << do_delimiters_nest() << std::endl;
	return 0;
}

//Your function definitions go here

//Prints out whatever is in test_code character by character
void print_program(){
	ece150::start_reading_file();
	while(!ece150::at_eof()){
		std::cout << ece150::get_next_character();
	}
}

/*
 * Takes character type delimiter called delimiter
 * Checks to see if each open delimiter has a closing delimiter
 * If it does return true
 * Otherwise return false
 */
bool does_delimiter_match(char delimiter){
	int round = 0, square = 0, curly = 0;
	bool unmatched = false;
	ece150::start_reading_file();
	while(!ece150::at_eof()){
		char c = ece150::get_next_character();
		if(delimiter == '('){
			if(c == '('){
				round++;
			}
			else if(c == ')' && round <= 0){
				std::cout << "Unmatched )" << std::endl;
				unmatched = true;
			}
			else if(c == ')' && round >0){
				round--;
			}
		}
		else if (delimiter == '['){
			if(c == '['){
				square++;
			}
			else if(c == ']' && square <= 0){
				std::cout << "Unmatched ]" << std::endl;
				unmatched = true;
			}
			else if(c == ']' && square >0){
				square--;
			}
		}
		else if(delimiter == '{'){
			if(c == '{'){
				curly++;
			}
			else if(c == '}'&& curly <= 0){
				std::cout << "Unmatched }" << std::endl;
				unmatched = true;
			}
			else if(c == '}' && curly >0){
				curly--;
			}
		}
		else{
			return false;
		}
	}
	if(round > 0){
		std::cout << "Missing ";
		for(int i = 0; i < round; i++){
			std::cout << ")";
		}
		std::cout << std::endl;
		return false;
	}
	else if(square > 0){
		std::cout << "Missing ";
		for(int i = 0; i < square; i++){
			std::cout << "]";
		}
		std::cout << std::endl;
		return false;
	}
	else if(curly > 0){
		std::cout << "Missing ";
		for(int i = 0; i < curly; i++){
			std::cout << "}";
		}
		std::cout << std::endl;
		return false;
	}
	if(unmatched == true){
		return false;
	}
	return true;
}

/*
 * Checks to see if the delimiters are also properly nested within each other
 * If they are then return true
 * Otherwise return false
 */
bool do_delimiters_nest(){
	bool unmatched = false;
	ece150::start_reading_file();
	ece150::initialize_table();
	while(!ece150::at_eof()){
		char c = ece150::get_next_character();
		if(c == '(' || c == '[' || c == '{'){
			ece150::place_character(c);
		}
		else if(c == ')'){
			if(ece150::get_right_most_character() == '('){
				ece150::erase_right_most_character();
			}
			else{
				std::cout << "Unmatched )" << std::endl;
				unmatched = true;
			}
		}
		else if(c == ']'){
			if(ece150::get_right_most_character() == '['){
				ece150::erase_right_most_character();
			}
			else{
				std::cout << "Unmatched ]" << std::endl;
				unmatched = true;
			}
		}
		else if(c == '}'){
			if(ece150::get_right_most_character() == '{'){
				ece150::erase_right_most_character();
			}
			else{
				std::cout << "Unmatched }" << std::endl;
				unmatched = true;
			}
		}
	}
	if(!ece150::is_table_empty()){
		std::cout << "Missing ";
				while(!ece150::is_table_empty()){
					if(ece150::get_right_most_character() == '('){
						std::cout << ")";
						ece150::erase_right_most_character();
					}
					else if(ece150::get_right_most_character() == '['){
						std::cout << "]";
						ece150::erase_right_most_character();
					}
					else if(ece150::get_right_most_character() == '{'){
						std::cout << "}";
						ece150::erase_right_most_character();
					}
				}
				std::cout << std::endl;	}
	else{
		if(unmatched == true){
			return false;
		}
		else{
			return true;
		}
	}
	return false;
}

