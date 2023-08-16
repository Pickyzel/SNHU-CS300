/============================================================================
// Name        : CoursePlanner.cpp
// Author      : Tiffany McDonnell
// Version     : 1.0
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Defines what a course is
struct Course {
	string courseNumber;
	string name;
	string prerequisite1;
	string prerequisite2;

	//constructor
	Course() {
		courseNumber = "";
		name = "";
		prerequisite1 = "N/A";
		prerequisite2 = "N/A";
	}

	// an overloaded constructor
	Course(string courseNum, string name, string prerequisite1, string prerequisite2) {
		this->courseNumber = courseNum;
		this->name = name;
		this->prerequisite1 = prerequisite1;
		this->prerequisite2 = prerequisite2;
	}
}


// Defines node
struct Node {
	Course course;
	Node* left;
	Node* right;

	//node constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	// overloaded node constructor that takes course
	Node(Course aCourse) :
		Node() {
		course = aCourse;
	}
};

//Defines the BST 
class courseBinarySearchTree {

	//private members
private:
	void inOrder(Node* node);
	void addNode(Node* node, Course course);

	//public methods
public:
	Node* root;
	courseBinarySearchTree();
	void InOrder();
	void Insert(Course course);
	Course Search(string courseNum);
};

//BTS constructor
courseBinarySearchTree::courseBinarySearchTree() {

	//root equals nullptr
	root = nullptr;
}

// traverses through the tree
void courseBinarySearchTree::InOrder() {

	//calls inOrder 
	this->inOrder(root);
}

// Defines inOrder with node
void courseBinarySearchTree::inOrder(Node* node) {

	//if node does not equal nullptr
	if (node != nullptr) {

		//traverse left
		inOrder(node->left);

		//output the course
		cout << node->course.courseNumber << ", " << node->course.name << endl;

		//traverse right
		inOrder(node->right);
	}
}

//add the node
void courseBinarySearchTree::addNode(Node* node, Course course) {

	// add node to the left
	if (node->course.courseNumber.compare(course.courseNumber) > 0) {

		//if left node is null
		if (node->left == nullptr) {

			//left is new node
			node->left = new Node(course);
		}

		else {

			//traverse left
			this->addNode(node->left, course);
		}
	}

	else {

		//if is equal to null 
		if (node->right == nullptr) {

			//insert to the right
			node->right = new Node(course);
		}

		else {

			//traverse
			this->addNode(node->right, course);
		}
	}
}

// add course to BST
void courseBinarySearchTree::Insert(Course course) {

	//if root is null
	if (root == nullptr) {

		//root is new node
		root = new Node(course);
	}

	else {
		this->addNode(root, course);
	}
}

//splits vector
vector<string> splitString(string& line, char delimitor) {

	// temperary vector
	vector<string> tempVector;

	int begining = 0;
	int end = 0;

	// if no deliminator
	end = line.find(delimitor, begining);
	if (end < 0) {
		end = line.length();
	}

	// iterate through string
	while (begining < line.length() - 1) {

		// add temp vector
		tempVector.push_back(line.substr(begining, end - begining));

		begining = end + 1;

		end = line.find(delimitor, begining);
		if (end < 0) {
			end = line.length();
		}
	}

	return tempVector;
}

// load file
void loadCourses(string file, courseBinarySearchTree* courseBTS) {

	// string that hold a line in the file
	string newLine;

	// open fstream to read file
	ifstream fstreamfile;
	fstreamfile.open(file);


	// iterate through each line of the file
	while (getline(fstreamfile, newLine)) {
		vector<string> temp = splitString(newLine, ',');

		if (temp.size() < 2) {
			cout << "incorrect data" << endl;
			break;
		}

		Course course;
		course.courseNumber = temp.at(0);
		course.name = temp.at(1);

		//if a course has a prerequisite
		if (temp.size() == 3) {
			course.prerequisite1 = temp.at(2);
		}
		if (temp.size() == 4) {
			course.prerequisite1 = temp.at(2);
			course.prerequisite2 = temp.at(3);
		}

		// add the course to BST
		courseBTS->Insert(course);
	}

	//close file
	fstreamfile.close();
}

//Search tree
Course courseBinarySearchTree::Search(string courseNum) {

	//start at the root
	Node* current = root;

	//continue to loop until nullptr
	while (current != nullptr) {

		if (current->course.courseNumber.compare(courseNum) == 0) {
			return current->course;
		}

		//traverse left
		if (courseNum.compare(current->course.courseNumber) < 0) {
			current = current->left;
		}

		//traverse right
		else {
			current = current->right;
		}
	}

	// if nothing is found send a decoy course
	Course decoy;
	return decoy;
}

//print users course
void displayCourse(Course course) {
	cout << course.courseNumber << ": " << course.name << endl;

	//output prerequisites if a course has them
	if (course.prerequisite1 != "N/A") {
		cout << "Prerequisites: " << course.prerequisite1;
		if (course.prerequisite2 != "N/A") {
			cout << ", " << course.prerequisite2;
		}
		cout << endl;
	}
	cout << endl;
}

//main function
int main() {

	//initialize
	courseBinarySearchTree* courseTree;
	courseTree = new courseBinarySearchTree;
	Course course;
	string filePath;
	string courseKey;
	int choice = 0;

	//start up output
	cout << "Welcome to the course planner." << endl;
	cout << endl;

	//loop through the menu until user chooses 9
	while (choice != 9) {

		//display the menu
		cout << "1. Load Data Structure." << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course." << endl;
		cout << "9. Exit." << endl;
		cout << endl;
		cout << "What would you like to do?" << endl;

		//read user's choice
		cin >> choice;

		switch (choice) {

			//if user choice is 1
		case 1:			

			//reads the file
			filePath = "courseListFile.csv";

			// loads courses
			loadCourses(filePath, courseTree);
			cout << endl;

			//file not found
			if (courseTree->root == nullptr) {
				cout << "File didn't load" << endl;
				cout << endl;

			}

			//load good
			else {
				cout << filePath << " file loaded." << endl;
				cout << endl;
			}
			break;

			//if user choice is 2
		case 2:

			//file did not load
			if (courseTree->root == nullptr) {
				cout << endl;
				cout << "Please load courses and try again" << endl;
				cout << endl;
				break;
			}

			//list the courses
			else {
				cout << endl;
				cout << "Here is a sample schedule." << endl << endl;
				courseTree->InOrder();
				cout << endl;
			}
			break;

			//if user choice is 3
		case 3:

			//file did not load
			if (courseTree->root == nullptr) {
				cout << endl;
				cout << "Please load courses and try again" << endl;
				cout << endl;
				break;
			}
			//ask the use to choose a course
			cout << endl;
			cout << "What course would you like to know about?" << endl;
			cout << endl;
			cin >> courseKey;
			for (int i = 0; i < courseKey.size() - 1; ++i) {
				if (isalpha(courseKey[i])) {
					courseKey[i] = toupper(courseKey[i]);
				}
			}

			course = courseTree->Search(courseKey);

			//display courses
			if (course.courseNumber != "") {
				cout << endl;
				displayCourse(course);
				cout << endl;
			}

			// course not found
			else {
				cout << endl;
				cout << "Course not found, please try again." << endl;
				cout << endl;
			}

			break;

			//if user choice is 9
		case 9:
			cout << endl;
			cout << "Thank you for using course planner!" << endl << endl;
			break;

			//invaild choice
		default:
			cout << choice << " is not a valid option." << endl;
			cout << endl;
			cin.clear();
			cin.ignore(1000, '\n');

		}
	}
	return 0;
}
