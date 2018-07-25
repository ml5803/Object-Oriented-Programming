#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Instrument{
public:
    Instrument(){}
    virtual void makeSound() const = 0;
private:
};

void Instrument::makeSound() const{
    cout << "To make a sound... ";
}

class Brass : public Instrument{
public:
    Brass(unsigned mpsize) : Instrument(), mouthpieceSize(mpsize){}
    void makeSound() const{
        Instrument::makeSound();
        cout << "blow on mouthpiece of size " << mouthpieceSize << endl;
    }
private:
    unsigned mouthpieceSize;
};

class String : public Instrument{
public:
    String(unsigned stringnum) : pitch(stringnum){}
    void makeSound() const{
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
private:
    unsigned pitch;
};

class Percussion: public Instrument{
public:
    Percussion() : Instrument(){}
    void makeSound() const{
        Instrument::makeSound();
        cout << "To make a sound... hit me!" << endl;
    }
};

class Drum : public Percussion{
public:
    Drum(): Percussion(){};
};
class Cello : public String{
public:
     Cello(unsigned stringnum) : String(stringnum){};
};
class Cymbal : public Percussion{
public:
    Cymbal(): Percussion(){};
};
class Trombone: public Brass{
public:
    Trombone(unsigned mpsize) : Brass(mpsize){};
};
class Trumpet : public Brass{
public:
    Trumpet(unsigned mpsize) : Brass(mpsize){};
};
class Violin: public String{
public:
    Violin(unsigned stringnum) : String(stringnum){};
};

class MILL{
public:
    MILL():library(1){
        library[0] = nullptr;
    }
    void receiveInstr(Instrument& instr){
        instr.makeSound();
        Instrument* instPtr = &instr;
        for(size_t i = 0; i < library.size(); ++i){
            if (library[i] == nullptr){
                library[i] = instPtr;
                return;
            }
        }
        library.push_back(instPtr);
    }

    Instrument* loanOut(){
        Instrument* instPtr = nullptr;
        for(size_t i = 0; i < library.size(); ++i){
            if(library[i]){
                instPtr = library[i];
                library[i] = nullptr;
                break;
            }
        }
        return instPtr;
    }

    void dailyTestPlay() const{
        for(size_t i = 0; i < library.size(); ++i){
            if(library[i]){
                library[i]->makeSound();
            }
        }
    }
private:
    vector<Instrument*> library;
};

class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }

private:
    Instrument* instr;
};

// PART ONE
int main() {

     cout << "Define some instruments ----------------------------------------\n";
     Drum drum;
     Cello cello(673);
     Cymbal cymbal;
     Trombone tbone(4);
     Trumpet trpt(12) ;
     Violin violin(567) ;

    // // use the debugger to look at the mill
     cout << "Define the MILL ------------------------------------------------\n";
     MILL mill;

     cout << "Put the instruments into the MILL ------------------------------\n";
     mill.receiveInstr(trpt);
     mill.receiveInstr(violin);
     mill.receiveInstr(tbone);
     mill.receiveInstr(drum);
     mill.receiveInstr(cello);
     mill.receiveInstr(cymbal);

     cout << "Daily test -----------------------------------------------------\n";
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;

     cout << "Define some Musicians-------------------------------------------\n";
     Musician harpo;
     Musician groucho;

     cout << "TESTING: groucho.acceptInstr(mill.loanOut());-----------------------\n";
     groucho.testPlay();
     cout << endl;
     groucho.acceptInstr(mill.loanOut());
     cout << "GROUCHO NOW HAS AN INSTRUMENT!" <<endl;
     groucho.testPlay();
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();

     cout << endl << endl;

     groucho.testPlay();
     cout << endl;
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     cout << endl;
     groucho.testPlay();
     cout << endl;
     harpo.testPlay();
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();

     cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ----------\n";

     // fifth
     mill.receiveInstr(*groucho.giveBackInstr());
     cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
     mill.receiveInstr(*harpo.giveBackInstr());


     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;
}

