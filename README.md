# 🌌 SkyNav AI - Flight Path Visualizer 🚀

SkyNav AI is an advanced flight navigation tracker that visualizes and optimizes flight routes between multiple destinations. With powerful algorithms, custom-built data structures, and dynamic graphics, SkyNav AI delivers an interactive and personalized travel planning experience. 

---

## 🛠️ **Technologies Used**
- **Graphics Library**: [SFML](https://www.sfml-dev.org/) or [GLUT](https://www.opengl.org/resources/libraries/glut/) , [OpenCV](https://opencv.org/)
- **Programming Language**: C++
- **Custom Data Structures**: Linked Lists, Queues, Stacks, Trees, Graphs
- **Algorithms**: Dijkstra’s Algorithm, A*, and Bidirectional Search

---

## 📌 **Core Features**

### 1️⃣ **Flight Data Representation**
- **Description**: Flight data is parsed into a graph where cities are nodes and flights are edges. Each edge contains detailed flight information (e.g., airline, duration, dates).
- **Graphics**: 
  - Cities (nodes) and routes (edges) are visualized with tooltips for detailed flight information.
  - Edge styles represent flight duration.
- **Example**: View flights from *New York (JFK)* to *Los Angeles (LAX)*, including both direct and connecting options.

---

### 2️⃣ **Flight Booking**
- **Description**: Users can search and book flights with detailed options for layovers and direct flights.
- **Graphics**: Highlights direct and connecting routes on the graph.
- **Example**: Book flights from *Boston* to *Paris* via a layover in *London*.

---

### 3️⃣ **Shortest and Cheapest Route Finder**
- **Description**: 
  - Use Dijkstra's or A* to find optimal routes based on cost or duration.
  - Efficient processing via priority queues (heap implementation).
- **Graphics**:
  - Real-time animation highlights optimal paths.
  - Glowing effects indicate the final selected route.
- **Example**: Discover economical paths from *San Francisco* to *Tokyo*, with possible layovers in *Seattle* or *Honolulu*.

---

### 4️⃣ **Custom Flight Paths and Preferences**
- **Description**: Users can filter results based on airline preferences or specific layover cities.
- **Graphics**: 
  - Highlight preferred cities with unique icons.
  - Recalculate and display updated paths dynamically.
- **Example**: Filter routes to only show *Emirates* flights with layovers in *Dubai*.

---

### 5️⃣ **Layover Management**
- **Description**: Efficiently manage layover times using a queue structure.
- **Graphics**: Dashed lines indicate layovers, with dynamic updates for flight and layover durations.
- **Example**: Plan a flight from *Miami* to *London* with a 14-hour layover in *New York*.

---

### 6️⃣ **Advanced Route Generation**
- **Description**: Represent complex multi-leg journeys dynamically using a linked list structure.
- **Graphics**: 
  - Visualize each leg of the journey with arrows.
  - Interactively add or remove segments of the trip.
- **Example**: Plan a route from *San Francisco* to *Tokyo* with multiple layovers.

---

### 7️⃣ **Graphical Query and Subgraph Generation**
- **Description**: Generate subgraphs based on user preferences (e.g., specific airlines or routes).
- **Graphics**: 
  - Highlight active routes.
  - Reduce opacity for excluded cities.
- **Example**: Focus on routes served by *Qatar Airways*.

---

## 🧠 **Advanced Algorithm Visualizations**
- **Real-time Feedback**:
  - Dijkstra’s and A* algorithms dynamically show node evaluations.
  - Visual animations highlight decision-making and pathfinding steps.
- **Pathfinding Enhancements**:
  - Bidirectional search for improved long-distance route efficiency.

---

## 📂 **Project Files**
- `Flights.txt`: Contains flight data for cities, airlines, and schedules.
- `HotelCharges.txt`: Details hotel costs for layovers.
- `1.cpp`: Main file to be eexecuted.
- `layover_queue.h`: This header file contains the whole main functionality.
- `EXTRA_FUNCTION.h`: Another header file for assistance.
- `Some audio and video files`: Along with font files.

---

## 📜 Future Enhancements
- Implementing time-based key expiration for additional security.
- Encrypt `creds.txt` for even more secure storage like using a tool called crypter.
- Adding more detailed logging and error-handling mechanisms.

---

## 🛠️ Setup and Usage

1. Clone this repository:
   ```bash
   git clone https://github.com/YourUsername/SkyNavAI.git
   cd SkyNavAI

2. Command for execution:
   ```bash
   g++ -o test 1.cpp -I/usr/include/opencv4 `pkg-config --libs opencv4` -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
   ./test

3. Additional Notes:
   Please compile the server first so it will be up for listening otherwise the client alone would not be able to make a connection solely.

---

## ⚠️ Errors and Omissions

If you encounter any errors, bugs, or have suggestions for improvements, feel free to reach out to me.

You can contact me via email at: [ahad06074@gmail.com](mailto:ahad06074@gmail.com)

Errors and omissions are accepted!

## 🤖 Credits

Built with ❤️ by a passionate team of developers. 
The one and only [Abdul Ahad (Null and Void)], [Touqeer Ahmed (Mr. Snoop)] and [Mr. Faizan (The creative guy.)]
Graphics powered by **SFML** and **GLUT**.  
Algorithms inspired by cutting-edge pathfinding techniques.

Feel free to **fork**, **contribute**, or **share your thoughts**! 🌟
