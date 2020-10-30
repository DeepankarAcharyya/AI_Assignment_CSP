/*
Roll No. : CSB17017
Sessional II : CO401 : Artificial Intelligence
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <conio.h>

using namespace std;

//function to check if a character is in a string
int ifin(string s1, char c)
{
    int i;
    int n = s1.size();
    for (i = 0; i < n; i++)
    {
        if (s1[i] == c)
            return 1;
    }
    return 0;
}

//function to extract unique characters from a string
string extract(string s1, string s2)
{
    int i, a;
    int n1 = s1.size();
    int n2 = s2.size();

    if (n2 == 0)
    {
        a = 1;
        s2 = s1[0];
    }
    else
        a = 0;

    for (i = a; i < n1; i++)
    {
        if (ifin(s2, s1[i]) == 0)
        {
            s2 = s2 + s1[i];
        }
    }
    return s2;
}

//function to extract the variables
string get_var(string s1, string s2, string s3)
{
    string s4("");
    s4 = extract(s1, s4);
    s4 = extract(s2, s4);
    s4 = extract(s3, s4);
    return s4;
}

//function to convert string to number
int convert_string_to_number(string s1, map<char, int> state)
{
    int i, n1 = 0;
    for (i = 0; i < s1.size(); i++)
    {
        n1 = n1 * 10 + state[s1[i]];
    }
    return n1;
}

//structure to hold domain available value info
struct state_node
{
    int value;
    int taken;
    map<char, int> tracker;
};

int create_state(int i, string var, vector<struct state_node> tracker, map<char, int> tracker01, int index)
{
    if (i < var.size())
    {
        for (int j = 0; j < 10; j++)
        {
            if (tracker.at(j).taken == 1 || tracker.at(j).tracker[var[i]] == 1)
                continue;
            tracker01[var[i]] = j;
            tracker.at(j).taken = 1;
            tracker.at(j).tracker[var[i]] = 1;
            index = create_state(i + 1, var, tracker, tracker01, index);

            if (index == -1)
            {
                return -1;
            }

            tracker.at(j).taken = 0;
        }
    }
    else if (i == var.size())
    {
        cout << "NODE: " << index++ << " [";
        for (map<char, int>::const_iterator it = tracker01.begin(); it != tracker01.end(); ++it)
        {
            cout << " " << it->first << "=" << it->second;
        }
        cout<<"] ";
        int send = convert_string_to_number("SEND", tracker01);
        int more = convert_string_to_number("MORE", tracker01);
        int money = convert_string_to_number("MONEY", tracker01);
        
        if (send + more == money)
        {
            cout << "SEND=" << send << " MORE=" << more << " TOTAL=" << send + more << " MONEY=" << money;
            cout << "----SOLUTION FOUND";
            return -1;
        }
        cout << endl;
    }
    return index;
}

//------------------------------------------------MAIN FUNCTION--------------------------------------------------------------
int main()
{
    //define the inputs
    string input01("SEND");
    string input02("MORE");
    string input03("MONEY");
    char operation = '+';

    //PART 1 : Modeling the cryptarithmetic problem into a CSP
    cout << "\nPART 1 : Modeling into a CSP" << endl;

    cout << "string 1 : "<< input01<<endl;
    cout << "string 2 : " << input02 << endl;
    cout << "string 3 : " << input03 << endl;
    //Extracting variables
    string variables = get_var(input01, input02, input03);
    cout << "\nThe (distinct) variables: " << variables << endl;

    //extracting the constraints
    cout << "\nconstraint :" << endl;
    cout << "1." << input01 << operation << input02 << "=" << input03 << endl;
    cout << "2. All the variables must have distinct values." << endl;

    //Setting the domain for the problem
    int domain[10];
    int i;
    for (i = 0; i < 10; i++)
    {
        domain[i] = i;
    }
    cout << "\nThe domain : " << endl;
    for (i = 0; i < 10; ++i)
        cout << i << " ";
    cout << endl;
    cout << "\n<Press Enter to continue>" << endl;
    getch();

    //PART 2 : Searching for the solution
    cout << "\nPART 2 : Searching for the solution " << endl;

    map<char, int> tracker01;

    for (i = 0; i < variables.size(); i++)
    {
        tracker01[variables[i]] = 0;
    }

    vector<struct state_node> domain_tracker;

    for (i = 0; i < 10; i++)
    {
        struct state_node n1;
        n1.value = i;
        n1.taken = 0;
        n1.tracker = tracker01;
        domain_tracker.push_back(n1);
    }

    int index = 1;
    index = create_state(0, variables, domain_tracker, tracker01, index);

    if (index != -1)
    {
        cout << "SOLUTION NOT FOUND!!!" << endl;
    }
    getch();

    return 0;
}