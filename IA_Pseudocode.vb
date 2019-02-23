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

    If((fp = Open File "HISTORY.CYPH" for reading) <> NULL) Then

        While(Not End Of File fp) Do
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

-------------------[StringManipulator.c]-----------------------
