#include <iostream>   // 표준 입출력 스트림 라이브러리
#include <fstream>    // 파일 입출력 스트림 라이브러리
#include <string>     // 문자열 라이브러리
#include <vector>     // 벡터(동적 배열) 라이브러리
#include <iomanip>    // 입출력 조정 라이브러리
#include <algorithm>  // 알고리즘 라이브러리 (std::max 함수 포함)

using namespace std;  // 표준 네임스페이스 사용

// 문자열 끝의 공백을 제거하는 함수
string trimEnd(const string& str) {
    // 문자열 끝에서 공백 문자를 찾음
    size_t end = str.find_last_not_of(" \n\r\t");
    if (end == string::npos) {
        // 공백이 없는 경우 빈 문자열 반환
        return "";
    } else {
        // 공백을 제거한 문자열 반환
        return str.substr(0, end + 1);
    }
}

int main() {
    // lexical_analyzer 프로그램 실행 및 출력 억제
    int ret = system("./lexical_analyzer > /dev/null 2>&1");
    if (ret != 0) {
        // 실행 오류 시 에러 메시지 출력 후 종료
        cerr << "Error executing lexical_analyzer" << endl;
        return 1;
    }

    // grammar_checker 프로그램 실행 및 출력 억제
    ret = system("./grammar_checker > /dev/null 2>&1");
    if (ret != 0) {
        // 실행 오류 시 에러 메시지 출력 후 종료
        cerr << "Error executing grammar_checker" << endl;
        return 1;
    }

    // input.txt 파일 열기
    ifstream inputFile("input.txt");
    // grammar.txt 파일 열기
    ifstream grammarFile("grammar.txt");
    // Complete.txt 파일 쓰기 모드로 열기
    ofstream mergedFile("Complete.txt");

    // 파일이 제대로 열렸는지 확인
    if (!inputFile.is_open() || !grammarFile.is_open()) {
        cerr << "Error opening one of the files." << endl;
        return 1;
    }

    // 각 파일의 줄을 저장할 벡터 생성
    vector<string> inputLines;
    vector<string> grammarLines;
    string line;  // 각 줄을 저장할 문자열

    // input.txt 파일에서 줄 단위로 읽어와서 벡터에 저장
    while (getline(inputFile, line)) {
        inputLines.push_back(trimEnd(line));
    }

    // grammar.txt 파일에서 줄 단위로 읽어와서 벡터에 저장
    while (getline(grammarFile, line)) {
        grammarLines.push_back(trimEnd(line));
    }

    // 파일 닫기
    inputFile.close();
    grammarFile.close();

    // 두 벡터의 줄 수가 같은지 확인
    if (inputLines.size() != grammarLines.size()) {
        cerr << "lexical_analyzer OR grammar_checker don't works!" << endl;
        return 1;
    }

    // 각 파일의 최대 줄 길이를 계산
    size_t maxWidth1 = 0;
    size_t maxWidth2 = 0;

    for (size_t i = 0; i < inputLines.size(); i++) {
        if (inputLines[i].size() > maxWidth1) {
            maxWidth1 = inputLines[i].size();
        }
    }

    for (size_t i = 0; i < grammarLines.size(); i++) {
        if (grammarLines[i].size() > maxWidth2) {
            maxWidth2 = grammarLines[i].size();
        }
    }

    // 열 간의 간격 설정
    size_t spacing = 4;

    // 헤더를 파일과 콘솔에 출력
    mergedFile << left << setw(maxWidth1 + spacing) << "Input value"
               << "Grammar Check" << endl;
    mergedFile << string(maxWidth1 + spacing + maxWidth2, '-') << endl;
    
    cout << left << setw(maxWidth1 + spacing) << "Input value"
         << "Grammar Check" << endl;
    cout << string(maxWidth1 + spacing + maxWidth2, '-') << endl;

    // 각 줄을 병합하여 파일과 콘솔에 출력
    for (size_t i = 0; i < inputLines.size(); i++) {
        mergedFile << left << setw(maxWidth1 + spacing) << inputLines[i]
                   << grammarLines[i] << endl;
        cout << left << setw(maxWidth1 + spacing) << inputLines[i]
             << grammarLines[i] << endl;
    }

    // 출력 파일 닫기
    mergedFile.close();

    // 성공 메시지 출력
    cout << "Done" << endl;

    return 0;
}
