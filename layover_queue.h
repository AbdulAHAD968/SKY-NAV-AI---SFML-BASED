#ifndef LAYOVER_QUEUE_H
#define LAYOVER_QUEUE_H


#include "HOTEL_CHARGES.h"

#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>  
#include<SFML/System.hpp> 
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<limits>
#include<cfloat>
#include<cmath>
#include<climits>


using namespace std;


static string PREV_LAND;
int FLAG=0;
int PC=0;

//** FLIGHT DATA CLASS. */
class FLIGHT_DATA{
    
    public:

        string origin;
        string destination;
        string date_of_travel;
        string TAKE_OFF;
        string LAND;
        double ticket_price;
        string airline;


        // CONSTRUCTOR OF CLASS WHICH WILL TAKE ALL THE PARAMETERS.
        FLIGHT_DATA(string o="", string d="", string dt="", string ft="", string lt="", double tp=0, string al=""){
            this->origin = o;
            this->destination = d;
            this->date_of_travel = dt;
            this->TAKE_OFF = ft;
            this->LAND = lt;
            this->ticket_price = tp;
            this->airline = al;
        }


        // CHECK IF THIS IS EMPTY OR NOT.
        bool IS_EMPTY(){
            return this->origin.empty() && this->destination.empty()
            && this->date_of_travel.empty() && this->TAKE_OFF.empty() 
            && this->LAND.empty() && this->ticket_price == 0 && this->airline.empty();
        }

        // APPOINT DATA.
        void APPOINT(const string& org , const string& dest, const string& date, const string& fly_time, const string& land_time, double price, const string& air){
            this->origin = org;
            this->destination = dest;
            this->date_of_travel = date;
            this->TAKE_OFF = fly_time;
            this->LAND = land_time;
            this->ticket_price = price;
            this->airline = air;
        }


        // FUNCTION TO PRINT DATA GRAPHICALLY ON 2-D SPRINT
        void PRINT_USING_SFML(string org=""){

            this->origin=org;
            // Define city structure
            struct City {
                const char* name;
                float x;
                float y;
            };

            // List of cities
            City cities[] = {
                {"Islamabad", 1180, 290},
                {"Newyork", 250, 150},
                {"Paris", 400, 200},
                {"Tokyo", 1000, 230},
                {"London", 300, 280},
                {"Singapore", 800, 300},
                {"HongKong", 850, 110},
                {"Berlin", 500, 450},
                {"Seoul", 1150, 150},
                {"Amsterdam", 560, 55},
                {"Sydney", 870, 470}
            };
            const int numCities = sizeof(cities) / sizeof(cities[0]);

            // Find indices of origin and destination
            auto findCityIndex = [](const string& name, City cities[], int numCities) {
                for (int i = 0; i < numCities; i++) {
                    if (name == cities[i].name) {
                        return i;
                    }
                }
                return -1;
            };

            int sourceIndex = findCityIndex(this->origin, cities, numCities);
            int destinationIndex = findCityIndex(this->destination, cities, numCities);

            if (sourceIndex == -1 || destinationIndex == -1) {
                cerr << "Invalid source or destination city!" << endl;
                return;
            }

            // Create SFML window
            sf::RenderWindow window(sf::VideoMode(1600, 600), "ZAR NAVIGATION SYSTEM");

            // Load map texture
            sf::Texture mapTexture;
            if (!mapTexture.loadFromFile("map.png")) {
                cerr << "Failed to load map texture!" << endl;
                return;
            }
            sf::Sprite mapSprite(mapTexture);

            // Load font for labels
            sf::Font font;
            if (!font.loadFromFile("arial.ttf")) {
                cerr << "Failed to load font!" << endl;
                return;
            }

            // Load the airplane texture
            sf::Texture airplaneTexture;
            if (!airplaneTexture.loadFromFile("3.png")) {
                cerr << "Error: Unable to load airplane.png" << endl;
                return ;
            }

            // Convert black pixels to transparent
            sf::Image airplaneImage = airplaneTexture.copyToImage();
            for (unsigned int y = 0; y < airplaneImage.getSize().y; ++y) {
                for (unsigned int x = 0; x < airplaneImage.getSize().x; ++x) {
                    if (airplaneImage.getPixel(x, y) == sf::Color::Black) {
                        airplaneImage.setPixel(x, y, sf::Color(0, 0, 0, 0)); // Set black pixels to transparent
                    }
                }
            }

            // Reload the modified image back into the texture
            if (!airplaneTexture.loadFromImage(airplaneImage)) {
                cerr << "Error: Unable to reload modified airplane texture"<<endl;
                return ;
            }

            // Create the airplane sprite
            sf::Sprite airplaneSprite(airplaneTexture);
            airplaneSprite.setScale(0.09999f, 0.09999f); // Scale the airplane as needed  

            // Movement variables  
            sf::Vector2f start(cities[sourceIndex].x, cities[sourceIndex].y);  
            sf::Vector2f end(cities[destinationIndex].x, cities[destinationIndex].y);  
            sf::Vector2f LOCATION = start;  
            float speed = 0.1f; // Speed of the airplane  
            float t = 0.0f;     // Interpolation factor (0 to 1) 

            // Function to draw a progressive dotted line
            auto DOTTED_LINES = [&](sf::RenderWindow& win, sf::Vector2f start, sf::Vector2f current) {
                float dotSpacing = 10.0f; // Distance between dots
                float totalDistance = sqrt(pow(current.x - start.x, 2) + pow(current.y - start.y, 2));
                sf::Vector2f direction = current - start;
                direction /= sqrt(direction.x * direction.x + direction.y * direction.y); // Normalize direction

                for (float i = 0; i < totalDistance; i += dotSpacing) {
                    sf::Vector2f dotPosition = start + direction * i;
                    sf::CircleShape dot(2); // Dot size
                    dot.setFillColor(sf::Color::Yellow); // Dot color
                    dot.setPosition(dotPosition.x - dot.getRadius(), dotPosition.y - dot.getRadius());
                    win.draw(dot);
                }
            };

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                }

                window.clear(sf::Color::Black);

                // Draw the map
                window.draw(mapSprite);

                // Draw cities and labels
                for (int i = 0; i < numCities; i++) {
                    sf::CircleShape marker(5, 3);
                    marker.setFillColor(sf::Color::Red);
                    marker.setPosition(cities[i].x - marker.getRadius(), cities[i].y - marker.getRadius());
                    window.draw(marker);

                    sf::Text label;
                    label.setFont(font);
                    label.setString(cities[i].name);
                    label.setCharacterSize(16);
                    label.setFillColor(sf::Color::White);
                    label.setPosition(cities[i].x + 10, cities[i].y - 5);
                    window.draw(label);
                }

                // Draw progressive dotted line from start to the current airplane position
                DOTTED_LINES(window, start, LOCATION);

                // Simulate airplane movement
                if (t < 1.0f) {
                    LOCATION.x = (1 - t) * start.x + t * end.x;
                    LOCATION.y = (1 - t) * start.y + t * end.y;
                    t += speed * 0.01f;
                }

                // Draw the airplane  
                airplaneSprite.setPosition(LOCATION);  
                window.draw(airplaneSprite);  

                // Draw table-like structure for flight information  
                sf::RectangleShape tableBackground(sf::Vector2f(250, 150)); // Size of the table  
                tableBackground.setFillColor(sf::Color(50, 50, 50, 200)); // Semi-transparent background  
                tableBackground.setPosition(10, 450); // Position of the table  
                window.draw(tableBackground);  

                // Draw flight information in the table  
                sf::Text infoLabel;  
                infoLabel.setFont(font);  
                infoLabel.setCharacterSize(16);
                infoLabel.setFillColor(sf::Color::White);  
                infoLabel.setPosition(30, 470); // Position inside the table  
                infoLabel.setString(  
                    "AIRLINE: " + this->airline + "\n" +  
                    "DATE: " + this->date_of_travel + "\n" +  
                    "DEPARTURE: " + origin + "\n" +   
                    "ARRIVAL: " + this->destination + "\n" +
                    "COST    : " + to_string(this->ticket_price) 
                );
                window.draw(infoLabel);  

                window.display(); 
            }
        }




        void PRINT_HEADER(){
            cout<<ANSI_COLOR_BOLD_RED<<"\n\t-------------------------------------------------------------------------------------------------------------------------------------";
            cout<<"\n\t|  NO.  |    ORIGIN     |   DESTINATION    |   DATE_OF_TRAVEL  |  TAKE_OFF_TIME  |  LANDING_TIME  |  TICKET_PRICE  |    AIRLINE     |";
            cout<<"\n\t-------------------------------------------------------------------------------------------------------------------------------------"<<ANSI_COLOR_RESET<<endl;
        }

        // PRINT INFO.
        void FLIGHT_PRINT(string s=""){
            if(FLAG==0){
                PRINT_HEADER();
                FLAG=1;
            }
            if(s==this->airline){
                cout<<ANSI_COLOR_BOLD_YELLOW<<left<<"\t| "<<setw(5)<<PC<<" | "<<setw(14)<<this->origin<<"| "<<setw(16)<<this->destination<<" | "<<setw(17)<<this->date_of_travel<<" | "<<setw(15)<<this->TAKE_OFF<<" | "<<setw(14)<<this->LAND<<" | $"<<setw(13)<<this->ticket_price<<" | "<<setw(14)<<this->airline<<" | ";
                cout<<"\n";
            }else{
                cout<<ANSI_COLOR_BOLD_GREEN<<left<<"\t| "<<setw(5)<<PC<<" | "<<setw(14)<<this->origin<<"| "<<setw(16)<<this->destination<<" | "<<setw(17)<<this->date_of_travel<<" | "<<setw(15)<<this->TAKE_OFF<<" | "<<setw(14)<<this->LAND<<" | $"<<setw(13)<<this->ticket_price<<" | "<<setw(14)<<this->airline<<" | ";
                cout<<"\n";
            }
            PC++;
        }

        // DESTRUCTOR.
        ~FLIGHT_DATA(){
            // I ANT DOING ANYTHING HERE...
        }
};


//NOTE - SOME SHIT FOR SEGMENT FLIGHT INTO DIFFERENT PARTS...


//** MKAING A NODE CLASS FOR LINKED LIST THAT WILL KEEP THE TRACK OF EACH CITY[OBJECT OF FLIGHT DATA] IF ROUTE IS COMPLEX. */
class NODE_FLIGHT_DATA{
    
    public:

        FLIGHT_DATA data;
        NODE_FLIGHT_DATA* next;
        
        // CONSTRUCTORS.
        NODE_FLIGHT_DATA(const FLIGHT_DATA& flight){
            this->data = flight;
            this->next = NULL;
        }

        // DESTRUCTOR.
        ~NODE_FLIGHT_DATA(){
            // I ANT DOING ANYTHING HERE...
        }

};


//** MAKING A LINKED LIST CLASS [TO KEEP THE DETAILS OF EACH STEP OF FLIGHT IN IN-DIRECT FLIGHT]. */
class FLIGHT_LIST{
    
    public:

        NODE_FLIGHT_DATA* head;
        NODE_FLIGHT_DATA* tail;
        int count;
    
    public:

        // USER DEFINED DEFAULT CONSTRUCTORS.
        FLIGHT_LIST(){
            this->head = NULL;
            this->tail = NULL;
            this->count = 0;
        }

        // INSERTION FUNCTION [INSERT AT THE END OF LIST].
        void INSERT(const FLIGHT_DATA& flight){
            NODE_FLIGHT_DATA* new_node = new NODE_FLIGHT_DATA(flight);
            if(this->head == NULL){
                this->head = this->tail = new_node;
            }
            else{
                this->tail->next = new_node;
                this->tail = new_node;
            }
            this->count++;
        }

        // DEL_ME FROM HEAD ALWAYS AS THE CITY IS TRAVELLED.
        void REMOVE_VISITED_HEAD(){
            if(this->head == NULL){
                cout<<"\n FLIGHT LIST IS EMPTY. \n";
                return;
            }
            NODE_FLIGHT_DATA* temp = this->head;
            this->head = this->head->next;
            delete temp;
            this->count--;
        }


        // DELETE SELECTED ROUTE FROM DATA.
        void DELETE_PASSED_DATA(FLIGHT_DATA& F){
            NODE_FLIGHT_DATA* temp = this->head;
            NODE_FLIGHT_DATA* prev = NULL;
            while(temp!= NULL ){
                if(temp->data.destination == F.destination && temp->data.origin == F.origin && temp->data.date_of_travel == F.date_of_travel){
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
            if(temp == NULL){
                cout<<"\n ROUTE NOT FOUND. \n";
                return;
            }
            if(prev == NULL){
                this->head = this->head->next;
            }
            else{
                prev->next = temp->next;
            }
            delete temp;
            this->count--;
        }


        // GET SIZE OF THE LIST. [GETTER]
        int SIZE(){
            return this->count;
        }


        // TRAVERSE TILL NUMBER AND RETURN THE OBJECT.
        FLIGHT_DATA GET_AT(int index){
            NODE_FLIGHT_DATA* temp = this->head;
            for(int i=0; i<index; i++){
                if(temp == NULL){
                    cout<<"\n INDEX OUT OF BOUNDS. \n";
                    return FLIGHT_DATA();
                }
                temp = temp->next;
            }
            return temp->data;
        }


        // PRINT FUNCTION.
        void PRINT(string s="" , int FLA=0 , string g[]=NULL){
            if(this->head == NULL){
                cout<<"\n FLIGHT LIST IS EMPTY. \n";
                return;
            }
            PC=0;
            FLAG=0;
            NODE_FLIGHT_DATA* temp = this->head;
            int i=0;
            while(temp!= NULL){
                if(FLA==1){
                    temp->data.PRINT_USING_SFML(g[i]);
                }
                else{
                    temp->data.FLIGHT_PRINT(s);
                }
                temp = temp->next;
                i++;
            }
            cout<<ANSI_COLOR_BOLD_GREEN<<"\t|___________________________________________________________________________________________________________________________________|"<<ANSI_COLOR_RESET<<endl;
        }


        // GET THE TOTAL PRICE OF EACH NODES PATH.
        double GET_COST(){
            double COST = 0;
            NODE_FLIGHT_DATA* temp = this->head;
            while(temp!= NULL){
                COST += temp->data.ticket_price;
                temp = temp->next;
            }
            return COST;
        }

        // FUNCTION TO RETURN FLIGHT WITH MINIMUM COST OF TRAVEL.
        FLIGHT_DATA GET_MIN_COST_FLIGHT(){
            double min_cost = INT_MAX;
            NODE_FLIGHT_DATA* temp = this->head;
            FLIGHT_DATA min_flight;
            while(temp!= NULL){
                if(temp->data.ticket_price < min_cost){
                    min_cost = temp->data.ticket_price;
                    min_flight = temp->data;
                }
                temp = temp->next;
            }
            return min_flight;
        }

        // CHECK IF THE LIST IS EMPTY.
        bool IS_EMPTY(){
            return this->head == NULL;
        }


        // DESTRUCTOR OF CLASS.
        ~FLIGHT_LIST(){
            while(!this->IS_EMPTY()){
                this->REMOVE_VISITED_HEAD();
            }
        }

};



//** LAYOVER MANAGEMENT CLASS. *///NOTE - 
class LAY_OVER{
    public:
        string source;
        string destination;
        double flight_time;
        double LOV_TIME;
        double price;

        
        // USER DEFINED DEFAULT CONSTRUCTOR.
        LAY_OVER(const string& src="", const string& dest="", double t=0, double l=0, double p=0){
            this->source = src;
            this->destination = dest;
            this->flight_time = t;
            this->LOV_TIME = l;
            this->price = p;
        }


        void PRINT_HEADER(){
            cout<<ANSI_COLOR_BOLD_RED<<"\n\t--------------------------------------------------------------------------------------------";
            cout<<"\n\t|     SOURCE     |   DESTINATION    |     FLYING TIME   |   LAYOVER TIME  |  TICKET_PRICE  |";
            cout<<"\n\t--------------------------------------------------------------------------------------------"<<ANSI_COLOR_RESET<<endl;
        }

        // PRINT FUNCTION FOR LAYOVER MANAGEMENT.//ANCHOR - 
        void PRINT(string s=""){
            if(FLAG==0){
                PRINT_HEADER();
                FLAG=1;
            }
            else{
                cout<<ANSI_COLOR_BOLD_GREEN<<left<<"\t| "<<setw(14)<<this->source<<" | "<<setw(16)<<this->destination<<" | "<<setw(17)<<this->flight_time<<" | "<<setw(15)<<this->LOV_TIME<<" | "<<setw(14)<<this->price<<" | ";
                cout<<endl;
            }
        }

        // DESTRUCTOR.
        ~LAY_OVER(){
            // NOTIHING TO DO HERE AS EVERY THING IS STATIC.
        }
};


// MAKING A NODE CLASS FOR LAYOVER.
class NODE_LAYOVER{
    
    public:
        LAY_OVER data;
        NODE_LAYOVER* next;
        
        // USER DEFINED DEFAULT CONSTRUCTOR.
        NODE_LAYOVER(const LAY_OVER& layover){
            this->data = layover;
            this->next = NULL;
        }

        // DESTRUCTOR.
        ~NODE_LAYOVER(){
            // NOTIHING TO DO HERE AS EVERY THING IS STATIC.
        }

};


//** MAKINF THE LAYOVER_QUEUE CLASS. [AS PER REQUIREMENTS] */
class LAYOVER_QUEUE{

    private:

        NODE_LAYOVER* front;
        NODE_LAYOVER* rear;
        int count;
    
    public:

        // USER DEFINED DEFAULT CONSTRUCTOR.
        LAYOVER_QUEUE(){
            this->front = NULL;
            this->rear = NULL;
            this->count = 0;
        }

        // INSERTION FUCTION. [FIRST IN FIRST OUT]
        void INSERT(const LAY_OVER& layover){
            NODE_LAYOVER* new_node = new NODE_LAYOVER(layover);
            if(this->rear == NULL){
                this->front = this->rear = new_node;
            }
            else{
                this->rear->next = new_node;
                this->rear = new_node;
            }
            this->count++;
        }

        // DELETION FUNCTION. [FIRST IN FIRST OUT]
        void DEL_ME(){
            if(this->front == NULL){
                cout<<"\n LAYOVER QUEUE IS EMPTY. \n";
                return;
            }
            NODE_LAYOVER* temp = this->front;
            this->front = this->front->next;
            if(this->front == NULL){
                this->rear = NULL;
            }
            delete temp;
            this->count--;
        }


        // ACCULATE THE LAYOVER TIME.
        double GET_TOTAL_LAYOVER(){
            double total_time = 0;
            NODE_LAYOVER* temp = this->front;
            while(temp!= NULL){
                total_time += temp->data.LOV_TIME;
                temp = temp->next;
            }
            return total_time;
        }

        // CHECK IF QUEUE IS EMPTY.
        bool IS_EMPTY(){
            return this->front == NULL;
        }

        // GET THE SIZE OF QUEUE.
        int SIZE(){
            return this->count;
        }

        // GET THE FIRST ELEMENT IN QUEUE.
        LAY_OVER PEEK(){
            if(this->front == NULL){
                cout<<"\n LAYOVER QUEUE IS EMPTY. \n";
                return LAY_OVER();
            }
            return this->front->data;
        }


        // PRINT THE QUEUE.
        void PRINT(){
            if(this->front == NULL){
                cout<<"\n LAYOVER QUEUE IS EMPTY. \n";
                return;
            }
            cout<<ANSI_COLOR_BOLD_YELLOW<<"\n\t-------------------------------------------------------------------------------------------";
            cout<<"\n\t|                                    {   LAYOVER TIME   }                                  |";

            NODE_LAYOVER* temp = this->front;
            while(temp!= NULL){
                temp->data.PRINT();
                temp = temp->next;
            }
            cout<<ANSI_COLOR_BOLD_GREEN<<"\t|__________________________________________________________________________________________|"<<ANSI_COLOR_RESET<<endl;
            double sum = 0;
            sum =  this->GET_TOTAL_LAYOVER();
            cout<<ANSI_COLOR_BOLD_YELLOW<<"\t|                 < TOTAL LAYOVER TIME OF YOUR FLIGHTS >               ::    "<<left<<setw(14)<<sum<<"|"<<endl;
            cout<<"\t|__________________________________________________________________________________________|"<<ANSI_COLOR_RESET<<endl<<endl;

        }

        // DESTRUCTOR.
        ~LAYOVER_QUEUE(){
            while(!this->IS_EMPTY()){
                this->DEL_ME();
            }
        }
};


//** MAING A NODE CLASS. */
class Node{
    public:

        FLIGHT_DATA data;
        Node* next;

        // CONSTRUCTORS.
        Node(){
            this->next = NULL;
        }

        // DESTRUCTOR.
        ~Node(){
            //I ANT DOING ANYTHING HERE...
        }

};


//** MAKING A GRAPH CLASS. *//NOTE - 
class NAV_GRAPH : public HOTEL_CHARGE_LIST{

    public:

        static const int MAX_CITIES = 300;
        string UNIQUE_CITY[MAX_CITIES];

        Node* ADJ_LIST[MAX_CITIES];
        int count;
 
        string printed_paths[MAX_CITIES]; 
        static int path_count;
        int FLIGHT_EXISTS=0;
        static int LOV_COUNT;
        static double COST;


        // HELPER FUNCTION TO FIND THE INDEX OF A CITY.
        int FIND_CITY(const string& city_name){
            for(int i=0; i<count; i++){
                if(UNIQUE_CITY[i] == city_name){
                    return i;
                }
            }
            UNIQUE_CITY[count] = city_name;
            return count++;
        }

    public:

        // CONSTRUCTOR.
        NAV_GRAPH(){
            this->count = 0;
            for(int i=0; i<MAX_CITIES; i++){
                this->ADJ_LIST[i] = NULL;
            }
        }


        // FUNCTION TO SEARCH FOR FLIGHT BASED ON [ORIGIN, DESTINATION, AND DATE OF TRAVEL]
        FLIGHT_DATA FIND_FLIGHT(const string& origin, const string& destination, const string& date){
            
            int origin_index = FIND_CITY(origin);
            Node* temp = ADJ_LIST[origin_index];
            
            while(temp!= nullptr){
                if(temp->data.destination == destination &&
                    temp->data.date_of_travel == date){
                    return temp->data;
                }
                temp = temp->next;
            }
            return FLIGHT_DATA();
        }


        // ADD FLIGHT CONNECTION.
        void MAKE_CONNECT(const string& origin, const string& destination, const string& date, const string& fly_time, const string& land_time, double price, const string& airline){
            
            int origin_index = FIND_CITY(origin);
            Node* temp = ADJ_LIST[origin_index];

            while(temp != nullptr){
                if(temp->data.destination == destination &&
                    temp->data.date_of_travel == date &&
                    temp->data.TAKE_OFF == fly_time &&
                    temp->data.LAND == land_time &&
                    temp->data.ticket_price == price &&
                    temp->data.airline == airline){
                    return;
                }
                temp = temp->next;
            }

            Node* new_node = new Node();
            new_node->data.APPOINT(origin , destination, date, fly_time, land_time, price, airline);
            new_node->next = ADJ_LIST[origin_index];
            ADJ_LIST[origin_index] = new_node;
        }


        // LOAD FLIGHT DATA FROM FILE.
        void READ_FILE(const string& file_name){
            
            ifstream file(file_name);
            if(!file){
                cerr<<"\n ERROR OPENING FILE NAME: "<<file_name<<endl;
                return;
            }

            string line;
            string origin, destination, date, fly_time, land_time, airline;
            double price;

            while(getline(file, line)){
                istringstream iss(line);
                if(!(iss >> origin >> destination >> date >> fly_time >> land_time >> price >> airline)){
                    cerr<<"ERROR PROCESSING LINE: "<<line<<endl;
                    continue;
                }
                MAKE_CONNECT(origin, destination, date, fly_time, land_time, price, airline);
            }
            file.close();
        }


        // PRINT GRAPH FUNCTION.
        void print_graph(string s=""){
            PC=0;
            for(int i=0; i<count; i++){
                FLAG=0;
                cout<<"\n ORIGIN : "<<UNIQUE_CITY[i]<<endl;
                Node* temp = ADJ_LIST[i];
                while(temp!= NULL){
                    temp->data.FLIGHT_PRINT(s);
                    temp = temp->next;
                }
                cout<<ANSI_COLOR_BOLD_GREEN<<"\t|___________________________________________________________________________________________________________________________________|"<<ANSI_COLOR_RESET<<endl;
            }
        }


        // FIND THE FLIGHT WITH LEAST TRAVEL TIMES.
        string SHORTEST_ROUTE(const string& origin, const string& destination , int GUI=0 , int TMN=0){//NOTE - 

            int Org_idx = FIND_CITY(origin);  
            int Dest_idx = FIND_CITY(destination);
            string save_me[MAX_CITIES];
            string save_date;
            string fk_it;
            string air;

            int c=0;

            if(Org_idx >= count || Dest_idx >= count){  
                cout<<"\n INVALID ORIGIN OR DESTINATION.\n";  
                return "";  
            }  

            double travel_time[MAX_CITIES];  
            double travel_cost[MAX_CITIES];  
            bool visited[MAX_CITIES];  
            int previous[MAX_CITIES];  
 
            for(int i=0 ; i<MAX_CITIES ; i++){
                travel_time[i] = numeric_limits<double>::max();
                travel_cost[i] = numeric_limits<double>::max();  
                visited[i] = false;  
                previous[i] = -1;  
            }  

            travel_time[Org_idx] = 0;  
            travel_cost[Org_idx] = 0;  

            for(int i=0 ; i<count ; i++){
               
                int min_index = -1;  
                double min_value = numeric_limits<double>::max();  

                for(int j=0 ; j<count ; j++){
                    if(!visited[j] && travel_time[j]<min_value){
                        min_value = travel_time[j];  
                        min_index = j;  
                    }
                }

                if(min_index == -1){
                    break;
                }  

                visited[min_index] = true;  

                // GIVE RELAXATION TO 
                Node* temp = ADJ_LIST[min_index];  
                while(temp){
                    
                    int dest_index = FIND_CITY(temp->data.destination);

                    string DEPARTURE = temp->data.TAKE_OFF;
                    string LANDING = temp->data.LAND;

                    int dep_hours = stoi(DEPARTURE.substr(0, 2));
                    int dep_minutes = stoi(DEPARTURE.substr(3, 2));  
                    int Total_dep_min = dep_hours * 60 + dep_minutes;  

                    int arr_hours = stoi(LANDING.substr(0, 2));  
                    int arr_minutes = stoi(LANDING.substr(3, 2));  
                    int Total_arr_min = arr_hours * 60 + arr_minutes;

                    if(Total_arr_min<Total_dep_min){
                        Total_arr_min += 1440;  // Handle midnight wraparound
                    }

                    double flight_time = (Total_arr_min - Total_dep_min) / 60.0;
                    double ticket_price = temp->data.ticket_price;  

                    if(travel_time[min_index] + flight_time<travel_time[dest_index]){
                        travel_time[dest_index] = travel_time[min_index] + flight_time;  
                        travel_cost[dest_index] = travel_cost[min_index] + ticket_price;  
                        previous[dest_index] = min_index;  
                    }  
                    temp = temp->next;  
                }
            }  

            if(travel_time[Dest_idx] == numeric_limits<double>::max()){
                cout<<"\n NO ROUTE FOUND FROM [ "<<origin<< " ] TO [ "<<destination<<" ]\n";  
            }
            else{
                cout<<"\n MINIMUM TRAVEL TIME FROM [ "<<origin<<" ] TO [ "<<destination<<" ]: "<<travel_time[Dest_idx]<<" hours\n";
                cout<<" TOTAL COST: $"<<travel_cost[Dest_idx]<<"\n";
                // date 
                save_date = ADJ_LIST[Org_idx]->data.date_of_travel;
                air = ADJ_LIST[Org_idx]->data.airline;

                cout<<" PATH: ";
                int path[MAX_CITIES], path_length = 0;  
                for(int current=Dest_idx ; current != -1 ; current=previous[current]){
                    path[path_length++] = current;
                }
                for(int i=path_length-1 ; i>=0 ; i--){  
                    cout<<UNIQUE_CITY[path[i]];
                    fk_it += UNIQUE_CITY[path[i]];
                    save_me[c] += UNIQUE_CITY[path[i]];
                    c++;
                    if(i> 0){
                        fk_it += " -> ";
                        cout<<" -> ";
                    }
                }  
                cout<<endl;  
            }

        return fk_it;
        }


        // FUNCTION TO GET THE ROUTE WITH MINIMUM PRICE.
        double GET_MIN_PRICE(const string& origin, const string& destination , int f=0){

            int Org_idx = FIND_CITY(origin);
            int Dest_idx = FIND_CITY(destination);

            if(Org_idx >= count || Dest_idx >= count){
                cout<<" INVALID ORIGIN OR DESTINATION.\n";
                return 0;
            }

            double min_price[MAX_CITIES];
            bool visited[MAX_CITIES];

            for(int i=0 ; i<MAX_CITIES ; i++){
                min_price[i] = 1e9;
                visited[i] = false;
            }
            
            min_price[Org_idx] = 0;

            for(int i=0 ; i<count ; i++){
                int min_index = -1;
                double min_value = 1e9;

                for(int j=0 ; j<count ; j++){
                    if(!visited[j] && min_price[j] < min_value){
                        min_value = min_price[j];
                        min_index = j;
                    }
                }

                if(min_index == -1){
                    break;
                }
                visited[min_index] = true;

                // GIVE RELAXATION.
                Node* temp = ADJ_LIST[min_index];
                while(temp){
                    int dest_index = FIND_CITY(temp->data.destination);
                    if(min_price[min_index] + temp->data.ticket_price < min_price[dest_index]){
                        min_price[dest_index] = min_price[min_index] + temp->data.ticket_price;
                    }
                    temp = temp->next;
                }
            }

            if(min_price[Dest_idx] == 1e9){
                cout<<"\n NO ROUTE FOUND FROM [ "<<origin<<" ] TO [ "<<destination<<" ]  \n";
            }
            else{
                cout<<"\n MINIMUM PRICE FROM [ "<<origin<<" ] TO [ "<<destination<<" ] : "<<min_price[Dest_idx]<<"  \n";
            }
            return min_price[Dest_idx];
        }


        // SEE ALL THE POSSIBLE FLIGHTS FROM SOURCE TO DESTINATION [DIRECT].
        FLIGHT_DATA LIST_DIRECT_FLIGHTS(const string& origin, const string& destination , int DF_FLIGHT=0 , int GUI=0 , int VIA_TIME=0){

            FLAG=0;
            PC=0;
            int origin_index = FIND_CITY(origin);
            int destination_index = FIND_CITY(destination);

            if(origin_index >= count || destination_index >= count){
                cout<<" INVALID ORIGIN OR DESTINATION.\n";
                return FLIGHT_DATA();
            }

            cout<<"\n ALL DIRECT ROUTES FROM  [ "<<origin<<" ] TO  [ "<<destination<<" ]  ::  \n";

            Node* temp = ADJ_LIST[origin_index];
            FLIGHT_LIST L;
            bool route_found = false;

            while(temp){
                if(temp->data.destination == destination){
                    route_found = true;
                    if(VIA_TIME==0){
                        if(GUI==0){
                            temp->data.origin=origin;
                            temp->data.FLIGHT_PRINT();
                        }
                        else{
                            temp->data.FLIGHT_PRINT();
                            temp->data.PRINT_USING_SFML(origin);
                        }
                    }
                    L.INSERT(temp->data);
                }
                temp = temp->next;
            }
            cout<<ANSI_COLOR_BOLD_GREEN<<"\t|___________________________________________________________________________________________________________________________________|"<<ANSI_COLOR_RESET<<endl;

            if(!route_found){
                cout<<"\n NO DIRECT ROUTE FOUND FROM [ "<<origin<<" ] TO [ "<<destination<<" ]  \n";
                this->FLIGHT_EXISTS=-1;
            }

            if(DF_FLIGHT == 1 && this->FLIGHT_EXISTS !=-1){
                int flight_num;
                cout<<"\n ENTER FLIGHT NUMBER TO BOOK : ";
                cin>>flight_num;
                while(flight_num < 0 || flight_num>L.count){
                    cout<<"\n INVALID FLIGHT NUMBER. TRY AGAIN : ";//NOTE - 
                    cin>>flight_num;
                }

                FLIGHT_DATA F = L.GET_AT(flight_num);
                return F;
            }
            else{
                return FLIGHT_DATA();
            }
        }


        ////////////////////////////////////////////////////////////////////////////


        // REMOVE DUPLICATES FROM THE ARRAY IN IN-DIRECT PATHS.
        void REMOVE_DUPLICATES(){

            string unique[MAX_CITIES];
            int count = 0;

            for(int i=0 ; i<path_count ; i++){
                bool is_duplicate = false;

                for(int j=0 ; j<count ; j++){
                    if(printed_paths[i] == unique[j]){
                        is_duplicate = true;
                        break;
                    }
                }
                if(!is_duplicate){
                    unique[count++] = printed_paths[i];
                }
            }

            for(int i=0 ; i<count ; i++){
                printed_paths[i] = unique[i];
            }
            path_count = count;
        }


        // SEE IF THE PATH IS UNIQUE [INDIRECT]. 
        bool UNIQUE_INDIRECT(const string& path_str){
            for(int i=0 ; i<path_count ; i++){
                if(printed_paths[i] == path_str){  
                    return false;
                }
            }
            return true;
        }  


        // DFS TRAVERSAL TO GET ALL THE INDIRECT PATHS. 
        void DFS(int crr_city, int dest_city, bool visited[], string path[], int path_length){

            visited[crr_city] = true;
            path[path_length] = UNIQUE_CITY[crr_city];
            path_length++;

            if(crr_city == dest_city){
                if(path_length > 1){

                    string path_str;  
                    for(int i=0 ; i<path_length-1 ; i++){
                        path_str += path[i] + " -> ";  
                    }  
                    path_str += path[path_length - 1];  
 
                    if(UNIQUE_INDIRECT(path_str)){
                        printed_paths[path_count++] = path_str;
                        cout << path_str << endl;
                    }  
                }
            }
            else{  
                Node* temp = ADJ_LIST[crr_city];  
                while(temp != NULL){
                    int next_city = FIND_CITY(temp->data.destination);  
                    if(!visited[next_city]){  
                        DFS(next_city, dest_city, visited, path, path_length);  
                    }  
                    temp = temp->next;  
                }  
            }  
            visited[crr_city] = false;
        }


        // FUNCTION TO LIST ALL THE INDIRECT PATHS. 
        void LIST_INDIRECT_FLIGHTS(const string& origin, const string& destination , int GUI=0){
            
            FLAG=0;
            PC=0;
            int origin_index = FIND_CITY(origin);  
            int destination_index = FIND_CITY(destination);  

            if(origin_index>=count || destination_index>=count){  
                cout<<"\n INVALID ORIGIN OR DESTINATION.\n";  
                return;
            }  

            bool visited[MAX_CITIES] = {false};
            string path[MAX_CITIES]; 
            path_count = 0;

            cout<<"\n ALL INDIRECT ROUTES FROM [ "<<origin<<" ] TO [ "<<destination<<" ] :: \n";  
            DFS(origin_index, destination_index, visited, path, 0);
            this->REMOVE_DUPLICATES();
        }


        // GET THE CIRIES SEPERATED IN INDIRECT PATHS TO FIND THE DIRECT PATHS.
        void SPLIT_CITIES(const string& path, string cities[], int& city_count) {
            
            city_count = 0;
            string city = "";

            for(int i=0 ; i<path.length() ; i++){
                if(path.substr(i, 4) == " -> "){
                    cities[city_count++] = city;
                    city = "";
                    i += 3;
                }
                else{
                    city += path[i];
                }
            }
            cities[city_count++] = city;
        }


        ////////////////////////////////////////////////////////////////////////////

        // FUNCTION TO FIND FLIGHT DATA BASED ON CRITERIA
        FLIGHT_DATA FIND_FLIGHT_DF(const string& origin, const string& destination , const string& AIR_L){

            int Org_idx = FIND_CITY(origin);
            int Dest_idx = FIND_CITY(destination);

            if(Org_idx >= count || Dest_idx >= count){
                cout<<"\n INVALID ORIGIN OR DESTINATION.\n";
                return FLIGHT_DATA();
            }
            
            double min_price = this->GET_MIN_PRICE(origin, destination);

            if(min_price == 1e9){
                cout<<"\n NO VALID ROUTE FOUND FROM "<<origin<<" TO  ["<<destination <<"].\n";
                return FLIGHT_DATA();
            }

            FLIGHT_DATA best_flight;
            Node* temp = ADJ_LIST[Org_idx];
            
            while(temp){
                FLIGHT_DATA crr_flight = temp->data;

                if(crr_flight.destination == destination && crr_flight.ticket_price == min_price && crr_flight.airline == AIR_L){
                    best_flight = crr_flight;
                    break;
                }
                temp = temp->next;
            }

            if(best_flight.IS_EMPTY()){
                
                cout<<"\n NO FLIGHT FOUND FROM [ "<<origin<<" ] TO [ "<<destination<<" ] WITH AIRLINE "<<AIR_L<<".\n";
                cout<<" LOOKING FOR OTHER AIRLINE OPTIONS. \n";
                // IF IN CASE THE SELECTED AIRLINE IS NOT FOUND THEN SKIP THAT CHECK.
                temp = ADJ_LIST[Org_idx];
                
                while(temp){
                    FLIGHT_DATA crr_flight = temp->data;

                    if(crr_flight.destination == destination && crr_flight.ticket_price == min_price){
                        best_flight = crr_flight;
                        break;
                    }
                    temp = temp->next;
                }
            }
            return best_flight;
        }


        ////////////////////////////////////////////////////////////////////////////

        // MANAGE HOURS AND MINUTES AS WELL.
        double TRANSLATE_TIME(const string& time){
            int hrs = stoi(time.substr(0, 2));
            int min = stoi(time.substr(3, 2));
            return hrs + (min / 60.0);
        }


        // THIS FUNCION WORKS PARALLEL WITH SOME GLOBAL VARIABLES TO GET THE RIGHT LAYOVER TIME.
        LAY_OVER SHOW_LAYOVER(const string& org, const string& dest){

            int org_idx = FIND_CITY(org);
            int dest_idx = FIND_CITY(dest);

            if (org_idx >= count || dest_idx >= count) {
                cout << "\n INVALID ORIGIN OR DESTINATION.\n";
                return LAY_OVER();
            }

            double DURATION = 0;
            double LOV_TIME = 0;

            FLIGHT_DATA INF = FIND_FLIGHT_DF(org , dest , "");

            if(INF.IS_EMPTY()){
                cout << "\n NO DIRECT OR CONNECTING FLIGHT AVAILABLE.\n";
                return LAY_OVER();
            }

            DURATION += stod(INF.LAND) - stod(INF.TAKE_OFF);
            if(DURATION < 0){
                DURATION += 24;        // MIDNIGHT WRAP AROUND.
            }
            COST = 0;
            COST += INF.ticket_price;
            

            if(LOV_COUNT==0){
                LOV_COUNT++;
                PREV_LAND = INF.LAND;       // PREV_LAND WILL SAVE THE VALUE OF LANDING TIME OF FLIGHT.
                return LAY_OVER(org, dest, DURATION, 0 , COST);
            }
            else{
                LOV_TIME = stod(INF.TAKE_OFF) - stod(PREV_LAND);
                if(LOV_TIME < 0){
                    LOV_TIME += 24;      // MIDNIGHT WRAP AROUND.
                }
                PREV_LAND = INF.LAND;       // UPDATE PREV_LAND WITH LANDING TIME OF CURRENT FLIGHT.
                return LAY_OVER(org, dest, DURATION, LOV_TIME, COST);
            }
        }

        // RESET STATIC VARIABLES [MUST CALL THIS AS IT IS NECESSARY...]
        void RESET_STATIC_VARS() {
            LOV_COUNT = 0;
            COST = 0;
            PREV_LAND = "";
        }



        ////////////////////////////////////////////////////////////////////////////

        // DESTRUCTOR.
        ~NAV_GRAPH() {
            // Deallocate the adjacency list
            for (int i = 0; i < count; i++) {
                Node* temp = ADJ_LIST[i];
                while (temp != NULL) {
                    Node* to_delete = temp;
                    temp = temp->next;
                    delete to_delete;
                }
            }
        }

        
};


int NAV_GRAPH :: path_count=0;
int NAV_GRAPH :: LOV_COUNT=0;
double NAV_GRAPH :: COST=0;


//** MAKING ADMIN CLASS [ADMIN CAN ADD NEW ROUTE, DELETE AND CAN EDIT THE PRICE OF A PARTICULAR ROUTE ONLY.] */
class ADMIN : public NAV_GRAPH{


    private:

        string name;
        string password;
    
    public:

        //* CONSTRUCTORS *//
        ADMIN(string n="", string p=""){
            this->name = n;
            this->password = p;
        }


        // READ ALL THE FLIGHTS DATA IN LINKED LIST.
        void LOAD_FLIGHTS(FLIGHT_LIST& lst){

            ifstream read("Flights.txt");
            if(!read){
                cout<<"\n FILE NOT FOUND...";
                return;
            }
            else{
                string dest, src, date, airline, take_off, land;
                double price;
                
                while(read>>dest>>src>>date>>take_off>>land>>price>>airline){
                    FLIGHT_DATA temp(dest, src, date, take_off, land, price, airline );
                    lst.INSERT(temp);
                }
                read.close();
            }
        }


        //*VERIFICATION FUNCTION.*//
        bool LOGIN_VERIFY(){

            string compare_1;
            string compare_2;

            cout<<"\n ENTER THE ADMIN NAME : ";
            cin>>this->name;
            cout<<"\n ENTER THE ADMIN PASSWORD : ";
            cin>>this->password;

            string decrypted_name = XOR_CIPHER(this->name , "key");
            string decrypted_password = XOR_CIPHER(this->password , "key");

            ifstream pass("admin_pass.txt" , ios::in );     //OPEN FILE IN READING MODE...

            if(!pass){
                cout<<"\n FILE NOT FOUND...";
                return false;
            }

            while(!pass.eof() ){
                
                pass>>compare_1>>compare_2;
                if( compare_1 == decrypted_name &&  compare_2== decrypted_password ){
                    pass.close();
                    return true;        // GRANTING ACCESS...
                }
            }
                
            pass.close();       // CLOSING THE FILE...

            return false;           // DENYING ACCESS...
        }


        //*ADD NEW ROUTE.*//
        void ADD_NEW_ROUTE(){
            string org, dest, date , airline, land_time, take_off, price;

            cout<<"\n  ____________________________________\n";
            cout<<"\n |  ENTER THE ORIGIN OF FLIGHT  :: \n";
            cin>>org;
            cout<<"\n |  ENTER THE DESTINATION OF FLIGHT :: \n";
            cin>>dest;
            cout<<"\n |  ENTER THE DATE OF FLIGHT      :: \n";
            cin>>date;
            cout<<"\n |  ENTER THE AIRLINE NAME         :: \n";
            cin>>airline;
            cout<<"\n |  ENTER THE LANDING TIME         :: \n";
            cin>>land_time;
            cout<<"\n |  ENTER THE TAKE-OFF TIME          :: \n";
            cin>>take_off;
            cout<<"\n |  ENTER THE PRICE OF FLIGHT       :: \n";
            cin>>price;


            // WE WILL APPEND DATA DIRECTLY TO FILE.
            ofstream write("Flights.txt", ios::app);

            if(!write){
                cout<<"\n ERROR: COULD NOT OPEN FILE.\n";
                return;
            }
            write<<endl<<org<<" "<<dest<<" "<<date<<" "<<take_off<<" "<<land_time<<" "<<price<<" "<<airline;
            write.close();

            return;
        }


        // EDIT PRICE OF A FLIGHT. [READ DATA IN FLIGHT_LIST AND THE UPDATE THE FLIGHT PRICE]
        // BASED ON SOURCE , DESTINATION AND DATE OF TRAVELL.
        void EDIT_PRICE(FLIGHT_LIST& lst){
            string org, dest, date;
            double new_price;

            cout<<"\n  ____________________________________\n";
            cout<<"\n |  ENTER THE ORIGIN OF FLIGHT  :: \n";
            cin>>org;
            cout<<"\n |  ENTER THE DESTINATION OF FLIGHT :: \n";
            cin>>dest;
            cout<<"\n |  ENTER THE DATE OF FLIGHT      :: \n";
            cin>>date;
            cout<<"\n |  ENTER THE NEW PRICE OF FLIGHT   :: \n";
            cin>>new_price;

            bool yes=false;
            NODE_FLIGHT_DATA* temp = lst.head;
            while(temp!=NULL){
                if(temp->data.destination == dest && temp->data.origin == org && temp->data.date_of_travel == date){
                    temp->data.ticket_price = new_price;
                    yes=true;
                    break;
                }
                temp = temp->next;
            }
            if(yes){
                cout<<"\n PRICE UPDATED SUCCESSFULLY.\n";
            }
            else{
                cout<<"\n NO SUCH ROUTE FOUND.\n";
            }

            // UPDATE DATA IN FILE AS WELL.
            ofstream write("Flights.txt", ios::trunc);
            if(!write){
                cout<<"\n ERROR: COULD NOT OPEN FILE.\n";
                return;
            }
            else{
                NODE_FLIGHT_DATA* temp = lst.head;
                while(temp!=NULL){
                    write<<temp->data.origin<<" "<<temp->data.destination<<" "<<temp->data.date_of_travel<<" "<<temp->data.TAKE_OFF<<" "<<temp->data.LAND<<" "<<temp->data.ticket_price<<" "<<temp->data.airline<<endl;
                    temp = temp->next;
                }
                write.close();
                cout<<"\n DATA UPDATED SUCCESSFULLY.\n";
            }

            return;
        }


        //*DELETE A ROUTE.*//
        void DELETE_ROUTE(FLIGHT_LIST& lst){
            
            string org, dest, date;
            cout<<"\n  ____________________________________\n";
            cout<<"\n |  ENTER THE ORIGIN OF FLIGHT  :: \n";
            cin>>org;
            cout<<"\n |  ENTER THE DESTINATION OF FLIGHT :: \n";
            cin>>dest;
            cout<<"\n |  ENTER THE DATE OF FLIGHT      :: \n";
            cin>>date;

            
            bool yes=false;
            NODE_FLIGHT_DATA* temp = lst.head;
            while(temp!=NULL){
                if(temp->data.destination == dest && temp->data.origin == org && temp->data.date_of_travel == date){
                    lst.DELETE_PASSED_DATA(temp->data);
                    yes=true;
                    break;
                }
                temp = temp->next;
            }
            if(yes){
                cout<<"\n ROUTE DELETED SUCCESSFULLY.\n";
            }
            else{
                cout<<"\n NO SUCH ROUTE FOUND.\n";
            }

            // UPDATE DATA IN FILE AS WELL.
            ofstream write("Flights.txt", ios::trunc);
            if(!write){
                cout<<"\n ERROR: COULD NOT OPEN FILE.\n";
                return;
            }
            else{
                NODE_FLIGHT_DATA* temp = lst.head;
                while(temp!=NULL){
                    write<<temp->data.origin<<" "<<temp->data.destination<<" "<<temp->data.date_of_travel<<" "<<temp->data.TAKE_OFF<<" "<<temp->data.LAND<<" "<<temp->data.ticket_price<<" "<<temp->data.airline<<endl;
                    temp = temp->next;
                }
                write.close();
                cout<<"\n DATA UPDATED SUCCESSFULLY.\n";
            }
        }


        //** A KIND OF LOCAL MAIN FOR ADMIN FUNCTIONALITIES HANDELING. */
        void ADMIN_MENUE(){

            bool GRANT_PERMIT = this->LOGIN_VERIFY();
            // NAME = BILLA <-> PASSWORD = 1234

            if(GRANT_PERMIT){
                LOADING_LINE();
                
                ADMIN_PLAYS();

                // WE WILL SEARCH DATA IN FLIGHT_LIST AND UPDATE THE PRICE.
                FLIGHT_LIST lst;
                LOAD_FLIGHTS(lst);

                char choice;

                while(true){
                    
                    cout<<endl<<endl;
                    cout<<ANSI_COLOR_BOLD_RED<<"\t\t  ____________________________________________"<<endl;
                    cout<<"\t\t ||             ADMINISTRATOR MENU           || \n";
                    cout<<"\t\t ||__________________________________________||"<<ANSI_COLOR_RESET<<endl;
                    cout<<ANSI_COLOR_BOLD_YELLOW<<"\t\t ||     [A]   ADD NEW ROUTE.                 || \n";
                    cout<<"\t\t ||     [B]   DELETE A ROUTE.                || \n";
                    cout<<"\t\t ||     [C]   EDIT PRICE OF A ROUTE.         || \n";
                    cout<<"\t\t ||     [D]   SEE ALL THE CURRENT ROUTES.    || \n";
                    cout<<"\t\t ||     [F]   SEE AIRLINE SERVICES.          || \n";
                    cout<<"\t\t ||     [E]   EXIT.                          || \n";
                    cout<<"\t\t ||             ENTER YOUR CHOICE :          || \n";
                    cout<<"\t\t ||__________________________________________||"<<endl;
                    cout<<"\t\t ||__________________________________________||"<<ANSI_COLOR_RESET<<endl;
                    cin>>choice;

                    char edit = tolower(choice);

                    // MAKE INPUT FOR CAPITAL AND SMALL LETTER
                    switch(edit){
                        case 'a':
                        {
                            this->ADD_NEW_ROUTE();
                            break;
                        }
                        case 'b':
                        {
                            this->DELETE_ROUTE(lst);
                            break;
                        }
                        case 'c':
                        {
                            this->EDIT_PRICE(lst);
                            break;
                        }
                        case 'd':
                        {
                            FLAG=0;
                            lst.PRINT();
                            cout<<ANSI_COLOR_BOLD_GREEN<<"\t|______________________________________________________________________________________________________________________________|"<<ANSI_COLOR_RESET<<endl;
                            break;
                        }
                        case 'f':
                        {
                            FLAG=0;
                            string airline;
                            cout<<"\n  ____________________________________\n";
                            cout<<"\n |  ENTER THE NAME OF AIRLINE  :: \n";
                            cin>>airline;
                            cout<<endl;
                            cout<<endl;
                            lst.PRINT(airline);
                            cout<<ANSI_COLOR_BOLD_GREEN<<"\t|__________________________________________________________________________________________________________________________________|"<<ANSI_COLOR_RESET<<endl;
                            break;
                        }
                        case 'e':
                        {
                            cout<<"\n THANK YOU FOR USING OUR FLIGHT NAVIGATION SYSTEM. \n";
                            return;
                        }
                    }
                }
            }
            else{
                cout<<"\n LOGIN UNSUCCESSFUL. [RETURNING BACK TO MAIN]\n";
            }
        }

};






#endif