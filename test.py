import subprocess
import sys
import os

testTarget = sys.argv[1]
mode = 'cmake-build-debug'
exeFile_Path = os.path.join('.', testTarget, mode, testTarget)

caseFolder_Path = './TestCases/'
caseFolder = [
    "case_01",
    "case_02",
    "case_03",
    "case_04",
    "case_05",
    "case_06"
]

if sys.platform == 'win32':
    exeFile_Path = os.path.join('.', testTarget, mode, f'{testTarget}.exe')

for case in caseFolder:
    print(f"running {case}")
    caseFolderFullPath = os.path.join(caseFolder_Path, case)
    if not os.path.exists(caseFolderFullPath):
        print(f"Folder not found: {caseFolderFullPath}")
        continue
    
    caseFileIn_Path = os.path.join(caseFolderFullPath, f'{case}.in')
    caseFileOut_Path = os.path.join(caseFolderFullPath, f'{case}.out')
    genFile_Path = os.path.join(caseFolderFullPath, f'{case}.txt')
    
    # 将错误输出附加到生成文件的末尾
    with open(genFile_Path, 'a') as f_gen:
        genCmd = f'"{exeFile_Path}" "{caseFileIn_Path}"'
        process = subprocess.run(genCmd, shell=True, stdout=f_gen, stderr=subprocess.PIPE)
        # 将标准错误输出写入生成文件末尾
        f_gen.write(process.stderr.decode())

