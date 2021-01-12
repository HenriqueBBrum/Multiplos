#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <tuple>
#include <sstream>
//  #include <string>
#include <algorithm>

typedef unsigned int uint;

// Obs: R =  RIGHT, L = LEFT, N = NULL


struct Tape{
  std::string tape;
  int head = 0;

  friend std::ostream& operator<<(std::ostream& out, const Tape& tp){
      out<<"Content: "<<tp.tape <<", head pos: "<< tp.head;
      return out;
  }

};



struct TransitionFormula5Tuple{
  std::pair<uint, char> lhs;
  std::tuple<uint, char, char> rhs;
};

struct TransitionFormula4Tuple{
  std::pair<uint, std::string> lhs;
  std::pair<std::string, uint> rhs;
};


class TuringMachine{

private:
  Tape working, history, output;


  std::vector<std::pair<TransitionFormula4Tuple, TransitionFormula4Tuple>> computeTxns;
  std::vector<std::pair<TransitionFormula4Tuple, TransitionFormula4Tuple>> copyTxns;
  std::vector<std::pair<TransitionFormula4Tuple, TransitionFormula4Tuple>> retraceTxns;
  std::vector<TransitionFormula5Tuple> txns5tuple;


  uint pres_state = 0;
  std::vector<uint> computeStates;
  std::vector<uint> copyStates;


  std::string input_alphabet;
  std::string tape_alphabet;

public:

  bool run(std::string file_name){
    bool r = read_file(file_name);
    if(!r) return r;

    std::cout<<"--------------------- Compute -----------------------------\n";
    quintuple_to_quadruple();
    compute();

    std::cout<<"\n\n--------------------- Copy -----------------------------\n";
    create_copy_quarduples();
    copy_to_output();

    std::cout<<"\n\n--------------------- Retrace -----------------------------\n";
    create_retrace_quarduples();
    retrace();
    return r;
  }

private:

  // Multipurpose funcs
  int change_head_pos(char movement){
    int v = -2;

    switch (movement) {
      case 'R': v = 1;
        break;
      case 'L': v = -1;
        break;
      case 'N': v = 0;
    }

    return v;
  }


  // Compute part funcs

  void quintuple_to_quadruple(){
    TransitionFormula4Tuple tuple_1, tuple_2;
    for(auto i: txns5tuple){
      //std::cout<<"5Tuple = "<<i.lhs.first<<", "<<i.lhs.second<<" => "<<std::get<0>(i.rhs)<<", "<<std::get<1>(i.rhs)<<", "<<std::get<2>(i.rhs)<<"\n";
      std::string aux;

      tuple_1.lhs.first = i.lhs.first;
      tuple_1.lhs.second = (aux = i.lhs.second)+"/B";
      tuple_1.rhs.first = (aux = std::get<1>(i.rhs))+"RB";
      tuple_1.rhs.second = i.lhs.first;

      //std::cout<<"First 4Tuple = "<<tuple_1.lhs.first<<", "<<tuple_1.lhs.second<<" => "<<tuple_1.rhs.first<<", "<<tuple_1.rhs.second<<"\n";

      tuple_2.lhs.first = tuple_1.rhs.second;
      tuple_2.lhs.second = "/B/";
      tuple_2.rhs.first = std::get<2>(i.rhs)+std::to_string(std::get<0>(i.rhs))+"N";
      tuple_2.rhs.second = std::get<0>(i.rhs);

      //std::cout<<"Second 4Tuple = "<<tuple_2.lhs.first<<", "<<tuple_2.lhs.second<<" => "<<tuple_2.rhs.first<<", "<<tuple_2.rhs.second<<"\n\n";
      computeTxns.push_back(std::make_pair(tuple_1, tuple_2));
    }
  }

  void compute(){
    pres_state = computeStates.at(0);
    while(pres_state!=computeStates.back()){
      char c = working.tape[working.head];
      for(auto i: computeTxns){
          if(pres_state == i.first.lhs.first && c == i.first.lhs.second[0]){

            // Working tape
            working.tape[working.head] = i.first.rhs.first[0];
            working.head+= change_head_pos(i.second.rhs.first[0]);

            // History tape
            history.tape.insert(history.head , 1,  i.second.rhs.first[1]);
            history.head+= change_head_pos(i.first.rhs.first[1]);

            // Output tape
            output.tape[output.head] = i.first.rhs.first[2];
            output.head+= change_head_pos(i.second.rhs.first[2]);

            // Updates
            pres_state = i.second.rhs.second;
            std::vector<uint>::iterator itr = std::find(computeStates.begin(), computeStates.end(), pres_state);
            if (itr == computeStates.cend()) { std::cout << "Pres_state is not a valid state\n";return;  }

            break;
          }
      }
    }
    working.head = 0;
    std::cout<<"\nWorking tape => "<<working<<"\n"<<"History tape => "<<history<<"\n"<<"Output tape => "<<output<<"\n\n";
  }


  // Copy part funcs

  // x = qualquer simbolo no fita 'working' menos 'B'
  // n = qualquer numero salvo na fita 'history'
  void create_copy_quarduples(){
      TransitionFormula4Tuple tuple_1, tuple_2;
      copyStates = {1,2,3};

      tuple_1.lhs.first = 1;
      tuple_1.lhs.second = "xnB";
      tuple_1.rhs.first = "xnx";
      tuple_1.rhs.second = 1;

      tuple_2.lhs.first = 1;
      tuple_2.lhs.second = "///";
      tuple_2.rhs.first = "RNR";
      tuple_2.rhs.second = 1;

      copyTxns.push_back(std::make_pair(tuple_1, tuple_2));

      tuple_1.lhs.first = 1;
      tuple_1.lhs.second = "BnB";
      tuple_1.rhs.first = "BnB";
      tuple_1.rhs.second = 2;

      tuple_2.lhs.first = 2;
      tuple_2.lhs.second = "///";
      tuple_2.rhs.first = "NNN";
      tuple_2.rhs.second = 3;

      copyTxns.push_back(std::make_pair(tuple_1, tuple_2));
  }

  void run_copy_txns(std::pair<TransitionFormula4Tuple, TransitionFormula4Tuple> txns, char c){
    working.tape[working.head] = c;
    working.head+= change_head_pos(txns.second.rhs.first[0]);

    // History tape
    history.tape[history.head] = history.tape[history.head];
    history.head+= change_head_pos(txns.second.rhs.first[1]);

    // Output tape
    output.tape[output.head] = c;
    output.head+= change_head_pos(txns.second.rhs.first[2]);

    // Updates state
    pres_state = txns.second.rhs.second;

    std::vector<uint>::iterator itr = std::find(copyStates.begin(), copyStates.end(), pres_state);
    if (itr == computeStates.cend()) { std::cout << "Pres_state is not a valid state\n";return;  }

  }

  void copy_to_output(){
    pres_state = copyStates.at(0);

    while(pres_state!=copyStates.back()){
      char c = working.tape[working.head];

      for(auto i: copyTxns){
        if(pres_state == i.first.lhs.first && (c == i.first.lhs.second[0] &&  c == 'B') ){
          run_copy_txns(i, c);
          break;
        }else if(pres_state == i.first.lhs.first && c!='B' && (std::find(tape_alphabet.begin(), tape_alphabet.end(), c) != tape_alphabet.end())){
          run_copy_txns(i, c);
          break;
        }
      }
    }
    std::cout<<"\nWorking tape => "<<working<<"\n"<<"History tape => "<<history<<"\n"<<"Output tape => "<<output<<"\n";
  }


  // Retrace funcs

  void create_retrace_quarduples(){
    TransitionFormula4Tuple tuple_1, tuple_2;
    for(auto it = computeTxns.rbegin(); it!=computeTxns.rend();++it){
        std::string aux;
        tuple_1.lhs.first = it->second.rhs.second;
        tuple_1.lhs.second = "/"+(aux = it->second.rhs.first[1])+"/";

        aux  = "N";
        if(it->second.rhs.first[0] == 'R') aux = "L";
        else if(it->second.rhs.first[0] == 'L') aux = "R";

        tuple_1.rhs.first = aux+"BN";
        tuple_1.rhs.second = it->second.lhs.first;

        std::cout<<"First 4Tuple = "<<tuple_1.lhs.first<<", "<<tuple_1.lhs.second<<" => "<<tuple_1.rhs.first<<", "<<tuple_1.rhs.second<<"\n";

        tuple_2.lhs.first = tuple_1.rhs.second;
        tuple_2.lhs.second = (aux = it->first.rhs.first[0])+"/B";

        tuple_2.rhs.first = (aux = it->first.lhs.second[0])+"LB";
        tuple_2.rhs.second = tuple_1.rhs.second;

        std::cout<<"Second 4Tuple = "<<tuple_2.lhs.first<<", "<<tuple_2.lhs.second<<" => "<<tuple_2.rhs.first<<", "<<tuple_2.rhs.second<<"\n\n";

        retraceTxns.push_back(std::make_pair(tuple_1, tuple_2));
    }

  }

  void retrace(){
    pres_state = computeStates.back();
    while(working.head>=0){
      char c = working.tape[working.head];
      std::cout<<"Pres_state = "<<pres_state<<" c = "<<c<<"\n";
      for(auto i: retraceTxns){
          if(pres_state == i.first.lhs.first && c == i.second.lhs.second[0]){

            // Working tape
            std::cout<<"i.second.rhs.first[0]  = "<<i.second.rhs.first[0]<<" i.first.rhs.first[0] = "<<i.first.rhs.first[0]<<"\n";
            working.tape[working.head] = i.second.rhs.first[0];
            working.head+= change_head_pos(i.first.rhs.first[0]);

            // History tape
            history.tape[history.head] = 'B';
            history.head+= change_head_pos(i.second.rhs.first[1]);

            // Output tape
            output.tape[output.head] = output.tape[output.head];
            output.head+= change_head_pos(i.first.rhs.first[2]);

            // Updates
            pres_state = i.second.rhs.second;
            std::vector<uint>::iterator itr = std::find(computeStates.begin(), computeStates.end(), pres_state);
            if (itr == computeStates.cend()) { std::cout << "Pres_state is not a valid state\n";return;  }

            break;
          }
      }
      std::cout<<"\nWorking tape => "<<working<<"\n"<<"History tape => "<<history<<"\n"<<"Output tape => "<<output<<"\n\n";
    }
    //std::cout<<"\nWorking tape => "<<working<<"\n"<<"History tape => "<<history<<"\n"<<"Output tape => "<<output<<"\n\n";
  }


  // File reading functions

  void handle_before_transitions(std::ifstream& file, std::vector<uint>& units){
    std::string str;

    std::getline(file, str);
    std::stringstream sstr_1(str);
    while(std::getline(sstr_1, str, ' '))
      units.push_back(std::stoi(str));

    std::getline(file, str);
    std::stringstream sstr_2(str);
    while(std::getline(sstr_2, str, ' '))
      computeStates.push_back(std::stoi(str));

    std::getline(file, input_alphabet);
    input_alphabet.erase(std::remove(input_alphabet.begin(), input_alphabet.end(), ' '), input_alphabet.end());

    std::getline(file, tape_alphabet);
    tape_alphabet.erase(std::remove(tape_alphabet.begin(), tape_alphabet.end(), ' '), tape_alphabet.end());

  }

  void handle_transitions(std::ifstream& file, std::vector<uint> units){
    std::string trash_chars(" (),="), str;
    for(uint i = 0;i<units[3];i++){
      std::getline(file, str);
      for(auto c: trash_chars)
          str.erase(std::remove(str.begin(), str.end(), c), str.end());

      txns5tuple.push_back(TransitionFormula5Tuple());
      txns5tuple[i].lhs = std::make_pair<uint, char>((uint)(str[0]-'0'), (char)str[1]);
      txns5tuple[i].rhs = std::make_tuple<uint, char, char>((uint)(str[2]-'0'), (char)str[3], (char)str[4]);
    }
  }


  bool read_file(std::string file_name){
    std::vector<uint> units;
    std::ifstream file(file_name, std::ifstream::in);
    if(file.fail()){
      std::cout<<"Unable to read file with name: "<<file_name<<"\n";
      return false;
    }

    handle_before_transitions(file, units);
    handle_transitions(file, units);

    std::getline(file, working.tape);
    working.tape+="B";
    output.tape.assign(working.tape.length(), 'B');

    return true;
  }

};



int main(int argc, char** args){
  TuringMachine tm;
  tm.run(args[1]);

}
