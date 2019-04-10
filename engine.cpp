/*
g++ -std=c++14 -lsfml-graphics -lsfml-window -lsfml-system -Os "%f"
1. fmt 1.txt > input.txt
2. inputfile is: input.txt
3. in class Textfile the readfile(); execute
4. copy the output string to message= section

to do:

*/
#include <iostream>
#include <string>
#include <math.h>
#include <random>
#include <fstream> // textfile
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>

#define PI 3.14159265

class Textfile {
public:
  std::string message="hi world\nthis is a test.";
  int pagesize=1400;
  
  void readfile() {
    std::string result;
    std::string line;
    std::ifstream myfile ("input.txt");
    if (myfile.is_open()) {
      while ( getline (myfile,line) ) {
        result+= line+"\\n";
      }
      myfile.close();  
    }
    std::cout << result << std::endl;
  }
  void showtext() {
    std::cout << message << std::endl;
  }
  auto getpart(int start, int end) {
    std::string result;
    if (end>message.size()) end=message.size();
    // search for beginning
    int first=0;
    for (int i=start; i<start+500;i++) {
      if (message[i]=='\n') {
        first=i+1;
        break;
      }
    }
    for (int i=first; i<end+500;i++) {
      if (i>message.size()) break;
      if (i>end and message[i]=='\n') // end reached?
        break;
      else result+= message[i]; 
    }
    return result;
  }
  auto gettext(int page) {
    int start, end;
    start=page*pagesize;
    end=start+pagesize;
    return getpart(start,end);
  }
  auto getpagemax() {
    int result=message.size()/pagesize;
    return result;
  }
  Textfile() {
    //readfile();
    //showtext();
    
  }
};

class GUI {
public:
  Textfile mytext;
  sf::RenderWindow window;
  sf::Font font;
  sf::Text sfmltext;
  int framestep=0;
  int fps=10;
  int page=0;
  int pagemax=mytext.getpagemax();
  int xmax=800;
  int ymax=650;
  sf::Event event; // SFML event
  void inputhandling() {
    while(window.pollEvent(event)) {
      if (event.type==sf::Event::Closed)
        window.close();
      if (event.type==sf::Event::KeyPressed) { // key pressed down
        if (event.key.code == sf::Keyboard::Up) {
          if (page>0) page -=1;
          else page=pagemax;
        }
        else if (event.key.code == sf::Keyboard::Down) {
          if (page<pagemax) page +=1;
          else page=0;
        }
      }
    }
  }
  void render() {
    framestep++;
    window.clear(sf::Color::White); // clear
    // text
    std::string text=mytext.gettext(page);
    painttext(text,{10,10});
    // status
    std::string status=std::to_string(page)+"/"+std::to_string(pagemax);
    float y=ymax-30;
    painttext(status,{10,y});
    float x=300+200*sin(4*framestep*PI/180);
    y=ymax-25;
    drawcircle({x,y},3);
    // update
    sf::sleep(sf::milliseconds(1000/fps)); // wait
    window.display();
  }
  void painttext(std::string s, sf::Vector2f pos) { 
    sfmltext.setString(s);
    sfmltext.setPosition(pos.x,pos.y);
    window.draw(sfmltext);
  }  
  void drawcircle(sf::Vector2f pos, int radius) {
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(pos);
    window.draw(circle);
  }  
  GUI() {
    font.loadFromFile("/usr/share/fonts/dejavu/DejaVuSansMono.ttf");
    sfmltext.setFont(font);
    sfmltext.setCharacterSize(16);
    sfmltext.setFillColor(sf::Color::Black);
    window.create(sf::VideoMode(xmax, ymax), "Trollheaven Diskmag #03, 2019-04-08");
    while(window.isOpen()) {
      inputhandling();
      render();
    }
  }
};  

int main() { 
  GUI mygui;
  return 0;
}

