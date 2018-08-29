import sys, os
from spec import sections
from subprocess import call, DEVNULL

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

COMPILE_CMD = 'g++'
COMPILE_FLAGS = '-std=c++11'
printing = False
desc = False

def parseCommand(cmd, content=None, testPath=None, compileFlags=None):
    global printing, desc
    cmds = cmd.split(' ')
    if content:
        if 'start' in cmds:
            content.write('\\begin{lstlisting}\n')
            printing = True
        elif 'end' in cmds:
            content.write('\\end{lstlisting}\n')
            printing = False
        elif 'desc' in cmds:
            printing = True
            desc = True
    else:
        for cmd in cmds:
            if cmd.startswith('test='):
                if testPath != None:
                    testPath.append(cmd[5:])
            if cmd.startswith('flag=') or cmd.startswith('flags='):
                if compileFlags != None:
                    compileFlags.append(cmd[5:])

def gen():
    global printing, desc
    with open('content.tex', 'w+') as content:
        for sectionName, section in sections.items():
            content.write('\\section{'+sectionName+'}\n')
            for codeTitle, codeFile in section.items():
                content.write('\\subsection{'+codeTitle+'}\n')
                print('Inserting ' + bcolors.OKBLUE + codeFile + bcolors.ENDC)
                with open(codeFile) as f:
                    for line in f:
                        sline = line.strip()
                        if (sline.startswith('//---codebook ') or
                                sline.startswith('/*---codebook ') or
                                sline.startswith('%---codebook ')):
                            parseCommand(sline[14:].strip(), content)
                        elif sline.startswith('*/') and desc:
                            printing = False
                            desc = False
                        elif printing:
                            content.write(line)

def testSingle(testDir, filename):
    # Look for the test commands
    testCasesList = []
    userCompileFlags = []
    with open(filename, 'r') as f:
        for line in f:
            sline = line.strip()
            if (sline.startswith('//---codebook ') or
                    sline.startswith('/*---codebook ')):
                parseCommand(sline[14:].strip(), content=None, 
                        testPath=testCasesList, compileFlags=userCompileFlags)
    # Compile the program
    if userCompileFlags:
        ret = call([COMPILE_CMD] + userCompileFlags + [filename])
    else:
        ret = call([COMPILE_CMD, COMPILE_FLAGS, filename])
    if ret:
        print('   ' + bcolors.FAIL + 'Error: ' + bcolors.ENDC + \
                'Compile failed, skip the test.')
        return ret

    numTest = 0
    numSucc = 0
    for testCases in testCasesList:
        print('   Running testsuite ' + bcolors.OKBLUE + testCases + bcolors.ENDC)
        testCasesPath = os.path.join(testDir, testCases)
        if not os.path.isdir(testCasesPath):
            print('   ' + bcolors.WARNING + 'Warn: ' + bcolors.ENDC + \
                    'The testsuite ' + bcolors.OKBLUE + testCases + \
                    bcolors.ENDC + 'does not exist, skip.')
            continue
        succTests = []
        for root, dirs, files in os.walk(testCasesPath):
            dirs[:] = []
            files = [f for f in files if f.endswith('.in')]
            for inputName in files:
                print('    ' + inputName, end='...')
                outputName = inputName[:-3] + '.out'
                inputFileName = os.path.join(root, inputName)
                outputAnsName = os.path.join(root, outputName)
                numTest+=1
                succ = True
                with open(inputFileName, 'r') as inputFile:
                    with open(os.path.join('tmp', outputName), 'w+') as outputFile:
                        ret = call(['./a.out'], stdin=inputFile, stdout=outputFile)
                        if ret:
                            print(bcolors.WARNING + 'RE' + bcolors.ENDC)
                            succ = False
                ret = call(['diff', os.path.join('tmp', outputName), outputAnsName])
                if ret:
                    print(bcolors.FAIL + 'WA' + bcolors.ENDC)
                    succ = False
                if(succ):
                    numSucc+=1
                    succTests.append(os.path.join('tmp', outputName))
                    print(bcolors.OKGREEN + 'PASS' + bcolors.ENDC)
        for succTest in succTests:
            os.remove(succTest)
    os.remove('a.out')
    if numTest == 0:
        print('   ' + bcolors.WARNING + 'Warn: ' + bcolors.ENDC + \
                'There\'s no testsuite to run for the snippet')

def testAllCode(testDir):
    excluded = ['tests', '__pycache__', 'tmp']
    included = ('.cpp', '.c')
    for root, dirs, files in os.walk('.'):
        dirs[:] = [d for d in dirs if d not in excluded]
        files[:] = [f for f in files if f.endswith(included)]
        path = root.split(os.sep)
        print(' '*(len(path)-1) + 'Testing code in ' + bcolors.OKBLUE + path[-1] + bcolors.ENDC)
        for filename in files:
            print(' '*(len(path)) + '--Testing ' + bcolors.OKBLUE + filename + bcolors.ENDC)
            testSingle(testDir, os.path.join(os.path.join( \
                    os.path.dirname(os.path.abspath(__file__)), \
                    root), filename))

def testCodebook(testDir):
    included = ('.cpp', '.c')
    for sectionName, section in sections.items():
        print('Testing the ' + bcolors.OKBLUE + sectionName + bcolors.ENDC + ' section')
        for codeTitle, codeFile in section.items():
            print(' --Testing ' + bcolors.OKBLUE + codeTitle + bcolors.ENDC)
            testSingle(testDir, os.path.join( \
                    os.path.dirname(os.path.abspath(__file__)), \
                    codeFile))

def test(testAll=True, testDir='tests'):
    testDir = os.path.join(os.path.dirname(os.path.abspath(__file__)), testDir)
    try:
        os.mkdir('tmp')
    except FileExistsError as e:
        pass
    if testAll:
        print('Testing all the code in the directories...')
        testAllCode(testDir)
    else:
        print('Testing code mentioned in spec.py only')
        testCodebook(testDir)

if __name__ == '__main__':
    if len(sys.argv) == 1:
        print('Please specify a command')
        quit()
    if 'generate'.startswith(sys.argv[1]):
        gen()
        call(['pdflatex', '-jobname=codebook', 'template.tex'], stdout=DEVNULL)
        if len(sys.argv) > 2 and sys.argv[2] == '-v':
            call(['pdflatex', '-jobname=codebook', 'template.tex'])
    elif sys.argv[1] == 'test':
        if len(sys.argv) == 2:
            test(False)
        elif sys.argv[2] == 'all':
            test(True)
        else:
            test(False)
