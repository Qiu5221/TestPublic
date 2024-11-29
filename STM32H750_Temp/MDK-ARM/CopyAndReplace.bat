%删除hex、map、bin文件%
del /Q ..\Output\*.hex
del /Q ..\Output\*.map
del /Q ..\Output\*.bin
del /Q ..\Output\*.sct

%复制hex、map、bin文件%
copy Objects\*.hex ..\Output\*.hex
copy Listings\*.map ..\Output\*.map
copy Objects\*.bin ..\Output\*.bin
copy Objects\*.sct ..\Output\*.sct

%del /Q ..\..\..\Output\TreeFrog3Boot.hex%


%copy Objects\*.hex ..\..\..\Output\%
