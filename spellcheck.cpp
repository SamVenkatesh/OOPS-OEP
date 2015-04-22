/*
 * @Author:Shyam Venkatesh. 
 * This project is hosted at https://github.com/vsamster/OOPS-OEP
 * Performs a spell check implemented in C++.
 */

#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<string>
using namespace std;


int LevenshteinDistance(string s,int s_len, string t,int t_len)
{
 
  int d[s_len][t_len];
 
  for(int i=0;i<s_len;i++)
  {
	for(int j=0;j<t_len;j++)
	{
		d[i][j]=0;
	}
  }
 
  // source prefixes can be transformed into empty string by
  // dropping all characters
  for(int i=0;i<s_len;i++)
      d[i][0] = i;
 
  // target prefixes can be reached from empty source prefix
  // by inserting every character
  for(int j=0;j<t_len;j++)
      d[0][j] = j;
  int i,j;
  for(j=1;j<t_len;j++)
  {
      for(i=1;i<s_len;i++)
      {
          if(s[i] == t[j])
            d[i][j] = d[i-1][j-1];              // no operation required
        else
	    {
		  int a=d[i-1][j] + 1;
		  int b=d[i][j-1] + 1;
		  int c=d[i-1][j-1] + 1;
		  d[i][j]= (a<b) ? ((a<c)? a: c) : ((b<c)? b: c);
 	    }
	  }
    }
  return d[s_len-1][t_len-1];
}

class SpellCheck
{
	vector <string> Dictionary;
	
    public:
	SpellCheck()
	{
		//Import the words from the file and push_back into the vector.	
		ifstream fin("american-english.txt");
		if(!fin)
		{
			cout<<"Error opening input file.\n";
			exit(-1);			
		}
		while(!fin.eof())
		{
			string iWord;
			fin>>iWord;
			Dictionary.push_back(iWord);
		}
	}
	int exit(int i)
	{
		return i;
	}
	//Check whether the given word from the text file is present in the dictionary or not and return bool value
	int Check_ifPresent(string word)
	{
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);
		if(std::find(Dictionary.begin(),Dictionary.end(),word)!=Dictionary.end())
			return 1;
		else
			return 0;
	}

	/*Uses an iterator i across the Dictionary vector and applies the Distance forumla between each word in the dictionary 
	  and the word from the text file being checked. If the edit distance is found to be less than or equal to 1 the word 
	  is considered a valid alternative and is displayed as such. */
	void Check_eDistance(string word)
	{
		vector <string>::iterator i;
		for(i=Dictionary.begin();i!=Dictionary.end();i++)
		{
			string dWord;
			dWord=*i;
			int eDist=LevenshteinDistance(word,word.length(),dWord,dWord.length());
			if(eDist<=2)
			{	
				cout<<dWord<<" ";
			}
		}
	
	}	
	
};

/*Takes the name of the file to be checked from the user and opens an input stream fin for it. Each word is read from the
  file and the Dictionary is checked to see if the word is present i.e a valid word or not. If found, the next word is read
  and if not the word is passed to the Check_eDistance function to generate alternatives.
*/


int main()
{
	SpellCheck S;
	string input_word;
	int f=1;
	cout<<"Enter a File name\n";
	
	string fname;
	cin>>fname;
	ifstream fin;
	fin.open(fname.c_str());
	
	if(!fin)
	{
		cout<<"Unable to open file\n";
		return -1;
	}
	while(true)	
	{
		fin>>input_word;
		if(fin.eof()) break;
		if(!S.Check_ifPresent(input_word))
		{	
			f=0;
			cout<<"Incorrect word  "<<input_word<<"\n\nAlternatives: ";
			S.Check_eDistance(input_word);
			cout<<endl<<endl;
		}
	}
	if(f)
	{
		cout<<"No errors found\n";
	}
	return 0;
}







