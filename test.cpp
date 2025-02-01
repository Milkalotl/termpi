#include "main.cpp"

int main(){
  LINUX_SETUP('n');
  system("clear -x");
  struct sigaction sigIntHandler;
  sigIntHandler.sa_handler = linux_handler;
  sigemptyset(&sigIntHandler.sa_mask);
  sigIntHandler.sa_flags = 0;
  sigaction(SIGINT, &sigIntHandler, NULL);

  vector<string> v_script;
  vector<string> v_profile;
  std::ifstream f_script("script.txt");
  std::ifstream f_profile("portrait.txt");
  std::ostringstream buffer;
  string s_buffer;
  
  buffer << f_script.rdbuf();
  s_buffer = buffer.str();
  v_script = s_split_func(s_buffer, '#'); 
 
  while(std::getline( f_profile, s_buffer))
    v_profile.push_back(s_buffer);
  
  v_s_clean_func(&v_script);  

  event_class fox; 
//  for(int e = 1; e < v_script.size(); e++)
//    fox.add_textbox(v_script.at(e), v_profile);
  for(int e = 1; e < v_script.size(); e++)
    fox.add_textbox(v_script.at(e), v_profile);
/*
  fox.play_textbox(1);
  fox.play_textbox(2);
  fox.play_textbox(3);
*/
  fox.play_all();
  LINUX_SETUP('f');
  return 0;
  
}
