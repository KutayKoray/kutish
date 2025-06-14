#!/usr/bin/env python3

import subprocess
import difflib
import os
import shutil
import re

MINISHELL_PATH = './minishell'
VALGRIND_PATH = shutil.which('valgrind')
ERROR_FILE = 'Errors.txt'

TEST_CASES = [
    # Basit
    'echo hello world',
    'ls -la',
    'pwd',
    'cat < testfile',
    'echo A | cat | grep A',
    'ls | wc -l',
    'echo $?',
    
    # ENVIRONMENT
    'export VAR=hello',
    'echo $VAR',
    'export EMPTY=""',
    'echo $EMPTY',
    'unset VAR',
    'echo $VAR',
    'echo "$UNDEFINED"',
    'export VAR=val',
    'echo "$VAR"',
    'export A="one two"',
    'echo $A',
    'export A="one"',
    'export B="two"',
    'echo $A $B',

    # QUOTES
    'echo "double quoted with spaces"',
    "echo 'single quoted with spaces'",
    'echo "mix"\'ed\'" quotes"', #
    'echo ""',
    "echo ''",
    'echo "a b"c"d e"',
    "echo 'abc'def'",

    # REDIRECTIONS
    'echo hello > out.txt',
    'cat out.txt',
    'echo first > out.txt',
    'echo second >> out.txt',
    'cat out.txt',
    'cat < out.txt',

    # PIPE
    'echo hello | cat | cat | cat',
    'ls | grep src | wc -l',

    # COMPLEX
    'export A="hello world"',
    'echo "$A" | cat > test2.txt',
    'echo "  spaced    words  " | tr -s " "',
    'echo "text" | grep "te" | wc -c',
]



def run_shell(command, shell='/bin/bash'):
    return subprocess.run(
        [shell, '-c', command],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

def run_minishell(command):
    if not VALGRIND_PATH:
        raise RuntimeError("valgrind not found. Please install it.")

    return subprocess.run(
        [
            VALGRIND_PATH,
            '--leak-check=full',
            '--show-leak-kinds=all',
            '--suppressions=readline.supp',
            '--error-exitcode=42',
            MINISHELL_PATH
        ],
        input=command + '\nexit\n',
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )


def clean_minishell_output(output: str) -> str:
    cleaned_lines = []
    for line in output.splitlines():
        if "☁" in line:
            continue
        if line.strip() == "exit":
            continue
        cleaned_lines.append(line)
    return '\n'.join(cleaned_lines)

def compare_outputs(expected, actual):
    return expected.strip() == actual.strip()

def print_section(title, content):
    print(f"\n>>> {title}")
    print(content.strip() if content.strip() else "(empty)")

def write_error_log(index, command, bash_out, mini_out, diff_out, mem_leak):
    with open(ERROR_FILE, 'a') as f:
        f.write(f"🧪 Test {index}: `{command}`\n")
        f.write(">>> BASH STDOUT\n")
        f.write(bash_out.strip() + "\n\n")
        f.write(">>> MINISHELL STDOUT\n")
        f.write(mini_out.strip() + "\n\n")
        f.write(">>> DIFF\n")
        f.write(diff_out.strip() + "\n\n")
        if mem_leak:
            f.write(">>> MEMORY LEAK DETECTED ❌\n")
        f.write("=" * 60 + "\n\n")

def main():
    if not os.path.exists(MINISHELL_PATH):
        print("❌ minishell not found at ./minishell")
        return

    # Clear previous error log
    if os.path.exists(ERROR_FILE):
        os.remove(ERROR_FILE)

    print("🔍 Starting tests...\n")

    for i, command in enumerate(TEST_CASES, 1):
        print(f"🧪 Test {i}: `{command}`")

        bash_result = run_shell(command)
        bash_stdout = bash_result.stdout.strip()
        bash_stderr = bash_result.stderr.strip()

        mini_result = run_minishell(command)
        mini_stdout = clean_minishell_output(mini_result.stdout)
        mini_stderr = mini_result.stderr.strip()

        success = compare_outputs(bash_stdout, mini_stdout)
        mem_ok = mini_result.returncode != 42

        print_section("BASH STDOUT", bash_stdout)
        print_section("MINISHELL STDOUT", mini_stdout)

        if bash_stderr or mini_stderr:
            print_section("BASH STDERR", bash_stderr)
            print_section("MINISHELL STDERR", mini_stderr)

        if success:
            print("✅ Output match")
        else:
            print("❌ Output mismatch")
            diff = '\n'.join(difflib.unified_diff(
                bash_stdout.splitlines(),
                mini_stdout.splitlines(),
                fromfile='bash',
                tofile='minishell',
                lineterm=''
            ))
            print_section("DIFF", diff)
            write_error_log(i, command, bash_stdout, mini_stdout, diff, not mem_ok)

        if mem_ok:
            print("✅ No memory leak")
        else:
            print("❌ Memory leak detected")
            if success:
                write_error_log(i, command, bash_stdout, mini_stdout, "(no diff)", True)

        print("\n" + "=" * 60 + "\n")

if __name__ == "__main__":
    main()
