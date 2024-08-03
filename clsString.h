#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class clsString
{
private:
    string _Value = "";

public:
    clsString()
    {
        _Value;
    }

    clsString(string Value)
    {
        _Value = Value;
    }

    void setValue(string Value)
    {
        _Value = Value;
    }

    string getValue()
    {
        return _Value;
    }

    //__declspec(property(get = GetValue, put = SetValue)) string Value;

    static short Length(string S1)
    {
        return S1.length();
    };

    short Length()
    {
        return _Value.length();
    };

    static void PrintFirstLetterOfEachWord(string msg)
    {
        bool isFirstLetter = true;
        cout << "\nFirst letters of this string: \n";

        for (int i = 0; i < msg.length(); i++)
        {

            if (msg[i] != ' ' && isFirstLetter)
            {
                cout << msg[i] << endl;
            }

            isFirstLetter = (msg[i] == ' ' ? true : false);
        }
    }

    void PrintFirstLetterOfEachWord()
    {
        PrintFirstLetterOfEachWord(_Value);
    }

    static string UpperFirstLetterOfEachWord(string S1)
    {
        bool isFirstLetter = true;

        for (int i = 0; i < S1.length(); i++)
        {

            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = toupper(S1[i]);
            }

            isFirstLetter = (S1[i] == ' ' ? true : false);
        }

        return S1;
    }

    void UpperFirstLetterOfEachWord()
    {
        // no need to return value , this function will directly update the object value
        _Value = UpperFirstLetterOfEachWord(_Value);
    }

    static string LowerFirstLetterOfEachWord(string S1)
    {
        bool isFirstLetter = true;

        for (int i = 0; i < S1.length(); i++)
        {
            if (S1[i] != ' ' && isFirstLetter)
            {
                S1[i] = tolower(S1[i]);
            }
            isFirstLetter = (S1[i] == ' ' ? true : false);
        }

        return S1;
    }

    void LowerFirstLetterOfEachWord()
    {
        // no need to return value , this function will directly update the object value
        _Value = LowerFirstLetterOfEachWord(_Value);
    }

    static string UpperAllLetters(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            S1[i] = toupper(S1[i]);
        }
        return S1;
    }

    string UpperAllLetters()
    {
        return UpperAllLetters(_Value);
    }

    static string LowerAllLetters(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            S1[i] = tolower(S1[i]);
        }
        return S1;
    }

    string LowerAllLetters()
    {
        return LowerAllLetters(_Value);
    }

    static char InvertLetterCase(char Letter)
    {
        return isupper(Letter) ? tolower(Letter) : toupper(Letter);
    }

    static string InvertAllLettersCase(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            S1[i] = InvertLetterCase(S1[i]);
        }
        return S1;
    }

    enum enWhatToCount
    {
        SmallLetters = 0,
        CapitalLetters = 1,
        All = 3
    };

    static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All)
    {

        if (WhatToCount == enWhatToCount::All)
        {
            return S1.length();
        }

        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {

            if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i]))
                Counter++;

            if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
                Counter++;
        }

        return Counter;
    }

    string InvertAllLettersCase()
    {
        return InvertAllLettersCase(_Value);
    }

    static int CountCapitalLetters(string S1)
    {
        int Counter = 0;

        for (int i = 0; i < S1.length(); i++)
        {
            if (isupper(S1[i]))
            {
                Counter++;
            }
        }
        return Counter;
    }

    int CountCapitalLetters()
    {
        return CountCapitalLetters(_Value);
    }

    static int CountSmallLetters(string S1)
    {
        int Counter = 0;

        for (int i = 0; i < S1.length(); i++)
        {
            if (islower(S1[i]))
            {
                Counter++;
            }
        }
        return Counter;
    }

    int CountSmallLetters()
    {
        return CountSmallLetters(_Value);
    }

    static short CountLetter(string S1, char Letter, bool MatchCase = true)
    {
        short Counter = 0;

        for (short i = 0; i < S1.length(); i++)
        {
            if (MatchCase)
            {
                if (S1[i] == Letter)
                    Counter++;
            }
            else
            {
                if (tolower(S1[i]) == tolower(Letter))
                    Counter++;
            }
        }
        return Counter;
    }

    short CountLetter(char Ch1, bool MatchCase = true)
    {
        return CountLetter(_Value, Ch1, MatchCase);
    }

    static bool isVowel(char Ch1)
    {
        Ch1 = tolower(Ch1);

        switch (Ch1)
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;

        default:
            return false;
            break;
        }
    }

    static short CountVowel(string S1)
    {
        short Count = 0;
        for (short i = 0; i < S1.length(); i++)
        {
            if (isVowel(S1[i]))
            {
                Count++;
            }
        }
        return Count;
    }

    short CountVowel()
    {
        return CountVowel(_Value);
    }

    static void PrintAllVowels(string S1)
    {
        for (short i = 0; i < S1.length(); i++)
        {
            if (isVowel(S1[i]))
            {
                cout << S1[i] << "\t";
            }
        }
        cout << endl;
    }

    void PrintAllVowels()
    {
        return PrintAllVowels(_Value);
    }

    static void PrintEachWord(string S1)
    {
        cout << "\nYour string wrords are: \n\n";

        string delim = " "; // delimiter
        short pos = 0;
        string sWord; // define a string variable

        // use find() function to get the position of the delimiters
        while ((pos = S1.find(delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word

            if (sWord != "")
            {
                cout << sWord << endl;
            }

            S1.erase(0, pos + delim.length()); // erase() until positon and move to next word.
        }

        if (S1 != "")
        {
            cout << S1 << endl; // it print last word of the string.
        }
    }

    void PrintEachWord()
    {
        return PrintEachWord(_Value);
    }

    static int CountEachWord(string S1)
    {
        string Space = " ";
        short Index = 0;
        string Word;
        int Count = 0;

        // use find() function to get the position of the space
        while ((Index = (S1.find(Space))) != string::npos)
        {
            Word = S1.substr(0, Index); // store the word

            if (Word != "")
            {
                Count++;
            }

            S1.erase(0, Index + Space.length()); // erase() until positon and move to next word.
        }

        if (S1 != "")
        {
            Count++; // it counts the last word of the string.
        }

        return Count;
    }

    int CountEachWord()
    {
        return CountEachWord(_Value);
    }

    static vector<string> Split(string S1, string Delim = " ")
    {

        short Index = 0;
        string Word;
        vector<string> vString;

        while ((Index = S1.find(Delim)) != string::npos)
        {
            Word = S1.substr(0, Index);

            if (Word != "")
            {
                vString.push_back(Word);
            }

            S1.erase(0, Index + Delim.length());
        }

        if (S1 != "")
        {
            vString.push_back(S1);
        }
        return vString;
    }

    vector<string> Split(string Delim = " ")
    {
        return Split(_Value, Delim);
    }

    static string TrimLeft(string S1)
    {
        return S1.substr(S1.find_first_not_of(" "), S1.length());
    }

    void TrimLeft()
    {
        _Value = TrimLeft(_Value);
    }

    static string TrimRight(string S1)
    {
        return S1.substr(0, S1.find_last_not_of(" ") + 1);
    }

    void TrimRight()
    {
        _Value = TrimRight(_Value);
    }

    static string Trim(string S1)
    {
        return TrimLeft(TrimRight(S1));
    }

    void Trim()
    {
        _Value = Trim(_Value);
    }

    static string ReverseWords(string S1, string Dilem = " ")
    {
        vector<string> vString;
        string S2 = "";
        vString = Split(S1, Dilem);

        vector<string>::iterator iter = vString.end(); // declare iterator

        while (iter != vString.begin())
        {
            --iter;
            S2 += *iter + " ";
        }

        S2 = S2.substr(0, S2.length() - 1); // remove last space.

        return S2;
    }

    void ReverseWords(string Dilem = " ")
    {
        _Value = ReverseWords(_Value, Dilem);
    }

    static string JoinString(vector<string> vString, string Delim)
    {
        string S1;
        for (string &s : vString)
        {
            S1 = S1 + s + Delim;
        }
        return S1.substr(0, S1.length() - Delim.length());
    }

    static string JoinString(string arrString[], short Length, string Delim)
    {

        string S1 = "";

        for (short i = 0; i < Length; i++)
        {
            S1 = S1 + arrString[i] + Delim;
        }

        return S1.substr(0, S1.length() - Delim.length());
    }

    static string ReplaceWord(string S1, string OldWord, string UpdateWord, bool MatchCase = true)
    {
        vector<string> vString = Split(S1, " ");
        for (string &s : vString)
        {
            if (MatchCase)
            {
                if (s == OldWord)
                {
                    s = UpdateWord;
                }
            }
            else
            {
                if (LowerAllLetters(s) == LowerAllLetters(OldWord))
                {
                    s = UpdateWord;
                }
            }
        }
        return JoinString(vString, " ");
    }

    string ReplaceWord(string OldWord, string UpdateWord, bool MatchCase = true)
    {
        return ReplaceWord(_Value, OldWord, UpdateWord, MatchCase);
    }

    static string RemovePunctuations(string S1)
    {
        for (int i = 0; i < S1.length(); i++)
        {
            if (ispunct(S1[i]))
            {
                S1[i] = S1.empty();
            }
        }
        return S1;
    }

    string RemovePunctuations()
    {
        return RemovePunctuations(_Value);
    }
};