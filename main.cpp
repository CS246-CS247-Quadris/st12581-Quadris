#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include "PRNG.h"
#include "board.h"

using namespace std;

int main (int argc, const char * argv[]){

    int times=-1,numOftimes;
    string command;
    int at=0;//to find the index of command
    bool check=true;
    int level;
    bool text=false;//if its only the text version
    
    char block;
    char block2;
    
    const char* fileName="sequence.txt";
    PRNG randNum;
    
    Board * board = new Board;
    
    for(int i=1;i<argc;i++){//check command-line argument
        if(!strcmp(argv[i],"-text")){//text version only
            board->setText();
            text=true;
        }
        else if(!strcmp(argv[i],"-scriptfile")){//change filename
            fileName=argv[i+1];
            i++;
        }
        else if(!strcmp(argv[i],"-seed")){//random number
            randNum.seed(atoi(argv[i+1]));
            i++;
        }
    }
    if(!text){//set user interface
        board->setWindow();
        board->draw();
    }
    
    while(check){
        ifstream file(fileName); 
        level=0;
        times=-1;
        at=0;
        numOftimes=0;
        block=' ',block2=' ';
        board->reset();
        
        for(int i=1;i<argc;i++){
            if(!strcmp(argv[i],"-startlevel")){//change level
                level=atoi(argv[i+1]);
                if(level<0||level>3){
                    level=0;
                }
                if(level!=0){
                    for(int j=0;j<level;j++){
                        board->increLevel();
                    }
                }
                i++;
            }
        }
        
        
        
        if(level==0){//level0, read from file
            file>>block;
        
            if(file.eof()){
                delete board;
                return 0;
            }
        
            file>>block2;
        
            if(file.eof()){
                block2='N';
            }
        }
        else{//other levels, random numbers
            block=generateNextBlock(level,randNum);
            block2=generateNextBlock(level,randNum);
        }
        
        
        board->setNext(block2);
        
        board->createBlock(block);
        board->print();
        
        cin>>command;//read command
        if(cin.eof()) break;
        
        for (int i=0; i<(int)command.length(); i++) {
            if(command[i]>='0' && command[i]<='9'){
                numOftimes=numOftimes*10+command[i]-'0';//get the times of executing command
            }
            else{
                at=i;
                break;
            }
        }
        if(numOftimes!=0){
            times=numOftimes;
        }
        
        
        while(command[at]!='r'||command[at+1]!='e'|| times!=-1){
            
            if(command[at]=='r'&&command[at+1]=='i') {//right
                while((times>0)||times==-1){
                    board->move('R');
                    times--;
                }
            }
            else if(command[at]=='l'){
                if(command[at+2]=='f'){//left
                    while((times!=0&&times>0)||times==-1){
                        board->move('L');
                        times--;
                    }
                }
                else if(command[at+2]=='v'){
                    if(command[at+5]=='u'){//levelup
                        while(times>0||times==-1){
                            if(level<3){
                                board->increLevel();
                                level++;
                            }
                            times--;
                        }
                    }
                    else if(command[at+5]=='d'){//leveldown
                        while(times>0||times==-1){
                            if(level>0){
                                board->decreLevel();
                                level--;
                            }
                            times--;
                        }
                    }
                }
            }
            else if(command[at]=='d'){
                if(command[at+1]=='o'){//down
                    while((times>0)||times==-1){
                        board->move('D');
                        times--;
                    }
                }
                else if(command[at+1]=='r'){//drop
                    bool check=false;
                    while((times>0)||times==-1){
                        board->move('P');
                        times--;
                        
                        if(block2=='N'){
                            board->print();
                            return 0;
                        }
                        block=block2;
                        if(level==0){//if drop, generate new block
                            file>>block2;
                            if(file.eof()){
                                block2='N';
                            }
                        }
                        else{
                           block2=generateNextBlock(level,randNum);
                        }
                                                    
                        board->setNext(block2);
                        if(board->createBlock(block)!=0){
                            check=true;
                            break;
                        }
                    }
                    if(check){
                        break;
                    }
                }
                
            }
            else if(command[at+1]=='l'){//clockwise  
                while((times>0)||times==-1){
                    board->move('T');
                    times--;
                }
            }
            else if(command[at+1]=='o'){//counterclockwise
                while((times>0)||times==-1){
                    board->move('C');
                    times--;
                }
            }
            
            board->print(); //print the board each time          
            
            at=0;
            times=-1;
            numOftimes=0;
            
            cin>>command;
            if(cin.eof()){
                check=false;break;
            }
            
            for (int i=0; i<(int)command.length(); i++) {
                if(command[i]>='0' && command[i]<='9'){
                    numOftimes=numOftimes*10+command[i]-'0';
                }
                else{
                    at=i;
                    break;
                }
            }
            if(numOftimes!=0){
                times=numOftimes;
            }
            
            
        }
    }
    
    delete board;
}





