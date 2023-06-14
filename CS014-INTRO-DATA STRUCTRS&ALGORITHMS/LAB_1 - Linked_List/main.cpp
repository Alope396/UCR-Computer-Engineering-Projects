#include <iostream>
#include <string>
// #include <vector>

#include "Playlist.h"

using namespace std;

void PrintMenue(string title);

int main(){
    string title;

    cout<< "Enter playlist's title:" << endl << endl;
    getline(cin, title);
    PrintMenue(title);
    return 0;
}

void PrintMenue(string title){
    char userInput = ' ';
    // vector <PlaylistNode*> Playlist;
    PlaylistNode* head = nullptr;
    PlaylistNode* tail = nullptr;
    PlaylistNode* currNode = nullptr;
    PlaylistNode* lastNode = nullptr;
    string ID;
    string sName;
    string aName;
    int length;
    int counter;
    int numSongs = 0;
    int oldPosition;
    int newPosition;
    cout<< title << " PLAYLIST MENU" << endl;
    cout<< "a - Add song" << endl;
    cout<< "d - Remove song" << endl;
    cout<< "c - Change position of song" << endl;
    cout<< "s - Output songs by specific artist" << endl;
    cout<< "t - Output total time of playlist (in seconds)" << endl;
    cout<< "o - Output full playlist" << endl;
    cout<< "q - Quit" << endl << endl;
    cout<< "Choose an option:" << endl;
    cin>> userInput;

    while(userInput != 'q' && userInput != 'Q'){
        if(userInput == 'a' || userInput == 'A'){
            cout<< "ADD SONG" << endl;
            cout<< "Enter song's unique ID:" << endl;
            cin.clear();
            cin.ignore();
            getline(cin, ID);
            cout<< "Enter song's name:" << endl;
            getline(cin, sName);
            cout<< "Enter artist's name:" << endl;
            cin.clear();
            getline(cin, aName);
            cout<< "Enter song's length (in seconds):" << endl;
            cin>> length;
            if(head == nullptr){
                head = new PlaylistNode(ID, sName, aName, length);
                tail = head;
            }
            else{
                PlaylistNode* newNode = new PlaylistNode(ID, sName, aName, length);
                tail->SetNext(newNode);
                tail = newNode;
            }
            numSongs++;
            cout<< endl;
        }
        if(userInput == 'd' || userInput == 'D'){
            cout<< "REMOVE SONG" << endl;
            cout<< "Enter song's unique ID:" << endl;
            cin.clear();
            cin.ignore();
            getline(cin, ID);
            if(head->GetID() == ID){
                PlaylistNode* temp = head;
                head = head->GetNext();
                cout<< "\"" << temp->GetSongName() << "\" removed." << endl;
                delete temp;
            }
            else if(tail->GetID() == ID){
                cout<< "\"" << tail->GetSongName() << "\" removed." << endl;
                delete tail;
            }
            else{
                lastNode = head;
                currNode = head->GetNext();
                while(currNode != tail){
                    if(currNode->GetID() == ID){
                        PlaylistNode* temp = currNode;
                        cout<< "\"" << currNode->GetSongName() << "\" removed." << endl;
                        lastNode->SetNext(currNode->GetNext());
                        delete temp;
                    }
                    currNode = currNode->GetNext();
                    lastNode = lastNode->GetNext();
                }
            }
            numSongs--;
            cout<< endl;
        }
        //colaborated with Jake Hofferbert
        if(userInput == 'c' || userInput == 'C'){
            cout<< "CHANGE POSITION OF SONG" << endl;
            cout<< "Enter song's current position:" << endl;
            cin>> oldPosition;
            // cout<< endl;
            cout<< "Enter new position for song:" << endl;
            cin>> newPosition;
            PlaylistNode* lastOldPositionNode = head;
            PlaylistNode* newPositionNode = head;
            PlaylistNode* lastNewPositionNode = head;
            currNode = head;
            while(oldPosition < 1 || oldPosition > numSongs){
                cout<< "Enter song's current position:" << endl;
                cin>> oldPosition;
            }
            if(newPosition < 1){
                newPosition = 1;
            }
            if(newPosition > numSongs){
                newPosition = numSongs;
            }
                for(int i = 0; i < oldPosition - 1; i++){
                    currNode = currNode->GetNext();
                }
                for(int i = 0; i < oldPosition - 2; i++){
                    lastOldPositionNode = lastOldPositionNode->GetNext();
                }
                for(int i = 0; i < newPosition - 1; i++){
                    newPositionNode = newPositionNode->GetNext();
                }
                for(int i = 0; i < newPosition - 2; i++){
                    lastNewPositionNode = lastNewPositionNode->GetNext();
                }
                //1234
                //1423
                if(oldPosition > newPosition){
                    lastOldPositionNode->SetNext(currNode->GetNext());
                    currNode->SetNext(newPositionNode);
                    if(newPositionNode != head){
                        lastNewPositionNode->SetNext(currNode);
                    }
                    else{
                        head = currNode;
                    }
                }
                //1234
                //1342
                if(oldPosition < newPosition && currNode != head){
                    lastOldPositionNode->SetNext(currNode->GetNext());
                    currNode->SetNext(newPositionNode->GetNext());
                    newPositionNode->SetNext(currNode);
                }
                //1234
                //2314
                if(oldPosition < newPosition && currNode == head){
                    head = currNode->GetNext();
                    currNode->SetNext(newPositionNode->GetNext());
                    newPositionNode->SetNext(currNode);
                }
                if(oldPosition == numSongs){
                    tail = lastOldPositionNode;
                }
                if(newPosition == numSongs){
                    tail = currNode;
                }
                // currNode->SetNext(newPositionNode);
            cout<< "\"" << currNode->GetSongName() << "\" moved to position " << newPosition << endl;
            cout<< endl;
        }
        if(userInput == 's' || userInput == 'S'){
            cout<< "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout<< "Enter artist's name:" << endl;
            cout<< endl;
            cin.clear();
            cin.ignore();
            getline(cin, aName);
            PlaylistNode* currNode = head;
            counter = 1;
            while(currNode != nullptr){
                if(currNode->GetArtistName() == aName){
                    cout<< counter << "." << endl;
                    currNode->PrintPlaylistNode();
                    cout<< endl;
                }
                currNode = currNode->GetNext();
                counter++;
            }
            // for(unsigned i = 0; i < Playlist.size(); i++){
            //     if(Playlist.at(i)->GetArtistName() == aName){
            //         cout<< i + 1 << "." << endl;
            //         Playlist.at(i)->PrintPlaylistNode();
            //         cout<< endl;
            //     }
            // }
        }
        if(userInput == 't' || userInput == 'T'){
            int totalTime = 0;
            currNode = head;
            while(currNode != nullptr){
                totalTime = totalTime + currNode->GetSongLength();
                currNode = currNode->GetNext();
            }
            cout<< "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            cout<< "Total time: " << totalTime << " seconds" << endl;
            cout<< endl;
        }
        if(userInput == 'o' || userInput == 'O'){
            cout<< title << " - OUTPUT FULL PLAYLIST" << endl;
            currNode = head;
            if(currNode == nullptr){
                cout<< "Playlist is empty" << endl;
                cout<< endl;
            }
            else{
                counter = 1;
                while(currNode != nullptr){
                    cout<< counter << "." << endl;
                    currNode->PrintPlaylistNode();
                    cout<< endl;
                    currNode = currNode->GetNext();
                    counter++;
                }
            }
        }
        cout<< title << " PLAYLIST MENU" << endl;
        cout<< "a - Add song" << endl;
        cout<< "d - Remove song" << endl;
        cout<< "c - Change position of song" << endl;
        cout<< "s - Output songs by specific artist" << endl;
        cout<< "t - Output total time of playlist (in seconds)" << endl;
        cout<< "o - Output full playlist" << endl;
        cout<< "q - Quit" << endl << endl;
        cout<< "Choose an option:" << endl;
        cin>> userInput;
    }
}