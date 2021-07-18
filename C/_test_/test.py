import time
from sys import argv

def testadd(a, b):
    begin = time.time_ns()
    c = a + b
    duration = time.time_ns() - begin
    print(c)
    print("[i] Addition took: {}ns".format(duration))

def testsub(a, b):
    begin = time.time_ns()
    c = a - b
    duration = time.time_ns() - begin
    print(c)
    print("[i] Subtraction took: {}ns".format(duration))
    

def testmul(a, b):
    begin = time.time_ns()
    c = a * b
    duration = time.time_ns() - begin
    print(c)
    print("[i] Multiplication took: {}ns".format(duration))

def testdiv(a, b):
    begin = time.time_ns()
    c = a // b
    duration = time.time_ns() - begin
    print(c)
    print("[i] Division took: {}ns".format(duration))


if argv[1] == 'a':
    testadd(int(argv[2]), int(argv[3]))
elif argv[1] == 's':
    testsub(int(argv[2]), int(argv[3]))
elif argv[1] == 'm':
    testmul(int(argv[2]), int(argv[3]))
elif argv[1] == 'd':
    testdiv(int(argv[2]), int(argv[3]))
