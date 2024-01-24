/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : Artom Zabihi
Student ID#: 137978227
Email      : azabihi1@myseneca.ca
Section    : NLL

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");

        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt){
    int i, flag = 0;

    if (fmt == FMT_TABLE){
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++){
        if (patient[i].patientNumber != 0){
            displayPatientData(&patient[i], fmt);
            flag = 1;
        }
    }

    if (flag == 0){
        printf("*** No records found ***\n");;
    }

    printf("\n");

    return;
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max){
    int choice;
    do {
        printf("Search Options\n==========================\n1) By patient number\n2) By phone number\n..........................\n0) Previous menu\n..........................\n");
        printf("Selection: ");
        scanf(" %d", &choice);
        printf("\n");

        if (choice == 1){
            searchPatientByPatientNumber(patient, max);
            clearInputBuffer();
            suspend();
        } else if (choice == 2){
            searchPatientByPhoneNumber(patient, max);
            clearInputBuffer();
            suspend();
        }
    } while (choice != 0);
    return;
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max){
    int i, index = -1;

    for (i = 0; i < max; i++){
        if (patient[i].patientNumber == 0){
            index = i;
            i = max;
        }
    }

    if (index != -1){
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);

        printf("*** New patient record added ***\n\n");
    } else {
        printf("ERROR: Patient listing is FULL!\n\n");
    }

    return;
}


// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max){
    int patientNumber, index;

    printf("Enter the patient number: ");
    scanf(" %d", &patientNumber);
    printf("\n");

    index = findPatientIndexByPatientNum(patientNumber, patient, max);

    if (index != -1){
        menuPatientEdit(&patient[index]);
    } else {
        printf("ERROR: Patient record not found!\n\n");
    }

    return;
}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max){
    int patientNumber, index, exit = 0;
    char choice, extra;

    printf("Enter the patient number: ");
    scanf(" %d", &patientNumber);
    printf("\n");

    index = findPatientIndexByPatientNum(patientNumber, patient, max);


    if (index != -1){
        printf("Name  : %s\nNumber: %05d\nPhone : ", patient[index].name, patient[index].patientNumber);
        displayFormattedPhone(patient[index].phone.number);
        printf(" (%s)\n\n", patient[index].phone.description);

        printf("Are you sure you want to remove this patient record? (y/n): ");
       

        do {
            scanf(" %c%c", &choice, &extra);
            if (choice == 'y' && extra == '\n'){
                patient[index].patientNumber = 0;
                printf("Patient record has been removed!\n\n");
                exit = 1;
            } else if (choice == 'n' && extra == '\n'){
                printf("Operation aborted.\n\n");
                exit = 1;
                clearInputBuffer();
            } else {
                clearInputBuffer();
                printf("ERROR: Character must be one of [yn]: ");
            }
        } while (exit == 0);
    } else {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }

    return;
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data){
    int i, j;
    sortAppointments(data->appointments, data->maxAppointments);

    displayScheduleTableHeader(NULL, 1);
    for (i = 0; i < data->maxAppointments; i++){
        for (j = 0; j < data->maxPatient; j++){
            if (data->appointments[i].patientNumber != 0 && data->patients[j].patientNumber != 0){
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber){
                    displayScheduleData(&data->patients[j], &data->appointments[i], 1);
                }
            }
        }
    }
    printf("\n");
}


// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data){
    struct Date date;
    int i, j;

    sortAppointments(data->appointments, data->maxAppointments);

    printf("Year        : ");
    date.year = inputIntPositive();
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);

    date.day = inputIntRange(1, calcNumDays(date.year, date.month));
    printf("\n");

    displayScheduleTableHeader(&date, 0);

    for (i = 0; i < data->maxAppointments; i++){
        for (j = 0; j < data->maxPatient; j++){
            if (data->appointments[i].patientNumber == data->patients[j].patientNumber){
                if (data->appointments[i].date.year == date.year && data->appointments[i].date.month == date.month && data->appointments[i].date.day == date.day){
                    displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                }
            }
        }
    }

    printf("\n"); 
}


// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appointment, int maxApp, struct Patient* patient, int maxPat){
    struct Date date;
    struct Time time;
    int patientNumber, index, available, exit = 0, i;

    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNumber, patient, maxPat);

    if (index != -1){
        do {
            available = 0;
            printf("Year        : ");
            date.year = inputIntPositive();
            printf("Month (1-12): ");
            date.month = inputIntRange(1, 12);
            date.day = inputIntRange(1, calcNumDays(date.year, date.month));
            printf("Hour (0-23)  : ");  
            time.hour = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);

            for (i = 0; i < maxApp; i++){
                if (appointment[i].date.year == date.year 
                && appointment[i].date.month == date.month 
                && appointment[i].date.month == date.month 
                && appointment[i].date.day == date.day 
                && appointment[i].time.hour == time.hour 
                && appointment[i].time.min == time.min){
                    printf("\nERROR: Appointment timeslot is not available!\n\n");
                    available = 0;
                    i = maxApp;
                } else {
                    available = 1;
                }
            }

             if (available == 1) {
                    do {
                        if ((time.hour < START_HOUR || time.hour > END_HOUR) || (time.min % MINUTE_INTERVAL != 0) || (time.hour == END_HOUR && time.min > 0)){
                            printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", START_HOUR, END_HOUR, MINUTE_INTERVAL);
                            printf("Hour (0-23)  : ");
                            time.hour = inputIntRange(0, 23);
                            printf("Minute (0-59): ");
                            time.min = inputIntRange(0, 59);
                        } else {
                            exit = 1;
                        }
                    } while (exit == 0);
                }

        } while (available == 0);

        for (i = 0; i < maxApp; i++){
            if (appointment[i].patientNumber == 0){
                appointment[i].date = date;
                appointment[i].time = time;
                appointment[i].patientNumber = patientNumber;
                i = maxApp;
            }
        }

        printf("\n*** Appointment scheduled! ***\n\n");
    } else {
        printf("\nERROR: Patient record not found!\n\n");
    }
}


// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* appointment, int maxApp, struct Patient* patient, int maxPat){
    struct Date date;
    int patientNumber, index, appointmentNum = -1, i;
    char choice;
    
    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNumber, patient, maxPat);

    if (index != -1){
        printf("Year        : ");
        date.year = inputIntPositive();
        printf("Month (1-12): ");
        date.month = inputIntRange(1, 12);
        date.day = inputIntRange(1, calcNumDays(date.year, date.month));

        for (i = 0; i < maxApp; i++){
            if (appointment[i].patientNumber != 0){
                if (appointment[i].patientNumber == patientNumber 
                && appointment[i].date.year == date.year 
                && appointment[i].date.month == date.month 
                && appointment[i].date.day == date.day){
                    appointmentNum = i;
                    i = maxApp;
                }
            }
        }

        if (appointmentNum != -1){
            printf("\n");
            displayPatientData(&patient[index], 1);
            printf("Are you sure you want to remove this appointment (y,n): ");
            
            choice = inputCharOption("yn");

            if (choice == 'y'){
                appointment[appointmentNum].patientNumber = 0;
                printf("\nAppointment record has been removed!\n\n");
            } else {
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
    } else {
        printf("ERROR: Patient record not found!\n\n");
    }
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

int calcNumDays (int year, int month){
    printf("Day (1-");

    if (month == 2 && year % 4 == 0){
        printf("29)  : ");
        return 29;
    } else if (month == 2){
        printf("28)  : ");
        return 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11){
        printf("30)  : ");
        return 30;
    } else {
        printf("31)  : ");
        return 31;
    }
}

void sortAppointments(struct Appointment apps[], int max){
    int totalMinutes[MAX_APPOINTMENTS];
    int i, j, tempInt;
    struct Appointment tempApp;

    for (i = 0; i < MAX_APPOINTMENTS; i++){
        totalMinutes[i] = apps[i].time.min + apps[i].time.hour*60 + apps[i].date.day*24*60 + apps[i].date.month*30*24*60 + apps[i].date.year*12*30*24*60;
    }

    for (i = 0; i < max-1; i++){
        for (j = 0; j < max-1; j++){
                if (totalMinutes[j+1] < totalMinutes[j]){
                    tempApp = apps[j];
                    tempInt = totalMinutes[j];
                    apps[j] = apps[j+1];
                    totalMinutes[j] = totalMinutes[j+1];
                    apps[j+1] = tempApp;
                    totalMinutes[j+1] = tempInt;
                }
        }
    }
}

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max){
    int number, i;

    printf("Search by patient number: ");
    scanf(" %d", &number);
    printf("\n");

    i = findPatientIndexByPatientNum(number, patient, max);

    if (i != -1){
        printf("Name  : %s\nNumber: %05d\nPhone : ", patient[i].name, patient[i].patientNumber);
        displayFormattedPhone(patient[i].phone.number);
        printf(" (%s)\n\n", patient[i].phone.description);
    } else {
        printf("*** No records found ***\n\n");
    }
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max){
    int flag = 0, i;
    char phoneNumber[PHONE_LEN+1];
    clearInputBuffer();
    
    printf("Search by phone number: ");
    scanf("%s", phoneNumber);
    printf("\n");

    displayPatientTableHeader();

    for (i = 0; i <= max; i++){
        if (strcmp(phoneNumber, patient[i].phone.number) == 0){
            printf("%05d %-15s ", patient[i].patientNumber, patient[i].name);
            displayFormattedPhone(patient[i].phone.number);
            printf(" (%s)\n", patient[i].phone.description);
            flag = 1;
        }
    }

    printf("\n");

    if (flag != 1){
        printf("*** No records found ***\n\n");
    }
}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max){
    int highest = 0, i;

    for (i = 0; i < max; i++){
        if (highest < patient[i].patientNumber){
            highest = patient[i].patientNumber;
        }
    }

    return highest+1;
}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max){
    int i;

    for (i=0; i < max; i++){
        if (patientNumber == patient[i].patientNumber){
            return i;
        }
    }

    return -1;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient){
    char name[NAME_LEN+1];
    int i;
    printf("Patient Data Input\n------------------\n");
    printf("Number: %05d\nName  : ", patient->patientNumber);
    inputCString(name, 0, NAME_LEN);
    printf("\n");

    for (i = 0; i < strlen(name); i++){
        patient->name[i] = name[i];
    }

    inputPhoneData(&patient->phone);
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone){
    int choice;
    printf("Phone Information\n-----------------\nHow will the patient like to be contacted?\n");
    printf("1. Cell\n2. Home\n3. Work\n4. TBD\nSelection: ");
    choice = inputIntRange(1,4);
    printf("\n");

    switch (choice){
        case 1:
            strcpy(phone->description, "CELL");
            break;
        case 2:
            strcpy(phone->description, "HOME");
            break;
        case 3:
            strcpy(phone->description, "WORK");
            break;
        case 4:
            strcpy(phone->description, "TBD");
            *phone->number = 0;
        default:
            break;
    }

    switch (choice){
        case 1:
        case 2:
        case 3:
            printf("Contact: %s\n", phone->description);
            printf("Number : ");
            inputPhoneNumber(phone->number, PHONE_LEN, PHONE_LEN);
            printf("\n");
            break;
        default:
            break;
    }
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* file, struct Patient patients[], int max){
    int i, j, counter = 0;
    char line[LINE_LEN], *token;

    FILE *fp = NULL;
    fp = fopen(file, "r");

    if (fp == NULL){
        printf("ERROR: Failed to read file");
    } else {

        for (i = 0; i < max && feof(fp) == 0; i++){
            fgets(line, LINE_LEN, fp);
            token = strtok(line, "|");
            patients[i].patientNumber = atoi(token);
            token = strtok(NULL, "|");
            strcpy(patients[i].name, token);
            token = strtok(NULL, "|");
            strcpy(patients[i].phone.description, token);
            token = strtok(NULL, "|");

            for (j = 0; j < 10; j++){
                patients[i].phone.number[j] = token[j];
            }
            
            counter++;
        }
    }

    

    fclose(fp);

    return counter;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* file, struct Appointment appointments[], int max){
    int i, counter = 0;
    FILE *fp = NULL;
    fp = fopen(file, "r");

    if (fp == NULL){
        printf("ERROR: Failed to read file");
    } else {
        for (i = 0; i < max && !feof(fp); i++){
            fscanf(fp, "%d,%d,%d,%d,%d,%d", &appointments[i].patientNumber, &appointments[i].date.year, &appointments[i].date.month, 
            &appointments[i].date.day, &appointments[i].time.hour, &appointments[i].time.min);
            if (!feof(fp)){
                counter++;
            }
        }

        fclose(fp);
    }

    return counter;
}