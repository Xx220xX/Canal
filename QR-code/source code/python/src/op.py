import os, shutil, re


def nextFile():
    i = 1
    while os.path.exists(f"R{i}"):
        i += 1
    return (f'R{i}', i)


last = 'Template'
dest, n = nextFile()

try:
    if not os.path.exists(dest):
        os.mkdir(dest)
    for file in os.listdir(last):
        shutil.copy(f'{last}/{file}', dest)
        nextFile = re.sub('relatorio [\\d]+', f'relatorio {n}', file)
        os.rename(f'{dest}/{file}', f"{dest}/{nextFile}");
except Exception as e:
    print(e)
