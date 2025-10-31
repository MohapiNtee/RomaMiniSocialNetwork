#ifndef CLASS_1_H
#define CLASS_1_H

#include <unordered_map>
#include <map>
#include<iostream>
#include "linkedlists.h"
#include<vector>
#include<fstream>
#include<sstream>
#include <queue>
#include <ctime>
using namespace std;

struct msg{
	string Username;
	string text;
};

struct DOB{
	int day; 
	int month;
	int year;
};


class post{
	    string username;
	    string content;
	    string timestamp;
	public:
		post();
		void setPost(string user, string text, string timestamp0); 
		void setPost(string user, string text);
		string getUsername() const;   
		string getContent();
		void displayPost();	
	friend class user;
};

class SocialGraph{
		map<string, vector<string>> friendsList;
	public:
		// Add a friendship (bidirectional)
		void addFriendship(const string& user1, const string& user2);
		// View all friends of a user
		void viewFriends(const string& user);
		// Check if two users are friends
		bool areFriends(const string& user1, const string& user2);
		void loadFriendshipsFromFile();
		void saveFriendshipsToFile(const string& filename);
		bool hasFriends(const string& userName);
};

class user{
	protected:
		int userID;
		string fulname;
		string userName;
		string address;
		DOB DateOfBirth;
		string PhoneNumber[2];
		string Email;
		string occupation;
		vector<Linkedlist<msg>> friendMessages;
		int friendcount;
		string course;
		queue<post> Posts;// recent Post Printed first (FIFO)		
	public:
		user();
		void setDetails(int userID0, string fulname0,string userName0, string address0,DOB DateOfBirth0,string *PhoneNum,string Email0, string occupation0);
		void updateProfile(string fulname0,string address0 ,DOB DateOfBirth0, string occupation0,string course);
		void getMessage(string  friendUserName);
		void sendMessage(string FriendName, string txt);
		void loadMessagesFromFile();
		void writeMessagesFromFile();
		void uploadProfileFromFile(string userName);
		void displayProfile();
		string getUserName() const;
		void loadPostsFromFile();
		void viewAllPosts();
		void addPost(post newPost0);
		void savePostsToFile();
		void displayFriendPosts(const string& friendUserName);
		void displayAllUsernames();
			
};

#endif