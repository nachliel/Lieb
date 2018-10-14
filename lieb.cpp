///*******************************************
///**										**
///**--------MATH CALCULUS V1.0-------------**
///** Created by Nachliel Shilo,			**
///**			09/02/2011-10/02/2011 v1.0	**
///**	EMAIL : nachliels@gmail.com			**
///**										**
///*******************************************
#include <iostream>
#include <string>
#include <math.h>
using namespace std;


class lieb
{
	//The number counter here points all vars, A, B, C... etc...
	//			   A, B, C, D, E, F, G, H, I, J
	int vars[10];
	//Here I define whom cannot be zero; true - mean no zero;
	//				 A,B,C,D,E,F,G,H,I,J
	bool nozero[10];
	//Pointer to the VARS. to get the numbers for calculation.
	int *add_input[10][10];
	//The number of possible results.
	int results;
public:
	//******USER INPUT******
	//user equation input.
	char input[10][10];
	//user operator input.
	char oper[10];

	//This is the numbers generated from the user's equation.
	int num[10];
	//This is the length of the vars calculated by user input.
	int var_len;

	//This will generate the numbers according the the equation and to the vars.
	void gen();
	//This will initialize all vars (constructor)
	lieb()
	{
		//Initial the vars and the no zero. to -1 and 0.
		for(int i=0;i<10;i++) {vars[i] = -1;nozero[i] = false;}
		var_len=0;
		results=0;
	}

	//Initializing the var.
	void begin_var();

	//Addone adds +1 to the vars to roll all over the possible numbers for the vars A,B,C,D...
	//returns true on success or false if reach the limit.
	bool addone(int);
	//Prints the values in the var array.
	void print_var()
	{
		results++;
		cout << "\n@"; ///var_len
		for(int i=0;i<var_len;i++)
		{
			cout << char(i+65) << "=" << vars[i] << ", ";
		}
		cout << ";";
	}
	//print the number of possible results.
	void print_num()
	{
		cout << "\n+++++++++++++++++++++++++++" <<
			"\nYou have: " << results << " results.\n++++++++++++++++++++++++++++\n";
	}
};


//Begin_Var initialize the values according to user input.
//This will put the minimum number according the user input
//in the vars section, and addressing the pointers.
void lieb::begin_var()
{
	//Flag to know if we define zero in the vars.
	bool flag=true;
	int i,add = 0;

	//Define the number of vars inserted by the user
	int inp_len;
	for(i=0;i<input[i][0]!=NULL;i++)
	{
		//Check the length of the input.
		inp_len = strlen(input[i]);
		for(int j=0;j<inp_len+1;j++)
		{
			vars[input[i][j]-65] = -2;
			if (j==0)	//Asign that each number who is the first could not be zero;.
				nozero[input[i][j]-65]=true;
		}
	}
	for(i=0;vars[i]==-2;i++)
		{var_len++; vars[i]=-1;}
	
	//This is the loop that define the numbers to be inserted to the vars
	//for example: for the strings ABCD -> 1023 - the minimum numbers..
	//or ABC+BCD -> 1203, B cannot be zero.
	for(i=1;i<var_len;i++)
	{
		//must have no zero 
		if ((nozero[i]) && (add==0))
		{
			//In case that each var cannot be 0,
			// skips to the next number .. 1.
			if (i==var_len-1)
			{
				flag=false;  //sign for next level. 1 +++
				i=-1;		// restart the loop.
				add=1;		// next level 1,2, 3... and so on..
			}
			continue;
		}
		else
		{
			if (vars[i] == -1)
			{
				vars[i] = add++;
				// if it's the first num with zero..
				// define to go to the next level.
				//
				if (flag)
				{
					flag=false; //sign for the next level.
					i=-1;		//restart the loop
				}
			}
		}
	}


	//now need to address the pointers, to the vars.
	//according to user input.
	for(i=0;i<input[i][0]!=NULL;i++) //loop till the end of user line vars.
	{
		for(int j=0;input[i][j]!=NULL;j++) // loop till the end of the var
		{
			//Address the pointer to the var according to the user input.
			//NOTICE!
			// user input must be in CAPITAL letters ABC.. etc.
			add_input[i][j]=&vars[input[i][j]-65];
		}
	}
}

//generator function, will generate the value of the number
//according to the vars and to the user input.
void lieb::gen()
{
	int inp_len;
	int l;
	for(l=0;l<input[l][0]!=NULL;l++)
	{
		//Check the length of the input.
		inp_len = strlen(input[l]);
		num[l]=0; //zeroize the value for another check.input[i][j]!=NULL
		for(int j=0;j<inp_len;j++)
			num[l] += *add_input[l][j]*powl(10,inp_len-j-1);
	}
}

//This function adds +1 to the vars, to repeate all posible numbers.
bool lieb::addone(int n)
{

	if ((n==-1) || (vars[0]==0))
		return false;

	if (vars[n]!=9)
		vars[n]++;
	else
	{
		vars[n]=0;
		if (nozero[n])
			vars[n]=1;
		//addone(n-1); --V
		if (addone(n-1)==false)
			return false;
	}

	///Check that each number is diffrent, in the vars.
	int i;
	for(i=0;i<var_len;i++)
	{
		if ((vars[n]==vars[i]) && (n!=i))
			if ((vars[n]==0) && (n<var_len-2))
				addone(n+1);
			else
				addone(n);
	}
	int num=9;
	i=0;
	while((vars[i]==num) && (i<var_len-1))
	{
		num--;
		i++;
	}
	if (i==var_len-1)
		return false;

	return true;
}

int main()
{

	cout << "---===Calculus  V1.0===---" <<
			"\nPlease follow the instructions below:" <<
			"\n*All variables must be in CAPITAL LETTERS (i.e 'ABC')" <<
			"\n*All variables must be from A to J, each var represent a diffrent number." <<
			"\n*Do not skip any letter. (i.e Wrong: ABC+HG Good: ABC+DE" <<
			"\nExample:\nABD	[ENTER]\n+	[ENTER]\nBC	[ENTER]\n=	[ENTER]\nDAB	[ENTER]\n" <<
			"\n----------------------------------------------------------\n";
	//define exm as new class.
	lieb exm;
	
	char str[10]={'.'}, i=1,l=0;
	while (str[0]!='=')
	{
		cin >> str;
		if (i%2==0)
		{
			exm.oper[l]=str[0];						///If inserted a operator, usualy will be the second.
			l++;
		}
		else
			strcpy_s(exm.input[l],str);
		i++;
	}
	///Here the user insert the answer.
	cin >> exm.input[l];
	int counter=i-1;
	int sideone=0;
	///initial the var.
	exm.begin_var();
	do
	{
		//generate the new numbers.
		exm.gen();
		//enter the first value.
		sideone = exm.num[0];
		for(i=0;i<counter;i++)
		{
			switch (exm.oper[i])
			{
				case '+':
					sideone+=exm.num[i+1];
					break;
				case '-':
					sideone-=exm.num[i+1];
					break;
				case '*':
					sideone*=exm.num[i+1];
					break;
				case '=':
					if (sideone==exm.num[i+1])
						exm.print_var();
					break;
			}
		}

	}
	while (exm.addone(exm.var_len-1));

	exm.print_num();

	system("pause");
	return 0;
}