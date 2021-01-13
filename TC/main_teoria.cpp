#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <tuple>
#include <sstream>
//  #include <string>
#include <algorithm>

typedef unsigned int uint;

// Obs: R =  RIGHT, L = LEFT, S = STOP


struct Tape{
  std::vector<std::string> tape;
  int head = 0;

  friend std::ostream& operator<<(std::ostream& out, const Tape& tp){
      out<<"Content: ";
      for(auto i: tp.tape) out<<i<<", ";

      out <<" head pos: "<< tp.head;
      return out;
  }

};


struct TransitionFormula5Tuple{
  std::pair<uint, char> lhs;
  std::tuple<uint, char, char> rhs;
};

struct TransitionFormula4Tuple{
  std::pair<uint, std::vector<std::string>> lhs;
  std::pair<std::vector<std::string>, uint> rhs;
};


class ReversibleTuringMachine{

private:
  Tape working, history, output;


  std::vector<std::pair<TransitionFormula4Tuple, TransitionFormula4Tuple>> computeTxns;
  std::vector<std::pair<TransitionFormula4Tuple, TransitionFormula4Tuple>> copyTxns;
  std::vector<std::pair<TransitionFormula4Tuple, TransitionFormula4Tuple>> retraceTxns;
  std::vector<TransitionFormula5Tuple> txns5tuple;

  std::vector<uint> units;
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
  int change_head_pos(std::string movement){
    int v = 0;

    if(movement == "R") v = 1;
    else if(movement == "L") v = -1;

    return v;
  }

  template<typename T>
  void printVec(std::vector<T> vec){
    for(auto i: vec) std::cout<<i;
  }

  // Compute part funcs

  void quintuple_to_quadruple(){
    TransitionFormula4Tuple tuple_1, tuple_2;
    uint cont = 1;
    std::string aux;

    for(auto i: txns5tuple){

      tuple_1.lhs.first = i.lhs.first;
      tuple_1.lhs.second = {std::string(1, i.lhs.second), "/", "B"};
      tuple_1.rhs.first = {std::string(1,std::get<1>(i.rhs)), "R", "B"};
      tuple_1.rhs.second = i.lhs.first;

      tuple_2.lhs.first = tuple_1.rhs.second;
      tuple_2.lhs.second = {"/", "B", "/"};
      tuple_2.rhs.first = {std::string(1,std::get<2>(i.rhs)), std::to_string(cont), "S"};
      tuple_2.rhs.second = std::get<0>(i.rhs);

      computeTxns.push_back(std::make_pair(tuple_1, tuple_2));
      cont++;
    }
  }

  void compute(){
    pres_state = computeStates.at(0);
    std::string aux;
    while(pres_state!=computeStates.back()){
      std::string c = working.tape[working.head];
      for(auto i: computeTxns){
          if(pres_state == i.first.lhs.first && c ==  i.first.lhs.second[0]){

            // Working tape
            working.tape[working.head] = i.first.rhs.first[0];
            working.head+= change_head_pos(i.second.rhs.first[0]);

            // History tape
            history.head+= change_head_pos(i.first.rhs.first[1]);
            history.tape.insert(history.tape.begin()+history.head , i.second.rhs.first[1]);

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
      tuple_1.lhs.second = {"x", "n", "B"};
      tuple_1.rhs.first = {"x", "n", "x"};
      tuple_1.rhs.second = 1;

      tuple_2.lhs.first = 1;
      tuple_2.lhs.second = {"/", "/", "/"};
      tuple_2.rhs.first = {"R", "S", "R"};
      tuple_2.rhs.second = 1;

      copyTxns.push_back(std::make_pair(tuple_1, tuple_2));

      tuple_1.lhs.first = 1;
      tuple_1.lhs.second = {"B", "n", "B"};
      tuple_1.rhs.first = {"B", "n", "B"};
      tuple_1.rhs.second = 2;

      tuple_2.lhs.first = 2;
      tuple_2.lhs.second = {"/", "/", "/"};
      tuple_2.rhs.first = {"S", "S", "S"};
      tuple_2.rhs.second = 3;

      copyTxns.push_back(std::make_pair(tuple_1, tuple_2));
  }

  void run_copy_txns(std::pair<TransitionFormula4Tuple, TransitionFormula4Tuple> txns, std::string c){
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
      std::string c = working.tape[working.head];

      for(auto i: copyTxns){
        if(pres_state == i.first.lhs.first && (c == i.first.lhs.second[0] &&  c == "B") ){
          run_copy_txns(i, c);
          break;
        }else if(pres_state == i.first.lhs.first && c!="B" && (std::find(tape_alphabet.begin(), tape_alphabet.end(), c[0]) != tape_alphabet.end())){
          run_copy_txns(i, c);
          break;
        }
      }
    }
    std::cout<<"\nWorking tape => "<<working<<"\n"<<"History tape => "<<history<<"\n"<<"Output tape => "<<output<<"\n";
  }


  // Retrace funcs

  // Create inverse transitions
  void create_retrace_quarduples(){
    TransitionFormula4Tuple tuple_1, tuple_2;
    std::string aux;

    for(auto it = computeTxns.rbegin(); it!=computeTxns.rend();++it){
        tuple_1.lhs.first = it->second.rhs.second;
        tuple_1.lhs.second = {"/", it->second.rhs.first[1], "/"};

        aux  = "S";
        if(it->second.rhs.first[0] == "R") aux = "L";
        else if(it->second.rhs.first[0] == "L") aux = "R";

        tuple_1.rhs.first = {aux, "B", "S"};
        tuple_1.rhs.second = it->second.lhs.first;


        tuple_2.lhs.first = tuple_1.rhs.second;
        tuple_2.lhs.second = {it->first.rhs.first[0], "/", "B"};
        tuple_2.rhs.first = {it->first.lhs.second[0], "L", "B"};
        tuple_2.rhs.second = tuple_1.rhs.second;

        retraceTxns.push_back(std::make_pair(tuple_1, tuple_2));
    }
  }

  // While history tape has a valid transition, execute this transition
  void retrace(){

    while(history.tape[history.head] != "B" ){
      // Fetch reverse transition
      auto i = retraceTxns.at(units[3] - std::stoi(history.tape[history.head]));
      std::string c = working.tape[working.head];

      // Working tape
      working.head+= change_head_pos(i.first.rhs.first[0]);
      working.tape[working.head] = i.second.rhs.first[0];

      // History tape
      history.tape[history.head] = "B";
      history.head+= change_head_pos(i.second.rhs.first[1]);

      // Output tape
      output.head+= change_head_pos(i.first.rhs.first[2]);
      output.tape[output.head] = output.tape[output.head];

      // Updates
      pres_state = i.second.rhs.second;
      std::vector<uint>::iterator itr = std::find(computeStates.begin(), computeStates.end(), pres_state);
      if (itr == computeStates.cend()) { std::cout << "Pres_state is not a valid state\n";return;  }

    }
    std::cout<<"\nWorking tape => "<<working<<"\n"<<"History tape => "<<history<<"\n"<<"Output tape => "<<output<<"\n\n";
  }


  // File reading functions

  // Reads all lines before transitions
  void handle_before_transitions(std::ifstream& file){
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

  // Reads all transitions
  void handle_transitions(std::ifstream& file){
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
    std::ifstream file(file_name, std::ifstream::in);
    if(file.fail()){
      std::cout<<"Unable to read file with name: "<<file_name<<"\n";
      return false;
    }

    handle_before_transitions(file);
    handle_transitions(file);

    std::string aux;
    std::getline(file, aux);
    for(auto c: aux) working.tape.push_back(std::string(1,c));
    working.tape.push_back("B");
    history.tape.push_back("B");
    output.tape.assign(working.tape.size(), "B");

    return true;
  }

};



int main(int argc, char** args){
  ReversibleTuringMachine rtm;
  rtm.run(args[1]);

}
