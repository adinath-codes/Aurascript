@echo off
echo --- Setting up AuraScript Environment ---

:: Adds current folder to the User PATH so you can run 'aura' from any terminal
setx PATH "%PATH%;%~dp0"

echo AuraScript has been added to your PATH.
echo Please restart your terminal for changes to take effect.
echo Try running: aura examples\demo.aura
echo Try running: python examples\demo.aura
echo THEN COMAPARE THEIR RUNTIME SECONDS OF THAT SIMPLE PRINTING MECHANISM OF A WHILE LOOP
pause