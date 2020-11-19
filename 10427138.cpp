//
//
//                           10427138 葉士瑋 SP 第二次實作 
//
//
//
//

#include <iostream>                                                        
#include <stdio.h>
#include <fstream>                                                          
#include <string>                                                           
#include <string.h> 
#include <vector>                                                           
#include <cstdlib>                                                       
#include <iomanip>                                                      
#include <cstring>                                                      	
#include <stdlib.h>

using namespace std;


typedef struct TT	              // token list (all token & enter)
{	
	string	        toto;         // a token 
	int 	        tablee;       // table num
	int             loca ;        // the location of tabel
	                
}	TokenType;

typedef struct cList											           
{	
	int 	        posInVector;    // pos. in token list
	                
}	createList;

typedef struct TC											           
{	
	int 	        arrayNum;                                     	 
	string          tokenName ; 
	
}	tableContent;

vector<TokenType> cSet ;      //////////////  全域的list, 擁有所有token /////////////
vector<createList> creatSet ; ///////// 擁有要放入5. 6. 7.的token的位置 ///////////// 

tableContent table5[100] ;    // 5  symbol
tableContent table6[100] ;    // 6  integer
tableContent table7[100] ;    // 7  string

string outName ; 
int commentEnd, commentStart ; 

int FindNStore( int ch, bool isSame ) {  // if true, put the char in the same slot  // return size of the whole list
	
	if( cSet.size() == 0 ) {  // first time enter 
		TokenType te ; 
		te.toto = "" ; 
		te.toto.push_back(((char)ch)) ;
		te.loca = 0 ; 
		te.tablee = 0 ; 
		 
		cSet.push_back(te) ; 
		
	} // if
	else {
	
	
		if (isSame) {                                        // put a new char in a same slot
			string temp ; 
		
			temp = cSet.at( cSet.size()-1 ).toto ; 
		
			temp.push_back(((char)ch)) ; 
		
			cSet.at( cSet.size()-1 ).toto = temp ; 
		
		
		} // if 
		else {                                          // create a new slot
			TokenType te ; 
			te.toto = "" ; 
			te.toto.push_back(((char)ch)) ;
			te.loca = 0 ; 
			te.tablee = 0 ; 
		 
			cSet.push_back(te) ; 
		
		
		} // else 
	
	} // else 
	return cSet.size() ; 
	
} // end FindNStore()

bool readRecords(vector<TokenType> &cSet)         // read records from a file
{   FILE*       inFile;                            // input file handle
    string      fileName ;
    cout << "Input the file name: (NOTE : PLZ INCLUDE Filename Extension! ex: .txt)" << endl  ;
    cin >> fileName ;
	char* file2 ;
	file2 = (char *)malloc(fileName.size() + 1);
	memcpy(file2, fileName.c_str(), fileName.size()+1);
    int o = 0 ; //test
    bool engTok = false ; 
    inFile = fopen(file2, "r");      // open file to read
    if (inFile == NULL ) {                        // unable to open file
        cout << endl << "### " << fileName << " does not exist! ###" << endl;
        exit(0) ;
    } // if
    else {
    	outName = fileName ; 
    	int ch ;
    	char a = '\0'; 
    	ch = fgetc(inFile) ; 
    	
        while ( ch != EOF ) {
        	
        	
        	while ( ch != EOF && ((char)ch) != ' ' && ((char)ch) != '\t' && ((char)ch) != '\n') {
        		
				//engTok = false ; 
        		if( ch == 39 ) {    // be ready to read a string  39 = ' 
				 	FindNStore(ch, false) ;
				 	ch = fgetc(inFile) ; 
				 	bool same = false ; 
				 	
				 	while ( ch != 39 ) {
				 		FindNStore(ch, same) ;
				 		same = true ;
				 		ch = fgetc(inFile) ; 
					 } // while 
				 
				     FindNStore(ch, false) ;
				 
				} else if ( (ch >= 65 && ch <= 90 ) || (ch >= 97 && ch <= 122 )){
					                           // if read in a eng char A~Z a~z
					FindNStore(ch, engTok) ;
					engTok = true ; 
	
				} else if( ch >= 48 && ch <= 57 ){
					FindNStore(ch, engTok) ;   // number
					engTok = true ; 
				} else {
					engTok = false ; 
					FindNStore(ch, engTok) ;   // other char
				} // end elseif 
        		
        		ch = fgetc(inFile) ; 
        		// cout << (char)ch << endl ;  // test 
			} // end inner while ( ((char)ch) != ' ' && ((char)ch) != '\t' && ((char)ch) != '\n')
			
			engTok = false ; 
			
			if( ((char)ch) == '\n' ) {
				FindNStore(ch, false) ;
			} // line enter 
			
			
			cout << o << endl ; // test 
			o++ ; 
			ch = fgetc(inFile) ; 
		} // end otter while 
		


    	fclose(inFile);                             // close file
    	
		if (!cSet.size()) {
    		cout << endl << "### Get nothing from the file " << fileName << " ! ### " << endl;
		} // if 
	} // else
}   // end readRecords

/////////////////////////////////////////////////////////////////////////////////////////////////////// 

void introMsg(void)                                                         // initiate an opening message
{   cout << "*******************************************************" << endl;
    cout << "*                                                     *" << endl;
    cout << "*                 SP PRACTICE 2                       *" << endl;
    cout << "*                                                     *" << endl;
    cout << "*******************************************************" << endl;
}   // end introMsg

///////////////////////////////////////////////////////////////////////////////////////////////////////

bool readTable( int tableNum, int cur, vector<TokenType> &cSet )        // read records from a file // if find return the num of the locate , if not,  return -1 
{   fstream     inFile;                            // input file handle
    string      fileName = "" ;
    
    if( tableNum == 1  ) {
    	fileName = "Table1.table" ; 
	} else if( tableNum == 2 ) {
		fileName = "Table2.table" ; 
	} else if( tableNum == 3 ) {
		fileName = "Table3.table" ; 
	} else { // tableNum == 4 
		fileName = "Table4.table" ; 
	} // else 
    
    string      coName, depName, stLevel;
    char        rBuf[255];                       // input buffer for one line
    char      trash[255] ;
    
    inFile.open(fileName.c_str(), fstream::in);      // open file to read
    if (!inFile.is_open()) {                        // unable to open file
        cout << endl << "### " << fileName << " does not exist! ###" << endl;
        exit(0) ;
    } // if
    else {
    	int count = 1 ; // 算座標 
        while (inFile.getline(rBuf, 255, '\n'))  // get each input record line by line
        {   if( commentStart != -1 ) {
        		cSet.at(cur).tablee = 0 ; 
        		cSet.at(cur).loca = 0 ; 
        		return true ; 
			} // if 
			string      temp;             // transform the c-string of input record
            temp.assign(rBuf);           // copy string as a c-string
            // cout << temp << endl ; // test 
        	if( temp.at(temp.length()-1) == '\n' ) { // there is a  line enter 
        		commentStart = -1 ; 
        		temp = temp.substr (0,temp.length()-1);
        		//cout << temp << endl ;  // test 
        		const char * x = cSet.at(cur).toto.c_str();
        		const char * y = temp.c_str();
        		if ( strcmpi(x, y) == 0 ) {
        			//cout << temp << endl ;  // test 
        			cSet.at(cur).tablee = tableNum ; 
        			cSet.at(cur).loca = count ; 
        			//cout << cSet.at(cur).tablee << " " << cSet.at(cur).loca << endl ; // test 
        			return true ; 	
				} // if 
			} else { // there is no line enter at the end  
				const char * x = cSet.at(cur).toto.c_str();
        		const char * y = temp.c_str();
        		// cout << temp << endl ;  // test 
				if ( strcmpi(x, y) == 0 ) {
					//cout << temp << endl ;  // test 
        			cSet.at(cur).tablee = tableNum ; 
        			cSet.at(cur).loca = count ; 
        			// cout << cSet.at(cur).tablee << " " << cSet.at(cur).loca << endl ; // test 
        			if( cSet.at(cur).toto.compare(".") == 0 ) {
        				commentStart = cur ; 
					} // if 
        			return true ; 	
				} // if 
			} // else 
			
			count++ ; // 算座標 
        }   //end while
    inFile.close();                             // close file
    
    return false ; 
} // else
}   // end readTable

//-----------------------------------------------------------------------

void createATable1( int a, bool gonnaPutItIn, vector<TokenType> &cSet ) // put the cur into create list
{ 
    if( gonnaPutItIn == false ) { // 還沒要開始分類table 
    	createList temp ; 
			temp.posInVector = a ; 
			creatSet.push_back(temp) ; 		
	} // if 
	else if( gonnaPutItIn == true ) { // 開始分類table 
	
		for( int a = 0 ; a < creatSet.size() ; a ++ ) { // classify the tokens one by one
		    // cout << creatSet.at(a).posInVector << endl ;  // test
			int cur = creatSet.at(a).posInVector ;
			// cout << cSet.at(cur).toto << endl ; // test
			int Sum = 0 ;
			if( cSet.at(cur).toto.compare("\n") == 0 ) {
				// do nothing 
			} // if 
			else if( cSet.at(cur).toto.compare(".") == 0) {
				
			} // else if 
			else if( (cur > 1 && (cur+1)< cSet.size() ) && cSet.at(cur-1).toto.compare("'") == 0 && cSet.at(cur+1).toto.compare("'") == 0 ) {
			
				// 判斷此token是string  // table 7 
				Sum = 0 ; 
				if( cur > 2 && (cSet.at(cur-2).toto.compare("X") == 0 || cSet.at(cur-2).toto.compare("x") == 0 ) ) {   
				// X'F1' 
					cSet.at(cur-2).tablee = 0 ; 
					cSet.at(cur-2).loca = 0 ;
					cSet.at(cur).tablee = 6 ;  // 16進位數字   // table 6
					for( int f = 0 ; f < cSet.at(cur).toto.length() ; ++f ) {
						Sum = Sum + cSet.at(cur).toto.at(f) ; // 把 ASCII 相加 
					} // for 
					
					Sum = Sum % 100 ; 
					while ( Sum < 100 ) { // put in array 
						if( table6[Sum].tokenName.compare( "" ) != 0 && table6[Sum].tokenName.compare( cSet.at(cur).toto ) == 0 ) {
							cSet.at(cur).loca = Sum ; 
							break ; 
						} // if 
						else if( table6[Sum].tokenName.compare( "" ) == 0 ) {
							table6[Sum].tokenName = cSet.at(cur).toto ; 
							cSet.at(cur).loca = Sum ; 
							break ; 
						} //else  if
						
						Sum++ ; 
						
					} // while 
				 
				 	// cout << Sum << endl ; // test 
					if( Sum == 100 ) {
						cout << "Cant define code " << cSet.at(cur).toto << "to any table." << endl ; 
					} // if 
				} else {
					if( cur > 2 && (cSet.at(cur-2).toto.compare("C") == 0 || cSet.at(cur-2).toto.compare("c") == 0 ) ) {
					// C'EOF'
						cSet.at(cur-2).tablee = 0 ; 
						cSet.at(cur-2).loca = 0 ;	
					} // if 
					
					cSet.at(cur).tablee = 7 ; 
					Sum = 0 ;
					for( int f = 0 ; f < cSet.at(cur).toto.length() ; ++f ) {
						Sum = Sum + cSet.at(cur).toto.at(f) ; // 把 ASCII 相加 
					} // for 
					
					Sum = Sum % 100 ; 
					
					while ( Sum < 100 ) { // put in array 
						if( table7[Sum].tokenName.compare( "" ) != 0 && table7[Sum].tokenName.compare( cSet.at(cur).toto ) == 0 ) {
							cSet.at(cur).loca = Sum ;
							break ; 
						} // if 
						else if( table7[Sum].tokenName.compare( "" ) == 0 ) {
							table7[Sum].tokenName = cSet.at(cur).toto ; 
							cSet.at(cur).loca = Sum ; 
							break ; 
						} //else  if
						
						Sum++ ; 
						
					} // while 
				 
				 	//cout << Sum << endl ; // test 
					if( Sum == 100 ) {
						cout << "Cant define code " << cSet.at(cur).toto << "to any table." << endl ; 
					} // if 
				} // else 
			} // else if
			else if( ( cSet.at(cur).toto.at(0) >= 48 ) && ( cSet.at(cur).toto.at(0) <= 57 ) ) {   
			// 判斷此token是integer  // table 6
			
				cSet.at(cur).tablee = 6 ; 
				Sum = 0 ;
				for( int f = 0 ; f < cSet.at(cur).toto.length() ; ++f ) {
					Sum = Sum + cSet.at(cur).toto.at(f) ; // 把 ASCII 相加 
				} // for 
				
				Sum = Sum % 100 ; 
				
				while ( Sum < 100 ) { // put in array 
					if( table6[Sum].tokenName.compare( "" ) != 0 && table6[Sum].tokenName.compare( cSet.at(cur).toto ) == 0 ) {
						cSet.at(cur).loca = Sum ; 
						break ; 
					} // if 
					else if( table6[Sum].tokenName.compare( "" ) == 0 ) {
						table6[Sum].tokenName = cSet.at(cur).toto ; 
						cSet.at(cur).loca = Sum ; 
						break ; 
					} //else if
						
					Sum++ ; 
						
				} // while 
				 
				// cout << Sum << endl ; // test 
				if( Sum == 100 ) {
					cout << "Cant define code " << cSet.at(cur).toto << "to any table." << endl ; 
				} // if 
				
			} // else if
			else if ( (cSet.at(cur).toto.at(0) >= 65 && cSet.at(cur).toto.at(0) <= 90 ) || (cSet.at(cur).toto.at(0) >= 97 && cSet.at(cur).toto.at(0) <= 122 ) ) {  
			// 判斷此token是symbol  // table 5
				cSet.at(cur).tablee = 5 ; 
				Sum = 0 ;
				for( int f = 0 ; f < cSet.at(cur).toto.length() ; ++f ) {
					Sum = Sum + cSet.at(cur).toto.at(f) ; // 把 ASCII 相加 
				} // for 
				
				Sum = Sum % 100 ; 
				while ( Sum < 100 ) { // put in array 
					if( table5[Sum].tokenName.compare( "" ) != 0 && table5[Sum].tokenName.compare( cSet.at(cur).toto ) == 0 ) {
						cSet.at(cur).loca = Sum ; 
						break ; 
					} // if 
					else if( table5[Sum].tokenName.compare( "" ) == 0 ) {
						table5[Sum].tokenName = cSet.at(cur).toto ; 
						cSet.at(cur).loca = Sum ; 
						break ; 
					} // else if
						
					Sum++ ; 
						
				} // while 
				 
				//cout << Sum << endl ; // test 
				if( Sum == 100 ) {
					cout << "Cant define code " << cSet.at(cur).toto << "to any table." << endl ; 
				} // if 
			} // else if 
			else {
				cout << "Cant define code " << cSet.at(cur).toto << "to any table." << endl ; 
			} // else 
			
		} // for 
		
	} // else if

	
	
} // end createATable1

//----------------------------------------------------------------------

void createATable2( ) // write a table file 
{ 

} // end createATable2


//////////////////////////////////////////////////////////////////////////////////////////// 

void putAllRecords( vector<TokenType> &cSet)  {	// show the entire set of records on the screen of vector
    int z = 0 ;            // for last record 
	for ( int a = 0 ; a < cSet.size() ; a++ )
 	{	
 		 cout << cSet.at(a).toto << "(" << cSet.at(a).tablee << "," << cSet.at(a).loca << ")" << "\t" ; 
    }   //end for
    
}   // end putAllRecords

void writeRecords() // output all into a file (原始程式碼 + 座標)
{ 
 int j = 0;
 fstream outFile; // output file handle
 fstream inFile ; // input source code 
 string infname = outName ; 
 string fname = "(output)" + outName ; // output file name
 inFile.open(infname.c_str(), fstream::in); // file to read
 outFile.open(fname.c_str(), fstream::out); // create a new file to write
 if (!outFile.is_open()) {      // if  unable to create a file
 	cout << endl << "### Cannot create " << fname << " ! ###" << endl;
 	return;
 } //end if
 
 int count = 0 ; 
 bool outt = false ; 
 char rBuf[255];     // input buffer for one line
 while ( inFile.getline(rBuf, 255, '\n') ) {
 	outFile << rBuf << endl ; // output a line of source code 
 	for( ; count < cSet.size() && !outt ; count++ ) {
 		if( cSet.at(count).toto.compare("\n") == 0 ) {
 			outt = true ; 
		} // if 
		 
		 if( cSet.at(count).tablee != 0 ) {
		 	outFile << "(" << cSet.at(count).tablee << "," << cSet.at(count).loca << ") " ;
		 } // if 
 		
	 } // for 
	 
	 outFile << endl ; 
	 outt = false ; 
 } // while 
 
 
 inFile.close() ; 
 outFile.close(); // close output file
 
} // end writeRecords


//////////////////////////////////////////////////////////////////////////////////////////
void FindOPcode() {
	
} // end FindOPcode

void MCode( vector<TokenType> &cSet ) {  
/*
    typedef struct TT	              // token list (all token & enter)
	{	
		string	        toto;         // a token 
		int 	        tablee;       // table num
		int             loca ;        // the location of tabel              
	}	TokenType;
*/

// 5  symbol
// 6  integer
// 7  string
	int cur = 0 ; 
//	int 
    
	if( cSet.at(cur).tablee == 1) {  // first encounter 
		
	} else if( cSet.at(cur).tablee == 2 ) {
		
	} else if( cSet.at(cur).tablee == 3 ) {
		
	} else if( cSet.at(cur).tablee == 4 ) {
		
	} else if( cSet.at(cur).tablee == 5 ) {
		
	} else if( cSet.at(cur).tablee == 6 ) {
		
	} else if( cSet.at(cur).tablee == 7 ) {
		
	}  // end if else
	
	
} // end MCode


int main(void)
{   introMsg() ; 
	
	readRecords(cSet) ; 
	commentEnd = -1 ; 
	commentStart = -1 ; 
	/*
	for ( int a = 0 ; a < cSet.size() ; a++ ) {
		cout << cSet.at(a).toto << endl ; 
	} // for test 
	*/
	
	for( int a = 0 ; a < cSet.size() ; a++) { // dig in the table to locate all the pos.
		
		if( cSet.at(a).toto.compare("\n") == 0 ) {
			cSet.at(a).tablee = 0 ; 
			cSet.at(a).loca = 0 ; 
			commentStart = -1 ; 
		} else if( readTable( 1, a, cSet ) ) {
			
		} else if( readTable( 2, a, cSet ) ) {
			 
		} else if( readTable( 3, a, cSet ) ) {
			
		} else if( readTable( 4, a, cSet ) ) {
			
		} else {
			// create a table 
			createATable1(a, false, cSet) ; // 還沒開始分類table
		} // else 
		
		
	} // for 
	

    for ( int z = 0 ; z < 100 ; z++ ) { // 先把table array 洗乾淨 
    	table5[z].arrayNum = z ; 
    	table5[z].tokenName = "" ; 
    	table6[z].arrayNum = z ; 
    	table6[z].tokenName = "" ;
    	table7[z].arrayNum = z ; 
    	table7[z].tokenName = "" ;
	} // for 
	
	createATable1( 0, true, cSet) ; // 開始分類table 
	writeRecords() ;   // 寫檔 原始程式碼 
    //putAllRecords( cSet ) ; // test 
	// createATable2() ; // 把分好的table寫檔
	
    cout << endl << endl << "Thx for using !!" << endl << endl ;
    cSet.clear() ; 
    creatSet.clear() ; 
    commentEnd = -1 ; 
	commentStart = -1 ;
	for ( int z = 0 ; z < 100 ; z++ ) { // 先把table array 洗乾淨 
    	table5[z].arrayNum = z ; 
    	table5[z].tokenName = "" ; 
    	table6[z].arrayNum = z ; 
    	table6[z].tokenName = "" ;
    	table7[z].arrayNum = z ; 
    	table7[z].tokenName = "" ;
	} // for 
	exit(0) ;  
}	// end main
