UNIT StackUnit;
INTERFACE
TYPE
  ValueType = (RepeatV, UntilV, IfV, ThenV, ElseV, BeginV, EndV, RecordV, NoneV);

  FUNCTION Push(VAR Val: ValueType): BOOLEAN;
  FUNCTION Pop(VAR Val: ValueType): BOOLEAN;
  PROCEDURE Trace(VAR Fout: TEXT);
  FUNCTION IsEmpty(): BOOLEAN;
  FUNCTION GetLastVal(): ValueType;
  FUNCTION GetPreLastVal(): ValueType;
  FUNCTION CheckStackNestyEmpty(): BOOLEAN;

IMPLEMENTATION
TYPE
  ElementType = RECORD
                  val: ValueType;
                  prev: ^ElementType			
                END;
VAR
  StackPtr: ^ElementType;

FUNCTION IsEmpty(): BOOLEAN;
BEGIN {IsEmpty}
  IsEmpty := (StackPtr = NIL);
END; {IsEmpty}

FUNCTION Push(VAR Val: ValueType): BOOLEAN;
VAR 
  ElementPtr: ^ElementType;
BEGIN {Push}
  NEW(ElementPtr);
  ElementPtr^.val := Val;
  ElementPtr^.prev := StackPtr;  
  StackPtr := ElementPtr;
  Push := TRUE
END; {Push}

FUNCTION Pop(VAR Val: ValueType): BOOLEAN;
VAR 
  ElementPtr: ^ElementType;
BEGIN {Pop}
  IF (StackPtr <> NIL)
  THEN
    BEGIN
      ElementPtr := StackPtr;
      Val := ElementPtr^.val;
      Pop := TRUE;
      StackPtr := StackPtr^.prev
    END
  ELSE  
    Pop := FALSE
END; {Pop}

FUNCTION GetLastVal(): ValueType;
BEGIN {GetLastVal}
  IF StackPtr <> NIL
  THEN
    GetLastVal := StackPtr^.val
  ELSE
    GetLastVal := NoneV
END; {GetLastVal}

FUNCTION GetPreLastVal(): ValueType;
BEGIN {GetPreLastVal}
  GetPreLastVal := NoneV;
  IF (StackPtr <> NIL) AND (StackPtr^.prev <> NIL)
  THEN
    GetPreLastVal := StackPtr^.prev^.val
END; {GetLastVal}

PROCEDURE PrintValue(VAR Fout: TEXT; val: ValueType);
BEGIN {PrintValue}
  CASE val OF
    RepeatV: WRITELN(Fout, 'Repeat');
    UntilV:  WRITELN(Fout, 'until');
    IfV:     WRITELN(Fout, 'If');
    ThenV:   WRITELN(Fout, 'Then');
    ElseV:   WRITELN(Fout, 'Else');
    BeginV:  WRITELN(Fout, 'Begin');
    EndV:    WRITELN(Fout, 'End');
    RecordV: WRITELN(Fout, 'Record');
    NoneV:   WRITELN(Fout, 'None');
  END;
END; {PrintValue}

FUNCTION CheckStackNestyEmpty(): BOOLEAN;
VAR
  Success: BOOLEAN;
  ElementPtr: ^ElementType;
BEGIN {CheckStackNestyEmpty}
  Success := TRUE;
  ElementPtr := StackPtr;
  IF NOT IsEmpty()
  THEN
    WHILE (ElementPtr <> NIL) AND Success
    DO
      BEGIN
        Success := (ElementPtr^.val = ThenV);
        ElementPtr := ElementPtr^.prev
      END;
  CheckStackNestyEmpty := Success
END; {CheckStackNestyEmpty}

PROCEDURE Trace(VAR Fout: TEXT);
VAR 
  ElementPtr: ^ElementType;
BEGIN {Trace}
  ElementPtr := StackPtr;
  WHILE ElementPtr <> NIL
  DO
    BEGIN
      PrintValue(Fout, ElementPtr^.val);
      ElementPtr := ElementPtr^.prev
    END
END; {Trace}

BEGIN {StackUnit}
  StackPtr := NIL;
END. {StackUnit}