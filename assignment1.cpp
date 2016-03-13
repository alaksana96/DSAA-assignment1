/*
 * assignment1.cpp
 *
 *  Created on: 12 Mar 2016
 *      Author: alaksana
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

typedef int Item;

struct Node{
	Item data; //data to be stored in the node
	Node* next; //pointer to the next node
};

typedef Node* NodePtr; //NodePtr is a pointer to a node

void addToListUnordered(Item number, NodePtr &hdList);
Item getFromList(NodePtr &hdList);
void printList(NodePtr hdList);
void addToListOrdered(Item number, NodePtr &hdList);
void deleteFromListOrdered(Item number, NodePtr &hdList);
void bubbleSort(NodePtr &hdList);
void readDataFile(int n, NodePtr &hdList);
void writeDataFile(int n, NodePtr &hdList);
void numberOfEvens(int n, NodePtr hdList);

int main(){

	cout << "Enter the name of the command file:" << endl;
	string file;
	cin >> file;
	ifstream comFile;
	comFile.open(file.c_str());

	if(!comFile.is_open()){
		cout << "Failed to open command file!" << endl;
		exit(EXIT_FAILURE);
	}

	//create list
	NodePtr head = NULL;

	string command;
	int dataFileNumber;

	bool sorted = false;

	comFile >> command;

	if(command == "r"){
		comFile >> command;
		dataFileNumber = atoi(command.c_str());
		readDataFile(dataFileNumber, head);
	}

	while(comFile >> command){

		if(command == "s"){
			bubbleSort(head);
			sorted = true;
		}
		else if(command == "w"){
			writeDataFile(dataFileNumber, head);
		}
		else if(command == "i"){
			comFile >> command;
			if(sorted){
				addToListOrdered(atoi(command.c_str()), head);
			} else {
				addToListUnordered(atoi(command.c_str()), head);
			}
		}
		else if(command == "d"){
			comFile >> command;
			deleteFromListOrdered(atoi(command.c_str()), head);
		}
		else if(command == "e"){
			numberOfEvens(dataFileNumber, head);
		}
	}


}

void addToListUnordered(Item number, NodePtr &hdList){
	NodePtr newNode = new Node; //creates a pointer to a new node
	newNode->data = number;
	newNode->next = hdList; //make this new node point to the beginning of the old list
	hdList = newNode; //make this new node the head of the list
}

void addToListOrdered(Item number, NodePtr &hdList){
	bool found = false;

	NodePtr newNode = new Node;
	newNode->data = number;
	newNode->next = NULL;

	if(hdList == NULL){
		hdList = newNode;
		return;
	}
	else if(number <= hdList->data){
		newNode->next = hdList;
		hdList = newNode;
	}
	else {
		found = false;
		NodePtr searchPtr, lastPtr;
		searchPtr = hdList;
		lastPtr = hdList;
		while((searchPtr != NULL) && !found){
			if(number <= searchPtr->data){
				found = true;
			} else {
				lastPtr = searchPtr;
				searchPtr = searchPtr->next;
			}
		}
		newNode->next = searchPtr;
		lastPtr->next = newNode;
	}
}

void deleteFromListOrdered(Item number, NodePtr &hdList){
	bool found = false;
	NodePtr oldPtr;

	if(hdList == NULL){
		//do nothing list is empty
	}
	else if(hdList->data == number){
		//only one element in the list, delete this item;
		oldPtr = hdList;
		hdList = hdList->next; //NULL
		delete oldPtr;
	}
	else {
		found = false;
		NodePtr searchPtr;
		searchPtr = hdList;
		oldPtr = hdList;

		while((searchPtr->next != NULL) && !found){

			if(searchPtr->data == number){
				found = true;
			}
			else {
				oldPtr = searchPtr;
				searchPtr = searchPtr->next;
			}
		}

		oldPtr->next = searchPtr->next;
		delete searchPtr;
	}
}

void bubbleSort(NodePtr &hdList){

	NodePtr current, trail, temp, currentHead = hdList;

	int count;
	while(currentHead != NULL){
		count++;
		currentHead = currentHead->next;
	}

	currentHead = hdList;

	for(int i = 0; i < count; i++){

		current = currentHead;
		trail = currentHead;

		while(current->next != NULL){

			if(current->data > current->next->data){

				temp = current->next;
				current->next = current->next->next;
				temp->next = current;

				if(current == currentHead){
					currentHead = temp;
					trail = temp;
				} else {
					trail->next = temp;
					current = temp;
				}
			}

			trail = current;
			current = current->next;
		}

	}
	hdList = currentHead;
}

void printList(NodePtr hdList){
	NodePtr tmp;
	tmp = hdList;
	while(tmp != NULL){
			cout << getFromList(tmp) << endl;
		}
}

void numberOfEvens(int n, NodePtr hdList){
	NodePtr tmp = hdList;
	int count;
	while(tmp != NULL){
		if( ((tmp->data) %2) == 0){ //is even
			count++;
		}
		tmp = tmp->next;
	}

	stringstream ss;
	ss << n;
	string filename = "output_" + ss.str() + ".txt";

	ofstream outFile;
	outFile.open(filename.c_str(), ios::app);

	if(!outFile.is_open()){
		cout << "Failed to open output file!" << endl;
		exit(EXIT_FAILURE);
	}

	stringstream pp;
	pp << count;

	outFile << "Number of even elements: " + pp.str() << endl;
}

Item getFromList(NodePtr &hdList){ //need to store the head of the list so we can still access the list
	int number;
	number = hdList->data;
	hdList = hdList->next; //moves to next node
	return Item(number);
}

void readDataFile(int n, NodePtr &hdList){

	stringstream ss;
	ss << n;
	string filename = "data_" + ss.str() + ".txt";

	ifstream inFile;
	inFile.open(filename.c_str());

	if(!inFile.is_open()){
		cout << "failed to open data file" << endl;
	}

	int m;

	while(inFile >> m){
		addToListUnordered(m, hdList);
	}

}

void writeDataFile(int n, NodePtr &hdList){

	stringstream ss;
	ss << n;
	string filename = "output_" +ss.str() + ".txt";

	ofstream outfile;
	outfile.open(filename.c_str(), ios::app); //append

	NodePtr tmp = hdList;

	while(tmp != NULL){
		outfile << tmp->data << endl;
		tmp = tmp->next;
	}


}
