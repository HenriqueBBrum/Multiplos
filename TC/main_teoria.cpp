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
};

struct TransitionFormula5Tuple{
  std::pair<uint, char> rhs;
  std::tuple<uint, char, char> lhs;
};

struct TransitionFormula4Tuple{
  std::pair<uint, std::string> rhs;
  std::pair<std::string, uint> lhs;
};


class TuringMachine{

private:
  Tape input, history, output;


  std::vector<std::pair<TransitionFormula4Tuple, TransitionFormula4Tuple>> computeTxns;
  std::vector<std::pair<TransitionFormula4Tuple, TransitionFormula4Tuple>> copyTxns;
  std::vector<std::pair<TransitionFormula4Tuple, TransitionFormula4Tuple>> retraceTxns;
  std::vector<TransitionFormula5Tuple> txns5tuple;


  uint pres_state = 0;
  std::vector<uint> computeStates;
  std::vector<uint> copyStates;
  std::vector<uint> retaceStates;


  std::string input_alphabet;
  std::string tape_alphabet;

public:

  bool run(std::string file_name){
    bool r = read_file(file_name);
    if(!r) return r;

    quintupleToquadruple();


    compute();


    return r;
  }

private:

  int changeHeadPos(char movement){
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


  void compute(){
    while(input.head < (int)input.tape.length() && pres_state!=computeStates.back()){
      char c = input.tape[input.head];

      std::cout<<"Tape = "<<input.tape<<"  ";
      std::cout<<" Present state = "<<pres_state<<"   ";
      std::cout<<" tape char  = "<<c<<"\n";

      for(auto i: computeTxns){
          if(pres_state == i.first.rhs.first && c == i.first.rhs.second[0]){
            // Input tape
            input.tape[input.head] = i.first.lhs.first[0];
            input.head+= changeHeadPos(i.second.lhs.first[0]);

            // History tape_alphabet


            history.head+= changeHeadPos(i.first.lhs.first[1]);

            // Output tape


            output.head+= changeHeadPos(i.first.lhs.first[1]);

            // Updates

            pres_state = i.second.lhs.second;

            std::vector<uint>::iterator itr = std::find(computeStates.begin(), computeStates.end(), pres_state);
            if (itr == computeStates.cend()) {
                std::cout << "Pres_state is not a valid state\n";
                return;
            }

            std::cout<<"--------------- Found valid transaction -------------------------"<<"\n";
            break;
          }
      }
    }
  }

  void quintupleToquadruple(){
    TransitionFormula4Tuple tuple_1, tuple_2;
    for(auto i: txns5tuple){
      //std::cout<<"5Tuple = "<<i.rhs.first<<", "<<i.rhs.second<<" => "<<std::get<0>(i.lhs)<<", "<<std::get<1>(i.lhs)<<", "<<std::get<2>(i.lhs)<<"\n";
      //First tuple
      std::string aux;

      tuple_1.rhs.first = i.rhs.first;
      tuple_1.rhs.second = (aux = i.rhs.second)+"/B";

      tuple_1.lhs.first = (aux = std::get<1>(i.lhs))+"RB";
      tuple_1.lhs.second = i.rhs.first;

      //std::cout<<"First 4Tuple = "<<tuple_1.rhs.first<<", "<<tuple_1.rhs.second<<" => "<<tuple_1.lhs.first<<", "<<tuple_1.lhs.second<<"\n";

      //Second tuple

      tuple_2.rhs.first = tuple_1.lhs.second;
      tuple_2.rhs.second = "/B/";

      tuple_2.lhs.first = std::get<2>(i.lhs)+std::to_string(tuple_1.lhs.second)+"N";
      tuple_2.lhs.second = std::get<0>(i.lhs);

      //std::cout<<"Second 4Tuple = "<<tuple_2.rhs.first<<", "<<tuple_2.rhs.second<<" => "<<tuple_2.lhs.first<<", "<<tuple_2.lhs.second<<"\n\n";

      computeTxns.push_back(std::make_pair(tuple_1, tuple_2));
    }

  }

  bool read_file(std::string file_name){
    std::vector<uint> units;

    std::ifstream file(file_name, std::ifstream::in);
    if(file.fail()){
      std::cout<<"Unable to read file with name: "<<file_name<<"\n";
      return false;
    }

    std::string str;

    std::getline(file, str);
    std::stringstream sstr_1(str);
    while(std::getline(sstr_1, str, ' '))
      units.push_back(std::stoi(str));

    std::getline(file, str);
    std::stringstream sstr_2(str);
    while(std::getline(sstr_2, str, ' '))
      computeStates.push_back(std::stoi(str));

    pres_state = computeStates.at(0);

    std::getline(file, input_alphabet);
    input_alphabet.erase(std::remove(input_alphabet.begin(), input_alphabet.end(), ' '), input_alphabet.end());
    //input_alphabet+=" ";

    std::getline(file, tape_alphabet);
    tape_alphabet.erase(std::remove(tape_alphabet.begin(), tape_alphabet.end(), ' '), tape_alphabet.end());

    std::string trash_chars(" (),=");
    for(uint i = 0;i<units[3];i++){
      std::getline(file, str);
      for(auto c: trash_chars)
          str.erase(std::remove(str.begin(), str.end(), c), str.end());

      txns5tuple.push_back(TransitionFormula5Tuple());
      txns5tuple[i].rhs = std::make_pair<uint, char>((uint)(str[0]-'0'), (char)str[1]);
      txns5tuple[i].lhs = std::make_tuple<uint, char, char>((uint)(str[2]-'0'), (char)str[3], (char)str[4]);
    }

    std::getline(file, input.tape);

    return true;
  }

};



int main(int argc, char** args){
  TuringMachine tm;
  auto res = tm.run(args[1]);

}
