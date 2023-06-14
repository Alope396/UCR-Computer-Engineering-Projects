#include <string>
#include <iostream>

using namespace std;

struct IntNode{
	int data;
	IntNode *next;
	IntNode(int data) : data(data), next(nullptr) { }
};

class PlaylistNode{
    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode* nextNodePtr;
    public:
        PlaylistNode();
        PlaylistNode(string , string , string ,int );
        void InsertAfter(PlaylistNode* );
        void SetNext(PlaylistNode* );
        string GetID() const;
        string GetSongName() const;
        string GetArtistName() const;
        int GetSongLength() const;
        PlaylistNode* GetNext() const;
        void PrintPlaylistNode();
};