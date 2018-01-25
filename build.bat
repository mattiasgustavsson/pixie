@echo off
setlocal

REM ------------------------------------------------------------------------------
REM           Licensing information can be found at the end of the file.
REM ------------------------------------------------------------------------------
REM 
REM Code and data build script by Mattias Gustavsson, developed for Pixie Game System.
REM 

rem Configure whether to build data by default ( set build_data=true ) or not ( set build_data= )
set build_data=true

rem Configure whether to always make a build with a console window ( set force_console=true ) or not ( set force_console= )
set force_console=

rem Determine if launched from commandline or from windows shell
echo %cmdcmdline% | findstr /i /c:"%~nx0" 1>nul && set launched_from_explorer=true 

rem Print help
if [%1]==[/?] (
	echo:
	echo BUILD.BAT - Code and data build script by Mattias Gustavsson, developed for Pixie Game System.
	echo:
	echo SYNTAX:
	echo 	build [ clean ] [ x86 ^| x64 ^| x86 x64 ] [ debug ^| release ^| package ] [ code ^| data ^| code data ]
	echo:
	endlocal
	if defined launched_from_explorer pause	
	goto :eof
)

rem Set current path to that of build.bat
pushd %~dp0

rem Find the name of the folder we are running from.
set "CDIR=%~dp0"
rem for loop requires removing trailing backslash from %~dp0 output
set "CDIR=%CDIR:~0,-1%"
rem extract the last folder name of the path
for %%i in ("%CDIR%") do set "PARENTFOLDERNAME=%%~nxi"

rem Parse command line options
set package=
set clean=
set x86=true
set x64=
set config=release
set code=true
set data=%build_data%
call :parse_commandline %*

rem Print VS version 
setlocal
call :vsvars32
echo Compiler path: %VSINSTALLDIR%
echo.
endlocal

rem Report build settings
if defined package (
	echo|set /p _temp=------ Package started:
) else (
	if defined clean (
		echo|set /p _temp=------ Rebuild started:
	) else (
		echo|set /p _temp=------ Build started:
	)
)
echo|set /p _temp= Project: %PARENTFOLDERNAME%, Configuration: %config% 
if defined x86 (
	if defined x64 (
		echo|set /p _temp= x86 x64
	) else (
		echo|set /p _temp= x86
	)
) else (
	if defined x64 (
		echo|set /p _temp= x64
	)
)
if defined code (
	if defined data (
		echo|set /p _temp=, Code and Data
	) else ( 
		echo|set /p _temp=, Code only
	)
) else (
	if defined data (
		echo|set /p _temp=, Data only
	)
)
echo: ------

rem Clean

if defined clean (
	if defined x86 (
		del /q .build_temp\%config%\x86\*.* 2> nul
		if %config%==debug (
			del /q .runtime\%PARENTFOLDERNAME%_debug.exe 2> nul
			del /q .runtime\%PARENTFOLDERNAME%_debug.ilk 2> nul
			del /q .runtime\%PARENTFOLDERNAME%_debug.pdb 2> nul
		)
		if %config%==release (
			del /q .runtime\%PARENTFOLDERNAME%.exe 2> nul
		)
	)
	if defined x64 (
		del /q .build_temp\%config%\x64\*.* 2> nul
		if %config%==debug (
			del /q .runtime\%PARENTFOLDERNAME%_debug_x64.exe 2> nul
			del /q .runtime\%PARENTFOLDERNAME%_debug_x64.ilk 2> nul
			del /q .runtime\%PARENTFOLDERNAME%_debug_x64.pdb 2> nul
		)
		if %config%==release (
			del /q .runtime\%PARENTFOLDERNAME%_x64.exe 2> nul
		)
	)
	if defined data (
		del /q /s .build_temp\build_data >nul 2> nul 
		rd /q /s .build_temp\build_data >nul 2> nul 
		del /q /s .build_temp\data >nul 2> nul 
		rd /q /s .build_temp\data >nul 2> nul 
		del /q /s .runtime\data >nul 2> nul 
		rd /q /s .runtime\data >nul 2> nul 
		del /q /s .runtime\.* >nul 2> nul 
		rd /q /s .runtime\.* >nul 2> nul 
		del /q /s .runtime\data.dat >nul 2> nul
	)
)

if defined package (
	del /q /s .runtime\*.exe >nul 2> nul 
	del /q /s .runtime\*.pdb >nul 2> nul 
	del /q /s .runtime\*.ilk >nul 2> nul 
	FOR /D %%G IN (".runtime\.*.*") DO del /q /s %%G >nul 2> nul
	FOR /D %%G IN (".runtime\.*.*") DO rd /q /s %%G >nul 2> nul 
	if defined data (
		del /q /s .runtime\data >nul 2> nul 
		rd /q /s .runtime\data >nul 2> nul 
		del /q /s .runtime\data.dat >nul 2> nul
	)
)

rem Create temp directories

if not exist .build_temp mkdir .build_temp
if not exist .build_temp\build_data mkdir .build_temp\build_data
if not exist .build_temp\seticon mkdir .build_temp\seticon
if not exist .build_temp\%config% mkdir .build_temp\%config%
if defined x86 (
	if not exist .build_temp\%config%\x86 mkdir .build_temp\%config%\x86
)
if defined x64 (
	if not exist .build_temp\%config%\x64 mkdir .build_temp\%config%\x64
)


if not exist .runtime mkdir .runtime

rem Compile and link

set subsystem_win=/SUBSYSTEM:WINDOWS
if defined force_console set subsystem_win=/SUBSYSTEM:CONSOLE

if %config%==debug (
	set CONFIG_FLAGS=/Od /MTd /D "_DEBUG" /Gm /Zi 
	set LINKER_FLAGS=/INCREMENTAL /SUBSYSTEM:CONSOLE
	set EXE_NAME=%PARENTFOLDERNAME%_debug
)
if %config%==release (
	set CONFIG_FLAGS=/Ox /Ob2 /Oi /Ot /Oy /MT /GL /GF /D "NDEBUG" 
	set LINKER_FLAGS=/INCREMENTAL:NO /OPT:REF /OPT:ICF /LTCG %subsystem_win%
	set EXE_NAME=%PARENTFOLDERNAME%
)

rem The following warnings are of an informational nature, and are always disabled.
rem Other warnings should be disabled by #pragma directives in the code, if necessary.
rem C4514: 'function' : unreferenced inline function has been removed
rem C4710: 'function' : function not inlined
rem C4711: function 'function' selected for inline expansion
rem C4738: storing 32-bit float result in memory, possible loss of performance
rem C4820: 'bytes' bytes padding added after construct 'member_name'
set WARNING_FLAGS=/Wall /wd 4514 /wd 4710 /wd 4711 /wd 4738 /wd 4820 /WX

if %config%==release if not exist .build_temp\seticon\seticon.exe call :build_seticon

for %%F in (*.ico) do (
	set ico_file=%%F
	goto exit_for_loop
)
:exit_for_loop

if defined PIXIE_DIR set INCLUDE_PIXIE=/I "%PIXIE_DIR%"
if defined PGS_DIR set INCLUDE_PGS=/I "%PGS_DIR%"

if not exist "%ico_file%" ( if defined PGS_DIR ( if exist "%PGS_DIR%\pixie_game_system.ico" set ico_file="%PGS_DIR%\pixie_game_system.ico" ) )

if defined code call :build_code

if defined data (
	if not exist .build_temp\build_data\build_data.exe call :build_build_data
	pushd .runtime
	call ..\.build_temp\build_data\build_data.exe -build
	popd
)


if defined package call :package

echo Done.
if defined launched_from_explorer pause	
popd
endlocal
goto :eof


:build_code
	if defined x86 call :build_x86
	if defined x64 call :build_x64
	goto :eof
	
:build_x86
	setlocal
	call :vsvars32
	cl source\*.c* %INCLUDE_PIXIE% %INCLUDE_PGS% /Fe".runtime\%EXE_NAME%.exe" /Fo.build_temp\%config%\x86\ /nologo /Fd.build_temp\%config%\x86\ %CONFIG_FLAGS% /arch:SSE2 /Zc:forScope %WARNING_FLAGS% %extraflags% /link %LINKER_FLAGS%%LINKER_VER% /MACHINE:X86
	endlocal
	if exist "%ico_file%" ( if %config%==release .build_temp\seticon\seticon.exe ".runtime\%EXE_NAME%.exe" "%ico_file%" )
	if exist .runtime\%EXE_NAME%.exe echo .runtime\%EXE_NAME%.exe
	goto :eof

:build_x64
	setlocal 
	call :vsvars32 amd64
	
	cl source\*.c* %INCLUDE_PIXIE% %INCLUDE_PGS% /Fe".runtime\%EXE_NAME%_x64.exe" /Fo.build_temp\%config%\x64\ /nologo /Fd.build_temp\%config%\x64\ %CONFIG_FLAGS% /Zc:forScope %WARNING_FLAGS% %extraflags%  /D_WIN32_WINNT=0x0600 /link %LINKER_FLAGS%%LINKER_VER% /MACHINE:X64
	endlocal
	if exist "%ico_file%" ( if %config%==release .build_temp\seticon\seticon.exe ".runtime\%EXE_NAME%_x64.exe" "%ico_file%" )
	if exist .runtime\%EXE_NAME%_x64.exe echo .runtime\%EXE_NAME%_x64.exe
	goto :eof
	
:build_seticon
	call :write_seticon
	setlocal
	call :vsvars32
	cl .build_temp\seticon\seticon.cpp /Fe".build_temp\seticon\seticon.exe" /Fo.build_temp\seticon\ /Fd.build_temp\seticon\ /nologo /Ox /Ob2 /Oi /Ot /Oy /MT /GL /GF /D "NDEBUG" /arch:SSE2 /Zc:forScope %extraflags% /link /INCREMENTAL:NO /SUBSYSTEM:CONSOLE,5.01 /OPT:REF /OPT:ICF /LTCG /MACHINE:X86
	echo .build_temp\seticon\seticon.exe
	endlocal
	goto :eof
	
:build_build_data
	setlocal
	call :vsvars32
	cl source\*.c* %INCLUDE_PIXIE% %INCLUDE_PGS% /Fe".build_temp\build_data\build_data.exe" /Fo.build_temp\build_data\ /Fd.build_temp\build_data\ /nologo /Ox /Ob2 /Oi /Ot /Oy /MT /GL /GF /D "BUILD_DATA" /D "NDEBUG" /arch:SSE2 /Zc:forScope %extraflags% /link /INCREMENTAL:NO /SUBSYSTEM:CONSOLE /OPT:REF /OPT:ICF /LTCG /MACHINE:X86
	echo .build_temp\build_data\build_data.exe
	endlocal
	goto :eof

	
:initvs
	pushd %*
	if exist "vsvars32.bat" call "vsvars32.bat" 1>nul
	if exist "vsdevcmd.bat" call "vsdevcmd.bat" 1>nul
	popd
	if not errorlevel 1 goto :eof
	popd
	if defined launched_from_explorer pause	
	endlocal
	EXIT /B
	

:xp_toolset
	set INCLUDE=%ProgramFiles(x86)%\Microsoft SDKs\Windows\7.1A\Include;%INCLUDE%
	set PATH=%ProgramFiles(x86)%\Microsoft SDKs\Windows\7.1A\Bin;%PATH%
	if defined x86 set LIB=%ProgramFiles(x86)%\Microsoft SDKs\Windows\7.1A\Lib;%LIB%
	if defined x64 set LIB=%ProgramFiles(x86)%\Microsoft SDKs\Windows\7.1A\Lib\x64;%LIB%
	if defined x86 set LINKER_VER=,5.01
	if defined x64 set LINKER_VER=,5.02
	goto :eof
	
	
:vsvars32
	set VCINSTALLDIR=
	if defined VS150COMNTOOLS call :initvs %VS150COMNTOOLS% & call :xp_toolset
	if defined VCINSTALLDIR goto :vsvars32_done            
	if defined VS140COMNTOOLS call :initvs %VS140COMNTOOLS% & call :xp_toolset 
	if defined VCINSTALLDIR goto :vsvars32_done            
	if defined VS130COMNTOOLS call :initvs %VS130COMNTOOLS% & call :xp_toolset
	if defined VCINSTALLDIR goto :vsvars32_done            
	if defined VS120COMNTOOLS call :initvs %VS120COMNTOOLS% & call :xp_toolset
	if defined VCINSTALLDIR goto :vsvars32_done            
	if defined VS110COMNTOOLS call :initvs %VS110COMNTOOLS% & call :xp_toolset
	if defined VCINSTALLDIR goto :vsvars32_done
	if defined VS100COMNTOOLS call :initvs %VS100COMNTOOLS%
	if defined VCINSTALLDIR goto :vsvars32_done
	if defined VS90COMNTOOLS call :initvs %VS90COMNTOOLS%
	if defined VCINSTALLDIR goto :vsvars32_done
	if defined VS80COMNTOOLS call :initvs %VS80COMNTOOLS%
	if defined VCINSTALLDIR goto :vsvars32_done
	set libcfg=
	if %config%==debug set libcfg=d
	if defined VS71COMNTOOLS call :initvs %VS71COMNTOOLS% & set extraflags=/Og /Wp64 /MT%libcfg%
	if defined VCINSTALLDIR goto :vsvars32_done
	if defined VS70COMNTOOLS call :initvs %VS70COMNTOOLS% & set extraflags=/Og /Wp64 /MT%libcfg%
	if defined VCINSTALLDIR goto :vsvars32_done
	if defined VS60COMNTOOLS call :initvs %VS60COMNTOOLS%
	if defined VCINSTALLDIR goto :vsvars32_done
	goto :eof
	:vsvars32_done
		if exist "%VCINSTALLDIR%\vcvarsall.bat" call "%VCINSTALLDIR%\vcvarsall.bat" %1 1>nul
		if exist "%VCINSTALLDIR%\Auxiliary\Build\vcvarsall.bat" call "%VCINSTALLDIR%\Auxiliary\Build\vcvarsall.bat" %1 1>nul	
		if defined VCINSTALLDIR goto :eof
		echo Visual Studio is not installed. Aborting.
		popd
		if defined launched_from_explorer pause	
		endlocal
		EXIT /B


:package
	echo Packaging into %PARENTFOLDERNAME%.zip
	del /q %PARENTFOLDERNAME%.zip 2> nul
	echo. 																																	> .build_temp\zip.vbs
	echo Set objArgs = WScript.Arguments 																								 	>> .build_temp\zip.vbs
	echo Set FS = CreateObject("Scripting.FileSystemObject")  																				>> .build_temp\zip.vbs
	echo InputFolder = FS.GetAbsolutePathName(objArgs(0))																					>> .build_temp\zip.vbs
	echo ZipFile = FS.GetAbsolutePathName(objArgs(1))                                                                              			>> .build_temp\zip.vbs
	echo CreateObject("Scripting.FileSystemObject").CreateTextFile(ZipFile, True).Write "PK" ^& Chr(5) ^& Chr(6) ^& String(18, vbNullChar)  >> .build_temp\zip.vbs
	echo Set objShell = CreateObject("Shell.Application")                                                                          			>> .build_temp\zip.vbs
	echo Set source = objShell.NameSpace(InputFolder).Items                                                                                	>> .build_temp\zip.vbs
	echo objShell.NameSpace(ZipFile).CopyHere(source)																						>> .build_temp\zip.vbs
	echo Do Until objShell.NameSpace(InputFolder).Items.Count ^<= objShell.NameSpace(ZipFile).Items.Count : Wscript.Sleep(200) : Loop		>> .build_temp\zip.vbs
	echo wScript.Sleep 2000																													>> .build_temp\zip.vbs
	cscript /nologo .build_temp\zip.vbs .runtime %PARENTFOLDERNAME%.zip
	goto :eof
	
:parse_commandline	
	if [%1]==[clean] (
		set clean=true 
		shift
	)
	if [%1]==[x86] (
		set x86=true 
		set x64=
		if [%2]==[x64] (
			set x64=true
			shift
		)
		shift
	)
	if [%1]==[x64] (
		set x86=
		set x64=true
		if [%2]==[x86] (
			set x86=true
			shift
		)
		shift
	)

	if [%1]==[debug] (
		set config=debug
		set data=
		shift
	)
	if [%1]==[release] (
		set config=release
		set data=
		shift
	)
	if [%1]==[package] (
		set config=package
		shift
	)

	if [%1]==[code] (
		set code=true 
		set data=
		if [%2]==[data] (
			set data=%build_data%
			shift
		)
		shift
	)
	if [%1]==[data] (
		set code=
		set data=%build_data%
		if [%2]==[code] (
			set code=true
			shift
		)
		shift
	)
	
	if %config%==package (
		set package=true
		set config=release
		set code=true
		set data=%build_data%
		set clean=true
	)

	goto :eof

	
:write_seticon
	echo. 																																							 > .build_temp\seticon\seticon.cpp
	echo #define _CRT_SECURE_NO_WARNINGS																															>> .build_temp\seticon\seticon.cpp
	echo #include ^<stdio.h^>                                                                                                                                       >> .build_temp\seticon\seticon.cpp
	echo #pragma warning( push )                                                                                                                                    >> .build_temp\seticon\seticon.cpp
	echo #pragma warning( disable: 4668 )                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo #pragma warning( disable: 4255 )                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo #include ^<windows.h^>                                                                                                                                     >> .build_temp\seticon\seticon.cpp
	echo #pragma warning( pop )                                                                                                                                     >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo int main( int argc, char** argv )                                                                                                                          >> .build_temp\seticon\seticon.cpp
	echo 	{                                                                                                                                                       >> .build_temp\seticon\seticon.cpp
	echo     if( argc != 3 ) return 1; char const* exe_file = argv[ 1 ]; char const* icon_file = argv[ 2 ];                                                         >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo     HANDLE hUpdateRes = BeginUpdateResourceA( exe_file, FALSE );                                                                                           >> .build_temp\seticon\seticon.cpp
	echo 	if( hUpdateRes == NULL ) { printf( "seticon: Failed to open exe file: %%s\n", exe_file ); return 1; }		                                            >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo     FILE* fp = fopen( icon_file, "rb" );                                                                                                                   >> .build_temp\seticon\seticon.cpp
	echo 	if( !fp ) { printf( "seticon: Failed to open icon file: %%s\n", icon_file ); return 1; }                                                                >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo 	struct ICONHEADER { WORD reserved, type, count; } header;                                                                                               >> .build_temp\seticon\seticon.cpp
	echo 	fread( ^&header, sizeof( header ), 1, fp );                                                                                                             >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo     struct ICONENTRY { BYTE width, height, colorCount, reserved; WORD planes, bitCount; DWORD bytesInRes, imageOffset; };	                                >> .build_temp\seticon\seticon.cpp
	echo 	ICONENTRY* entries = (ICONENTRY*) malloc( header.count * sizeof( ICONENTRY ) );                                                                         >> .build_temp\seticon\seticon.cpp
	echo 	fread( entries, header.count * sizeof( ICONENTRY ), 1, fp );                                                                                            >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo     #pragma pack(push,2)                                                                                                                                   >> .build_temp\seticon\seticon.cpp
	echo     struct GRPICONENTRY { BYTE width, height, colourCount, reserved, planes, bitCount; WORD bytesInRes, bytesInRes2, reserved2, id; };                     >> .build_temp\seticon\seticon.cpp
	echo     #pragma pack(pop)                                                                                                                                      >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo     #pragma pack(push,2)                                                                                                                                   >> .build_temp\seticon\seticon.cpp
	echo     struct GRPICONHEADER { WORD reserved, type, count; GRPICONENTRY entries[1]; };                                                                         >> .build_temp\seticon\seticon.cpp
	echo     #pragma pack(pop)                                                                                                                                      >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo     size_t total_size = sizeof( GRPICONHEADER ) + ( header.count - 1 ) * sizeof( GRPICONENTRY );                                                           >> .build_temp\seticon\seticon.cpp
	echo     size_t max_size = total_size;                                                                                                                          >> .build_temp\seticon\seticon.cpp
	echo     for( int i = 0; i ^< header.count; ++i )                                                                                                               >> .build_temp\seticon\seticon.cpp
	echo         max_size = entries[ i ].bytesInRes ^> max_size ? entries[ i ].bytesInRes : max_size;                                                               >> .build_temp\seticon\seticon.cpp
	echo 	void* data = malloc( max_size );                                                                                                                        >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo     GRPICONHEADER* grpheader = (GRPICONHEADER*)data;                                                                                                       >> .build_temp\seticon\seticon.cpp
	echo     grpheader-^>reserved = 0; grpheader-^>type = 1; grpheader-^>count = header.count;                                                                      >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo     for( int i = 0; i ^< header.count; ++i )                                                                                                               >> .build_temp\seticon\seticon.cpp
	echo         {                                                                                                                                                  >> .build_temp\seticon\seticon.cpp
	echo         GRPICONENTRY* entry = grpheader-^>entries + i;                                                                                                     >> .build_temp\seticon\seticon.cpp
	echo         entry-^>bitCount = 0;                                                                                                                              >> .build_temp\seticon\seticon.cpp
	echo         entry-^>bytesInRes = entries[ i ].bitCount;                                                                                                        >> .build_temp\seticon\seticon.cpp
	echo         entry-^>bytesInRes2 = (WORD) entries[ i ].bytesInRes;                                                                                              >> .build_temp\seticon\seticon.cpp
	echo         entry-^>colourCount = entries[ i ].colorCount;                                                                                                     >> .build_temp\seticon\seticon.cpp
	echo         entry-^>height = entries[ i ].height;                                                                                                              >> .build_temp\seticon\seticon.cpp
	echo         entry-^>id = (WORD)( i + 1 );                                                                                                                      >> .build_temp\seticon\seticon.cpp
	echo         entry-^>planes = (BYTE) entries[ i ].planes;                                                                                                       >> .build_temp\seticon\seticon.cpp
	echo         entry-^>reserved = entries[ i ].reserved;                                                                                                          >> .build_temp\seticon\seticon.cpp
	echo         entry-^>width = entries[ i ].width;                                                                                                                >> .build_temp\seticon\seticon.cpp
	echo         entry-^>reserved2 = 0;                                                                                                                             >> .build_temp\seticon\seticon.cpp
	echo         }                                                                                                                                                  >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo     #define ICON MAKEINTRESOURCEA( 3 )                                                                                                                     >> .build_temp\seticon\seticon.cpp
	echo     #define GROUP_ICON MAKEINTRESOURCEA( (ULONG_PTR)( ICON ) + DIFFERENCE )                                                                                >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo 	BOOL result = UpdateResourceA( hUpdateRes, GROUP_ICON, MAKEINTRESOURCEA( 1 ), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), data, (DWORD) total_size );    >> .build_temp\seticon\seticon.cpp
	echo 	if (result == FALSE) { printf( "seticon: Could not add resource.\n" ); return 1; }                                                                      >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo     for( int i = 0; i ^< header.count; ++i )                                                                                                               >> .build_temp\seticon\seticon.cpp
	echo         {                                                                                                                                                  >> .build_temp\seticon\seticon.cpp
	echo 	    fseek( fp, (long)entries[ i ].imageOffset, SEEK_SET );                                                                                              >> .build_temp\seticon\seticon.cpp
	echo 	    size_t sz = entries[ i ].bytesInRes;                                                                                                                >> .build_temp\seticon\seticon.cpp
	echo 	    fread( data, sz, 1, fp );                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo         result = UpdateResourceA( hUpdateRes, ICON, MAKEINTRESOURCEA( i + 1 ),  MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), data, (DWORD)sz );              >> .build_temp\seticon\seticon.cpp
	echo 	    if( result == FALSE ) { printf( "seticon: Could not add resource.\n" ); return 1; }                                                                 >> .build_temp\seticon\seticon.cpp
	echo         }                                                                                                                                                  >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo     free( data );                                                                                                                                          >> .build_temp\seticon\seticon.cpp
	echo 	fclose( fp );                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo   	if( !EndUpdateResourceA( hUpdateRes, FALSE ) ) { printf( "seticon: Could not write changes to file: %%s.\n", exe_file ); return 1; }                    >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp
	echo 	return 0;                                                                                                                                               >> .build_temp\seticon\seticon.cpp
	echo 	}                                                                                                                                                       >> .build_temp\seticon\seticon.cpp
	echo.                                                                                                                                                           >> .build_temp\seticon\seticon.cpp	
	goto :eof


REM ------------------------------------------------------------------------------
REM 
REM This software is available under 2 licenses - you may choose the one you like.
REM 
REM ------------------------------------------------------------------------------
REM 
REM ALTERNATIVE A - MIT License
REM 
REM Copyright (c) 2017 Mattias Gustavsson
REM 
REM Permission is hereby granted, free of charge, to any person obtaining a copy of 
REM this software and associated documentation files (the "Software"), to deal in 
REM the Software without restriction, including without limitation the rights to 
REM use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
REM of the Software, and to permit persons to whom the Software is furnished to do 
REM so, subject to the following conditions:
REM 
REM The above copyright notice and this permission notice shall be included in all 
REM copies or substantial portions of the Software.
REM 
REM THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
REM IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
REM FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
REM AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
REM LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
REM OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
REM SOFTWARE.
REM 
REM ------------------------------------------------------------------------------
REM 
REM ALTERNATIVE B - Public Domain (www.unlicense.org)
REM 
REM This is free and unencumbered software released into the public domain.
REM 
REM Anyone is free to copy, modify, publish, use, compile, sell, or distribute this 
REM software, either in source code form or as a compiled binary, for any purpose, 
REM commercial or non-commercial, and by any means.
REM 
REM In jurisdictions that recognize copyright laws, the author or authors of this 
REM software dedicate any and all copyright interest in the software to the public 
REM domain. We make this dedication for the benefit of the public at large and to 
REM the detriment of our heirs and successors. We intend this dedication to be an 
REM overt act of relinquishment in perpetuity of all present and future rights to 
REM this software under copyright law.
REM 
REM THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
REM IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
REM FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
REM AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
REM ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
REM WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
REM 
REM ------------------------------------------------------------------------------

	