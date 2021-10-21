#include <stdio.h>
#include <windows.h> //gotoxy() for xy co-ordinates
#include <conio.h>	 // delay(), getch()
#include <ctype.h>	 // toupper(), tolower()
#include <string.h>	 // strcmp(), strcpy(), strlen()
// Defining Global Variable
int b, valid=0;
// FUNCTION PROTOTYPE
void welcomeScreen(void); // Welcome Screen Prototype Function
void ex_it(void); // Close everything and shows homescreen
void title(void); // Title - Hospital Name
void dashboard(void); // Shows Option for CRUD operation
void addRecord(void); // Add Record
void viewRecord(void); // View or display record
void searchRecord(void); // Search for patients
void editRecord(void); // Edit patient's record
int listLoopRow(int row); // Loop patient's record
void addRecordItem(void); // Placed inside addRecord and editRecord to add new patients or edit existing patient
void recordTableHead(void); // Heaing for Table
void delRecord(void); // Delete existing record
void gotoxy(short x, short y) {
	//sets co-ordinates in (x,y)
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
//List of Global Variables
struct patient {
	int age, id;
	char gender, fname[20], lname[20], address[20], doctor[20], problem[20], contactNo[10];
};
struct patient p;
//Main Function
void main(void) {
	welcomeScreen();
	printf("\n\n\t\t\t\tEnter any key to continue...");
	getch();
	dashboard();
}

void welcomeScreen(void) {
	// Function for Welcome Screen
	printf("\n\n\n\n\n\n\t\t\t\t________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t        WELCOME TO       \t");
	printf("\n\t\t\t\t\t\t\tPATIENT MANAGEMENT SYSTEM\t");
	printf("\n\t\t\t\t\t\t\t       ABC HOSPITAL    \t\t");
	printf("\n\t\t\t\t________________________________________________________________________________");
}
void dashboard(void) {
	// Shows Option for CRUD operation
	int choice;
	printf("\n\n\n\t\t\t\t1. Add Patient Data");
	printf("\n\t\t\t\t2. Display Patient Record");
	printf("\n\t\t\t\t3. Search Patient Record");
	printf("\n\t\t\t\t4. Edit Patient Record");
	printf("\n\t\t\t\t5. Delete Patient Record");
	printf("\n\t\t\t\t6. Exit");
	printf("\n\n\t\t\t\tChoose from 1 to 6: ");
	scanf("%d", &choice);
	switch(choice) {
		case 1:
			addRecord();
			break;
		case 2:
			viewRecord();
			break;
		case 3:
			searchRecord();
			break;
		case 4:
			editRecord();
			break;
		case 5:
			delRecord();
			break;
		case 6:
			break;
		default:
			printf("\n\n\t\t\tOops !! Invalid Entry !! Enter again :");
			fflush(stdin); // To escape all the escape sequence. (Avoids unwanted inputs)
			getch();
			ex_it();
			break;
	}
} // dashboard ends
void addRecord(void) {
	// To record patient's data
	system("cls"); // Clear everything in console
	title(); // calls title and shows hospital's name
	char ans;
	FILE *fp; // taking fp file pointer
	fp = fopen("PatientsRecord.dat","a"); // open file in append mode
	printf("\n\n\t\t\t!!!!!!!!!! Add Patients Record !!!!!!!!!!\n");
	addRecordItem(); // Add patient's all data
	fprintf(fp, "%i %s %s %c %i %s %s %s %s\n", p.id, p.fname, p.lname, p.gender, p.age, p.address, p.contactNo, p.problem, p.doctor); // Print in file
	printf("\n\n\t\t\t.....Information Record Successful ...");
	fclose(fp); // closing file pointer after successfull record entry
sd:
	getch(); // hold screen
	printf("\n\n\t\t\tDo you want to add more [Y/N]?? "); // Asking user, if they want to add more record
	scanf(" %c", &ans);
	if (toupper(ans)=='Y')
		addRecord(); // If user wants, again calling addRecord();
	else if (toupper(ans)=='N') {
		ex_it(); // If user don't want, then go back to home
	}
} // Add Record Ends
void addRecordItem(void) { // This is placed inside addRecord() to record patient's available data
	printf("\n\t\t\tID: ");
	fflush(stdin);
	scanf("%i", &p.id); // Patient's id
A:
	fflush(stdin);
	printf("\n\n\t\t\tFirst Name: ");
	scanf("%s", p.fname);
	p.fname[0]=toupper(p.fname[0]);
	if(strlen(p.fname)>20 || strlen(p.fname)<2)	{ // Validating length of first name
		printf("\n\t Invalid !! The max range for first name is 20 and min is 2");
		goto A; // If not meet requirement, process repeat again (Goto A)
	}
B:
	printf("\n\n\t\t\tLast Name: ");
	scanf("%s", p.lname); // For last name
	p.lname[0]=toupper(p.lname[0]);
	if(strlen(p.lname)>20 || strlen(p.lname)<2)	{
		printf("\n\t Invalid !! The max range for last name is 20 and min is 2");
		goto B; // If not meet requirement, process repeat again (Goto B)
	}
C:
	printf("\n\t\t\tGender[M|F]:");
	scanf(" %c", &p.gender); // For Gender
	if(toupper(p.gender)=='M'|| toupper(p.gender)=='F') // change input string to uppercase
		valid = 1; // if entered 'm' or 'M' or 'f' or 'F' , valid = 1
	else
		valid = 0; // otherwise valid = 0
	if (!valid) {
		printf("\n\t\t\tGender contains Invalid Character. Enter either F or M : ");
		goto C; // if valid is not 1, again repeat the process, (Goto C)
	}
	/* ********************* Age ************************ */
D:
	printf("\n\t\t\tAge: ");
	scanf(" %i", &p.age);
	/* ********************* Address ************************ */
E:
	printf("\n\t\t\tAddress: ");
	scanf("%s", p.address);
	p.address[0]=toupper(p.address[0]); // making first letter uppercase
	if(strlen(p.address)>30||strlen(p.address)<3) { // length mustn't be > 30 ir < 3
		printf("\n\n\t\t\tInvalid : Address must be max of 20 Character and 4 minimum");
		goto E; // if condition not meet, repeat process again (Goto E)
	}
F:
	printf("\n\t\t\tPhone Number: ");
	scanf("%s", p.contactNo);
	if (strlen(p.contactNo)>10||strlen(p.contactNo)!=10) { // Phone number must be exact of 10 character
		printf("\n\t Oops !! Phone Number must be of 10 numbers");
		goto F;
	} else {
		for (b=0; b<strlen(p.contactNo); b++) {
			if (!isalpha(p.contactNo[b]))
				// Phone number must only contains numbers
				valid = 1;
			else {
				valid = 0;
				break;
			}
		}
		if(!valid) {
			printf("\n\n\t\t\tPhone number mustn't contain any character'");
			// If phone number contains any other character, then repeat process, (Goto F)
			goto F;
		}
	}
G:
	printf("\n\t\t\tProblem: ");
	scanf("%s", p.problem);
	p.problem[0]= toupper(p.problem[0]); // making first letter uppercase
	if(strlen(p.problem)>20||strlen(p.problem)<3) {
		printf("\n\n\t\t\tProblem can't be max than 20 characters or less than 3'");
		goto G;
	} else {
		for (b=0; b<strlen(p.problem); b++) {
			if (isalpha(p.problem[b])) {
				// Problem must only contain alphabets
				valid = 1;
			} else {
				valid = 0;
				break;
			}
		}
		if(!valid) {
			printf("\n\n\t\t\tProblem contain Invalid Character : Enter again");
			goto G; // If problem contains invalid character, repeat again (Goto G)
		}
	}
H:
	printf("\n\t\t\tPrescribed Doctor: ");
	scanf("%s", p.doctor);
	p.doctor[0]=toupper(p.doctor[0]); // making first letter uppercase
	if(strlen(p.doctor)>30||strlen(p.doctor)<3) { // Validating string length limit
		printf("\n\n\t\t\tOops!! Doctor name must only contain upto 30 alphabets");
		goto H; // If validation failed, repeat again (Goto H)
	}
}
void ex_it(void) {
	// function to clear everything in console and call welcomescreen and dashboard
	system("cls");
	welcomeScreen();
	dashboard();
}
// title Function
void title(void) {
	printf("\n\n\t\t\t************************ ABC HOSPITAL *************************\n");
}
int listLoopRow(int row) {
	// This function is used inside while loop, to print the user's record in each line
	gotoxy(5,row);
	printf("%i", p.id);
	gotoxy(10, row);
	printf("%s %s", p.fname, p.lname);
	gotoxy(25, row);
	printf("%c", toupper(p.gender));
	gotoxy(35, row);
	printf("%i", p.age);
	gotoxy(45, row);
	printf("%s",p.address);
	gotoxy(60, row);
	printf("%s", p.contactNo);
	gotoxy(80, row);
	printf("%s", p.problem);
	gotoxy(95, row);
	printf("%s", p.doctor);
}
void recordTableHead(void) {
	// This is used before while loop, to print the table heading
	printf("\n____________________________________________________________________________________________________________________\n\n");
	gotoxy(5,10); // Go directly to (x,y) co-ordinates
	printf("ID");
	gotoxy(10,10);
	printf("Full Name");
	gotoxy(25,10);
	printf("Gender");
	gotoxy(35,10);
	printf("Age");
	gotoxy(45,10);
	printf("Address");
	gotoxy(60,10);
	printf("Phone No");
	gotoxy(80,10);
	printf("Problem");
	gotoxy(95,10);
	printf("Prescribed Doctor\n");
	printf("____________________________________________________________________________________________________________________");
}
/* ********************* View Records ************************ */
void viewRecord(void) {
	int row = 13; // This will assign value to argument below to listLoopRow(Row)
	system("cls"); // Clear the whole screen
	FILE *fp; // Opening file pointer fp
	fp = fopen("PatientsRecord.dat","r"); // Open file in read mode only
	printf("\n\n\n\n\n\n\t\t************************** ABC Hospital - Patients Record *************************\n");
	recordTableHead(); // Heading Title For Records
	while (fscanf(fp, "%i %s %s %c %i %s %s %s %s\n", &p.id, p.fname, p.lname, &p.gender, &p.age, p.address, p.contactNo, p.problem, p.doctor)!=EOF) {
		listLoopRow(row); // Display the available results in row of each patient
		row++; // Increase value of row once, function is called. Then another list will print in next line
	}
	printf("\n\n____________________________________________________________________________________________________________________");
	fclose(fp); // Closing file ponter after displaying record
	printf("\n\n\t\t\t\t    Enter any key to continue..."); // Asking user to press any key
	getch(); // Hold screen until user press any key
	ex_it();// Takes back to main screen
} // View Record Ends
/* ********************* Search Records ************************ */
void searchRecord(void) {
	int searchID;
	system("cls");
	FILE *fp;
	int row = 12;
	char ans;
	int count = 0; // It is used to show total available records
	fp = fopen("PatientsRecord.dat","r"); // open file in read mode
	printf("\n\n\n\n\n\n\t\t************************** ABC Hospital - Search Patient *************************\n");
	gotoxy(12,8);
	fflush(stdin);
	printf("\n\t\t\t\t\t Enter Patient's ID : ");
	scanf("%i",&searchID); // Takes user ID for search
	system("cls"); // Once data read, clearing screen again
	printf("\n\n\n\n\n\t\t************************** ABC Hospital - Search Patient *************************\n");
	printf("\n\t\t\t\t\t Patient Searched for: %i \n", searchID);
	recordTableHead(); // Record Heading - Display the heading of table

	while (fscanf(fp, "%i %s %s %c %i %s %s %s %s\n", &p.id, p.fname, p.lname, &p.gender, &p.age, p.address, p.contactNo, p.problem, p.doctor)!=EOF) {
		if(p.id == searchID) {
			listLoopRow(row); // It takes row = 12 at first and row++ later
			row++; // Display the available results in row of each patient
			count++; // increasing count value after each successfull finding of ID
		}
	}
	printf("\n\n\t\t\t\t\t\tTotal Patients found : %d", count);
	fclose(fp); // closing file pointer
I:
	printf("\n\n\t\t\t\t\t   Enter any key to continue...");
	getch();
	printf("\n\n\t\t\t\t\t   Do you want to view more [Y/N]?? ");
	scanf(" %c", &ans);
	if (toupper(ans)=='Y')
		searchRecord(); // If user want to search more, then again call searchRecord()
	else if (toupper(ans)=='N') {
		ex_it(); // If not, Go back to main memu
	} else {
		printf("\n\tInvalid Input. \n");
		goto I;
	}
} // Search Record Ends
/* ********************* Edit Records ************************ */
void editRecord(void) {
	// to edit we need another file pointer, taking *tf (temporary file)
	FILE *fp, *tf;
	int i,b,valid=0;
	int searchID;
	int row = 13;
	system("cls");
	printf("\n\n\n\n\t\t************************** ABC Hospital - Edit Record *************************\n");
	tf=fopen("temp_PatientsRecord.dat","w+"); // opening file pointer 'tf' in write and read more
	fp = fopen("PatientsRecord.dat", "r"); // opening file pointer 'fp' in read more only
	if (fp==NULL) {
		// when file pointer fp doesn't open ( Returns Null)
		printf("\n\t Cannot Open File !!");
		ex_it(); // Go back to main memu
	} else {
		// if file pointer fp exists
		gotoxy(12,6);
		fflush(stdin); // Avoid unwanted escape sequence as unwanted input
		printf("\n\t\t\t\t\t Enter Patient's ID : ");
		scanf("%i",&searchID); // ID of patient's to edit
		gotoxy(12,10);
		if (tf==NULL) {
			// when file pointer tf doesn't open ( Returns Null)
			printf("\n\t Cannot Open File !!");
			ex_it(); // Go back to main memu
		}
		while (fscanf(fp, "%i %s %s %c %i %s %s %s %s\n", &p.id, p.fname, p.lname, &p.gender, &p.age, p.address, p.contactNo, p.problem, p.doctor)!=EOF) {
			// looping in file pointer fp to check each patient's record until END OF FILE
			if(p.id == searchID) {
				// When entered searchID and patient's ID meet
				valid=1; // Assigning valid value to 1
				system("cls");
				printf("\n\n\n\n\n\t\t************************** ABC Hospital - Record Found *************************\n");
				printf("\n\t\t\t\t\t Record Found for: %i \n", searchID);
				recordTableHead(); // Record Heading
				listLoopRow(row); // Print available data - loop data
				row++;
				addRecordItem(); // add data/edit data
				// After successfull entry of record, print the data inside the file pointer 'tf' temporary file
				fprintf(tf, "%i %s %s %c %i %s %s %s %s\n", p.id, p.fname, p.lname, p.gender, p.age, p.address, p.contactNo, p.problem, p.doctor);
				printf("\nUpdated Successfully");
			} else {
				// if searchID not matched, print all the avaibale records to temporary file (This will exclude whose record meets)
				fprintf(tf, "%i %s %s %c %i %s %s %s %s\n", p.id, p.fname, p.lname, p.gender, p.age, p.address, p.contactNo, p.problem, p.doctor);
			}
		}
		if(!valid) { // If not searched ID not matched
			printf("\n\t\t No Record Found...");
		}
		// Closing all file pointers
		fclose(tf);
		fclose(fp);
		remove("PatientsRecord.dat"); // remove existing file
		rename("temp_PatientsRecord.dat","PatientsRecord.dat"); // Renaming temporaty file to original name
		getch();
		ex_it(); // Go back to main memu
	}
}
void delRecord() {
	int notValid = 0;
	char ch;
	int searchID;
	int found = 0;
	int confirmID;
	int row = 13;
	system("cls");
	FILE *fp, *tf; // Opening both file pointer
	tf = fopen("temp_PatientsRecord2.dat", "w+"); // Write and Read modes
	fp = fopen("PatientsRecord.dat", "r"); // Read mode to original file
	printf("\n\n\n\n\n\t\t************************** ABC Hospital - Delete Record *************************\n");
	gotoxy(12,6);
	fflush(stdin);
	printf("\n\t\t\t\t\t Search For Patient's ID : ");
	scanf("%i", &searchID);
	fflush(stdin);
	printf("\n\n\t\t\t\t\t Enter age again to confirm : ");

	scanf("%i", &confirmID); // To confirm with search ID entered before
	if(searchID==confirmID) {
		// If both searchID and ConfirmID matched while loop will run
		while (fscanf(fp, "%i %s %s %c %d %s %s %s %s\n", &p.id, p.fname, p.lname, &p.gender, &p.age, p.address, p.contactNo, p.problem, p.doctor)!=EOF) {
			if(searchID!=p.id) {
				fprintf(tf, "%i %s %s %c %i %s %s %s %s\n", p.id, p.fname, p.lname, p.gender, p.age, p.address, p.contactNo, p.problem, p.doctor);
			} else {
				found = 1; // when ID didn't match with existing records
			}
		}
	} else {
		// if searchID and confirmID not matched
		notValid = 1; // It was 0 before
	}
	if(notValid || found!=1) {
		// if searchID and confirmID not matched or not ID matched with existing records
		// close all the file pointers
		fclose(fp);
		fclose(tf);
		// Remove the remporary files, no need to copy any data in this condition
		remove("temp_PatientsRecord2.dat");
		if(notValid)
			// If can't confirm searchID and confirmID
			printf("\n\n\t\t\t\t\t Sorry you can't confirm age");
		else
			// If ID didn't match the record
			printf("\n\n\t\t\t\t\t Oops !! Record Not Found...");
		printf("\n\n\t\t\t\t\t Enter any key to continue : ");
		getch();
		ex_it();
	}
	if(found) {
		// If record found
		printf("\n\n\t\t\t\t\t Record Deleted Successfully !!");
		// close all file pointer
		fclose(fp);
		fclose(tf);
		remove("PatientsRecord.dat"); // remove existing file
		// change temporary file to original name
		rename("temp_PatientsRecord2.dat","PatientsRecord.dat");
		printf("\n\n\t\t\t\t\t Enter any key to continue : ");
		getch();
		// After successfull deletion, call viewRecord() to show the available records
		viewRecord();
	}
}
