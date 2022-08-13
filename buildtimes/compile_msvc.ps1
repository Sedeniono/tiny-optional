# Open a x64 command prompt of Visual Studio,
# then type "powershell.exe", 
# then ".\compile_msvc.ps1".

$RESULT_NAME = "result_msvc.csv"

$cmds = @("cl.exe /std:c++17","cl.exe /std:c++17 /O2")

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
