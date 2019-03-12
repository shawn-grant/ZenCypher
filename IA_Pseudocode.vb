----------------------[CYPHER.H]----------------------------

'data type to hold the before and after text of an encryption
Record TextCypher
    original: String
    encoded: String
    reciever: String
    dateTime: String
EndTextCypher

'data type to hold the current user
Record User
    username: String
    password: String
EndUser

----------------------[main.c]----------------------------
Driver ()
    userInput: TextCypher
    user: User
    choice: Character

    If (LoginSignUp (user) = 1) Then
        choice = MainMenu ()

        While (choice <> 'F' AND choice <> 'f') DO
            CASE of choice
                Case 'A':
                Case 'a':
                    Encode (userInput)

                Case 'B':
                Case 'b':
                    Decode (userInput)

                Case 'C':
                Case 'c':
                    OpenFromFile ()

                Case 'D':
                Case 'd':
                    ShowHistory ()

                Case 'E':
                Case 'e':
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

MainMenu(): Character
    c: Character

    Print "A) ENCODE A MESSAGE"
    Print "B) DECODE A MESSAGE"
    Print "C) NEW FROM FILE"
    Print "D) SHOW HISTORY"
    Print "E) UPDATE LOGIN INFO"
    Print "F) EXIT"

    Print "CHOOSE AN OPTION ABOVE: "
    Read c

    return c
EndMainMenu

-------------------[EncoderDecoder.c]-----------------------
SPACE_SPECIFIER = "<[S]>": Constant String
NUMBER_SPECIFIER = "<[N]>": Constant String
SYMBOL_SPECIFIER = "<[@]>": Constant String

INCREMENT = 5: Constant Integer
UPPER = 10: Constant Integer
LOWER = 2: Constant Integer

Encode()

EndEncode

Decode()

EndDecode

SaveToFile(cypher: TextCypher)
    fName: String
    fp: File

    Print "ENTER A FILENAME: "
    Read fName

    While(fName = "")
        Print "**ENTER A VALID FILENAME: "
        Read fName
    EndWhile

    fName = fName + ".cyph" 'add extension

    If((fp = Open File, fName, for writing) <> NULL)
        Write cypher, To File, fp
    Else
        Print "=( File cannot be saved..."
    EndIf
EndSaveToFile

-------------------[CypherHistory.c]-----------------------
AddToHistory (newCypher: TextCypher)
    fp: File

    If((fp = Open File "HISTORY.CYPH" for appending) <> NULL) Then
        Write newCypher, To File, fp
        Close File fp
    Else
        Print "AN ERROR OCCURED..."
    EndIf
EndAddToHistory

ShowHistory ()
    Array list[100]: TextCypher
    fp: File
    i = 0, opt, length: Integer

    Print "_________HISTORY_______"

    If ((fp = Open File "HISTORY.CYPH" for reading) <> NULL) Then

        While (NOT EOF fp) Do
            Read list[i], From File fp
            i = i + 1
        EndWhile

        Close File, fp

        'DISPLAY
        length = i - 1 
        Print "THERE ARE ", length, " ITEM(s)"

        If (length > 0) Then
            For (i = 0 To length) Do
                Print "DATE          : ", list[i].dateTime
                Print "ORIGINAL TEXT : ", list[i].original
                Print "ENCODED TEXT  : ", list[i].encoded
                Print "RECIPIENT     : ", list[i].reciever
            EndFor

            Print "_______OPTIONS_______"
            Print "1) DELETE ITEM"
            Print "2) CLEAR HISTORY"
            
            Print "Choose an option: "
            Read opt

            CASE OF opt
                Case 1:
                    RemoveItem()

                Case 2:
                    Clear()
            EndCASE
        EndIf
    Else
        Print "NO HISTORY DATA..."
    EndIf
EndShowHistory

RemoveItem(item: Integer)
    'remove item
EndRemoveItem

Clear()
    Delete File "HISTORY.CYPH"
EndClear

-------------------[StringManipulator.c]-----------------------

'Function to determine if a string ends with the specified ending
'Returns 1 if the ending matches, else 0
strEndsWith(str: String, ending: String): Integer
    i, j, result: Integer
    j = Length of str

    For (i = Length of ending To 0) Do
        If(str[j] = ending[i] AND result <> 0) Then
            result = 1
        Else
            result = 0
        EndIf
        j = j - 1
    EndFor

    return result
EndstrEndsWith

strPresentAtIndex(text: String, subString: String, at: Integer): Integer
    i, j: Integer
    len = Length of subString: Integer
    result: Integer

    For(i = 0 To len-1) Do
        If(text[at + i] = subString[j] AND result <> 0)
            result = 1
        Else
            result = 0
        EndIf

        j = j + 1
    EndFor

    return result
EndstrPresentAtIndex

'Find the index of a character in a string
strIndexOf(of: Character, in: String): Integer
    index = 0: Integer

    While (in[index] <> of)
        index = index + 1
    EndWhile

    return index
EndstrIndexOf