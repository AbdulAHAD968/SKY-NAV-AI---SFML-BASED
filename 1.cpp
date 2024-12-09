#include "layover_queue.h"

// ==> COMMAND TO RUN  ::  {g++ -o test 1.cpp -I/usr/include/opencv4 `pkg-config --libs opencv4` -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio}
// PRE REQUIREMENTS: [SETUP SFML AND ALSO SETUP OPENCV FOR VIDEOGRAPHY]

using namespace std;

bool BOOK_FLAG=0;


//** MAKING A CLASS OF PASSENGER THAT CAN BOOK TICKETS, SELECT CUSTOOM PATHS, SHE SHORTEST AND CHEAPEST PATHS. */
class PASSENGER : public NAV_GRAPH{

    private:

        string NAME;
        string DEPT_CON;
        string ARR_CON;
        string DEPT_DATE;
        string ARR_DATE;
        string AIR_LINE;
    
    public:
    
        // USER DEFINED DEFAULT CONSTRUCTOR.
        PASSENGER(){
            this->NAME = "";
            this->DEPT_CON = "";
            this->ARR_CON = "";
            this->DEPT_DATE = "";
            this->ARR_DATE = "";
            this->AIR_LINE = "";
        }


        // TAKE INPUT.
        void INPUT(){
            cout<<"\n ENTER PASSENGER NAME  ::  ";
            cin>>this->NAME;
            cout<<"\n ENTER DEPARTURE CITY  ::  ";
            cin>>this->DEPT_CON;
            cout<<"\n ENTER ARRIVAL CITY    ::  ";
            cin>>this->ARR_CON;
            cout<<"\n ENTER DEPARTURE DATE  :: [DD/MM/YY]  ";
            cin>>this->DEPT_DATE;
            cout<<"\n ENTER ARRIVAL DATE    ::  [DD/MM/YY]  ";
            cin>>this->ARR_DATE;
            cout<<"\n ENTER AIRLINE NAME    ::  ";
            cin>>this->AIR_LINE;
        }


        void LIST_ALL_PATHS_GUI(NAV_GRAPH& v){
            
            string shortest = v.SHORTEST_ROUTE(this->DEPT_CON, this->ARR_CON, 0, 1);
            v.LIST_INDIRECT_FLIGHTS(this->DEPT_CON, this->ARR_CON);

            cout<<"\n < ALL PATHS WILL BE PRINTED ONE BY ONE > \n";
            for(int i=0 ; i<v.path_count ; i++){
                cout<<" [ "<<i<<" ]   ::   "<<v.printed_paths[i]<<endl;
            }
            cout<<"\n < SHORTEST PATH: "<<shortest<<" > \n";

            struct City{
                string name;
                float x;
                float y;
            };

            City cities[] = {
                {"Islamabad", 1180, 290}, {"Newyork", 250, 150}, {"Paris", 400, 200},
                {"Tokyo", 1000, 230}, {"London", 300, 280}, {"Singapore", 800, 300},
                {"HongKong", 850, 110}, {"Berlin", 500, 450}, {"Seoul", 1150, 150},
                {"Amsterdam", 560, 55}, {"Sydney", 870, 470}
            };

            const int numCities = sizeof(cities) / sizeof(cities[0]);

            auto LOCATE_CITY = [&](const string& name){
                for(int i=0 ; i<numCities ; i++){
                    if(name == cities[i].name){
                        return i;
                    }
                }
                return -1;
            };

            sf::RenderWindow window(sf::VideoMode(1600, 600), "ZAR NAVIGATION SYSTEM");
            sf::Texture mapTexture;

            if(!mapTexture.loadFromFile("map.png")){
                cerr<<"\n FAILED TO LOAD MAP TEXTURE!"<<endl;
                return;
            }

            sf::Sprite mapSprite(mapTexture);

            sf::Font font;
            if(!font.loadFromFile("arial.ttf")){
                cerr<<"\n FAILED TO LOAD FONTS!"<<endl;
                return;
            }

            sf::VertexArray dottedLines(sf::Lines);
            sf::VertexArray shortestPathDottedLines(sf::Lines);
            std::vector<sf::ConvexShape> arrows;

            auto createArrow = [](sf::Vector2f start, sf::Vector2f end, float arrowSize = 10.0f) {
                sf::Vector2f direction = end - start;
                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                direction /= length;

                sf::Vector2f perp(-direction.y, direction.x);
                sf::Vector2f tip = end;
                sf::Vector2f left = end - direction * arrowSize + perp * (arrowSize / 2);
                sf::Vector2f right = end - direction * arrowSize - perp * (arrowSize / 2);

                sf::ConvexShape arrow;
                arrow.setPointCount(3);
                arrow.setPoint(0, tip);
                arrow.setPoint(1, left);
                arrow.setPoint(2, right);
                arrow.setFillColor(sf::Color::Green);

                return arrow;
            };

            // Process all paths
            for (int pathIdx = 0; pathIdx < v.path_count; pathIdx++) {
                string user_choice = v.printed_paths[pathIdx];
                int city_count = 0;
                string C_BRIDGE[MAX_CITIES];
                v.SPLIT_CITIES(user_choice, C_BRIDGE, city_count);

                sf::Vector2f cityPositions[MAX_CITIES];
                for (int i = 0; i < city_count; i++) {
                    int index = LOCATE_CITY(C_BRIDGE[i]);
                    if (index == -1) {
                        cerr << "City " << C_BRIDGE[i] << " not found!" << endl;
                        continue;
                    }
                    cityPositions[i] = sf::Vector2f(cities[index].x, cities[index].y);
                }

                // Draw dotted lines and arrows for each path
                for (int i = 0; i < city_count - 1; i++) {
                    sf::Vector2f start = cityPositions[i];
                    sf::Vector2f end = cityPositions[i + 1];
                    sf::Vector2f direction = end - start;
                    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                    direction /= length;
                    const float dotSpacing = 15.0f;

                    for (float j = 0; j < length; j += dotSpacing) {
                        sf::Vector2f dotPosition = start + direction * j;
                        if (user_choice == shortest) {
                            shortestPathDottedLines.append(sf::Vertex(dotPosition, sf::Color::Yellow));
                        } else {
                            dottedLines.append(sf::Vertex(dotPosition, sf::Color::Magenta));
                        }
                    }

                    // Add an arrow to indicate direction
                    arrows.push_back(createArrow(start, end));
                }
            }

            // Variables for blinking effect
            bool showShortestPath = true;
            sf::Clock clock;
            float blinkInterval = 0.5f; // Blink every 0.5 seconds

            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                }

                // Toggle the shortest path visibility based on timer
                if (clock.getElapsedTime().asSeconds() > blinkInterval) {
                    showShortestPath = !showShortestPath;
                    clock.restart();
                }

                window.clear(sf::Color::Black);

                // Draw the map
                window.draw(mapSprite);

                // Draw city markers and labels
                for (int i = 0; i < numCities; i++) {
                    sf::CircleShape marker(5);
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

                // Draw all dotted lines
                window.draw(dottedLines);

                // Draw the blinking shortest path
                if (showShortestPath) {
                    window.draw(shortestPathDottedLines);
                }

                // Draw arrows
                for (const auto& arrow : arrows) {
                    window.draw(arrow);
                }

                window.display();
            }
        }


        void LET_ME_HANDLE_COPY(NAV_GRAPH& v , string SITT=""){

            if(SITT==""){
                v.LIST_INDIRECT_FLIGHTS(this->DEPT_CON, this->ARR_CON);
            }

                string felas;
                int choice = -1;
                double HOTEL_CHARGES = 0;

                if(SITT==""){

                    for(int i=0 ; i<v.path_count ; i++){
                        cout<<" [ "<<i<<" ]   ::   "<<v.printed_paths[i]<<endl;
                    }

                    cout<<"\n < SELECT THE PATH OF YOUR CHOICE [NUMBER ONLY IS PROCESSED] > \n";
                    for(int i=0 ; i<v.path_count ; i++){
                        cout<<" [ "<<i<<" ]   ::   "<<v.printed_paths[i]<<endl;
                    }

                    cout<<"\n  YOUR CHOICE  [-1 TO RETURN] ::  ";
                    cin>>choice;
                    if(choice == -1){
                        return;
                    }
                    while(choice < 0 || choice >= v.path_count){
                        cout<<"\n  < INVALID CHOICE. TRY AGAIN >.\n";
                        cout<<"\n  YOUR CHOICE  ::  ";
                        cin>>choice;
                    }
                }

                // City structure for visualization
                struct City{
                    string name;
                    float x;
                    float y;
                };

                City cities[] = {
                    {"Islamabad", 1180, 290}, {"Newyork", 250, 150}, {"Paris", 400, 200},
                    {"Tokyo", 1000, 230}, {"London", 300, 280}, {"Singapore", 800, 300},
                    {"HongKong", 850, 110}, {"Berlin", 500, 450}, {"Seoul", 1150, 150},
                    {"Amsterdam", 560, 55}, {"Sydney", 870, 470}
                };

                const int numCities = sizeof(cities) / sizeof(cities[0]);

                auto LOCATE_CITY = [&](const string& name){
                    for(int i=0 ; i<numCities ; i++){
                        if(name == cities[i].name){
                            return i;
                        }
                    }
                    return -1;
                };

                string user_choice;
                if(SITT==""){
                    user_choice = v.printed_paths[choice];
                }
                else{
                    user_choice = SITT;
                }
                int city_count = 0;
                string C_BRIDGE[MAX_CITIES];
                v.SPLIT_CITIES(user_choice, C_BRIDGE, city_count);

                FLIGHT_LIST L;
                LAYOVER_QUEUE Q;
                HOTEL_CHARGE_LIST H;
                H.READ_HOSTEL_CHARGE();

                cout<<ANSI_COLOR_BOLD_YELLOW<<"\n\t ______________________________________________________________________________________________________________________________";
                cout<<"\n\t|                                   =>       STARTING POINT OF JOURNEY      ::         "<<left<<setw(40)<<C_BRIDGE[0]<<"|";
                cout<<"\n\t|______________________________________________________________________________________________________________________________|";

                for(int i=0 ; i<city_count-1 ; i++){
                    felas += C_BRIDGE[i]+",";
                    FLIGHT_DATA d = v.FIND_FLIGHT_DF(C_BRIDGE[i], C_BRIDGE[i + 1], this->AIR_LINE);
                    L.INSERT(d);
                    HOTEL_CHARGES += H.GET_CHARGES_FOR_CITY(C_BRIDGE[i]);
                }

                sf::RenderWindow window(sf::VideoMode(1600, 600), "ZAR NAVIGATION SYSTEM");
                sf::Texture mapTexture;
                if(!mapTexture.loadFromFile("map.png")){
                    cerr << "Failed to load map texture!" << endl;
                    return;
                }
                sf::Sprite mapSprite(mapTexture);

                sf::Font font;
                if (!font.loadFromFile("arial.ttf")) {
                    cerr << "Failed to load font!" << endl;
                    return;
                }

                // LOAD THE AIRPLANE TEXTURE.
                sf::Texture airplaneTexture;
                if (!airplaneTexture.loadFromFile("3.png")){
                    cerr<<"\n UNABLE TO LOCATE AIRPLANE.PNG FILE. "<<endl;
                    return ;
                }

                // CONVERT BACKGROUND TO TRANSPARENT
                sf::Image airplaneImage = airplaneTexture.copyToImage();
                for (unsigned int y = 0; y < airplaneImage.getSize().y; ++y) {
                    for (unsigned int x = 0; x < airplaneImage.getSize().x; ++x) {
                        if (airplaneImage.getPixel(x, y) == sf::Color::Black) {
                            airplaneImage.setPixel(x, y, sf::Color(0, 0, 0, 0)); // Set black pixels to transparent
                        }
                    }
                }

                // Reload the modified image back into the texture
                if (!airplaneTexture.loadFromImage(airplaneImage)){
                    cerr<<"\n ERROR: UNABLE TO LOAD MODIFIED AIRPLANE TEXTURE. "<<endl;
                    return ;
                }

                // CREATING THE AIRPLANE SPRITE.
                sf::Sprite AIR_PLANE(airplaneTexture);
                AIR_PLANE.setScale(0.0999f, 0.0999f);

                sf::Vector2f cityPositions[MAX_CITIES];
                for(int i = 0; i < city_count; i++) {
                    int index = LOCATE_CITY(C_BRIDGE[i]);
                    if (index == -1) {
                        cerr<<"\n CITY "<<C_BRIDGE[i]<<" NOT FOUND. "<<endl;
                        return;
                    }
                    cityPositions[i] = sf::Vector2f(cities[index].x, cities[index].y);
                }

                size_t currentLeg = 0;
                float t = 0.0f;
                float speed = 0.1f;

                // VERTEX ARRAY TO STORE DOTED LINE.
                sf::VertexArray dottedLines(sf::Lines);

                while (window.isOpen()){

                    sf::Event event;
                    while(window.pollEvent(event)){
                        if(event.type == sf::Event::Closed){
                            window.close();
                        }
                    }

                    window.clear(sf::Color::Black);
                    window.draw(mapSprite);

                    for(int i=0 ; i<numCities ; i++){

                        sf::CircleShape marker(5);
                        
                        if(std::find( C_BRIDGE , C_BRIDGE+currentLeg+1 , cities[i].name) != C_BRIDGE+currentLeg+1){
                            marker.setFillColor(sf::Color::Green); // GREEN ARE VISITED HERE
                        }
                        else{
                            marker.setFillColor(sf::Color::Red); // RED ARE UNVISITED HERE
                        }
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

                    // PRINT ALL STORED DOTED LINES.
                    window.draw(dottedLines);

                    if(currentLeg < city_count - 1){

                        sf::Vector2f start = cityPositions[currentLeg];
                        sf::Vector2f end = cityPositions[currentLeg + 1];
                        sf::Vector2f currentPosition = (1 - t) * start + t * end;
                        AIR_PLANE.setPosition(currentPosition);

                        // Draw a dotted line from start to currentPosition
                        const float dotSpacing = 15.0f; // Distance between dots
                        sf::Vector2f direction = end - start;
                        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                        direction /= length; // Normalize direction vector

                        for(float i=0 ; i<length ; i += dotSpacing){

                            sf::Vector2f dotPosition = start + direction * i;

                            if(sqrt((dotPosition.x - start.x) * (dotPosition.x - start.x) +
                                        (dotPosition.y - start.y) * (dotPosition.y - start.y)) >
                                sqrt((currentPosition.x - start.x) * (currentPosition.x - start.x) +
                                        (currentPosition.y - start.y) * (currentPosition.y - start.y))) {
                                break; // Stop adding dots past the current position
                            }

                            // Add vertices to dottedLines
                            sf::Vertex dot(dotPosition, sf::Color::Yellow);
                            dottedLines.append(dot);
                        }

                        if(t < 1.0f){
                            t += speed * 0.04f;
                        }
                        else{
                            t = 0.0f;
                            currentLeg++;
                        }

                        // DISPLAY FLIGHT DETAILS.
                        NODE_FLIGHT_DATA* temp = L.head;
                        for(int i=0 ; i<currentLeg && temp!=nullptr ; i++){
                            temp = temp->next;
                        }
                        if(temp != nullptr){
                            const FLIGHT_DATA& flight = temp->data;
                            sf::Text flightInfo;
                            flightInfo.setFont(font);
                            flightInfo.setCharacterSize(20);
                            flightInfo.setFillColor(sf::Color::Cyan);
                            flightInfo.setString(
                                "AIRLINE      ::  " + flight.airline +
                                "\nFROM         ::  " + flight.origin +
                                "\nTOWARDS  ::  " + flight.destination +
                                "\nDATE          ::  " + flight.date_of_travel +
                                "\nCOST          ::  $" + to_string(flight.ticket_price)
                            );
                            flightInfo.setPosition(20, 470);
                            window.draw(flightInfo);
                        }
                    }
                    window.draw(AIR_PLANE);
                    window.display();
                }

                double total = L.GET_COST();
                cout<<ANSI_COLOR_BOLD_YELLOW<<"\t ______________________________________________________________________________________________________________________________";
                cout<<"\n\t|                                 =>       < TOTAL PRICE OF YOUR FLIGHTS >      ::         "<<left<<setw(36)<<total<<"|";
                cout<<"\n\t|______________________________________________________________________________________________________________________________|"<<ANSI_COLOR_RESET;


                // ASK IF USER WANTS TO SEE THE LAYOVER TIME.
                char wana_see;
                double sav_time = 0;
                cout<<"\n  < DO YOU WANT TO SEE THE LAYOVER TIME > (Y/N) ::  ";
                cin>>wana_see;

                while( ( wana_see!= 'Y'  || wana_see == 'y' ) && wana_see!= 'N'){
                    cout<<"\n  < INVALID CHOICE. TRY AGAIN >.\n";
                    cout<<"\n  < DO YOU WANT TO SEE THE LAYOVER TIME > (Y/N) ::  ";
                    cin>>wana_see;
                }
                if(wana_see == 'Y' || wana_see == 'y'){
                    for(int i=0 ; i<city_count-1 ; i++){
                        LAY_OVER d = v.SHOW_LAYOVER(C_BRIDGE[i],C_BRIDGE[i+1] );
                        Q.INSERT(d);
                    }
                    FLAG=0;
                    Q.PRINT();
                    sav_time = Q.GET_TOTAL_LAYOVER();
                }

                cout<<"\n PRESS ANY KEY TO CONTINUE...";
                cin.ignore();
                cin.get();

                // JUST GENERATE A TOKEN LIKE TICKET WITH NAME, PRICE, FLIGHTS
                if(BOOK_FLAG){
                    BOOK_FLAG=0;

                    cout<<ANSI_COLOR_BOLD_YELLOW<<endl;
                    cout<<"\t\t\t\t\t\t\t    _________________ ____________ "<<endl;
                    cout<<"\t\t\t\t\t\t\t   /_  __/  _/ ___/ //_/ __/_  __/ "<<endl;
                    cout<<"\t\t\t\t\t\t\t    / / _/ // /__/ ,< / _/  / /    "<<endl;
                    cout<<"\t\t\t\t\t\t\t   /_/ /___/\\___/_/|_/___/ /_/     ";
                    cout<<"\n\t__________________________________________________________________________________________________________________________________________________";
                    cout<<"\n\t|     PASSENGER NAME       ::  "<<left<<setw(115)<<this->NAME<<"|";
                    cout<<"\n\t|     DEPARTURE CITY       ::  "<<left<<setw(115)<<C_BRIDGE[0]<<"|";
                    cout<<"\n\t|     ARRIVAL CITY         ::  "<<left<<setw(115)<<C_BRIDGE[city_count-1]<<"|";
                    cout<<"\n\t|     DEPARTURE DATE       ::  "<<left<<setw(115)<<this->DEPT_DATE<<"|";
                    cout<<"\n\t|     ARRIVAL DATE         ::  "<<left<<setw(115)<<this->ARR_DATE<<"|";
                    cout<<"\n\t|     AIRLINE NAME         ::  "<<left<<setw(115)<<this->AIR_LINE<<"|";
                    cout<<"\n\t|     FLIGHTS              ::  "<<left<<setw(115)<<user_choice<<"|";
                    cout<<ANSI_COLOR_BOLD_RED<<"\n\t|     TOTAL PRICE    [$]   ::  "<<left<<setw(115)<<total<<"|";
                    cout<<ANSI_COLOR_BOLD_GREEN<<"\n\t|     LAYOVER TIME  [HRS]  ::  "<<left<<setw(115)<<sav_time<< "|";
                    cout<<ANSI_COLOR_BOLD_YELLOW<<"\n\t|_________________________________________________________________________________________________________________________________________________|"<<ANSI_COLOR_RESET<<endl;

                    char yes;
                    cout<<"\n DO YOU WANT TO SEE HOTEL CHARGES ? [y/n]";
                    cin>>yes;
                    yes = tolower(yes);
                    if(yes == 'y'){
                        cout<<ANSI_COLOR_BOLD_GREEN<<"\n\t ______________________________________________________________________________________________________________________________";
                        cout<<ANSI_COLOR_BOLD_YELLOW<<"\n\t|                                 =>       < HOTEL CHARGES >      ::         "<<left<<setw(50)<<HOTEL_CHARGES<<"|";
                        cout<<ANSI_COLOR_BOLD_GREEN<<"\n\t|______________________________________________________________________________________________________________________________|"<<ANSI_COLOR_RESET<<endl;
                        H.LIST_HOTELS_AND_CHARGES(felas);
                        cout<<"\n WANT TO SEE THE HOTEL CHARGES LIST AS WELL ??? ";
                        cin>>yes;
                        yes = tolower(yes);
                        if(yes=='y'){
                            H.PRINT_DATA();
                        }

                    }
                    else{
                        cout<<"\n\t PRESS ANY KEY TO CONTINUE...";
                        cin.get();
                    }
                }

                while(!Q.IS_EMPTY()){
                    Q.DEL_ME();
                }

                while(!L.IS_EMPTY()){
                    L.REMOVE_VISITED_HEAD();
                }
                v.RESET_STATIC_VARS();
        }


        // THIS FUNCTION IS THE BACKBONE TO MANAGE ALL THE USER SELECTED FLIGHTS.
        void LET_ME_HANDLE(NAV_GRAPH& v ){

            v.LIST_INDIRECT_FLIGHTS(this->DEPT_CON , this->ARR_CON);

            string felas;
            int choice=-1;
            double sav_time=0;
            double HOTEL_CHARGES=0;
            cout<<"\n < SELECT THE PATH OF YOUR CHOICE [NUMBER ONLY IP PROCESSED] > \n";
            for(int i=0 ; i<v.path_count ; i++){
                cout<<" [ "<<i<<" ]   ::   "<<v.printed_paths[i]<<endl;
            }
            cout<<"\n  YOUR CHOICE  [PRESS -1 TO RETURN] ::  ";
            cin>>choice;
            if(choice == -1){
                return;
            }
            while(choice<0 || choice>v.path_count){
                cout<<"\n  < INVALID CHOICE. TRY AGAIN >.\n";
                cout<<"\n  YOUR CHOICE  ::  ";
                cin>>choice;
            }

            // SELECT THE INDIRECT PATH STRING.
            string user_choice = v.printed_paths[choice];
            int city_count=0;
            string C_BRIDGE[MAX_CITIES];
            v.SPLIT_CITIES(user_choice, C_BRIDGE , city_count);

            FLIGHT_LIST L;
            LAYOVER_QUEUE Q;
            HOTEL_CHARGE_LIST H;
            H.READ_HOSTEL_CHARGE();

            for(int i=0 ; i<city_count-1 ; i++){
                felas += C_BRIDGE[i] + ",";
                FLIGHT_DATA d = v.FIND_FLIGHT_DF(C_BRIDGE[i],C_BRIDGE[i+1] , this->AIR_LINE);
                L.INSERT( d );
                HOTEL_CHARGES += H.GET_CHARGES_FOR_CITY(C_BRIDGE[i]);
            }
            cout<<ANSI_COLOR_BOLD_YELLOW<<"\n\t ______________________________________________________________________________________________________________________________";
            cout<<"\n\t|                                   =>       STARTING POINT OF JOURNEY      ::         "<<left<<setw(40)<<C_BRIDGE[0]<<"|";
            cout<<"\n\t|______________________________________________________________________________________________________________________________|";

            FLAG=0;

            L.PRINT();            

            double total = L.GET_COST();
            cout<<ANSI_COLOR_BOLD_YELLOW<<"\t ______________________________________________________________________________________________________________________________";
            cout<<"\n\t|                                 =>       < TOTAL PRICE OF YOUR FLIGHTS >      ::         "<<left<<setw(36)<<total<<"|";
            cout<<"\n\t|______________________________________________________________________________________________________________________________|"<<ANSI_COLOR_RESET;


            // ASK IF USER WANTS TO SEE THE LAYOVER TIME.
            char wana_see;
            cout<<"\n  < DO YOU WANT TO SEE THE LAYOVER TIME > (Y/N) ::  ";
            cin>>wana_see;
            while( ( wana_see!= 'Y'  || wana_see == 'y' ) && wana_see!= 'N'){
                cout<<"\n  < INVALID CHOICE. TRY AGAIN >.\n";
                cout<<"\n  < DO YOU WANT TO SEE THE LAYOVER TIME > (Y/N) ::  ";
                cin>>wana_see;
            }
            if(wana_see == 'Y' || wana_see == 'y'){
                for(int i=0 ; i<city_count-1 ; i++){
                    LAY_OVER d = v.SHOW_LAYOVER(C_BRIDGE[i],C_BRIDGE[i+1] );
                    Q.INSERT(d);
                }
                FLAG=0;
                Q.PRINT();
                sav_time=0.0;
                sav_time = Q.GET_TOTAL_LAYOVER();
            }

            cout<<"\n PRESS ANY KEY TO CONTINUE...";
            cin.ignore();
            cin.get();

            // JUST GENERATE A TOKEN LIKE TICKET WITH NAME, PRICE, FLIGHTS
            if(BOOK_FLAG){
                BOOK_FLAG=0;

                cout<<ANSI_COLOR_BOLD_YELLOW<<endl;
                cout<<"\t\t\t\t\t\t\t    _________________ ____________ "<<endl;
                cout<<"\t\t\t\t\t\t\t   /_  __/  _/ ___/ //_/ __/_  __/ "<<endl;
                cout<<"\t\t\t\t\t\t\t    / / _/ // /__/ ,< / _/  / /    "<<endl;
                cout<<"\t\t\t\t\t\t\t   /_/ /___/\\___/_/|_/___/ /_/     ";
                cout<<"\n\t__________________________________________________________________________________________________________________________________________________";
                cout<<"\n\t|     PASSENGER NAME       ::  "<<left<<setw(115)<<this->NAME<<"|";
                cout<<"\n\t|     DEPARTURE CITY       ::  "<<left<<setw(115)<<C_BRIDGE[0]<<"|";
                cout<<"\n\t|     ARRIVAL CITY         ::  "<<left<<setw(115)<<C_BRIDGE[city_count-1]<<"|";
                cout<<"\n\t|     DEPARTURE DATE       ::  "<<left<<setw(115)<<this->DEPT_DATE<<"|";
                cout<<"\n\t|     ARRIVAL DATE         ::  "<<left<<setw(115)<<this->ARR_DATE<<"|";
                cout<<"\n\t|     AIRLINE NAME         ::  "<<left<<setw(115)<<this->AIR_LINE<<"|";
                cout<<"\n\t|     FLIGHTS              ::  "<<left<<setw(115)<<user_choice<<"|";
                cout<<ANSI_COLOR_BOLD_RED<<"\n\t|     TOTAL PRICE    [$]   ::  "<<left<<setw(115)<<total<<"|";
                cout<<ANSI_COLOR_BOLD_GREEN<<"\n\t|     LAYOVER TIME  [HRS]  ::  "<<left<<setw(115)<<sav_time<< "|";
                cout<<ANSI_COLOR_BOLD_YELLOW<<"\n\t|_________________________________________________________________________________________________________________________________________________|"<<ANSI_COLOR_RESET<<endl;

                char yes;
                cout<<"\n DO YOU WANT TO SEE HOTEL CHARGES ? [y/n]";
                cin>>yes;
                yes = tolower(yes);
                if(yes == 'y'){
                    cout<<ANSI_COLOR_BOLD_GREEN<<"\n\t ______________________________________________________________________________________________________________________________";
                    cout<<ANSI_COLOR_BOLD_YELLOW<<"\n\t|                                 =>       < HOTEL CHARGES >      ::         "<<left<<setw(50)<<HOTEL_CHARGES<<"|";
                    cout<<ANSI_COLOR_BOLD_GREEN<<"\n\t|______________________________________________________________________________________________________________________________|"<<ANSI_COLOR_RESET<<endl;

                    H.LIST_HOTELS_AND_CHARGES(felas);
                    cout<<"\n WANT TO SEE THE HOTEL CHARGES LIST AS WELL ??? ";
                    cin>>yes;
                    yes = tolower(yes);
                    if(yes=='y'){
                        H.PRINT_DATA();
                    }

                }
                else{
                    cout<<"\n\t PRESS ANY KEY TO CONTINUE...";
                    cin.get();
                }
            }
            while(!Q.IS_EMPTY()){
                Q.DEL_ME();
            }

            while(!L.IS_EMPTY()){
                L.REMOVE_VISITED_HEAD();
            }
            v.RESET_STATIC_VARS();
        }


        // MAIN BOOKING FLIGHT FUNCTION.
        void BOOK_A_FLIGHT(NAV_GRAPH& ng){
            
            char choice;

            while(true){
                cout<<endl<<endl;
                cout<<ANSI_COLOR_BOLD_RED<<"\t\t  ____________________________________________________________"<<endl;
                cout<<"\t\t ||                 { PASSENGER  MENU }                      || \n";
                cout<<"\t\t ||__________________________________________________________||"<<ANSI_COLOR_RESET<<endl;
                cout<<ANSI_COLOR_BOLD_GREEN<<"\t\t ||     [A]   BOOK A DIRECT FLIGHT  {NON-STOP}               || \n";
                cout<<"\t\t ||     [B]   BOOK INDIRECT OR CONNECTING FLIGHTS            || \n";
                cout<<"\t\t ||     [R]   RETURN WITHOUT PURCHASING  [--R]               || \n";
                cout<<"\t\t ||                  ENTER YOUR CHOICE :                     || \n";
                cout<<"\t\t ||__________________________________________________________||"<<endl;
                cout<<"\t\t ||__________________________________________________________||"<<ANSI_COLOR_RESET<<endl;
                cin>>choice;

                char edit = tolower(choice);

                switch(edit){
                    case 'a':
                    {
                        FLIGHT_DATA waste = ng.LIST_DIRECT_FLIGHTS(this->DEPT_CON , this->ARR_CON , 1 , 1 );
                        if(ng.FLIGHT_EXISTS == -1){
                            cout<<"\n\t NO DIRECT FLIGHTS FOUND FOR THIS TRIP.\n";
                            break;
                        }
                        else{
                            cout<<ANSI_COLOR_BOLD_YELLOW<<endl;
                            cout<<"\t\t\t\t\t\t\t    _________________ ____________ "<<endl;
                            cout<<"\t\t\t\t\t\t\t   /_  __/  _/ ___/ //_/ __/_  __/ "<<endl;
                            cout<<"\t\t\t\t\t\t\t    / / _/ // /__/ ,< / _/  / /    "<<endl;
                            cout<<"\t\t\t\t\t\t\t   /_/ /___/\\___/_/|_/___/ /_/     ";
                            cout<<"\n\t___________________________________________________________________________________________________________________________________";
                            cout<<"\n\t|     PASSENGER NAME       ::  "<<left<<setw(100)<<this->NAME<<"|";
                            cout<<"\n\t|     DEPARTURE CITY       ::  "<<left<<setw(100)<<this->DEPT_CON<<"|";
                            cout<<"\n\t|     ARRIVAL CITY         ::  "<<left<<setw(100)<<this->ARR_CON<<"|";
                            cout<<"\n\t|     DEPARTURE DATE       ::  "<<left<<setw(100)<<this->DEPT_DATE<<"|";
                            cout<<"\n\t|     ARRIVAL DATE         ::  "<<left<<setw(100)<<this->ARR_DATE<<"|";
                            cout<<"\n\t|     AIRLINE NAME         ::  "<<left<<setw(100)<<this->AIR_LINE<<"|";
                            cout<<ANSI_COLOR_BOLD_RED<<"\n\t|     TOTAL PRICE    [$]   ::  "<<left<<setw(100)<<waste.ticket_price<<"|";
                            cout<<ANSI_COLOR_BOLD_GREEN<<"\n\t|     LAYOVER TIME  [HRS]  ::  "<<left<<setw(100)<<0<< "|";
                            cout<<ANSI_COLOR_BOLD_YELLOW<<"\n\t|__________________________________________________________________________________________________________________________________|"<<ANSI_COLOR_RESET<<endl;
                            break;
                        }
                    }
                    case 'b':
                    {
                        char choice;
                        cout<<"\n  < SELECT THE TYPE OF DISPLAY > ";
                        cout<<"\n   [1]. TERMINAL BASED VIEW... ";
                        cout<<"\n   [2]. SFML [GUI] VIEW... ";
                        cin>>choice;
                        if(choice == '1'){
                            BOOK_FLAG=1;
                            this->LET_ME_HANDLE(ng);
                        }
                        else{
                            BOOK_FLAG=1;
                            this->LET_ME_HANDLE_COPY(ng);
                        }
                        break;
                    }
                    case 'r':
                    {
                        cout<<ANSI_COLOR_BOLD_YELLOW<<"\n --------------------------------------------------------";
                        cout<<"\n |  < THANK YOU FOR USING OUR FLIGHT BOOKING SERVICE. > |";
                        cout<<"\n --------------------------------------------------------"<<endl<<endl<<ANSI_COLOR_RESET;
                        return;
                    }
                    default:
                    {
                        cout<<"\n\t INVALID CHOICE. TRY AGAIN.\n";
                        break;
                    }
                }
            }
        }
                               

        //** A KIND OF LOCAL MAIN FOR PASSENGER FUNCTIONALITIES. */
        void PASSENGER_MENUE(){

            NAV_GRAPH ng;
            ng.READ_FILE("data.txt");
            this->INPUT();

            char choice;

            while(1){

                cout<<endl<<endl;
                cout<<ANSI_COLOR_BOLD_RED<<"\t\t  ____________________________________________________________"<<endl;
                cout<<"\t\t ||                 { PASSENGER  MENU }                      || \n";
                cout<<"\t\t ||__________________________________________________________||"<<ANSI_COLOR_RESET<<endl;
                cout<<ANSI_COLOR_BOLD_GREEN<<"\t\t ||     [A]   BOOK A FLIGHT. {MAIN FUN TO BOOK REST R- }     || \n";
                cout<<"\t\t ||     [B]   SEARCH FOR FLIGHT WITH LEAST TRAVEL TIME.      || \n";
                cout<<"\t\t ||     [C]   SEARCH FOR FLIGHT WITH LEAST COST.             || \n";
                cout<<"\t\t ||     [D]   LIST DOWN ALL DIRECT PATHS. [NON-STOP]         || \n";
                cout<<"\t\t ||     [F]   LIST DOWN ALL INDIRECT PATHS. [CUSTOM ROUTES]  || \n";
                cout<<"\t\t ||     [G]   SEE AIRLINE SERVICES.                          || \n";
                cout<<"\t\t ||     [H]   GET THE LAYOVER TIMES ON DIFFERENT ROUTES.     || \n";
                cout<<"\t\t ||     [I]   SEE THE LIST OF HOTEL CHARGES.                 || \n";
                cout<<"\t\t ||     [J]   CHANGE THE [FLIGHT] SOURCE AND DESTINATION.    || \n";
                cout<<"\t\t ||     [K]   ADVANCE VISUALIZATION OF SHORTEST PATHS.       || \n";
                cout<<"\t\t ||     [O]   ADDITIONAL FUNCTION. [EXTRA'S]                 || \n";
                cout<<"\t\t ||     [E]   EXIT.                                          || \n";
                cout<<"\t\t ||                  ENTER YOUR CHOICE :                     || \n";
                cout<<"\t\t ||__________________________________________________________||"<<endl;
                cout<<"\t\t ||__________________________________________________________||"<<ANSI_COLOR_RESET<<endl;
                cin>>choice;

                char edit = tolower(choice);

                switch(edit){
                    case 'a':
                    {
                        this->BOOK_A_FLIGHT(ng);
                        break;
                    }
                    case 'b':
                    {
                        char opt;
                        cout<<"\n  < SELECT THE TYPE OF DISPLAY > ";
                        cout<<"\n   [1]. TERMINAL BASED VIEW... [BOTH WILL BE DISPLAYED]";
                        cout<<"\n   [2]. SFML   [GUI]   VIEW... [BOTH WILL BE DISPLAYED]";
                        cin>>opt;
                        if(opt == '1' || opt =='2'){
                            string mango = ng.SHORTEST_ROUTE(this->DEPT_CON , this->ARR_CON , 0);
                            if(mango != ""){
                                this->LET_ME_HANDLE_COPY(ng , mango);
                            }
                            break;
                        }
                        else{
                            break;
                        }
                    }
                    case 'c':
                    {
                        char opt;
                        cout<<"\n  < SELECT THE TYPE OF DISPLAY > ";
                        cout<<"\n   [1]. TERMINAL BASED VIEW... ";
                        cout<<"\n   [2]. SFML [GUI] VIEW... ";
                        cin>>opt;
                        if(opt == '1'){
                            ng.GET_MIN_PRICE(this->DEPT_CON , this->ARR_CON , 0);
                            break;
                        }
                        else{
                            ng.GET_MIN_PRICE(this->DEPT_CON , this->ARR_CON , 1);
                            break;
                        }
                    }
                    case 'd':
                    {
                        char opt;
                        cout<<"\n  < SELECT THE TYPE OF DISPLAY > ";
                        cout<<"\n   [1]. TERMINAL BASED VIEW... ";
                        cout<<"\n   [2]. SFML [GUI] VIEW... ";
                        cin>>opt;
                        if(opt == '1'){
                            FLIGHT_DATA waste = ng.LIST_DIRECT_FLIGHTS(this->DEPT_CON , this->ARR_CON , 0 , 0);
                        }
                        else{
                            FLIGHT_DATA waste = ng.LIST_DIRECT_FLIGHTS(this->DEPT_CON , this->ARR_CON , 0 , 1);
                        }
                        break;
                    }
                    case 'f':
                    {
                        char opt;
                        cout<<"\n  < SELECT THE TYPE OF DISPLAY > ";
                        cout<<"\n   [1]. TERMINAL BASED VIEW... ";
                        cout<<"\n   [2]. SFML [GUI] VIEW... ";
                        cin>>opt;
                        if(opt == '1'){
                            BOOK_FLAG=0;
                            this->LET_ME_HANDLE(ng);
                            break;
                        }
                        else{
                            BOOK_FLAG=0;
                            this->LET_ME_HANDLE_COPY(ng);
                            break;
                        }
                    }
                    case 'g':
                    {
                        string airline;
                        cout<<"\n  < ENTER AIRLINE NAME > ::  ";
                        cin>>airline;
                        ng.print_graph(airline);
                        break;
                    }
                    case 'h':
                    {
                        this->LET_ME_HANDLE(ng);
                        break;
                    }
                    case 'i':
                    {
                        HOTEL_CHARGE_LIST H;
                        H.READ_HOSTEL_CHARGE();
                        H.PRINT_DATA();
                        break;
                    }
                    case 'j':
                    {
                        cout<<"\n  < RESET THE NEW ORIGIN > ::  ";
                        cin>>this->DEPT_CON;
                        cout<<"\n  < RESET THE NEW DESTINATION > ::  ";
                        cin>>this->ARR_CON;
                        break;
                    }
                    case 'k':
                    {
                        this->LIST_ALL_PATHS_GUI(ng);
                        break;
                    }
                    case 'o':
                    {
                        AIK_AXHI_BAT_PROC();
                        break;
                    }
                    case 'e':
                    {
                        cout<<ANSI_COLOR_BOLD_YELLOW<<"\n --------------------------------------------------------";
                        cout<<"\n |  < THANK YOU FOR USING OUR FLIGHT BOOKING SERVICE. > |";
                        cout<<"\n --------------------------------------------------------"<<endl<<endl<<ANSI_COLOR_RESET;
                        return;
                    }
                    default:
                    {
                        cout<<ANSI_COLOR_BOLD_RED<<"\n ---------------------------------";
                        cout<<"\n  < INVALID CHOICE. TRY AGAIN >  |";
                        cout<<"\n ---------------------------------"<<endl<<endl<<ANSI_COLOR_RESET;
                        break;
                    }
                }
            }

        }

};


//** MAIN FUNCTION */
int main(){

    sf::RenderWindow window(sf::VideoMode(1280, 720), "ZAR NAVIGATION SYSTEM");
    INTRO_WALI_VIDEO("madni.mp4" , "audio.ogg", window);
    
    LOADING_LINE();
    
    // CALL THE INTRO GUY.
    COVER_TAGS();

    char choice;

    while(1){
        cout<<endl<<endl;
        cout<<ANSI_COLOR_BOLD_RED<<"\t\t  ____________________________________________________________"<<endl;
        cout<<"\t\t ||                  { FLIGHT BOOKING SERVICE }              || \n";
        cout<<"\t\t ||__________________________________________________________||"<<ANSI_COLOR_RESET<<endl;
        cout<<ANSI_COLOR_BOLD_GREEN<<"\t\t ||     [A]   PASSENGER FUNCTIONALITIES.                     || \n";
        cout<<"\t\t ||     [B]   AIRLINE ADMINISTRATION.                        || \n";
        cout<<"\t\t ||     [E]   EXIT.                                          || \n";
        cout<<"\t\t ||                  ENTER YOUR CHOICE :                     || \n";
        cout<<"\t\t ||__________________________________________________________||"<<endl;
        cout<<"\t\t ||__________________________________________________________||"<<endl;
        BUTTONS();
        cin>>choice;

        LOADING_LINE();

        choice = tolower(choice);
        
        switch(choice){
            case 'a':
            {
                PASSENGER_TAGS();
                PASSENGER P;
                P.PASSENGER_MENUE();
                break;
            }
            case 'b':
            {
                ADMIN A;
                A.ADMIN_MENUE();
                break;
            }
            case 'e':
            {
                cout<<ANSI_COLOR_BOLD_YELLOW<<"\n --------------------------------------------------------";
                cout<<"\n |  < THANK YOU FOR USING OUR FLIGHT BOOKING SERVICE. > |";
                cout<<"\n --------------------------------------------------------"<<endl<<endl<<ANSI_COLOR_RESET;
                return 0;
            }
            default:
            {
                cout<<ANSI_COLOR_BOLD_RED<<"\n ---------------------------------";
                cout<<"\n  < INVALID CHOICE. TRY AGAIN >  |";
                cout<<"\n ---------------------------------"<<endl<<ANSI_COLOR_RESET;
                break;
            }
        }
    }


return 0;
}