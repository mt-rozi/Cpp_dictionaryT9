/*
	Autor: Mateusz Rozmus mt.rozmus@wp.pl
*/

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <fstream>

#define numberOfLetters 26

using namespace std;

ifstream file("dane.txt");

typedef string elementtype;

struct node{
	char number;
	bool endOfWord;
	struct node* children[numberOfLetters];
};

typedef node* position;

class Tree{

	protected:
			position head;
	public:

	Tree(){
		head=new node();
		head->endOfWord=false;
	}

	~Tree(){
		cout << "Czyszczenie pamieci..." << endl;
		DeleteNode(head);
		cout << "Zakonczone pomyslnie" << endl;
	}

	void Insert(elementtype word)
	{
		position p=head;

		for(int i=0;i<word.length();i++)
		{
			int letter=(int)word[i]-(int)'a';
			if(p->children[letter]==NULL)
			{
				p->children[letter]=new node();
				p->children[letter]->number=NumberLetter(word[i]);
			}
			p=p->children[letter];
		}
		p->endOfWord=true;
	}

	void DeleteWord(elementtype word)
	{
		node *n=head;
		int size;

		for(int i=0;i<word.length();i++)
		{
			size=(int)word[i]-(int)'a';
			if(n->children[size]==NULL)
			{
				cout << "Nie mozna usunac takiego wyrazu. Taki wyraz nie istnieje." << endl;
				return;
			}
			n=n->children[size];
		}
		if(n->endOfWord) n->endOfWord=false;
		cout << "Wyraz '" << word << "' zostal pomyslnie usuniety." << endl; 
	}

	bool SearchWord(elementtype word)
	{
		node *n=head;
		int size;

		for(int i=0;i<word.length();i++)
		{
			size=(int)word[i]-(int)'a';
			if(n->children[size]==NULL) return false;
			n=n->children[size];
		}
		if(n->endOfWord) return true;
		return false;
	}

	void SearchNumberWord(elementtype word)
	{
		node *n=head;

		SearchNumberWordIf(word,"",n,0);
	}

	private:

	void DeleteNode(position p)
	{
		for(int i=0;i<numberOfLetters;i++)
			if(p->children[i]!=NULL) DeleteNode(p->children[i]);
		delete p;
	}

	void SearchNumberWordIf(elementtype word, elementtype result, position n, int i)
	{
		if(word[i]=='2')
			for( int k=0; k<3; k++)
				if(n->children[k]!=NULL) SearchNumberWordContinue(word,result,n->children[k],i,k);
		if(word[i]=='3')
			for( int k=3; k<6; k++)
				if(n->children[k]!=NULL) SearchNumberWordContinue(word,result,n->children[k],i,k);
		if(word[i]=='4')
			for( int k=6; k<9; k++)
				if(n->children[k]!=NULL) SearchNumberWordContinue(word,result,n->children[k],i,k);
		if(word[i]=='5')
			for( int k=9; k<12; k++)
				if(n->children[k]!=NULL) SearchNumberWordContinue(word,result,n->children[k],i,k);
		if(word[i]=='6')
			for( int k=12; k<15; k++)
				if(n->children[k]!=NULL) SearchNumberWordContinue(word,result,n->children[k],i,k);
		if(word[i]=='7')
			for( int k=15; k<19; k++)
				if(n->children[k]!=NULL) SearchNumberWordContinue(word,result,n->children[k],i,k);
		if(word[i]=='8')
			for( int k=19; k<22; k++)
				if(n->children[k]!=NULL) SearchNumberWordContinue(word,result,n->children[k],i,k);
		if(word[i]=='9')
			for( int k=22; k<26; k++)
				if(n->children[k]!=NULL) SearchNumberWordContinue(word,result,n->children[k],i,k);		
	}

	void SearchNumberWordContinue(elementtype word, elementtype result, position n, int i, int j)
	{
		int size = word.length()-1;

		if(n->number==word[i])
		{
			result+=(char)(j+(int)'a');
			if(n->endOfWord && i==size) cout << result << ", ";
			if(i<=size)
				SearchNumberWordIf(word,result,n,i+1);
		}
	}

	char NumberLetter(char letter)
	{
		if(letter=='a'||letter=='b'||letter=='c') return '2';
		else if(letter=='d'||letter=='e'||letter=='f') return '3';
		else if(letter=='g'||letter=='h'||letter=='i') return '4';
		else if(letter=='j'||letter=='k'||letter=='l') return '5';
		else if(letter=='m'||letter=='n'||letter=='o') return '6';
		else if(letter=='p'||letter=='q'||letter=='r'||letter=='s') return '7';
		else if(letter=='t'||letter=='u'||letter=='v') return '8';
		else if(letter=='w'||letter=='x'||letter=='y'||letter=='z') return '9';
	}
};

int main()
{
	Tree tree;
	string result;
	bool z;
	int i=0;

	cout << "Wczytywanie slownika z pliku dane.txt..." << endl;
	while(file.eof()==false)
	{
		string word;
		file>>word;
		tree.Insert(word);
		i++;
	}
	cout << "Slownik zostal wczytany. Zostalo " << i << " wczytanych slow.\n" << endl;

	while(1)
	{
		string word="";
		cout << "\n\n" << endl;
		cout << "+===========================+" << endl;
		cout << "|    7    |   8   |    9    |" << endl;
		cout << "| p q r s | t u v | w x y z |" << endl;		
		cout << "+===========================+" << endl;
		cout << "|    4    |   5   |    6    |" << endl;
		cout << "|  g h i  | j k l |  m n o  |" << endl;
		cout << "+===========================+" << endl;
		cout << "|    1    |   2   |    3    |" << endl;
		cout << "|  exit   | a b c |  d e f  |" << endl;
		cout << "+===========================+" << endl;
		cout << "Podaj liczby: ";
		cin >> word;
		cout << endl;
		if(word[0]=='1') break;
		tree.SearchNumberWord(word);
	}

	return 0;
}
