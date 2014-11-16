UNIT NestingParserUnit;
INTERFACE
USES
  StackUnit;

  FUNCTION AddElement(NewElt: ValueType): BOOLEAN;
  FUNCTION CheckSuccess(): BOOLEAN;

IMPLEMENTATION

TYPE 
  Elements = SET OF ValueType;
VAR
  LastNone, LastRecord, LastRepeat, LastIf, LastThen, LastBegin, OpenElt, CloseElt: Elements;

PROCEDURE PrintValue(val: ValueType);
BEGIN {PrintValue}
  CASE val OF
    RepeatV: WRITELN('Repeat');
    UntilV:  WRITELN('until');
    IfV:     WRITELN('If');
    ThenV:   WRITELN('Then');
    ElseV:   WRITELN('Else');
    BeginV:  WRITELN('Begin');
    EndV:    WRITELN('End');
    RecordV: WRITELN('Record');
    NoneV:   WRITELN('None');
  END;
END; {PrintValue}

FUNCTION GetElementsSetByElt(NewElt: ValueType): Elements;
BEGIN {GetElementsSetByElt}
  IF NewElt = NoneV
  THEN
    GetElementsSetByElt := LastNone
  ELSE IF NewElt = RecordV
  THEN
    GetElementsSetByElt := LastRecord
  ELSE IF NewElt = RepeatV
  THEN
    GetElementsSetByElt := LastRepeat
  ELSE IF NewElt = IfV
  THEN
    GetElementsSetByElt := LastIf
  ELSE IF NewElt = ThenV
  THEN
    GetElementsSetByElt := LastThen
  ELSE IF NewElt = BeginV
  THEN
    GetElementsSetByElt := LastBegin

END; {GetElementsSetByElt}

FUNCTION GetCurrElementsSet(): Elements;
VAR
  LastElt: ValueType;
BEGIN {GetElementsSet}
  LastElt := GetLastVal();
  IF LastElt = ThenV
  THEN
    GetCurrElementsSet := GetElementsSetByElt(LastElt) + GetElementsSetByElt(GetPreLastVal())
  ELSE
    GetCurrElementsSet := GetElementsSetByElt(LastElt)
END; {GetElementsSet}

PROCEDURE UpdateStack(NewElt: ValueType);
VAR
  Buff: ValueType;
BEGIN {UpdateStack}
  IF NewElt IN OpenElt
  THEN
    Push(NewElt)
  ELSE IF NewElt IN CloseElt
  THEN
    IF (GetLastVal() = ThenV) AND (NewElt <> ElseV)
    THEN
      BEGIN
        Pop(Buff); 
        Pop(Buff)
      END
    ELSE
      Pop(Buff);

  IF NewElt = ThenV
  THEN
    Push(NewElt);
END; {UpdateStack}

FUNCTION AddElement(NewElt: ValueType): BOOLEAN;
BEGIN {AddElement}
  WRITELN(OUTPUT, '-------1');
  PrintValue(NewElt);
  WRITELN(OUTPUT, '-------2');
  Trace(OUTPUT);    
  AddElement := TRUE;
  IF NewElt <> NoneV
  THEN
    IF NOT(NewElt IN GetCurrElementsSet())
    THEN
      AddElement := FALSE
  ELSE
    UpdateStack(NewElt);
  WRITELN(OUTPUT, '-------3');
  Trace(OUTPUT); 
END; {AddElement}

FUNCTION CheckSuccess(): BOOLEAN;
BEGIN {CheckSuccess}
  CheckSuccess := CheckStackNestyEmpty();
END; {CheckSuccess}

BEGIN {NestingParser}
  LastNone   := [RepeatV, IfV, BeginV, RecordV];
  LastRecord := [EndV];
  LastRepeat := [BeginV, IfV, UntilV];
  LastIf     := [ThenV];
  LastThen   := [BeginV, RepeatV, ElseV, Ifv];
  LastBegin  := [RepeatV, IfV, BeginV, EndV];
  OpenElt    := [RepeatV, IfV, BeginV, RecordV];
  CloseElt   := [UntilV, ThenV, ElseV, EndV];
END. {NestingParser}           