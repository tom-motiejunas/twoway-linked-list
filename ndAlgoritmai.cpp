#include <iostream>
using namespace std;

struct node
{
	int data;
	node *next;	
	node *prev;
};

class linkedList
{
	private:
		node *head;
		node *tail;
	public:
		linkedList()  // constructor
			{
				head = NULL; 
				tail = NULL;
			}
			
		void addNodeEnd(int value)
		{
			node *temp = new node;
			temp->data = value;  
			temp->next = NULL;
			temp->prev=NULL;
			if(head == NULL)  
			{
				head = temp; 
				tail = temp;
			}
			else  // pridedam i gala
			{	
				temp->prev = tail;
				tail->next = temp;
				tail = temp;      
			}
			cout << "added new element" << endl;
		}
		
		void display()
		{
			node *temp = head;     		
			if(this->isEmpty()) {
				cout << "list is empty" << endl;
				return;
			}
			while(temp != NULL)
			{
				cout << temp->data << '\t'; // #tab
				temp = temp->next; 			
			}
			cout << endl;
		}
		void addNodeStart(int value)
		{
		// we use head to find first pos
			node *temp = new node;
			temp->data = value;
			temp->next = NULL;
			temp->prev = NULL;
			if(head == NULL) {
				head = temp;
				tail = temp;
			} else {	// add to front
				head->prev = temp;
				temp->next= head;
				head = temp;
			}
			cout << "added new element" << endl;
		}
		void addNodePos(int pos, int value)
		{
			if(pos < 1) {
				cout << "please choose position greater than 0" << endl;
				return;
			}
		// step 1 go to position where we want to add element
		node *temp = new node;
		temp->data = value;
		node *pre;
		node *cur = head;

		if(head == NULL && pos > 1) {
			cout << "error outside list boundaries" << endl;
			return;
		}
		else if((head == NULL) || pos == 1) {
			this->addNodeStart(value);
			return;
		}
		for(int i=1; i<pos; i++) {
			pre = cur;
			if(cur == tail && i+1 == pos) {
				this->addNodeEnd(value);
				return;
			}
			else if(cur == NULL) {
				cout << "error outside list boundaries" << endl;
				return;
			}
			cur = cur->next;
		}
		// step 2 add new element and adjust pointers
		temp->next = cur;
		temp->prev = pre;
		cur->prev = temp;
		pre->next = temp;
		}
		void deleteNodeStart()
		{
			if(head != NULL) {
			cout << "deleted element" << endl;
				if(head->next == NULL) {
					delete head;
					head = NULL;
					tail = NULL;
					return;
				}
				node *temp = head;
				head=head->next;
				head->prev = NULL;
				delete temp;
			}
			else {
				cout << "nothing to delete" << endl;
			}
		}
		void deleteNodeEnd() 
		{
			if(head != NULL) {
				cout << "deleted element" << endl;
				if(tail->prev==NULL) { //	if only one element left
					delete head;
					head = NULL; 
					tail = NULL;
					return;
				}
				node *temp = tail;
				tail=tail->prev;
				tail->next = NULL;
				delete temp;	
			}
			else {
				cout << "nothing to delete" << endl;
			}
		}
		void deleteNodePos(int pos)
		{
			if(pos < 1) {
				cout << "please choose position greater than 0" << endl;
				return;
			}
			node *pre = head;
			node *cur = head;
			if(head == NULL) {
				cout << "nothing to delete" << endl;
			}
			else {
				// travelling to position
				for(int i=1; i < pos; i++) {
					pre = cur;
					cur = cur->next;
					if(cur == NULL) {
						cout << "error outside list boundaries" << endl;
						return;
					}
				}
				if(cur == tail) {	// if we need to delete last element
					this->deleteNodeEnd();
				}
				else if (cur == head) {	// if we need to delete first element
					this->deleteNodeStart();
				}
				else {
					pre->next=cur->next;
					cur->next->prev=pre;
					delete cur;
				}
			}
		}
		void search(int value)
		{
			if(this->isEmpty()) {
				cout << "list is empty nothing to search for" << endl;
				return;
			}

			node *temp = head;    
			int i = 1;
			while(temp != NULL)
			{
				if(temp->data == value) {
					cout << "element position:" << i << endl; 
					return;
				}
				temp = temp->next; 
				i++;
			}
			cout << "element is not present in the list" << endl;
		}
		bool isEmpty() {
			return head == NULL ? true : false;
		}
		void reverse() {
			if(this->isEmpty()) {
				cout << "list is empty nothing to reverse" << endl;
				return;
			}
			int a;
			node *pre = NULL;
			node *cur = head;
			node *nxt = NULL;
			tail = head;

			while(cur != NULL) {	// if list is not empty	
			// step 1 save next element address
				nxt = cur->next;
			// step 2 swap current element pointers (next becomes previous, previous becomes next)
				cur->next = cur->prev;
				cur->prev = nxt;	
			// step 3 assign previous pointer to current
				pre = cur;
			// step 4 current becomes next
				cur = nxt;
			}
			head = pre;
			cout << "list has been reversed" << endl;
		}
		void clear() {
			node *temp = new node;
			while(head != tail) {
				temp = head;
				head = head->next;
				delete temp;
			}
			delete head;
			head = NULL;
			tail = NULL;
			cout << "list has been cleared" << endl;
		}
};
int main()
{
	linkedList listas;
	char option;
	string help = "a - add item to list; d - delete item from the list; s - search for item; e - check if list is empty; p - display list items; r - reverse list items; k - stop program";
	string otherHelp ="s - at the start; e - at the end; p - custom position";
	cout << help << endl;

	while (true)
	{
		cin >> option;
		switch (option)
		{
		case 'a':
			int value;
			cout << "enter value:";
			cin >> value;
			cout << "where to add value: " + otherHelp << endl;
			cin >> option;
			switch (option)
			{
			case 's':
				listas.addNodeStart(value);
				break;
			case 'e':
				listas.addNodeEnd(value);
				break;
			case 'p':
				int pos;
				cout << "enter position:";
				cin >> pos;
				listas.addNodePos(pos, value);
				break;
			default:
				cout << "unknown option" << endl;
				break;
			}
			break;
		case 'd':
			cout << "where to delete a value: " + otherHelp << endl;
			cin >> option;
			switch (option)
			{
			case 's':
				listas.deleteNodeStart();
				break;
			case 'e':
				listas.deleteNodeEnd();
				break;
			case 'p':
				int pos;
				cout << "enter position element which you want to delete" << endl;
				cin >> pos;
				listas.deleteNodePos(pos);
				break;
			default:
				cout << "unknown option" << endl;
				break;
			}
			break;
		case 's':
			int searchValue;
			cout << "enter value you searching for" << endl;
			cin >> searchValue;
			listas.search(searchValue);
			break;
		case 'e':
			if(listas.isEmpty()) {
				cout << "list is empty" << endl;
			} else {
				cout << "list is not empty" << endl;
			}
			break;
		case 'p':
			listas.display();
			break;
		case 'r':
			listas.reverse();
			break;
		case 'k':
			listas.clear();
			cout << "program shutting down" << endl;
			return 0;
			break;
		default:
			cout << "unknown option" << endl;
			break;
		}
	}
	return 0;
}
