#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Instrument{
public:
    Instrument(){}
    virtual void makeSound() const = 0;
    virtual void play() const = 0;
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
    void play() const{
        cout << "Boom";
    }
};
class Cello : public String{
public:
     Cello(unsigned stringnum) : String(stringnum){};
     void play() const{
        cout << "Squawk";
    }
};
class Cymbal : public Percussion{
public:
    Cymbal(): Percussion(){};
    void play() const{
        cout << "Crash";
    }
};
class Trombone: public Brass{
public:
    Trombone(unsigned mpsize) : Brass(mpsize){};
    void play() const{
        cout << "Blat";
    }
};
class Trumpet : public Brass{
public:
    Trumpet(unsigned mpsize) : Brass(mpsize){};
    void play() const{
        cout << "Toot";
    }
};
class Violin: public String{
public:
    Violin(unsigned stringnum) : String(stringnum){};
    void play() const{
        cout << "Screech";
    }
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

    Instrument* getInstr() const{
        return instr;
    }

    void playInstr() const{
        if (instr){
            instr->play();
        }
    }
private:
    Instrument* instr;
};

class Orch{
public:
    Orch(){}
    void addPlayer(Musician& player){
        if (playerCount < 25){
            Musician* musPtr = &player;
            players.push_back(musPtr);
        }else{
            cout << "Sorry buddy, the Orchestra is full :(" << endl;
        }
    }

    void play(){
        for (size_t i = 0; i < players.size(); ++i){
            if(players[i]->getInstr()){
                players[i]->playInstr();
            }
        }
    }
private:
    vector<Musician*> players;
    int playerCount = 0;
};

// PART TWO
int main() {
    // The initialization phase

    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    cout << "Bob joins the orchestra!" << endl;
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "Orchestra performs ... but with no instruments?" << endl;
    orch.play();
    cout << endl;

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);
    cout << "Sue shows up to party! But with an instrument!" << endl;

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);
    cout << "Hey look! It's Mary and her instrument!" << endl;

    //Ralph returns his instrument to the MIL2.
    cout << endl << "Ralph returns his instrument and the MILL tests if it's working!" << endl;
    mill.receiveInstr(*ralph.giveBackInstr());
    cout << endl;

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);
    cout << "WHOA! It's Jody and her instrument!" << endl;

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "Orchestra performs\n";
    orch.play();
    cout << endl;

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);
    cout << "Ralph joins empty-handed!" << endl;

    //The orchestra performs.
    cout << "Orchestra performs\n";
    orch.play();
    cout << endl;

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());
    cout << "It's about time! Bob gets an instrument!" << endl;

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());
    cout << "It's about time! Ralph gets an instrument!" << endl;

    //The orchestra performs.
    cout << "Orchestra performs\n";
    orch.play();
    cout << endl;

    //Morgan joins the orchestra.
    cout << "Surprise! It's Morgan!" << endl;
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "Orchestra performs\n";
    orch.play();
    cout << endl;

} // main

