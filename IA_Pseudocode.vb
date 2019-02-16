'data type to hold the before and after text of an encryption
Record TextCypher
    original: String
    encoded: String
    reciever: String
EndTextCypher

'data type to hold the current user
Record User
    username: String
    password: String
EndUser

Driver()
    userInput: TextCypher
    user: User
    choice: Character

    LoginSignUp (user)

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
                OpenFromFile ()

            Case 'D':
            Case 'd':
                ShowHistory ()

            Default
                Print "INVALID OPTION!"
        EndCase

        choice = MainMenu ()
    EndWhile

    GoodBye ()
EndDriver

LoginSignUp ( user: User)
    nameOnFile, passwordOnFile: String
    fp: FILE

    If ((fp = Open "userData.dat" for reading + writing)) <> NULL) Then
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
        EndIf

        Close File, fp
    Else
        Print "CANNOT LOAD USER DATA... RESTART THE PROGRAM"
    EndIf
EndLoginSignUp

MainMenu(): Character
    c: Character

    Print "A) ENCODE A MESSAGE"
    Print "B) DECODE A MESSAGE"
    Print "C) NEW FROM FILE"
    Print "D) SHOW HISTORY"
    Print "E) EXIT"

    Print "CHOOSE AN OPTION ABOVE: "
    Read c

    return c
EndMainMenu