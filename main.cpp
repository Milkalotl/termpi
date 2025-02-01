#include <iostream>
#include <algorithm>
#include <chrono>
#include <string>
#include <sstream>
#include <vector>
#include <termios.h>
#include <unistd.h>
#include <fstream>

#define MAX_COL 60
#define MAX_ROW 5
#define LINE_DELAY 25000

std::vector<std::string> s_split_func(std::string h_text, char del){
      std::vector<std::string> t_vector;
      std::string token;
      size_t pos = 0;
      while ((pos = h_text.find(del)) != std::string::npos) {
        token = h_text.substr(0, pos);
        t_vector.push_back(token);
        h_text.erase(0, pos + 1);
    }
    t_vector.push_back(h_text);

    return t_vector;
}

void v_s_clean_func(std::vector<std::string> * vectorptr){
  for(int e = 0; e < vectorptr->size(); e++){
    vectorptr->at(e).erase(remove_if(vectorptr->at(e).begin(), vectorptr->at(e).end(), ::iscntrl), vectorptr->at(e).end());
  }
  return;
}

class textbox{
  private:
    bool pref_pause;
    bool pref_clear;
    int pref_row;
    int pref_col;
    char spaces;
  public:
    std::vector <std::string> fulltext;
    std::vector<std::string> portrait;
    int linenum;
    int boxnum;

    textbox(std::string h_text, std::vector<std::string> h_portrait){ 
      fulltext = s_split_func(h_text,' ');
      linenum = fulltext.size();
      portrait = h_portrait;
      pref_pause = false;
      pref_clear = true;
      pref_row = 0;
      pref_col = MAX_COL;
      spaces = ' ';
    }
    
    textbox(std::string h_text, std::vector<std::string> h_portrait, bool pp, bool pc, int prow, int pcol, char spc){ 
      fulltext = s_split_func(h_text,' ');d
      linenum = fulltext.size();
      portrait = h_portrait;
      pref_pause = pp;
      pref_clear = pc;
      pref_row = prow;
      pref_col = pcol;
      spaces = del;
    }
    
    void play(){
      printportrait();
      printtext(' ', false);
      clear(true);
    }

    void printportrait(){
      std::string t_string;
      std::stringstream buffer;
      std::cout << "*";
      for(int e = 0; e < MAX_COL; e++) std::cout << "-";
      std::cout << "*" << std::endl;
      for(int e = 1; e < portrait.size(); e++)
        std::cout << "| " << portrait.at(e) << std::endl;
      std::cout << "*";
      for(int e = 0; e < MAX_COL; e++) std::cout << "-";
      std::cout << "*" << std::endl;


      return;
    }

    void printtext(char del, bool ask){
      
      std::cout << "*";
      for (int e = 0; e < (MAX_COL + 2); e++)
        std::cout << "-";
      std::cout << "*";
      
      std::cout << std::endl;
      int curcount = 0;
      int w_length;
      std::cout << "| ";
      int oldcur; 
      
      for(int e = 0; e < linenum; e++){

        w_length = fulltext.at(e).length() + 1;  
        oldcur = curcount; 
        curcount += w_length;
        if(curcount >= MAX_COL){ 
          for (int f = 0; f < (MAX_COL - oldcur); f++) std::cout << del;
          std::cout << " |"; 
          if(ask == true) std::cin.get();
          std::cout << std::endl << "| "; 
          curcount = w_length;   
        }
        
        usleep(LINE_DELAY);
        std::cout << fulltext.at(e) << " ";
      }
      for (int f = 0; f < (MAX_COL - curcount); f++) std::cout << del;
      std::cout <<" |" << std::endl;
      std::cout << "*";
      for (int e = 0; e < (MAX_COL + 2); e++)
        std::cout << "-";
      std::cout << "*" << std::endl;
    }
    void clear(bool wait){
      if(wait == true) std::cin.get();
      system("clear -x");
    }
 // private:
};

class event_class{
  private:
    bool pref_pause;
    bool pref_clear;
    int pref_row;
    int pref_col;
    int event_length;

  public:
    std::vector<textbox> textboxes;
      
      event_class(void){
        event_length = 0;
        pref_pause = false;
        pref_clear = true;
        pref_row = 0;
        pref_col = MAX_COL;
      }
      
      event_class(bool pp, bool pc, int prow, int pcol){
        event_length = 0;
        pref_pause = pp;
        pref_clear = pc;
        pref_row = prow;
        pref_col = pcol;
      }

    void add_textbox(std::string h_text, std::vector<std::string> h_portrait){
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
  std::cout << std::endl;
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

  if(argc == 1){ std::cout << "please put a text dummy" << std::endl; return -1;} 
  std::string holdstd::string(argv[1]);
  for(int e = 2; e < argc; e++){ 
    std::string temp_std::string(argv[e]);
    holdstd::string += " " + temp_std::string;
  } 
  std::vector<std::string> v_script;
  std::vector<std::string> v_portrait;
  std::ifstream f_script("script.txt");
  std::ifstream f_portrait("images/marjane.txt");
  std::ostd::stringstream buffer;
  std::string s_buffer;
  
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
