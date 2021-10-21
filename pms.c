#include <stdio.h>
#include <windows.h> //gotoxy()
#include <conio.h>	 // delay(), getch()
#include <ctype.h>	 // toupper(), tolower()
#include <string.h>	 // strcmp(), strcpy(), strlen()
#include <stdlib.h>	 // Dynamic Memory Allocation
// Defining Global Variable
char ans = 0;
int b, valid=0;
// FUNCTION PROTOTYPE
void welcomeScreen(void); // Welcome Screen Prototype Function
void ex_it(void);
void title(void);
void dashboard(void);
void addRecord(void);
void viewRecord(void);
void searchRecord(void);
void editRecord(void);
int listLoopRow(int row);
void addRecordItem(void);
void recordTableHead(void);
void delRecord(void);
void gotoxy(short x, short y) {
	COORD pos = {x,y}; //sets co-ordinates in (x,y)
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
//List of Global Variables
struct patient {
	int age, id;
	char gender, fname[20], lname[20], address[20], doctor[20], problem[20], contactNo[10];
};
struct patient p, temp_c;
//Main Function
void main(void) {
	welcomeScreen();
	printf("\n\n\t\t\t\tEnter any key to continue...");
	getch();
	dashboard();
}
// Function Welcome Screen
void welcomeScreen(void) {
	printf("\n\n\n\n\n\n\t\t\t\t________________________________________________________________________________");
	printf("\n\n\t\t\t\t\t\t\t        WELCOME TO       \t");
	printf("\n\t\t\t\t\t\t\tPATIENT MANAGEMENT SYSTEM\t");
	printf("\n\t\t\t\t\t\t\t       ABC HOSPITAL    \t\t");
	printf("\n\t\t\t\t________________________________________________________________________________");
}

void dashboard(void) {
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
			scanf("%*[^\n]"); // To bypass default input after operation
			getch();
			ex_it();
			break;
	}
}
void addRecord(void) {
	system("cls");
	title();
	char ans;
	FILE *fp;
	fp = fopen("PatientsRecord.dat","a"); // open file in append mode
	printf("\n\n\t\t\t!!!!!!!!!! Add Patients Record !!!!!!!!!!\n");
	addRecordItem();
	fprintf(fp, "%i %s %s %c %i %s %s %s %s\n", p.id, p.fname, p.lname, p.gender, p.age, p.address, p.contactNo, p.problem, p.doctor);
	printf("\n\n\t\t\t.....Information Record Successful ...");
	fclose(fp);

	//fp file is closed
sd:
	getch();
	printf("\n\n\t\t\tDo you want to add more [Y/N]?? ");
	scanf(" %c", &ans);
	if (toupper(ans)=='Y')
		addRecord();
	else if (toupper(ans)=='N') {
		system("cls");
		welcomeScreen();
		dashboard();
	}
} // Add Record Ends

void addRecordItem(void) {

	printf("\n\t\t\tID: ");
	fflush(stdin);
	scanf("%i", &p.id);

A:
	fflush(stdin);
	printf("\n\n\t\t\tFirst Name: ");
	scanf("%s", p.fname);
	p.fname[0]=toupper(p.fname[0]);
	if(strlen(p.fname)>20 || strlen(p.fname)<2)	{
		printf("\n\t Invalid !! The max range for first name is 20 and min is 2");
		goto A;
	}

B:
	printf("\n\n\t\t\tLast Name: ");
	scanf("%s", p.lname);
	p.lname[0]=toupper(p.lname[0]);
	if(strlen(p.lname)>20 || strlen(p.lname)<2)	{
		printf("\n\t Invalid !! The max range for last name is 20 and min is 2");
		goto A;
	} else {
		for(b=0; b<strlen(p.lname); b++) {
			if(isalpha(p.lname[b])) {
				valid=1;
			} else {
				valid=0;
				break;
			}
		}
		if(!valid) {
			system("cls");
			title();
			printf("\n\n\t\t\tOops !! Last Name contain Invalid Character !! Enter again :");
			goto B;
		}
	}
C:
	printf("\n\t\t\tGender[M|F]:");
	scanf(" %c", &p.gender);
	if(toupper(p.gender)=='M'|| toupper(p.gender)=='F')
		valid = 1;
	else
		valid = 0;
	if (!valid) {
		printf("\n\t\t\tGender contains Invalid Character. Enter either F or M : ");
		goto C;
	}

	/* ********************* Age ************************ */

D:
	printf("\n\t\t\tAge: ");
	scanf(" %i", &p.age);

	/* ********************* Address ************************ */

E:
	printf("\n\t\t\tAddress: ");
	scanf("%s", p.address);
	p.address[0]=toupper(p.address[0]);
	if(strlen(p.address)>20||strlen(p.address)<3) {
		printf("\n\n\t\t\tInvalid : Address must be max of 20 Character and 4 minimum");
		goto E;
	}
F:
	printf("\n\t\t\tPhone Number: ");
	scanf("%s", p.contactNo);
	if (strlen(p.contactNo)>10||strlen(p.contactNo)!=10) {
		printf("\n\t Oops !! Phone Number must be of 10 numbers");
		goto F;
	} else {
		for (b=0; b<strlen(p.contactNo); b++) {
			if (!isalpha(p.contactNo[b]))
				valid = 1;
			else {
				valid = 0;
				break;
			}

		}
		if(!valid) {
			printf("\n\n\t\t\tPhone number mustn't contain any character'");
			goto F;
		}
	}

G:
	printf("\n\t\t\tProblem: ");
	scanf("%s", p.problem);
	p.problem[0]= toupper(p.problem[0]);
	if(strlen(p.problem)>20||strlen(p.problem)<3) {
		printf("\n\n\t\t\tProblem can't be max than 20 characters or less than 3'");
		goto G;
	} else {
		for (b=0; b<strlen(p.problem); b++) {
			if (isalpha(p.problem[b])) {
				valid = 1;
			} else {
				valid = 0;
				break;
			}
		}
		if(!valid) {
			printf("\n\n\t\t\tProblem contain Invalid Character : Enter again");
			goto G;
		}
	}
H:
	printf("\n\t\t\tPrescribed Doctor: ");
	scanf("%s", p.doctor);
	p.doctor[0]=toupper(p.doctor[0]);
	if(strlen(p.doctor)>30||strlen(p.doctor)<3) {
		printf("\n\n\t\t\tOops!! Doctor name must only contain upto 30 alphabets");
		goto H;
	} else {
		for (b=0; b<strlen(p.doctor); b++) {
			if(isalpha(p.doctor[b])) {
				valid = 1;
			} else {
				valid =0;
				break;
			}
		}
		if(!valid) {
			printf("\n\n\t\t\tDoctor name contain Invalid character, Enter again");
			goto H;
		}
	}
}


// ex_it function
void ex_it(void) {
	system("cls");
	welcomeScreen();
	dashboard();
}
// title Function
void title(void) {
	printf("\n\n\t\t\t************************ ABC HOSPITAL *************************\n");
}
int listLoopRow(int row) {
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
	printf("\n____________________________________________________________________________________________________________________\n\n");
	gotoxy(5,10);
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
	int row = 13;
	system("cls");
	FILE *fp;
	fp = fopen("PatientsRecord.dat","r");
	printf("\n\n\n\n\n\n\t\t************************** ABC Hospital - Patients Record *************************\n");
	recordTableHead(); // Heading Title For Records
	while (fscanf(fp, "%i %s %s %c %i %s %s %s %s\n", &p.id, p.fname, p.lname, &p.gender, &p.age, p.address, p.contactNo, p.problem, p.doctor)!=EOF) {
		listLoopRow(row); // Display the available results in row of each patient
		row++; // Increase value of row once, function is called
	}
	printf("\n\n____________________________________________________________________________________________________________________");
	fclose(fp);
	printf("\n\n\t\t\t\t    Enter any key to continue...");
	getch();
	ex_it();
} // View Record Ends
/* ********************* Search Records ************************ */
void searchRecord(void) {
	int searchID;
	system("cls");
	FILE *fp;
	int row = 12;
	int count = 0;
	fp = fopen("PatientsRecord.dat","r");
	printf("\n\n\n\n\n\n\t\t************************** ABC Hospital - Search Patient *************************\n");
	gotoxy(12,8);
	fflush(stdin);
	printf("\n\t\t\t\t\t Enter Patient's ID : ");
	scanf("%i",&searchID);
	system("cls");
	printf("\n\n\n\n\n\t\t************************** ABC Hospital - Search Patient *************************\n");
	printf("\n\t\t\t\t\t Patient Searched for: %i \n", searchID);
	recordTableHead(); // Record Heading

	while (fscanf(fp, "%i %s %s %c %i %s %s %s %s\n", &p.id, p.fname, p.lname, &p.gender, &p.age, p.address, p.contactNo, p.problem, p.doctor)!=EOF) {
		if(p.id == searchID) {
			listLoopRow(row);
			row++; // Display the available results in row of each patient
			count++;
		}

	}
	printf("\n\n\t\t\t\t\t\tTotal Patients found : %d", count);
	fclose(fp);
I:
	printf("\n\n\t\t\t\t\t   Enter any key to continue...");
	getch();
	printf("\n\n\t\t\t\t\t   Do you want to view more [Y/N]?? ");

	scanf(" %c", &ans);
	if (toupper(ans)=='Y')
		searchRecord();
	else if (toupper(ans)=='N') {
		ex_it(); // Go back to main memu
	} else {
		printf("\n\tInvalid Input. \n");
		goto I;
	}

} // Search Record Ends
/* ********************* Edit Records ************************ */
void editRecord(void) {
	FILE *fp, *tf;
	int i,b,valid=0;
	char ch;
	int searchID;
	int row = 13;
	system("cls");
	printf("\n\n\n\n\t\t************************** ABC Hospital - Edit Record *************************\n");
	tf=fopen("temp_PatientsRecord.dat","w+");
	fp = fopen("PatientsRecord.dat", "r");
	if (fp==NULL) {
		printf("\n\t Cannot Open File !!");
		ex_it(); // Go back to main memu
	} else {
		gotoxy(12,6);
		fflush(stdin);
		printf("\n\t\t\t\t\t Enter Patient's ID : ");
		scanf("%i",&searchID);
		gotoxy(12,10);
		if (tf==NULL) {
			printf("\n\t Cannot Open File !!");
			ex_it(); // Go back to main memu
		}

		while (fscanf(fp, "%i %s %s %c %i %s %s %s %s\n", &p.id, p.fname, p.lname, &p.gender, &p.age, p.address, p.contactNo, p.problem, p.doctor)!=EOF) {
			if(p.id == searchID) {
				valid=1;
				system("cls");
				printf("\n\n\n\n\n\t\t************************** ABC Hospital - Record Found *************************\n");
				printf("\n\t\t\t\t\t Record Found for: %i \n", searchID);
				recordTableHead(); // Record Heading
				listLoopRow(row); // Print available data - loop data
				row++;
				addRecordItem(); // add data/edit data
				printf("\n Press U character for the Updating Operation : ");
				ch = getche();

				if (ch=='u' || ch =='U') {
					fprintf(tf, "%i %s %s %c %i %s %s %s %s\n", p.id, p.fname, p.lname, p.gender, p.age, p.address, p.contactNo, p.problem, p.doctor);
					printf("\nUpdated Successfully");
				}
			} else {
				fprintf(tf, "%i %s %s %c %i %s %s %s %s\n", p.id, p.fname, p.lname, p.gender, p.age, p.address, p.contactNo, p.problem, p.doctor);
			}
		}
		if(!valid) {
			printf("\n\t\t No Record Found...");
		}
		fclose(tf);
		fclose(fp);
		remove("PatientsRecord.dat");
		rename("temp_PatientsRecord.dat","PatientsRecord.dat");
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
	FILE *fp, *tf;
	tf = fopen("temp_PatientsRecord2.dat", "w+");
	fp = fopen("PatientsRecord.dat", "r");
	printf("\n\n\n\n\n\t\t************************** ABC Hospital - Delete Record *************************\n");
	gotoxy(12,6);
	fflush(stdin);
	printf("\n\t\t\t\t\t Search For Patient's ID : ");
	scanf("%i", &searchID);
	fflush(stdin);
	printf("\n\n\t\t\t\t\t Enter age again to confirm : ");

	scanf("%i", &confirmID);
	if(searchID==confirmID) {
		while (fscanf(fp, "%i %s %s %c %d %s %s %s %s\n", &p.id, p.fname, p.lname, &p.gender, &p.age, p.address, p.contactNo, p.problem, p.doctor)!=EOF) {
			if(searchID!=p.id) {
				fprintf(tf, "%i %s %s %c %i %s %s %s %s\n", p.id, p.fname, p.lname, p.gender, p.age, p.address, p.contactNo, p.problem, p.doctor);
			} else {
				found = 1;
			}
		}
	} else {
		notValid = 1;
	}
	if(notValid || found!=1) {
		fclose(fp);
		fclose(tf);
		remove("temp_PatientsRecord2.dat");
		if(notValid)
			printf("\n\n\t\t\t\t\t Sorry you can't confirm age");
		else
			printf("\n\n\t\t\t\t\t Oops !! Record Not Found...");
		printf("\n\n\t\t\t\t\t Enter any key to continue : ");
		getch();
		ex_it();
	}
	if(found) {
		printf("\n\n\t\t\t\t\t Record Deleted Successfully !!");
		fclose(fp);
		fclose(tf);
		remove("PatientsRecord.dat");
		rename("temp_PatientsRecord2.dat","PatientsRecord.dat");
		printf("\n\n\t\t\t\t\t Enter any key to continue : ");
		getch();
		viewRecord();
	}
}
