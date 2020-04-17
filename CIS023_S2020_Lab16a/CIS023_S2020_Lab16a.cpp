// Module:		CIS023_S2020_Lab16a.cpp
// Author:		Miguel Antonio Logarta
// Date:		April 16, 2020
// Purpose:		Learn how to create a linked list using class code.
//				Create object nodes and fill them with data.
//				Scroll through an object - based linked list to find a specific node.
//

#include "framework.h"
#include "CIS023_S2020_Lab16a.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hWnd_Input;								// input field
HWND hWnd_Name;									// output fields
HWND hWnd_Dec;									// .
HWND hWnd_Hex;									// .
HWND hWnd_Oct;									// .
HWND hWnd_Bin;									// .
HWND hWnd_Find;									// Button

// Linked list pointers
Matrix* firstNode, * lastNode, * newNode, * currentNode;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void LoadFile();								// load file into linked list

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CIS023S2020LAB16A, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CIS023S2020LAB16A));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CIS023S2020LAB16A));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+0);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CIS023S2020LAB16A);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 350, 325, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case BN_CLICKED:	// capture button click
				if (LOWORD(lParam) == (WORD)hWnd_Find)				// If the user has clicked the find button
				{
					TCHAR szInput[TCHAR_SIZE];						// User data
					string strInput;								// Converted user input
					string strComparison;							// String to compare to

					// Capture user input
					SendMessage(hWnd_Input,
						WM_GETTEXT,
						TCHAR_SIZE,
						LPARAM(szInput));

					TCHARtoString(szInput, &strInput);				// Convert the user input to string

					// Set the current node to the first node
					currentNode = firstNode;

					// Get the name from the current node for comparison
					TCHARtoString(currentNode->GetName(), &strComparison);

					// Roll through list until it finds what the user entered
					while ((strInput != strComparison)			// While the input does not match the string
						&& (currentNode != nullptr))			// While not the end of the list
					{
							currentNode = currentNode->GetNext();						// Get the address to the next node
							TCHARtoString(currentNode->GetName(), &strComparison);		// Get the name from that node for comparison
					}

					// Display output if there is a match
					if (currentNode != nullptr)
					{
						SetWindowText(hWnd_Name, currentNode->GetName());
						SetWindowText(hWnd_Dec, currentNode->GetDec());
						SetWindowText(hWnd_Hex, currentNode->GetHex());
						SetWindowText(hWnd_Oct, currentNode->GetOct());
						SetWindowText(hWnd_Bin, currentNode->GetBin());
					}
				}
			break;
			
			case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CREATE:

		// prompt
		CreateWindow(TEXT("STATIC"),
			TEXT("Enter a string to search:"),
			WS_VISIBLE | WS_CHILD,
			10, 10, 175, 20, hWnd, NULL, NULL, NULL);

		// labels
		CreateWindow(TEXT("STATIC"),
			TEXT("Name:"),
			WS_VISIBLE | WS_CHILD,
			10, 50, 110, 20, hWnd, NULL, NULL, NULL);
		CreateWindow(TEXT("STATIC"),
			TEXT("Decimal:"),
			WS_VISIBLE | WS_CHILD,
			10, 80, 110, 20, hWnd, NULL, NULL, NULL);
		CreateWindow(TEXT("STATIC"),
			TEXT("Hexadecimal:"),
			WS_VISIBLE | WS_CHILD,
			10, 110, 110, 20, hWnd, NULL, NULL, NULL);
		CreateWindow(TEXT("STATIC"),
			TEXT("Octal:"),
			WS_VISIBLE | WS_CHILD,
			10, 140, 110, 20, hWnd, NULL, NULL, NULL);
		CreateWindow(TEXT("STATIC"),
			TEXT("Binary:"),
			WS_VISIBLE | WS_CHILD,
			10, 170, 110, 20, hWnd, NULL, NULL, NULL);

		// create edit control for user input
		hWnd_Input = CreateWindow(TEXT("EDIT"),
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL | WS_CHILD,
			200, 10, 100, 20, hWnd, NULL, NULL, NULL);

		// output static controls
		hWnd_Name = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD,
			130, 50, 170, 20, hWnd, NULL, NULL, NULL);
		hWnd_Dec = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD,
			130, 80, 170, 20, hWnd, NULL, NULL, NULL);
		hWnd_Hex = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD,
			130, 110, 170, 20, hWnd, NULL, NULL, NULL);
		hWnd_Oct = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD,
			130, 140, 170, 20, hWnd, NULL, NULL, NULL);
		hWnd_Bin = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD,
			130, 170, 170, 20, hWnd, NULL, NULL, NULL);

		// find button
		hWnd_Find = CreateWindow(TEXT("BUTTON"),
			TEXT("Find"),
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			150, 200, 70, 30, hWnd, NULL, NULL, NULL);

		// put your name in the window title
		SetWindowText(hWnd, TEXT("CIS 023, Lab 16a, Miguel Antonio Logarta"));

		// load file into linked list
		LoadFile();

		break;

	case WM_DESTROY:
		// Delete the linked list
		if (currentNode)							// If the list exists
		{
			lastNode->SetNext(nullptr);				// Set last next to prevent overflow

			Matrix* tempNode = nullptr;				// Temporary pointer
			currentNode = firstNode;				// Start at the top of the list

			while (currentNode != nullptr)			// Loop until the entire list is deleted
			{
				tempNode = currentNode->GetNext();	// Save pointer to next node
				delete currentNode;					// Delete the current node
				currentNode = tempNode;				// Move on to the next node
			}
		}

        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// load the file into the linked list
void LoadFile()
{
	string strName = "";								// temps to hold file data
	string strDec = "";
	string strHex = "";
	string strOct = "";
	string strBin = "";

	ifstream fInput;									// file pointer

	try
	{
		fInput.open("CIS023_S2020_Lab16a_Data.csv");	// open file

		if (!fInput)
			throw 1;

		while (fInput.good())
		{
			getline(fInput, strName, ',');
			getline(fInput, strDec, ',');
			getline(fInput, strHex, ',');
			getline(fInput, strOct, ',');
			getline(fInput, strBin, '\n');

			// Create the linked list to store the values
			newNode = new Matrix(strName, strDec, strHex, strOct, strBin);

			if (firstNode == nullptr)						// If this is the first pointer
				firstNode = newNode;						// Then set the pointer
			else                                            // List has been started
				lastNode->SetNext(newNode);					// Set the pointer of the previous node

			lastNode = newNode;								// This new node becomes the last
		}

		fInput.close();										// ALWAYS remember to close the file

		currentNode = firstNode;							// Start at the top of the list
		EnableWindow(hWnd_Find, true);						// enable search button
	}
	catch (int)
	{
		MessageBox(NULL,
			TEXT("Failed to load file"),
			TEXT("File Error"),
			MB_ICONERROR);

		EnableWindow(hWnd_Find, false);						// disable search

	}
}


