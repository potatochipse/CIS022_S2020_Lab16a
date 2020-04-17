// Module:	Matrix.h
// Author:	Miguel Antonio Logarta
// Date:	April 16, 2020
// Purpose:	Header file for Matrix class
//			Node class for linked list

#pragma once
class Matrix
{
public:
	Matrix(string, string, string, string, string);

	// Accessors
	TCHAR* GetName();
	TCHAR* GetDec();
	TCHAR* GetHex();
	TCHAR* GetOct();
	TCHAR* GetBin();

	// Link
	void SetNext(Matrix*);			// Mutator
	Matrix* GetNext();				// Accessor

private:
	// Store input
	TCHAR szName[TCHAR_SIZE];		// Name
	TCHAR szDec[TCHAR_SIZE];		// Name in decimal
	TCHAR szHex[TCHAR_SIZE];		// Name in hexadecimal
	TCHAR szOct[TCHAR_SIZE];		// Name in octaldecimal
	TCHAR szBin[TCHAR_SIZE];		// Name in binary

	Matrix* Next;					// Address of the next node
};

