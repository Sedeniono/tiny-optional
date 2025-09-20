# Open a x64 command prompt of Visual Studio,
# then type "powershell.exe", 
# then ".\compile_msvc.ps1".

$clVersion = cl.exe 2>&1 | Select-String "Version"
$clVersionNumber = $clVersion -replace '.*Version ([\d\.]+).*', '$1'
echo "msvc version: $clVersionNumber"
echo "$clVersionNumber" | Out-File -FilePath "version_msvc.txt"

$cmds = @("cl.exe /std:c++17","cl.exe /std:c++17 /O2 /DNDEBUG","cl.exe /std:c++20","cl.exe /std:c++20 /O2 /DNDEBUG","cl.exe /std:c++20 /DTINY_OPTIONAL_NO_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS","cl.exe /std:c++20 /O2 /DNDEBUG /DTINY_OPTIONAL_NO_TRIVIAL_SPECIAL_MEMBER_FUNCTIONS")

$RESULT_NAME = "result_msvc.csv"
echo "Testcode" | Out-File -NoNewline -FilePath $RESULT_NAME
for ($i=0; $i -lt $cmds.length; $i++){
    $cmd = $cmds[$i]
    echo ";$cmd" | Out-File -NoNewline -Append -FilePath $RESULT_NAME
}
echo "" | Out-File -Append -FilePath $RESULT_NAME


Get-ChildItem ".\" -Filter *.cpp | 
Foreach-Object {
    $filename = $_.Name
    echo "============ Compiling $filename ============"
    
    echo "$filename" | Out-File -NoNewline -Append -FilePath $RESULT_NAME

    for ($i=0; $i -lt $cmds.length; $i++){
        $cmd = $cmds[$i]
        $fullCmd = "$cmd /I../../include /nologo $filename"
        echo "Compiling with: '$fullCmd'"

        $timing = Measure-Command { iex $fullCmd }

        $elapsedInSeconds = $timing.TotalSeconds
        echo ";$elapsedInSeconds" | Out-File -NoNewline -Append -FilePath $RESULT_NAME
    } 

    echo "" | Out-File -Append -FilePath $RESULT_NAME
    #echo "elapsedInSeconds = $elapsedInSeconds"
    echo " "
    echo " "
}
