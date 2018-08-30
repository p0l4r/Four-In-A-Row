///StarGame With AI
///Developed by team- AlephNull
///CSE475-Machine Learning Project
///Team Members: Razwan Ahmed Tanvir (2015-1-60-111),
///              Shantanu Kumar Rahut (2015-1-60-114),
///              Riffat Sharmin (2015-2-60-010)

///========================================================================================================================================
///========================================================================================================================================





#include<iostream>
#include<bits/stdc++.h>
#include<windows.h>
#include <unistd.h>
#include "windows.h"



using namespace std ;

 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
char box[15][15]; ///={'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'} ;
int inputColumn;
int column[7] ;
int recentInputColumn,recent_input_row,k ;

int PL1Input();///takes input player 1
int PL2Input();///takes input of player 2
bool PL1Win(int x);///checks if player 1 wins in recent input
bool PL2Win(int x);///checks if player 2 wins in recent input

void Newgame();
void initializeSequencwArray();
void color (unsigned short v);
void print();

bool win1 =false;
bool win2=false ;
int sequenceArray[50];
int Array_For_Saving_Moves_With_Utility[500000][101]={0};
int PossibleMoves[101],MovesCounter=0;///collect moves
int XX=0 , YY; /// row and column counter for Array_For_Saving_Moves_With_Utility
int U_Counter; ///counter needed for increasing utility of a set
int RecenInputPL1 , RecenInputPL2;
int turn=0;
string username;
int NumberOfMoves = 0 ;
int MUSIC_FLAG=0;
FILE * sequenceFile ;
int FRow=500;

void StoreValue();
int Check_Utility_Of_Moves_for_player_1();
int Check_Utility_Of_Moves_for_player_2();
int BlockTheWinningMovePL1();
int BlockTheWinningMovePL2();
int PL1WinningMove();
int PL2WinningMove();
int getMoveForPL1();
int getMoveForPL2();
int EasyPlay_PL1();
int EasyPlay_PL2();
int HardPlay_PL1();
int HardPlay_PL2();






///main function starts from here
int main(){

    srand(time(NULL));
    int choice;
    initializeSequencwArray();

    cout<<endl<<"\t\t\tPlease Enter Your User Name: ";
            getline(cin,username);
            cout<<endl<<endl;
    //uncomment this part to take username

    do{

        color(7);

        StoreValue(); ///stores moves from file to Array_For_Saving_Moves_With_Utility array
        U_Counter=-1;

        cout<<"\t\t\t1.Newgame\n\n\t\t\t2.How to play\n\n\t\t\t3.Quit Game\n\n\n";

        cout<<"\t\t\tEnter Your Choice: ";
        cin>>choice;
        if(choice==1){

         cout<<endl<<endl;
            for(int j=0;j<6;j++){
                for(int l=0;l<7;l++){
                    box[j][l]='*';
                }
            } ///initializing the board again for a new game

            cout<<endl;
            turn++;
            if(MUSIC_FLAG==0){
             //PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }

            Newgame();

        }
        else if(choice==3){
                cout<<endl<<endl;
            break;
            cout<<"\t\t\tInvalid Input!"<<endl;
        }


        else if(choice==2){
                cout<<endl<<endl;
                ///stating the game rules
            cout<<"\t\t\tPLAYER INPUT:Choose your column(1 to 7)to place\n\t\t\t your sign.\n\t\t\tTry that 4 signs remain together vertically\n\t\t\t , horizontally or diagonally.\n\t\t\tVery first input of each column would be\n\t\t\t placed at the bottom and\n\t\t\tthen each input will be stacked\n\t\t\t upon existing input.\n"<<endl<<endl;
             for(int j=0;j<6;j++){
                for(int l=0;l<7;l++){
                    box[j][l]='*';
                }
            }
            box[5][0]='A';
            box[4][1]='A';box[3][2]='A';box[2][3]='A';
            print();
            cout<<"\t\t\tThis is a sample winning combination (diagonally)\n\t\t\t for player 1 !"<<endl<<endl<<endl;
        }
        else{
            cout<<endl<<endl<<"\t\t\tInvalid Input !!!"<<endl<<endl<<endl;
        }

    }while(choice!=3);
}
///main function ends here





///other functions start from here

void initialize_box(){  ///initializes box for a new game  , box means a 2-D array
    for(int i=0;i<15;i++){
        for(int j =0;j<15;j++){
            box[i][j]='*';
        }
    }
}


void initialize_Column(){ ///initializes column of the box for a new game , box means a 2-D array
    for(int i=0;i<7;i++){
        column[i] = 7 ;
    }
}


void initializeSequencwArray(){ /// initializes sequence array that will keep the moves of a current ongoing game
    for(int i=0;i<42;i++)
        sequenceArray[i]=-1;
}


void PrintGameSequenceArray (){   /// saves the sequence array in the file
    for(int i = 0 ; sequenceArray[i]!=-1 ;i++ ){
        fprintf(sequenceFile,"%d ",sequenceArray[i]);
    }

}


void PrintPossibleMovesArray(){  ///prints possible moves from the array
    cout<<endl<<"Possible Moves Array:";
    for(int i=0;i<MovesCounter;i++)
        cout<<PossibleMoves[i]<<" ";
        cout<<endl;
}


void color (unsigned short v) {   /// color function
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, v);
}




void print(){ ///prints the board(box)
        color(14);
        cout<<endl;
        cout<<"\t\t\t1   2   3   4   5   6   7"<<endl;
        cout<<"\t\t\t"<<char(25)<<"   "<<char(25)<<"   "<<char(25)<<"   "<<char(25)<<"   "<<char(25)<<"   "<<char(25)<<"   "<<char(25)<<"   "<<endl;//displaying arrow key
        cout<<"\t\t\t-------------------------------"<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        for(int i=0;i<=6;i++){
            cout<<"\t\t\t";

            for(int j=0;j<7;j++){

                if(box[i][j]=='B'){
                    SetConsoleTextAttribute(hConsole, 11);
                }
                else if(box[i][j]=='A'){
                    SetConsoleTextAttribute(hConsole, 12);
                }
                else{
                    SetConsoleTextAttribute(hConsole, 14);
                }

                cout<<box[i][j]<<"   ";
        }
            cout<<endl<<endl;
    }


}




int PL1Input(){  /// player 1 (A) input
         SetConsoleTextAttribute(hConsole, 10);
         cout<<"\t\t\tPlayer 1 choice column:";

            if(turn%2!=0){
            Sleep(1000);

                 inputColumn= getMoveForPL1() ;
                 //cout<<inputColumn<<endl;
            }
            else{
                cin>>inputColumn;
                ///uncomment the following line for random play mode
                //inputColumn = rand()%7+1;
            }

            if(inputColumn<1 || inputColumn>7 || column[inputColumn-1]<=0){ ///checking the over flow of player's input
                cout<<"\t\t\tInvalid Input. Please input Correctly!"<<endl;
                return -1;
            }
            sequenceArray[NumberOfMoves++] = inputColumn ;
            inputColumn = inputColumn-1;// int this program column number starts from zero(0)
            box[column[inputColumn]-1][inputColumn]='A' ; ///inserting the input into the board
            column[inputColumn]--; /// decrementing the input column value i.e. decrementing top value of a column
            PossibleMoves[MovesCounter++]= inputColumn+1;
            print();

            return inputColumn ;

}

int PL2Input(){ /// player 2 (B) input
            SetConsoleTextAttribute(hConsole, 10);
            cout<<"\t\t\tPlayer 2 choice column:";

            if(turn%2==0){
             //Sleep(1000);

                 inputColumn= getMoveForPL2() ;
                 //cout<<inputColumn<<endl;


            }
            else{
                cin>>inputColumn;
                ///uncomment the following line for random play mode and comment the above line
                //inputColumn = rand()%7+1;
            }



            if(inputColumn<1 || inputColumn>7 || column[inputColumn-1]<=0){
                cout<<"\t\t\tInvalid Input. Please input correctly!"<<endl;
                return -1;
            }

            sequenceArray[NumberOfMoves++] = inputColumn ;

            inputColumn = inputColumn-1 ;///col starts from 0

            box[column[inputColumn]-1][inputColumn] = 'B'; ///inserting P2 input in board
            cout<<box[column[inputColumn]-1][inputColumn]<<endl;

            column[inputColumn]-- ; /// decrementing the input column value i.e. decrementing top value of a column
            PossibleMoves[MovesCounter++]=inputColumn+1 ;

            print();
            return inputColumn;

}


bool PL1Win(int recentInputColumn){  ///conditions where player 1 will win
            recent_input_row = column[recentInputColumn] ; /// here recentInputColumn is the recent input column and recent_input_row is the recent input row
           if(k>1){
           if((box[recent_input_row][recentInputColumn]=='A'&& box[recent_input_row+1][recentInputColumn]=='A' && box[recent_input_row+2][recentInputColumn]=='A' && box[recent_input_row+3][recentInputColumn]=='A')
              || (box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row-1][recentInputColumn]=='A' && box[recent_input_row-2][recentInputColumn]=='A' && box[recent_input_row-3][recentInputColumn]=='A')
              || (box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row][recentInputColumn+1]=='A' && box[recent_input_row][recentInputColumn+2]=='A' && box[recent_input_row][recentInputColumn+3]=='A' )
              || (box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row-1][recentInputColumn+1]=='A' && box[recent_input_row-2][recentInputColumn+2]=='A' && box[recent_input_row-3][recentInputColumn+3]=='A')
              || (box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row+1][recentInputColumn-1]=='A' && box[recent_input_row+2][recentInputColumn-2]=='A' && box[recent_input_row+3][recentInputColumn-3]=='A')
              ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row][recentInputColumn-1]=='A' && box[recent_input_row][recentInputColumn-2]=='A' && box[recent_input_row][recentInputColumn-3]=='A')
              || (box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row-1][recentInputColumn-1]=='A' && box[recent_input_row-2][recentInputColumn-2]=='A' && box[recent_input_row-3][recentInputColumn-3]=='A')
              ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row+1][recentInputColumn-1]=='A' && box[recent_input_row+2][recentInputColumn-2]=='A' && box[recent_input_row+3][recentInputColumn-3]=='A')
           || (box[recent_input_row][recentInputColumn-1]=='A' && box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row][recentInputColumn+1]=='A' && box[recent_input_row][recentInputColumn+2]=='A' ) ///***
              ///------newly added

              ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row-1][recentInputColumn+1]=='A' && box[recent_input_row+1][recentInputColumn-1]=='A' && box[recent_input_row+2][recentInputColumn-2]=='A' )
              ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row-1][recentInputColumn-1]=='A' && box[recent_input_row+1][recentInputColumn+1]=='A' && box[recent_input_row-2][recentInputColumn-2]=='A' )
              ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row][recentInputColumn-1]=='A' && box[recent_input_row][recentInputColumn+1]=='A' && box[recent_input_row][recentInputColumn-2]=='A' )
                         ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row+1][recentInputColumn+1]=='A' && box[recent_input_row+2][recentInputColumn+2]=='A' && box[recent_input_row+3][recentInputColumn+3]=='A' )
              ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row+1][recentInputColumn+1]=='A' && box[recent_input_row-1][recentInputColumn-1]=='A' && box[recent_input_row-2][recentInputColumn-2]=='A' )

              ){///checking that vertical recent_input_row or horizontalrecent_input_row win or not
                return true;
           }
            else{
                return false ;
            }
        }
        return false ;
}



bool PL2Win(int recentInputColumn){   ///conditions where player 2 will win
           recent_input_row = column[recentInputColumn];
           if(k>2){
                ///checking the winning conditions for everrecent_input_row single input . an input has 8 possible combination to check up,down,left,right,upright diagonal,upleft diagonal,downright diagonal , downleft diagonal
      if((box[recent_input_row][recentInputColumn]=='B'&& box[recent_input_row+1][recentInputColumn]=='B' && box[recent_input_row+2][recentInputColumn]=='B' && box[recent_input_row+3][recentInputColumn]=='B')
              || (box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row-1][recentInputColumn]=='B' && box[recent_input_row-2][recentInputColumn]=='B' && box[recent_input_row-3][recentInputColumn]=='B')
              || (box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row][recentInputColumn+1]=='B' && box[recent_input_row][recentInputColumn+2]=='B' && box[recent_input_row][recentInputColumn+3]=='B' )
              || (box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row-1][recentInputColumn+1]=='B' && box[recent_input_row-2][recentInputColumn+2]=='B' && box[recent_input_row-3][recentInputColumn+3]=='B')
              || (box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row+1][recentInputColumn-1]=='B' && box[recent_input_row+2][recentInputColumn-2]=='B' && box[recent_input_row+3][recentInputColumn-3]=='B')
              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row][recentInputColumn-1]=='B' && box[recent_input_row][recentInputColumn-2]=='B' && box[recent_input_row][recentInputColumn-3]=='B')
              || (box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row-1][recentInputColumn-1]=='B' && box[recent_input_row-2][recentInputColumn-2]=='B' && box[recent_input_row-3][recentInputColumn-3]=='B')
              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row+1][recentInputColumn-1]=='B' && box[recent_input_row+2][recentInputColumn-2]=='B' && box[recent_input_row+3][recentInputColumn-3]=='B')
              || (box[recent_input_row][recentInputColumn-1]=='B' && box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row][recentInputColumn+1]=='B' && box[recent_input_row][recentInputColumn+2]=='B' ) ///***
              ///------newly added

              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row-1][recentInputColumn+1]=='B' && box[recent_input_row+1][recentInputColumn-1]=='B' && box[recent_input_row+2][recentInputColumn-2]=='B' )
              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row-1][recentInputColumn-1]=='B' && box[recent_input_row+1][recentInputColumn+1]=='B' && box[recent_input_row-2][recentInputColumn-2]=='B' )
              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row][recentInputColumn-1]=='B' && box[recent_input_row][recentInputColumn+1]=='B' && box[recent_input_row][recentInputColumn-2]=='B' )
              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row+1][recentInputColumn+1]=='B' && box[recent_input_row+2][recentInputColumn+2]=='B' && box[recent_input_row+3][recentInputColumn+3]=='B' )
              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row+1][recentInputColumn+1]=='B' && box[recent_input_row-1][recentInputColumn-1]=='B' && box[recent_input_row-2][recentInputColumn-2]=='B' )

              ){///checking that vertical recent_input_row or horizontalrecent_input_row win or not

                return true;
           }
           else{
            return false ;
           }
           }
           return false ;
}


void Newgame(){
    int UtilityValue;
    initialize_Column();
    initialize_box();
    NumberOfMoves = 0 ;
    MovesCounter = 0;
    sequenceFile = fopen ("GameSequence.txt","a");
    print();
    for(k=0; ;k++){
        if(k%2==0){
                for( ; ; ){
                    recentInputColumn=PL1Input();
                    if(recentInputColumn==-1){
                        continue;
                    }
                    else{
                        break;
                    }
                }

           win1 = PL1Win(recentInputColumn) ; /// checks if player 1 wins for the recent input
           if(win1==true){
            UtilityValue=50;
            color(10);

           if(turn%2!=0){
           // PlaySound(TEXT("mock.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout<<"\t\t\t================"<<endl;
            cout<<"\t\t\t|COMPUTER Wins!|"<<endl;
            cout<<"\t\t\t================"<<endl<<endl<<endl;
           }
           else{
            cout<<"\t\t\t================"<<endl;
            cout<<"\t\t\t|"<<username<<" Wins!|"<<endl;
            cout<<"\t\t\t================"<<endl<<endl<<endl;
           }
            PrintGameSequenceArray();
            fprintf(sequenceFile,"%d",UtilityValue); /// winning utility for player 1 is 50 and player 2 is 100
            fprintf(sequenceFile,"\n");
            fclose(sequenceFile);
            break;
           }
        } ///end of taking input from player 1111111111

        if(k%2==1){
                   for( ; ; ){
                    recentInputColumn=PL2Input();
                    if(recentInputColumn==-1){
                        continue;
                    }
                    else{
                        break;
                    }
                }
            win2 = PL2Win(recentInputColumn) ; /// checks if player 2 wins for the recent input
            if(win2==true){
                UtilityValue = 100;
                color(11);
            if(turn%2==0){
           // PlaySound(TEXT("mock.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout<<"\t\t\t================"<<endl;
            cout<<"\t\t\t|COMPUTER Wins!|"<<endl;
            cout<<"\t\t\t================"<<endl<<endl<<endl;
           }
           else{
            cout<<"\t\t\t================"<<endl;
            cout<<"\t\t\t|"<<username<<" Wins!|"<<endl;
            cout<<"\t\t\t================"<<endl<<endl<<endl;
           }
                PrintGameSequenceArray();
                fprintf(sequenceFile,"%d",UtilityValue); /// winning utility for player 2 is 100
                fprintf(sequenceFile,"\n");
                fclose(sequenceFile);
                break;
            }
        }///end of taking input player 2

    }


}



void StoreValue(){  ///stores value from file in a array for checking and matching previous learned moves with new moves
sequenceFile = fopen ("GameSequence.txt","a");
int ValueFromFile;
int Counter_For_Utility_Space ;
ifstream SequenceValue("GameSequence.txt");
while(!SequenceValue.eof()){
YY=0;
Counter_For_Utility_Space=XX;
    for( ; ; ){
    SequenceValue>>ValueFromFile;
        if((ValueFromFile != 50) && (ValueFromFile != 100)){
            Array_For_Saving_Moves_With_Utility[XX][YY]=ValueFromFile;
            YY++;
        }
        else if(ValueFromFile==50 || ValueFromFile==100){
            Array_For_Saving_Moves_With_Utility[Counter_For_Utility_Space][25]=ValueFromFile;
            break;
        }
    }
XX++;
}
}



int Check_Utility_Of_Moves_for_player_1(){    /// find moves for computer when computer is  first player

/// extra line added here for first move of the game to be random
if(turn==1){
    int RandomMove = rand()%7+1;
    return RandomMove ;
}
/// extra line ended here

    for(int FileRow=0;FileRow<FRow;FileRow++){
            int Possible_Moves_Array_Position=0 ;
        if(Array_For_Saving_Moves_With_Utility[FileRow][100]==50){
        for(int FileColumn=0;FileColumn<=MovesCounter;FileColumn++,Possible_Moves_Array_Position++){
            if(Array_For_Saving_Moves_With_Utility[FileRow][FileColumn]==PossibleMoves[Possible_Moves_Array_Position]) {
                if(Possible_Moves_Array_Position==MovesCounter-1){
                    int ComputerMoveDecided=  Array_For_Saving_Moves_With_Utility[FileRow][FileColumn+1];
                    return ComputerMoveDecided ;
                }
            }
            else
                break ;

        }
        }///inner loop ends
        else{
                continue;

        }
    }///outer loop ends
    int RandomMove = rand()%7+1 ;
    return RandomMove ;
}


int Check_Utility_Of_Moves_for_player_2(){  /// find moves for computer when computer is  second player

for(int FileRow=0;FileRow<FRow;FileRow++){
            int Possible_Moves_Array_Position=0 ;
        if(Array_For_Saving_Moves_With_Utility[FileRow][100]==100){
        for(int FileColumn=0;FileColumn<=MovesCounter;FileColumn++,Possible_Moves_Array_Position++){
            if(Array_For_Saving_Moves_With_Utility[FileRow][FileColumn]==PossibleMoves[Possible_Moves_Array_Position]) {
                if(Possible_Moves_Array_Position==MovesCounter-1){
                    int ComputerMoveDecided=  Array_For_Saving_Moves_With_Utility[FileRow][FileColumn+1];
                    return ComputerMoveDecided ;
                }
            }
            else
                break ;

        }
        }///inner loop ends
        else{
                continue;

        }
    }///outer loop ends
    int RandomMove = rand()%7+1 ;
    return RandomMove ;
}




int BlockTheWinningMovePL1(){  ///block winning move of player 2 for player 1
    for(int startColumn=0;startColumn<7;startColumn++){
            //cout<<"Checking blocking move!"<<endl;
       if(column[startColumn]>0){

        if(box[column[startColumn]-1][startColumn+1]=='B' && box[column[startColumn]-1][startColumn+2]=='B' && box[column[startColumn]-1][startColumn+3]=='B'){ ///1st *   B   B

            return startColumn+1 ;
        }
        else if(box[column[startColumn]-2][startColumn+1]=='B' && box[column[startColumn]-3][startColumn+2]=='B' && box[column[startColumn]-4][startColumn+3]=='B'){
                                                                                                                    /// 2nd   B

            return startColumn+1 ;                                                                                  ///    B
        }                                                                                                          /// *

        else if(box[column[startColumn]][startColumn]=='B' && box[column[startColumn]+1][startColumn]=='B' && box[column[startColumn]+2][startColumn]=='B'){
                                                                                                                    ///   *  3rd

            return startColumn+1 ;                                                                                  ///   B
        }                                                                                                       ///   B

        else if(box[column[startColumn]-1][startColumn-1]=='B' && box[column[startColumn]-1][startColumn-2]=='B' && box[column[startColumn]-1][startColumn-3]=='B'){///         4th

            return startColumn+1 ;                                                                              ///   B  B  *
        }                                                                                                     ///

        else if(box[column[startColumn]][startColumn-1]=='B' && box[column[startColumn]+1][startColumn-2]=='B' && box[column[startColumn]+2][startColumn-3]=='B'){
                                                                                                                    ///         *    5th

            return startColumn+1 ;                                                                                  ///      B
        }                                                                                                         ///   B

        else if(box[column[startColumn]][startColumn-1]=='B' && box[column[startColumn]-2][startColumn+1]=='B'  && box[column[startColumn]-3][startColumn+2]=='B'){///       B    6th**

            return startColumn+1 ;                                                                              ///        *
        }                                                                                                     ///     B

        else if(box[column[startColumn]-2][startColumn-1]=='B' && box[column[startColumn]][startColumn+1]=='B' && box[column[startColumn]+1][startColumn+2]=='B'){///   B       7th

            return startColumn+1 ;                                                                                                                                           ///     *
        }                                                                                                                                                                         ///     B

        else if(box[column[startColumn]-1][startColumn-1]=='B' && box[column[startColumn]-1][startColumn+1]=='B' && box[column[startColumn]-1][startColumn+2]=='B'){ ///1st    B    *    B

            return startColumn+1 ;
        }
        ///----------------------------------------------------------------recently added

        else if(box[column[startColumn]-1][startColumn-2]=='B' && box[column[startColumn]-1][startColumn-1]=='B' && box[column[startColumn]-1][startColumn+1]=='B'){///         **

            return startColumn+1 ;                                                                              ///   B  B  *
        }

         else if(box[column[startColumn]+1][startColumn-2]=='B' && box[column[startColumn]][startColumn-1]=='B'  && box[column[startColumn]-3][startColumn+1]=='B'){
                                                                                                                ///       B    6th**

            return startColumn+1 ;                                                                              ///        *
        }
        else if(box[column[startColumn]-3][startColumn-2]=='B' && box[column[startColumn]-2][startColumn-1]=='B' && box[column[startColumn]][startColumn+1]=='B'){///   B       7th

            return startColumn+1 ;                                                                                                                                ///     *
        }
        else if(box[column[startColumn]-4][startColumn-3]=='B' && box[column[startColumn]-3][startColumn-2]=='B' && box[column[startColumn]-2][startColumn-1]=='B'){///   B       7th

            return startColumn+1 ;                                                                                                                                  ///     *
        }
        else if(box[column[startColumn]+2][startColumn+1]=='B'  && box[column[startColumn]+3][startColumn+2]=='B' && box[column[startColumn]+4][startColumn+3]=='B' ){///   B       7th

            return startColumn+1 ;                                                                                                                                           ///     *
        }
        else if(box[column[startColumn]-1][startColumn+1]=='B' && box[column[startColumn]-1][startColumn+2]=='B'&& box[column[startColumn]-1][startColumn+3]=='B'){ ///1st *   B   B

            return startColumn+1 ;
        }
        else if(box[column[startColumn]-1][startColumn-1]=='B' && box[column[startColumn]-1][startColumn-2]=='B'&& box[column[startColumn]-1][startColumn-3]=='B'){///         4th

            return startColumn+1 ;                                                                              ///   B  B  *
        }
        else if(box[column[startColumn]-1+1][startColumn-1]=='B' && box[column[startColumn]-1+2][startColumn-2]=='B' && box[column[startColumn]-1-1][startColumn+1]=='B'){///         4th

            return startColumn+1 ;
            /////B
            ////*
            ///B
            //B
        }
        }

    }
    return -1 ;
}




int PL1WinningMove(){  ///winning move for player 1 when player 1 has three in a row

   for(int startColumn=0;startColumn<7;startColumn++){


if(column[startColumn]>0){

        if(box[column[startColumn]-1][startColumn+1]=='A' && box[column[startColumn]-1][startColumn+2]=='A' && box[column[startColumn]-1][startColumn+3]=='A'){ ///1st *   B   B

            return startColumn+1 ;
        }
        else if(box[column[startColumn]-2][startColumn+1]=='A' && box[column[startColumn]-3][startColumn+2]=='A' && box[column[startColumn]-4][startColumn+3]=='A'){
                                                                                                                    /// 2nd   B

            return startColumn+1 ;                                                                                  ///    B
        }                                                                                                          /// *

        else if(box[column[startColumn]][startColumn]=='A' && box[column[startColumn]+1][startColumn]=='A' && box[column[startColumn]+2][startColumn]=='A'){
                                                                                                                    ///   *  3rd

            return startColumn+1 ;                                                                                  ///   B
        }                                                                                                       ///   B

        else if(box[column[startColumn]-1][startColumn-1]=='A' && box[column[startColumn]-1][startColumn-2]=='A' && box[column[startColumn]-1][startColumn-3]=='A'){///         4th

            return startColumn+1 ;                                                                              ///   B  B  *
        }                                                                                                     ///

        else if(box[column[startColumn]][startColumn-1]=='A' && box[column[startColumn]+1][startColumn-2]=='A' && box[column[startColumn]+2][startColumn-3]=='A'){
                                                                                                                    ///         *    5th

            return startColumn+1 ;                                                                                  ///      B
        }                                                                                                         ///   B

        else if(box[column[startColumn]][startColumn-1]=='A' && box[column[startColumn]-2][startColumn+1]=='A'  && box[column[startColumn]-3][startColumn+2]=='A'){///       B    6th**

            return startColumn+1 ;                                                                              ///        *
        }                                                                                                     ///     B

        else if(box[column[startColumn]-2][startColumn-1]=='A' && box[column[startColumn]][startColumn+1]=='A' && box[column[startColumn]+1][startColumn+2]=='A'){///   B       7th

            return startColumn+1 ;                                                                                                                                           ///     *
        }                                                                                                                                                                         ///     B

        else if(box[column[startColumn]-1][startColumn-1]=='A' && box[column[startColumn]-1][startColumn+1]=='A' && box[column[startColumn]-1][startColumn+2]=='A'){ ///1st    B    *    B

            return startColumn+1 ;
        }
        ///----------------------------------------------------------------recently added

        else if(box[column[startColumn]-1][startColumn-2]=='A' && box[column[startColumn]-1][startColumn-1]=='A' && box[column[startColumn]-1][startColumn+1]=='A'){///         **

            return startColumn+1 ;                                                                              ///   B  B  *
        }

         else if(box[column[startColumn]+1][startColumn-2]=='A' && box[column[startColumn]][startColumn-1]=='A'  && box[column[startColumn]-3][startColumn+1]=='A'){
                                                                                                                ///       B    6th**

            return startColumn+1 ;                                                                              ///        *
        }
        else if(box[column[startColumn]-3][startColumn-2]=='A' && box[column[startColumn]-2][startColumn-1]=='A' && box[column[startColumn]][startColumn+1]=='A'){///   B       7th

            return startColumn+1 ;                                                                                                                                ///     *
        }
        else if(box[column[startColumn]-4][startColumn-3]=='A' && box[column[startColumn]-3][startColumn-2]=='A' && box[column[startColumn]-2][startColumn-1]=='A'){///   B       7th

            return startColumn+1 ;                                                                                                                                  ///     *
        }
        else if(box[column[startColumn]+2][startColumn+1]=='A'  && box[column[startColumn]+3][startColumn+2]=='A' && box[column[startColumn]+4][startColumn+3]=='A' ){///   B       7th

            return startColumn+1 ;                                                                                                                                           ///     *
        }
        else if(box[column[startColumn]-1][startColumn+1]=='A' && box[column[startColumn]-1][startColumn+2]=='A'&& box[column[startColumn]-1][startColumn+3]=='A'){ ///1st *   B   B

            return startColumn+1 ;
        }
        else if(box[column[startColumn]-1][startColumn-1]=='A' && box[column[startColumn]-1][startColumn-2]=='A'&& box[column[startColumn]-1][startColumn-3]=='A'){///         4th

            return startColumn+1 ;                                                                              ///   B  B  *
        }
        else if(box[column[startColumn]-1+1][startColumn-1]=='A' && box[column[startColumn]-1+2][startColumn-2]=='A' && box[column[startColumn]-1-1][startColumn+1]=='A'){///         4th

            return startColumn+1 ;
            /////B
            ////*
            ///B
            //B
        }
        }
    }
    return -1 ;
}



int BlockTheWinningMovePL2(){    ///block winning move of player 1 for player 2

    for(int startColumn=0;startColumn<7;startColumn++){

       if(column[startColumn]>0){
            if(box[column[startColumn]-1+1][startColumn-1]=='A' && box[column[startColumn]-1+2][startColumn-1]=='A' && box[column[startColumn]-1+3][startColumn-1]=='A'){ ///1st *   B   B

            return startColumn+1 ;
        }
                                                                                                   /// *
        if(box[column[startColumn]-1][startColumn+1]=='A' && box[column[startColumn]-1][startColumn+2]=='A' && box[column[startColumn]-1][startColumn+3]=='A'){ ///1st *   B   B

            return startColumn+1 ;
        }
        else if(box[column[startColumn]-1-1][startColumn+1]=='A' && box[column[startColumn]-2-1][startColumn+2]=='A' && box[column[startColumn]-3-1][startColumn+3]=='A'){/// 2nd   B

            return startColumn+1 ;                                                                                  ///    B
        }                                                                                                         /// *

        else if(box[column[startColumn]+1-1][startColumn]=='A' && box[column[startColumn]+2-1][startColumn]=='A' && box[column[startColumn]+3-1][startColumn]=='A'){ ///   *  3rd

            return startColumn+1 ;                                                                               ///   B
        }                                                                                                      ///   B

        else if(box[column[startColumn]-1][startColumn-1]=='A' && box[column[startColumn]-1][startColumn-2]=='A' && box[column[startColumn]-1][startColumn-3]=='A'){///         4th

            return startColumn+1 ;                                                                              ///   B  B  *
        }                                                                                                     ///

        else if(box[column[startColumn]+1-1][startColumn-1]=='A' && box[column[startColumn]+2-1][startColumn-2]=='A' && box[column[startColumn]+3-1][startColumn-3]=='A'){///         *    5th

            return startColumn+1 ;                                                                                  ///      B
        }                                                                                                         ///   B

        else if(box[column[startColumn]+1-1][startColumn-1]=='A' && box[column[startColumn]-1-1][startColumn+1]=='A'  && box[column[startColumn]-2-1][startColumn+2]=='A'){///       B    6th**

            return startColumn+1 ;                                                                              ///        *
        }                                                                                                     ///     B

        else if(box[column[startColumn]-1-1][startColumn-1]=='A' && box[column[startColumn]+1-1][startColumn+1]=='A' && box[column[startColumn]+2-1][startColumn+2]=='A'){///   B       7th

            return startColumn+1 ;                                                                                                                                           ///     *
        }                                                                                                                                                                         ///     B

        else if(box[column[startColumn]-1][startColumn-1]=='A' && box[column[startColumn]-1][startColumn+1]=='A' && box[column[startColumn]-1][startColumn+2]=='A'){ ///1st    B    *    B

            return startColumn+1 ;
        }
        ///----------------------------------------------------------------recently added

        else if(box[column[startColumn]-1][startColumn-2]=='A' && box[column[startColumn]-1][startColumn-1]=='A' && box[column[startColumn]-1][startColumn+1]=='A'){///         **

            return startColumn+1 ;                                                                              ///   B  B  *
        }

         else if(box[column[startColumn]+2-1][startColumn-2]=='A' && box[column[startColumn]+1-1][startColumn-1]=='A'  && box[column[startColumn]-2-1][startColumn+1]=='A'){///       B    6th**

            return startColumn+1 ;                                                                              ///        *
        }
        else if(box[column[startColumn]-2-1][startColumn-2]=='A' && box[column[startColumn]-1-1][startColumn-1]=='A' && box[column[startColumn]+1-1][startColumn+1]=='A'){///   B       7th

            return startColumn+1 ;                                                                                                                                           ///     *
        }
        else if(box[column[startColumn]-3-1][startColumn-3]=='A' && box[column[startColumn]-2-1][startColumn-2]=='A' && box[column[startColumn]-1-1][startColumn-1]=='A'){///   B       7th

            return startColumn+1 ;                                                                                                                                           ///     *
        }
        else if(box[column[startColumn]+1+1][startColumn+1]=='A'  && box[column[startColumn]+2+1][startColumn+2]=='A' && box[column[startColumn]+3+1][startColumn+3]=='A' ){///   B       7th

            return startColumn+1 ;                                                                                                                                           ///     *
        }
        else if(box[column[startColumn]-1][startColumn+1]=='A' && box[column[startColumn]-1][startColumn+2]=='A'&& box[column[startColumn]-1][startColumn+3]=='A'){ ///1st *   A   A

            return startColumn+1 ;
        }
        else if(box[column[startColumn]-1][startColumn-1]=='A' && box[column[startColumn]-1][startColumn-2]=='A' && box[column[startColumn]-1][startColumn-3]=='A'){///){///         4th

            return startColumn+1 ;                                                                              ///   A  A  *
        }                                                                                                       ///   A
        else if(box[column[startColumn]-1+1][startColumn-1]=='A' && box[column[startColumn]-1+2][startColumn-2]=='A' && box[column[startColumn]-1-1][startColumn+1]=='A'){///         4th

            return startColumn+1 ;
            /////A
            ////*
            ///A
            //A
        }
        }
    }
    return -1 ;
}




int PL2WinningMove(){   ///winning move for player 2 when player 2 has three in a row

   for(int startColumn=0;startColumn<7;startColumn++){
            if(box[column[startColumn]-1][startColumn+1]=='B' && box[column[startColumn]-1][startColumn+2]=='B' && box[column[startColumn]-1][startColumn+3]=='B'){ ///1st *   B   B B

            return startColumn+1 ;
        }
        else if(box[column[startColumn]-2][startColumn+1]=='B' && box[column[startColumn]-3][startColumn+2]=='B' && box[column[startColumn]-4][startColumn+3]=='B'){/// 2nd   B

            return startColumn+1 ;                                                                                  ///    B
        }                                                                                                         /// *

        else if(box[column[startColumn]][startColumn]=='B' && box[column[startColumn]+1][startColumn]=='B' && box[column[startColumn]+2][startColumn]=='B'){ ///   *  3rd

            return startColumn+1 ;                                                                               ///   B
        }                                                                                                      ///   B

        else if(box[column[startColumn]-1][startColumn-1]=='B' && box[column[startColumn]-1][startColumn-2]=='B' && box[column[startColumn]-1][startColumn-3]=='B'){///         4th

            return startColumn+1 ;                                                                              ///   B  B  *
        }                                                                                                     ///

        else if(box[column[startColumn]][startColumn-1]=='B' && box[column[startColumn]+1][startColumn-2]=='B' && box[column[startColumn]+2][startColumn-3]=='B'){///         *    5th

            return startColumn+1 ;                                                                                  ///      B
        }                                                                                                         ///   B

        else if(box[column[startColumn]][startColumn-1]=='B' && box[column[startColumn]-2][startColumn+1]=='B'  && box[column[startColumn]-3][startColumn+2]=='B'){///       B    6th**

            return startColumn+1 ;                                                                              ///        *
        }                                                                                                     ///     B

        else if(box[column[startColumn]-2][startColumn-1]=='B' && box[column[startColumn]][startColumn+1]=='B' && box[column[startColumn]+1][startColumn+2]=='B'){///   B       7th

            return startColumn+1 ;                                                                                                                                           ///     *
        }                                                                                                                                                                         ///     B

        else if(box[column[startColumn]-1][startColumn-1]=='B' && box[column[startColumn]-1][startColumn+1]=='B' && box[column[startColumn]-1][startColumn+2]=='B'){ ///1st    B    *    B

            return startColumn+1 ;
        }
        ///----------------------------------------------------------------recently added

        else if(box[column[startColumn]-1][startColumn-2]=='B' && box[column[startColumn]-1][startColumn-1]=='B' && box[column[startColumn]-1][startColumn+1]=='B'){///         **

            return startColumn+1 ;                                                                              ///   B  B  *
        }

         else if(box[column[startColumn]+2-1][startColumn-2]=='B' && box[column[startColumn]+1-1][startColumn-1]=='B'  && box[column[startColumn]-2-1][startColumn+1]=='B'){///       B    6th**

            return startColumn+1 ;                                                                              ///        *
        }
        else if(box[column[startColumn]-2-1][startColumn-2]=='B' && box[column[startColumn]-1-1][startColumn-1]=='B' && box[column[startColumn]+1-1][startColumn+1]=='B'){///   B       7th

            return startColumn+1 ;                                                                                                                                           ///     *
        }
        else if(box[column[startColumn]-3-1][startColumn-3]=='B' && box[column[startColumn]-2-1][startColumn-2]=='B' && box[column[startColumn]-1-1][startColumn-1]=='B'){///   B       7th

            return startColumn+1 ;                                                                                                                                           ///     *
        }
        else if(box[column[startColumn]+1+1][startColumn+1]=='B'  && box[column[startColumn]+2+1][startColumn+2]=='B' && box[column[startColumn]+3+1][startColumn+3]=='B' ){///   B       7th

            return startColumn+1 ;                                                                                                                                           ///     *
        }

        else if(box[column[startColumn]-1][startColumn+1]=='B' && box[column[startColumn]-1][startColumn+2]=='B'){ ///1st *   A   A

            return startColumn+1 ;
        }
        else if(box[column[startColumn]-1][startColumn-1]=='B' && box[column[startColumn]-1][startColumn-2]=='B'){///         4th

            return startColumn+1 ;                                                                              ///   A  A  *
        }


    }
    return -1 ;
}



int getMoveForPL1(){
       int BlockPosition = BlockTheWinningMovePL1();
       int WinningMove = PL1WinningMove();
       int MoveFromFile = Check_Utility_Of_Moves_for_player_1();



        if(WinningMove!=-1){
            return WinningMove ;
       }
         else if(BlockPosition!=-1){
            return BlockPosition;
       }
       else {
            SetConsoleTextAttribute(hConsole, 15);

            cout<<"COMPUTER is thinking ";
            for(int dot=0;dot<10;dot++){
                cout<<".";
                Sleep(100);
            }
            cout<<endl;
            return MoveFromFile;
       }

}


int getMoveForPL2(){
       int BlockPosition = BlockTheWinningMovePL2();
       int WinningMove = PL2WinningMove();
       int MoveFromFile = Check_Utility_Of_Moves_for_player_2();

       if(WinningMove!=-1){
            return WinningMove ;
       }
       else if(BlockPosition!=-1){
            return BlockPosition;
       }
       else {
            SetConsoleTextAttribute(hConsole, 15);

            cout<<"COMPUTER is thinking ";
            for(int dot=0;dot<10;dot++){
                cout<<".";
                Sleep(100);
            }
            cout<<endl;
            return MoveFromFile;
       }

}





