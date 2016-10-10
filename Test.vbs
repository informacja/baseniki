Dim oShell
Set oShell = WScript.CreateObject ("WSCript.shell")
oShell.run  "Test.cmd",0
Set oShell = Nothing
