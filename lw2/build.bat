del CheckNesting.exe
call C:\lng\FPC\bin\i386-win32\ppc386.exe CheckNesting.pas > "!compile.log"
IF NOT ERRORLEVEL 1 del "!compile.log"
del CheckNesting.o 
del Stack.o 
del Stack.ppu 
del CharBuffer.o 
del CharBuffer.ppu 
del CharBufferUnit.o 
del StackUnit.o 
del CharBufferUnit.ppu 
del StackUnit.ppu 
del NestingParserUnit.o 
del NestingParserUnit.ppu 