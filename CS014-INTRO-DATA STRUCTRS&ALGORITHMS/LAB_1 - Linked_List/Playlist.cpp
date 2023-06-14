#include "Playlist.h"

using namespace std;

PlaylistNode::PlaylistNode(){
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = 0;
}

PlaylistNode::PlaylistNode(string uniqueID, string songName, string artistName, int songLength){
    this->uniqueID = uniqueID;
    this->songName = songName;
    this->artistName = artistName;
    this-> songLength = songLength;
    nextNodePtr = nullptr;
}

//123
//1243
void PlaylistNode::InsertAfter(PlaylistNode* currNode){
    PlaylistNode* temp = this->nextNodePtr;
    this->nextNodePtr = currNode;
    currNode->nextNodePtr = temp;
    // if(currNode->GetNext() == nullptr){
    //     newNode->nextNodePtr = this->GetNext();  
    //     this->nextNodePtr = newNode;
    // }
    // else{
    // }
}

void PlaylistNode::SetNext(PlaylistNode* currNode){
    this->nextNodePtr = currNode;
}

string PlaylistNode::GetID() const{
    return uniqueID;
}

string PlaylistNode::GetSongName() const{
    return songName;
}

string PlaylistNode::GetArtistName() const{
    return artistName;
}

int PlaylistNode::GetSongLength() const{
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const{
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode(){
    cout<< "Unique ID: " << this->GetID() << endl;
    cout<< "Song Name: " << this->GetSongName() << endl;
    cout<< "Artist Name: " << this->GetArtistName() << endl;
    cout<< "Song Length (in seconds): " << this->GetSongLength() << endl;
}