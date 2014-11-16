UNIT CharBufferUnit;
INTERFACE
USES
  StackUnit;
CONST 
  DEFAULT_SYMBOL  = '@';
  NEW_LINE_SYMBOL = '@';
TYPE
  ElementType = CHAR;

  PROCEDURE Add(NewElt: ElementType);
  PROCEDURE Print(VAR Fout: TEXT);
  PROCEDURE Init;
  FUNCTION CheckREPEAT(): BOOLEAN;
  FUNCTION CheckUNTIL(): BOOLEAN;
  FUNCTION CheckRECORD(): BOOLEAN;
  FUNCTION CheckIF(): BOOLEAN;
  FUNCTION CheckTHEN(): BOOLEAN;
  FUNCTION CheckELSE(): BOOLEAN;
  FUNCTION CheckEND(): BOOLEAN;
  FUNCTION CheckBEGIN(): BOOLEAN;

IMPLEMENTATION
VAR
  Buffer: ARRAY[1..8] OF ElementType;

PROCEDURE Add(NewElt: ElementType);
BEGIN {Add}
  Buffer[1] := Buffer[2];
  Buffer[2] := Buffer[3];
  Buffer[3] := Buffer[4];
  Buffer[4] := Buffer[5];
  Buffer[5] := Buffer[6];
  Buffer[6] := Buffer[7];
  Buffer[7] := Buffer[8];
  Buffer[8] := NewElt
END; {Add}

PROCEDURE Init;
VAR
  I: INTEGER;
BEGIN
  FOR I := 1 TO LENGTH(Buffer)
  DO
    Buffer[I] := DEFAULT_SYMBOL;
END;

PROCEDURE Print(VAR Fout: TEXT);
VAR
  I: INTEGER;
BEGIN {Print}
  FOR I := 1 TO LENGTH(Buffer)
  DO
    WRITE(Fout, Buffer[I]);
  WRITELN(Fout)
END; {Print}

FUNCTION CheckREPEAT(): BOOLEAN;
BEGIN {CheckREPEAT}
  CheckREPEAT := ((Buffer[1] = ' ') OR (Buffer[1] = NEW_LINE_SYMBOL)) AND
                 (Buffer[2] = 'R') AND
                 (Buffer[3] = 'E') AND 
                 (Buffer[4] = 'P') AND
                 (Buffer[5] = 'E') AND
                 (Buffer[6] = 'A') AND
                 (Buffer[7] = 'T') AND
                 ((Buffer[8] = ' ') OR (Buffer[8] = NEW_LINE_SYMBOL));
END; {CheckREPEAT}

FUNCTION CheckUNTIL(): BOOLEAN;
BEGIN {CheckUNTIL}
  CheckUNTIL :=  ((Buffer[2] = ' ') OR (Buffer[2] = NEW_LINE_SYMBOL)) AND
                 (Buffer[3] = 'U') AND 
                 (Buffer[4] = 'N') AND
                 (Buffer[5] = 'T') AND
                 (Buffer[6] = 'I') AND
                 (Buffer[7] = 'L') AND
                 ((Buffer[8] = ' ') OR (Buffer[8] = NEW_LINE_SYMBOL));
END; {CheckUNTIL}

FUNCTION CheckIF(): BOOLEAN;
BEGIN {CheckIF}
  CheckIF :=    ((Buffer[5] = ' ') OR (Buffer[5] = NEW_LINE_SYMBOL)) AND
                 (Buffer[6] = 'I') AND
                 (Buffer[7] = 'F') AND
                ((Buffer[8] = ' ') OR (Buffer[8] = NEW_LINE_SYMBOL));
END; {CheckIF}

FUNCTION CheckTHEN(): BOOLEAN;
BEGIN {CheckTHEN}
  CheckTHEN :=  ((Buffer[3] = ' ') OR (Buffer[3] = NEW_LINE_SYMBOL)) AND
                 (Buffer[4] = 'T') AND
                 (Buffer[5] = 'H') AND
                 (Buffer[6] = 'E') AND
                 (Buffer[7] = 'N') AND
                ((Buffer[8] = ' ') OR (Buffer[8] = NEW_LINE_SYMBOL));
END; {CheckTHEN}

FUNCTION CheckELSE(): BOOLEAN;
BEGIN {CheckELSE}
  CheckELSE :=  ((Buffer[3] = ' ') OR (Buffer[3] = NEW_LINE_SYMBOL)) AND
                 (Buffer[4] = 'E') AND
                 (Buffer[5] = 'L') AND
                 (Buffer[6] = 'S') AND
                 (Buffer[7] = 'E') AND
                ((Buffer[8] = ' ') OR (Buffer[8] = NEW_LINE_SYMBOL));
END; {CheckELSE}

FUNCTION CheckEND(): BOOLEAN;
BEGIN {CheckEND}
  CheckEND :=   ((Buffer[4] = ' ') OR (Buffer[4] = NEW_LINE_SYMBOL)) AND
                 (Buffer[5] = 'E') AND
                 (Buffer[6] = 'N') AND
                 (Buffer[7] = 'D') AND
                ((Buffer[8] = ' ') OR (Buffer[8] = NEW_LINE_SYMBOL));
END; {CheckEND}

FUNCTION CheckRECORD(): BOOLEAN;
BEGIN {CheckRECORD}
  CheckRECORD := ((Buffer[1] = ' ') OR (Buffer[1] = NEW_LINE_SYMBOL)) AND
                 (Buffer[2] = 'R') AND
                 (Buffer[3] = 'E') AND 
                 (Buffer[4] = 'C') AND
                 (Buffer[5] = 'O') AND
                 (Buffer[6] = 'R') AND
                 (Buffer[7] = 'D') AND
                ((Buffer[8] = ' ') OR (Buffer[8] = NEW_LINE_SYMBOL));
END; {CheckRECORD}

FUNCTION CheckBEGIN(): BOOLEAN;
BEGIN {CheckBEGIN}
  CheckBEGIN := ((Buffer[2] = ' ') OR (Buffer[2] = NEW_LINE_SYMBOL)) AND
                 (Buffer[3] = 'B') AND 
                 (Buffer[4] = 'E') AND
                 (Buffer[5] = 'G') AND
                 (Buffer[6] = 'I') AND
                 (Buffer[7] = 'N') AND
                ((Buffer[8] = ' ') OR (Buffer[8] = NEW_LINE_SYMBOL));
END; {CheckBEGIN}

BEGIN {CharBufferUnit}
  Init;
END. {CharBufferUnit}
