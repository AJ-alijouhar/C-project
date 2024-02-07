#include <bits/stdc++.h> //included all header files
#include <fstream>       //to include file streams in the projects
#include <stdlib.h>
using namespace std;

// Class Blood bank that keep the databse of available blood in the blood bank

class blood_bank
{
public:
    static int bloodgroup[8]; // Static data memeber that will keep the record of available blood units in the blood bank
};

int blood_bank::bloodgroup[] = {0, 0, 0, 0, 0, 0, 0, 0}; // intilization of static member of bllod_bank class

// Admin will have the access of the complete database of the blood bank, including donors data, patient data

class admin
{
public:
    void display();

    admin()
    {
        char s[20] = "NITJSR";
        char str[20];
        cout << "Enter password:";
        cin >> str;
        if (strcmp(s, str) == 0)
        {
            cout << "\nwelcome!!!" << endl;
            display();
        }
        else
            cout << "\nPlease contact Akshay to become an admin" << endl;
    }
};

// after the successful login of the Admin, admin will be able to display all the details of the available blood groups
void admin::display()
{
    cout << "A +ve:" << blood_bank::bloodgroup[0] << endl;
    cout << "O +ve:" << blood_bank::bloodgroup[1] << endl;
    cout << "B +ve:" << blood_bank::bloodgroup[2] << endl;
    cout << "AB +ve:" << blood_bank::bloodgroup[3] << endl;

    cout << "A -ve:" << blood_bank::bloodgroup[4] << endl;
    cout << "O -ve:" << blood_bank::bloodgroup[5] << endl;
    cout << "B -ve:" << blood_bank::bloodgroup[6] << endl;
    cout << "AB -ve:" << blood_bank::bloodgroup[7] << endl;
}
// Pateint will interact with this class for their requirements of the blood, they will fill all the details and will be
// assigned the blood as per the requirements and the availability

class Patient
{
private:
    // data members of class Patient

    char name_of_patient[50];   // An array of characters to store the name of the Patient
    char blood_group[20];       // An array of characters to store the blood group of the Patient
    char case_details[50];      // An array of characters to store the medical issue of the Patient
    char hospital_name[50];     // An array of characters to store the name of the hospital in which patient is admitted
    char bystander_name[50];    // An array of characters to store the name of the attendent with the Patient
    char bystander_contact[12]; // An array of characters to store the contact number of the attendent with the Patient

public:
    // Default constructor of the Patient class to set the data members with default values

    Patient()
    {
        strcpy(name_of_patient, "default");
        strcpy(blood_group, "default");
        strcpy(case_details, "default");
        strcpy(hospital_name, "default");
        strcpy(bystander_name, "default");
        strcpy(bystander_contact, "00000000");
    }

    void set_name_of_patient(char *name) { strcpy(name_of_patient, name); } // This function will set the name of the Patient

    void set_case(char *cs) { strcpy(case_details, cs); } // This function will set the medical issue of the Patient

    void set_name_of_hospital(char *hname) { strcpy(hospital_name, hname); } // This function will set the name of the
                                                                             // hospital in which patient is admitted

    void set_name_of_bystander(char *bname) { strcpy(bystander_name, bname); } // This function will set the name of
                                                                               // the attendent with the Patient

    void set_bystander_contact(char *cont) { strcpy(bystander_contact, cont); } // This function will set the contact
                                                                                // number of the attendent with the Patient

    void new_Patient_registration(); // This function will be called to create a registration window for the patient

    void check_availability(int); // This function will be called to check the availability of the
                                  // compatible blood groups as per the requirement of the patient in the blood bank
};

// This function will give the patiient a registration form, in which they will fill the details and get the blood as per the need
// Function definition of new_Patient_registration(), from Patient class

void Patient::new_Patient_registration()
{
    char name[50], blood[20], cs[50], hname[50], bname[50], cont[12], user[20], pass[20]; // to store the patient profile

    int c;
    cin.ignore();
    cout << "\nEnter Patient name: " << endl;
    cin.getline(name, 50);
    cout << "Enter type of blood group you are looking for:" << endl;

    cout << "0 = A positive" << endl
         << "1 = O positive" << endl
         << "2 = B positive" << endl // as per the requirement of the patient the patient will enter the
                                     // Number respective to blood group from the table
         << "3 = AB positive" << endl
         << "4 = A negative" << endl
         << "5 = O negative" << endl
         << "6 = B negative" << endl
         << "7 = AB negative" << endl;

    cin >> c;
    cin.ignore();
    cout << "\nEnter Case Details: ";
    cin.getline(cs, 50);
    cout << "\nEnter Hosptal Details: ";
    cin.getline(hname, 50);
    cout << "\nEnter Bystander name: ";
    cin.getline(bname, 50);
    cout << "\nEnter Bystander contact number: ";
    cin.getline(cont, 12);

    set_name_of_patient(name);
    set_case(cs);
    set_name_of_hospital(hname);
    set_name_of_bystander(bname);
    set_bystander_contact(cont);

    // This will store all the patient info in the database(file - Patient_details.dat)

    ofstream fout;                                                       // file stream object of the ofstream class
    fout.open("Patient_details.dat", ios::out | ios::binary | ios::app); // to link the file stream object with our file and open the file
    fout.write((char *)this, sizeof(*this));                             //.write function will write the whole data of Patient object in the file "Patient_details.dat"
    fout.close();

    //********************* Registration is successful **********************

    check_availability(c); // function call
}

// As per the need of the patient the function will check_availability for the required blood group and will assign it to the patient

void Patient::check_availability(int c)
{
    cout << "++++list of Available blood groups compatible with the entered blood group:++++" << endl;
    if (c == 0)
    {
        cout << "A +ve:" << blood_bank::bloodgroup[0] << endl; // Listing all the compatible blood groups
        cout << "A -ve:" << blood_bank::bloodgroup[4] << endl;
        cout << "O +ve:" << blood_bank::bloodgroup[1] << endl;
        cout << "O -ve:" << blood_bank::bloodgroup[5] << endl;

        if (blood_bank::bloodgroup[0] > 0) // If any of blood group's availability is greater than zero we will assign the blood to the patient.
            blood_bank::bloodgroup[0]--;   // After assigning the blood, we will decrease the count in the database
        else if (blood_bank::bloodgroup[4] > 0)
            blood_bank::bloodgroup[4]--;
        else if (blood_bank::bloodgroup[1] > 0)
            blood_bank::bloodgroup[2]--;
        else if (blood_bank::bloodgroup[5] > 0)
            blood_bank::bloodgroup[6]--;
        else
            cout << "----Sorry Compatible blood group is not available, Kindly contact the Admin to arrange a Donor-----" << endl; // if blood group is not available
    }

    else if (c == 1)
    {
        cout << "O +ve:" << blood_bank::bloodgroup[1] << endl;
        cout << "O -ve:" << blood_bank::bloodgroup[5] << endl;

        if (blood_bank::bloodgroup[1] > 0)
            blood_bank::bloodgroup[1]--;
        else if (blood_bank::bloodgroup[5] > 0)
            blood_bank::bloodgroup[5]--;
        else
            cout << "----Sorry Compatible blood group is not available, Kindly contact the Admin to arrange a Donor-----" << endl; // if blood group is not available
    }

    else if (c == 2)
    {
        cout << "B +ve:" << blood_bank::bloodgroup[2] << endl;
        cout << "B -ve:" << blood_bank::bloodgroup[6] << endl;
        cout << "O +ve:" << blood_bank::bloodgroup[1] << endl;
        cout << "O -ve:" << blood_bank::bloodgroup[5] << endl;

        if (blood_bank::bloodgroup[2] > 0)
            blood_bank::bloodgroup[2]--;
        else if (blood_bank::bloodgroup[6] > 0)
            blood_bank::bloodgroup[6]--;

        else if (blood_bank::bloodgroup[1] > 0)
            blood_bank::bloodgroup[1]--;
        else if (blood_bank::bloodgroup[5] > 0)
            blood_bank::bloodgroup[5]--;
        else
            cout << "----Sorry Compatible blood group is not available, Kindly contact the Admin to arrange a Donor-----" << endl; // if blood group is not available
    }

    else if (c == 3)
    {
        cout << "A +ve:" << blood_bank::bloodgroup[0] << endl;
        cout << "A -ve:" << blood_bank::bloodgroup[4] << endl;
        cout << "B +ve:" << blood_bank::bloodgroup[2] << endl;
        cout << "B -ve:" << blood_bank::bloodgroup[6] << endl;
        cout << "AB +ve:" << blood_bank::bloodgroup[3] << endl;
        cout << "AB -ve:" << blood_bank::bloodgroup[7] << endl;
        cout << "O +ve:" << blood_bank::bloodgroup[1] << endl;
        cout << "O -ve:" << blood_bank::bloodgroup[5] << endl;

        if (blood_bank::bloodgroup[0] > 0)
            blood_bank::bloodgroup[0]--;
        else if (blood_bank::bloodgroup[4] > 0)
            blood_bank::bloodgroup[4]--;
        else if (blood_bank::bloodgroup[2] > 0)
            blood_bank::bloodgroup[2]--;
        else if (blood_bank::bloodgroup[6] > 0)
            blood_bank::bloodgroup[6]--;
        else if (blood_bank::bloodgroup[3] > 0)
            blood_bank::bloodgroup[3]--;
        else if (blood_bank::bloodgroup[7] > 0)
            blood_bank::bloodgroup[7]--;
        else if (blood_bank::bloodgroup[1] > 0)
            blood_bank::bloodgroup[1]--;
        else if (blood_bank::bloodgroup[5] > 0)
            blood_bank::bloodgroup[5]--;
        else
            cout << "----Sorry Compatible blood group is not available, Kindly contact the Admin to arrange a Donor-----" << endl; // if blood group is not available
    }
    else if (c == 4)
    {
        cout << "A -ve:" << blood_bank::bloodgroup[4] << endl;
        cout << "O -ve:" << blood_bank::bloodgroup[5] << endl;

        if (blood_bank::bloodgroup[4] > 0)
            blood_bank::bloodgroup[4]--;

        else if (blood_bank::bloodgroup[5] > 0)
            blood_bank::bloodgroup[5]--;

        else
            cout << "----Sorry Compatible blood group is not available, Kindly contact the Admin to arrange a Donor-----" << endl; // if blood group is not available
    }

    else if (c == 5)
    {
        cout << "O -ve:" << blood_bank::bloodgroup[5] << endl;

        if (blood_bank::bloodgroup[5] > 0)
            blood_bank::bloodgroup[5]--;
        else
            cout << "----Sorry Compatible blood group is not available, Kindly contact the Admin to arrange a Donor-----" << endl; // if blood group is not available
    }

    else if (c == 6)
    {
        cout << "B -ve:" << blood_bank::bloodgroup[6] << endl;
        cout << "O -ve:" << blood_bank::bloodgroup[5] << endl;

        if (blood_bank::bloodgroup[6] > 0)
            blood_bank::bloodgroup[6]--;
        else if (blood_bank::bloodgroup[5] > 0)
            blood_bank::bloodgroup[5]--;
        else
            cout << "----Sorry Compatible blood group is not available, Kindly contact the Admin to arrange a Donor-----" << endl; // if blood group is not available
    }

    else if (c == 7)
    {
        cout << "A -ve:" << blood_bank::bloodgroup[4] << endl;
        cout << "B -ve:" << blood_bank::bloodgroup[6] << endl;
        cout << "O -ve:" << blood_bank::bloodgroup[5] << endl;
        cout << "AB -ve:" << blood_bank::bloodgroup[7] << endl;

        if (blood_bank::bloodgroup[4] > 0)
            blood_bank::bloodgroup[4]--;

        else if (blood_bank::bloodgroup[6] > 0)
            blood_bank::bloodgroup[6]--;

        else if (blood_bank::bloodgroup[5] > 0)
            blood_bank::bloodgroup[5]--;

        else if (blood_bank::bloodgroup[7] > 0)
            blood_bank::bloodgroup[7]--;
        else
            cout << "----Sorry Compatible blood group is not available, Kindly contact the Admin to arrange a Donor-----" << endl; // if blood group is not available
    }
}

// Donor will interact with this class to donate blood, they will give all the information required for the registration

class Donor
{
private:
    char name_of_donor[50];     // an array of characters to store the name of the donor
    char donor_blood_group[10]; // an array of characters to store the blood group of the donor
    char donor_age[10];         // an array of characters to store the age of the donor
    char donor_weight[50];      // an array of characters to store the body weight of the donor
    char donor_address[50];     // an array of characters to store the address of the donor
    char donor_contact[12];     // an array of characters to store the contact number of the donor
    char previous_donation[30]; // an array of characters to store the previous blood donation date of the donor

public:
    // Default constructor of the donor class to set the data memebrs with the default values
    Donor()
    {
        strcpy(name_of_donor, "default");
        strcpy(donor_blood_group, "default");
        strcpy(donor_age, "00");
        strcpy(donor_weight, "00");
        strcpy(donor_address, "default");
        strcpy(donor_contact, "00000000");
        strcpy(previous_donation, "00/00/0000");
    }

    void set_name_of_donor(char *name) { strcpy(name_of_donor, name); }           // function to set the name of the Donor
    void set_donor_blood_group(char *blood) { strcpy(donor_blood_group, blood); } // function to set the blood group of the Donor
    void set_donor_age(char *age) { strcpy(donor_age, age); }                     // function to set the age of the Donor
    void set_donor_weight(char *weight) { strcpy(donor_weight, weight); }         // function to set the weight of the Donor
    void set_donor_address(char *address) { strcpy(donor_address, address); }     // function to set the address of the Donor
    void set_donor_contact(char *contact) { strcpy(donor_contact, contact); }     // function to set the contact number of the Donor
    void set_previous_donation(char *date) { strcpy(previous_donation, date); }   // function to set the date of previous blood donation of the Donor

    // Function will be called to give donor a interface to enter his/her details as per the need
    void new_donor_registration();
};

// Function definition of the member function new_donor_registration(), of the Donor class
void Donor::new_donor_registration()
{

    char name[50], blood[10], age[10], weight[10], address[50], contact[12], date[30];
    int c, x;
    cin.ignore();
    cout << "\nEnter donor name: ";
    cin.getline(name, 50);

    cout << "Enter type of blood group you are donating:" << endl;

    cout << "0 = A positive" << endl // user will enter the respective number of the blood group, he/she wants to donate to, from the table provided
         << "1 = O positive" << endl
         << "2 = B positive" << endl
         << "3 = AB positive" << endl
         << "4 = A negative" << endl
         << "5 = O negative" << endl
         << "6 = B negative" << endl
         << "7 = AB negative" << endl;
    cout << "-->>";

    cin >> c;
    cin.ignore();
    cout << "how many packets of blood are you donating:"; // the count of packets the donor wants to donate
    cin >> x;
    blood_bank::bloodgroup[c] += x; // here we will update the number of packets of the respective blood group in out database
    cin.ignore();
    cout << "\nEnter the Age: ";
    cin.getline(age, 10);
    cout << "\nEnter weight Details: ";
    cin.getline(weight, 10);
    cout << "\nEnter address: ";
    cin.getline(address, 50);
    cout << "\nEnter contact number: ";
    cin.getline(contact, 12);
    cout << "\nEnter previous donation date (dd/mm/yyyy): " << endl;
    cin.getline(date, 30);

    set_name_of_donor(name);
    set_donor_age(age);
    set_donor_weight(weight);
    set_donor_address(address);
    set_donor_contact(contact);
    set_previous_donation(date);

    // This will store all the donor info in the database(file - donor_details.dat)

    ofstream fout;                                                     // file stream object of the ofstream class
    fout.open("donor_details.dat", ios::out | ios::binary | ios::app); // to link the file stream object with our file and open the file
    fout.write((char *)this, sizeof(*this));                           //.write function will write the whole data of Patient object in the file "donor_details.dat"
    fout.close();
}

int main()
{
    int choice;
    int i = 0, j = 0;
    Patient p1[100]; // an array of objects of Patient class.
    Donor d1[50];    // an array of objects of Donor class.
    cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  -----  WELCOME TO HELPING HAND FOUNDATION  -----   " << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    do
    {
        cout << "\n1.DONATE BLOOD \n2.NEED BLOOD? \n3.ADMIN \n4.EXIT" << endl;
        cout << "\nEnter your choice:" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // case 1 will call the function of donor class and the registration of the donor will be done.

            cout << "\n*****Thankyou for your service towards humanity, Kindly follow the instructions ahead*****" << endl;
            d1[i].new_donor_registration();
            i++;
            break;
        }

        case 2:
        {
            // case 2 will call the function of Patient class and the registration of the Patient will be done.

            cout << "\n*****We are always available in your service, Kindly follow the instructions ahead*****" << endl;
            p1[j].new_Patient_registration();
            j++;
            break;
        }

        case 3:
        {
            // case 3 will interact with the adin class, after login admin will be able to see all the details
            // from the database
            admin a1;
            break;
        }

        case 4:
        {
            exit(0);
        }

        default:
        {
            cout << "Invalid choice" << endl;
            break;
        }
        }
    } while (true);

    return 0;
}