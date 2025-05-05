


// visualize_route_with_cities.cpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <string>

using namespace std;

// City structure containing name and coordinates
struct City {
    string name;
    float x, y;
};

// Function to draw the map with city markers and route
void drawMap(sf::RenderWindow &window, const vector<City> &cities, const vector<int> &route) {
    window.clear(sf::Color::White);

    // Create a circle for each city and label it
    for (const auto& city : cities) {
        sf::CircleShape cityMarker(10.f);  // radius of 10
        cityMarker.setFillColor(sf::Color::Red);
        cityMarker.setPosition({ city.x, city.y });
        window.draw(cityMarker);

        sf::Font font;
        if (!font.openFromFile("arial.ttf")) {  // Make sure you have a font file in the same directory
            std::cerr << "Error loading font!" << std::endl;
            return;
        }

        sf::Text cityName(font, city.name, 20);
        cityName.setPosition({ city.x + 12.f, city.y - 10.f });
        window.draw(cityName);
    }

    // Draw the route between cities
    for (size_t i = 0; i + 1 < route.size(); ++i) {
        int a = route[i];
        int b = route[i + 1];

        sf::Vertex line[] = {
            { { cities[a].x + 10.f, cities[a].y + 10.f }, sf::Color::Blue },
            { { cities[b].x + 10.f, cities[b].y + 10.f }, sf::Color::Blue }
        };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    window.display();
}

int main() {
    // Define cities and their coordinates (for demonstration)
    vector<City> cities = {
        {"New York", 50, 50},       // New York
        {"Los Angeles", 600, 100},  // California
        {"Chicago", 300, 200},      // Illinois
        {"Houston", 400, 400},      // Texas
        {"Miami", 700, 400},        // Florida
        {"Atlanta", 350, 250},      // Georgia
        {"Denver", 300, 100},       // Colorado
        {"Boston", 100, 100},       // Massachusetts
        {"Phoenix", 500, 250},      // Arizona
        {"Philadelphia", 150, 50},  // Pennsylvania
        {"Seattle", 550, 50},       // Washington
        {"Dallas", 450, 300},       // Texas
        {"Portland", 500, 50},      // Oregon
        {"San Diego", 450, 500},    // California
        {"San Francisco", 550, 150},// California
        {"Charlotte", 200, 300},    // North Carolina
        {"Detroit", 250, 300},      // Michigan
        {"Cleveland", 200, 400},    // Ohio
        {"Indianapolis", 250, 200}, // Indiana
        {"Jacksonville", 600, 350}, // Florida
        {"Louisville", 350, 350},   // Kentucky
        {"Nashville", 300, 350},    // Tennessee
        {"Salt Lake City", 550, 250}, // Utah
        {"Minneapolis", 250, 100},  // Minnesota
        {"New Orleans", 350, 400},  // Louisiana
        {"Kansas City", 350, 150},  // Missouri
        {"Orlando", 450, 300},      // Florida
        {"Tampa", 500, 300},        // Florida
        {"Salt Lake City", 500, 350}, // Utah
        {"Dallas", 450, 300},       // Texas
        {"Birmingham", 250, 450},   // Alabama
        {"Louisville", 200, 250},   // Kentucky
        {"Raleigh", 300, 250},      // North Carolina
        {"Madison", 500, 100},      // Wisconsin
        {"Columbus", 250, 350},     // Ohio
        {"Montpelier", 150, 200},   // Vermont
        {"Albany", 100, 200},       // New York
        {"Anchorage", 650, 400},    // Alaska
        {"Bismarck", 350, 100},     // North Dakota
        {"Cheyenne", 450, 500},     // Wyoming
        {"Charleston", 200, 300},   // West Virginia
        {"Fargo", 250, 200},        // North Dakota
        {"Helena", 300, 350},       // Montana
        {"Madison", 500, 150},      // Wisconsin
        {"Little Rock", 400, 400},  // Arkansas
        {"Topeka", 500, 250},       // Kansas
        {"Phoenix", 450, 150},      // Arizona
        {"Sacramento", 550, 100},   // California
        {"Boise", 550, 300},        // Idaho
        {"Richmond", 150, 400},     // Virginia
        {"Frankfort", 400, 200},    // Kentucky
        {"Columbia", 300, 500},     // South Carolina
        {"Lincoln", 450, 150},      // Nebraska
        {"Trenton", 150, 200},      // New Jersey
        {"Hartford", 100, 300},     // Connecticut
        {"Buffalo", 150, 450},      // New York
        {"San Jose", 550, 200},     // California
        {"Baltimore", 200, 50},     // Maryland
        {"Colorado Springs", 250, 50} // Colorado
    };

    // Define a simple route (replace this with Dijkstra's output)
    vector<int> route = {0, 2, 3, 5, 6, 8};  // Example route

    // Create a window to display the map
    sf::RenderWindow window(sf::VideoMode({800, 600}), "City Route Map");

    // Main loop to display the map and route
    // while (window.isOpen()) {
    //     // SFML 3.0 event polling returns std::optional<sf::Event>
    //     while (auto ev = window.pollEvent()) {
    //         if (ev->type == sf::Event::Closed)
    //             window.close();

    //     }

    //     drawMap(window, cities, route);
    // }

    while (window.isOpen()) {
        // SFML 3.0: pollEvent() returns std::optional<sf::Event>
        while (auto ev = window.pollEvent()) {
            // use is<T>() instead of inspecting a .type member
            if (ev->is<sf::Event::Closed>())
                window.close();
        }
    } 

    return 0;
}




// // visualize_route_with_cities.cpp

// #include <SFML/Graphics.hpp>
// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <map>
// #include <string>

// using namespace std;

// // City structure containing name and coordinates
// struct City {
//     string name;
//     float x, y;
// };

// // Function to draw the map with city markers and route
// void drawMap(sf::RenderWindow &window, const vector<City> &cities, const vector<int> &route) {
//     window.clear(sf::Color::White);

//     // Create a circle for each city and label it
//     for (const auto& city : cities) {
//         sf::CircleShape cityMarker(10);  // radius of 10
//         cityMarker.setFillColor(sf::Color::Red);
//         cityMarker.setPosition(city.x, city.y);
//         window.draw(cityMarker);

//         sf::Font font;
//         if (!font.openFromFile("arial.ttf")) {  // Make sure you have a font file in the same directory
//             std::cerr << "Error loading font!" << std::endl;
//             return;
//         }

//         sf::Text cityName(font, city.name, 20)
//         // sf::Text cityName(city.name, font, 20);
//         cityName.setPosition({ city.x + 12, city.y - 10 });
//         window.draw(cityName);
//     }

//     // Draw the route between cities
//     for (size_t i = 0; i < route.size() - 1; ++i) {
//         sf::Vertex line[] = {
//             { { cities[a].x+10, cities[a].y+10 }, sf::Color::Blue },
//             { { cities[b].x+10, cities[b].y+10 }, sf::Color::Blue }
//         };
//         window.draw(line, 2, sf::Lines);
//     }

//     window.display();
// }

// int main() {
//     // Define cities and their coordinates (for demonstration)
//     vector<City> cities = {
//         {"New York", 50, 50},       // New York
//         {"Los Angeles", 600, 100}, // California
//         {"Chicago", 300, 200},     // Illinois
//         {"Houston", 400, 400},     // Texas
//         {"Miami", 700, 400},       // Florida
//         {"Atlanta", 350, 250},     // Georgia
//         {"Denver", 300, 100},      // Colorado
//         {"Boston", 100, 100},      // Massachusetts
//         {"Phoenix", 500, 250},     // Arizona
//         {"Philadelphia", 150, 50}, // Pennsylvania
//         {"Seattle", 550, 50},      // Washington
//         {"Dallas", 450, 300},      // Texas
//         {"Portland", 500, 50},     // Oregon
//         {"San Diego", 450, 500},   // California
//         {"San Francisco", 550, 150}, // California
//         {"Charlotte", 200, 300},   // North Carolina
//         {"Detroit", 250, 300},     // Michigan
//         {"Cleveland", 200, 400},   // Ohio
//         {"Indianapolis", 250, 200}, // Indiana
//         {"Jacksonville", 600, 350}, // Florida
//         {"Louisville", 350, 350},  // Kentucky
//         {"Nashville", 300, 350},   // Tennessee
//         {"Salt Lake City", 550, 250}, // Utah
//         {"Minneapolis", 250, 100}, // Minnesota
//         {"New Orleans", 350, 400},  // Louisiana
//         {"Kansas City", 350, 150},  // Missouri
//         {"Orlando", 450, 300},    // Florida
//         {"Tampa", 500, 300},      // Florida
//         {"Salt Lake City", 500, 350}, // Utah
//         {"Dallas", 450, 300},     // Texas
//         {"Birmingham", 250, 450}, // Alabama
//         {"Louisville", 200, 250}, // Kentucky
//         {"Raleigh", 300, 250},    // North Carolina
//         {"Madison", 500, 100},    // Wisconsin
//         {"Columbus", 250, 350},   // Ohio
//         {"Montpelier", 150, 200}, // Vermont
//         {"Albany", 100, 200},     // New York
//         {"Anchorage", 650, 400},  // Alaska
//         {"Bismarck", 350, 100},   // North Dakota
//         {"Cheyenne", 450, 500},   // Wyoming
//         {"Charleston", 200, 300}, // West Virginia
//         {"Fargo", 250, 200},      // North Dakota
//         {"Helena", 300, 350},     // Montana
//         {"Madison", 500, 150},    // Wisconsin
//         {"Little Rock", 400, 400}, // Arkansas
//         {"Topeka", 500, 250},     // Kansas
//         {"Phoenix", 450, 150},    // Arizona
//         {"Sacramento", 550, 100}, // California
//         {"Boise", 550, 300},      // Idaho
//         {"Richmond", 150, 400},   // Virginia
//         {"Frankfort", 400, 200},  // Kentucky
//         {"Columbia", 300, 500},   // South Carolina
//         {"Lincoln", 450, 150},    // Nebraska
//         {"Trenton", 150, 200},    // New Jersey
//         {"Hartford", 100, 300},   // Connecticut
//         {"Buffalo", 150, 450},    // New York
//         {"San Jose", 550, 200},   // California
//         {"Baltimore", 200, 50},   // Maryland
//         {"Colorado Springs", 250, 50} // Colorado
//     };

//     // Define a simple route (replace this with Dijkstra's output)
//     vector<int> route = {0, 2, 3, 5, 6, 8};  // Example route (New York -> Chicago -> Houston -> Miami -> Atlanta -> Phoenix)

//     // Create a window to display the map
//     sf::RenderWindow window(sf::VideoMode({800, 600}), "City Route Map");

//     // Main loop to display the map and route
//     while (window.isOpen()) {
//         while (auto ev = window.pollEvent())
//             if (ev->type == sf::Event::Closed)
//                 window.close();

//         // Draw the cities and route on the map
//         drawMap(window, cities, route);
//     }

//     return 0;
// }
