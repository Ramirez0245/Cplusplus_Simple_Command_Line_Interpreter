// ConsoleApplication1.cpp : Simple Command Line Interpreter.
// Copyright (c) Omar Ramirez 9/26/2022
//Ignore depracated
//About: This code is about working on creating threads using Winapi and doing os system calls within the thread
//		 There are only 9 allowed system calls.
//		 The only allowed options are dir, help, vol, path, tasklist, notepad, echo, color, ping, and exit
//		 The code check if correct inputs are entered
//		 This is written in C++

#pragma warning(disable : 4996)

#include <windows.h>
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>

using namespace std;
char* cstr;

DWORD WINAPI myShell(LPVOID inputParamm) {
	system(cstr);
	return 0;
}

int main() {
	string inputParam;
	string* inputpointer = &inputParam;
	HANDLE ThreadHandle;
	DWORD ThreadId;
	string backstring;

	while (1) {
		//Get input
		cout << "Please Enter your command to send the os system: ";
		getline(cin, inputParam);

		//Convert String -> Char
		cstr = new char[inputParam.length() + 1];
		strcpy(cstr, inputParam.c_str());

		//Make trim to first token
		char* p; 
		p = strtok(cstr, " ");

		//Convert Char -> String
		backstring = cstr;
		
		if (backstring == "dir" || backstring == "help" || backstring == "vol" || backstring == "path" || backstring == "tasklist" || backstring == "notepad" || backstring == "echo" || backstring == "color" || backstring == "ping" || backstring == "exit") {
			//Get oringal string input
			strcpy(cstr, inputParam.c_str());

			//End the program if true
			if (backstring == "exit") {
				return 0; 
			}

			//Create thread
			ThreadHandle =	CreateThread(NULL, 0, myShell, &inputpointer, 0, &ThreadId);

			//Wait for threadto finish
			if (ThreadHandle != NULL) {
				WaitForSingleObject(ThreadHandle, INFINITE);
				CloseHandle(ThreadHandle);
			}
		}
		else { cout << endl << "\n" << "Incorrect Input, please try again" << "\n"; }
	}
}

 