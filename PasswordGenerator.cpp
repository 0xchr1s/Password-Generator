#include <iostream>
#include <random>
#include <limits>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
#include <fstream>



// Possible characters for the password 

const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()-_=+[]{}<>?/";



std::string random_string (size_t length){
	

//Random Number Generator
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<> distribution(0, characters.size() - 1);


// Build random password character by character
	std::string random_string;
	for (size_t i = 0; i < length ; ++i){
		random_string += characters[distribution(generator)];
	}

	return random_string;
}

// ** Design for the password generator 
void banner() {

	std::cout << "\033[38;2;64;224;208m";
	std::cout << R"(
            ____                                          __   ______                           __
           / __ \____ ____________      ______  _________/ /  / ____/__  ____  ___  _________ _/ /_____  _____
          / /_/ / __ `/ ___/ ___/ | /| / / __ \/ ___/ __  /  / / __/ _ \/ __ \/ _ \/ ___/ __ `/ __/ __ \/ ___/
         / ____/ /_/ (__  |__  )| |/ |/ / /_/ / /  / /_/ /  / /_/ /  __/ / / /  __/ /  / /_/ / /_/ /_/ / /
        /_/    \__,_/____/____/ |__/|__/\____/_/   \__,_/   \____/\___/_/ /_/\___/_/   \__,_/\__/\____/_/   )";

	std::cout << "\033[0m" << "\n";
 
}


void underlined(){

	std::cout << "───────────────────────────────────────────────────────────────────────────────────────────────────────── \n";
}


// Loading bar for the generated password

void bar(){


	std::string loading_bar = "█";
	std::string empty_bar = "░";

	std::cout << "\nPassword will be generated...\n\n";
	std::cout << "[";

	for (int i = 0; i < 25; i++) {
		std::cout << empty_bar;
	}

	std::cout << "]";
	std::cout << "\r[";

	for (int i = 0; i < 25; i++) {
		std::cout << loading_bar << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(60));
	}

	std::cout << "] 100%\n";
}



//User is forced to press only ENTER (for error handling)
void press_enter(){

	std::string input ;

	do {

		std::getline(std::cin, input);

		if (!input.empty()){
			std::cout << "Please press ENTER only: ";
		}
	} while (!input.empty());
}




// Console loading animation for entropy analysis
void entropy_analyse(){


	std::string loading_bar = "█";
	std::string empty_bar = "░";

	std::cout << "\nStart security check...\n\n";
	std::cout << "[";

	for (int i = 0; i < 25; i++) {
		std::cout << empty_bar;
	}

	std::cout << "]";
	std::cout << "\r[";

	for (int i = 0; i < 25; i++) {
		std::cout << loading_bar << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(70));
	}

	std::cout << "] 100%\n";
}



// Shows the list for password security
void show_security_table (){


	std::cout << "\nPASSWORD STRENGTH TABLE\n";
	std::cout << "--------------------------------------------------\n";

	std::cout << "< 40       \033[38;2;255;102;102mVERY WEAK\033[0m\n";

	std::cout << "40 - 59    \033[38;2;255;102;102mWEAK\033[0m\n";

	std::cout << "60 - 79    \033[38;2;255;165;0mMODERATE\033[0m\n";

	std::cout << "80 - 99    \033[38;2;144;238;144mSTRONG\033[0m\n";

	std::cout << "100 - 127  \033[38;2;144;238;144mVERY STRONG\033[0m\n";

	std::cout << ">= 128     \033[38;2;0;100;0mEXTREMELY STRONG\033[0m\n";

	std::cout << "--------------------------------------------------\n\n";

}



// The password will be saved to a .txt file.
// Users can save their generated or manually setted passwords directly

void password_txt(const std::string& password, double entropy){

	std::ofstream file("password.txt");

	file << "YOUR SAVED PASSWORD\n\n";
	file << "Password: " << password << "\n";
	file << "Entropy: " << entropy << " Bit\n";

	file.close();

	system("explorer.exe password.txt");
}




int main(){

	
	int password_selection;
	int max1{0};	
	int password_length; 
	int password_manual{1};
	int password_generated{2};
	
	
	std::string generated_password; 
	std::string password_check;
	double entropy_manual{0.0};
	double entropy{0.0};
	char entropy_selection{0};
	char password_save{0};

	std::string f_password;
	double f_entropy{0.0};


// The user can choose between entering their password manually or having it generated

	banner();
	underlined();


	std::cout << "\n[1] CREATE A PASSWORD \n\n"
	<< "[2] GENERATE A PASSWORD \n";

	do {
		std::cout << "\n => ";


		if (!(std::cin >> password_selection)){
			
            std::cin.clear(); 															  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			 
            continue;																	
        }

    } while (password_selection < 1 || password_selection > 2);



    std::cout << "\033[2J\033[1;1H";





// Users can choose a password manually


    std::string password_manual_check;
    std::string password_manual_confirm;


    if (password_selection == password_manual){


    	banner();
    	underlined();



    	std::cout << "\n    SET PASSWORD \n";
    	std::cout << "  ----------------\n\n";

    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    	do {
    		std::cout << "=> ";
    		std::getline(std::cin, password_manual_check);

    		if (password_manual_check.empty()){
    			std::cout << "\n\033[38;2;255;102;102mPassword cannot be empty.\033[0m\n\n";
    		}

    	} while (password_manual_check.empty());


    	std::cout << "\n\n   CONFIRM YOUR PASSWORD \n";
    	std::cout << "  -----------------------\n\n";


    	do {
    		std::cout << "=> ";

    		std::getline(std::cin, password_manual_confirm);



    		if (password_manual_check != password_manual_confirm){
    			std::cout << "\n\033[38;2;255;102;102mPASSWORD wrong - please repeat it\033[0m\n";

    		}

    	} while (password_manual_check != password_manual_confirm);

    	

    	std::cout << "\033[2J\033[1;1H";

    	banner();
    	underlined();


		std::cout << "\nPASSWORD CONFIRMED\n\n";

    	f_password = password_manual_check;



// Users can have their password security checked

    	std::cout << "\nWould you like to analyze the security of your password? (y/n) \n";

    	do {
    		std::cout << "\n=> ";
    		std::cin >> entropy_selection;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			 

} while (entropy_selection != 'y'&& 
	entropy_selection != 'Y'&&
	entropy_selection != 'n'&&
	entropy_selection != 'N');


if (entropy_selection == 'y' || entropy_selection == 'Y'){

	std::cout << "\033[2J\033[1;1H";
	banner();
	underlined();


	entropy_analyse();


	entropy_manual = password_manual_check.size() * std::log2(characters.size());	// Entropy is calculated (indicates how secure a password is, measured in bits)

	f_entropy = entropy_manual;

	std::cout << "\nPassword: \033[38;2;64;224;208m" << password_manual_check << "\033[0m\n";
	std::cout << "\nEntropy: " << entropy_manual << " Bit" << "\n";



	if (entropy_manual >= 128 ){
		std::cout << "Password strength: \033[38;2;0;100;0mEXTREMELY STRONG\033[0m\n";

	} else if (entropy_manual >= 100) {
		std::cout << "Password strength: \033[38;2;144;238;144m VERY STRONG\033[0m\n";

	}else if (entropy_manual >= 80) {
		std::cout << "Password strength: \033[38;2;144;238;144mSTRONG\033[0m\n";

	}else if (entropy_manual >= 60) {
		std::cout << "Password strength: \033[38;2;255;165;0mMODERATE\033[0m\n"; 

	}else if (entropy_manual >= 40) {
		std::cout << "Password strength: \033[31mWEAK\033[0m\n";

	}else {
		std::cout << "Password strength: \033[31mVERY WEAK\033[0m\n";
	}

	std::cout << "\n\nPlease enter \033[38;2;64;224;208m!table\033[0m to view the entropy table and check your password strength.\n";




// shows Entropy list with the command !table

	std::string input1;

	do{
		std::cout << "\n=> ";
		std::cin >> input1;

		if (input1 != "!table"){
			std::cout << "\n\033[38;2;255;102;102mPlease enter only !table\033[0m\n";

		}

	} while (input1 != "!table");

	show_security_table();

	std::cout << "\n   Press ENTER to continue... \n\n";
		 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');				
		 press_enter();														   

		}	
	}





// Users can have a password generated

	if (password_selection == password_generated){
		banner();
		underlined();

		std::cout << "\nHow long should your password be?  \n\n"
		<< " [1] Password length of 12 characters\n"
		<< " [2] Password length of 15 characters\n"
		<< " [3] Password length of 20 characters\n\n";
		do {
			std::cout << "\nChoose between 1-3:  ";


			if (!(std::cin >> password_length)){
				
	            std::cin.clear(); 															 
	            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			 
	            continue;																	
	        }

	    } while (password_length < 1|| password_length > 3);

	    std::cout << "\033[2J\033[1;1H";

	    banner();

	    underlined();



// The user can choose between 3 different password lengths for their generated password

	    if (password_length == 1) {
	    	max1=12;

	    	std::cout << "\n  Your generated password will contain " << max1 << " characters\n\n";
	    }
	    else if (password_length == 2){
	    	max1=15;

	    	std::cout << "\n  Your generated password will contain " << max1 << " characters\n\n";
	    }

	    else if (password_length == 3){
	    	max1=20;

	    	std::cout << "\n  Your generated password will contain " << max1 << " characters\n\n";	
	    }

		// Press ENTER to generate your password
	    std::cout << "\n   Press ENTER to generate your password: \n\n";
		 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			
		 press_enter();																   



		 std::cout << "\033[2J\033[1;1H";



		 banner();
		 underlined();


//The generated password for the user is created here

		 bar();

		 generated_password = random_string(max1);

		 f_password = generated_password;

		 std::cout << "\n\033[38;2;64;224;208mPASSWORD:\033[0m " << generated_password << "\n"; 
		 
		 std::cout << "\n\nPress ENTER to continue...";
		 press_enter();	


		 std::cout << "\033[2J\033[1;1H";
		 banner();

		 underlined();




		 std::cout << "\nWould you like to analyze the security of your password? (y/n) \n";


		 do{


		 	std::cout << "\n=> ";
		 	std::cin >> entropy_selection;

		 	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


		 } while (entropy_selection != 'y' &&
		 	entropy_selection != 'Y' &&
		 	entropy_selection != 'n' &&
		 	entropy_selection != 'N');



		 if (entropy_selection == 'y' || entropy_selection == 'Y'){



		 	std::cout << "\033[2J\033[1;1H";
		 	banner();
		 	underlined();

		 	entropy_analyse();

		 	entropy = max1 * std::log2(characters.size());		

		 	f_entropy = entropy;



		 	std::cout << "\nPassword: \033[38;2;64;224;208m" << generated_password << "\033[0m\n";
		 	std::cout << "\nEntropy: " << entropy << " Bit\n";


		 	if (entropy >= 128 ){
		 		std::cout << "Password strength: \033[38;2;0;100;0mEXTREMELY STRONG\033[0m\n";
		 	}else if (entropy >= 100) {
		 		std::cout << "Password strength: \033[38;2;144;238;144m VERY STRONG\033[0m\n";

		 	}else if (entropy >= 80) {
		 		std::cout << "Password strength: \033[38;2;144;238;144mSTRONG\033[0m\n";

		 	}else if (entropy >= 60) {
		std::cout << "Password strength: \033[38;2;255;165;0mMODERATE\033[0m\n"; 

	}else if (entropy >= 40) {
		std::cout << "Password strength: \033[31mWEAK\033[0m\n";

	}else{
		std::cout << "Password strength: \033[31mVERY WEAK\033[0m\n";
	} 
	



	std::cout << "\n\nPlease enter \033[38;2;64;224;208m!table\033[0m to view the entropy table and check your password strength.\n";


 
	std::string input2;

	do{
		std::cout << "\n=> ";
		std::cin >> input2;

		if (input2 != "!table"){
			std::cout << "\n\033[38;2;255;102;102mPlease enter only !table\033[0m\n";

		}

	} while (input2 != "!table");

	show_security_table();


	std::cout << "\n   Press ENTER to continue... \n\n";
		 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			
		 press_enter();															   

		}	

	}



	std::cout << "\033[2J\033[1;1H";
	banner();
	underlined();	


//The password can be saved in a .txt file

	std::cout << "\n Do you want to save the password to a .txt file?  (y/n)\n\n";

	do{
		std::cout << "=> ";
		std::cin >> password_save;

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	} while (password_save != 'y' &&
		password_save != 'Y' &&
		password_save != 'n' &&
		password_save != 'N');


	if (password_save == 'y' || password_save == 'Y'){
		password_txt(f_password, f_entropy);

		std::cout << "\nYour password has been successfully saved.\n";

		std::cout << "\nTHANK YOU FOR USING THE PASSWORD GENERATOR.\n";
	} else {

		std::cout << "\033[2J\033[1;1H";
		banner();
		underlined();		
		std::cout << "\nTHANK YOU FOR USING THE PASSWORD GENERATOR.\n\n";
		std::cout << "\n\033[38;2;64;224;208mYOUR PASSWORD:\033[0m " << f_password << "\n\n"; 
	}
	

	return 0;

}

