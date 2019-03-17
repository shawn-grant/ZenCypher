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

SPACE_SPECIFIER = "|": Constant String
NUMBER_SPECIFIER = "[N]": Constant String
SYMBOL_SPECIFIER = "[@]": Constant String

INCREMENT = 5: Constant Integer
UPPER =  9: Constant Integer
LOWER = 2: Constant Integer

Encode(cypher: TextCypher)
    inputStr, newTxt = "", amPm, asciiValTxt: String
    i, asciiVal: Integer
    ' [C specific code] Get the time and date from the system
    tm = Get system time: Time

    publicKey, privateKey: Integer 'equivalent to public and private key in cryptography

    publicKey = Random between UPPER AND LOWER 
    privateKey = (publicKey * 5) - publicKey ' key used to encrypt

    ' Add the public key to the text
    newTxt[0] = publicKey 

    ' '''' GET USER DATA '''''

    Print "ENTER RECIPIENT USERNAME:"
    Read cypher.reciever

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

            If(asciiVal < 100) 'add 0 before to ensure groups of 3 digits 
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
    cypher.dateTime = tm.day + "/" + tm.month + "/" + tm.year + " @ " + tm.hour + ":" + tm.minutes

    'add recipient name to the coded string here

    Print "ENCODED TEXT: ", cypher.encoded

    AddToHistory(cypher)

EndEncode

Decode(cypher: TextCypher)
    inputStr, newTxt = "", amPm, asciiValTxt: String
    i, asciiVal: Integer
    publicKey, privateKey: Integer 'equivalent to public and private key in cryptography

    publicKey = Random between UPPER AND LOWER 
    privateKey = (publicKey * 5) - publicKey ' key used to encrypt

    ' '''' GET USER DATA '''''/

    Print "ENTER CODE : "
    Read inputStr

    cypher.encoded = inputStr

    publicKey = inputStr[0]
    privateKey = privateKey = (publicKey * 5) - publicKey ' key used to decrypt


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

--------------------[CypherHistory.c]-----------------------

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
    i = 0, opt, length, item: Integer

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
                    Print "Item #: "
                    Read item
                    RemoveItem(item)

                Case 2:
                    Clear()
            EndCASE
        EndIf
    Else
        Print "NO HISTORY DATA..."
    EndIf
EndShowHistory

RemoveItem(item: Integer)
    'remove item from file??
EndRemoveItem

Clear()
    Delete File "HISTORY.CYPH"
EndClear

-------------------[StringManipulator.c]-----------------------

' Appends a character to a string
strAppend(str: String, c: Character)

    str[Length of(str)] = c
    'mark string end (needed in C )
    str[Length of(str) + 1] = '\0' 
EndstrAppend

'Function to determine if a string ends with the specified ending
'Returns 1 if the ending matches, else 0
strEndsWith(str: String, ending: String): Integer
    i, j, result: Integer
    j = Length of str

    For (i = Length of(ending) To 0) Do
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
    len = Length of(subString): Integer
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