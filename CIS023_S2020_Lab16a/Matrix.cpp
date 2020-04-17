// Module:	Matrix.h
// Author:	Miguel Antonio Logarta
// Date:	April 16, 2020
// Purpose:	Implementation file for Matrix class
//			Node class for linked list

#include "framework.h"
#include "CIS023_S2020_Lab16a.h"

Matrix::Matrix(string strName, string strDec, string strHex, string strOct, string strBin)
{
	StringtoTCHAR(&strName, szName);	// Store name
	StringtoTCHAR(&strDec, szDec);		// Store decimal
	StringtoTCHAR(&strHex, szHex);		// Store hexadecimal
	StringtoTCHAR(&strOct, szOct);		// Store octaldecimal
	StringtoTCHAR(&strBin, szBin);		// Store binary
}

TCHAR* Matrix::GetName()
{
	return szName;
}

TCHAR* Matrix::GetDec()
{
	return szDec;
}

TCHAR* Matrix::GetHex()
{
	return szHex;
}

TCHAR* Matrix::GetOct()
{
	return szOct;
}

TCHAR* Matrix::GetBin()
{
	return szBin;
}

void Matrix::SetNext(Matrix* node)
{
	Next = node;
}

Matrix* Matrix::GetNext()
{
	return Next;
}
