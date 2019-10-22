//--------------------------------------------------------------------
//  Laboratory 9                                         database.cpp
/*!-------------------------------------------------------------------
	\file 
    \brief Testing database functionality 

	Builds a binary search tree index for the account records in the
	text file accounts.dat
*/
//--------------------------------------------------------------------

using namespace std;

#include "config.h"
#include "BSTree.h"

#include "BSTree.cpp"
#include "show9.cpp"

void print_help();

//--------------------------------------------------------------------
//
// Declarations specifying the accounts database
//
//--------------------------------------------------------------------

///Data that gets stored into the array
/*! 
		Where the user data is stored.
		
		Each node has an a unique key which is the acctID and a 
		recNum which is how each individual is stored into the 
		array for the database.
		
*/
struct AccountRecord
{
	/// Account identifier
	int acctID;
	/// First name of the account holder
	string firstName,	
	/// Last name of the account holder
		lastName;
	/// Account balance
	double balance;

	///Default constructor
	AccountRecord() {}
	
	/// Constructor for AccountRecord 
	/*! 
		Reads from accounts.dat to assign each individual
		person the correct information. Then it stored into 
		an array with a corresponding reference number.
		
		@param acctID : Passed in reference number
		@param first : Passed in first name 
		@param last : Passed in last name
		@param bal : Passed in balance for their account
	*/ 
	AccountRecord(int acctID, string first, string last, double bal) {
		this->acctID = acctID;
		this->firstName = first;
		this->lastName = last;
		this->balance = bal;
	}
};

//--------------------------------------------------------------------
//
// Declaration specifying the database index
//
//--------------------------------------------------------------------

/// Nodes of binary search tree for the database
/*! 
		This class is used as the indecies to the database.
		
		Each node has an a unique key which is the acctID and a 
		recNum which is how each individual is stored into the 
		array for the database.
		
*/ 
struct IndexEntry
{
	/// (Key) Account identifier
	int acctID;  
	/// Record number used to access the array.
	long recNum;             

	/// Sets the variables of the node
	/*! 
		@param recNum : Passed in reference number
		@param acctID : Passed in unique key
	*/ 
	void setKey(long recNum, int acctID) {
		this->acctID = acctID;
		this->recNum = recNum;
	} // Set the initial data

	///Return unique key acctID
	int getKey() const
	{
		return acctID;
	}   // Return key field

	///Return record number
	int getRecNum() const
	{
		return recNum;
	}   // Return key field
};

//--------------------------------------------------------------------

int main()
{
	ifstream file_cin;
	string FileIn = "accounts.dat";   // Accounts database file
	AccountRecord acctRec;                // Account record
	BSTree<IndexEntry, int> index;         // Database index
	IndexEntry entry;                     // Index entry
	vector<AccountRecord> indicies;       // Array of records from database
	string temp;
	int searchID;                         // User input account ID
	long recNum;                          // Record number
	char cmd;                        // Input command

	// Iterate through the database records. For each record, read the
	// account ID and add the (account ID, record number) pair to the
	// index.

	//Open the file
	file_cin.open(FileIn);
	//See if file manipulators are open
	if (!file_cin.is_open())
	{
		cout << "\nCannot open File" << endl;
		system("pause");
		exit(0);
	}

	//Clear header line
	getline(file_cin, temp);
	while (file_cin.good())
	{
		long recNum;                  // Record number
		int acctID;                   // Account identifier
		string firstName,   // Name of account holder
			lastName;
		double balance;

		file_cin >> recNum >> acctID >> firstName >> lastName >> balance;

		IndexEntry dbNode;
		dbNode.setKey(recNum, acctID);
		index.insert(dbNode);

		AccountRecord userData(acctID, firstName, lastName, balance);
		indicies.push_back(userData);
	}

	// Clear the status flags for the database file.

	file_cin.clear();

	// Read an account ID from the keyboard and output the
	// corresponding record.

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	print_help();

	// Output the account IDs in ascending order.
	cout << "Keys in ascending order." << endl;
	index.writeKeys();
	cout << endl;

	do
	{
		index.showStructure();                     // Output tree

		cout << endl << "Command: ";               // Read command
		cin >> cmd;
		if (cmd == '+' || cmd == '?' ||
			cmd == '-' || cmd == '<')
			cin >> searchID;

		switch (cmd)
		{
		case 'P': case 'p':
			print_help();
			break;

		case '?':                                  // retrieve
			if (index.retrieve(searchID, entry)) {
				cout << "Retrieved : getKey = "
					<< entry.getKey() << endl;
				cout << "User data" << endl
					<< "First name: " << indicies[entry.getRecNum()].firstName << endl
					<< "Last Name: " << indicies[entry.getRecNum()].lastName << endl
					<< "Balance: $" << indicies[entry.getRecNum()].balance << endl;
			}

			else
				cout << "Not found" << endl;
			break;

		case '-':                                  // remove
			if (index.remove(searchID))
				cout << "Removed data item" << endl;
			else
				cout << "Not found" << endl;
			break;

		case 'K': case 'k':                       // writeKeys
			cout << "Keys:" << endl;
			index.writeKeys();
			break;

		case 'C': case 'c':                       // clear
			cout << "Clear the tree" << endl;
			index.clear();
			break;

		case 'E': case 'e':                       // empty
			if (index.isEmpty())
				cout << "Tree is empty" << endl;
			else
				cout << "Tree is NOT empty" << endl;
			break;

#if   LAB9_TEST1
		case 'G': case 'g':                   // Programming Exercise 2
			cout << "Tree nodes count = " << index.getCount() << endl;
			break;
#endif	// LAB9_TEST1

#if   LAB9_TEST2
		case 'H': case 'h':                   // Programming Exercise 2
			cout << "Tree height = " << index.getHeight() << endl;
			break;
#endif	// LAB9_TEST2

#if   LAB9_TEST3
		case '<':                              // Programming Exercise 3
			cout << "Keys < " << searchID << " : " << endl;
			index.writeLessThan(searchID);
			cout << endl;
			break;
#endif	// LAB9_TEST3

		case 'Q': case 'q':                   // Quit test program
			break;

		default:                               // Invalid command
			cout << "Inactive or invalid command. 'P' prints help." << endl;
		}
	} while (cin && (cmd != 'Q') && (cmd != 'q'));

	return 0;
}

void print_help() {
	cout << endl << "Commands:" << endl;
	cout << "  P    : [P]rint Help (displays this message)" << endl;
	cout << "  +key : Insert (or update) data item (use integers)" << endl;
	cout << "  ?key : Retrieve data item" << endl;
	cout << "  -key : Remove data item" << endl;
	cout << "  K    : Write keys in ascending order" << endl;
	cout << "  C    : Clear the tree" << endl;
	cout << "  E    : Empty tree?" << endl;
	cout << "  G    : Get count of nodes          "
#if LAB9_TEST1
		<< "(Active   : "
#else
		<< "(Inactive : "
#endif
		<< "In-lab Exercise 2)" << endl;

	cout << "  H    : Height                      "
#if LAB9_TEST2
		<< "(Active   : "
#else
		<< "(Inactive : "
#endif
		<< "In-lab Exercise 2)" << endl;

	cout << "  <key : Write keys that are < key   "
#if LAB9_TEST3
		<< "(Active   : "
#else
		<< "(Inactive : "
#endif
		<< "In-lab Exercise 3)" << endl;
	cout << "  Q    : Quit the test program" << endl;
	cout << endl;
}