#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <termios.h>
#include <unistd.h>

using std::string;
using std::vector;

using std::cout;
using std::cin;
using std::endl;


#define MAX_ROW 60
#define MAX_COL 5
#define LINE_DELAY 25000

class textbox{
  public:
    vector <string> fulltext;
    int linenum;
    int boxnum;

    textbox(string h_text){ 
      size_t pos = 0;
      string token;
      linenum = 1;
      while ((pos = h_text.find(" ")) != string::npos) {
        token = h_text.substr(0, pos);
        fulltext.push_back(token);
        h_text.erase(0, pos + 1);
       // string temporary; 
       // for (const auto &piece : fulltext) temporary += " | " + piece;
       // cout <<"T: " << token << endl <<"H:" << h_text << endl << "F: " << temporary << endl;
        linenum += 1;
    }
    fulltext.push_back(h_text);

    }
    
    void printportrait(){
      //do this haha
      return;
    }



    void printtext(char del, bool ask){
      
      cout << "*";
      for (int e = 0; e < (MAX_ROW + 2); e++)
        cout << "-";
      cout << "*";
      
      cout << endl;
      int curcount = 0;
      int w_length;
      cout << "| ";
      int oldcur; 
      
      for(int e = 0; e < linenum; e++){

        w_length = fulltext.at(e).length() + 1;  
        oldcur = curcount; 
        curcount += w_length;
        if(curcount >= MAX_ROW){ 
          for (int f = 0; f < (MAX_ROW - oldcur); f++) cout << del;
          cout << " |"; 
          if(ask == true) cin.get();
          cout << endl << "| "; 
          curcount = w_length;   
        }
        
        usleep(LINE_DELAY);
        cout << fulltext.at(e) << " ";
      }
      for (int f = 0; f < (MAX_ROW - curcount); f++) cout << del;
      cout <<" |" << endl;
      cout << "*";
      for (int e = 0; e < (MAX_ROW + 2); e++)
        cout << "-";
      cout << "*" << endl;
    }
    void clear(bool wait){
      if(wait == true) cin.get();
      system("clear -x");
    }
 // private:
};

void LINUX_SETUP(char on_or_off){
  if(on_or_off == 'n') system("stty -echo");
  else system("stty echo");

  return;
}

void linux_handler(int s){
  cout << endl;
  system("stty echo");
  exit(1);
}

//temporary as this is a library
int main(int argc, char ** argv){
  
//linux only stuff
  LINUX_SETUP('n');
  system("clear -x");
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = linux_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);
// end of linux only;

/*
  if(argc == 1){ cout << "please put a text dummy" << endl; return -1;} 
  string holdstring(argv[1]);
  for(int e = 2; e < argc; e++){ 
    string temp_string(argv[e]);
    holdstring += " " + temp_string;
  }*/
  string holdstring_1(
      "The quick brown fox jumped over the lazy dog, but jumped so high he reached the heavens. There, there was a chariot being driven around and around by three golden deer. As the deer approached the fox, they asked him questions. \"why are you here, isnt this a miserable place?\". \"why come to a place such as this, where your shoulders ache and your legs quake\". The fox looked puzzled, as his shoulders and legs were as they were when he was on the floor.");
  string holdstring_2(
      "So he said as such. \"I quite don't know what aches and quakes you speak of, quick deer. My body is as firm and fit as it was when I was below the clouds\". But the deer, still going round and round, sneered at this assertion. \"But it has always been this way, fox. Here, shoulders ache and legs ache, and such is the way of life. so either you are above everyone else, or you arent alive\" Fox pondered this for a moment.");
  string holdstring_3(
      "He looked at his paws, and saw his fur not rotten. He scratched his ears, and saw they still heard. He sat down, and saw his legs still sat. \"I am rather certain I am not dead, deer. So, therefore, I must be above you all\". and so he was.");
  textbox n_textbox_1(holdstring_1);
  textbox n_textbox_2(holdstring_2);
  textbox n_textbox_3(holdstring_3);
  n_textbox_1.printtext(' ', false); n_textbox_1.clear(true);
  n_textbox_2.printtext(' ', false); n_textbox_2.clear(true);
  n_textbox_3.printtext(' ', false); n_textbox_3.clear(true);

  LINUX_SETUP('f');
  return 0;

}
