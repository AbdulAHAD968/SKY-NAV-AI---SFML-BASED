#ifndef EXTRA_FUN_h
#define EXTRA_FUN_h


#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<thread>
#include<chrono>


#include <SFML/Audio.hpp>
#include <opencv2/opencv.hpp>
#include <SFML/Window.hpp>
#include<SFML/Graphics.hpp>  
#include<SFML/System.hpp> 

//#include<windows.h>
using namespace std;


//* ANSI COLOR SEQUENCES. *//
#define ANSI_COLOR_RESET        "\x1b[0m "
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_BLUE         "\033[34m"
#define ANSI_COLOR_ORANGE       "\033[38;5;208m"
#define ANSI_COLOR_PINK         "\033[38;5;205m"
#define ANSI_COLOR_PURPLE       "\033[38;5;165m"
#define ANSI_COLOR_DARK_GREEN   "\033[38;5;22m"
#define CLEAR_SCREEN            "\x1B[2J\x1B[H"
#define ANSI_COLOR_BOLD_RED   "\033[1;31m"
#define ANSI_COLOR_BOLD_GREEN   "\033[1;32m"
#define ANSI_COLOR_BOLD_YELLOW "\033[1;33m"


// *[ CLEAR-SCREEN FUNCTION ]* //
void CLEARSCREEN(){
    cout<<CLEAR_SCREEN;  		// USING THE DEFINED FUNCTIONALITY.
}


//*ADMIN_DISPLAY_UTILITY*//
void ADMIN_PLAYS(){
    
    cout<<endl<<endl;
    cout<<ANSI_COLOR_BOLD_GREEN<<"\t  #########################################################################"<<endl;
    cout<<ANSI_COLOR_BOLD_RED<<"\t  //        __      ________  ___      ___  __   _____  ___              //"<<endl; 
    cout<<"\t  //       /  \\    |        \\|   \\    /   ||  \\ (\\    \\|   \\             //"<<endl; 
    cout<<"\t  //      /    \\   (.  ___  :)\\   \\  //   |||  ||.\\\\   \\    |            //"<<endl; 
    cout<<"\t  //     /' /\\  \\  |: \\   ) ||/\\\\  \\/.    ||:  ||: \\.   \\\\  |            //"<<endl; 
    cout<<"\t  //    //  __'  \\ (| (___\\ ||: \\.        ||.  ||.  \\    \\. |            //"<<endl; 
    cout<<"\t  //   /   /  \\\\  \\|:       :|.  \\    /:  |/\\  ||    \\    \\ |            //"<<endl; 
    cout<<"\t  //  (___/    \\___(________/|___|\\__/|___(__\\_|_\\___|\\____\\)            //"<<ANSI_COLOR_RESET<<endl; 
    cout<<ANSI_COLOR_BOLD_GREEN<<"\t  #########################################################################"<<endl<<ANSI_COLOR_RESET<<endl;

    cout<<"\n PRESS ANY KEY TO CONTINUE...";
    cin.get();

return;
}


//*UTILITY OF PASSENGER FUNCTIONALITIES*//
void PASSENGER_TAGS(){

    cout<<ANSI_COLOR_BOLD_RED<<endl<<endl;
    cout<<"\t\t  ________________________________________________________________ "<<endl;
    cout<<ANSI_COLOR_BOLD_GREEN<<"\t\t ||    _____ _____ _____ _____ _____ _____ _____ _____ _____     ||"<<endl;
    cout<<"\t\t ||   |  _  |  _  |   __|   __|   __|   | |   __|   __| __  |    ||"<<endl;
    cout<<"\t\t ||   |   __|     |__   |__   |   __| | | |  |  |   __|    -|    ||"<<endl;
    cout<<"\t\t ||   |__|  |__|__|_____|_____|_____|_|___|_____|_____|__|__|    ||"<<endl;
    cout<<ANSI_COLOR_BOLD_RED<<"\t\t ||______________________________________________________________||"<<ANSI_COLOR_RESET<<endl<<endl;

    cout<<"PRESS ANY KEY TO CONTINUE...";
    cin.get();                                        
}



//** COVER_TAGS */
void COVER_TAGS(){


    CLEARSCREEN();
    cout<<endl<<endl;
    cout<<ANSI_COLOR_BOLD_RED<<"\t\t  ______________________________________________________________________"<<endl;
    cout<<"\t\t ||____________________________________________________________________||"<<ANSI_COLOR_RESET<<endl;
    cout<<ANSI_COLOR_BOLD_GREEN<<"\t\t ||        _____ _   ____   __  _   _   ___  _   _    ___  _____       || "<<endl;
    cout<<"\t\t ||       /  ___| | / /\\ \\ / / | \\ | | / _ \\| | | |  / _ \\|_   _|      || "<<endl;
    cout<<"\t\t ||       \\ `--.| |/ /  \\ V /  |  \\| |/ /_\\ \\ | | | / /_\\ \\ | |        || "<<endl;
    cout<<"\t\t ||        `--. \\\\   \\   \\ /   | . ` ||  _  | | | | |  _  | | |        || "<<endl;
    cout<<"\t\t ||       /\\\\__/ /|\\  \\  | |   | |\\  || | | \\ \\_/ / | | | |_| |_       || "<<endl;
    cout<<"\t\t ||       \\____/\\_| \\_/  \\_/   \\_| \\_/\\_| |_/\\___/  \\_| |_/\\___/       || "<<endl;
    cout<<"\t\t ||                                                                    || "<<endl;
    cout<<ANSI_COLOR_BOLD_RED<<"\t\t ||____________________________________________________________________||"<<endl;
    cout<<"\t\t |______________________________________________________________________|"<<ANSI_COLOR_RESET<<endl<<endl;

    cout<<"\n PRESS ANY KEY TO CONTINUE...";
    cin.get();

return ;
}


// *[ LOADING LINE FUNCTION ]* //
void LOADING_LINE(){

    CLEARSCREEN();
	
	int star = 20;
	int space = 65;
	int per = 25;
	
	CLEARSCREEN();			// CALLING THE CLEAR SCREEN FUNCTION.
	
    const char* color = ANSI_COLOR_RESET;
	cout<<ANSI_COLOR_BOLD_RED<<"\n\n\t\t\t\t\t _____________________________________" ;
	cout<<"\n\t\t\t\t\t|                                     |";
	cout<<"\n\t\t\t\t\t|  >>>    LOADING PLEASE WAIT     <<< |";
	cout<<"\n\t\t\t\t\t|_____________________________________|"<<ANSI_COLOR_RESET<<endl;
	
	cout<<"\t\t "<<setfill('-')<<setw(89)<<"-"<<setfill(' ')<<endl;
	
	for(int i=0 ; i<=3 ; i++ )
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		if(i==0){
			color = ANSI_COLOR_BOLD_RED;
		}
		else if(i==1){
			color = ANSI_COLOR_PURPLE;
		}
		else if(i==2){
			color = ANSI_COLOR_BOLD_YELLOW;
		}
		else if(i==3){
			color = ANSI_COLOR_BOLD_GREEN;
		}
		
		cout<<"\t\t | "<<color<<setfill('*')<<setw(star)<<" "<<setfill(' ')<<setw(space)<<" "<<" | "<<per<<" %"<<ANSI_COLOR_RESET<<endl;
		
		star += 20 ;
		space -= 20;
		per += 25 ;
	}
	
	cout<<"\t\t "<<setfill('-')<<setw(89)<<"-"<<setfill(' ');
	
	cout<<ANSI_COLOR_BOLD_GREEN<<"\n\t\t\t\t\t\t ___________________________" ;
	cout<<"\n\t\t\t\t\t\t|                           |";
	cout<<"\n\t\t\t\t\t\t|  >>>    COMPLETED    <<<  |";
	cout<<"\n\t\t\t\t\t\t|___________________________|\n"<<ANSI_COLOR_RESET<<endl;
	
    cout<<"\n PRESS ANY KEY TO CONTINUE...";
    cin.get();
return;
}


// *[ BUTTONS-MENU ]* //
void BUTTONS(){
    cout<<"\n\t\t ______________________________________";
    cout<<"\n\t\t|                                      |";
    cout<<ANSI_COLOR_BOLD_GREEN<<"\n\t\t| > PRESS THE BUTTON {ONE AT A TIME} < |"<<ANSI_COLOR_RESET;
    cout<<ANSI_COLOR_BOLD_YELLOW<<"\n\t\t|      __________________________      |";
    cout<<"\n\t\t|     |                          |     |";
    cout<<"\n\t\t|     |    ' A '   ' F '   ' E ' |     |";
    cout<<"\n\t\t|     |                          |     |";
    cout<<"\n\t\t|     |    ' G '   ' B '   ' D ' |     |";
    cout<<"\n\t\t|     |                          |     |";
    cout<<"\n\t\t|     |    ' H '   ' I '   ' C ' |     |";
    cout<<"\n\t\t|     |__________________________|     |";
    cout<<"\n\t\t|                                      |";
    cout<<"\n\t\t|______________________________________|\n\n"<<ANSI_COLOR_RESET;
		
return;
}



//*FUNCTION TO ENCRYPT OR DECRYPT USING [XOR_CIPHER].*//
string XOR_CIPHER(const string& text, const string& key){

    string result = text;
    
    for(int i=0 ; i<text.size() ; i++){
        result[i] = text[i] ^ key[i % key.size()];          //MASKING WITH THE ^ {size of key}.
    }

return result;
}


// INTRO VIDEO.
void INTRO_WALI_VIDEO(const std::string& videoPath, const std::string& audioPath, sf::RenderWindow& window){

    // OpenCV: USING OPENCV TO LOAD THE VIDEO FILE.
    cv::VideoCapture video(videoPath);
    if(!video.isOpened()){
        cerr<<"\n ERROR: OPEN FILE FOR VIDEO. "<<videoPath<<endl;
        return;
    }

    // SFML: LOAD THE AUDIO FILE
    sf::Music audio;
    if(!audio.openFromFile(audioPath)){
        cerr<<"\n ERROR: OPEN FILE FOR VIDEO. "<<audioPath<<endl;
        return;
    }

    // GET THE VIDEO PROPERTIES. [GPT KI MARHOON-E-MINNAT]
    int videoWidth = static_cast<int>(video.get(cv::CAP_PROP_FRAME_WIDTH));
    int videoHeight = static_cast<int>(video.get(cv::CAP_PROP_FRAME_HEIGHT));
    float frameRate = static_cast<float>(video.get(cv::CAP_PROP_FPS));


    sf::Texture videoTexture;
    sf::Sprite videoSprite;

    // OpenCV Mat to hold video frames
    cv::Mat frame;

    // Scale video to fit window
    sf::Vector2u windowSize = window.getSize();
    float scaleX = static_cast<float>(windowSize.x) / videoWidth;
    float scaleY = static_cast<float>(windowSize.y) / videoHeight;
    float scale = std::min(scaleX, scaleY);

    videoSprite.setScale(scale, scale);
    videoSprite.setPosition(
        (windowSize.x - videoWidth * scale) / 2.0f,
        (windowSize.y - videoHeight * scale) / 2.0f
    );

    sf::Clock clock;
    audio.play();

    while(video.read(frame)){
        if(!window.isOpen()){
            break;   
        }

        // Get current times
        double currentVideoTime = video.get(cv::CAP_PROP_POS_MSEC) / 1000.0;
        double currentAudioTime = audio.getPlayingOffset().asSeconds();
        double timeDiff = currentVideoTime - currentAudioTime;

        if(timeDiff < -0.1){
            continue;       // IF VIDEO IS BEHIND SKIP THIS FRAME.
        }

        // ADJUST PLAYBACK TIMING.
        if(timeDiff > 0){
            sf::sleep(sf::seconds(timeDiff));
        }

        // Convert BGR to RGBA and render
        cv::cvtColor(frame, frame, cv::COLOR_BGR2RGBA);
        videoTexture.create(videoWidth, videoHeight);
        videoTexture.update(frame.data, videoWidth, videoHeight, 0, 0);
        videoSprite.setTexture(videoTexture);

        window.clear();
        window.draw(videoSprite);
        window.display();

        // Process window events
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
                return;
            }
        }
    }
    audio.stop();
}


// BONUS FUNCTION TO PRINT [AIK AXHI BAT.]
void AIK_AXHI_BAT_PROC(){
   
    sf::RenderWindow window(sf::VideoMode(900, 550), " ZAROLOGY INFOMANIA.");

    sf::Texture image_back;
    if(!image_back.loadFromFile("4.png")) {
        cerr<<"Error loading envelope image.\n";
        return;
    }

    sf::Sprite TAGGED_BG(image_back);

    // Scale the image to fit the entire window
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = image_back.getSize();
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    TAGGED_BG.setScale(scaleX, scaleY);

    // Create a button (rectangle)
    sf::RectangleShape button(sf::Vector2f(250, 50)); // Adjusted size to fit the text
    button.setFillColor(sf::Color::Magenta);
    button.setPosition(20, windowSize.y - button.getSize().y - 20); // Position at bottom-left corner

    // Create button text
    sf::Font font;
    if(!font.loadFromFile("font.ttf")){
        cerr<<" ERROR LOADING FONTS FILE.\n";
        return;
    }

    sf::Text BUTTON("AIK AXHI BATT!", font, 30);
    BUTTON.setFillColor(sf::Color::Green);
    BUTTON.setPosition(button.getPosition().x + 25, button.getPosition().y + 5);

    sf::Text msg("", font, 30);
    msg.setFillColor(sf::Color::White);
    msg.setPosition(70, 60);

    sf::RectangleShape msg_box(sf::Vector2f(100, 20));
    msg_box.setFillColor(sf::Color(0, 0, 0, 150));
    msg_box.setPosition(msg.getPosition().x - 10, msg.getPosition().y - 10);

    sf::Music sound_msg;
    if(!sound_msg.openFromFile("axhibat.ogg")) {
        cerr<<"\n ERROR LOADING BACKGROUND MUSIC.\n";
        return;
    }
    sound_msg.setLoop(true); // Loop the music
    sound_msg.play();

    // MAIN LOOP
    while(window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){

            if(event.type == sf::Event::Closed){
               window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed){

                if(event.mouseButton.button == sf::Mouse::Left){

                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    if(button.getGlobalBounds().contains(mousePosition.x, mousePosition.y)){

                        msg.setString("Don't seek happines! Create it.");
                        msg_box.setSize(sf::Vector2f(msg.getLocalBounds().width + 20, 60));
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(TAGGED_BG);
        window.draw(button);
        window.draw(BUTTON);

        if(!msg.getString().isEmpty()){
            window.draw(msg_box);
            window.draw(msg);
        }

        window.display();
    }
}







#endif