{
   Усков Иван

   Задан  текстовый  файл. Каждая строка содержит не более 
   255 символов. Создать  новый  файл,  в  котором  строки  будут
   следовать в обратном порядке. Размер файла  не  ограничивается.

   Программа принимает два аргумента:
     1 - имя реверсируемого файла
     2 - имя выходного файла 
}
PROGRAM ReversInputToOutput(INPUT, OUTPUT);
USES 
  sysutils;
VAR
  Fin, Fout: TEXT;
  Buffer: FILE OF STRING;
  S: STRING;
  StartTime: TDateTime;
  I: LONGINT;
BEGIN
  StartTime := Time;
  IF ParamCount < 2 
  THEN
    BEGIN
      WRITELN('Please enter parameters!');
      EXIT;
    END;   
  ASSIGN(Fin, ParamStr(1));
  {$I-}     
  RESET(Fin);
  {$I+}     
  IF IoResult <> 0 
  THEN 
    BEGIN
      WRITELN(OUTPUT, 'Please enter parameters!', ParamStr(1));
      EXIT
    END;
  ASSIGN(Fout, ParamStr(2));
  REWRITE(Fout);
  ASSIGN(Buffer, 'buffer.txt');  
  REWRITE(Buffer);
  WHILE NOT EOF(Fin)
  DO
    BEGIN
      READLN(Fin, S);
      WRITE(Buffer, S)
    END;
  CLOSE(Buffer);
  RESET(Buffer);
  FOR I := FileSize(buffer) - 1 DOWNTO 0
  DO
    BEGIN
      SEEK(buffer, I);
      READ(buffer, S);
      WRITELN(Fout, S)
    END;
  CLOSE(Buffer);
  ERASE(Buffer);
  CLOSE(Fin);
  CLOSE(Fout);
  WRITELN(OUTPUT, 'Runtime is : ', TimeToStr(Time - StartTime))
END.