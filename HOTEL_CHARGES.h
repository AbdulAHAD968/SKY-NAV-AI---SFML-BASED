#ifndef HOTEL_CHARGES_H
#define HOTEL_CHARGES_H


#include "EXTRA_FUN.h"

#include<iostream>
#include<fstream>

using namespace std;


class HOTEL_CHARGES{

    public:

        string city;
        double CHARGE_PER_DAY;
    
    public:

        // USER DEFINED DEFAULT CONSTRUCTOR.
        HOTEL_CHARGES(){
            this->city = "";
            this->CHARGE_PER_DAY = 0.0;
        }


        // PRINT FUNCTION.
        void PRINT_HOTEL_CHARGES(){
            cout<<ANSI_COLOR_BOLD_YELLOW<<endl<<"\t |   "<<left<<setw(17)<<this->city<<"|   "<<left<<setw(20)<<this->CHARGE_PER_DAY<<" |";
        }


        // DESTRUNCOR.
        ~HOTEL_CHARGES(){
            // NOTHING TO DO HERE AS USUAL.
        }

};


//** MAKING NODE CLASS FOR HOTEL CHARGES. */
class HOTEL_CHARGE_NODE{
    
    public:
    
        HOTEL_CHARGES data;
        HOTEL_CHARGE_NODE* next;
    
        // CONSTRUCTOR FOR THIS CLASS.
        HOTEL_CHARGE_NODE(HOTEL_CHARGES data){
            this->data = data;
            this->next = nullptr;
        }

        // DESTRUCTOR.
        ~HOTEL_CHARGE_NODE(){
            // NOTHING TO DO HERE AS USUAL.
        }

};


//** LIST OF HOTEL CHARGES. */
class HOTEL_CHARGE_LIST{

    private:

        HOTEL_CHARGE_NODE* head;
    
    public:

        // CONSTRUCTOR FOR THIS CLASS.
        HOTEL_CHARGE_LIST(){
            this->head = nullptr;
        }

        // FUNCTION TO INSERT AT HEAD.
        void INSERT_AT_HEAD(HOTEL_CHARGES data){
            HOTEL_CHARGE_NODE* temp = new HOTEL_CHARGE_NODE(data);
            if(this->head == NULL){
                this->head = temp;
                return;
            }
            else{
                temp->next = this->head;
                this->head = temp;
            }
        }

        // FUNCTION TO READ DATA FROM FILE.
        void READ_HOSTEL_CHARGE(){

            string file_name = "HotelCharges_perday.txt";

            ifstream read(file_name);
            if(!read){
                cout<<"\n FILE NOT FOUND.\n";
                return;
            }
            while(!read.eof()){
                HOTEL_CHARGES temp;
                read>>temp.city>>temp.CHARGE_PER_DAY;
                this->INSERT_AT_HEAD(temp);
            }
        }

        // PRINT FUNCTION.
        void PRINT_DATA(){
            cout<<ANSI_COLOR_BOLD_RED<<"\n\t ----------------------------------------------";
            cout<<"\n\t |     CITY NAME      |      HOTEL CHARGE     |";
            cout<<"\n\t ----------------------------------------------"<<ANSI_COLOR_RESET;
            HOTEL_CHARGE_NODE* temp = this->head;
            while(temp!= nullptr){
                temp->data.PRINT_HOTEL_CHARGES();
                temp = temp->next;
            }
            cout<<"\n\t |_____________________________________________|"<<ANSI_COLOR_RESET;
        }

        // DELETE FROM START FUNCTION.
        void DELETE_START(){
            if(this->head == nullptr){
                cout<<"\n LIST IS EMPTY.\n";
                return;
            }
            HOTEL_CHARGE_NODE* temp = this->head;
            this->head = this->head->next;
            delete temp;
        }


        // TAKE CITY AS INPUT AND RETURN ITS CHARGES.
        double GET_CHARGES_FOR_CITY(string city){
            HOTEL_CHARGE_NODE* temp = this->head;
            while(temp!= nullptr){
                if(temp->data.city == city){
                    return temp->data.CHARGE_PER_DAY;
                }
                temp = temp->next;
            }
            return -1.0;    // IF NOT FOUND.
        }


        // LIST ALL THE HOTELS AVAILABLE, ALONG WITH THEIR PRICE LIST AND ASK THE USER WHERE HE WANTS TO STAY.
        double LIST_HOTELS_AND_CHARGES(string cities){
            stringstream ss(cities);
            string city;
            double total_charges = 0.0;
            while(getline(ss, city, ',')){
                double charges = this->GET_CHARGES_FOR_CITY(city);
                if(charges!= -1.0){
                    cout<<"\n\t HOTEL ["<<city<<"]   ::  ["<<charges<<"] PER DAY."<<endl;
                    total_charges += charges;
                }
                else{
                    cout<<"\n\t HOTEL IN ["<<city<<"] NOT FOUND."<<endl;
                }
            }
            return total_charges;
        }


        // DESTRUCTOR OF CLASS.
        ~HOTEL_CHARGE_LIST(){
            while(this->head!= nullptr){
                HOTEL_CHARGE_NODE* temp = this->head;
                this->head = this->head->next;
                delete temp;
            }
        }

};



#endif