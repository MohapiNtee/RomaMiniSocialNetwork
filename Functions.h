#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include<iostream>
#include "Class_1.h"
#include<vector>
#include<fstream>
#include<sstream>
#include <ctime>
using namespace std;

unordered_map<string, string> loginTable; // username-password pairs


void EditProfile(user& U){
    string firstName, surName, address, email, occupation, course = "";
    string dobStr;
    DOB dob;
    string phone1, phone2;
    
	cout <<endl<<"Edit Profile"<<endl;
    cin.ignore();
    cout << "Enter Firstname: ";
    cin.ignore();
    getline(cin, firstName);
    cout << "Enter Surname: ";
    getline(cin, surName);
    cout << "Enter Date Of Birth (DD-MM-YYYY): ";
    getline(cin, dobStr);
    stringstream dobStream(dobStr);
    char dash;
    dobStream >> dob.day >> dash >> dob.month >> dash >> dob.year;

    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Enter Occupation (Student / Lecturer / Other): ";
    getline(cin, occupation);

    if (occupation == "Student" || occupation == "Lecturer") {
        cout << "Enter Course: ";
        getline(cin, course);
    }

    string fullName = firstName + " " + surName;
	U.updateProfile(fullName,address,dob, occupation, course);
	cout << "Profile Updated "<<endl;
	return;
}

void ViewProfile(user U){
	U.displayProfile();
	int choice;
	cout << endl;
	cout << "1) Edit Profile"<<endl;
    cout << "2) Back to DASHBOARD "<<endl;
    cout << "Enter your choice: ";
    cin >> choice;
	cout<<endl;
	if(choice == 1){
		EditProfile(U);
		ViewProfile(U);
	}
}

void ViewPost(user& U){
	U.viewAllPosts();
	int choice;
	string contents;
	post newPost;
	cout << endl;
	cout << "1) Add Post"<<endl;
    cout << "2) Back to DASHBOARD "<<endl;
    cout << "Enter your choice: ";
	cin >> choice;
	cout<<endl;
	if(choice == 1){
		cout<<"Enter new Post"<<endl;
		cin.ignore();
    	getline(cin, contents);
    	newPost.setPost( U.getUserName(),contents);
    	U.addPost(newPost);
		cout<<"--------Posted---------"<<endl;	
	}
	return;
}

void AddFriend(user &U,SocialGraph &FGraph){
	U.displayAllUsernames();
	string Uname;
	cout<<endl<<"Enter The UserName"<<endl;
	cin>>Uname;
	if(!FGraph.areFriends(Uname,U.getUserName())){
		FGraph.addFriendship(Uname, U.getUserName());
		FGraph.saveFriendshipsToFile("Friends.txt");
		cout<<"Your Now Friends With "<<Uname<<endl<<endl;
	}
	else{
		cout<<"Your Are Already Friends"<<endl;
	}
	return;
}

void ViewFriends(user& U,SocialGraph &FGraph){
	FGraph.viewFriends(U.getUserName());
	string Uname;
	if(FGraph.hasFriends(U.getUserName())){
		cout<<endl<<"Enter Friend`s UserName to Socialize with: "<<endl<<">";
		cin>>Uname;
		int choice, num = 1;
		cout<<endl;
		do{
		cout <<"========Socializig With "<<Uname<<"========"<<endl;
		cout << "1. Messages"<<endl;
	    cout << "2. View Posts"<<endl;
	    cout << "3. View Profile"<<endl;
	    cout << "4. Back to DASHBOARD "<<endl;
	    cout << "===========================\n";
	    cout << "Enter your choice: ";
	    cin >> choice;
	    switch (choice) {
	        case 1:
	        	{
	        	int choice0;string msg0;
	        	U.uploadProfileFromFile(Uname);
	            U.getMessage(Uname);
	            cout<<"1. Send Message"<<endl;
	            cout<<"2. Back"<<endl;
	            cout << "Enter your choice: ";
	            cin>>choice0;
	            if(choice0 == 1){
	            	cout<<"Write Message:"<<endl;
	            	cin.ignore();
	            	getline(cin, msg0);
	            	U.sendMessage(Uname, msg0);
	            	U.writeMessagesFromFile();
				}
	            break;
	        }
	        case 2:
	            U.displayFriendPosts(Uname);
	            break;
	        case 3:{
	        		user *user1 = new user();
					user1->uploadProfileFromFile(Uname);
					user1->displayProfile();
					delete  user1;
				break;
			}
			case 4:{
				num = 0;
				break;
			}    
	        default:
	            cout << "Invalid Input! Please try again.\n";
	            break;   
	    }	    
		}while(num != 0);
	}
	return;
}


// =============================
// DASHBOARD MENU FUNCTION
// =============================
void DashboardMenu(string UserName) {
	user user0;
	user0.uploadProfileFromFile(UserName);
	user0.loadPostsFromFile();
	SocialGraph Frienship;
	Frienship.loadFriendshipsFromFile();
	user0.loadMessagesFromFile();
    int choice, num = 1;
    do{
		cout<<endl;
	    cout << "======== DASHBOARD ========\n";
	    cout << "1. My Profile\n";
	    cout << "2. All Posts\n";
	    cout << "3. Add Friend\n";
	    cout << "4. View Friends\n";
	    cout << "5. Logout\n";
	    cout << "===========================\n";
	    cout << "Enter your choice: ";
	    cin >> choice;
	    switch (choice) {
	        case 1:
	            ViewProfile(user0);
	            break;
	        case 2:
	            ViewPost(user0);
	            break;
	        case 3:
	            AddFriend(user0,Frienship);
	            break;
	        case 4:
	            ViewFriends(user0, Frienship);
	            user0.uploadProfileFromFile(UserName);//restore this users profile
	            break;
	        case 5:
	        	num = 0;
	        	cout<<"Logging out ... "<<endl;
	            break;
	        default:
	            cout << "Invalid Input! Please try again.\n";
	            break;   
	    }
	}while(num != 0);
	user0.savePostsToFile();
}


void createUserProfile(const string &username) {
    string firstName, surName, address, email, occupation, course;
    string dobStr;
    DOB dob;
    string phone1, phone2;
    static int userID = 1000; // you can load this from file later if you want unique IDs
    
	cout <<username <<" Create your Profile"<<endl;
    cin.ignore();
    cout << "Enter Firstname: ";
    cin.ignore();
    getline(cin, firstName);
    cout << "Enter Surname: ";
    getline(cin, surName);
    cout << "Enter Date Of Birth (DD-MM-YYYY): ";
    getline(cin, dobStr);
    stringstream dobStream(dobStr);
    char dash;
    dobStream >> dob.day >> dash >> dob.month >> dash >> dob.year;

    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Enter Occupation (Student / Lecturer / Other): ";
    getline(cin, occupation);

    if (occupation == "Student" || occupation == "Lecturer") {
        cout << "Enter Course: ";
        getline(cin, course);
    }

    cout << "Enter Phone number 1: ";
    getline(cin, phone1);
    cout << "Enter Phone number 2 (optional, press Enter to skip): ";
    getline(cin, phone2);

    string phoneArray[2] = {phone1, phone2};

    string fullName = firstName + " " + surName;

    // Store in Users.txt
    ofstream file("Users.txt", ios::app);
    if (!file) {
        cerr << "Error opening Users.txt for writing." << endl;
        return;
    }
    // Format: username:userID~fullname~email~address~occupation~course~PhoneNumber1~PhoneNumber2~day~month~year
    file << username << ":"<<userID<< "~" << fullName << "~" << email << "~" << address << "~" << occupation<< "~" <<phone1<< "~" <<phone2<<"~"<<dob.day<<"~"<<dob.month<<"~"<<dob.year<<"~"<<course<<endl;
    file.close();
    cout << "Your Profile has been saved successfully "<<endl;
}


void loadLoginData() {
    ifstream file("Login.txt");
    if (!file) {
        cerr << "Login file not found. Creating new one...\n";
        ofstream newFile("Login.txt");
        newFile.close();
        return;
    }
    string username, password;
    while (file >> username >> password) {
        loginTable[username] = password;
    }
    file.close();
}

void saveLoginData() {
    ofstream file("Login.txt");
    for (auto &entry : loginTable) {
        file << entry.first << " " << entry.second << endl;
    }
    file.close();
}

void registerUser() {
    string username, password;
    cout <<endl<<"--- Register ---"<<endl;
    cout << "Enter Username: ";
    cin >> username;
    if (loginTable.find(username) != loginTable.end()) {
        cout << "Username already exists!"<<endl;
        return;
    }
    cout << "Enter Password: ";
    cin >> password;
    loginTable[username] = password;
    saveLoginData();
    cout << "User registered successfully!"<<endl<<endl;
    createUserProfile(username);//building the user profile
    DashboardMenu(username);
    
}

void loginUser() {
    string username, password;
    cout <<endl<<"--- Login ---"<<endl;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;
    if (loginTable.find(username) != loginTable.end() && loginTable[username] == password) {
        cout << "Login Successful! Welcome, " << username << "!\n";
        DashboardMenu(username);
    }
    else{
    	cout << "Invalid Username or Password.\n";
	}
}


//----------------------------METHODS OF THE USER CLASS----------------------------------------------------

user::user():course(""), fulname(""),userName(""), address(""),Email(""),occupation(""), userID(0){}

void user::getMessage(string  friendUserName){
	for(Linkedlist<msg> friendMessage : friendMessages){
		if(friendMessage.getNode()->data.Username == friendUserName){
			Node<msg> *temp = friendMessage.getNode()->next;
			if(temp != NULL){
				cout<<endl<<"----------------------------------"<<endl;
				while(temp != NULL){
				cout<< temp->data.Username<< ":" <<temp->data.text<<endl;
				temp = temp->next;
				}
				cout<<"----------------------------------"<<endl;
			}
			else{
				cout<<endl<<"----------------------------------"<<endl;
				cout<<"No Messages Available!"<<endl;
				cout<<"----------------------------------"<<endl;
			}
			break;
		}
	}
}
		
void user::loadMessagesFromFile(){
	ifstream file("Msg_" + this->userName + ".txt");
		if(!file){
			cerr<<"Message File Not Found!"<<endl;
		}
		else{
			string line;
			while(getline(file, line)){
				Linkedlist<msg> Messages;
				stringstream s(line);
				msg M;
				string userName0, txt;
				int count = 0;
				for(int i = 0; i < line.length(); ++i){
					if(line[i] == '|'){
						++count;
					}
				}
				for(int i = 0; i < count ; ++i){
					getline(s,userName0, '~');
					getline(s,txt, '|');
					M.Username = userName0;
					M.text = txt;
					Messages.insertAtTail(M);	
				}
				friendMessages.push_back(Messages);					
			}
		}
	file.close();
}

void user::setDetails(int userID0, string fulname0,string userName0, string address0,DOB DateOfBirth0,string *PhoneNum,string Email0, string occupation0){
	userID = userID0;
	fulname = fulname0;
	userName = userName0;
	address = address0;
	DateOfBirth = DateOfBirth0;
	//deep copy
	PhoneNumber[0] = PhoneNum[0];
	PhoneNumber[1] = PhoneNum[1];
	Email = Email0;
	occupation = occupation0;	
}

void user::updateProfile(string fulname0,string address0 ,DOB DateOfBirth0, string occupation0, string course0){
	fulname = fulname0;
	address = address0;
	DateOfBirth = DateOfBirth0;
	occupation = occupation0;
	course	= course0;
}
void user::sendMessage(string FriendName, string txt){
	msg msg0;
	msg0.text = txt;
	msg0.Username = userName;
	for(Linkedlist<msg>& friendMessage : friendMessages){
		if(friendMessage.getNode()->data.Username == FriendName){
			friendMessage.insertAtTail(msg0);
			break;
		}
	}
}

void user::writeMessagesFromFile(){
	ofstream file("Msg_" + this->userName + ".txt");
	if(!file)
	{
		cerr<<"Message File Not Found!"<<endl;
	}
	else{
		for(Linkedlist<msg>& friendMessage : friendMessages){
			Node<msg> *temp = friendMessage.getNode();
			while(temp != NULL){
				file<<temp->data.Username<<"~"<<temp->data.text<<"|";
					temp = temp->next;
			}
			file<<endl;
		}
	}
	file.close();
}


void user::uploadProfileFromFile(string searchUserName) {
    ifstream file("Users.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open Users.txt file.\n";
        return;
    }
    string line;
    string token[15];
    while (getline(file, line)) {
    	stringstream ss(line);
    	getline(ss, token[0], ':');
    	if(token[0] == searchUserName){
    		getline(ss, token[1], '~');
    		getline(ss, token[2], '~');
    		getline(ss, token[3], '~');
    		getline(ss, token[4], '~');
    		getline(ss, token[5], '~');
    		getline(ss, token[6], '~');
    		getline(ss, token[7], '~');
    		getline(ss, token[8], '~');
    		getline(ss, token[9], '~');
    		getline(ss, token[10], '~'); 
    		getline(ss, token[11], '~');
			// 		
			this->userName = token[0];
	        this->userID = stoi(token[1]);
	        this->fulname = token[2];
	        this->Email = token[3];
	        this->address = token[4];
	        this->occupation = token[5];
	        this->PhoneNumber[0] = token[6];
	        this->PhoneNumber[1] = token[7];
	        this->DateOfBirth.day = stoi(token[8]);
	        this->DateOfBirth.month = stoi(token[9]);
	        this->DateOfBirth.year = stoi(token[10]);
	        this->course = token[11];
    	}
	}
	file.close();
}

void user::displayAllUsernames() {
    ifstream file("Login.txt");
    if (!file) {
        cout << "Error: Could not open Login.txt\n";
        return;
    }
    string username, pin;
    cout << "\n--- List of User ---\n";

    while (file >> username >> pin) {
        cout << username << endl;
    }

    file.close();
}


void user::displayProfile() {
	cout<<endl;
    cout << "==========================" << endl;
    cout << "          PROFILE         " << endl;
    cout << "==========================" << endl;
    cout << "Full Name    : " << fulname << endl;
    cout << "Username     : " << userName << endl;
    cout << "Email        : " << Email << endl;
    cout << "Address      : " << address << endl;
    cout << "Occupation   : " << occupation << endl;
    if(course !=""){
    	cout << "course       : " << course << endl;	
	}
    cout << "Date of Birth: " 
         << DateOfBirth.day << "-" 
         << DateOfBirth.month << "-" 
         << DateOfBirth.year << endl;
    cout << "==========================" <<endl<<endl;
}

string user::getUserName() const{return userName;}

void user::loadPostsFromFile() {
    ifstream file("Posts.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open Posts.txt file.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token[3];
		
		
        getline(ss, token[0], '~'); // username
        getline(ss, token[1], '~'); // content
        getline(ss, token[2], '~'); // content

        post newPost;
        newPost.setPost(token[0], token[1],token[2]);

        // Store in queue
        Posts.push(newPost);
    }
    file.close();
}

void user::viewAllPosts() {
    if (Posts.empty()) {
        cout << "?? No posts available.\n";
        return;
    }

    queue<post> temp = Posts; // copy so we don't lose original
    while (!temp.empty()) {
        temp.front().displayPost();
        temp.pop();
    }
}

void user::displayFriendPosts(const string& friendUserName) {
    // Create a temporary queue to preserve original order
    queue<post> temp = Posts;
    bool found = false;

    cout << "\n--- Posts by " << friendUserName << " ---\n";

    while (!temp.empty()) {
        post currentPost = temp.front();
        temp.pop();

        // Check if the post belongs to the specified friend
        if (currentPost.getUsername() == friendUserName) {
        		currentPost.displayPost();
			    found = true;
        }
    }
    if (!found) {
        cout << "No posts found for user: " << friendUserName <<endl<<endl;
    }
}


//----------------------------END OF USER CLASS METHODS----------------------------------------------------

//----------------------------METHODS OF THE POST CLASS----------------------------------------------------

post::post() : username(""), content(""), timestamp("") {}
void post::setPost(string user, string text) {
    username = user;
    content = text;
	// Set timestamp (current date/time)
    time_t now = time(0);
    char* dt = ctime(&now);
    timestamp = string(dt);
    timestamp.pop_back(); // remove trailing newline
}

void post::setPost(string user, string text, string timestamp0) {
    username = user;
    content = text;
    timestamp = timestamp0;
}

string post::getUsername() const{ return username; }

string post::getContent(){ return content; }

void post::displayPost(){
    cout <<endl<< "---------------------------------\n";
    cout << "User: " << username << "\n";
    cout << "Posted on: " << timestamp << "\n";
    cout << "Content: " << content << "\n";
    cout << "---------------------------------"<<endl<<endl;
}

void user::addPost(post newPost0) {
    Posts.push(newPost0);
}

void user::savePostsToFile() {
    ofstream file("Posts.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open Posts.txt for writing.\n";
        return;
    }

    // Copy queue to preserve order
    queue<post> temp = Posts;

    while (!temp.empty()) {
        post p = temp.front();
        temp.pop();
        file << p.username << "~"
             << p.content << "~"
             << p.timestamp << "\n";
    }
    file.close();
}


//----------------------------END OF POST CLASS METHODS----------------------------------------------------

//----------------------------METHODS OF THE SocialGraph CLASS----------------------------------------------------

void SocialGraph:: addFriendship(const string& user1, const string& user2) {
    friendsList[user1].push_back(user2);
    friendsList[user2].push_back(user1);
}

    // View all friends of a user
void SocialGraph::viewFriends(const string& user) {
	if (friendsList.find(user) == friendsList.end()) {
        cout << user << " has no friends yet.\n";
        return;
    }

    cout << user << "'s friends:\n";
    for (auto& friendName : friendsList[user]) {
        cout << "- " << friendName << endl;
    }
}

    // Check if two users are friends
bool SocialGraph::areFriends(const string& user1, const string& user2) {
    for (auto& f : friendsList[user1]) {
        if (f == user2) return true;
    }
    return false;
}

void SocialGraph::loadFriendshipsFromFile() {
    ifstream file("Friends.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string user, friendName;
        getline(ss, user, '~');
        while (getline(ss, friendName, '~')) {
            friendsList[user].push_back(friendName);
        }
    }
}

void SocialGraph::saveFriendshipsToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open " << filename << " for writing.\n";
        return;
	}

    for (auto& pair : friendsList) {
        const string& user = pair.first;
        const vector<string>& friends = pair.second;
        file << user;
        for (auto& friendName : friends) {
            file << "~" << friendName;
        }
        file << "\n";
    }

    file.close();
}

bool SocialGraph::hasFriends(const string& userName) {
    // Check if the user exists in the map
    auto it = friendsList.find(userName);
    if (it == friendsList.end()) 
        return false; // user not found ? no friends
    // Check if their friend list is empty
    return !it->second.empty();
}


//----------------------------END OF THE SocialGraph CLASS METHODS----------------------------------------------------

#endif