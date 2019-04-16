'----------------------[CYPHER Header]----------------------------

'data type to hold the before and after text of an encryption
Record TextCypher
    original: String
    encoded : String
    dateTime: String
EndTextCypher

'data type to hold the current user
Record User
    username: String
    password: String
EndUser

'----------------------[main]----------------------------
Driver ()
    userInput: TextCypher
    user: User
    choice: Character

    If (LoginSignUp (user) = 1) Then
        choice = MainMenu ()

        While (choice <> 'E' AND choice <> 'e') DO
            CASE of choice
                Case 'A':
                Case 'a':
                    Encode (userInput)

                Case 'B':
                Case 'b':
                    Decode (userInput)

                Case 'C':
                Case 'c':
                    ShowHistory ()

                Case 'D':
                Case 'd':
                    UpdateLogin ()

                Default
                    Print "INVALID OPTION!"
            EndCase

            choice = MainMenu ()
        EndWhile
    EndIf

    GoodBye ()
EndDriver

LoginSignUp (user: User): Integer 
    nameOnFile, passwordOnFile: String
    fp: File

    If ((fp = Open "userData.dat" for reading + writing) <> NULL) Then
        Read nameOnFile from File, fp
        Read passwordOnFile from File, fp

        'check if to sign up or login
        If (nameOnFile <> "") Then
            'login
            Repeat
                Print "LOGIN"
                Print "ENTER USERNAME: "
                Read user.username
                Print "ENTER PASSWORD: "
                Read user.password
            Until (user.username = nameOnFile  OR user.password = passwordOnFile)

            return 1
        Else
            'sign up
            Repeat
                Print "SIGN UP"
                Print "ENTER USERNAME: "
                Read user.username
                Print "ENTER PASSWORD: "
                Read user.password
            Until (user.username <> ""  OR user.password <> "")

            Write user.username, user.password to File, fp
            return 1
        EndIf

        Close File, fp
    Else
        Print "CANNOT LOAD USER DATA... RESTART THE PROGRAM"
        return 0
    EndIf
EndLoginSignUp

UpdateLogin()
    uname, pwd: String
    fp: File

    Repeat
        Print "CHANGE USERNAME AND PASSWORD"

        Print "ENTER NEW USERNAME: "
        Read uname
        Print "ENTER NEW PASSWORD: "
        Read pwd
    Until (uname <> "" AND pwd <> "")

    If((fp = Open File "userData.dat", for writing) <> NULL) Then
        Write uname, pwd To File, fp
        Close File fp
    Else
        Print "CANNOT UPDATE AT THIS TIME..."
    EndIf
EndUpdateLogin

MainMenu(): Character
    c: Character

    Print "A) ENCODE A MESSAGE"
    Print "B) DECODE A MESSAGE"
    Print "C) SHOW HISTORY"
    Print "D) UPDATE LOGIN INFO"
    Print "E) EXIT"

    Print "CHOOSE AN OPTION ABOVE: "
    Read c

    return c
EndMainMenu

'-------------------[Encoder & Decoder]-----------------------

SPACE_SPECIFIER = "700": Constant String
NUMBER_SPECIFIER = "800": Constant String
SYMBOL_SPECIFIER = "900": Constant String

UPPER = 9 : Constant Integer
LOWER = 2: Constant Integer

Encode(cypher: TextCypher)
    inputStr, newTxt = "", amPm, asciiValTxt: String
    i, asciiVal: Integer
    publicKey, privateKey: Integer 'equivalent to public and private key in cryptography
    tm: Time 'system time and date

    publicKey = Random between UPPER AND LOWER 
    privateKey = (publicKey * 5) - publicKey ' key used to encrypt

    ' Add the public key to the text
    newTxt[0] = publicKey 

    ' '''' GET USER DATA '''''

    Print "ENTER TEXT (ENGLISH): "
    Read inputStr

    cypher.original = inputStr

    ' ''' encoding process '''''
    For (i = 0 To Length of(inputStr)) Do

        If (inputStr[i] is Digit) Then'if the character is a number
            'add the number specifier before the num
            newTxt = newTxt + NUMBER_SPECIFIER
            newTxt = newTxt + inputStr[i]
        
        Else If (inputStr[i]) is Space) Then 'if the character is a space
            'add the space specifier before
            newTxt = newTxt + SPACE_SPECIFIER
        
        Else if (inputStr[i]) is Symbol) Then 'if the character is a symbol
            'add the symbol specifier before
            newTxt = newTxt + SYMBOL_SPECIFIER
            newTxt = newTxt + inputStr[i]
        
        Else 'regular letter
            asciiVal = inputStr[i] 'character's ascii value
            asciiVal = asciiVal + privateKey ' increment by key

            If (asciiVal < 100) 'add 0 before to ensure groups of 3 digits 
                newTxt = newTxt + "0"
            EndIf

            newTxt = newTxt + asciiValTxt
        EndIf
    EndFor   
    
    cypher.encoded = newTxt 'save encoded text to the structure

    ' Add time/date to the cypher
    If (tm.hour >= 12) Then
        amPm = "PM"
    Else
        amPm = "AM"
    EndIf

    'Format: dd/ mm/ yyyy @ hrs : min
    cypher.dateTime = tm.day, "/", tm.month, "/", tm.year, " @ ", tm.hour, ":", tm.minutes

    Print "ENCODED TEXT: ", cypher.encoded
    SaveToFile (cypher)

    AddToHistory(cypher)
EndEncode

Decode(cypher: TextCypher)
    inputStr, newTxt = "", amPm, asciiValTxt = "", fName: String
    opt: Character
    i, asciiVal: Integer
    publicKey, privateKey: Integer 'equivalent to public and private key in cryptography
    tm: Time  ' Get the time and date from the system
    fp: File

    Print "A) Decode a .zen file"
    Print "B) Decode copied text"
    
    Print "Choose an option: "
    Read opt

    CASE OF opt
        Case 'A':
		Case 'a':
            ' GET USER DATA
            Print "ENTER FILE NAME : "
            Read fName
			
			While (strEndsWith(fName, ".zen") <> 1) Do
                Print "*Must be a .zen file"
                Print "ENTER VALID FILE NAME : "
                Read fName
            EndWhile

            If((fp = Open File, fName, for reading) <> NULL) Then
                Read inputStr, from file, fp
                pass = 1
            Else
				Print "CAN'T OPEN FILE, IT MAY NOT EXIST"
                pass = 0
            EndIf

        Case 'B':
		Case 'b':
            ' GET USER DATA 
            Print "ENTER CODE : "
            Read inputStr
            pass = 1
    EndCASE

    If(pass = 1) Then
        cypher.encoded = inputStr    

        publicKey = inputStr[0]
        privateKey = (publicKey * 5) - publicKey ' key used to decrypt

        For (i = 1 To Length of(inputStr)) DO

            ' get 3 digit ascii code
            asciiValTxt = asciiValTxt + inputStr[i]
            asciiValTxt = asciiValTxt + inputStr[i + 1]
            asciiValTxt = asciiValTxt + inputStr[i + 2]

            If (asciiValTxt = NUMBER_SPECIFIER)
                newTxt = newTxt + inputStr[i + Length of(NUMBER_SPECIFIER)]
                i = i + Length of(NUMBER_SPECIFIER)
            Else
            
                If (sasciiValTxt = SPACE_SPECIFIER)
                    newTxt = newTxt + " "
                    i = i + Length of(SPACE_SPECIFIER)
                Else
                    If (asciiValTxt = SYMBOL_SPECIFIER)
                        newTxt = newTxt + inputStr[i + Length of(SYMBOL_SPECIFIER)]
                        i = i + Length of(SYMBOL_SPECIFIER)
                    Else
                        asciiVal = asciiValTxt As Integer 'change the ascii string to an int
                        asciiVal = asciiVal - privateKey

                        newTxt = newTxt + (asciiVal As Character)

                        i = i + 2 ' skip to next ascii set
                    EndIf
                EndIf
            EndIf

            asciiValTxt = "" 'clear it for next entry
        EndFor

        cypher.original = newTxt 'save encoded text to the structure

        ' Add time/date to the cypher
        If (tm.hour >= 12) Then
            amPm = "PM"
        Else
            amPm = "AM"
        EndIf

        'Format: dd/ mm/ yyyy @ hrs : min
        cypher.dateTime = tm.day, "/", tm.month, "/", tm.year, " @ ", tm.hour, ":", tm.minutes, amPm

        Print "DECODED TEXT: ", cypher.original

        AddToHistory(cypher)
    EndIf
EndDecode

SaveToFile(cypher: TextCypher)
    fName: String
    opt: Character
    fp: File
	Print "ENTER A FILENAME: "
	Read fName

	While (fName = "")
		Print "**ENTER A VALID FILENAME: "
		Read fName
	EndWhile

	fName = fName + ".zen"  'add extension

	If((fp = Open File, fName, for writing) <> NULL)
		Write cypher, To File, fp
	Else
		Print "=( File cannot be saved..."
	EndIf
EndSaveToFile

'--------------------[Cypher History]-----------------------

AddToHistory (newCypher: TextCypher)
    fp: File

    If ((fp = Open File "HISTORY.CYPH" for appending) <> NULL) Then
        Write newCypher, To File, fp
        Close File fp
    Else
        Print "AN ERROR OCCURED..."
    EndIf
EndAddToHistory

ShowHistory ()
    Array list[100]: TextCypher
    fp: File
    i = 0, opt, length, item: Integer

    Print "_________HISTORY_______"

    If ((fp = Open File "HISTORY.CYPH" for reading) <> NULL) Then

        While (NOT EOF fp) Do
            Read list[i], From File fp
            i = i + 1
        EndWhile

        Close File fp

        'DISPLAY
        length = i
        Print "THERE ARE ", length, " ITEM(s)"

        If (length > 0) Then
            For (i = 0 To length) DO
                Print "DATE          : ", list[i].dateTime
                Print "ORIGINAL TEXT : ", list[i].original
                Print "ENCODED TEXT  : ", list[i].encoded
            EndFor

            Print "_______OPTIONS_______"
            Print "DO YOU WISH TO CLEAR HISTORY? [Y/N] "
            Read opt

            If opt = 'Y' OR opt = 'y'
                    Clear()
            EndIf
        EndIf
    Else
        Print "NO HISTORY DATA..."
    EndIf
EndShowHistory

Clear ()
    Delete File "HISTORY.CYPH"
    Print "HISTORY DELETED"
EndClear

'-------------------[String Manipulation]-----------------------

'Function to determine if a string ends with the specified ending
'Returns 1 if the ending matches, else 0
strEndsWith(str: String, ending: String): Integer
    i, j, result: Integer
    j = Length of str

    For (i = Length of(ending) To 0) Do
        If (str[j] = ending[i] AND result <> 0) Then
            result = 1
        Else
            result = 0
        EndIf
        j = j - 1
    EndFor

    return result
EndstrEndsWith
