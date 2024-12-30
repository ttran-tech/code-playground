import dis

def say_hello():
    print("Hello world")

print(dis.Bytecode(say_hello))