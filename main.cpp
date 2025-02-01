#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <vector>
#include <termios.h>
#include <unistd.h>
#include <fstream>

using std::string;
using std::vector;

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;



#define MAX_ROW 60
#define MAX_COL 5
#define LINE_DELAY 25000

vector<string> s_split_func(string h_text, char del){
      vector<string> t_vector;
      string token;
      size_t pos = 0;
      while ((pos = h_text.find(del)) != string::npos) {
        token = h_text.substr(0, pos);
        t_vector.push_back(token);
        h_text.erase(0, pos + 1);
    }
    t_vector.push_back(h_text);

    return t_vector;
}

void v_s_clean_func(vector<string> * vectorptr){
  for(int e = 0; e < vectorptr->size(); e++){
    vectorptr->at(e).erase(remove_if(vectorptr->at(e).begin(), vectorptr->at(e).end(), ::iscntrl), vectorptr->at(e).end());
  }
  return;
}

class textbox{
  public:
    vector <string> fulltext;
    vector<string> portrait;
    int linenum;
    int boxnum;

    textbox(string h_text, vector<string> h_portrait){ 
      fulltext = s_split_func(h_text,' ');
      linenum = fulltext.size();
      portrait = h_portrait;
    }
    
    void play(){
      printportrait();
      printtext(' ', false);
      clear(true);
    }

    void printportrait(){
      string t_string;
      std::stringstream buffer;
      cout << "*";
      for(int e = 0; e < MAX_ROW; e++) cout << "-";
      cout << "*" << endl;
      for(int e = 1; e < portrait.size(); e++)
        cout << "| " << portrait.at(e) << endl;
      cout << "*";
      for(int e = 0; e < MAX_ROW; e++) cout << "-";
      cout << "*" << endl;


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

class event_class{
  public:
    vector<textbox> textboxes;
    int event_length;
      
      event_class(void){
        event_length = 0;
      }

    void add_textbox(string h_text, vector<string> h_portrait){
      textbox h_textbox(h_text, h_portrait);
      textboxes.push_back(h_textbox);
      event_length += 1;
      return;
    }
    void play_textbox(int index){
      textboxes.at(index).play();
      return;
    }
    void play_between(int index_a, int index_b){
      for (int e = index_a; e <= index_b; e++)
        play_textbox(e);
      return;
    }

    void play_all(){
      for(int e = 0; e < event_length; e++)
        play_textbox(e); 
      return;
    }
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


/*
//temporary as this is a library
int old_main(int argc, char ** argv){
  
//linux only stuff
  LINUX_SETUP('n');
  system("clear -x");
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = linux_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;

  sigaction(SIGINT, &sigIntHandler, NULL);
// end of linux only;

  if(argc == 1){ cout << "please put a text dummy" << endl; return -1;} 
  string holdstring(argv[1]);
  for(int e = 2; e < argc; e++){ 
    string temp_string(argv[e]);
    holdstring += " " + temp_string;
  } 
  vector<string> v_script;
  vector<string> v_portrait;
  std::ifstream f_script("script.txt");
  std::ifstream f_portrait("images/marjane.txt");
  std::ostringstream buffer;
  string s_buffer;
  
  buffer << f_script.rdbuf();
  s_buffer = buffer.str();
  v_script = s_split_func(s_buffer, '#'); 
 
  while(std::getline( f_portrait, s_buffer))
    v_portrait.push_back(s_buffer);
  
  v_s_clean_func(&v_script);  

  for(int e = 1; e < v_script.size(); e++){
    textbox c_textbox(v_script.at(e), v_portrait);
    c_textbox.printportrait(0);
    c_textbox.printtext(' ', false); c_textbox.clear(true);
  }

  LINUX_SETUP('f');
  return 0;

}*/
