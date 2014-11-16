{
    Усков Иван, Лабораторная работа "Линейные Списки"

    25. Программа на ПАСКАЛЕ включает такие  сочетания ключевых
    слов,    как    REPEAT..UNTIL,   IF..THEN..ELSE,   BEGIN..END,
    RECORD..END. Конец оператора  определяется  точкой  с  запятой 
    (";").  Требуется  проверить  правильность  вложенности данных
    конструкций с учетом допустимости взаимных вложений.

    Компилятор FreePascal

}
PROGRAM CheckNesting(INPUT, OUTPUT);
USES
  CharBufferUnit, NestingParserUnit, StackUnit;
VAR
  Ch: CHAR;
  Parsing: BOOLEAN;
  StringsCount: INTEGER;
FUNCTION ProcessStatus(): BOOLEAN;
VAR
  BuffVal: ValueType;
BEGIN {ProcessStatus}
  IF CheckREPEAT()
  THEN
    ProcessStatus := AddElement(StackUnit.RepeatV)
  ELSE IF CheckUNTIL()
  THEN 
    ProcessStatus := AddElement(StackUnit.UntilV)
  ELSE IF CheckRECORD()
  THEN
    ProcessStatus := AddElement(StackUnit.RecordV)
  ELSE IF CheckIF()
  THEN
    ProcessStatus := AddElement(StackUnit.IfV)
  ELSE IF CheckTHEN()
  THEN 
    ProcessStatus := AddElement(StackUnit.ThenV)
  ELSE IF CheckELSE()
  THEN
    ProcessStatus := AddElement(StackUnit.ElseV)
  ELSE IF CheckEND()
  THEN
      ProcessStatus := AddElement(StackUnit.EndV)
  ELSE IF CheckBEGIN()
  THEN
    ProcessStatus := AddElement(StackUnit.BeginV)
  ELSE
    ProcessStatus := TRUE
END; {ProcessStatus}

BEGIN {CheckNesting}
  Parsing := TRUE;
  StringsCount := 1;
  WHILE NOT EOF(INPUT) AND Parsing
  DO
    BEGIN
      WHILE NOT EOLN(INPUT) AND Parsing
      DO
        BEGIN
          READ(INPUT, Ch);
          Add(Ch);
          Parsing := ProcessStatus();
        END; 
      Add(CharBufferUnit.NEW_LINE_SYMBOL);
      Parsing := ProcessStatus();
      INC(StringsCount);
      READLN(INPUT)
    END;
  IF Parsing AND CheckSuccess()
  THEN
    WRITELN('True')
  ELSE
    WRITELN('False, on string: ', StringsCount - 1);
END. {CheckNesting}

  