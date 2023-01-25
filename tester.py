import os
import shutil
import sys
import time


class Tester:

    def __init__(self, dir, sort=False, showdiff=False, notree=False, unit=False, broad=False, difftm=False, nocomments=False):
        self.sort = sort
        self.showdiff = showdiff
        self.notree = notree
        self.unit = unit
        self.broad = broad
        self.difftm = difftm
        self.nocomments = nocomments
        self.src_dir = os.path.join(dir, 'src')
        self.test_dir = os.path.join(dir, 'test')
        if broad:
            self.test_dir = os.path.join(self.test_dir, 'BroadTests')
        if unit:
            self.test_dir = os.path.join(self.test_dir, 'UnitTests')
        self.tmp_dir = os.path.join(dir, 'tmp')

        if not os.path.exists(self.tmp_dir):
            os.mkdir(self.tmp_dir)

    def run_all(self, flags=''):
        self.execute(self.src_dir, 'make clean')
        compiler = os.path.join(self.src_dir, 'c-')
        if not os.path.exists(compiler):
            self.execute(self.src_dir, 'make')

        print(f'Running all tests in \'{self.test_dir}\'')
        tests = [f[:-3] for f in os.listdir(self.test_dir) if f.endswith('.c-')]
        tests.sort()

        diffs = {}
        total_diff_count = 0
        passed_tests = []
        failed_tests = []
        for i, test in enumerate(tests):
            print(f'Running {test} {i + 1}/{len(tests)}...', end='')
            diff_count = 0
            if self.difftm:
                diff_count = self.run_tm(test, flags=flags, clean=False)
            else:
                diff_count = self.run(test, flags=flags, clean=False)
            if not diff_count:
                passed_tests.append(test)
                self.success_msg(f'[ PASSED ({diff_count} diff) ]')
            else:
                failed_tests.append(test)
                self.error_msg(f'[ FAILED ({diff_count} diff) ]')
                diffs[test] = diff_count
            total_diff_count += diff_count

        if len(passed_tests) == len(tests):
            self.remove_tmp()
            self.success_msg('=' * 32)
            self.success_msg(f'Passed {len(passed_tests)}/{len(tests)} tests; {total_diff_count} diff')
            self.success_msg('=' * 32)
        else:
            self.error_msg('=' * 32)
            self.error_msg(f'Passed {len(passed_tests)}/{len(tests)} tests; {total_diff_count} diff')
            min_diff = min(diffs, key=diffs.get)
            self.error_msg(f'Min diff: {min_diff} ({diffs[min_diff]} diff)')
            self.error_msg('=' * 32)

        self.execute(self.src_dir, 'make clean')
        return passed_tests, failed_tests, total_diff_count

    def run(self, test, flags='', clean=True):
        src = os.path.join(self.test_dir, test + '.c-')
        out = os.path.join(self.test_dir, test + '.out')
        actual = os.path.join(self.tmp_dir, test + '.actual')
        expected = os.path.join(self.tmp_dir, test + '.expected')
        compiler = os.path.join(self.src_dir, 'c-')

        if not os.path.exists(compiler):
            self.execute(self.src_dir, 'make')

        if not os.path.exists(compiler):
            raise Exception('Compilation failed')

        src_cp = os.path.join(self.tmp_dir, test + '.c-')
        os.system(f'cp {src} {src_cp}')

        if self.sort:
            os.system(f'sort {out} > {expected}')
            tmp_actual = os.path.join(self.tmp_dir, 'tmp.out')
            os.system(f'{compiler} {src} {flags} > {tmp_actual}')
            os.system(f'sort {tmp_actual} > {actual}')
            os.remove(tmp_actual)
        else:
            os.system(f'cp {out} {expected}')
            os.system(f'{compiler} {src} {flags} > {actual}')

        if self.notree:
            self.remove_tree(expected)
            self.remove_tree(actual)

        if clean:
            self.execute(self.src_dir, 'make clean')

        diff = os.path.join(self.tmp_dir, test + '.diff')
        os.system(f'diff {expected} {actual} > {diff}')

        diff_count = self.count_diff(diff)
        if not diff_count:
            os.remove(expected)
            os.remove(actual)
            os.remove(diff)
            os.remove(src_cp)
        else:
            if self.showdiff:
                os.system(f'diff {expected} {actual}')
        return diff_count

    def run_tm(self, test, flags='', clean=True):
        src = os.path.join(self.test_dir, test + '.c-')
        out = os.path.join(self.test_dir, test + '.tm')
        tm = os.path.join(self.tmp_dir, test + '.tm')
        actual = os.path.join(self.tmp_dir, test + '.actual')
        expected = os.path.join(self.tmp_dir, test + '.expected')
        compiler = os.path.join(self.src_dir, 'c-')

        if not os.path.exists(compiler):
            self.execute(self.src_dir, 'make')

        if not os.path.exists(compiler):
            raise Exception('Compilation failed')

        src_cp = os.path.join(self.tmp_dir, test + '.c-')
        os.system(f'cp {src} {src_cp}')

        if self.sort:
            os.system(f'sort {out} > {expected}')
            raise Exception('Shouldnotsort')
        else:
            os.system(f'cp {out} {expected}')
        os.system(f'cp {out} {tm}')

        os.system(f'{compiler} {src} {flags}')
        tmp_actual = test + '.tm'
        if self.sort:
            os.system(f'sort {tmp_actual} > {actual}')
            os.remove(tmp_actual)
        else:
            os.system(f'mv {tmp_actual} {actual}')

        if self.notree:
            self.remove_tree(expected)
            self.remove_tree(actual)

        if self.nocomments:
            self.remove_comments(expected)
            self.remove_comments(actual)

        if clean:
            self.execute(self.src_dir, 'make clean')

        diff = os.path.join(self.tmp_dir, test + '.diff')
        os.system(f'diff {expected} {actual} > {diff}')

        diff_count = self.count_diff(diff)
        if not diff_count:
            os.remove(expected)
            os.remove(actual)
            os.remove(diff)
            os.remove(src_cp)
            os.remove(tm)
        else:
            if self.showdiff:
                os.system(f'diff {expected} {actual}')
        return diff_count

    def remove_tmp(self):
        if os.path.exists(self.tmp_dir):
            shutil.rmtree(self.tmp_dir)

    @staticmethod
    def count_diff(diff):
        diff_count = 0
        with open(diff, 'r') as file:
            for line in file.readlines():
                if line.startswith('>') or line.startswith('<'):
                    diff_count += 1
        return diff_count

    @staticmethod
    def execute(dir, cmd):
        cwd = os.getcwd()
        os.chdir(dir)
        os.system(cmd)
        os.chdir(cwd)

    @staticmethod
    def remove_tree(out):
        lines = []
        with open(out, 'r') as file:
            for line in file:
                if line.startswith('ERROR') or line.startswith('WARNING') or line.startswith('Number of '):
                    lines.append(line)
        with open(out, 'w') as file:
            file.write(''.join(lines))

    @staticmethod
    def remove_comments(out):
        lines = []
        with open(out, 'r') as file:
            for line in file:
                if not line.startswith('*'):
                    lines.append(line)
        with open(out, 'w') as file:
            file.write(''.join(lines))

    @staticmethod
    def bold_msg(msg, endc='\n'):
        print(f'\033[1m{msg}\033[0m', end=endc)

    @staticmethod
    def error_msg(msg, endc='\n'):
        Tester.bold_msg(f'\033[91m{msg}\033[0m', endc)

    @staticmethod
    def success_msg(msg, endc='\n'):
        Tester.bold_msg(f'\033[92m{msg}\033[0m', endc)

    @staticmethod
    def warn_msg(msg, endc='\n'):
        Tester.bold_msg(f'\033[93m{msg}\033[0m', endc)


def help():
    print('Usage: python3 tester.py hw_dir -flag --flag')

    print('\nTest Flags:')
    print('--help          Displays this help menu.')
    print('--sort          Sort the output files before diff.')
    print('--showdiff      Shows test diffs in the terminal.')
    print('--notree        Remove all AST output before diffing.')
    print('--rmtmp         Remove the \'tmp/\' directory after testing.')
    print('--unit          Run tests in the \'UnitTests/\' directory.')
    print('--broad         Run tests in the \'BroadTests/\' directory.')
    print('--difftm        Use \'.tm\' files in diff comparison.')
    print('--nocomments    Remove comments from \'.tm\' files before diffing.')

    print('\nCompiler Flags:')
    print('-h:    Print compiler usage message')
    print('-d:    Turn on parser debugging.')
    print('-D:    Turn on symbol table debugging.')
    print('-p:    Print the abstract syntax tree.')
    print('-P:    Print the abstract syntax tree plus type information.')
    print('-M:    Print the abstract syntax tree plus type and memory information.')

    print('\nFor this project:')
    print('$ python3 tester.py hw1/')
    print('$ python3 tester.py hw2/ -p')
    print('$ python3 tester.py hw3/ -p --sort')
    print('$ python3 tester.py hw4/ -P --sort')
    print('$ python3 tester.py hw5/ -P --sort')
    print('$ python3 tester.py hw6/ -M --sort')
    print('$ python3 tester.py hw7/ --difftm --nocomments --unit ')
    print('$ python3 tester.py hw7/ --difftm --nocomments --broad')


if __name__ == '__main__':
    test_flags = {'--help': False, '--sort': False, '--showdiff': False, '--notree': False, '--rmtmp': False, '--unit': False, '--broad': False, '--difftm': False, '--nocomments': False}
    compiler_flags = ''

    argc = len(sys.argv)
    if argc < 2:
        help()
        raise Exception('Insufficient args provided')
    elif argc == 2:
        if sys.argv[1] == '--help':
            help()
            sys.exit()
        if not os.path.exists(sys.argv[1]) or not os.path.isdir(sys.argv[1]):
            raise Exception('Invalid directory provided')
    elif argc > 2:
        cmd_flags = sys.argv[2:]
        for flag, value in test_flags.items():
            if flag in cmd_flags:
                test_flags[flag] = True
                cmd_flags.remove(flag)
        compiler_flags = ' '.join(cmd_flags)

    if test_flags['--unit'] and test_flags['--broad']:
        raise Exception('Run either unit or broad tests, not both')

    tester = Tester(sys.argv[1], sort=test_flags['--sort'], showdiff=test_flags['--showdiff'], notree=test_flags['--notree'], unit=test_flags['--unit'], broad=test_flags['--broad'], difftm=test_flags['--difftm'], nocomments=test_flags['--nocomments'])

    passed_tests, failed_tests, diff_count = tester.run_all(compiler_flags)
    with open('test.history', 'a') as history:
        cmd = ' '.join(sys.argv)
        failed_tests_str = '"[' + ', '.join(['\'' + t + '\'' for t in failed_tests]) + ']"'
        history.write(f'{time.time()},"python3 {cmd}",{len(passed_tests)},{len(passed_tests) + len(failed_tests)},{diff_count},{failed_tests_str}\n')

    if test_flags['--rmtmp']:
        tester.remove_tmp()
