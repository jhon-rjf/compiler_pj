#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Function to perform grammar check using finite state machine
string grammarCheck(const vector<string>& tokens) {
    int state = 0;
    cout << "Initial State: " << state << endl; // Debugging output
    for (const string& token : tokens) {
        cout << "Token: " << token << ", Current State: " << state << endl; // Debugging output
        if (token == "undefined") {
            return "invalid";
        }
        if (state == 0) {
            if (token == "Datatype") state = 1;
            else if (token == "identifier") state = 2;
            else return "invalid";
        } else if (state == 1) {
            if (token == "identifier") state = 2;
            else return "invalid";
        } else if (state == 2) {
            if (token == "delimiter") state = 6;
            else if (token == "operator") state = 3;
            else return "invalid";
        } else if (state == 3) {
            if (token == "identifier") state = 4;
            else if (token == "Constant") state = 5;
            else return "invalid";
        } else if (state == 4) {
            if (token == "operator") state = 3;
            else if (token == "delimiter") state = 6;
            else return "invalid";
        } else if (state == 5) {
            if (token == "operator") state = 3;
            else if (token == "delimiter") state = 6;
            else return "invalid";
        } else if (state == 6) {
            if (token == "identifier") state = 4;
            else if (token == "operator") state = 5;
            else if (token == "delimiter") return "invalid";
            else return "valid";  // 문장 종료 시 valid 처리
        } else {
            return "invalid";
        }
        cout << "New State: " << state << endl; // Debugging output
    }

    if (state == 6) {
        return "valid";
    }

    return "invalid";
}

int main() {
    // Open the lexical analysis output file
    ifstream lexicalInputFile("lexical.txt");
    if (!lexicalInputFile) {
        cerr << "Unable to open lexical input file" << endl;
        return 1;
    }

    // Vector to store the tokens read from the file
    vector<vector<string>> tokensPerLine;
    string line;

    // Read lines from the file
    while (getline(lexicalInputFile, line)) {
        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
        tokensPerLine.push_back(tokens);
    }

    lexicalInputFile.close();

    // Open the grammar output file
    ofstream grammarOutputFile("grammar.txt");
    if (!grammarOutputFile) {
        cerr << "Unable to open grammar output file" << endl;
        return 1;
    }

    // Process each line for grammar analysis and store the results in a 2D vector
    for (const auto& tokens : tokensPerLine) {
        cout << "Processing Line: "; // Debugging output
        for (const auto& token : tokens) {
            cout << token << " ";
        }
        cout << endl; // Debugging output
        string grammarResult = grammarCheck(tokens);
        grammarOutputFile << grammarResult << endl;
        cout << "Result: " << grammarResult << endl; // Debugging output
    }

    grammarOutputFile.close();

    return 0;
}
